/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: desc 03.11.06 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: ��������� �������� ����������, ����������, ���������� �����
*
******************************************************************************/


#include "func.h"
#include "macroexp.h"

/*-----------------------------------------------------------------------------
*
* ID: desc_nextidvar 03.11.06 0.0.A.
*
* Summary: ��������� ��������� ����������, ���������, ���� ���������
*
-----------------------------------------------------------------------------*/
plexem STDCALL desc_nextidvar( plexem curlex, ps_descid descid )
{
   //uint flgnextlex;//������������ ��������
   uint type;      //��� ������� ����������
   pmacrores mr;   //��������� ��������� ��������������
   uint msrtype;   //��� ������� �����������
   uint stkparsc[ MAX_MSR * 2 ];//���� ��� ���������� ������������ TReserved
   puint parsc;    //������� ��������� � ����� ������������
   plexem beglex;  //������� � ������ ��������������
   plexem skiplex; //������� ������� ��� ��������

   D( "Nextidvar start\n" );
   //flgnextlex = 0;
   //if ( descid->flgdesc & DESCID_PAR )
   //   flgnextlex = LEXNEXT_IGNLINE;
   if ( curlex->type == LEXEM_OPER &&
        curlex->oper.operid == OpComma )     
   {
      if ( descid->idtype )
      {
         curlex = lexem_next( curlex, LEXNEXT_IGNLINE );   
         if (descid->flgdesc & DESCID_PARFUNC)
         {
            descid->idtype = 0;     
         }
      }      
   }

   if ( !( descid->flgdesc & DESCID_VAR ) && 
        curlex->type == LEXEM_OPER && curlex->oper.operid == OpLine )
   {      
      descid->idtype = 0;
      curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
   }
   //���������� ��� ��������������
   if ( curlex->type != LEXEM_NAME )
   {  //��������������� ������ ���
      descid->idtype = 0;
      return curlex;
   }
   type = bc_type( curlex );
   if ( descid->idtype && type )
   {   //������ ����� ���
      descid->idtype = 0;
   }
   
   if ( !descid->idtype )
   {   //�������� ����� ���
      if ( !type || curlex->flag & LEXF_CALL )
      {         
         if ( descid->flgdesc & DESCID_PARFUNC &&
             curlex->type == LEXEM_NAME )
            msg( MExptype | MSG_LEXERR, curlex );//��������� ��� ����         
         return curlex;
      }
      descid->idtype = type;
      curlex = lexem_next( curlex, 0/*flgnextlex*/ );
   }
   //�������� �������������
   
   if ( curlex->type != LEXEM_NAME )
      msg( MExpname | MSG_LEXERR, curlex );//��������� �������������   

   beglex = curlex;
   descid->name = lexem_getname( curlex );
   descid->lex = curlex;
   descid->msr = 0;
   descid->oftype = 0;
   descid->lexres = 0;

   //��������� ������������
   if ( curlex->flag & LEXF_ARR )
   {
      if ( descid->flgdesc == DESCID_VAR && descid->idtype != TReserved )
      {  // ���� �� ��� Reserved �� ��������� ��������
         parsc = stkparsc;
         out_add2uint( CVarload, fd.varcount );
         *(parsc++) = type;
         *(parsc++) = 0;
      }
      curlex = lexem_next( curlex, 0/*flgnextlex*/ );

      while ( 1 ) //���� �� ������������
      {
         curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
         if ( !( descid->flgdesc & DESCID_PAR ))
         {   //����� ���� �����, ���������
            if ( descid->flgdesc == DESCID_VAR && descid->idtype != TReserved )
            {
               //��������� ���������
               curlex = f_expr( curlex, EXPR_ARR | EXPR_COMMA, &msrtype, 0 );
               *(parsc++) = msrtype;
               *(parsc++) = 0;
            }
            else
            {
               //��������� ��������������/�����
               curlex = macroexpr( curlex, &mr );
               if ( mr->vallexem.type = LEXEM_NUMBER &&
                     mr->vallexem.num.type == TUint )
               {
                  descid->msrs[descid->msr] = mr->vallexem.num.vint;
               }
               else
                  msg( MExpuint | MSG_LEXERR, curlex );
            }
         }
         descid->msr++;
         if ( curlex->type == LEXEM_OPER )
         {
            if ( curlex->oper.operid == OpComma )
            {                  
               continue;
            }
            if ( curlex->oper.operid == OpRsqbrack )
            {
               break;
            }
         }
         msg( MExpcomma | MSG_LEXERR, curlex );
      }
   }

   curlex = lexem_next( curlex, 0/*flgnextlex*/ );

   //��������� of
   if ( curlex->type == LEXEM_KEYWORD &&
        curlex->key == KEY_OF )
   {      
      if ( (( povmtype)PCMD( type ))->index.type )
         msg( 0 | MSG_LEXERR, curlex );
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
      descid->oftype = bc_type( curlex );
      if ( !descid->oftype )
         msg( MExptype | MSG_LEXERR, curlex );//������ ���� ������ ��� ����� of
      curlex = lexem_next( curlex, 0 );
   }

   //�������� ���������
   switch ( descid->flgdesc )
   {
      case DESCID_GLOBAL:
      case DESCID_TYPE:
         if ( curlex->type == LEXEM_OPER &&
               curlex->oper.operid == OpSet )
         {
            curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
            curlex = macroexpr( curlex, &mr );
            descid->lexres = &mr->vallexem;
         }
         //curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
         break;
      case DESCID_VAR:
         if ( descid->idtype != TReserved )
         {
            if ( descid->oftype )
            {
               out_adduints( 5, CVarload, fd.varcount, CCmdload, descid->oftype,
               bc_find( curlex, "@oftype", 2, descid->idtype, TUint ) );
            }
            if ( descid->msr )
               out_adduint(
                     bc_funcname( curlex, "@array", descid->msr+1, stkparsc )->vmo.id );

         }
         var_checkadd( descid );
         if ( ( curlex->type == LEXEM_OPER &&
              curlex->oper.operid == OpSet ) ||
              ( curlex->type == LEXEM_KEYWORD &&
              curlex->key == KEY_AS ))
         {
            //�������� �� ��������� �������� �������
            for( skiplex = curlex + 1; skiplex < curlex; skiplex++ )
               skiplex->type = LEXEM_SKIP;
            curlex = f_expr( beglex, EXPR_COMMA, 0, 0 );
         }
         //��������� ���������
         break;
      case DESCID_PARFUNC:
      case DESCID_PARSUBFUNC:
         var_checkadd( descid );
         break;
   }

   /*if ( curlex->type == LEXEM_OPER &&
        curlex->oper.operid == OpComma )     
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE );   */
   D( "Nextidvar stop\n" );
   return curlex;
}


/*-----------------------------------------------------------------------------
*
* ID: desc_idtype 03.11.06 0.0.A.
*
* Summary: ��������� �������� ����
*
-----------------------------------------------------------------------------*/
plexem STDCALL desc_idtype( plexem curlex, ps_desctype desctype)
{
   D( "type start\n" );
   desctype->idtype = bc_type( curlex );
   desctype->msr = 0;
   desctype->oftype = 0;

   if ( desctype->idtype )
   {
      curlex = lexem_next( curlex, 0 );

      if ( curlex->type == LEXEM_OPER &&
           curlex->oper.operid == OpLsqbrack ) //��������� ������������ []
      {   //������ ��� ����� ��� ������������� �� ������ �������
         while ( 1 ) //���� �� ������������
         {
            curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
            desctype->msr++;
            if ( curlex->type == LEXEM_OPER )
            {
               if ( curlex->oper.operid == OpComma )
               {
                  continue;
               }
               if ( curlex->oper.operid == OpRsqbrack )
               {
                  curlex = lexem_next( curlex, 0 );
                  break;
               }
            }
            if ( desctype->msr > 2 )
               msg( MExpcomma | MSG_LEXERR, curlex );
            else
            {
               return curlex - 1;
            }
         }
      }

      if ( curlex->type == LEXEM_KEYWORD &&
           curlex->key == KEY_OF )//��������� ���� �������� of
      {
         curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
         desctype->oftype = bc_type( curlex );
         if ( !desctype->oftype )
            msg( MExptype | MSG_LEXERR, curlex );
         curlex = lexem_next( curlex, 0 );
      }
   }
   D( "type stop\n" );
   return curlex;
}
