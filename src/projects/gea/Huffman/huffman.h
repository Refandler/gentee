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

#ifndef _HUFFMAN_
#define _HUFFMAN_

   #include "../gea.h"

   #ifdef __cplusplus
      extern "C" {
   #endif // __cplusplus

//--------------------------------------------------------------------------

struct hufleaf_tag;
typedef struct hufleaf_tag * pshufleaf;

// ���� ������ ��� ������� ��������
typedef struct hufleaf_tag
{
//   word       code;      // �������� ������ 
   dword      freq;      // ������� ���������
   pshufleaf  up;        // ��������� �� ������� �������
   pshufleaf  left;      // ��������� �� ����� �������
   pshufleaf  right;     // ��������� �� ������ �������
} shufleaf;

// ������ 
typedef struct
{
   dword      numcode;   // ������ ��������
   dword      allcode;   // ����� ���������� �����
   pshufleaf  root;      // ������� ������� ������
   pshufleaf  tree;      // ������ ��������

   pbyte      stack;     // ���� ������
   dword      min;       // ����������� ������� ���������
   dword      max;       // ������������ ������� ���������
//   dword      pretree;   // 1 ���� pretree ������� 
   pbyte      ptr;       // ��������� ������
   dword      bit;       // ����� ����
   dword      fixed;     // ����������� ������ �������������� ������
                         // ����� ������ ��� ���� ������ ����
   pbyte      prevlen;   // ���������� �����

   pdword     normalize; // ��� huf_normalize
   pdword     freq;      // ��� huf_detree
} shuf, * pshuf;

#define  PRET_MAXCODE    15  // ����������� ���������� �������
#define  PRET_ALPHABET   20  // ������� ������ ��������
//#define  PRET_MAXZERO    47  // ������������ ������ 0
#define  PRET_MAXZERO    87  // ������������ ������ 0

#define  PRET_OFF1       4
#define  PRET_OFF2       8
#define  PRET_OFF3       24

#define  PRET_ZERO2      16  // ������ ���� 2 bit ��� 0 4 - 7
//#define  PRET_ZERO3      16  // ������ ���� 3 bit ��� 0 4 - 11
//#define  PRET_ZERO3      17  // ������ ���� 3 bit ��� 0 8 - 15
#define  PRET_ZERO4      17  // ������ ���� 4 bit ��� 0 8 - 23
//#define  PRET_ZERO5      18  // ������ ���� 5 bit ��� 0 16 - 47
#define  PRET_ZERO6      18  // ������ ���� 6 bit ��� 0 24 - 87
#define  PRET_BIG        19  // ������ ���� bits ��� ����� > PRET_MAXCODE


//--------------------------------------------------------------------------
/*  ������ ������ ������ ��������
[1]   3 b - ������� ��� �������� �� �������� min, max - min + 1
            0 - �� ������ ������
      [1] b - ����������� ������� ������
      [1] b - �������� ������

  fixed
      numcode * [1] - ������� ��� ���� ��������

  not fixed
      

  20 * [1] b - ����� pre-tree

  2 b -  ����� �������� ����. ����������� � ��������� �����.
          0 1 2 3

*/
//--------------------------------------------------------------------------
// Common fucntions
pshuf STDCALL huf_new( pshuf huf, dword alphabet );
void  STDCALL huf_destroy( pshuf huf );
void  STDCALL huf_normilize( pshuf huf );

// Compression functions
void  STDCALL    huf_build( pshuf huf );
void  STACKAPI  huf_outbits( pshuf huf, dword item );
dword STACKAPI  huf_bits( pshuf huf, dword item );
void  STACKAPI  huf_incfreq( pshuf huf, dword item );
void  STACKAPI  huf_packnum( pshuf huf, dword val, dword bits );

// Decompression functions
void  STDCALL    huf_detree( pshuf huf );
dword STACKAPI  huf_inbits( pshuf huf );
dword  STACKAPI huf_unpacknum( pshuf huf, dword bits );


//--------------------------------------------------------------------------

   #ifdef __cplusplus
      }
   #endif // __cplusplus

#endif // _HUFFMAN_