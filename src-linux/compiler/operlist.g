/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: operlist 26.10.06 0.0.A.
*
* Author: Alexander Krivonogov ( algen )
*
* Summary: The program generates syslex.h and syslex.� files 
*
******************************************************************************/

include : $"..\..\lib\gt\gt.g"
include : $"..\bytecode\cmdlist.g"

/*-----------------------------------------------------------------------------
*
* ID: operlist_h 26.10.06 0.0.A. 
* 
* Summary: The .h output function.
*  
-----------------------------------------------------------------------------*/
text operlist_h( arr aopers of str, arr acom of str, arr amflgs of str, arr aflgscom of str )
\@headerout( "operlist_h", "Generated with 'operlist' program", 
"This file contains a list of the compiler's or VM's messages.")
#ifndef _OPERLIST_
#define _OPERLIST_

   #ifdef __cplusplus               
      extern "C" {                 
   #endif // __cplusplus      

#include "../common/types.h"

//����� �������� ��� ������� ��������
\{
   uint i
   
   fornum i, *amflgs
   {
      @("#define "@amflgs[i]@"\t\t"@"0x".hexu( 1<<i )@"\t\t//"@aflgscom[i]@"\l")
      //@(amflgs[i]@"xx")
   }
}

#define  OPERCOUNT  \( *aopers ) //���������� ��������

//�������������� ��������
enum {
\{   
   
   fornum i = 0, *aopers
   { 
      @"   \(aopers[ i ] ),\t\t  // 0x\( hex2stru( i )) \"\( acom[ i ] )\"\l" 
   }   
}
};

//��������� ��� �������� ��������
typedef struct {
   ubyte     before; // ��������� �� ����� � ���� ��������
   ubyte     after;  // ��������� ����� ������� � ���� ��������
   ushort    flgs;   // ��� �������� OPER_   
} soper, * psoper;

extern const soper opers[];
extern const ubyte operlexlist[];
   #ifdef __cplusplus              
      }                            
   #endif // __cplusplus

#endif // _OPERLIST_
\!


func str buf2const( str name, str res, buf b )
{
   uint i
   uint lnum
   res = "const ubyte \(name)[] = { "
   fornum i=0, *b
   {
      if b[i] 
      {  
         res += "'"
         res.appendch( b[i])
         res += "'"         
      }
      else
      {
         res += "0"
      }
      res +=", "      
      if *res - lnum  > 75 
      {                  
         res += "\l"
         lnum = *res
      }  
   }
   res += "};\l"
   return res
}

/*-----------------------------------------------------------------------------
*
* ID: operlist_c 26.10.06 0.0.A. 
* 
* Summary: The .c output function.
*  
-----------------------------------------------------------------------------*/

text  operlist_c( buf blex, arr aprin of str, arr aprout of str, arr atblflgs of str, arr aopers of str, arr acom of str )
\@headerout( "operlist_c", "Generated with 'operlist' program", "")

#include "operlist.h"

//������� ����������� � ����� ��������
const soper opers[] = {
\{
   uint i  
   
   fornum i, *atblflgs
   {
      @"   { \( aprin[i] ), \( aprout[i] ), \(atblflgs[i]) },// '\( acom[ i ] )'  \(aopers[i]) \l"
   }      
}
};

//������ ����� ��������
\{ str slex
   @buf2const( "operlexlist", slex, blex)
}

\!

/*-----------------------------------------------------------------------------
*
* ID: opermain 26.10.06 0.0.A.ABKL 
* 
* Summary: The main function.
*  
-----------------------------------------------------------------------------*/

func opermain<main>
{   
   str hout
   gt  opergt
//   gtitems gtis
   
   uint i,j   
   uint gtflgs, gttbl
   arr  aflgs  of str   //������ ����� ������
   arr  amflgs of str   //������ ����� ������ � ������������ ������� 
   arr  aflgscom of str //����������� � ����� ������
   arr  atblflgs of str //������ ������� ������ ��� ������� ��������
   arr  aopers   of str //������ ��������������� ��������
   arr  aoperscom of str //������ ������������ � ��������������� ��������
   arr  aprin  of str   //������ ������� ����������� ��� ������� ��������
   arr  aprout of str   //������ �������� ����������� ��� ������� ��������
   buf  blex            //��������� ������������� ��������
   uint flgwasundef     //��������� �������� ���� undef
   
   opergt.read( "operlist.gt" )
   
   gtflgs as opergt.find("flags")   
   aflgs.expand( *gtflgs )
   amflgs.expand( *gtflgs )
   aflgscom.expand( *gtflgs )
   foreach curf, gtflgs//.items//( gtis )
   {
//      curf as gtitem
      aflgs[i] = curf.name
      amflgs[i] = "OPF_" + curf.name
      amflgs[i].upper()
      aflgscom[i++] = curf.get( "comment" )      
   } 
   
   gttbl as opergt.find("tbl")
   atblflgs.expand( *gttbl )
   fornum i= 0, *atblflgs
   {  
   atblflgs[i].clear()
   }
   print( "\(atblflgs[j] )\n" ) 
   aopers.expand( *gttbl )
   aoperscom.expand( *gttbl )
   aprin.expand( *gttbl )
   aprout.expand( *gttbl )
   foreach cur, gttbl//.items( gtis )
   {      
//      cur as gtitem
      if cur.find( "prin" )
      {
         cur.get("prin",aprin[j])
      }
      else : aprin[j]="0"
      if cur.find( "prout" )
      {
         cur.get("prout",aprout[j])
      }
      else : aprout[j]="0"      
      aopers[j] = "Op" + cur.name
      aopers[j].uppersub( 2, 1 )
      aoperscom[j] = cur.value
      if flgwasundef && !cur.find( "post" )
      {
         blex += ""
      }
      else : blex += cur.value           
      fornum i=0, *aflgs
      {
         if cur.find( aflgs[i] ) 
         {
            if *atblflgs[j] : atblflgs[j]@" | "
            atblflgs[j]@amflgs[i] 
         }
      }
      if cur.find( "undef" ) : flgwasundef = 1
		else : flgwasundef = 0
      j++
   }

   hout@operlist_h( aopers, aoperscom, amflgs, aflgscom )
   hout.write( "operlist.h" )
   hout.clear()
   hout@operlist_c( blex, aprin, aprout, atblflgs, aopers, aoperscom )
   hout.write( "operlist.c" )
   congetch("Press any key...")   
}
