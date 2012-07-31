/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project <http://www.gentee.com>. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* search 20.04.2007 0.0.A.
*
* Author:  
*
******************************************************************************/

#ifndef _SEARCH_
#define _SEARCH_

#include "../common/types.h"

   #ifdef __cplusplus               
      extern "C" {                 
   #endif // __cplusplus      

//--------------------------------------------------------------------------

#define QS_IGNCASE    0x0001   // ������������ �������
#define QS_WORD       0x0002   // ������ �����
#define QS_BEGINWORD  0x0004   // ������ ������ �����

typedef struct search_tag
{
   pubyte   pattern;                  // ��������� �� ������� ������     
   uint     size;                     // ������ �������
   uint     shift[ ABC_COUNT ];        // ������ ��������
   uint     flag;                     // �����
} ssearch, * pssearch;

void  STDCALL qs_init( pssearch psearch, pubyte pattern, uint m, uint flag );
uint  STDCALL qs_search( pssearch psearch, pubyte y, uint n );

//--------------------------------------------------------------------------

   #ifdef __cplusplus              
      }                            
   #endif // __cplusplus

#endif // _SEARCH_
