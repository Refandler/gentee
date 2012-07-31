/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: vrun 18.10.06 0.0.A.
*
* Author: Alexey Krivonogov ( gentee )
*
* Summary: Execute the function.
* 
******************************************************************************/

#ifndef _VMRUN_
#define _VMRUN_

   #ifdef __cplusplus               
      extern "C" {                 
   #endif // __cplusplus      

#include "vm.h"

#pragma pack(push, 1)
// ��������� ��� �������� ��������� ������� ������� (������)
typedef struct
{
   puint       start;  // �������� ������ ����� �������. ���� ������� ���������� 
                       // � ���������� � ����� ��������� ������ ��� ������ ���� 
                       // ������������ �������
   puint       cmd;    // ��������� �� ������� ������� � ���� �������
   puint       top;    // ��������� �� ������� ����� - ������ ��������� �������
   uint        uiret;  // ������� ���������� dword
   pvmfunc     func;   // ������� ������� ����������� ������
   puint       clmark; // ����� �� ������� ��������� ����. ������ ����� start + predesc
                       // ���������� �� ����� �������� � ��������� �������.
   uint        nline;  // The latest line in debug mode
} stackpos, * pstackpos;
#pragma pack(pop)

// ��� �������� �������
typedef void ( STDCALL* stackfunc )( pstackpos );


#define  BCODE(x)  (( povmbcode )x->func)

//--------------------------------------------------------------------------

void  STDCALL pseudo_i( pstackpos curpos );
void  STDCALL pseudo_ul( pstackpos curpos );
void  STDCALL pseudo_pul( pstackpos curpos );
void  STDCALL pseudo_l( pstackpos curpos );
void  STDCALL pseudo_pl( pstackpos curpos );
void  STDCALL pseudo_f( pstackpos curpos );
void  STDCALL pseudo_pf( pstackpos curpos );
void  STDCALL pseudo_d( pstackpos curpos );
void  STDCALL pseudo_pd( pstackpos curpos );
void  STDCALL pseudo_ui( pstackpos curpos );
void  STDCALL pseudo_collectadd( pstackpos curpos );
uint  STDCALL vm_run( uint id, puint params, puint result, uint stacksize );
uint  STDCALL vm_runone( uint id, uint first );
uint  STDCALL vm_runtwo( uint id, uint first, uint second );
uint  STDCALL vm_calladdr( void );

   #ifdef __cplusplus              
      }                            
   #endif // __cplusplus

#endif // _VMRUN_

