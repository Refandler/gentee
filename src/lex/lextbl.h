/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: lextbl 18.10.06 0.0.A.
*
* Author: Alexey Krivonogov ( gentee )
*
* Summary: ������������� ������� ��������� �� ������� ����� ������
*
******************************************************************************/

#ifndef _LEXTBL_
#define _LEXTBL_

   #ifdef __cplusplus               
      extern "C" {                 
   #endif // __cplusplus      

#include "lex.h"

/*
   �������� ������� ����� ������
   0 uint - ���������� ���������
   ������ ������ ���������� � ���������� ��������.
   0 uint ���������� �������� ������ default. 

   1 uint default value
   
   �� ��������� 0 �������� ��������� ��������� LEX_STOP

   �������� ��������� ����������� ��������� �������. ��� ������� �� ��� uint 
   1 uint - ��������� �������� ��� ��������� �������
         1 byte - ����� ���������� 
         2 byte - ����� ���������
         3 byte - the first additional character
         4 byte - the second additional character
   2 uint - �������� ������� ���������

   ���������������� ���������
   0x3000 - ����� � 0x4100
   0x4100 - '_', 'A'-'Z', 'a'-'z' � ������ ��� ����� 128
   0x5800 - ����� � 'A'-'F' � 'a'-'f'

   0 byte - ���������� ������ �������� ����
   0 byte - ����� 
            0x0001 ignore case.
   ������ ���� ������� �� 
     1 uint - ��������� �������� ������� ��������� �����
     ������ � ��������� �������
     ������������� ������� �����
*/

//--------------------------------------------------------------------------
// output - �������������� ������� ���������
uint  STDCALL lex_tbl( plex pl, puint input );

//--------------------------------------------------------------------------

   #ifdef __cplusplus              
      }                            
   #endif // __cplusplus

#endif // _LEXTBL_

