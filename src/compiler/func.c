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
* Summary: ��������� �������, ������, ��������
*
******************************************************************************/

#include "func.h"
#include "bcodes.h"
#include "out.h"
#include "alias.h"

s_funcdata fd;

/*-----------------------------------------------------------------------------
*
* ID: m_func 02.11.06 0.0.A.
*
* Summary: The func, method, operator, property, text processing
*
-----------------------------------------------------------------------------*/
plexem STDCALL m_func( plexem curlex, uint flgextern )
{
#ifdef DOUT
   uint     i;
#endif 


   uint     funckey;  //��� �������
   uint     flgfunc;  //����� �������   

   pflabel  curlabel; // ������� ������� � ������� �����
   pflabel  endlabel; // ����� ������� �����
   uint     isreturn; //���� return

   uint     thistype; //��� ���������� this ��� �������+
   pubyte   name;     //��� �������
   plexem   lexname;  //������� � ������ �������
   plexem   lexprev;

   s_desctype desctype;//�������� ����
   s_descid   descvar; //�������� ����������

   uint off_parcount; //�������� � ��������� ������� �� ���. ����������
   uint off_blccount; //�������� � ��������� ������� �� ���. ������

   bcflag     bcf;    //���������� ��� ��������� ������ �������
   pbuf       b;
   pfwith     pwith; 
   pvmobj     funcobj;   
   uint       thisid; //����� ���������� ��� this � ����� �������

D( "Func start\n" );

// �������������
   desctype.idtype = 0;
   descvar.idtype = 0;
   descvar.flgdesc = 0;
   mem_zero( &fd, sizeof( fd ) );
   thistype = 0;
   funckey = curlex->key;
   hash_init( &fd.nvars, sizeof( uint ) );
   hash_init( &fd.nlabels, sizeof( uint ) );
   for ( b = &fd.bhead; b <= &fd.bvarsas; b++ )
   {
      buf_init( b );
      buf_reserve( b, 0x200 );
      b->step = 0x200;
   }
   fd.bvars.use = sizeof( fvar );
   fd.blabels.use = sizeof( flabel );
//   _compile->pout = &fd.bhead;   
//   fd.blcount = 0;
//   fd.varcount = 0;
//   fd.curcount = 0;
//   fd.lastcurcount = 0;
//   fd.bllevel = 0;
//   fd.blcycle = 0;
   fd.offlcbreak = -1;
   fd.offlccontinue = -1;   
//   fd.functype = 0;

   switch ( funckey )
   {
      case KEY_METHOD:
         flgfunc = GHBC_METHOD;
         break;
      case KEY_OPERATOR:
         flgfunc = GHBC_OPERATOR;
         break;
      case KEY_PROPERTY:
         flgfunc = GHBC_PROPERTY;
         break;
      case KEY_TEXT:
         flgfunc = GHBC_TEXT;
         break;
      default:
         flgfunc = 0;
   }
   curlex = lexem_next( curlex, LEXNEXT_IGNLINE );

// �������� ��� ������������� �������� �������/������ ���� �� ����
   if ( curlex->type == LEXEM_NAME )
      curlex = desc_idtype( curlex, &desctype );

   if ( desctype.idtype )
   {
      if ( ( funckey == KEY_METHOD || funckey == KEY_PROPERTY ) &&
           curlex->type == LEXEM_OPER &&
           curlex->oper.operid == OpWith )
      {
         //������� �� ������� ����� ������� ������� ��� �������
         desctype.idtype = 0;
         curlex--;
      }
      else
      {
         fd.functype = desctype.idtype;
         fd.funcoftype = desctype.oftype;
      }
   }
   lexprev = curlex;
   curlex = lexem_next( curlex, LEXNEXT_SKIPLINE );
// �������� ��� ������� ��� ������
   if ( funckey == KEY_METHOD || funckey == KEY_PROPERTY )
   {
      //�������� ��� �������
	  if ( curlex->type > 32 )
		 msg( MExptype | MSG_LEXERR, lexprev );
	  if ( thistype = bc_type( curlex ) )
      {
         curlex = lexem_next( curlex, 0 );
         if ( curlex->type == LEXEM_OPER &&
              curlex->oper.operid == OpWith )
         {
            curlex = lexem_next( curlex, 0 );
         }
         else
            msg( MExppoint | MSG_LEXERR, curlex );
      }
      else
         msg( MExptype | MSG_LEXERR, curlex );
   }
// ��������� ����� �������, ������ ...   
   if ( funckey == KEY_OPERATOR )
   {
      if ( curlex->type != LEXEM_OPER )
         msg( MExpoper | MSG_LEXERR, curlex );
      name = ( pubyte )&curlex->oper.name;
   }
   else
   {
      if ( curlex->type != LEXEM_NAME )
         msg( MExpname | MSG_LEXERR, curlex );
      name = lexem_getname( curlex );      
   }
   lexname = curlex;
   _vm.pos = curlex->pos;
   
// ��������� ������ ��������
   curlex = lexem_next( curlex, flgextern ? 0 : LEXNEXT_IGNLINE );   
   curlex = bc_flag( curlex, BFLAG_FUNC, &bcf );   
   flgfunc |= GHCOM_NAME | bcf.value;
   _compile->pout = &fd.bhead;   
   out_head( OVM_BYTECODE, flgfunc, name );

   create_varmode( &fd.bhead, &desctype, 0 );//������������ ��������

   off_parcount = fd.bhead.use;
   out_adduint( 0 );//���������� ����������

   if ( funckey == KEY_METHOD || funckey == KEY_PROPERTY )
   {   //�������� ��������� this
      mem_zero( &descvar, sizeof( descvar ));
      descvar.idtype = thistype;
      descvar.name = "this";
      descvar.lex = curlex;
      descvar.flgdesc = DESCID_PARFUNC;

      pwith = ( pfwith )buf_appendtype( &fd.bwith, sizeof( fwith )) ;
      pwith->num = var_checkadd( &descvar );
      pwith->oftype = 0;
      pwith->type = thistype;
   }

//��������� ������ ����������
   if ( curlex->type == LEXEM_OPER &&
        curlex->oper.operid == OpLbrack )//����������� ������
   {
      curlex = lexem_next( curlex, LEXNEXT_IGNLINE );
      curlex = var_def( curlex, DESCID_PARFUNC );
      if ( curlex->type != LEXEM_OPER ||//��������� �������
           curlex->oper.operid != OpRbrack )//����������� ������
         msg( MExpclosebr | MSG_LEXERR, curlex );

      curlex = lexem_next( curlex, flgextern ? 0 : LEXNEXT_IGNLINE );
   }
   else
   {
      if ( funckey == KEY_OPERATOR )
         msg( MExpopenbr | MSG_LEXERR, curlex );
   }

   fd.flgfunc = flgfunc;
   if ( flgfunc & GHBC_RESULT )
   {   //�������� ��������� result
      if ( !fd.functype || fd.functype <= TUlong )
         msg( MResulttype | MSG_LEXERR, curlex );
      mem_zero( &descvar, sizeof( descvar ));
      descvar.idtype = desctype.idtype;
      descvar.oftype = desctype.oftype;
      descvar.flgdesc = DESCID_PARFUNC;
      descvar.name = "result";
      descvar.lex = curlex;
      fd.idresult = var_checkadd( &descvar );
      fd.functype = 0;
   }
   if ( fd.varcount )
   {
      *( puint )( fd.bhead.data + off_parcount ) = fd.varcount;//���-�� ����������
      if ( flgfunc & ( GHBC_ENTRY | GHBC_MAIN ) )
         msg( MMainpar | MSG_LEXERR, curlex );
      fd.curcount = 0;
   }
   off_blccount = fd.bhead.use;
   out_adduint( 0 );//���������� ������

   if ( funckey == KEY_PROPERTY )
   {      
      if ( ( fd.functype && fd.varcount > 1 ) ||
           (!fd.functype && fd.varcount != 2 ))
      {
         msg( MProppar | MSG_LEXERR, curlex );//�������� ���������� ���������� � �������� ��������
      }
      if ( type_fieldname( thistype, name ) )
      {
         msg( MPropfield | MSG_LEXERR, curlex );//�������� ��������� � ������ ����
      }
   }
   
   funcobj = load_bytecode( &fd.bhead.data, flgextern ? VMLOAD_EXTERN : VMLOAD_FIRST );   
   if ( bcf.value & GHRT_ALIAS )
   {  
      alias_setid( bcf.alias, funcobj->id );     
   }
   if ( !( flgextern ) )
   {      
      if ( _compile->flag & CMPL_DEBUG )
      {  
         _compile->pout = fd.bout = &fd.bsubout;
         out_adduints( 3,  CDatasize, 
                           str_len( _compile->cur->filename ) + 5,
                           str_pos2line( _compile->cur->src, lexname->pos, 0 ) + 1 );
         out_addptr( str_ptr( _compile->cur->filename ), str_len( _compile->cur->filename ) + 1 );                     
         out_adduint( CDbgFunc );
         _compile->pout = fd.bout = &fd.bfuncout; 
      }
      _compile->pout = fd.bout = &fd.bfuncout;
      if ( funckey == KEY_TEXT )
      {   //�������� ��������� this ��� Text �������
         mem_zero( &descvar, sizeof( descvar ));
         descvar.idtype = TUint;
         descvar.name = "this";
         descvar.lex = curlex;
         descvar.flgdesc = DESCID_VAR;///DESCID_PARFUNC;
         thisid = var_checkadd( &descvar );
         
         /*pwith = ( pfwith )buf_appendtype( &fd.bwith, sizeof( fwith )) ;
         pwith->num = var_checkadd( &descvar );
         //print( "ssssssssss %x %x %x %x", fd.bvars.data, fd.bvars.use, pwith->num, sizeof( fvar ) );
         pwith->oftype = 0;
         pwith->type = TStr;*/
         ((pfvar)(fd.bvars.data + fd.bvars.use - sizeof( fvar )))->type = TStr;
         out_adduints( 4, CVarptrload, thisid, CGetText, CSetI );
         /*buf_appenduint( &fd.bblinit, CVarptrload );
         buf_appenduint( &fd.bblinit, thisid );
         buf_appenduint( &fd.bblinit, CGetText );
         buf_appenduint( &fd.bblinit, CSetI );*/
      }
      curlex = f_body( curlex );
      
      *((puint)(fd.bhead.data+off_blccount)) = fd.blcount;

      curlabel = ( pflabel )( fd.blabels.data ) + 1;
      endlabel = ( pflabel )( fd.blabels.data + fd.blabels.use );
      //�������� ������������� ����� � �������� ������� �� �������
      isreturn = 0;
      while( curlabel < endlabel )
      {
         if ( curlabel->type & LABT_GT )
         {
            if ( ( curlabel->type & LABT_GTUNDEF ) == LABT_GTUNDEF )
               msg( MUnklabel | MSG_LEXNAMEERR, curlabel->lex );
            *( puint )(fd.bfuncout.data + curlabel->offbout ) = 
                     ((( pflabel )(fd.blabels.data + curlabel->link ))->offbout + 
                      fd.bsubout.use )/sizeof(uint);
            if ( !isreturn )//�������� ����� ��� ������������ (�� �� ��� �������)
               (( pflabel )(fd.blabels.data + curlabel->link ))->type |= LABT_LABELWORK;            
         }
         else
         if ( curlabel->type & LABT_RETURN )
         {
            isreturn = 1;//������������� ����
         }
         else
         if ( curlabel->type & LABT_LABELWORK )
            isreturn = 0;//���� ���� ������������ �����, �� ���������� ����
         curlabel++;
      }
      if ( fd.functype )
      {
         if ( !isreturn )
            msg( MMustret | MSG_LEXNAMEERR, lexname );
      }
      else
         if ( !isreturn )
         {
            if ( fd.flgfunc & GHBC_RESULT )
            {
               out_add2uint( CVarload, fd.idresult );
            }
            out_adduint( CReturn );
         }      
      buf_add( &fd.bhead, &fd.bvardef );
      
      if ( fd.bsubout.use )
      {
         if ( fd.offsubgoto )
         {
            //*((( puint)fd.bsubout.data ) + 1) = fd.bsubout.use/sizeof( uint );
            *( puint )( fd.bsubout.data + fd.offsubgoto ) = fd.bsubout.use / sizeof( uint );
         }
         buf_add( &fd.bhead, &fd.bsubout );
      }
      buf_add( &fd.bhead, &fd.bfuncout );
      _compile->pout = &fd.bhead;
      out_finish();
#ifdef DOUT
   //����������� ����� 
   //if ( name[0] == 'c' && name[1] == 'r' ) getch();
   print( "FUNC OUT %x %s:\n", funcobj->id, name );
   for (i = 0; i < fd.bhead.use ; i++ )
   {
      print( "  %x", fd.bhead.data[i] );
   } 
   print( "\n" );
#endif            
      load_bytecode( &fd.bhead.data, VMLOAD_OK );
    //  print( "funcobjid2 =%x\n", funcobj->id );
   }
   //������� ������
   for ( b = &fd.bhead;/*&fd.bblinit;*/ b <= &fd.bvarsas; b++ )
   {
      buf_delete( b );
   }
   hash_delete( &fd.nvars );
   hash_delete( &fd.nlabels );

D( "Func Stop\n" );
   return curlex;
}

