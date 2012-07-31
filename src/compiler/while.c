/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: while 09.02.07 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: The while and do-while statements
*
******************************************************************************/

#include "func.h"

/*-----------------------------------------------------------------------------
*
* ID: c_while 09.02.07 0.0.A.
*
* Summary: The while processing
*
-----------------------------------------------------------------------------*/
plexem STDCALL c_while( plexem curlex )
{
   uint       labbeg;          //����� ������
   uint       labend;          //����� �����
   uint       offlcbreak;    //�������� � ������� �����
   uint       offlccontinue; //�������� � ������� �����

   fd.blcycle++;
D( "While start\n" );
   //��������� ����� �� ������
   labbeg = j_label( LABT_LABELVIRT, -1 );

   //��������� ����������� ���������
   curlex = f_expr( curlex, EXPR_BOOL, 0, 0 );

   //��������� ��������� ����� �����
   offlcbreak = fd.offlcbreak;
   offlccontinue = fd.offlccontinue;

   //��������� ������� �� �����
   fd.offlcbreak = j_jump( CIfze, LABT_GTVIRT, -1);
   fd.offlccontinue = -1;

   //��������� ����
   curlex = f_body( curlex );

   //��������� ������� �� ������
   j_jump( CGoto, LABT_GTVIRT, labbeg );

   //��������� ����� �� �����
   labend = j_label( LABT_LABELVIRT, -1 );

   //���� ��������� ��������� �� �����
   j_correct( fd.offlcbreak, labend );

   //���� ��������� ��������� �� ������
   j_correct( fd.offlccontinue, labbeg );

   //�������������� ����� �����
   fd.offlcbreak = offlcbreak;
   fd.offlccontinue = offlccontinue;
   fd.blcycle--;
D( "While stop\n" );
   return curlex;
}

/*-----------------------------------------------------------------------------
*
* ID: c_dowhile 09.02.07 0.0.A.
*
* Summary: <do_while> processing
*
-----------------------------------------------------------------------------*/
plexem STDCALL c_dowhile( plexem curlex )
{
   uint       labbeg;          //����� ������
   uint       labend;          //����� �����
   uint       labcont;         //����� ����������
   uint       fd_offlcbreak;    //�������� � ������� �����
   uint       fd_offlccontinue; //�������� � ������� �����

D( "DoWhile start\n" );
   fd.blcycle++;
   //��������� ����� �� ������
   labbeg = j_label( LABT_LABELVIRT, -1 );

   //��������� ��������� ����� �����
   fd_offlcbreak = fd.offlcbreak;
   fd_offlccontinue = fd.offlccontinue;

   //��������� ������� �� �����
   fd.offlcbreak = -1;
   fd.offlccontinue = -1;

   //��������� ����
   curlex = f_body( curlex );

   //�������� ��������� ����� while
   curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
   if ( curlex->type != LEXEM_KEYWORD || curlex->key != KEY_WHILE )
      msg( MExpwhile | MSG_LEXERR, curlex );
   curlex = lexem_next( curlex, 0 );
   //��������� ����� �� ����������
   labcont = j_label( LABT_LABELVIRT, -1 );

   //��������� ����������� ���������
   curlex = f_expr( curlex, EXPR_BOOL, 0, 0);
   //��������� ������� �� ������
   j_jump( CIfnze, LABT_GTVIRT, labbeg );

   //��������� ����� �� �����
   labend = j_label( LABT_LABELVIRT, -1 );

   //���� ��������� ��������� �� �����
   j_correct( fd.offlcbreak, labend );

   //���� ��������� ��������� �� ����������
   j_correct( fd.offlccontinue, labcont );

   //�������������� ����� �����
   fd.offlcbreak = fd_offlcbreak;
   fd.offlccontinue = fd_offlccontinue;
   fd.blcycle--;
D( "DoWhile stop\n" );
   return curlex;
}