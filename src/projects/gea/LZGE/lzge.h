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

#ifndef _LZGE_
#define _LZGE_

   #include "..\Huffman\huffman.h"
//   #include "..\GEA\gea.h"
   #include "match.h"

   #ifdef __cplusplus
      extern "C" {
   #endif // __cplusplus

//--------------------------------------------------------------------------
// ������ ��������� �������������� �� ��������, ����� ������� ���� 
// ����� ������
#define  HUF_BLOCK      10000      // ������ ����� �������� �� ���������.
// ������� �������� ������ ��������
#define  LZGE_ALPHABET  256
// ����������� ����� ����������
#define  MATCH_LEN      2
// ����������� ��������
#define  MIN_OFFSET     2
#define  ALL_LEN        19     // ����� ��������� �� �����
#define  SLOT_LEN       18     // ��������� ��� ������

typedef struct
{
   // ������������ �����
   dword  hufblock;    // ������ ����� ��� ���������� ������ �������
   // ������������ ��� ������
   dword  level;       // �������� ������ �� 1 �� 10
   // ����������� ���������
   dword  numoff;      // ���������� ��������� �������� �� rng
   dword  maxbit;      // ���������� bit �� ������ ����
   dword  solidoff;    // �������� solid ������
   dword  mft[3];      // ��������� ���� ��������
   dword  userfunc;    // ���������������� �������
   dword  pgeaparam;  // ��������� �� geaparam 
} slzge, * pslzge;

extern dword   rngbits[];
extern dword   rngmax[ 51 ];
extern dword   rngmin[ 51 ];

extern dword   lenmax[ 20 ];
extern dword   lenmin[ 20 ];
extern dword   lenbits[];


//--------------------------------------------------------------------------
// Common LZGE
dword  STACKAPI lzge_bits( dword val );

dword  STDCALL lzge_encode( pbyte in, dword size, pbyte out, pslzge lzge );
dword  STDCALL lzge_decode( pbyte in, pbyte out, dword size, pslzge lzge );
void   STDCALL lzge_ranges( pslzge lzge, dword maxoff );

//--------------------------------------------------------------------------

   #ifdef __cplusplus
      }
   #endif // __cplusplus

#endif // _LZGE_

