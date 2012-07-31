/******************************************************************************
*
* Copyright (C) 2009, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* Author: Alexey Krivonogov ( gentee )
*
******************************************************************************/

#ifndef _MATCH_
#define _MATCH_

   #include "../gea.h"

   #ifdef __cplusplus
      extern "C" {
   #endif // __cplusplus

//--------------------------------------------------------------------------

typedef struct
{
   pdword  hash2;     // �������� ��������� ���������� ����� 2

   pdword  hash[3];   // ���-������� ���������� �����
   pdword  next[3];   // ������� ��������� �� ������� � ����������
   dword   top[3];    // ������� ������� 0 == match->next  
   dword   hsize[3];  // ������ ���-�������
   dword   size[3];   // ������ ����
   dword   limit[3];  // ������� ������ � ���-�������
   dword   count;     // ���������� ���-������
   pbyte   start;     // ������
   pbyte   end;       // ����� 
} smatch, * psmatch;

//--------------------------------------------------------------------------

dword STDCALL   match_new( psmatch match, pbyte start, pbyte end, dword level );
void  STDCALL   match_destroy( psmatch match );
dword STACKAPI match_find( psmatch match, pbyte input, pdword retoff );
dword STACKAPI match_update( psmatch match, pbyte input );

//--------------------------------------------------------------------------

   #ifdef __cplusplus
      }
   #endif // __cplusplus

#endif // _MATCH_

