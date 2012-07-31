/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: func 02.11.06 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: �������� �������, ��������, �������� ����������� ��� ����������
*
******************************************************************************/

#ifndef _FUNC_
#define _FUNC_

   #ifdef __cplusplus
      extern "C" {
   #endif // __cplusplus

#include "../os/user/defines.h"
#include "../lex/lex.h"
#include "../lex/lexgentee.h"
#include "../common/arrdata.h"
#include "../common/msglist.h"
#include "../genteeapi/gentee.h"
#include "../vm/vmload.h"
#include "../bytecode/cmdlist.h"
#include "lexem.h"
#include "operlist.h"
#include "type.h"
#include "out.h"

/*-----------------------------------------------------------------------------
*
* ID: funcdata 02.11.06 0.0.A.
*
* Summary: funcdata structure.
*
-----------------------------------------------------------------------------*/

typedef struct
{
   //�� ������ ������� ������������ buf, � ������ ������������� ��������� � �����
   buf  bhead;    //��������� �������
   buf  bvardef;  //���� ��� �������� ��������� ����������
   buf  bfuncout; //����-���
   buf  bsubout;  //����-��� ��� ����������
   buf  bblinit;  //������� ���� ��� ������ ������������� ������
   buf  bvars;    //���� ��������� ����������, �������� fvar
   buf  blabels;  //���� �����, �������� flabel
   buf  bwith;    //���� ���������� with, �������� fwith
   buf  bvarsas;  //���� ����������, �������� fvaras

   pbuf bout;     //������� ����� ������ ��������

   hash nvars;    //��� ������� ��������� ����������
   hash nlabels;  //��� ������� �����

   uint blcount;      //����� ���������� ������
   uint varcount;     //����� ���������� ��������� ����������
   uint curcount;     //������� ���������� ��������� ����������
   uint lastcurcount; //���������� ��������� ���������� � ������� �����

   uint oldoffbvar;   //������ ������� ��������� ���������� �� ������ �������� �����
   uint functype;     //��� �������
   uint funcoftype;   //������ �������
   uint bllevel;      //������� ����������� �������� �����
   uint offlcbreak;   //�������� � ������� ����� ����������� �� break ��� �����
   uint offlccontinue;//�������� � ������� ����� ����������� �� continue ��� �����
   uint blcycle;      //����������� ������
   uint flgfunc;      //���� �������
   uint idresult;     //������������� ��������� result
   uint offsubgoto;   //�������� �������� ����� ���������
} s_funcdata, * ps_funcdata;

//��������� ��� �������� �������� ����� ���������� as
typedef struct
{
   uint offbvar;  //�������� �������� � ������� bvars
   uint type;     //�������� ���
   uint oftype;   //��� ��������
   uint flg;
} fvaras, *pfvaras;

//��������� ��� �������� with
typedef struct
{
   uint num;      //����� ��������� ����������
   uint type;     //��� �������
   uint oftype;   //��� �������� �������   
} fwith, *pfwith;

//��������� ��� �������� �������� � ����
typedef struct
{
   hashitem item;
   uint     val;
} hashiuint, *phashiuint;


#define FVAR_SUBFUNC 0x01
#define FVAR_UINTAS  0x02
//��������� ��������� ����������
typedef struct
{
   phashiuint hidn; //������������� � ������� ���
   uint flg;        //���� 1 ������ ������������� ���
   uint type;       //��� ����������
   uint num;        //����� ���������� � ������� ��������� ����������
   uint msr;        //����������� ��� �������
   uint oftype;     //��� �������� �������
   uint oldoffbvar; //�������� ������� �������� ���������� � bvars + 1, ��� ��������������� ����������

   uint addr;       //����� ��� ����������
   uint pars;       //���������� ���������� � ����������
   uint offbvardef; //�������� � ������ �������� ���������� �������

} fvar, *pfvar;

// ��������� ��� ������� �����
typedef struct
{
   uint type; //��� LABT_*
union {
   uint link; //�����, ������������� � ��� ������� �����, ������������� � �������
   phashiuint hitem;
};
   uint offbout;//�������� � ��������
   plexem lex;  //��������� �� ������� � ������ ��� LABT_LABEL
} flabel, *pflabel;


//��������� �������� ����
typedef struct
{
   uint idtype;//������������� ����
   uint oftype;//��� ��������
   byte msr;   //�����������
} s_desctype, *ps_desctype;


//--------------------------------------------------------------------------
//body.c
plexem STDCALL f_body( plexem plex );

//----------------------------------------------------------------------------
//desc.c
plexem STDCALL desc_nextidvar( plexem curlex, ps_descid pdescid );
plexem STDCALL desc_idtype( plexem curlex, ps_desctype pdesctype );

//----------------------------------------------------------------------------
//expr.c
extern uint artypes[];
#define EXPR_ORD    0x01   //�������� flg, ��� ��������� �������� ���������
#define EXPR_MACROS 0x02   //��������� ��� ��������
#define EXPR_VAR    0x04   //��������� � ����������� ��������� ����������
#define EXPR_COMMA  0x08   //��������� ������������ �� �������
#define EXPR_BOOL   0x10   //��������� ������
#define EXPR_NONULL 0x20   //��� ��������� ������ ���� �� ����
#define EXPR_ARR    0x40   //����������� �������
//����� ��������� ������� ��� �������� ������ ���������� � ���������
#define L_OPERAND    0x01  //�������
#define L_POST_CLOSE 0x02  //������� ���� ��������, ����������� ������
#define L_BINARY     0x04  //�������� ��������
#define L_UNARY_OPEN 0x08  //������� ��� ��������, ����������� ������
#define L_FUNC       0x10  //��������� ���� ��� ������� ��������� (

plexem STDCALL f_expr( plexem curlex, uint flg, puint rettype, puint retoftype );

//----------------------------------------------------------------------------
//extern.c
plexem STDCALL m_extern( plexem curlex );

//----------------------------------------------------------------------------
//for.c
plexem STDCALL c_for( plexem curlex );
plexem STDCALL c_fornum( plexem curlex );

//----------------------------------------------------------------------------
//foreach.c
plexem STDCALL c_foreach( plexem curlex );

//----------------------------------------------------------------------------
//func.c
extern s_funcdata fd;

plexem STDCALL m_func( plexem curlex, uint flgextern );

//----------------------------------------------------------------------------
//if.c
plexem STDCALL c_if( plexem curlex );

//----------------------------------------------------------------------------
//goto.c
plexem STDCALL c_goto( plexem curlex );
plexem STDCALL c_label( plexem curlex );

//----------------------------------------------------------------------------
//jump.c
#define LABT_VIRT       0x0100
#define LABT_GT         0x0200
#define LABT_GTUNDEF    ( LABT_GT | 0x0001 )  //������������� �������, � link ������������� � ��� �������
#define LABT_GTDEF      ( LABT_GT | 0x0002 )  //����������� ������� ��� ������� �� ����������� �����, � link ������������� � ������� �����
#define LABT_LABEL      0x0004  //�����, � link ������������� � ��� �������
#define LABT_LABELUNDEF 0x0008  //������������ �����
#define LABT_GTVIRT     ( LABT_VIRT | LABT_GT )
#define LABT_LABELVIRT  ( LABT_VIRT ) //����������� �����
#define LABT_SUBFUNC    0x1000   //����� ��������� ������ ����������
#define LABT_RETURN     0x2000 //�� ������ ����� ��� �������
#define LABT_LABELWORK  0x4000

void STDCALL j_correct( uint curoff, uint link );
uint STDCALL j_jump( uint cmd, uint flag, uint link );
uint STDCALL j_label( uint flag, uint link );

//----------------------------------------------------------------------------
//subfunc.c
plexem STDCALL f_subfunc( plexem curlex );

//----------------------------------------------------------------------------
//switch.c
plexem STDCALL c_switch( plexem curlex );

//----------------------------------------------------------------------------
//vars.c
#define DESCID_GLOBTYPE   0x010 //�������� ���������� ����������, �������� ��������� - arr a[10,20] of str
#define DESCID_GLOBAL     0x010
#define DESCID_TYPE	     0x011
#define DESCID_SUBFUNC    0x021//�������� ����������
#define DESCID_PAR        0x040 //�������� ��������� ������� - arr a of str
#define DESCID_PARFUNC    0x040
#define DESCID_PARSUBFUNC 0x041
#define DESCID_VAR        0x080 //�������� ��������� ���������� - arr a[x+10,y+20] of str

plexem STDCALL var_def( plexem curlex, uint flgdesc );
uint STDCALL var_checkadd( ps_descid descvar );
STDCALL create_varmode( pbuf out, ps_desctype desctype, ps_descid descid );
plexem STDCALL var_def( plexem curlex, uint flgdesc );
uint STDCALL var_add( phashiuint hidn, ps_descid descvar );
uint STDCALL var_addtmp( uint type, uint oftype );

//----------------------------------------------------------------------------
//while.c
plexem STDCALL c_while( plexem curlex );
plexem STDCALL c_dowhile( plexem curlex );

//----------------------------------------------------------------------------
//with.c
plexem STDCALL c_with( plexem curlex );

#ifdef DOUT
#define D printf
#else
#define D /**////##/
#endif
   #ifdef __cplusplus
      }
   #endif // __cplusplus

#endif // _FUNC_
