/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: vmload 18.10.06 0.0.A.
*
* Author: Alexey Krivonogov ( gentee )
*
* Summary: Load objects into VM
* 
******************************************************************************/

#ifndef _VMLOAD_
#define _VMLOAD_

   #ifdef __cplusplus               
      extern "C" {                 
   #endif // __cplusplus      

#include "vmrun.h"

// ����� ��� VAR DWORD MODE

#define  VAR_NAME   0x01   // ���� ��� 
#define  VAR_OFTYPE 0x02   // ���� of type
#define  VAR_DIM    0x04   // ���� ����������� [,,,]
#define  VAR_IDNAME 0x08   // For define if macro has IDNAME type
// � ���� ������, ��� ������, �� ��� �������� ��� ��������������
#define  VAR_PARAM  0x10   // �������� ������� ��� ����������
#define  VAR_DATA   0x20   // ������� ������

//--------------------------------------------------------------------------
/*    FULL MODE

��� FULL MODE ������ ���������� � 
1 - byte - ��� ������� OVM_*****
2 - uint - ����� flags
3 - BWD  - ������ ����������� ������ - ���� ������� ����� ������
4 - pbyte - ������������������ ���� �� 0 - ��� ������� ���� ���� ���� GHCOM_NAME 

//--------------------------------------------------------------------------

������ �������� ���������� ������������� ���� VAR DWORD MODE 

BWD - ���
ubyte - [VARFLAG] ����� VAR_

if [VARFLAG] & VAR_NAME
   pbyte - ��� ������� - ������������������ ���� �� 0

if [VARFLAG] & VAR_OFTYPE
   BWD - ��� - oftype 

if [VARFLAG] & VAR_DIM
   ubyte - [DIM] - �����������
   for [DIM]
      BWD - �������� ������������

if [VARFLAG] & VAR_DATA
   ������������������ ������. ��� ����� - �����
   ��� ������ 
      BWD - ������ 
      ����� ���� ������ 

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_TYPE 

if  GHTY_INHERIT
   BWD - ��� - �������� inherit ���� ���� ���� GHTY_INHERIT

if GHTY_INDEX
   BWD - ��� - index 
   BWD - ��� - index oftype 

if GHTY_INITDEL
   BWD - ID - method init
   BWD - ID - method delete

if GHTY_EXTFUNC
   BWD - ID - method oftype
   BWD - ID - method  = %{}

if GHTY_ARRAY 
   if BWD > MAX_MSR - ���� ����� ID array 
   else array[ MAX_MSR ] - ������ array 

BWD - [COUNT] - ���������� ��������. ���� GHTY_STACK, �� ������

for [COUNT]
   �������� [VAR DWORD MODE]

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_BYTECODE

[VAR DWORD MODE] - ��� ������������� ��������
BWD - [PAR COUNT] - ���������� ����������

for [ PAR COUNT ]  
   �������� [VAR DWORD MODE] ����������

BWD - [SET COUNT] - ���������� ������ ����������

for [ SET COUNT ]  
   BWD - [VAR COUNT] - ���������� ����������

for [SUMMARY VAR COUNT]
   �������� [VAR DWORD MODE] ����������

dwords - ������������������ dword - ������� ���� ����

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_EXFUNC

[VAR DWORD MODE] - ��� ������������� ��������
BWD - [PAR COUNT] - ���������� ����������

for [ PAR COUNT ]  
   �������� [VAR DWORD MODE] ����������

if [GHEX_IMPORT]
   BWD - library id
   pubyte - the original name

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_DEFINE

dword [COUNT] - ���������� ���������
for [COUNT]
   �������� [VAR DWORD MODE]

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_IMPORT

pubyte - the name of the file
if GHIMP_LINK
   dword [SIZE] - the size of DLL
   ubyte SIZE - the body of the dll

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_GLOBAL

[VAR DWORD MODE] - ��� ����������

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_ALIAS

BWD - the id of linked object

//--------------------------------------------------------------------------

 ������ DWORD MODE ��� OVM_RESOURCE

BWD - [COUNT] - ���������� �����
for [COUNT]
   BWD - the id of type
   TStr pubyte - ������ 
*/

// Parameters for 'mode' of load_bytecode
#define  VMLOAD_GE      0   // Loading from GE 
#define  VMLOAD_G       1   // Loading from G
#define  VMLOAD_EXTERN  1   // Extern description
#define  VMLOAD_FIRST   2   // Pre-loading function
#define  VMLOAD_OK      3   // Loading byte-code

uint    STDCALL load_bwd( pubyte * ptr );
uint    STDCALL load_convert( pubyte * ptr );
pvmobj  STDCALL load_addobj( uint over );
pvmobj  STDCALL load_stack( int top, int cmd, stackfunc pseudo );
pvmobj  STDCALL load_type( pubyte* input );
pvmobj  STDCALL load_bytecode( pubyte* input, uint mode );
pvmobj  STDCALL load_exfunc( pubyte* input, uint over );
pvmobj  STDCALL load_define( pubyte* input );
pvmobj  STDCALL load_import( pubyte* input );
pvmobj  STDCALL load_global( pubyte* input );
pvmobj  STDCALL load_alias( pubyte* input );

#ifdef _ASM
   void STDCALL ge_toasm( uint id, pbuf bout );
#endif

/*

  �� ��������� �������� ��������������� �������������

  ��������� ���� GHRT_INIT GHRT_DEINIT � �����
  �������������� global variables
  ��������� entry
  ��������� main ���� ��� ����������
*/

//--------------------------------------------------------------------------


   #ifdef __cplusplus              
      }                            
   #endif // __cplusplus

#endif // _VMLOAD_

