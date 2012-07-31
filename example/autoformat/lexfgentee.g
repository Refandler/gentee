/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project <http://www.gentee.com>. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* lexfgentee 19.11.2007
*
* Author: Generated with 'lextbl' program 
*
* Description: This file contains a lexical table for the lexical analizer.
*
******************************************************************************/


define
{
   // States
FG_BINARY = 0x240000 //  Binary data 
FG_TEXTSTR = 0x230000 //  Text string 
FG_COMMENT = 0x90000 //  Comment /* ... */ 
FG_UNKNOWN = 0x40000 //  Unknown characters 
FG_LINE = 0x2000000 //  New line 0x0D0A or 0x0A 
FG_NUMBER = 0x3000000 //  Number decimal, hexadecimal, float or double 
FG_IGNLINE = 0x30000 //  Ignore line character \ 
FG_SYSCHAR = 0x4000000 //  Punctuation marks 
FG_STRING = 0x1F0000 //  String 
FG_FILENAME = 0x200000 //  File data \<filename> 
FG_MACRO = 0x5000000 //  Macro identifier $name 
FG_OPERCHAR = 0x1000000 //  Operations 
FG_NAME = 0xB0000 //  Name identifier 
FG_SPACE = 0x50000 //  Space characters 
FG_MACROSTR = 0x1E0000 //  Macro string $"String" 
FG_LINECOMMENT = 0xA0000 //  Comment //...  
FG_TAB = 0x60000 //  Tab characters 

   // Keywords
KEY_AS = 0x1 
KEY_BREAK = 0x2 
KEY_CASE = 0x3 
KEY_CDECL = 0x4 
KEY_CONTINUE = 0x5 
KEY_DEFAULT = 0x6 
KEY_DEFINE = 0x7 
KEY_DO = 0x8 
KEY_ELIF = 0x9 
KEY_ELSE = 0xA 
KEY_EXTERN = 0xB 
KEY_FOR = 0xC 
KEY_FOREACH = 0xD 
KEY_FORNUM = 0xE 
KEY_FUNC = 0xF 
KEY_GLOBAL = 0x10 
KEY_GOTO = 0x11 
KEY_IF = 0x12 
KEY_IFDEF = 0x13 
KEY_IMPORT = 0x14 
KEY_INCLUDE = 0x15 
KEY_LABEL = 0x16 
KEY_METHOD = 0x17 
KEY_OF = 0x18 
KEY_OPERATOR = 0x19 
KEY_PRIVATE = 0x1A 
KEY_PROPERTY = 0x1B 
KEY_PUBLIC = 0x1C 
KEY_RETURN = 0x1D 
KEY_SIZEOF = 0x1E 
KEY_STDCALL = 0x1F 
KEY_SWITCH = 0x20 
KEY_SUBFUNC = 0x21 
KEY_TYPE = 0x22 
KEY_WHILE = 0x23 
KEY_WITH = 0x24 
KEY_TEXT = 0xFF 
KEY_ARR = 0x100 
KEY_BUF = 0x101 
KEY_BYTE = 0x102 
KEY_DOUBLE = 0x103 
KEY_FLOAT = 0x104 
KEY_HASH = 0x105 
KEY_INT = 0x106 
KEY_LONG = 0x107 
KEY_SHORT = 0x108 
KEY_STR = 0x109 
KEY_UBYTE = 0x10A 
KEY_UINT = 0x10B 
KEY_ULONG = 0x10C 
KEY_USHORT = 0x10D 

}

global
{ 
   buf lexfgentee = '\h4  25 1A 40005 2020 50005 403F2E2E 1000046 7E7E
 1000046 909 60005 A0A 2000006 D0D 70004 2F2F
 80004 2A3D2121 150004 5E5E 150004 2B2B 160004 2D2D
 170004 3C3C 180004 3E3E 190004 5C5C 30005 2525
 1D000C 2626 1A0004 7C7C 1B0004 4100 B1005 2424
 D0004 2222 1F0085 2727 240085 3030 30E0006 3139
 30F0006 29282C2C 4000046 7D7B3B3B 4000046 5D5B3A3A 4000046 0
 23000D 2 10008 D0D FE000000 A0A FE010000 2
 FE000000 20FF 10008 A0D0909 10008 1 10008 2020
 FE000000 1 10008 909 FE000000 1 40009 A0A
 2010002 3 101004A 2A2A 90001 2F2F A0001 3D3D
 1010042 1 FE000000 2F2A FE010800 1 FE000000 A0D0D
 10008 1 10008 3000 FE000000 2 10008 3000
 FE000000 2424 FE010000 2 40009 4100 50C0002 2222
 1E0001 8 10008 3039 FE0F0000 587878 FE100000 426262
 FE110000 4C6C6C FE010000 446464 FE010000 466666 FE010000 456565
 FE130000 2E2E FE120000 6 10008 3039 FE000000 4C6C6C
 FE010000 446464 FE010000 466666 FE010000 456565 FE130000 2E2E
 FE120000 2 10008 5800 FE000000 4C6C6C FE010000 2
 10008 313030 FE000000 4C6C6C FE010000 4 10008 446464
 FE010000 466666 FE010000 456565 FE130000 3039 FE000000 1
 140008 2D2B2B FE140000 3 10008 3039 FE000000 446464
 FE010000 466666 FE010000 1 101004A 3D3D 1010042 1
 101004A 2B3D3D 1010042 1 101004A 3E2D3D3D 1010042 2
 101004A 3D3D 1010042 3C3C 150000 2 101004A 3D3D
 1010042 3E3E 150000 1 101004A 263D3D 1010042 1
 101004A 7C3D3D 1010042 2 101004A 7B7B 1010042 3D3C3E3E
 150000 1 1C0000 3D2125 1010842 2 FE000000 2222
 FE010000 2222 FE000800 7 FE000000 2222 FE000100 5C5C
 FE000800 225C FE000800 3C5C 200885 2A5C 210880 5B5C
 FB220880 285C FA010800 1 FE000000 3E3E FE002100 1
 FE000000 5C2A FE000900 1 FE000000 5B5B FB000100 7
 FE000000 215C FE010800 3C5C 200885 2A5C 210880 5B5C
 FB220880 285C FA010800 7B5C FA010800 405C FA010800 5
 FE000000 2727 FE000100 225C 250880 3C5C 200885 2A5C
 210880 285C FA010800 1 FE000000 2222 FE000100 10003
 73610000 65726200 63006B61 657361 63656463 6F63006C 6E69746E 64006575
 75616665 6400746C 6E696665 6F640065 696C6500 6C650066 65006573 72657478
 6F66006E 6F660072 63616572 6F660068 6D756E72 6E756600 6C670063 6C61626F
 746F6700 6669006F 64666900 69006665 726F706D 6E690074 64756C63 616C0065
 6C6562 6874656D 6F00646F 706F0066 74617265 7000726F 61766972 70006574
 65706F72 797472 6C627570 72006369 72757465 6973006E 666F657A 64747300
 6C6C6163 69777300 686374 66627573 636E75 65707974 69687700 7700656C
 687469 FF00 78657400 74 61000001 62007272 62006675 657479
 62756F64 6600656C 74616F6C 73616800 6E690068 6F6C0074 7300676E 74726F68
 72747300 79627500 75006574 746E69 6E6F6C75 73750067 74726F68 0
'
}