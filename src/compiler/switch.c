/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: switch 08.02.07 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: The switch statement
*
******************************************************************************/

#include "func.h"
#include "bcodes.h"

/*-----------------------------------------------------------------------------
*
* ID: c_if 08.02.07 0.0.A.
*
* Summary: The switch processing
*
-----------------------------------------------------------------------------*/
//��������� ��� ��������� switch
#define SWITCH_STFIRST    0x01 //��������� ���������
#define SWITCH_STCASE     0x02 //���������� ������� ���������� case
#define SWITCH_STBODY     0x04 //���������� ���� case
#define SWITCH_STDEFAULT  0x08 //��������� default
plexem STDCALL c_switch( plexem curlex )
{
   uint      state;    //������� ��������� ������� SWITCH_*

   uint      jmpnext;// ������ ������� �� ��������� case
   uint      jmpbody;// C����� ������� �� ������ �����
   uint      jmpend; // ������ ������� �� �����

   pvmfunc   pfunc;    //��������� �� ��������� �������� ==
   uint      parsc[4]; //��������� ��� ��������� ���� �������� ==
   uint      ltype;    //��� ����� ����� ���������
   uint      dwsize;   //������ ���� ����� ����� ���������

   //�������������
   state = SWITCH_STFIRST;
   jmpnext = -1;
   jmpbody = -1;
   jmpend = -1;
D( "Switch start\n" );

   //�������� ���������
   curlex = f_expr( curlex, EXPR_NONULL, &ltype, &parsc[1] );
   parsc[0] = ltype;   
   dwsize = (( povmtype )PCMD( ltype ))->stsize; //�������� ������ ���� ����� ����� ���������

   //������� ���� switch
   curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
   if ( curlex->type != LEXEM_OPER ||
        curlex->oper.operid != OpLcrbrack )//����������� �������� ������
      msg( MLcurly | MSG_LEXERR, curlex );// ������ ��������� ����������� �������� ������
   //������� ����
   while ( 1 )
   {
      if ( jmpnext != -1 )
      {
         //������������� ���������� ��������
         j_correct( jmpnext, j_label( LABT_LABELVIRT, -1) );
         jmpnext = -1;
      }
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE  );
      if ( !(state & SWITCH_STDEFAULT ) && curlex->type == LEXEM_KEYWORD )
      {
         switch ( curlex->key )
         {
            case KEY_CASE:
               D( "Case\n" );
               curlex = lexem_next( curlex, 0 );
               //���� �������� ������� ��� �������� Case
               while ( 1 )
               {  //�������� �� ����� ���������� ���������
                  if ( !( state & SWITCH_STFIRST ) &&
                        !( state & SWITCH_STCASE ))
                     out_adduint( CPop );

                  state = SWITCH_STCASE;
                  // ��������� � ���� ������� ������������ ���������� ��������
                  out_adduint( dwsize == 1 ? CDup : CDuplong );

                  //������������ �������
                  curlex = f_expr( curlex, EXPR_COMMA | EXPR_NONULL, &parsc[2], &parsc[3]);

                  //�������� �������� ���������
                  pfunc = bc_funcname( curlex, "#==", 2, parsc );
                  out_adduint( pfunc->vmo.id );
                  if ( (( povmtype )PCMD( pfunc->ret->type ))->stsize == 2 )
                     out_adduint( CLoglongtrue );
                  
                  if ( curlex->type == LEXEM_OPER && curlex->oper.operid == OpComma )
                  {
                     D( "Comma\n" );
                     curlex = lexem_next( curlex, LEXNEXT_IGNLINE );                     
                  }
                  else
                  {
                     //������������� ������� �� ��������� Case
                     jmpnext = j_jump( CIfznocls, LABT_GTVIRT, -1 );
                     break;
                  }
                  //������������� ������� �� ���� �������� Case
                  jmpbody = j_jump( CIfnznocls, LABT_GTVIRT, jmpbody );
               }
               state = SWITCH_STBODY;
               //������������� ����� �� ������� ����
               j_correct( jmpbody, j_label( LABT_LABELVIRT, -1) );
               jmpbody = -1;
               
               //���� ��������� �������������� �����
               curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
               while ( curlex->type == LEXEM_KEYWORD && curlex->key == KEY_LABEL )
               {
                  curlex = lexem_next( curlex, 0 );
                  curlex = c_label( curlex );
                  curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
               }               
               //��������� ����
               curlex = f_body( curlex );
               //������ �� �����
               jmpend = j_jump( CGoto, LABT_GTVIRT, jmpend );
               break;

            case KEY_DEFAULT:
               //������������� ���������� ��������
               state = SWITCH_STDEFAULT;
               //���� ��������� �������������� �����
               while ( 1 )
               {
                  curlex = lexem_next( curlex, LEXNEXT_IGNLINE  );
                  if ( curlex->type == LEXEM_KEYWORD && curlex->key == KEY_LABEL )
                     curlex = c_label( curlex );
                  else
                     break;
               }               
               curlex = f_body( curlex );
               break;
            default:
               msg( MNokeyword | MSG_LEXERR, curlex );// ������ ������������ ������������� ��������� �����
         }
         continue;
      }
      else
      {
         if ( curlex->type == LEXEM_OPER && curlex->oper.operid == OpRcrbrack )
         {
            //������������� ��������� �� �����
            j_correct( jmpend, j_label( LABT_LABELVIRT, -1) );
            break;//����� �� ���� switch
         }
         msg( MRcurly | MSG_LEXERR, curlex );// ������ ��������� ����������� �������� ������
      }
   }

D( "Switch stop\n" );
   return curlex;
}