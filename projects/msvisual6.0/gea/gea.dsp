# Microsoft Developer Studio Project File - Name="gea" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gea - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gea.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gea.mak" CFG="gea - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gea - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gea - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gea - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEA_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gz /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEA_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib msvcrt.lib /nologo /dll /machine:I386 /nodefaultlib /out:"..\..\..\exe\gea.dll"

!ELSEIF  "$(CFG)" == "gea - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEA_EXPORTS" /YX /FD /GZ  /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GEA_EXPORTS" /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gea - Win32 Release"
# Name "gea - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\projects\gea\Huffman\dehuffman.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\LZGE\delzge.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\deppmd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\Huffman\enhuffman.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\LZGE\enlzge.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\enppmd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\gea.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\gea.def
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\Huffman\huffman.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\LZGE\lzge.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\LZGE\match.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\memory.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\memory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\ppmd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\PPMdCmn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\PPMdDec.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\PPMdEnc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\endeppmd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\gea.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\Huffman\huffman.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\LZGE\lzge.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\LZGE\match.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\PPMd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\projects\gea\PPMD\PPMdCmn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project