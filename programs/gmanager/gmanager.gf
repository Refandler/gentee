/*	
 //!GFG � //!\GFG  are commentary attributes generated by 
 the Gentee form editor. You should neither delete them 
 nor make any changes into the source code from the beginning 
 of the commentary attribute //!GFG to its end //!\GFG
*/

//!GFG include
include {
	"app.g"
	"edit.g"
	"btn.g"
	"panel.g"
	"tab.g"
	"label.g"
//!\GFG

}

//!GFG form
type vForm0 <inherit=vForm> {
	vTab	Tab0
	vTabItem	TabItem0
	vBtn	Btn0
	vBtn	Btn1
	vBtn	Btn2
	vPanel	Panel0
	vBtn	Btn5
	vBtn	Btn3
	vBtn	Btn8
	vTabItem	TabItem1
	vLabel	Label0
	vEdit	vRegcur
	vEdit	vRegnew
	vBtn	Btn6
	vBtn	Btn7
	vBtn	Btn4
 //!\GFG

}

include : $"..\..\lib\registry\registry.g"

func runshell( str name )
{
   str fname
   
   getmodulepath( fname, "" )
   fname.fgetdir( fname )
   shell( fname.faddname( name ))
}

//!GFG method runide evparEvent
method uint vForm0.runide <alias=Form0_runide>( evparEvent evn )//!\GFG
{
   runshell( "exe\\GenteeIDE.exe" )
   return 0
}

//!GFG method runstudio evparEvent
method uint vForm0.runstudio <alias=Form0_runstudio>( evparEvent evn )//!\GFG
{
   runshell( "studio\\gstudio.exe" )
return 0
}

//!GFG method runvis evparEvent
method uint vForm0.runvis <alias=Form0_runvis>( evparEvent evn )//!\GFG
{
   runshell( "exe\\visedit.exe" )
return 0
}

//!GFG method openchm25 evparEvent
method uint vForm0.openchm25 <alias=Form0_openchm25>( evparEvent evn )//!\GFG
{
   runshell( "studio\\Gentee.chm" )
return 0
}

//!GFG method openchm3 evparEvent
method uint vForm0.openchm3 <alias=Form0_openchm3>( evparEvent evn )//!\GFG
{
   runshell( "exe\\Gentee.chm" )
return 0
}

//!GFG method exit evparEvent
method uint vForm0.exit <alias=Form0_exit>( evparEvent evn )//!\GFG
{
   .WinMsg( $WM_CLOSE )
return 0
}

//!GFG method changegline evparEvent
method uint vForm0.changegline <alias=Form0_changegline>( evparEvent evn )//!\GFG
{
   str  curg
   
   curg = str( .vRegnew.Text )
   curg.regset( $HKEY_CLASSES_ROOT, $"gfile\Shell\Open\command", "" )
   
   curg.regget( $HKEY_CLASSES_ROOT, $"gfile\Shell\Open\command", "" )
   .vRegcur.Text = ustr( curg )
   
   return 0
}

//!GFG method appinit evparEvent
method uint vForm0.appinit <alias=Form0_appinit>( evparEvent evn )//!\GFG
{
   str  curg
   curg.regget( $HKEY_CLASSES_ROOT, $"gfile\Shell\Open\command", "" )
   .vRegcur.Text = ustr( curg )
   .vRegnew.Text = ustr( curg )

return 0
}

//!GFG method setdefault evparEvent
method uint vForm0.setdefault <alias=Form0_setdefault>( evparEvent evn )//!\GFG
{
   str  curg  stemp
   
   getmodulepath( stemp, "gentee.exe")
   curg = "\"\(stemp)\" -p default \"%1\""
   curg.regset( $HKEY_CLASSES_ROOT, $"gfile\Shell\Open\command", "" )

   curg.regget( $HKEY_CLASSES_ROOT, $"gfile\Shell\Open\command", "" )
   .vRegcur.Text = ustr( curg )
return 0
}

//!GFG method runviewer evparEvent
method uint vForm0.runviewer <alias=Form0_runviewer>( evparEvent evn )//!\GFG
{
   runshell( "exe\\GeViewer.exe" )
return 0
}

//!GFG includeinit
include { $"K:\Gentee\Open Source\gentee\programs\gmanager\gmanager.gi" 
}//!\GFG
