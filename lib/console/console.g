/******************************************************************************
*
* Copyright (C) 2004-2008, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: compiler 07.03.08 0.0.A.
*
* Author: Sergey Kurganov ( Pretorian )
*
******************************************************************************/
// ��������:
// title [R](str) - ��������� �������
// x [RW](uint) - x ���������� �������		
// y [RW](uint) - y ���������� �������
// length [RW](uint) - ������ ������� (������)
// height [RW](uint) - ������ ������� (������)
// color [RW](uint) - ������� ���� ��������
// background [RW](uint) - ������� ��� ��������
// cursoreShow [RW](uint) - ��������� ������� 0/1
// cursoreSize [RW](uint) - ������ ������� 0%-100%
// ctrlC [R](uint) - ������������� ������ ��������� �� Ctrl+C 0/1
// ������:
// Print(str|ubute|byte|ushort|short|uint|int|ulong|long|float|double) - ����� �� �������
// uint Char() - ��� ������� � ������� �����������
// �har(uint) - ����� ������� �� ��� ���� �� �������
// �har(uint,uint) - ����� ������� �� ��� ���� � ��������� ���������� �� �������
// Cls() - �������� �����
// Cls(uint,uint,uint,uint) - �������� �������� ���� � �������
// Inversion() - �������� ���� � �����
// Copy(uint,uint,uint,uint,uint,uint) - ����������� ������� ������� � ����� ����������
// ScrollUp() - ������������ ��� ������� �����
// ScrollDown() - ������������ ��� ������� ����
// ScrollLeft() - ������������ ��� ������� �����
// ScrollRight() - ������������ ��� ������� ������

import "kernel32.dll"
{
	AllocConsole()
	uint GetStdHandle(int)
	FreeConsole()
	SetConsoleTitleA(uint)
	uint GetConsoleScreenBufferInfo(uint,uint)
	SetConsoleCursorPosition(uint,uint)
	SetConsoleScreenBufferSize(uint,uint)
	SetConsoleWindowInfo(uint,uint,uint)
	SetConsoleTextAttribute(uint,uint)
	GetConsoleCursorInfo(uint,uint)
	SetConsoleCursorInfo(uint,uint)
	FillConsoleOutputCharacterA(uint,uint,uint,uint,uint)
	FillConsoleOutputAttribute(uint,uint,uint,uint,uint)
	SetConsoleCtrlHandler(uint,uint)
	WriteConsoleA(uint,uint,uint,uint,uint)
	ReadConsoleOutputCharacterA(uint,uint,uint,uint,uint)
	ReadConsoleOutputA(uint,uint,uint,uint,uint)
	WriteConsoleOutputA(uint,uint,uint,uint,uint)
}

//��������� ��� ������ � ����� � �������
type conrect
	{
	short left
	short top
	short right
	short bottom
	}

//�������	
type console <protected>
{
	short	column		//�������� � �������� ������ �������
	short	rows			//����� � �������� ������ �������
	short	xc				//���������� x �������
	short	yc				//���������� y �������
	uint	colorc		//�������� �������
	short left			//����� ������� ���� ���� ������ ������� �� ������ �������
	short	top
	short	right			//������ ������ ���� ���� ������ ������� �� ������ �������
	short	bottom
	short	maxcolumn	//������������ ������ ������ ������� � ������ ������ � ������� �������
	short	maxrows		//������������ ������ ������ ������� � ������ ������ � ������� �������

	uint	cursize		// ������ �������
	uint	curvisible	// ��������� �������
	
	uint	hstdin	// ���������� ������ � �������
	uint	hstdout	// ���������� ������ � �������
	uint	hstderr	// ���������� ������ ������ �� �������
}

//���������� �������� �������
property console.title(str string)
{
	SetConsoleTitleA(string.ptr())
}

//�������� ���������� ������� x
property uint console.x
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	return uint(.xc)
}

//�������� ���������� ������� y
property uint console.y
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	return uint(.yc)
}

//���������� ���������� ������� � x
property console.x(uint x)
{
	SetConsoleCursorPosition(.hstdout,(uint(.y)<<16)+x)
}

//���������� ���������� ������� � y
property console.y(uint y)
{
	SetConsoleCursorPosition(.hstdout,(uint(y)<<16)+.x)
}

//�������� ����� �������
property uint console.length
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	return uint(.column)
}

//�������� ������ �������
property uint console.height
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	return uint(.rows)
}

//���������� ����� �������
property console.length(uint length)
{
	if length>.length
	{
		SetConsoleScreenBufferSize(.hstdout,uint(.rows<<16)+length)
		.left=0; .top=0; .right=length-1; .bottom=.rows-1
		SetConsoleWindowInfo(.hstdout,1,&this.left)
	}
	else
	{
		.left=0; .top=0; .right=length-1; .bottom=.rows-1
		SetConsoleWindowInfo(.hstdout,1,&this.left)
		SetConsoleScreenBufferSize(.hstdout,uint(.rows<<16)+length)
	}
}

//���������� ������ �������
property console.height(uint height)
{
	if height>.height
	{
		SetConsoleScreenBufferSize(.hstdout,uint(height<<16)+.column)
		.left=0; .top=0; .right=.column-1; .bottom=height-1
		SetConsoleWindowInfo(.hstdout,1,&this.left)
	}
	else
	{
		.left=0; .top=0; .right=.column-1; .bottom=height-1
		SetConsoleWindowInfo(.hstdout,1,&this.left)
		SetConsoleScreenBufferSize(.hstdout,uint(height<<16)+.column)
	}
}

//���������� ���� ��������� ��������
property console.color(uint color)
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	SetConsoleTextAttribute(.hstdout,(.colorc&0xF0)+(color&0xF))
}
	
//�������� ���� ��������� ��������
property uint console.color
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	return uint(.colorc&0xF)
}

//���������� ��� ��������� ��������
property console.background(uint background)
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	SetConsoleTextAttribute(.hstdout,(.colorc&0xF)+(background<<4&0xF0))
}
	
//�������� ��� ��������� ��������
property uint console.background
{
	GetConsoleScreenBufferInfo(.hstdout,&this)
	return uint(.colorc>>4&0xF)
}

//���������� ��������� ������� 0/1
property uint console.cursoreShow
{
	GetConsoleCursorInfo(.hstdout,&.cursize)
	return .curvisible 
}	

//���������� ������ ������� 0-100
property uint console.cursoreSize
{
	GetConsoleCursorInfo(.hstdout,&.cursize)
	return .cursize 
}	

//���������� ��������� ������� 0/1
property console.cursoreShow(uint visible)
{
	GetConsoleCursorInfo(.hstdout,&.cursize)
	.curvisible=visible
	SetConsoleCursorInfo(.hstdout,&.cursize) 
}	
	
//���������� ������ ������� 0-100
property console.cursoreSize(uint size)
{
	GetConsoleCursorInfo(.hstdout,&.cursize)
	.cursize=size
	SetConsoleCursorInfo(.hstdout,&.cursize) 
}	

//�������� �������
method console.Cls()
{
   FillConsoleOutputCharacterA(.hstdout,32,.length*.height,0,0)
   FillConsoleOutputAttribute(.hstdout,(.background<<4)+.color,.length*.height, 0, 0)
   .x=0;.y=0
}

//������ str
method console.Print(str string) { print(string) }	

//������ uint
method console.Print(uint string) { print(str(string)) }	

//������ int
method console.Print(int string) { print(str(string)) }	

//������ ubyte
method console.Print(ubyte string) { print(str(string)) }	

//������ byte
method console.Print(byte string) { print(str(string)) }	

//������ ushort
method console.Print(ushort string) { print(str(string)) }	

//������ short
method console.Print(short string) { print(str(string)) }	

//������ float
method console.Print(float string) { print(str(string)) }	

//������ ulong
method console.Print(ulong string) { print(str(string)) }	

//������ long
method console.Print(long string) { print(str(string)) }	

//������ double
method console.Print(double string) { print(str(string)) }	

//�������� ������
method console.Inversion()
{
	uint i
	i=.color
	.color=.background
	.background=i
}

//������������� ������ ��������� �� Ctrl+C 0/1
property console.ctrlC(uint num)
{
	if num : SetConsoleCtrlHandler(0,0)
	else : SetConsoleCtrlHandler(0,1)
}  
	
//������������� �������
method console.init()
{
	AllocConsole()
	.hstdin=GetStdHandle(-10)
	.hstdout=GetStdHandle(-11)
	.hstderr=GetStdHandle(-12)
	.length=80
	.height=25
	.Cls()
}

//�������� �������
method console.delete() { FreeConsole() }

//����� ������� �� ��� ���� �� �������
method console.char(uint sym)
{
	str string=" "
	string[0]=byte(sym)
	WriteConsoleA(.hstdout,string.ptr(),*string,0,0)
}

//����� ������� �� ��� ���� � ��������� ���������� �� �������
method console.Char(uint sym, uint num)
{
	uint i
	byte sy=byte(sym)
	str string
	fornum i=0,num
	{
		string+=" "
		string[i]=sy
	}
	WriteConsoleA(.hstdout,string.ptr(),*string,0,0)
}

//���������� ��� ������� � �������� ����������� (������ ���� 128 �� �������������)
method uint console.char()
{
	uint i;str i2=" "
	GetConsoleScreenBufferInfo(.hstdout,&this)
   ReadConsoleOutputCharacterA(.hstdout,i2.ptr(),1,.xc,&i)
   return uint(i2[0])
}

//�������� �������� ���� � ������� (x,y,length,height)
method console.Cls(uint x y l h)
{
	uint i
	fornum i=0,h
   {
		FillConsoleOutputCharacterA(.hstdout,32,l,y+i<<16|x,0)
   	FillConsoleOutputAttribute(.hstdout,(.background<<4)+.color,l,y+i<<16|x,0)
	}
		.x=x; .y=y
}

//����������� ������� ������� xyhl � ����� ���������� 
method console.Copy(uint x y l h x1 y1)
{
	conrect rect
	rect.left=x
	rect.top=y
	rect.right=x+l
	rect.bottom=y+h
	buf buff[l*h*4]
	ReadConsoleOutputA(.hstdout,buff.ptr(),(h<<16)|l,0,&rect)
	rect.left=x1
	rect.top=y1
	rect.right=x1+l
	rect.bottom=y1+h
	WriteConsoleOutputA(.hstdout,buff.ptr(),(h<<16)|l,0,&rect)
}

//������������ ��� ������� �����
method console.ScrollUp()
{
	uint i
	.Copy(0,1,.length,.rows-1,0,0)
	FillConsoleOutputCharacterA(.hstdout,32,.column,(.rows-1)<<16,&i)
	FillConsoleOutputAttribute(.hstdout,(.background<<4)+.color,.column,(.rows-1)<<16,0)
}

//������������ ��� ������� ����
method console.ScrollDown()
{
	uint i
	.Copy(0,0,.length,.rows-1,0,1)
	FillConsoleOutputCharacterA(.hstdout,32,.column,0,&i)
	FillConsoleOutputAttribute(.hstdout,(.background<<4)+.color,.column,0,0)
}

//������������ ��� ������� �����
method console.ScrollLeft()
{
	uint i,j
	.Copy(1,0,.length,.rows,0,0)
	fornum j=0,.height
	{
		FillConsoleOutputCharacterA(.hstdout,32,1,(j<<16)+(.column-1),&i)
		FillConsoleOutputAttribute(.hstdout,(.background<<4)+.color,1,(j<<16)+(.column-1),0)
	}
}

//������������ ��� ������� ������
method console.ScrollRight()
	{
	uint i,j
	.Copy(0,0,.length-1,.rows,1,0)
	fornum j=0,.height
	{
		FillConsoleOutputCharacterA(.hstdout,32,1,j<<16,&i)
		FillConsoleOutputAttribute(.hstdout,(.background<<4)+.color,1,j<<16,0)
	}
		fornum j=0,.height
		{
			FillConsoleOutputCharacterA(.hstdout,32,1,(j<<16),&i)
		}
	}

/*
func main< main >
{
	console con
	datetime time_start, time_end, work_time
	time_start.gettime() //����� ������

	con.Inversion()
	con.Char(0xB0,1999)
	con.Cls(1,1,8,4)
	con.Print("dfdfdf")
	con.Copy(1,1,3,3,20,10)
	//con.Inversion()
	con.ScrollRight()
	time_end.gettime() //����� �����
	work_time = time_end - time_start
	print("����� ������ : \(gettimeformat(work_time , "HH:mm:ss", "")).\( work_time.msec) \n")
	getch()
}
*/
