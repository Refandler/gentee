/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: lex 18.10.06 0.0.A.
*
* Author: Alexey Krivonogov ( gentee )
*
******************************************************************************/

#ifndef _LEX_
#define _LEX_

   #ifdef __cplusplus               
      extern "C" {                 
   #endif // __cplusplus      

#include "../common/hash.h"

// �������������� ������� ������������ �������
typedef struct
{
   uint    type;    // ��� �������
   uint    pos;     // �������� ������ �������
   uint    len;     // ������ �������
   uint    value;   // �������������� ��������
} lexitem, * plexitem;

typedef struct
{
   uint    chars;   // ������������������ ��������.
   uint    value;   // �������������� �������
   ubyte   len;     // ���������� ��������    
} lexmulti, * plexmulti;

typedef struct
{
   ubyte   left;    // Open character ({
   ubyte   right;   // Close caharacter )}
   int     count;   // Counter - stop when -1
   uint    state;   // Return state
} lexexp, * plexexp;

// ��������� � �������� ��������� � ������ ����������� 
// ������������ �����������
typedef struct
{
   buf     tbl;     // ������� ���������. ������ ������ ������ ����� 
                    // 256 ���������
   arr     state;   // ���� ��������� � ������� �������� ������� ���������.
   arr     litems;  // �������� ������ lexitem ��� ��������� � ���� state. 
   arr     mitems;  // ������ multi �����������
                    // ������������� 64 ����� �� ��� ������� �� 8 ��������� � 
                    // ������ �����. ������ ������� lexmulti.
   uint    imulti;  // ������� ��������� ����� � ������� multi
   hash    keywords;  // Keywords
   arr     expr;      // ���� �� lexexp 
   ubyte   alloced;   // ��� lex �������� ������
} lex, *plex;

typedef struct
{
   uint  pos;       // ������ ������� LEX_TRY
//   uint  state;     // ��������� �������� 
   uint  ret;       // ��������� ��� LEX_RET 
} lextry, *plextry;

// �������������� �������
// � 128 ���� ����������������� ������� ��� LEXF_MULTI
#define  LEX_MULTI  0x80000000     // ������ ������ multi ����� 64
#define  LEX_EXPR    0xFA000000     // ��������� � \( )
#define  LEX_STRNAME 0xFB000000     // �������� �� ��� � ������ \[]
#define  LEX_GTNAME  0xFC000000     // �������� �� GT/XML ��� 
#define  LEX_SKIP    0xFD000000     // ���������� ������
#define  LEX_OK      0xFE000000     // ����������� �������
#define  LEX_STOP    0xFF000000     // ������� ��������� �������

// ����� ��� ��������� ������� ���������
#define  LEXF_ITSTATE 0x0001  // ��������� ������� �� ��������� ����������� �������
#define  LEXF_ITCMD   0x0002  // ��������� ������� �� ��������� ����������� �������
#define  LEXF_POS     0x0004  // ���������� �������
#define  LEXF_STAY    0x0008  // ���������� �� �����
#define  LEXF_TRY     0x0010  // ����� ���������� ��������
#define  LEXF_RET     0x0020  // ������� �� ��������� ��������� ��� LEXF_TRY
#define  LEXF_VALUE   0x0040  // value = ��������� �������� �������
#define  LEXF_PUSH    0x0080  // ��������� ������� ���������
#define  LEXF_POP     0x0100  // ������������ � ��������� ����������� ���������
#define  LEXF_PUSHLI  0x0200  // ������� ������ lexitem � ����.
#define  LEXF_POPLI   0x0400  // ������ ������ lexitem �� �����.
#define  LEXF_MULTI   0x0800  // �������� �� ���������� �������� (�� 4).
#define  LEXF_KEYWORD 0x1000  // ����� ���� �������� ������
#define  LEXF_NEW     0x2000  // ������� ����� ������� 
#define  LEXF_PAIR    0x4000  // ��������� ������ ������

/*
   �������� ������� ���������

   ������� ��������� ������� �� ����� �� 256 ��������� uint.
   
   ������� ������� ��������� (uint � 0-255)
   1 - 2 bytes
     Flags
   3 byte       ���� ���� LEXF_MULTI �� ��������� ���������� - 1
     New state
   4 byte       ���� ���� LEXF_MULTI �� ����� ������ � mitems 
     Command    ���� ���� LEXF_TRY �� ����� ��������� � ������ LEX_RET
*/

#ifndef RUNTIME

//--------------------------------------------------------------------------
// output - �������������� ������ ��������� lexitem
uint  STDCALL gentee_lexptr( pubyte input, plex pl, parr output );
uint  STDCALL gentee_lex( pbuf input, plex pl, parr output );
plex  STDCALL lex_init( plex pl, puint ptbl );
void  STDCALL lex_delete( plex pl );

//--------------------------------------------------------------------------

#endif

   #ifdef __cplusplus              
      }                            
   #endif // __cplusplus

#endif // _COMPILE_

