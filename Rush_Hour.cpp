#include <iostream>
#include"mygraphics.h"		//Using a different library because the library provided by sir was giving too much errors
#include"myconsole.h"
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

//List of all the functions used in the game

void showhighscores();
bool decidehighscore(int highscores[20],string scoresnames[20],int score,string name);
void drawtree(int x,int y);
void drawcar(int x,int y);
void drawtaxi(int x,int y,int taxicolor);
void drawtaximenu(int x,int y,int taxicolor);
void drawperson(int x,int y,int type);
void drawbox(int x,int y);
void getRandom(int&x,int&y);
bool avoidHit(int x,int y,int arr[6][2],int taxiX,int taxiY,bool simplecar,int personArr[3][2]);
void getRandomDest(int&x,int&y,int arr[6][2]);
bool checkHitting(int x,int y,int arr[6][2],int personArr[3][2],int carArr[10][6],int totalcars,int car1x,int car1y,int car2x,int car2y,int&object);
void putObstacles(int arr[6][2]);
void putPeople(int arr[3][2]);
void fillPeople(int arr[3][2],int obstaclesArr[6][2]);
bool nearperson(int arr[3][2],int x,int y,int& pickX,int& pickY);
void drawDestination(int x,int y);
void checkArrival(int destX,int destY,int x,int y,bool&personInCar,int peopleArr[3][2],bool&picked,int&totalScore,int&dropped,int obstaclesArr[6][2]);
bool checkOvertake(int carX,int carY,int x,int y);
int game(string playername);

//Main for this program

int main()
{
	int menuoption,count=0,scorenow,linelen,pos,highscores[20];
	string line,playername,linescore,linename,scoresnames[20];
	bool higher=false;

	//list of colors used in main

	COLORREF grey = RGB(128,128,128);
	COLORREF white = RGB(255,255,255);
	COLORREF black = RGB(00,00,00);
	COLORREF text = RGB(64,128,128);
	COLORREF darkgrey = RGB(50,50,50);
	COLORREF green = RGB(0,204,0);
	COLORREF peach = RGB(255,178,102);
	COLORREF yellow = RGB (255,255,0);
	COLORREF red = RGB(255,0,0);
	COLORREF red2=RGB(180,0,0);
	COLORREF grey2 = RGB(100,100,100);

	//Intro Screen

	myRect(5,5,765,455,grey2,grey2);	//Drawing grey rectangle as board

	for(int i=0;i<200;i=i+2)		//Loop to display intro name that brightens with time
	{
		COLORREF grey = RGB(i,i,i);
		myDrawTextWithFont(200,160,100,"RUSH HOUR",grey,black);		//Name of Game
		myLine(10,10,760,10,grey);		//Upper horizontal line
		myLine(10,10,10,450,grey);		//Left verical line
		myLine(760,10,760,450,grey);	//Right vertical line
		myLine(10,450,760,450,grey);	//Lower horizontal line
		Sleep(50);
	}
	myDrawText(300,280,10,"Press any key to continue",white,black);
	getch();
	myDrawText(300,280,10,"Press any key to continue",black,black);
	myDrawTextWithFont(200,160,100,"RUSH HOUR",grey2,grey2);

	//Menu for the Game

	myDrawTextWithFont(300,15,70,"MENU",grey2,red2);
	myDrawTextWithFont(60,120,40,"1- Start a New Game",red2,grey2);
	myDrawTextWithFont(400,120,40,"2- Check Highscores",red2,grey2);
	myDrawText(200,280,10,"Enter a number to choose its corresponding option",white,red2);
	cin>>menuoption;	//Input menu option
	system("CLS");		//Clear screen

	if(menuoption==1)	//Chosen to start the game
	{
		HANDLE myconsole=GetStdHandle(STD_OUTPUT_HANDLE);	//Code to set cursor on screen
		COORD mycursor;
		mycursor.X=0;										//Setting X coordinate for cursor
		mycursor.Y=3;										//Setting Y coordinate for cursor
		SetConsoleCursorPosition(myconsole,mycursor);

		//Input name screen

		myDrawTextWithFont(10,5,40,"Enter your first name:",black,grey);
		cin>>playername;
		system("CLS");

		scorenow=game(playername);		//Calling our main game function that return total score

		//Code to read highscores from file to decide if new high score has been made

		ifstream ScoreReadFile("highscores.txt");
		while(!ScoreReadFile.eof())
		{
			ScoreReadFile>>line;
			scoresnames[count]=line;
			pos=line.find("-");
			linescore=line.substr(0,pos);
			stringstream geek(linescore);
			geek>>highscores[count];
			count++;
		}
		ScoreReadFile.close();

		higher=decidehighscore(highscores,scoresnames,scorenow,playername);
		if(higher==true)
		{
			system("CLS");
			myDrawTextWithFont(190,100,80,"New High Score!",grey,black);
			Sleep(2000);
			ofstream ScoreWriteFile("highscores.txt");
			for(int i=0;i<10;i++)
				ScoreWriteFile<<scoresnames[i]<<std::endl;
			ScoreWriteFile.close();
		}
		_getch();
		system("CLS");
	}
	else if(menuoption==2)		//Chosen to Display Highscores on screen
	{
		showhighscores();		//Calls function that show highscores
		_getch();
		system("CLS");
	}
	_getch();
	system("pause");
}


void showhighscores()		//This function reads highscores from file and display them on screen
{
	//colors used in this function
	COLORREF grey = RGB(128,128,128);
	COLORREF black = RGB(00,00,00);

	//variables used in this function
	string scoresnames[20];
	int highscores[20];
	int count=0,len,pos;
	string linescore;
	string line;

	//File handling to read high scores
	ifstream ScoreReadFile("highscores.txt");
	while(!ScoreReadFile.eof())
	{
		ScoreReadFile>>line;
		len=line.length();
		pos=line.find("-");
		scoresnames[count]=line.substr(pos+1,len-pos);
		linescore=line.substr(0,pos);
		stringstream geek(linescore);
		geek>>highscores[count];
		count++;
	}
	ScoreReadFile.close();
	cout<<endl<<endl<<endl<<endl<<endl;

	//Loop to output highscores
	for(int i=0;i<10;i++)
	{
		if(i==9)
			cout<<"      "<<i+1<<"-"<<scoresnames[i]<<" : "<<highscores[i];
		else
			cout<<"      "<<i+1<<"-"<<scoresnames[i]<<" : "<<highscores[i]<<endl<<endl;
	}

		//Display highscore screen and board
		myDrawTextWithFont(10,10,40,"Top 10 high scores",grey,black);
		myLine(5,5,270,5,grey);		//Upper horizontal line
		myLine(270,5,270,400,grey);	//Right vertical line
		myLine(5,400,270,400,grey);	//Lower horizontal line
}

bool decidehighscore(int highscores[20],string scoresnames[20],int score,string name)		//This function decides if a new highscore has been made
{
	//variables used in this function
	int temp1;
	string temp2;
	bool high=false;

	stringstream ss;  
	ss<<score;  
	string scoring;  
	ss>>scoring;  

	//checks if new score is greater than the score that is last in the list of highscores
	if(score>highscores[9])
	{
		highscores[9]=score;
		scoresnames[9]=scoring + "-" + name;
		high=true;
	}

	//Sorts the highscore array to sort high scores
	for(int i=0;i<10;i++)
	 {
		 for(int j=0;j<10-i;j++)
		 {
			if(highscores[j]<highscores[j+1])
			 {
				 temp1=highscores[j];
				 highscores[j]=highscores[j+1];
				 highscores[j+1]=temp1;
				 temp2=scoresnames[j];
				 scoresnames[j]=scoresnames[j+1];
				 scoresnames[j+1]=temp2;
			 }
		 }
	 }
	return high;
}

void drawtree(int x,int y)		//This function draws a tree on random position on screen
{
	COLORREF green = RGB(0,128,0);
	COLORREF brown = RGB(139,69,19);
	myRect(x-2,y-2,x+2,y+10,brown,brown);		//Draws trunk of tree in brown color
	myEllipse(x-12,y-10,x+12,y+3,green,green);	//Draws Leaves of tree in green color
}

void drawcar(int x,int y)		//This function draws a car on specified position
{
	COLORREF black = RGB(00,00,00);
	COLORREF blue = RGB(0,0,150);

	myRect(x-10,y-5,x+10,y+5,blue,blue);		//Draws upper half of car
	myRect(x-20,y,x+20,y+10,blue,blue);			//Draws lower half of car
	myEllipse(x-11,y+8,x-4,y+15,black,black);	//Draws left tyre of car
	myEllipse(x+4,y+8,x+11,y+15,black,black);	//Draws right tyre of car
}

void drawtaxi(int x,int y,int taxicolor)		////This function draws our taxi on specified position
{
	COLORREF black = RGB(00,00,00);
	COLORREF tcolor;

	if(taxicolor==2)
		tcolor = RGB (255,205,0);		//Chooses yellow color for taxi
	else
		tcolor = RGB (200,0,0);			//Chooses red color for taxi

	myRect(x-10,y-5,x+10,y+5,tcolor,tcolor);	//Draws upper half of taxi
	myRect(x-20,y,x+20,y+10,tcolor,tcolor);		//Draws lower half of taxi
	myEllipse(x-11,y+8,x-4,y+15,black,black);	//Draws left tyre of taxi
	myEllipse(x+4,y+8,x+11,y+15,black,black);	//Draws right tyre of taxi
}

void drawtaximenu(int x,int y,int taxicolor)	//This function draws the menu where we have to choose our taxi color
{
	COLORREF black = RGB(00,00,00);
	COLORREF tcolor;

	if(taxicolor==1)
		tcolor = RGB (255,205,0);		//Chooses yellow color for taxi
	else if(taxicolor==2)
		tcolor = RGB (200,0,0);			//Chooses red color for taxi

	myRect(x-50,y-25,x+50,y+25,tcolor,tcolor);		//Draws upper half of taxi
	myRect(x-100,y,x+100,y+50,tcolor,tcolor);		//Draws lower half of taxi
	myEllipse(x-55,y+40,x-20,y+75,black,black);		//Draws left tyre of taxi
	myEllipse(x+20,y+40,x+55,y+75,black,black);		//Draws right tyre of taxi
}

void drawperson(int x,int y,int type)		//This function draws a passenger on random position on screen
{
	COLORREF Black = RGB(0, 0, 0);
	COLORREF White= RGB(255,255,255);
	COLORREF grey2 = RGB(100,100,100);

	if(type==0)		//Draws the passenger in black and white color
	{
		myEllipse(x, y, x+10, y+10, White,White);
		myLine(x+5,y+10,x+5,y+17,White);
		myLine(x+5,y+14,x+10,y+11,White);
		myLine(x+5,y+14,x,y+11,White);
		myLine(x+5,y+17,x+7,y+21,White);
		myLine(x+5,y+17,x+2,y+21,White);
		myEllipse(x+2, y+2, x+4, y+4, Black,Black);
		myEllipse(x+6, y+2, x+8, y+4, Black,Black);
		myEllipse(x+3, y+5, x+7, y+9, Black,Black);
		myRect(x+2, y+5, x+7, y+7, White, White);
	}
	else
	{
		myRect(x,y,x+12,y+30,grey2,grey2);		//This is used to remove passenger from board
	}
}

void drawbox(int x,int y)		//This function draws a box on random position on screen
{
	COLORREF brown = RGB(244,164,94);
	myRect(x-10,y-10,x+10,y+10,brown,brown);
}

void getRandom(int&x,int&y)		//This function is used to get random x and y coordinates on screen that are not occupied by buildings
{
	//variables used in this function
	int num;
	bool unique=false;
	while(unique==false)
	{
		x=rand()%750;
		x=x+11;
		y=rand()%440;
		y=y+11;

		//The numbers represent the number of building on the board
		//We are comparing our newly generated coordinates with the coordinates of buildings
		//If coordinates matches with those of buildings then we get random coordinates again

		if(x>=100 && y>=80 && x<=210 && y<=110)		//1
			unique=false;
		else if(x>=420 && y>=70 && x<=770 && y<=120)		//2
			unique=false;
		else if(x>=90 && y>=190 && x<=180 && y<=240)	//3
			unique=false;
		else if(x>=140 && y>=190 && x<=190 && y<=280)
			unique=false;
		else if(x>=240 && y>=190 && x<=360 && y<=240)	//4
			unique=false;
		else if(x>=310 && y>=110 && x<=360 && y<=210)
			unique=false;
		else if(x>=510 && y>=150 && x<=560 && y<=330)	//5
			unique=false;
		else if(x>=540 && y>=190 && x<=600 && y<=240)
			unique=false;
		else if(x>=650 && y>=160 && x<=700 && y<=340)	//6
			unique=false;
		else if(x>=290 && y>=260 && x<=455 && y<=310)	//7
			unique=false;
		else if(x>=405 && y>=230 && x<=455 && y<=280)
			unique=false;
		else if(x>=90 && y>=310 && x<=210 && y<=410)	//8	
			unique=false;
		else if(x>=290 && y>=280 && x<=340 && y<=430)	//9
			unique=false;
		else if(x>=410 && y>=380 && x<=770 && y<=430)	//10
			unique=false;
		else if(x>0 && y>=0 && x<=200 && y<=40)			//11
			unique=false;
		else
			unique=true;
	}
}

//This function tells if our car or taxi can hit any obstacle or building or not if it moves forward
//We decide our next movement of cars according to the boolean variable returned by this function
bool avoidHit(int x,int y,int arr[6][2],int taxiX,int taxiY,bool simplecar,int personArr[3][2])		
{
	bool notHitting;

	//The numbers represent the number of building on the board
	//We are comparing corodinates of our taxi with the coordinates of buildings,obstacles and passengers
	//If coordinates matches with any of above then we return that our taxi can hit that particular thing

	if(x>=90 && y>=80 && x<=220 && y<=110)		//1
			notHitting=false;
		else if(x>=420 && y>=70 && x<=770 && y<=120)		//2
			notHitting=false;
		else if(x>=90 && y>=190 && x<=180 && y<=240)	//3
			notHitting=false;
		else if(x>=140 && y>=190 && x<=190 && y<=280)
			notHitting=false;
		else if(x>=240 && y>=190 && x<=360 && y<=240)	//4
			notHitting=false;
		else if(x>=310 && y>=110 && x<=360 && y<=210)
			notHitting=false;
		else if(x>=510 && y>=150 && x<=560 && y<=330)	//5
			notHitting=false;
		else if(x>=540 && y>=190 && x<=600 && y<=240)
			notHitting=false;
		else if(x>=650 && y>=160 && x<=700 && y<=340)	//6
			notHitting=false;
		else if(x>=290 && y>=260 && x<=455 && y<=310)	//7
			notHitting=false;
		else if(x>=405 && y>=230 && x<=455 && y<=280)
			notHitting=false;
		else if(x>=90 && y>=310 && x<=210 && y<=410)	//8	
			notHitting=false;
		else if(x>=280 && y>=280 && x<=340 && y<=430)	//9
			notHitting=false;
		else if(x>=400 && y>=380 && x<=770 && y<=430)	//10
			notHitting=false;
		else if(x>0 && y>=0 && x<=200 && y<=40)			//11
			notHitting=false;
		else if(x>=(arr[0][0]-25) && x<=(arr[0][0]+25) && y>=(arr[0][1]-20) && y<=(arr[0][1]+15))		//Compares with obstacle 1
			notHitting=false;
		else if(x>=(arr[1][0]-25) && x<=(arr[1][0]+25) && y>=(arr[1][1]-20) && y<=(arr[1][1]+15))		//Compares with obstacle 2
			notHitting=false;
		else if(x>=(arr[2][0]-25) && x<=(arr[2][0]+25) && y>=(arr[2][1]-20) && y<=(arr[2][1]+15))		//Compares with obstacle 3
			notHitting=false;
		else if(x>=(arr[3][0]-25) && x<=(arr[3][0]+25) && y>=(arr[3][1]-20) && y<=(arr[3][1]+15))		//Compares with obstacle 4
			notHitting=false;
		else if(x>=(arr[4][0]-25) && x<=(arr[4][0]+25) && y>=(arr[4][1]-20) && y<=(arr[4][1]+15))		//Compares with obstacle 5
			notHitting=false;
		else if(x>=(arr[5][0]-25) && x<=(arr[5][0]+25) && y>=(arr[5][1]-20) && y<=(arr[5][1]+15))		//Compares with obstacle 6
			notHitting=false;
		else if(x>=(personArr[0][0]-15) && x<=(personArr[0][0]+30) && y>=(personArr[0][1]-10) && y<=(personArr[0][1]+25))	//Compares with person 1
			notHitting=false;
		else if(x>=(personArr[1][0]-15) && x<=(personArr[1][0]+30) && y>=(personArr[1][1]-10) && y<=(personArr[1][1]+25))	//Compares with person 2
			notHitting=false;
		else if(x>=(personArr[2][0]-15) && x<=(personArr[2][0]+30) && y>=(personArr[2][1]-10) && y<=(personArr[2][1]+25))	//Compares with person 3
			notHitting=false;
		else
			notHitting=true;


		if(simplecar==1)		//This runs when we are using the function for random car movement
		{
			if(x>=taxiX-40 && y>=taxiY-25 && x<=taxiX+30 && y<=taxiY+15)
				notHitting=false;
		}

		return notHitting;

}

void getRandomDest(int&x,int&y,int arr[6][2])	//This function gets coordinates to generate a random destination
{
	int num;
	bool unique=false;

	//This function is same as previous getRandom function except that it also checks obstacles
	//The numbers represent the number of building on the board
	//We are comparing our newly generated coordinates with the coordinates of buildings as well as with the obstacles
	//If coordinates matches with those of buildings then we get random coordinates again

	while(unique==false)
	{
		x=rand()%750;
		x=x+11;
		y=rand()%440;
		y=y+11;
		if(x>=100 && y>=80 && x<=210 && y<=110)		//1
			unique=false;
		else if(x>=420 && y>=70 && x<=770 && y<=120)		//2
			unique=false;
		else if(x>=90 && y>=190 && x<=180 && y<=240)	//3
			unique=false;
		else if(x>=140 && y>=190 && x<=190 && y<=280)
			unique=false;
		else if(x>=240 && y>=190 && x<=360 && y<=240)	//4
			unique=false;
		else if(x>=310 && y>=110 && x<=360 && y<=210)
			unique=false;
		else if(x>=510 && y>=150 && x<=560 && y<=330)	//5
			unique=false;
		else if(x>=540 && y>=190 && x<=600 && y<=240)
			unique=false;
		else if(x>=650 && y>=160 && x<=700 && y<=340)	//6
			unique=false;
		else if(x>=290 && y>=260 && x<=455 && y<=310)	//7
			unique=false;
		else if(x>=405 && y>=230 && x<=455 && y<=280)
			unique=false;
		else if(x>=90 && y>=310 && x<=210 && y<=410)	//8	
			unique=false;
		else if(x>=290 && y>=280 && x<=340 && y<=430)	//9
			unique=false;
		else if(x>=410 && y>=380 && x<=770 && y<=430)	//10
			unique=false;
		else if(x>0 && y>=0 && x<=200 && y<=40)			//11
			unique=false;	
		else if(x>=(arr[0][0]-20) && y>=(arr[0][1]-10) && x<=(arr[0][0]+20) && y<=(arr[0][1]+20))		//Compares with obstacle 1
			unique=false;
		else if(x>=(arr[1][0]-20) && y>=(arr[1][1]-10) && x<=(arr[1][0]+20) && y<=(arr[1][1]+20))		//Compares with obstacle 2
			unique=false;
		else if(x>=(arr[2][0]-20) && y>=(arr[2][1]-10) && x<=(arr[2][0]+20) && y<=(arr[2][1]+20))		//Compares with obstacle 3
			unique=false;
		else if(x>=(arr[3][0]-20) && y>=(arr[3][1]-10) && x<=(arr[3][0]+20) && y<=(arr[3][1]+20))		//Compares with obstacle 4
			unique=false;
		else if(x>=(arr[4][0]-20) && y>=(arr[4][1]-10) && x<=(arr[4][0]+20) && y<=(arr[4][1]+20))		//Compares with obstacle 5
			unique=false;
		else if(x>=(arr[5][0]-20) && y>=(arr[5][1]-10) && x<=(arr[5][0]+20) && y<=(arr[5][1]+20))		//Compares with obstacle 6
			unique=false;
		else
			unique=true;
	}
}

//This function checks if our taxi has hit something or not
//Then returns what object has been hit
bool checkHitting(int x,int y,int arr[6][2],int personArr[3][2],int carArr[10][6],int totalcars,int car1x,int car1y,int car2x,int car2y,int&object)
{
	bool notHitting=true;
		if(x>=(arr[0][0]-30) && x<=(arr[0][0]+30) && y>=(arr[0][1]-25) && y<=(arr[0][1]+25))
		{
			object=1;		//return 1 if taxi hits an obstacle
			notHitting=false;
		}
		else if(x>=(arr[1][0]-30) && x<=(arr[1][0]+30) && y>=(arr[1][1]-25) && y<=(arr[1][1]+20))
		{
			object=1;		//return 1 if taxi hits an obstacle
			notHitting=false;	
		}
		else if(x>=(arr[2][0]-30) && x<=(arr[2][0]+30) && y>=(arr[2][1]-25) && y<=(arr[2][1]+20))
		{
			object=1;		//return 1 if taxi hits an obstacle
			notHitting=false;
		}
		else if(x>=(arr[3][0]-30) && x<=(arr[3][0]+30) && y>=(arr[3][1]-25) && y<=(arr[3][1]+20))
		{
			object=1;		//return 1 if taxi hits an obstacle
			notHitting=false;
		}
		else if(x>=(arr[4][0]-30) && x<=(arr[4][0]+30) && y>=(arr[4][1]-25) && y<=(arr[4][1]+20))
		{
			object=1;		//return 1 if taxi hits an obstacle
			notHitting=false;
		}
		else if(x>=(arr[5][0]-30) && x<=(arr[5][0]+30) && y>=(arr[5][1]-25) && y<=(arr[5][1]+20))
		{
			object=1;		//return 1 if taxi hits an obstacle
			notHitting=false;
		}
		else if(x>=(personArr[0][0]-20) && x<=(personArr[0][0]+35) && y>=(personArr[0][1]-15) && y<=(personArr[0][1]+30))
		{
			object=2;		//return 2 if taxi hits a passenger
			notHitting=false;
		}
		else if(x>=(personArr[1][0]-20) && x<=(personArr[1][0]+35) && y>=(personArr[1][1]-15) && y<=(personArr[1][1]+30))
		{
			object=2;		//return 2 if taxi hits a passenger
			notHitting=false;
		}
		else if(x>=(personArr[2][0]-20) && x<=(personArr[2][0]+35) && y>=(personArr[2][1]-15) && y<=(personArr[2][1]+30))
		{
			object=2;		//return 2 if taxi hits a passenger
			notHitting=false;
		}
		else if(x>=car1x-30 && x<=car1x+30 && y>=car1y-30 && y<=car1y+30)
		{
			object=2;		//return 2 if taxi hits a passenger
			notHitting=false;
		}
		else if(x>=car2x-30 && x<=car2x+30 && y>=car2y-30 && y<=car2y+30)
		{
			object=2;		//return 2 if taxi hits a passenger
			notHitting=false;
		}
		for(int i=0;i<totalcars;i++)
		{
			if(x>=(carArr[i][0]-30) && x<=(carArr[i][0]+30) && y>=(carArr[i][1]-30) && y<=(carArr[i][1]+20))
			{
				object=3;		//returns 3 if taxi hits a car
				return false;
			}
		}
		return notHitting;
}

void putObstacles(int arr[6][2])		//This function randomly spreads obstacles on the board
{
	int x,y;
	for(int i=0,j=0;i<3;i++,j++)
	{
		getRandom(x,y);		//Get random coordinates
		drawtree(x,y);		//Use those coordinates to draw tree randomly
		arr[j][0]=x;		//Save the coordinates in obstacles array for later use
		arr[j][1]=y;
		getRandom(x,y);		//get random coordinates again
		drawbox(x,y);		//Use those coordinates to draw box randomly
		j++;			
		arr[j][0]=x;		//Save those coordinates in obstacles array for later use
		arr[j][1]=y;
	}
}

void putPeople(int arr[3][2])		//This functiton randomly spreads passengers on the board in the start of the game
{
	int x,y;
	for(int i=0;i<3;i++)
	{
		getRandom(x,y);		//Get random coordinates
		x=x+(i*100);
		y=y+(i*100);
		drawperson(x,y,0);	//Use the coordinates to draw a passenger
		arr[i][0]=x;		//Save those coordinates for later use
		arr[i][1]=y;
	}
}

void fillPeople(int arr[3][2],int obstaclesArr[6][2])		//spawns new passenger if any array element is null which means a person has been dropped
{
	bool dropped=false;
	int pos,x,y;
	for(int i=0;i<3;i++)		//loop checks if any passenger has been dropped or not
	{
		if(arr[i][0]=='\0')
		{
			dropped=true;
			pos=i;
		}
	}

	if(dropped==true)		//Run if a passenger has been dropped
	{
		getRandomDest(x,y,obstaclesArr);	//Get random coordinates
		drawperson(x,y,0);					//Use those coordinates to draw a new passenger on board
		arr[pos][0]=x;						//Save the coordinates for later use
		arr[pos][1]=y;
	}
}

bool nearperson(int arr[3][2],int x,int y,int& pickX,int& pickY)	//This function tells if our taxi has arrived near a passenger or not
{
	for(int i=0;i<3;i++)
	{
		if(x>=(arr[i][0]-40) && x<=(arr[i][0]+40) && y>=(arr[i][1]-30) && y<=(arr[i][1]+40))
		{
			drawperson(arr[i][0],arr[i][1],1);		//This is used to remove the passenger from the board if our taxi has picked it up
			arr[i][0]='\0';
			arr[i][1]='\0';
			return true;
		}
	}
	return false;
}

void drawDestination(int x,int y)		//This function draws the destination of a passenger on random location on board
{
	COLORREF green = RGB(0,204,0);	
	myRect(x-10,y-5,x+10,y+5,green,green);		//Draws green rectangle as destination
}

//This function checks if our taxi has arrived to the destination or not
void checkArrival(int destX,int destY,int x,int y,bool&personInCar,int peopleArr[3][2],bool&picked,int&totalScore,int&dropped,int obstaclesArr[6][2])
{
	//Colors used in this function
	COLORREF white = RGB(255,255,255);
	COLORREF black = RGB(00,00,00);
	COLORREF grey2 = RGB(100,100,100);

	if(x>=(destX-10) && y>=(destY-15) && x<=(destX+10) && y<=(destY+10))	//Compares coordinates of our taxi with the coordinates of destination 
	{
		myDrawTextWithFont(790,50,30,"Person Dropped!",black,grey2);	//Displays the message that person has been dropped 
		totalScore=totalScore+10;
		Sleep(1000);													//Waits for 1 second
		myDrawTextWithFont(790,50,30,"Person Dropped!",black,black);	//Removes the message
		fillPeople(peopleArr,obstaclesArr);								//to check and spawn a new passenger if one has been dropped
		personInCar=false;
		picked=false;
		dropped++;
		myRect(destX-10,destY-5,destX+10,destY+5,grey2,grey2);		//Removes the green destination rectangle from board
	}
}

bool checkOvertake(int carX,int carY,int x,int y)		//This function checks if our taxi has overtaken any of the car or not
{
	if(x>=(carX-10) && y>=(carY-50) && x<=(carX+10) && y<=(carY+50))	//Compares coordinates of taxi with coordiantes near other cars
		return true;
	return false;
}

int game(string playername)		//Our main function where whole game is running
{
	//Colors used in the game
	COLORREF grey = RGB(128,128,128);
	COLORREF white = RGB(255,255,255);
	COLORREF black = RGB(00,00,00);
	COLORREF text = RGB(64,128,128);
	COLORREF darkgrey = RGB(50,50,50);
	COLORREF green = RGB(0,204,0);
	COLORREF peach = RGB(255,178,102);
	COLORREF yellow = RGB (255,255,0);
	COLORREF red = RGB(255,0,0);
	COLORREF red2=RGB(180,0,0);
	COLORREF grey2 = RGB(100,100,100);
	COLORREF buttoncolor = RGB(6,189,111);
	COLORREF mustard = RGB(244,219,5);

	int taxicolor;

	//Code for taxi menu

	myRect(0,0,770,460,grey2,grey2);
	myDrawTextWithFont(180,15,70,"CHOOSE YOUR TAXI",grey2,black);
	myDrawTextWithFont(120,300,40,"1- Red Taxi",red2,grey2);
	myDrawTextWithFont(460,300,40,"2- Yellow Taxi",yellow,grey2);
	myDrawText(200,400,10,"Enter a number to choose its corresponding option",white,black);
	drawtaximenu(180,200,2);
	drawtaximenu(520,200,1);
	cin>>taxicolor;

	HANDLE myconsole=GetStdHandle(STD_OUTPUT_HANDLE);	//to set our cursor 
	COORD mycursor;

	myRect(0,0,780,470,grey2,grey2);		//Draw grey background board as roads

	//Following code is to draw black buildings on the board

	myRect(100,80,210,110,black,black);		//1
	myRect(430,80,760,110,black,black);		//2

	myRect(100,200,170,230,black,black);	//3
	myRect(150,200,180,270,black,black);

	myRect(250,200,350,230,black,black);	//4
	myRect(320,120,350,200,black,black);

	myRect(520,160,550,320,black,black);	//5
	myRect(550,200,590,230,black,black);

	myRect(660,170,690,330,black,black);	//6

	myRect(300,270,445,300,black,black);	//7
	myRect(415,240,445,270,black,black);

	myRect(100,320,200,400,black,black);	//8	

	myRect(300,290,330,420,black,black);	//9

	myRect(420,390,760,420,black,black);	//10

	myRect(0,0,200,40,black,black);	//11
	
	//Variables used in the game
	int x,y,speed,car1x,car2x,car1y,car2y,car1speed=4,pickX=0,pickY=0,destX,destY,totalScore=0,dropped=0,pairdropped=0,newX=0,newY=0,totalcars=2,hitobject=0;
	bool moveleft=true,movedown=false,moveup=false,moveright=false;
	bool moveleft1=false,movedown1=false,moveup1=false,moveright1=true,picked=false,personInCar=false;
	bool complete=false;
	bool won=false;
	char move;
	double time;
	bool timerStart=false;

	//Arrays used in the game
	char num[3];
	int obstaclesArr[6][2];
	int peopleArr[3][2];
	int carArr[10][6];

	for(int i=0;i<10;i++)		//Loop tp fill carArray with 0 at the start
	{
		for(int j=0;j<6;j++)
		{
			carArr[i][j]=0;
		}
		carArr[i][3]=1;		//Only choose the left boolean variable as true
	}

	if(taxicolor==1)	//Choose speed of taxi according to color type
		speed=10;
	else
		speed=15;

	putObstacles(obstaclesArr);		//Put obstacles on the board at the start of the game

	putPeople(peopleArr);			//Spread passengers on the board at the start of the ga,e
	
	getRandom(car1x,car1y);		//Get random coordinates
	drawcar(car1x,car1y);		//Draw first car using those coordinates

	getRandom(car2x,car2y);		//Get random coordinates
	drawcar(car2x,car2y);		//Draw second car using those coordinates

	x=30,y=60;					//Initial coordinates of our taxi
	drawtaxi(x,y,taxicolor);	//Draw taxi using those coordinates

	myDrawTextWithFont(800,10,25,"Total Score:",mustard,black);		//Display total score message

	clock_t hitStart;	//Variable to store starting of clock time
	double hitTime;		//Used to store time passed after a particular thing has happened in our code

	clock_t tStart = clock();	//This starts our main timer of the game

	while(complete!=true)
	{
		while(kbhit()==false)		//Registers keyboard key for simultaneous movements
		{
			mycursor.X=7;			
			mycursor.Y=0;
			SetConsoleCursorPosition(myconsole,mycursor);		//Set cursor in front of timer message to print time continously

			time=(double)(clock()-tStart)/CLOCKS_PER_SEC;
			time=600-time;										//Calculates time remaining
			myDrawTextWithFont(0,0,25,"Timer:",mustard,black);	//Displays timer message
			cout<<time;		//Displays time remaining

			if(pairdropped>0)		//Run if at least 2 passengers has been dropped
			{
				for(int i=1;i<pairdropped+1;i++)	//Loop to control extra cars that has been added on the board after initial 2 cars
				{
					if(carArr[i][2]==true)		//Checks if left boolean is true then move towards left
					{
						if(carArr[i][0]-car1speed>10 && avoidHit(carArr[i][0]-car1speed,carArr[i][1],obstaclesArr,x,y,1,peopleArr)) //Checks if car can move left or not
						{
							myRect(carArr[i][0]-20,carArr[i][1]-5,carArr[i][0]+20,carArr[i][1]+15,grey2,grey2);
							carArr[i][0]=carArr[i][0]-car1speed;
							drawcar(carArr[i][0],carArr[i][1]);
						}
						else		//If car can not move left then move up
						{
							carArr[i][5]=false;
							carArr[i][2]=false;
							carArr[i][4]=false;
							carArr[i][3]=true;
						}
					}
					if(carArr[i][3]==true)		//Checks if up boolean is true then move up
					{
						if(carArr[i][1]-car1speed>=10 && avoidHit(carArr[i][0],carArr[i][1]-car1speed,obstaclesArr,x,y,1,peopleArr)) //Checks if car can move up or not
						{
							myRect(carArr[i][0]-20,carArr[i][1]-5,carArr[i][0]+20,carArr[i][1]+15,grey2,grey2);
							carArr[i][1]=carArr[i][1]-car1speed;
							drawcar(carArr[i][0],carArr[i][1]);
						}
						else		//If car can not move up then move right
						{
							carArr[i][5]=false;
							carArr[i][2]=false;
							carArr[i][4]=true;
							carArr[i][3]=false;
						}
					}
					if(carArr[i][4]==true)		//Checks if right boolean is true then move towards right
					{
						if(carArr[i][0]+car1speed<=760 && avoidHit(carArr[i][0]+car1speed,carArr[i][1],obstaclesArr,x,y,1,peopleArr)) //Checks if car can move right or not
						{
							myRect(carArr[i][0]-20,carArr[i][1]-5,carArr[i][0]+20,carArr[i][1]+15,grey2,grey2);
							carArr[i][0]=carArr[i][0]+car1speed;
							drawcar(carArr[i][0],carArr[i][1]);
						}
						else		//If car can not move right then move down
						{
							carArr[i][5]=true;
							carArr[i][2]=false;
							carArr[i][4]=false;
							carArr[i][3]=false;
						}
					}
					if(carArr[i][5]==true)		//Checks if down boolean is true then move down
					{
						if(carArr[i][1]+car1speed<=450 && avoidHit(carArr[i][0],carArr[i][1]+car1speed,obstaclesArr,x,y,1,peopleArr)) //Checks if car can move down or not
						{
							myRect(carArr[i][0]-20,carArr[i][1]-5,carArr[i][0]+20,carArr[i][1]+15,grey2,grey2);
							carArr[i][1]=carArr[i][1]+car1speed;
							drawcar(carArr[i][0],carArr[i][1]);
						}
						else		//If car can not move down then move left
						{
							carArr[i][5]=false;
							carArr[i][2]=true;
							carArr[i][4]=false;
							carArr[i][3]=false;
						}
					}
				}
			}

			//To control the first car from the initial ones

			if(moveleft==true)		//Checks if left boolean is true then move towards left
			{
				if(car2x-car1speed>10 && avoidHit(car2x-car1speed,car2y,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car2x-20,car2y-5,car2x+20,car2y+15,grey2,grey2);
					car2x=car2x-car1speed;
					drawcar(car2x,car2y);
				}
				else
				{
					movedown=false;
					moveleft=false;
					moveright=false;
					moveup=true;
				}
			}
			if(moveup==true)		//Checks if up boolean is true then move up
			{
				if(car2y-car1speed>=10 && avoidHit(car2x,car2y-car1speed,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car2x-20,car2y-5,car2x+20,car2y+15,grey2,grey2);
					car2y=car2y-car1speed;
					drawcar(car2x,car2y);
				}
				else
				{
					movedown=false;
					moveleft=false;
					moveright=true;
					moveup=false;
				}
			}
			if(moveright==true)		//Checks if right boolean is true then move towards right
			{
				if(car2x+car1speed<=760 && avoidHit(car2x+car1speed,car2y,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car2x-20,car2y-5,car2x+20,car2y+15,grey2,grey2);
					car2x=car2x+car1speed;
					drawcar(car2x,car2y);
				}
				else
				{
					movedown=true;
					moveleft=false;
					moveright=false;
					moveup=false;
				}
			}
			if(movedown==true)		//Checks if down boolean is true then move down
			{
				if(car2y+car1speed<=450 && avoidHit(car2x,car2y+car1speed,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car2x-20,car2y-5,car2x+20,car2y+15,grey2,grey2);
					car2y=car2y+car1speed;
					drawcar(car2x,car2y);
				}
				else
				{
					movedown=false;
					moveleft=true;
					moveright=false;
					moveup=false;
				}
			}

			//To control the second car from the initial ones

			if(moveleft1==true)		//Checks if left boolean is true then move towards left
			{
				if(car1x-car1speed>10 && avoidHit(car1x-car1speed,car1y,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car1x-20,car1y-5,car1x+20,car1y+15,grey2,grey2);
					car1x=car1x-car1speed;
					drawcar(car1x,car1y);
				}
				else if(car1x-car1speed<=10 || !avoidHit(car1x-car1speed,car1y,obstaclesArr,x,y,1,peopleArr))
				{
					if(rand()%3==2)
					{
						movedown1=true;
						moveup1=false;
					}
					else
					{
						moveup1=true;
						movedown1=false;
					}
					moveleft1=false;
					moveright1=false;
				}
			}
			if(moveup1==true)		//Checks if up boolean is true then move up
			{
				if(car1y-car1speed>10 && avoidHit(car1x,car1y-car1speed,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car1x-20,car1y-5,car1x+20,car1y+15,grey2,grey2);
					car1y=car1y-car1speed;
					drawcar(car1x,car1y);
				}
				else
				{
					if(rand()%3==2)
					{
						moveleft1=true;
						moveright1=false;
					}
					else
					{
						moveleft1=false;
						moveright1=true;
					}
					movedown1=false;
					moveup1=false;
				}
			}
			if(moveright1==true)		//Checks if right boolean is true then move towards right
			{
				if(car1x+car1speed<=760 && avoidHit(car1x+car1speed,car1y,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car1x-20,car1y-5,car1x+20,car1y+15,grey2,grey2);
					car1x=car1x+car1speed;
					drawcar(car1x,car1y);
				}
				else
				{
					if(rand()%3==2)
					{
						movedown1=false;
						moveup1=true;
					}
					else
					{
						movedown1=true;
						moveup1=false;
					}
					moveleft1=false;
					moveright1=false;
				}
			}
			if(movedown1==true)		//Checks if down boolean is true then move down
			{
				if(car1y+car1speed<=450 && avoidHit(car1x,car1y+car1speed,obstaclesArr,x,y,1,peopleArr))
				{
					myRect(car1x-20,car1y-5,car1x+20,car1y+15,grey2,grey2);
					car1y=car1y+car1speed;
					drawcar(car1x,car1y);
				}
				else
				{
					if(rand()%3==2)
					{
						moveleft1=false;
						moveright1=true;
					}
					else
					{
						moveleft1=true;
						moveright1=false;
					}
					movedown1=false;
					moveup1=false;
				}
			}

				hitTime=(double)(clock()-hitStart)/CLOCKS_PER_SEC;		//Continously updates time passed after something happens
				if(timerStart==true)	//If timer was started then move in it
				{
					if(hitTime>2)		//If 2 seconds has been passed then remove the display message
					{
						myDrawTextWithFont(800,150,30,"Overtake!",black,black);		//print all black in order to remove display message
						myDrawTextWithFont(800,100,30,"Overtake!",black,black);
						timerStart=false;		//Set timer started to false so that everytime these things are not repeated
					}
				}
			Sleep(90);		//Adds a little delay to slow down the movement of cars
		}
		if(checkHitting(x,y,obstaclesArr,peopleArr,carArr,totalcars,car1x,car1y,car2x,car2y,hitobject)==false)		//Checks if our taxi is hitting anything
		{
				myDrawTextWithFont(800,150,30,"Hitting!",black,red2);		//if it is hititng then display message of hitting
				timerStart=true;		//Sets timer started variable to true
				hitStart = clock();		//start timer for display message

				if(hitobject==1)		//If the object that was hit was an obstacle
				{
					if(taxicolor==1)				//Deduct points according to the color of our taxi
						totalScore=totalScore-2;
					else
						totalScore=totalScore-4;
				}
				else if(hitobject==2)		//If the object that was hit was a passenger
				{
					totalScore=totalScore-5;
				}
				else if(hitobject==3)		//If the object that was hit was a car
				{
					if(taxicolor==1)				//Deduct points according to the color of our taxi
						totalScore=totalScore-3;
					else
						totalScore=totalScore-2;
				}

				num1(totalScore,num);		//function to get current score as string to be printed
				myDrawTextWithFont(910,10,25,"100",black,black);	//Removes previous score by printing all black
				if(totalScore<100)
					myDrawTextWithFont(910,10,25,num,mustard,black);
				else
					myDrawTextWithFont(910,10,25,"100+",mustard,black);
		}

		if(personInCar==true)		//If our taxi currently holds a passenger
		{
			drawDestination(destX,destY);		//Then first of all draw a destination for that passenger
			if(checkOvertake(car1x,car1y,x,y)==true || checkOvertake(car2x,car2y,x,y)==true)		//Check if our car has overtaken a car
			{
				myDrawTextWithFont(800,100,30,"Overtake!",black,buttoncolor);		//Display overtake message
				timerStart=true;		//Sets timer started variable to true
				hitStart = clock();		//start timer for display message
				totalScore++;			//Adds score if we overtake a car

				num1(totalScore,num);	//function to get current score as string to be printed
				myDrawTextWithFont(910,10,25,"100",black,black);	//Removes previous score by printing all black
				if(totalScore<100)
					myDrawTextWithFont(910,10,25,num,mustard,black);
				else
					myDrawTextWithFont(910,10,25,"100+",mustard,black);
			}
		}

		if(time<0 || totalScore>=100)		//Condition to end the game...Either the time runs out or 100 score has been completed
		{
			if(totalScore>=100)		//Checks if score is greater or equal than 100
				won=true;			//If score is greater or equal to 100 then game has been won
			complete==true;		//In order to terminate the game
			break;
		}

		if(dropped==2)		//If two passengers has been dropped
		{
					pairdropped++;		//Pairs dropped will be added in order to count how many extra cars has been added
					totalcars++;		//Total cars are also incremented
					getRandomDest(newX,newY,obstaclesArr);		//New coordinates are taken
					drawcar(newX,newY);							//To draw a new car on board

					car1speed=car1speed+2;			//Increase the speed of all the cars on board
					carArr[pairdropped][0]=newX;	//Save the coordinates of the added car in an array for later use
					carArr[pairdropped][1]=newY;
					dropped=0;	//Make dropped people counter to 0 to to check if two passengers has been dropped after it
		}

		move=getch();		//Gets the character input from the keyboard for our taxi movement

		if(move=='a')		//to move taxi left
		{
			if(x-speed>10 && avoidHit(x-speed,y,obstaclesArr,x,y,0,peopleArr))	//If our taxi is not hitting any obstacle or left boundary then move left
			{
				myRect(x-20,y-5,x+20,y+15,grey2,grey2);
				x=x-speed;
				drawtaxi(x,y,taxicolor);
			}
		}
		else if(move=='d')		//to move taxi right
		{
			if(x+speed<760 && avoidHit(x+speed,y,obstaclesArr,x,y,0,peopleArr))	//If our taxi is not hitting any obstacle or right boundary then move right
			{
				myRect(x-20,y-5,x+20,y+15,grey2,grey2);
				x=x+speed;
				drawtaxi(x,y,taxicolor);
			}
		}
		else if(move=='w')		//to move taxi up
		{
			if(y-speed>10 && avoidHit(x,y-speed,obstaclesArr,x,y,0,peopleArr))	//If our taxi is not hitting any obstacle or upper boundary then move up
			{
				myRect(x-20,y-5,x+20,y+15,grey2,grey2);
				y=y-speed;
				drawtaxi(x,y,taxicolor);
			}
		}
		else if(move=='s')		//to move taxi down
		{
			if(y+speed<450 && avoidHit(x,y+speed,obstaclesArr,x,y,0,peopleArr))	//If our taxi is not hitting any obstacle or down boundary then move down
			{
				myRect(x-20,y-5,x+20,y+15,grey2,grey2);
				y=y+speed;
				drawtaxi(x,y,taxicolor);
			}
		}
		else if(move==32)		//if spacebar is clicked then check status of passengers
		{
			if(personInCar==false)		//If our taxi does not hold any passenger
			{
				picked=nearperson(peopleArr,x,y,pickX,pickY);		//tells if taxi has arrived near a passenger
				if(picked==true)		//If a passenger has been picked 
				{
					getRandomDest(destX,destY,obstaclesArr);	//Get coordinates for destination
					drawDestination(destX,destY);				//Draw random destination

					personInCar=true;
					myDrawTextWithFont(800,50,30,"Person Picked!",black,grey2);		//Display message that person has been picked
					Sleep(1000);
					myDrawTextWithFont(800,50,30,"Person Picked!",black,black);

				}
			}
			else		//If our taxi holds a passenger
			{
				checkArrival(destX,destY,x,y,personInCar,peopleArr,picked,totalScore,dropped,obstaclesArr);		//Check if taxi has arrived to the destination
				
				num1(totalScore,num);		//function to get current score as string to be printed
				myDrawTextWithFont(910,10,25,"100",black,black);	//Removes previous score by printing all black
				if(totalScore<100)
					myDrawTextWithFont(910,10,25,num,mustard,black);
				else
					myDrawTextWithFont(910,10,25,"100+",mustard,black);
			}
		}
	}
	if(won==true)		//If game has been won 
	{
		system("CLS");		//Clear the screen
		myDrawTextWithFont(190,100,100,"You Won!",grey,black);		//Display the Winning message
		Sleep(2000);	//Put delay of 2 seconds to show message
	}
	else	//If game is not won but finished
	{
		system("CLS");		//Clear the screen	
		myDrawTextWithFont(190,100,100,"Time Over!",grey,black);	//Display the time over message
		Sleep(2000);	//Put delay of 2 seconds to show message
	}
	return totalScore;		//Return total score of player in order to check for new highscore
}