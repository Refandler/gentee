/******************************************************************************
*
* Copyright (C) 2004-2007, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: vis.menuitem 18.07.07 0.0.A.
*
* Author: Alexander Krivonogov ( gentee )
*
******************************************************************************/
/* ���������� vMenuItem, ��������� �� vComp
�������
   OnClick - ���������� ��� ������� �� ����� ����  
*/

type vMenuItem <inherit=vCustomMenu>
{  
//Hidden fields
   uint     pEnabled     //����������� �������� ����
   uint     pSeparator   //������� ���� - �����������
   locustr  pCaption     //���������
   uint     pChecked     //������
   uint     pRadioCheck  //� ���� ������
   uint     pVisible     //�������
   uint     pAutoCheck   //�������������� �����
   shortkey pShortKey    //���������� ������
   ustr     pImage       //��� ������
   uint     ptrImage     //������ ���� ����
   uint     pEllipsis    //���������� ��������� 
//Public fields          
   
//Events
   evEvent OnClick
}

/* ���������� vFakeMenuItem, ��������� �� vComp
��������� ����� ����, ����� ��� ����������� ������  
*/
type vFakeMenuItem <inherit=vComp>
{
   uint pMenu//��������� �� vCustomMenu ���������� ������ ����
}


extern {   
   method vCustomMainMenu.FreeShortKey( vMenuItem item )
   method vCustomMainMenu.SetShortKey( vMenuItem item )
}
//Virtual Method Identifiers
/*define {
   mMenuClick     = $vComp_last
   vMenuItem_last
}*/

/*------------------------------------------------------------------------------
   Internal Methods
*/
/*����� vMenuItem.iUpdate()
�������� ���������� ������������� ����
*/
method vMenuItem.iUpdate()
{
   ustr caption
   MENUITEMINFO mi
   mi.cbSize = sizeof( MENUITEMINFO )
   mi.fMask = $MIIM_TYPE | $MIIM_STATE | $MIIM_DATA | $MIIM_CHECKMARKS | $MIIM_SUBMENU
   mi.fType = ?( .pSeparator, $MFT_SEPARATOR, $MFT_STRING ) | ?( .pRadioCheck, $MFT_RADIOCHECK, 0 )      
   mi.fState = ?( .pEnabled, $MFS_ENABLED, $MFS_GRAYED ) | ? ( .pChecked, $MFS_CHECKED, $MFS_UNCHECKED )
   mi.hSubMenu = .phMenu  

   caption = this.pCaption.Text( this ) 
   if .pEllipsis : caption += "..."  
   if *this.pShortKey.caption : caption += "\t".ustr() + this.pShortKey.caption      
   mi.dwTypeData = caption.ptr()
   SetMenuItemInfo( .Owner->vCustomMenu.phMenu, &this, 0, mi )
   if /*&.Owner.Owner &&*/ .Owner.Owner.TypeIs( vForm )
   {
      DrawMenuBar( .Owner.Owner->vForm.hwnd )
   }
}

/*------------------------------------------------------------------------------
   Properties
*/

/* �������� uint AutoCheck - Get Set
1 - ����� ���� ������������� ���������� ������� ��� ������� 
*/
property vMenuItem.AutoCheck( uint val )
{
   .pAutoCheck = val
   .iUpdate()
}

property uint vMenuItem.AutoCheck
{
   return .pAutoCheck
}

/* �������� ustr Caption - Get Set
������������� ��� �������� ��������� ������ ����
*/
property vMenuItem.Caption( ustr val )
{
   .pCaption.Value = val
   .iUpdate()    
}

property ustr vMenuItem.Caption <result>
{
   result = this.pCaption.Value
}

/* �������� ustr Enabled - Get Set
0 - ����� ���� �� ��������, ������������ ����� ������
1 - ����� ���� ��������
*/
property vMenuItem.Enabled( uint val )
{
   if .pEnabled != val
   {
      .pEnabled = val
      .iUpdate()
   }
}

property uint vMenuItem.Enabled
{
   return .pEnabled
}

/* �������� ustr Separator - Get Set
0 - ����� ���� ����� ������� ���
1 - ����� ���� ������������ ����� �����������
*/
property vMenuItem.Separator( uint val )
{
   .pSeparator = val
   .iUpdate()
}

property uint vMenuItem.Separator
{
   return .pSeparator
}

/* �������� ustr RadioCheck - Get Set
1 - ����� �� ������ ���� ������������ ������-�����, ���� ����� ������ (checked)  
*/
property vMenuItem.RadioCheck( uint val )
{
   .pRadioCheck = val
   .iUpdate()
}

property uint vMenuItem.RadioCheck
{
   return .pRadioCheck
}

/* �������� uint Visible - Get Set
0 - ����� ���� �� �����
1 - ����� ���� �����
*/
property uint vMenuItem.Visible
{   
   return .pVisible
}

property vMenuItem.Visible( uint val )
{
   if .pVisible != val
   {
      uint i, pos
      fornum i = 0, (this.CompIndex + 0)
      {
         if .Owner.Comps[i]->vMenuItem.Visible 
         {
            pos++
         }
      }
      .pVisible = val
      if .pVisible
      {
         MENUITEMINFO mi         
         /*uint i, pos         
         fornum i = 0, (this.CompIndex + 0)
         {
            if .Owner.Comps[i]->vMenuItem.Visible 
            {
               pos++
            }
         }*/         
         mi.cbSize = sizeof( MENUITEMINFO )
         mi.fMask = $MIIM_ID | $MIIM_DATA        
         mi.wID = &this
         mi.dwItemData = pos  
         InsertMenuItem( .Owner->vCustomMenu.phMenu, pos * ?(.Owner.TypeIs( vMenu ),1, 2), 1, mi  )
         if !.Owner.TypeIs( vMenu )
         {
         mi.cbSize = sizeof( MENUITEMINFO )
         mi.fMask = $MIIM_ID | $MIIM_TYPE | $MIIM_DATA 
         mi.fType = $MFT_SEPARATOR | $MFT_OWNERDRAW   
         mi.dwItemData = pos     
         mi.wID = .Owner->vCustomMenu.pFake
         InsertMenuItem( .Owner->vCustomMenu.phMenu, pos * 2 + 1, 1, mi  )
         }         
         .iUpdate()
      }
      else
      {      
         RemoveMenu( .Owner->vCustomMenu.phMenu, &this, 0 )
         if !.Owner.TypeIs( vMenu )
         {
            RemoveMenu( .Owner->vCustomMenu.phMenu, pos * 2, 0x400 )
         }
         .iUpdate()     
      }
   }
}

/* �������� ustr Index - Get Set
��������� �������� ��� �������� ���������� ����� ������ ����, ���������� �����
��������� ����� � ��������� ��������
*/
property vMenuItem.Index( uint val )
{
   uint curvisible = .Visible
   .Visible = 0
   this.CompIndex = val
   .Visible = curvisible
}

property uint vMenuItem.Index()
{
   return this.CompIndex   
}

/* �������� ustr Checked - Get Set
0 - ����� ���� �� ������
1 - ����� ���� ������, ����� �� ��������� ������ ���� ������������ ������ � ���� 
�������, ���� ����������� �������� RadioCheck, �� ������ � ���� �����.
���� ����������� �������� AutoCheck, �� �������� Checked ����� ��������������� 
��� ��������� ��� ������ ������� �� ����� ����. ���� ����������� �������� 
RadioCheck � ������ ����������� �������, �� Checked ��������������� ������ � 
���� ������ �� ������, � � ��������� ������ ��� ������������� ���������  
*/
property vMenuItem.Checked( uint val )
{   
   if .pChecked != val 
   {      
      .pChecked = val
      if val && .RadioCheck 
      {   
         uint i
         for i = .Index - 1, int(i) >= 0, i--
         {
            if .Owner.Comps[i]->vMenuItem.RadioCheck
            {               
               .Owner.Comps[i]->vMenuItem.Checked = 0
            }
            else : break 
         }   
         fornum i = .Index + 1, *(.Owner.Comps)
         {
            if .Owner.Comps[i]->vMenuItem.RadioCheck
            {
               .Owner.Comps[i]->vMenuItem.Checked = 0
            }
            else : break
         }  
      }
      .iUpdate()
   }
}

property uint vMenuItem.Checked
{   
   return .pChecked
}

/* �������� ustr ShortKey - Get Set
������� �������  
*/
property vMenuItem.ShortKey( ustr val )
{   
   if .pShortKey.caption != val
   {        
      uint mainmenu as .iMainMenu()
      mainmenu.FreeShortKey( this )
      .pShortKey.caption = val.str()
      .iUpdate()
      mainmenu.SetShortKey( this )      
   }
}

property ustr vMenuItem.ShortKey<result>
{   
   result = .pShortKey.caption
}

/* �������� ustr Image - Get Set
��� ������ 
*/
property ustr vMenuItem.Image <result>
{
   result = this.pImage
}

property vMenuItem.Image( ustr val )
{
   if val != this.pImage
   { 
      this.pImage = val
      .ptrImage = &this.GetImage( .pImage )
      .iUpdate()
   }
}

/* �������� ustr Image - Get Set
���������� ���������
0 - �� ���������� 
1 - ����������
*/
property uint vMenuItem.Ellipsis
{
   return this.pEllipsis
}

property vMenuItem.Ellipsis( uint val )
{
   if val != this.pEllipsis
   { 
      this.pEllipsis = val            
      .iUpdate()
   }
}

/*------------------------------------------------------------------------------
   Virtual methods
*/

method vMenuItem.mMenuClick <alias=vMenuItem_mMenuClick>( )
{
   if .AutoCheck
   {  
      if .RadioCheck
      {
         if !.Checked : .Checked = 1
      }
      else : .Checked = !.Checked       
   }
   this.OnClick.Run( this )
}

method vMenuItem.mInsert <alias=vMenuItem_mInsert>( vComp comp )
{
   
   if !this.phMenu 
   {
      this.phMenu = CreatePopupMenu()
   }
   this->vCustomMenu.mInsert( comp )         
   .iUpdate()
}

method uint vMenuItem.mLangChanged <alias=vMenuItem_mLangChanged>()
{
   .iUpdate()
   this->vComp.mLangChanged()
   return 0  
}

method vFakeMenuItem.mWinMeasureItem <alias=vFakeMenuItem_mWinMeasureItem>(MEASUREITEMSTRUCT ms)
{   
    ms.itemWidth = 0
    ms.itemHeight = 0 
}

method vFakeMenuItem.mWinDrawItem <alias=vFakeMenuItem_mWinDrawItem>(DRAWITEMSTRUCT ds)
{
   uint menu as .pMenu->vCustomMenu
   uint i, pos
   uint hwnd = FindWindowEx( 0, 0,32768, 0 )//������� ���� ������������ ����
   
   fornum i = 0, *menu.Comps
   {
      if menu.Comps[i]->vComp.TypeIs( vMenuItem ) 
      {
         uint menuitem as menu.Comps[i]->vMenuItem
         if menuitem.Visible 
         {
            if pos == ds.itemData
            {
               if menuitem.ptrImage
               {            
                  POINT p
                  RECT  r
                  uint  off //����� ��� �������������
                  SetBkMode( ds.hDC, $TRANSPARENT )
                  GetMenuItemRect( hwnd, menu.phMenu, pos * 2, r )
                               
                  off = ( r.bottom - r.top - menuitem.ptrImage->Image.Height)/2
                  p.x = r.left + off 
                  p.y = r.top + off                  
                  ScreenToClient( hwnd, p )
                  
                  DrawIconEx( ds.hDC, p.x, p.y, ?( menuitem.Enabled, menuitem.ptrImage->Image.hImage, menuitem.ptrImage->Image.hDisImage ), menuitem.ptrImage->Image.Width, menuitem.ptrImage->Image.Height, 0, 0,  $DI_NORMAL | $DI_MASK)                             
               }
               break
            }
            pos++            
         }
      }
   }
   return
/*   uint menu as .pMenu->vCustomMenu
   uint i         
   uint visi
   uint hwnd = FindWindowEx( 0, 0,32768, 0 )//������� ���� ������������ ����
   SetBkMode( ds.hDC, $TRANSPARENT )
   
   fornum i = 0, *menu.Comps
   {
      if menu.Comps[i]->vComp.TypeIs( vMenuItem ) 
      {
         uint menuitem as menu.Comps[i]->vMenuItem
         if menuitem.Visible 
         {
            if menuitem.ptrImage
            {            
               POINT p
               RECT  r
               uint  off //����� ��� �������������
               
               GetMenuItemRect( hwnd, menu.phMenu, visi, r )
                            
               off = ( r.bottom - r.top - menuitem.ptrImage->Image.Height)/2
               p.x = r.left + off - 1 
               p.y = r.top + off
               
               ScreenToClient( hwnd, p )
               DrawIconEx( ds.hDC, p.x, p.y, ?( menuitem.Enabled, menuitem.ptrImage->Image.hImage, menuitem.ptrImage->Image.hDisImage ), menuitem.ptrImage->Image.Width, menuitem.ptrImage->Image.Height, 0, 0,  $DI_NORMAL | $DI_MASK)                             
            }
            visi++   
            visi++         
         }
      } 
   }   
   return*/  
}

/*------------------------------------------------------------------------------
   Registration
*/
method vMenuItem vMenuItem.init( )
{   
   this.pTypeId = vMenuItem
   this.pEnabled = 1
   this.pVisible = 1   
   return this 
}  

method vFakeMenuItem vFakeMenuItem.init( )
{   
   this.pTypeId = vFakeMenuItem  
   return this 
}





