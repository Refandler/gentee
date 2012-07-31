/******************************************************************************
*
* Copyright (C) 2009, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* Author: Alexey Krivonogov ( gentee )
*
******************************************************************************/

#include "huffman.h"
/*#ifdef LAUNCHER
   #include "K:\Gentee\Gentee Language\Opti Launcher\memory.h"
#else
   #include "K:\Gentee\Gentee Language\VM Lib\memory.h"
#endif
*/
//--------------------------------------------------------------------------

pshuf  STDCALL huf_new( pshuf huf, dword alphabet )
{
   huf->allcode = ( alphabet + ( alphabet & 0x1 )) << 1;
   huf->stack = mem_allocz( 1024 );
   huf->prevlen = mem_allocz( 2048 );
   huf->tree = mem_allocz( huf->allcode * sizeof( shufleaf ));
   huf->numcode = alphabet;
   huf->root = NULL;
   huf->bit = 0;
   huf->fixed = 0;
   huf->normalize = ( pdword )mem_alloc( 2048 * sizeof( dword ) );
   huf->freq = ( pdword )mem_alloc( 2048 * sizeof( dword ) );
//   huf->pretree = 0;
//   huf->maxfreq = 512;//1000;
   return huf;
}

//--------------------------------------------------------------------------

void  STDCALL huf_destroy( pshuf huf )
{
   mem_free( huf->tree );
   mem_free( huf->stack );
   mem_free( huf->prevlen );
   mem_free( huf->normalize );
   mem_free( huf->freq );
}

//--------------------------------------------------------------------------

void  STDCALL huf_normilize( pshuf huf )
{
   pshufleaf cur, node;
   dword     i, codes, count;
//   pshufleaf prevstk[ 2048 ];
   pdword    prev = huf->normalize;

   for ( i = 0; i < 2048; i++ )
      prev[ i ] = 0;//( dword )NULL;

   codes = huf->numcode;
   while ( 1 )
   {
      cur = huf->tree;
      count = 0;
      while ( cur < huf->tree + codes )
      {
         if ( cur->freq )
         {
            count++;
            // ���� ��� ��� � ����� �� ����������� �����
            if ( prev[ cur->freq ] )
            {
               // �������� ����� �������
               node = huf->tree + codes++;
               node->freq = cur->freq - 1;
               node->left = ( pshufleaf )prev[ cur->freq ];
               node->right = cur;
               (( pshufleaf)prev[ cur->freq ])->up = node;
               prev[ cur->freq ] = 0;//NULL;
               cur->up = node;
               if ( !node->freq ) break;
            }
            else
            {
               prev[ cur->freq ] = ( dword )cur;
            }
            cur->freq = 0;
         }
         cur++;
      }
      if ( count == 1 )
      {
         node = huf->tree + codes;
         node->freq = 0;
         node->left = ( pshufleaf )prev[ 1 ];
         node->right = NULL;
         (( pshufleaf)prev[ 1 ])->up = node;
      }
      if ( !node->freq ) break;
   }
   huf->root = node;
   huf->root->up = NULL;
}

//--------------------------------------------------------------------------
// ����������� ������ - ���������� ���������� ���. 
// ����������� ������ ��������� � huf->inout 1 ���� = 1 ���
/*dword STDCALL huf_entree( pshuf huf )
{
   dword   i;

   huf->size = 0;
   for ( i = 0; i < huf->numcode; i++ )
   {
//      if ( !i )
//         printf("Freq = %i\n", huf->tree[ i ].freq );
      huf_pack( huf, huf->tree[ i ].freq, 8 );
//      huf->inout[ i ] = huf->tree[ i ].freq;
   }
//   huf->size = huf->numcode;

   dword     length[ 1024 ];
   dword     min, max, i = 0, k;
   pshufleaf cur = huf->tree;
   pshufleaf end = huf->tree + huf->numcode;
   shuf  huftree;

   length[ i ] = min = max = cur->freq;
   cur++;
   while ( cur < end )
   {
      if ( cur->freq )
      {
         if ( !min || cur->freq < min ) min = cur->freq;
         else
            if ( cur->freq > max ) max = cur->freq;
      }
      if ( ( length[ i ] & 0xFFFF ) == cur->freq && ( length[i] >> 24 ) < 77 )
         length[ i ] += 0x01000000;
      else
         length[ ++i ] = cur->freq;
      cur++;
   }
   if ( !huf->pretree )
   {
      huf_new( &huftree, 20 ); //  0 - 15 + 16 17 18 19
      huftree.pretree = 1;

      for ( k = 0; k <= i; k++ )
      {
         dword  code = length[ k ] & 0xFFFF;
         dword  repeat = length[ k ] >> 24;
      
         if ( code > 15 )
         {
            huf_incfreq( &huftree, code );
         }
         else
            huf_incfreq( &huftree, code );
         if ( repeat )
         {
            if ( repeat < 3 )
            {
               if ( repeat == 2 )
                  huf_incfreq( &huftree, code );
               huf_incfreq( &huftree, code );
//                  huf_incfreq( &huftree, code ? code - min + 1 : 0 );
//               huf_incfreq( &huftree, code ? code - min + 1 : 0 );
            }
            else
            if ( repeat < 7 )
            {
//               huf_incfreq( &huftree, huftree.numcode - 3 );
               huf_incfreq( &huftree, huftree.numcode - 3 );
            }
            else
               if ( repeat < 15 )
               {
                  huf_incfreq( &huftree, huftree.numcode - 2 );
               }
               else
               {
                  huf_incfreq( &huftree, huftree.numcode - 1 );
               }
         }
      }
      huf_build( &huftree );
      mem_copy( huf->inout, huftree.inout, huftree.size );
      huf->size = huftree.size;

//      huf->stree = huftree.stree + more;
      for ( i = 0; i < huftree.numcode; i++ )
      {
//         huf->stree += huf_bits( &huftree, i );
      }
//         printf("%x ", length[ i ]);
      huf_destroy( &huftree );
      printf("SIZE = %i\n", huf->size );
   }
   else
   {
      dword  bits;//, shift = 0;

      huf->size = 0;
//      shift = min - 1;
//      if ( shift > 3 ) shift = 3;
//      max -= shift;
      // ����������� ���������� ��� �� �������
      if ( max < 4 ) bits = 2;
      else bits =  max < 8 ? 3 : 4;
      huf_pack( huf, bits - 1, 2 );
//      huf_pack( huf, shift, 2 );
//      printf("min=%i shift=%i\n", min, shift);
      cur = huf->tree;
      while ( cur < end )
      {
         huf_pack( huf, cur->freq, bits );
         printf("%x ", cur->freq );
         cur++;
      }
//      huf->stree = 4; // min
//      huf->stree += 4; // count  ( numcode - 4 )
//      huf->stree += huf->numcode * 4; // ����� pre-codes
//      for ( k = 0; i < huftree.numcode; i++ )
//      {
//         printf("%x ", length[ k ]);
//         huf->stree += huf_bits( &huftree, i );
//      }
//      for ( k = 0; k <= i; k++ )
//         printf("%x ", length[ k ]);
//      printf("MaxLEN=%i\n", max );
   }
//   huf->inout[ out++ ] = 
//   printf("Len=%i min=%i max=%i\n", i, min, max );
//   huf->stree = i;
//   for ( i = 0; i <= huf->stree; i++ )
//      printf("%x ", length[ i ]);
//   huf_init( huftree, huf->)
//   huf->stree = 0;
   return huf->size;
}*/

//--------------------------------------------------------------------------

/*
void  OSAPI loc_hufleafchange( pshufleaf one, pshufleaf two, bool rec )
{
   // ������� ������ ����� ��� ������� one �� ����� ���� ������ ������� two
   pshufleaf  upone = one->up;
   // onepair - ���� � one
   pshufleaf  onepair = ( upone->left == one ? upone->right : upone->left );
   // maxchild - ������� � ������� �������� � two
   pshufleaf  maxchild = ( two->left ? ( two->left->freq > 
              two->right->freq ? two->left : two->right ) : NULL );

   if ( upone->left == one )
      upone->left = two;
   else
      upone->right = two;
   if ( two->up->left == two )
      two->up->left = one;
   else
      two->up->right = one;
   one->up = two->up;
   two->up = upone;

   // ������ �������� �������� ��� ���� pair ����� ����� ������ 
   // ��� ��� ������ ���� onepair � cur.
   if ( rec && maxchild && onepair->freq < maxchild->freq )
   {
      // ���������� �������� ������� � two
      two->freq -= maxchild->freq - onepair->freq;
      // ������ �� �������
      loc_hufleafchange( maxchild, onepair, 0 );
   }
   // �� ���� ������� onepair �� ����� ���� ������ two
}

//--------------------------------------------------------------------------

void  OSAPI huf_init( pshuf huf )
{
   word       numcode = ( word )PARA( huf );
   pshufleaf  hufcur;
   word       i = 0;

   huf->tree = obj_create( huf, &arr_info, ( pvoid )
                  LONGMAKE( numcode<<1, sizeof( shufleaf )) );
   huf->numcode = numcode;
   huf->maxfreq = 512;//1000;
   
   // �������������� ������ ��������� � ���������� ��������
   hufcur = ( pshufleaf )huf->tree->buf.buf;
   while ( i < huf->numcode )
   {
      mem_zero( hufcur, sizeof( shufleaf ));
      hufcur->code = i++;
      hufcur->freq = i;
      hufcur++;
   }

   CMD( huf, HufTreeBuild );
}

//--------------------------------------------------------------------------

void  OSAPI huf_treebuild( pshuf huf )
{
   pshufleaf  cur = ( pshufleaf )huf->tree->buf.buf;
   pshufleaf  left;
   pshufleaf  right;
   long       i = 0;
   long       full = huf->numcode + huf->numcode - 1;

   huf->allcode = huf->numcode;
   while ( i++ < full )
   {
      cur->up = NULL;
      cur++;
   }

   while ( huf->allcode < full )
   {
      // ���� ��� ����������� �������
      cur = ( pshufleaf )huf->tree->buf.buf;
      left = NULL;
      right = NULL;

      i = 0;
      while ( i++ < huf->allcode )
      {
         if ( !cur->up  )
         {
            if ( !left || cur->freq < left->freq )
            {
               if ( left && !right )
                  right = left;
               left = cur;
            }
            else
               if ( !right || cur->freq < right->freq )
                  right = cur;
         }
         cur++;
      }
      // �� ������ ���� ������ ���������� ������
      cur = CMDA( huf->tree, IDataPtr, huf->allcode++ );
      cur->code = huf->allcode - 1;
      cur->freq = left->freq + right->freq;
      cur->left = left;
      cur->right = right;
      left->up = cur;
      right->up = cur;
   }
   cur->up = NULL;
   huf->root = cur;
}

//--------------------------------------------------------------------------

void  OSAPI huf_update( pshuf huf, word code )
{
   pshufleaf  cur = CMDA( huf->tree, IDataPtr, code );
   pshufleaf  upcur;  // ������ ��������
   pshufleaf  pair;   // ���� �������
   long       i;

   while ( cur )
   {
      upcur = cur->up;

      // ����������� �������� ����� ����� ���� ������� ��������
      if ( upcur && upcur->up )
      {
         // ���������� ���� � ��������� ���� �� ���� �������
         // ���� ������� �������� ����� �������
         pair = ( upcur->up->left == upcur ? upcur->up->right :
                  upcur->up->left );

         // ������ ����� ������ � ��� ������ ���� ������� ������ �����, 
         // � ��� ���������� � cur ����� �� 1 ������
         if ( cur->freq >= pair->freq )
            loc_hufleafchange( cur, pair, TRUE );
      }
      // ������ ������� � cur
      cur->freq++;
      cur = cur->up;
   }
   if ( huf->root->freq >= huf->maxfreq )
   {
      cur = ( pshufleaf )huf->tree->buf.buf;
      for ( i = 0; i < huf->allcode; i++ )
         cur++->freq >>= 1; 
   }
}

//--------------------------------------------------------------------------

retend  OSAPI huf_func( pshuf huf )
{
   switch ( PARCMD( huf ))
   {
      case ObjInit:
         huf_init( huf );
         break;
      
      case HufTreeBuild:
         huf_treebuild( huf );
         break;

      case HufUpdate:
         huf_update( huf, ( word )PARA( huf ));
         goto retobj;

      default:
         return CONTINUE;
   }
   return BREAK;

retobj:
   return BREAKOBJ;
}

//--------------------------------------------------------------------------

sobjinfo  huf_info = { sizeof( shuf ), ty_Huf, &obj_info, huf_func, 
                       POSTPAR_NONE };
*/
//--------------------------------------------------------------------------
