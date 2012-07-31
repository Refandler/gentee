/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project <http://www.gentee.com>. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* lexfgentee 13.10.2006
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
FG_TEXTSTR = 0x220000 //  Text string 
FG_COMMENT = 0x90000 //  Comment /* ... */ 
FG_UNKNOWN = 0x40000 //  Unknown characters 
FG_LINE = 0x2000000 //  New line 0x0D0A or 0x0A 
FG_NUMBER = 0x3000000 //  Number decimal, hexadecimal, float or double 
FG_IGNLINE = 0x30000 //  Ignore line character \ 
FG_SYSCHAR = 0x4000000 //  Punctuation marks 
FG_STRING = 0x1E0000 //  String 
FG_MACRO = 0x5000000 //  Macro identifier $name 
FG_OPERCHAR = 0x1000000 //  Operations 
FG_NAME = 0xB0000 //  Name identifier 
FG_SPACE = 0x50000 //  Space characters 
FG_MACROSTR = 0x1D0000 //  Macro string $"String" 
FG_LINECOMMENT = 0xA0000 //  Comment //...  
FG_TAB = 0x60000 //  Tab characters 

   // Keywords
KEY_AS = 0x1 
KEY_BREAK = 0x2 
KEY_CASE = 0x3 
KEY_CONTINUE = 0x4 
KEY_DEFAULT = 0x5 
KEY_DEFINE = 0x6 
KEY_DO = 0x7 
KEY_ELIF = 0x8 
KEY_ELSE = 0x9 
KEY_EXTERN = 0xA 
KEY_FOR = 0xB 
KEY_FOREACH = 0xC 
KEY_FORNUM = 0xD 
KEY_FUNC = 0xE 
KEY_GLOBAL = 0xF 
KEY_GOTO = 0x10 
KEY_IF = 0x11 
KEY_IFDEF = 0x12 
KEY_IMPORT = 0x13 
KEY_INCLUDE = 0x14 
KEY_LABEL = 0x15 
KEY_METHOD = 0x16 
KEY_OF = 0x17 
KEY_OPERATOR = 0x18 
KEY_RETURN = 0x19 
KEY_SWITCH = 0x1A 
KEY_SUBFUNC = 0x1B 
KEY_TYPE = 0x1C 
KEY_WHILE = 0x1D 
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
 80004 2A3D2121 140004 5E5E 140004 2B2B 150004 2D2D
 160004 3C3C 170004 3E3E 180004 5C5C 30005 2525
 1C000C 2626 190004 7C7C 1A0004 4100 B1005 2424
 C0004 2222 1E0085 2727 240085 3030 30D0006 3139
 30E0006 29282C2C 4000046 7D7B3B3B 4000046 5D5B3A3A 4000046 0
 220005 2 10008 D0D FE000000 A0A FE010000 2
 FE000000 20FF 10008 A0D0909 10008 1 10008 2020
 FE000000 1 10008 909 FE000000 1 40009 A0A
 2010002 3 101004A 2A2A 90001 2F2F A0001 3D3D
 1010042 1 FE000000 2F2A FE010800 1 FE000000 A0D0D
 10008 1 10008 3000 FE000000 2 40009 4100
 50B0002 2222 1D0001 8 10008 3039 FE0E0000 587878
 FE0F0000 426262 FE100000 4C6C6C FE010000 446464 FE010000 466666
 FE010000 456565 FE120000 2E2E FE110000 6 10008 3039
 FE000000 4C6C6C FE010000 446464 FE010000 466666 FE010000 456565
 FE120000 2E2E FE110000 2 10008 5800 FE000000 4C6C6C
 FE010000 2 10008 313030 FE000000 4C6C6C FE010000 4
 10008 446464 FE010000 466666 FE010000 456565 FE120000 3039
 FE000000 1 130008 2D2B2B FE130000 3 10008 3039
 FE000000 446464 FE010000 466666 FE010000 1 101004A 3D3D
 1010042 1 101004A 2B3D3D 1010042 1 101004A 3E2D3D3D
 1010042 2 101004A 3D3D 1010042 3C3C 140000 2
 101004A 3D3D 1010042 3E3E 140000 1 101004A 263D3D
 1010042 1 101004A 7C3D3D 1010042 2 101004A 7B7B
 1010042 3D3C3E3E 140000 1 1B0000 3D2125 1010842 2
 FE000000 2222 FE010000 2222 FE000800 6 FE000000 2222
 FE000100 225C FE000800 3C5C 1F0880 2A5C 200880 5B5C
 FB210880 285C FA010800 1 FE000000 3E3E FE000100 1
 FE000000 5C2A FE000900 1 FE000000 5B5B FB000100 7
 FE000000 215C FE010800 3C5C 1F0880 2A5C 200880 5B5C
 FB210880 285C FA010800 7B5C FA010800 405C 230800 2
 FE000000 2828 FA010000 2929 220000 5 FE000000 2727
 FE000100 225C 250880 3C5C 1F0880 2A5C 200880 285C
 FA010800 1 FE000000 2222 FE000100 10003 73610000 65726200
 63006B61 657361 746E6F63 65756E69 66656400 746C7561 66656400 656E69
 65006F64 66696C 65736C65 74786500 6E7265 726F66 65726F66 686361
 6E726F66 66006D75 636E75 626F6C67 67006C61 6F746F 69006669 66656466
 706D6900 74726F 6C636E69 656475 6562616C 656D006C 646F6874 666F00
 7265706F 726F7461 74657200 6E7275 74697773 73006863 75666275 7400636E
 657079 6C696877 FF000065 74000000 747865 10000 72726100 66756200
 74796200 6F640065 656C6275 6F6C6600 68007461 687361 746E69 676E6F6C
 6F687300 73007472 75007274 65747962 6E697500 6C750074 676E6F 6F687375
 7472 0'
}