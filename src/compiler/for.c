/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: for 09.02.07 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: ����������� for, fornum
*
******************************************************************************/

#include "func.h"
#include "bcodes.h"

/*-----------------------------------------------------------------------------
*
* ID: c_for 09.02.07 0.0.A.
*
* Summary: The for processing
*
-----------------------------------------------------------------------------*/
plexem STDCALL c_for( plexem curlex )
{
   uint       labbeg;          //����� ������
   uint       labend;          //����� �����
   uint       labcont;         //����� �� continue
   uint       fd_offlcbreak;   //�������� � ������� �����
   uint       fd_offlccontinue;//�������� � ������� �����
   plexem     incrlex;         //������ ������ ��������� ����������

D( "For start\n" );
   fd.blcycle++;

   //��������� ��������� �������������
   curlex = f_expr( curlex, EXPR_COMMA, 0, 0 );

   if ( curlex->type != LEXEM_OPER || curlex->oper.operid != OpComma )
      msg( MExpcomma | MSG_LEXERR, curlex );
   curlex = lexem_next( curlex, 0 );

   //��������� ����� �� ������
   labbeg = j_label( LABT_LABELVIRT, -1 );

   //��������� ����������� ���������
   curlex = f_expr( curlex, EXPR_BOOL | EXPR_COMMA, 0, 0 );
   if ( curlex->type != LEXEM_OPER || curlex->oper.operid != OpComma )
      msg( MExpcomma | MSG_LEXERR, curlex );
   curlex = lexem_next( curlex, 0 );

   //��������� ��������� ����� �����
   fd_offlcbreak = fd.offlcbreak;
   fd_offlccontinue = fd.offlccontinue;

   //��������� ������� �� �����
   fd.offlcbreak = j_jump( CIfze, LABT_GTVIRT, -1);
   fd.offlccontinue = -1;

   //������� ����������
   incrlex = curlex;
   do
   {
      curlex = lexem_next( curlex, 0 );
   }
   while ( curlex->type != LEXEM_OPER || curlex->oper.operid != OpLcrbrack );

   //��������� ����
   curlex = f_body( curlex );

   //����� �� continue
   labcont = j_label( LABT_LABELVIRT, -1 );

   //��������� ����������
   incrlex = f_expr( incrlex, 0, 0, 0 );
   incrlex = lexem_next( incrlex, LEXNEXT_SKIPLINE );

   if ( incrlex->type != LEXEM_OPER || incrlex->oper.operid != OpLcrbrack )
      msg( MLcurly | MSG_LEXERR, incrlex );

   //��������� ������� �� ������
   j_jump( CGoto, LABT_GTVIRT, labbeg );

   //��������� ����� �� �����
   labend = j_label( LABT_LABELVIRT, -1 );

   //���� ��������� ��������� �� �����
   j_correct( fd.offlcbreak, labend );

   //���� ��������� ��������� �� ������
   j_correct( fd.offlccontinue, labcont );

   //�������������� ����� �����
   fd.offlcbreak = fd_offlcbreak;
   fd.offlccontinue = fd_offlccontinue;
   fd.blcycle--;

D( "For stop\n" );
   return curlex;
}


/*-----------------------------------------------------------------------------
*
* ID: c_fornum 09.02.07 0.0.A.
*
* Summary: The fornum processing
*
-----------------------------------------------------------------------------*/
#define INDEX_LOCVAR 0x1  //������-���������� ���������
#define INDEX_GLOBVAR 0x2 //������-���������� ����������
plexem STDCALL c_fornum( plexem curlex )
{
   plexem     indexlex;      //������� � ���������� ��������
   uint       indexflg;      //���� ���������� ������� ���������/���������� ����������
   uint       indexnum;      //�����/��� ���������� �������
   uint       indextype;     //��� �������

   uint       labbeg;          //����� ������
   uint       labend;          //����� �����
   uint       labcont;         //����� �� continue

   uint       fd_offlcbreak;   //�������� � ������� �����
   uint       fd_offlccontinue;//�������� � ������� �����

   uint       casenum;  //����� �������������� ���������� �������� ������� �������
   uint       globid;   //������������� ���������� ����������
   pfvar      var;      //��������� �� ��������� ��������� ����������
   phashiuint phitem;   //������� ���������� � ��������� ����������
   uint       parsc[4]; //��������� ��� ��������� ���� ��������

D( "Fornum start\n" );
   fd.blcycle++;
   indexlex = curlex;
   indexflg = 0;

   //��������� ���������� �������
   phitem = (phashiuint)hash_find( &fd.nvars, lexem_getname( curlex ) );
   if ( phitem )
   {  //������������� ���� � ������� ��������� ����������
      var = ( pfvar )(fd.bvars.data + phitem->val);
      if ( !(var->flg ) )
      {  // ��������� ����������
         indexnum = var->num;
         indexflg = INDEX_LOCVAR;
         indextype = var->type;
      }
   }   
   if ( !indexflg  )
   {      
      globid = bc_getid( curlex );      
      if ( globid && (( pvmobj )PCMD( globid ))->type == OVM_GLOBAL )
      {  //���������� ����������    
         indexnum = globid;
         indexflg = INDEX_GLOBVAR;
         indextype = ((povmglobal)PCMD( globid ))->type->type;
      }
   }   
   if ( !indexflg )
      msg( MUnklex | MSG_LEXNAMEERR, curlex );//����������� �������������
   if ( indextype <= TInt || indextype >= TUshort )
      msg( MVaruint | MSG_LEXERR, curlex );
   parsc[0] = indextype;

   //��������� ��������� �������������
   curlex = lexem_next( curlex, 0 );
   if ( curlex->type == LEXEM_OPER && curlex->oper.operid == OpSet )
   {
      curlex = f_expr( indexlex, EXPR_COMMA, 0, 0 );
   }


   curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
   if ( curlex->type != LEXEM_OPER || curlex->oper.operid != OpComma )
      msg( MExpcomma | MSG_LEXERR, curlex );//������ ������ ���� �������
   curlex = lexem_next( curlex, 0 );

   //��������� ��������� ������������� ��������
   //��������� ������������� �������� � ������ � ��������� ����������
   casenum = var_addtmp( indextype, 0 );
   out_add2uint( CVarptrload, casenum );
   curlex = f_expr( curlex, EXPR_NONULL, &parsc[2], &parsc[3] );

   parsc[1] = 0;   
   out_adduint( bc_funcname( curlex, "#=", 2, parsc )->vmo.id );

   //��������� ����� �� ������
   labbeg = j_label( LABT_LABELVIRT, -1 );

   out_debugtrace( curlex );
   //�������� ��������� <
   out_add2uint( indexflg & INDEX_LOCVAR ? CVarload : CPtrglobal,
               indexnum );
   if ( indexflg & INDEX_GLOBVAR )
   {
      out_adduint( CGetI );
   }
   out_adduints( 3, CVarload,
                  casenum,
                  bc_funcname( curlex, "#<", 2, parsc )->vmo.id );

   //��������� ��������� ����� �����
   fd_offlcbreak = fd.offlcbreak;
   fd_offlccontinue = fd.offlccontinue;

   //��������� ������� �� �����
   fd.offlcbreak = j_jump( CIfze, LABT_GTVIRT, -1);
   fd.offlccontinue = -1;

   //��������� ����
   curlex = f_body( curlex );

   //����� �� continue
   labcont = j_label( LABT_LABELVIRT, -1 );

   //��������� ���������� ++
   out_adduints( 3, indexflg & INDEX_LOCVAR ? CVarptrload : CPtrglobal,
                  indexnum,
                  bc_funcname( curlex, "#++", 1, parsc )->vmo.id );

   //��������� ������� �� ������
   j_jump( CGoto, LABT_GTVIRT, labbeg );

   //��������� ����� �� �����
   labend = j_label( LABT_LABELVIRT, -1 );

   //���� ��������� ��������� �� �����
   j_correct( fd.offlcbreak, labend );

   //���� ��������� ��������� �� ������
   j_correct( fd.offlccontinue, labcont );

   //�������������� ����� �����
   fd.offlcbreak = fd_offlcbreak;
   fd.offlccontinue = fd_offlccontinue;
   fd.blcycle--;

D( "Fornum stop\n" );
   return curlex;
}
