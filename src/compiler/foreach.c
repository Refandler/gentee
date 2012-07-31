/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved.
* This file is part of the Gentee open source project - http://www.gentee.com.
*
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT").
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: foreach 09.02.07 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: The foreach statement
*
******************************************************************************/

#include "func.h"
#include "bcodes.h"

/*-----------------------------------------------------------------------------
*
* ID: c_foreach 08.02.07 0.0.A.
*
* Summary: The foreach processing
*
-----------------------------------------------------------------------------*/
plexem STDCALL c_foreach( plexem curlex )
{
   uint       labbeg;           //����� ������
   uint       labend;           //����� �����
   uint       labcont;          //����� �� continue
   uint       fd_offlcbreak;    //�������� � ������� �����
   uint       fd_offlccontinue; //�������� � ������� �����
   uint       indexnum;         //�����/��� ���������� �������
   uint       objnum;           //����� �������������� ���������� �������� ������
   uint       fordata;          //����� ���������� �� ���������� fordata

   plexem     indexlex;      //������� � ��������� ����������

   uint       objtype;       //��� �������   
   uint       itemtype;      //��� ��������
   uint       deftype;       //��������� ��� ��������
   uint       vartype;

   uint       bcfirst;       //����-��� ������ First
   uint       bceof;         //����-��� ������ Eof
   uint       bcnext;        //����-��� ������ Next
   //uint       bcset;         //����-��� ������������ ��������
   uint       bcadvget;      //����-��� ��� ��������������� ���� ������������
   uint       bcadvset;      //����-��� ��� ��������������� ���� ������������

   pfvar      var;          //��������� �� ��������� ��������� ����������
   pfvaras    varas;        //��������� �� ��������� as
   phashiuint phitem;       //������� ���������� � ��������� ����������
   pubyte     varname;      //��� ��������� ����������
   uint       flgnewvar;    //���� ��������� ����� ��������� ���������� � ���������
   s_descid   descvar;      //��������� ��� �������� ��������� ����������
   uint       offvar;       //�������� ��������� ��������� ����������

   //pvmfunc    pfunc;    //��������� �� ��������� ��������
   //uint       parsc[4]; //��������� ��� ��������� ���� ��������

D( "Foreach start\n" );
   fd.blcycle++;

   //��������� ������� �����
   
   if ( curlex->type != LEXEM_NAME )
      msg( MExpname | MSG_LEXERR, curlex );
   vartype = bc_type( curlex );   
   if ( vartype )
   {
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
   }
   if ( curlex->type != LEXEM_NAME )
      msg( MExpname | MSG_LEXERR, curlex );
   
   indexlex = curlex;

   //���������� �� ��������� ����������
   phitem = (phashiuint)hash_find( &fd.nvars, lexem_getname( curlex ) );
   //flgnewvar = 1;
   if ( phitem && phitem->val &&
        !(( var = (pfvar)( fd.bvars.data + ( offvar = phitem->val )))->flg & FVAR_SUBFUNC))
   {  //������������� ���� � ������� ��������� ����������
      flgnewvar = 0;
      indexnum = var->num;        
   }
   else
   {
      flgnewvar = 1;      
      varname = lexem_getname( curlex );
   }
   curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
   if ( curlex->type != LEXEM_OPER || curlex->oper.operid != OpComma )
      msg( MExpcomma | MSG_LEXERR, curlex );
   curlex = lexem_next( curlex, LEXNEXT_IGNLINE );

   //��������� ���������-�������
   objnum = var_addtmp( TUint, 0 ); //�������� ���������� ��� �������� ������ �������
   out_add2uint( CVarptrload, objnum );//���� ��� ��� ���������� ���������� ���������
   curlex = f_expr( curlex, EXPR_NONULL, &objtype, &itemtype );
   if ( !itemtype )
   {
      /*if ( ! (itemtype = (( povmtype)PCMD( objtype ))->index.type ))
         itemtype = TUint;*/
      itemtype = (( povmtype)PCMD( objtype ))->index.type;
      
   }   
   out_adduint( CSetI );//���� ��� �������� ��������
   //�������� ����-���� �������
   bcfirst = bc_find( indexlex, "@first", 2, objtype, TAny );
   bceof   = bc_find( indexlex, "@eof", 2, objtype, TAny );
   bcnext  = bc_find( indexlex, "@next", 2, objtype, TAny );


   if ( (( pvmfunc)PCMD( bcfirst ))->ret->type != TUint )
   {
      itemtype = (( pvmfunc)PCMD( bcfirst ))->ret->type;
      deftype = TUint;
      /*if ( !(itemtype = (( pvmfunc)PCMD( bcfirst ))->ret->type ))
      {
         itemtype = TUint;
      }*/
   }
   fordata = var_addtmp((( pvmfunc)PCMD( bcfirst ))->params[1].type , 0 );   

   //��������� �����
   if ( (( pvmobj )PCMD( itemtype ))->flag & GHTY_STACK )
   {//������� ��� ��������, �������� ��������� � ��������
    //�������������� ��� first/next ����� ���������� ������ ���������
      //���������� ����� ��������� �������
      /*parsc[0] = itemtype;
      parsc[1] = 0;
      parsc[2] = itemtype;
      parsc[3] = 0;
      pfunc = bc_funcname( curlex, "#=", 2, parsc );*/
      //bcset = CSetI;            
      bcadvget = artypes[ itemtype ];
      bcadvset = (( povmtype )PCMD( itemtype ))->stsize == 1 ? CSetI : CSetL;
      deftype = itemtype;
   }
   else
   {  //��� �������� ���������      
      //bcset = CSetI;
      bcadvget = 0;
      deftype = TUint;
   }   
   if ( flgnewvar )
   {  //�������� ����� ��������� ����������-�������
      mem_zero( &descvar, sizeof( descvar ));
      descvar.idtype = deftype;
      descvar.name = varname;
      descvar.lex = curlex;
      descvar.flgdesc = DESCID_VAR;
      offvar = fd.bvars.use;
      indexnum = var_checkadd( &descvar );   
   }
   var = (( pfvar )( fd.bvars.data + offvar ));
   if ( deftype != ( var->flg & FVAR_UINTAS ? TUint : var->type ) ||
        ( vartype && vartype != itemtype ) )
      msg( MDiftypes | MSG_LEXERR, indexlex );
   if ( !((( pvmobj )PCMD( itemtype ))->flag & GHTY_STACK) ||
        var->flg & FVAR_UINTAS )
   {
      varas = ( pfvaras )buf_appendtype( &fd.bvarsas, sizeof( fvaras ) );

      varas->offbvar = offvar;
      varas->type = var->type;
      varas->oftype = var->oftype; 
      varas->flg = var->flg; 
      
      var->type = itemtype;
      var->oftype = 0;
      var->flg |= FVAR_UINTAS;      
   }

   //��������� ����� first
   out_adduints( 8, CVarptrload,
                  indexnum,
                  CVarload,
                  objnum,
                  CVarload,
                  fordata,
                  bcfirst,
                  /*bcset*/CSetI );

   //��������� ����� �� ������
   labbeg = j_label( LABT_LABELVIRT, -1 );

   out_debugtrace( curlex );

   //����� ������ Eof
   //��������� ����������� ���������
   out_adduints( 5, CVarload,
                  objnum,
                  CVarload,
                  fordata,
                  bceof );

   //��������� ��������� ����� �����
   fd_offlcbreak = fd.offlcbreak;
   fd_offlccontinue = fd.offlccontinue;

   //��������� ������� �� �����
   fd.offlcbreak = j_jump( CIfnze, LABT_GTVIRT, -1);
   fd.offlccontinue = -1;

   if ( bcadvget )
   {
      //��������� ��� ������� �����
      out_adduints( 7, CVarptrload,
                     indexnum,
                     CVarptrload,
                     indexnum,
                     CGetI,
                     bcadvget,
                     bcadvset );
      /*out_adduints( 6, CVarptrload,
                     indexnum,
                     CVarload,
                     indexnum,
                     bcadvget,
                     bcset );*/
   }

   //��������� ����
   curlex = f_body( curlex );

   //����� �� continue
   labcont = j_label( LABT_LABELVIRT, -1 );

   //����� ������ Next
   out_adduints( 8, CVarptrload,
                  indexnum,
                  CVarload,
                  objnum,
                  CVarload,
                  fordata,
                  bcnext,                  
                  /*bcset*/CSetI );

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

D( "Foreach stop\n" );
   return curlex;
}