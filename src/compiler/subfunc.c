/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: subfunc 02.02.06 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: ��������� ����������
*
******************************************************************************/

#include "func.h"

/*-----------------------------------------------------------------------------
*
* ID: f_subfunc 02.02.06 0.0.A.
*
* Summary: The subfunc processing
*
-----------------------------------------------------------------------------*/
plexem STDCALL f_subfunc( plexem curlex )
{
   uint       fd_lastcurcount;//���������� �������� ���. ���������� � ������� �����
   uint       fd_functype;  //������� ��� �������
   uint       fd_funcoftype;  //������� ������ �������
   uint       fd_oldoffbvar;//������� �������� � ����� ��������� ����������
   uint       offbvars;     //�������� � ����� ��������� ���������� ��� ����������

   pflabel    curlabel;     //������� ������� � ������� �����
   pflabel    endlabel;     //����� ������� �����
   uint       offblabels;   //������ ���������� � ����� �����

   uint       addr;         //����� ���������� � ��������
   uint       pars;         //���������� ���������� � ����������
   uint       offbvardef;   //�������� � ������ �������� ����������

   s_desctype desctype;     //��������� ��� ��������� ���� ����������
   s_descid   descvar;      //��������� ��� �������� ���������� ��� ��������� ����������
   pfvar      var;          //��������� �� ��������� ����������-����������

   uint       isreturn;     //���� ������ �� �������
   plexem     lexname;      //������� � ������ �������
   uint       off;          //��������� ���������� ��� ��������

   if ( fd.bllevel > 1 )
      msg( MSublevel | MSG_LEXERR, curlex );

//�������������
   desctype.idtype = 0;
   descvar.idtype = 0;
   _compile->pout = fd.bout = &fd.bsubout;

   offblabels  = fd.blabels.use;
   fd_functype = fd.functype;
   fd_funcoftype = fd.funcoftype;

   //if ( !fd.bsubout.use )
   if ( !fd.offsubgoto )
   {
      out_add2uint( CGoto, 0 );
      fd.offsubgoto = fd.bsubout.use - 4;
   }
   addr = fd.bsubout.use/sizeof( uint );

//��� ������������� �������� ���� ������   
   if ( curlex->type == LEXEM_NAME )
      curlex = desc_idtype( curlex, &desctype );
   if ( desctype.idtype )
   {
      fd.functype = desctype.idtype;
      fd.funcoftype = desctype.oftype;
      //������������� ��������
      out_add2uint( CSubret, (( povmtype)PCMD( fd.functype ))->stsize );
   }
   else
   {
      fd.functype = 0;
      fd.funcoftype = 0;
   }
//��� �������
   curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
   if ( curlex->type != LEXEM_NAME )
      msg( MExpname | MSG_LEXERR, curlex );//������ ������ ���� �������������
   lexname = curlex;
   offbvars = fd.bvars.use;
   descvar.idtype = fd.functype;
   descvar.oftype = fd.funcoftype;
   descvar.name = lexem_getname( lexname );
   descvar.lex = lexname;
   descvar.flgdesc = DESCID_SUBFUNC;
   var_checkadd( &descvar );

//������ ����������
   curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
   fd_oldoffbvar = fd.oldoffbvar;
   fd.oldoffbvar = fd.bvars.use;
   pars = 0;
   if ( curlex->type == LEXEM_OPER &&
        curlex->oper.operid == OpLbrack )//����������� ������
   {
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE );

      fd_lastcurcount = fd.lastcurcount;
      fd.lastcurcount = fd.curcount;
      fd.curcount = 0;
      offbvardef = fd.bvardef.use;

      curlex = var_def( curlex, DESCID_PARSUBFUNC );

      pars = fd.curcount;
      if ( fd.curcount )
      {
         out_add2uint( CSubpar, fd.blcount - 1 );//�������� ����������
         buf_appenduint( &fd.bhead, fd.curcount );
         fd.curcount = 0;
      }
      else
      {
         fd.curcount = fd.lastcurcount;
         fd.lastcurcount = fd_lastcurcount;
      }

      if ( curlex->type != LEXEM_OPER ||
           curlex->oper.operid != OpRbrack )//����������� ������
         msg( MExpclosebr | MSG_LEXERR, curlex );// ������ ��������� ����������� ������
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
   }

//������ ���������� ��� ��������� ����������
   var = (pfvar)( fd.bvars.data + offbvars );
   var->flg  = FVAR_SUBFUNC;
   var->addr = addr;
   var->pars = pars;
   var->offbvardef = offbvardef;

//��������� ���� �������
   curlex = f_body( curlex );

//������� ���������� �� ����� ��������� ����������
   off = (uint)fd.bvars.data + fd.oldoffbvar;
   for ( (uint)var = (uint)fd.bvars.data + fd.bvars.use - sizeof( fvar );
         (uint)var >= off; var-- )
   {
      if ( var->hidn )
         var->hidn->val = var->oldoffbvar;
   }
   fd.bvars.use = fd.oldoffbvar;
   fd.oldoffbvar = fd_oldoffbvar;

//��������� ���������, ������������� �����
   isreturn = 0;
   curlabel = ( pflabel )( fd.blabels.data + offblabels );
   endlabel = ( pflabel )( fd.blabels.data + fd.blabels.use );
   while( curlabel < endlabel )
   {
      if ( curlabel->type & LABT_GT )
      {
         if ( ( curlabel->type & LABT_GTUNDEF ) == LABT_GTUNDEF )
            msg( MUnklabel | MSG_LEXNAMEERR, curlabel->lex );

         *( puint )(fd.bsubout.data + curlabel->offbout ) =
               ((( pflabel )(fd.blabels.data + curlabel->link ))->offbout)/sizeof(uint);
         if ( !isreturn )
         {
            //�������� ����� ��� ������������ (�� �� ��� �������)
            (( pflabel )(fd.blabels.data + curlabel->link ))->type |= LABT_LABELWORK;
         }
      }
      else
      if ( curlabel->type & LABT_RETURN )
         isreturn = 1;//������������� ����
      else
      if ( curlabel->type & LABT_LABELWORK )
         isreturn = 0;//���� ���� ������������ �����, �� ���������� ����
      curlabel++;
   }
   fd.blabels.use = offblabels;

//�������� ������� �� �������
   if ( fd.functype )
   {
      if ( !isreturn )
         msg( MMustret | MSG_LEXNAMEERR, lexname );
   }
   else
      if ( !isreturn )
         out_adduint( CSubreturn );
//�������������� ������
   _compile->pout = fd.bout = &fd.bfuncout;
   fd.functype = fd_functype;
   fd.funcoftype = fd_funcoftype;

   return curlex;
}