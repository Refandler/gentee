/******************************************************************************
*
* Copyright (C) 2004-2007, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: vis.splitter 31.03.08 0.0.A.
*
* Author: Alexander Krivonogov ( gentee )
*
******************************************************************************/

/* ���������� vSplitter, ��������� �� vCtrl
����� ����� ������ ��� �������, ��� ���� ����� �������� ������� ������� �������� 
TabOrder
*/
/*! � �����������: ����������� ������ �� ��������, ����������� �� �������� �������
�����, ����������� ������� ���������
*/
type vSplitter <inherit = vCtrl>
{
//Hidden Fields
   uint pAutoSize
   uint pDistance
   uint pRealDistance
   uint pSplitterWidth
   uint pOrientation
   uint pFixedPart
   uint pLeftMinSize
   uint pRightMinSize
   
   uint pRightDistance
   
   double pProportion //��������� ��� ��������� �������� ����� � ������ �����      
   uint   fDrag       //���� ������ ��������������
   uint   fUpdatingSize //���� ���������� ��������
//Events   
   evEvent  OnMoved
}

define <export>{
//Orientation values:
   soVertical   = 0 //������� ����� � ������
   soHorizontal = 1 //������� ������ � �����  
   
//FixedPart values:  ��� ��������� �������� ������ ��������
   sfpLeft  = 0     //����� ������ �� ����� ���������� 
   sfpRight = 1     //������ ������ �� ����� ����������
   sfpNone  = 2     //������� ����� ���������� ���������������
}

extern {
   property uint vSplitter.Distance()
   property vSplitter.Distance( uint val)
}

/*------------------------------------------------------------------------------
   Internal Methods
*/
/*����� vSplitter.iUpdateSize()
����������� ������� ������ � ������� �������
*/
method vSplitter.iUpdateSize()
{
   if !.hwnd : return
   //print( "setdist1 \(.Name)\( .pDistance )\n" )   
   uint distance
   .fUpdatingSize = 1
   uint width = ?( .pOrientation == $soVertical, this.Width, this.Height ) - 
                     .pSplitterWidth                     
                                 
   if int( width ) > 0 && !.pAutoSize 
   {
      switch .pFixedPart
      { 
         case $sfpLeft
         {
            .pDistance = max( int( .pDistance ), int( .pLeftMinSize ) )      
            distance = width - max( int( width - .pDistance ), int( .pRightMinSize ) )
            distance = max( int( distance ), int( .pLeftMinSize ) )
            distance = min( width, int( distance ))
         }
         case $sfpRight
         { 
            
            
            .pRightDistance = width - .pDistance
            distance = width - .pRightDistance 
            //.pDistance = width - .pRightDistance
            //.pRightDistance = width - .pDistance
            //distance = .pDistance
            //.pRightDistance = width - max( int( width - int(.pDistance) ), int( .pRightMinSize ) )
            
            
            distance = max( int( distance ), int( .pLeftMinSize ) )          
            distance = width - max( int( width - int(distance) ), int( .pRightMinSize ) )
            
            //distance = max( int( distance ), int( .pLeftMinSize ) )      
            distance = min( width, int( distance ))
            //.pRightDistance = width - distance             
         }
         default
         {
            distance = width - max( int( width - .pDistance ), int( .pRightMinSize ) )
            distance = max( int( distance ), int( .pLeftMinSize ) )
            distance = min( width, int( distance ))
         }
      }              
   }
   else 
   {
      if .pFixedPart == $sfpRight : .pRightDistance = width - int(.pDistance)
      distance = .pDistance
   }
   
   if .pRealDistance != distance
   {
      .OnMoved.Run( this )
   }
   .pRealDistance = distance
ifdef !$DESIGNING {
   if *.Comps 
   {  
      if !.Comps[0]->vCtrl.Visible : distance = 0
      elif *.Comps > 1 && !.Comps[1]->vCtrl.Visible : distance = width           
   }  
}            
   if *.Comps && .Comps[0]->vCtrl.Visible
   {
      uint left as .Comps[0]->vCtrl
      left.HorzAlign = $alhLeft
      left.VertAlign = $alvTop
      left.flgNoPosChanging = 0
      left.Left = 0
      left.Top = 0
      
      if .pOrientation == $soVertical
      { 
         left.Height = this.Height
         left.Width = distance
      }
      else
      {
         left.Height = distance
         left.Width = .Width
      }
      if !( ( .pAutoSize || .p_designing ) && .pFixedPart == $sfpLeft ) : left.flgNoPosChanging = 1      
   }
   if *.Comps > 1 && .Comps[1]->vCtrl.Visible
   {   
      uint right as .Comps[1]->vCtrl
      right.HorzAlign = $alhLeft
      right.VertAlign = $alvTop
      right.flgNoPosChanging = 0
      
      if .pOrientation == $soVertical
      {
         right.Top = 0
         right.Height = this.Height         
         right.Left = distance + .pSplitterWidth
         right.Width = .Width - distance - .pSplitterWidth         
      }
      else
      {
         right.Top = distance + .pSplitterWidth         
         right.Left = 0      
         right.Width = this.Width
         right.Height = .Height - distance - .pSplitterWidth
      }
      if !( ( .pAutoSize || .p_designing ) && .pFixedPart == $sfpRight ) : right.flgNoPosChanging = 1      
   }   
   //print( "setdist2 \(.Name)\( .pDistance )\n" )
   .fUpdatingSize = 0
}

/*------------------------------------------------------------------------------
   Properties
*/
/* �������� uint vSplitter.AutoSize - Get Set
����� ������ ���������, ����� ���������� ������ ��������� ��������, �� ���
��������� �������� ������ �������, �������� ������� �������
*/
property uint vSplitter.AutoSize()
{  
   return this.pAutoSize
}

property vSplitter.AutoSize( uint val)
{   
   if this.pAutoSize != val
   {  
      this.pAutoSize = val
      .iUpdateSize()         
   }
}

/* �������� uint vSplitter.Distance - Get Set
��������� ��������� (���������� �� ������ ��� �������� ����
*/
property uint vSplitter.Distance()
{  
   return this.pDistance
}

property vSplitter.Distance( uint val)
{   
   if this.pDistance != val
   {  
      this.pDistance = val
      .iUpdateSize()
      .pProportion = double( .pDistance ) / double( .Width )
   }
}

/* �������� uint vSplitter.SplitterWidth - Get Set
������ ������� ���������
*/
property uint vSplitter.SplitterWidth()
{  
   return this.pSplitterWidth
}

property vSplitter.SplitterWidth( uint val)
{
   val = min( max( int( val ), int( 0 ) ), 50 )
   if this.pSplitterWidth != val
   {    
      this.pSplitterWidth = val
      .iUpdateSize()
   }
}

/* �������� uint vSplitter.Orientation - Get Set
���������� ��������� (��������� �������� - so* )
*/
property uint vSplitter.Orientation()
{  
   return this.pOrientation
}

property vSplitter.Orientation( uint val)
{
   if this.pOrientation != val
   {    
      this.pOrientation = val
      .iUpdateSize()
   }
}

/* �������� uint vSplitter.FixedPart - Get Set
���������� ����� ��������� (�� �������� ������� ��� ��������� �������� ������
�������
*/
property uint vSplitter.FixedPart()
{  
   return this.pFixedPart
}

property vSplitter.FixedPart( uint val)
{
   if this.pFixedPart != val
   {    
      this.pFixedPart = val
      .iUpdateSize()      
   }
}

/* �������� uint vSplitter.LeftMinSize - Get Set
����������� ������ �����/������� �����
*/
property uint vSplitter.LeftMinSize()
{  
   return this.pLeftMinSize
}

property vSplitter.LeftMinSize( uint val)
{
   if this.pLeftMinSize != val
   {    
      this.pLeftMinSize = val      
   }
}

/* �������� uint vSplitter.RightMinSize - Get Set
����������� ������ ������/������ �����
*/
property uint vSplitter.RightMinSize()
{  
   return this.pRightMinSize
}

property vSplitter.RightMinSize( uint val)
{
   if this.pRightMinSize != val
   {    
      this.pRightMinSize = val      
   }
}

/*------------------------------------------------------------------------------
   Virtual Methods
*/
/*����������� ����� vSplitter vSplitter.mCreateWin 
�������� ����
*/
method vSplitter vSplitter.mCreateWin <alias=vSplitter_mCreateWin>()
{
   uint distance = .pDistance
   uint style = $SS_NOTIFY | $WS_CHILD | $WS_CLIPCHILDREN | 
         $WS_CLIPSIBLINGS | $WS_OVERLAPPED
ifdef $DESIGNING {
   if .p_designing : style |= $WS_BORDER
}         
   .CreateWin( "STATIC".ustr(), 0, style )
   this->vCtrl.mCreateWin()
   if !.pAutoSize : .Distance = distance 
   return this
}

/*����������� ����� vSplitter.mInsert 
������� �������� ���������
*/
method vSplitter.mInsert <alias=vSplitter_mInsert>( vComp newcomp )
{  
   if newcomp.TypeIs( vCtrl ) && *.Comps < 2
   {
      this->vCtrl.mInsert( newcomp )
      .iUpdateSize()
   }
}

/*����������� ����� vSplitter.mPosChanging 
��������� ��������
*/
method vSplitter.mPosChanging <alias=vSplitter_mPosChanging>( eventpos evp )
{
   uint old = ?( .pOrientation == $soVertical, .Width, .Height )
   this->vCtrl.mPosChanging( evp )   
   switch .pFixedPart
   {
      case $sfpRight
      {  
         /*.pDistance += ?( .pOrientation == $soVertical,  
                           .Width - old, .Height-old )*/
         if *.Comps > 1 && .Comps[1]->vCtrl.Visible 
         {
            .pDistance = ?( .pOrientation == $soVertical,
                  .Width  /*- .Comps[1]->vCtrl.Width*/, 
                  .Height /*- .Comps[1]->vCtrl.Height*/ ) - .pRightDistance - .pSplitterWidth
            /*.pDistance = ?( .pOrientation == $soVertical,
                  .Width  - .Comps[1]->vCtrl.Width, 
                  .Height - .Comps[1]->vCtrl.Height ) - .pSplitterWidth*/
         } 
      }
      case $sfpNone
      {
         .pDistance = uint(  .pProportion * double( ?( .pOrientation == $soVertical, evp.loc.width, evp.loc.height ) ) )
      }
   }
   .iUpdateSize()
}

/*����������� ����� vSplitter.mMouse
��������� �� �����
*/
method uint vSplitter.mMouse <alias=vSplitter_mMouse> ( evparMouse ev )
{ 
   if !.pAutoSize
   {
      switch ev.evmtype 
      {
         case $evmMove
         {
            if .fDrag
            {              
               .Distance = ?( .pOrientation == $soVertical, ev.x, ev.y )            
            }
         }
         case $evmLDown 
         {
            if !.fDrag
            {
               .fDrag = 1
               SetCapture( .hwnd )
            }
         }
         case $evmLUp
         {
            if .fDrag : ReleaseCapture()
         }      
      }
      
      if .pOrientation == $soVertical
      { 
         if ev.x > .pRealDistance && ev.x <= .pRealDistance + .pSplitterWidth
         {
            SetCursor( App.cursorSizeWE )
         }
      }
      else
      {
         if ev.y > .pRealDistance && ev.y <= .pRealDistance + .pSplitterWidth
         {
         
            SetCursor( App.cursorSizeNS )            
         }
      } 
   }
   return this->vCtrl.mMouse( ev )
}

/*����������� ����� vSplitter.mSetName 
��������� ��������� � ������ ��������������
*/
ifdef $DESIGNING {
method uint vSplitter.mSetName <alias=vSplitter_mSetName>( str newname )
{
   SetWindowText( this.hwnd, newname.ustr().ptr() )
   return 1   
}    
}

/*����������� ����� vSplitter.mChildPosChanged 
��������� �������� �������� ���������
*/
method vSplitter.mChildPosChanged <alias=vSplitter_mChildPosChanged>( vComp curcomp )
{
   if !.fUpdatingSize
   {      
      if ( .pAutoSize || .p_designing ) 
      {    
         switch .pFixedPart
         {
            case $sfpLeft 
            {
               if *.Comps > 0 && &curcomp==.Comps[0]
               {                              
                  .pDistance = ?( .pOrientation == $soVertical, 
                              .Comps[0]->vCtrl.Width, .Comps[0]->vCtrl.Height )                                            
               }
               .iUpdateSize()     
            }
            case $sfpRight
            {
               if *.Comps > 1 && &curcomp==.Comps[1]
               {
                  if .Comps[1]->vCtrl.Visible
                  {              
ifdef $DESIGNING {                     
                     .pDistance = ?( .pOrientation == $soVertical, 
                     .Comps[1]->vCtrl.Left,
                     .Comps[1]->vCtrl.Top ) - .pSplitterWidth
}
else
{                        
                     .pDistance = ?( .pOrientation == $soVertical, 
                     .Width - .Comps[1]->vCtrl.Width,
                     .Height - .Comps[1]->vCtrl.Height ) - .pSplitterWidth
}                     
                  }    
               } 
               .iUpdateSize()   
            }         
         }      
      }
      else
      {
         .iUpdateSize() 
      }
   }
   //this->vCtrl.mChildPosChanged( evp ) 
}
   
/*------------------------------------------------------------------------------
   Windows messages 
*/
/*����� ��������� ��������� uint vSplitter.wmcapturechange
��������� � ������� � ������������ �����
*/
method uint vSplitter.wmcapturechange 
   <alias=vSplitter_wmcapturechanged>( winmsg wmsg )
{   
   if wmsg.lpar != .hwnd && .fDrag 
   {        
      .fDrag = 0      
   } 
   return 0
}

/*------------------------------------------------------------------------------
   Registration
*/
/*��������� ����� vSplitter vSplitter.init
������������� �������
*/   
method vSplitter vSplitter.init( )
{  
   this.pTypeId     = vSplitter
   this.pCanContain = 1      
   this.loc.width   = 200
   this.loc.height  = 100   
   this.pDistance   = 50
   this.pSplitterWidth = 5
   this.flgXPStyle = 1
   return this 
}  

//������� �����������
func init_vSplitter <entry>()
{  
   regcomp( vSplitter, "vSplitter", vCtrl, $vCtrl_last, 
      %{ %{$mCreateWin,  vSplitter_mCreateWin},         
         %{$mInsert,     vSplitter_mInsert},
         %{$mPosChanging,vSplitter_mPosChanging},
         %{$mMouse,      vSplitter_mMouse},
         %{$mChildPosChanged, vSplitter_mChildPosChanged}
ifdef $DESIGNING {,
         %{$mSetName,    vSplitter_mSetName}
}         
      },      
      //0->collection ) 
      %{ %{$WM_CAPTURECHANGED, vSplitter_wmcapturechanged }
      })      
            
ifdef $DESIGNING {
   cm.AddComp( vSplitter, 1, "Windows", "splitter" )
   
   cm.AddProps( vSplitter, %{ 
"Distance",      uint, $PROP_LOADAFTERCHILD,
"SplitterWidth", uint, 0,
"Orientation",   uint, 0,
"FixedPart",     uint, 0,
"LeftMinSize",   uint, 0,
"RightMinSize",  uint, 0,
"AutoSize",      uint, 0
   })
   
   cm.AddPropVals( vSplitter, "Orientation", %{ 
"soVertical",     $soVertical,
"soHorizontal",   $soHorizontal
   })
   
   cm.AddPropVals( vSplitter, "FixedPart", %{
"sfpLeft",  $sfpLeft,    
"sfpRight", $sfpRight,
"sfpNone",  $sfpNone
   })
   
   cm.AddEvents( vSplitter, %{
"OnMoved"      , "evparEvent"
   }) 
}
      
}
