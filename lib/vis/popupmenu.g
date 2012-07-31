/******************************************************************************
*
* Copyright (C) 2004-2007, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: vis.popupmenu 19.07.07 0.0.A.
*
* Author: Alexander Krivonogov ( gentee )
*
******************************************************************************/

include {
   "menu.g"
}


/* ���������� vPopupMenu, ��������� �� vCustomMenu, ����� ��������� vMenuItem   
*/
type vPopupMenu <inherit = vCustomMainMenu> {
   uint    pComp
   evQuery OnBeforeShow
   evEvent OnAfterShow     
}

/*------------------------------------------------------------------------------
   Public methods
*/

/* �������� uint PopupComp - Get
*/
property vComp vPopupMenu.PopupComp()
{
   return this.pComp->vComp
}

/*����� vPopupMenu.Show( int x, y )
������� ���������� ����
x, y - ���������� ������ ��� ������� ����������� ����
*/
method vPopupMenu.Show( vComp comp, int x, int y )
{  
   evparQuery eq
   //eq.val = &ctrl
   .pComp = &comp 
   .OnBeforeShow.Run( eq, this )
   if !eq.flgCancel
   {
       TrackPopupMenuEx( .phMenu, $TPM_LEFTALIGN | $TPM_TOPALIGN , x, y, 
         .Owner->vForm.hwnd, 0 )
      evparEvent evn
      .OnAfterShow.Run( evn, this )
   }
}

/*����� vPopupMenu.Show( )
������� ���������� ����, ���� ��������� ����� � �������� ����
*/
method vPopupMenu.Show( vComp comp )
{     
   POINT p
   GetCursorPos( p )
   .Show( comp, p.x, p.y )
}

/*------------------------------------------------------------------------------
   Virtual methods
*/

method vPopupMenu.mSetOwner <alias = vPopupMenu_mSetOwner> ( vComp owner )
{     
   if owner && owner.TypeIs( vForm )
   { 
      this.pOwner = &owner    
   }    
}

/*------------------------------------------------------------------------------
   Registration
*/
method vPopupMenu vPopupMenu.init( )
{
   this.pTypeId = vPopupMenu   
   this.phMenu = CreatePopupMenu()    
   return this 
}  

func init_vPopupMenu <entry>()
{   
   regcomp( vPopupMenu, "vPopupMenu", vCustomMenu, $vComp_last,
      %{ %{$mSetOwner,     vPopupMenu_mSetOwner }
      },
      0->collection )          
      
ifdef $DESIGNING {
   cm.AddComp( vPopupMenu, 1, "Windows", "popupmenu" )
  
   cm.AddEvents( vPopupMenu, %{
"OnBeforeShow", "evparQuery",
"OnAfterShow", "evparEvent"
   })   
}                                                      
}

