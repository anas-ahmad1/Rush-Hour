#define _WIN32_WINNT 0x0500 

#include <windows.h> 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void myLine(int x1, int y1, int x2, int y2,COLORREF lineColor)
{

	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
	HPEN pen =CreatePen(PS_SOLID,2,lineColor); //2 is the width of the pen
    SelectObject(device_context,pen);
	MoveToEx(device_context,x1,y1,NULL);
    LineTo(device_context,x2, y2);
	DeleteObject(pen);

	ReleaseDC(console_handle, device_context);  
}
void myRect(int x1, int y1, int x2, int y2,COLORREF lineColor,COLORREF fillColor)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen =CreatePen(PS_SOLID,2,lineColor); 
    SelectObject(device_context,pen);
	HBRUSH brush = ::CreateSolidBrush(fillColor);
	SelectObject(device_context,brush);
	
	Rectangle(device_context,x1,y1,x2,y2);
	DeleteObject(pen);
	DeleteObject(brush);
	ReleaseDC(console_handle, device_context); 
}
void myEllipse(int x1, int y1, int x2, int y2,COLORREF lineColor,COLORREF fillColor)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen =CreatePen(PS_SOLID,2,lineColor); 
    SelectObject(device_context,pen);
	HBRUSH brush = ::CreateSolidBrush(fillColor);
	SelectObject(device_context,brush);
	Ellipse(device_context,x1,y1,x2,y2);
	DeleteObject(pen);
	DeleteObject(brush);	
	ReleaseDC(console_handle, device_context);

}
void myDrawText(int x,int y,int ht,char str[],COLORREF lineColor,COLORREF fillColor)
{
	WCHAR wstr[20]={};
	for (int i=0;i<20&&str[i];++i)
		wstr[i] = str[i];

	RECT rects;
	rects.left = x;
	rects.top = y;
	rects.right = x+ht;
	rects.bottom = y+ht;//(x,y,x+ht,y+ht);
	
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

	SetTextColor(device_context,lineColor);
	SetBkColor(device_context,fillColor);
	DrawText(device_context,str,-1,&rects,DT_TOP|DT_NOCLIP);
	ReleaseDC(console_handle, device_context);
  
}

void myDrawTextWithFont(int x,int y,int ht,char str[],COLORREF lineColor,COLORREF fillColor)
{
	WCHAR wstr[20]={};
	for (int i=0;i<20&&str[i];++i)
		wstr[i] = str[i];

	RECT rects;
	HFONT hFont;
	rects.left = x;
	rects.top = y;
	rects.right = x+ht;
	rects.bottom = y+ht;//(x,y,x+ht,y+ht);
	
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);
	hFont = CreateFont(ht,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
			            CLIP_DEFAULT_PRECIS,1, VARIABLE_PITCH,TEXT("Impact"));
    SelectObject(device_context, hFont);

	SetTextColor(device_context,lineColor);
	SetBkColor(device_context,fillColor);
	DrawText(device_context,str,-1,&rects,DT_TOP|DT_NOCLIP);
	DeleteObject(hFont);   
	ReleaseDC(console_handle, device_context);
  
}
void mySetPixel(float x,float y,COLORREF colorVal)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);
	
	SetPixel(device_context,x,y,colorVal);
	ReleaseDC(console_handle,device_context);
}

void num1(int score,char num[3])
{
	score=score-1;
	switch(score)
	{
		case -10:
		{		
			num[0]='-';
			num[1]='9';
			num[2]='\0';
			break;
		}
		case -9:
		{		
			num[0]='-';
			num[1]='8';
			num[2]='\0';
			break;
		}
		case -8:
		{		
			num[0]='-';
			num[1]='7';
			num[2]='\0';
			break;
		}
		case -7:
		{		
			num[0]='-';
			num[1]='6';
			num[2]='\0';
			break;
		}
		case -6:
		{		
			num[0]='-';
			num[1]='5';
			num[2]='\0';
			break;
		}
		case -5:
		{		
			num[0]='-';
			num[1]='4';
			num[2]='\0';
			break;
		}
		case -4:
		{		
			num[0]='-';
			num[1]='3';
			num[2]='\0';
			break;
		}
		case -3:
		{		
			num[0]='-';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case -2:
		{		
			num[0]='-';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case -1:
		{		
			num[0]='0';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 0:
		{		
			num[0]='0';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 1:
		{		
			num[0]='0';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 2:
		{		
			num[0]='0';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 3:
		{		
			num[0]='0';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 4:
		{		
			num[0]='0';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 5:
		{		
			num[0]='0';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 6:
		{		
			num[0]='0';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 7:
		{		
			num[0]='0';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 8:
		{		
			num[0]='0';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 9:
		{	
			num[0]='1';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 10:
		{		
			num[0]='1';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 11:
		{		
			num[0]='1';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 12:
		{		
			num[0]='1';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 13:
		{		
			num[0]='1';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 14:
		{		
			num[0]='1';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 15:
		{		
			num[0]='1';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 16:
		{		
			num[0]='1';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 17:
		{		
			num[0]='1';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 18:
		{		
			num[0]='1';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 19:
		{	
			num[0]='2';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 20:
		{		
			num[0]='2';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 21:
		{		
			num[0]='2';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 22:
		{		
			num[0]='2';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 23:
		{		
			num[0]='2';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 24:
		{		
			num[0]='2';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 25:
		{		
			num[0]='2';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 26:
		{		
			num[0]='2';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 27:
		{		
			num[0]='2';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 28:
		{		
			num[0]='2';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 29:
		{	
			num[0]='3';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 30:
		{		
			num[0]='3';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 31:
		{		
			num[0]='3';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 32:
		{		
			num[0]='3';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 33:
		{		
			num[0]='3';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 34:
		{		
			num[0]='3';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 35:
		{		
			num[0]='3';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 36:
		{		
			num[0]='3';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 37:
		{		
			num[0]='3';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 38:
		{		
			num[0]='3';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 39:
		{	
			num[0]='4';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 40:
		{		
			num[0]='4';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 41:
		{		
			num[0]='4';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 42:
		{		
			num[0]='4';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 43:
		{		
			num[0]='4';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 44:
		{		
			num[0]='4';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 45:
		{		
			num[0]='4';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 46:
		{		
			num[0]='4';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 47:
		{		
			num[0]='4';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 48:
		{		
			num[0]='4';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 49:
		{	
			num[0]='5';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 50:
		{		
			num[0]='5';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 51:
		{		
			num[0]='5';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 52:
		{		
			num[0]='5';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 53:
		{		
			num[0]='5';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 54:
		{		
			num[0]='5';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 55:
		{		
			num[0]='5';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 56:
		{		
			num[0]='5';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 57:
		{		
			num[0]='5';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 58:
		{		
			num[0]='5';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 59:
		{	
			num[0]='6';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 60:
		{		
			num[0]='6';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 61:
		{		
			num[0]='6';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 62:
		{		
			num[0]='6';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 63:
		{		
			num[0]='6';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 64:
		{		
			num[0]='6';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 65:
		{		
			num[0]='6';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 66:
		{		
			num[0]='6';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 67:
		{		
			num[0]='6';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 68:
		{		
			num[0]='6';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 69:
		{	
			num[0]='7';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 70:
		{		
			num[0]='7';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 71:
		{		
			num[0]='7';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 72:
		{		
			num[0]='7';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 73:
		{		
			num[0]='7';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 74:
		{		
			num[0]='7';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 75:
		{		
			num[0]='7';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 76:
		{		
			num[0]='7';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 77:
		{		
			num[0]='7';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 78:
		{		
			num[0]='7';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 79:
		{	
			num[0]='8';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 80:
		{		
			num[0]='8';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 81:
		{		
			num[0]='8';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 82:
		{		
			num[0]='8';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 83:
		{		
			num[0]='8';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 84:
		{		
			num[0]='8';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 85:
		{		
			num[0]='8';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 86:
		{		
			num[0]='8';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 87:
		{		
			num[0]='8';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 88:
		{		
			num[0]='8';
			num[1]='9';
			num[2]='\0';
			break;
		}
	case 89:
		{	
			num[0]='9';
			num[1]='0';
			num[2]='\0';
			break;
		}
	case 90:
		{		
			num[0]='9';
			num[1]='1';
			num[2]='\0';
			break;
		}
	case 91:
		{		
			num[0]='9';
			num[1]='2';
			num[2]='\0';
			break;
		}
	case 92:
		{		
			num[0]='9';
			num[1]='3';
			num[2]='\0';
			break;
		}
	case 93:
		{		
			num[0]='9';
			num[1]='4';
			num[2]='\0';
			break;
		}
	case 94:
		{		
			num[0]='9';
			num[1]='5';
			num[2]='\0';
			break;
		}
	case 95:
		{		
			num[0]='9';
			num[1]='6';
			num[2]='\0';
			break;
		}
	case 96:
		{		
			num[0]='9';
			num[1]='7';
			num[2]='\0';
			break;
		}
	case 97:
		{		
			num[0]='9';
			num[1]='8';
			num[2]='\0';
			break;
		}
	case 98:
		{		
			num[0]='9';
			num[1]='9';
			num[2]='\0';
			break;
		}
	}
}

