/******************************************************************************
*
* Copyright (C) 2006, The Gentee Group. All rights reserved. 
* This file is part of the Gentee open source project - http://www.gentee.com. 
* 
* THIS FILE IS PROVIDED UNDER THE TERMS OF THE GENTEE LICENSE ("AGREEMENT"). 
* ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE CONSTITUTES RECIPIENTS 
* ACCEPTANCE OF THE AGREEMENT.
*
* ID: bytecode 18.10.06 0.0.A.
*
* Author: Alexey Krivonogov ( gentee )
*
* Summary: The byte-code structures, defines and enums
* 
******************************************************************************/

/*-----------------------------------------------------------------------------
*
* ID: shifttype 19.10.06 0.0.A.
* 
* Summary: The shift type of the embedded commands. Hi - top shift Lo - cmd
  shift
*  
-----------------------------------------------------------------------------*/

enum
{      
//  SH_TYPE,  // type
          //  top  cmd
  SHN3_1 = 1, //   -3   1    
  SHN2_1, //   -2   1    
  SHN1_2, //   -1   2
  SHN1_1, //   -1   1    
  SH0_2,  //   0    2
  SH0_1,  //   0    1    
  SH1_3,  //   1    3
  SH1_2,  //   1    2
  SH1_1,  //   1    1
  SH2_1,  //   2    1
  SH2_3,  //   2    3
};

/*enum
{
 
   SMulII,
   SDivII,
   SModII,
   SLeftII,
   SRightII,
   SSignI,
   SLessII,
   SGreaterII,

   SMulI,           // *=
   SDivI,           // /=
   SModI,           // %=
   SLeftI,          // <<=
   SRightI,         // >>=

   SAddULUL,          
   SSubULUL,
   SMulULUL,
   SDivULUL,
   SModULUL,
   SAndULUL,
   SOrULUL,
   SXorULUL,
   SLeftULUL,
   SRightULUL,
   SLessULUL,
   SGreaterULUL,
   SEqULUL,
   SNotUL,

   SIncLeftUL,      // ++
   SIncRightUL,     // ������ ++
   SDecLeftUL,      // --
   SDecRightUL,     // ������ --
   SAddUL,          // +=
   SSubUL,          // -=
   SMulUL,          // *=
   SDivUL,          // /=
   SModUL,          // %=
   SAndUL,          // &=
   SOrUL,           // |=
   SXorUL,          // ^=
   SLeftUL,         // <<=
   SRightUL,        // >>=

   SMulLL,
   SDivLL,
   SModLL,
   SLeftLL,
   SRightLL,
   SSignL,
   SLessLL,
   SGreaterLL,

   SMulL,           // *=
   SDivL,           // /=
   SModL,           // %=
   SLeftL,          // <<=
   SRightL,         // >>=

   SAddFF,
   SSubFF,
   SMulFF,
   SDivFF,
   SSignF,
   SLessFF,
   SGreaterFF,
   SEqFF,
   
   SIncLeftF,      // ++
   SIncRightF,     // ������ ++
   SDecLeftF,      // --
   SDecRightF,     // ������ --
   SAddF,
   SSubF,
   SMulF,
   SDivF,
   
   SAddDD,
   SSubDD,
   SMulDD,
   SDivDD,
   SSignD,
   SLessDD,
   SGreaterDD,
   SEqDD,
   
   SIncLeftD,      // ++
   SIncRightD,     // ������ ++
   SDecLeftD,      // --
   SDecRightD,     // ������ --
   SAddD,
   SSubD,
   SMulD,
   SDivD,

   SIncLeftB,      // ++
   SIncRightB,     // ������ ++
   SDecLeftB,      // --
   SDecRightB,     // ������ --
   SAddB,          // +=
   SSubB,          // -=
   SMulB,          // *=
   SDivB,          // /=
   SModB,          // %=
   SAndB,          // &=
   SOrB,           // |=
   SXorB,          // ^=
   SLeftB,         // <<=
   SRightB,        // >>=

   SMulBS,         // *=
   SDivBS,         // /=
   SModBS,         // %=
   SLeftBS,        // <<=
   SRightBS,       // >>=

   SIncLeftUS,      // ++
   SIncRightUS,     // ������ ++
   SDecLeftUS,      // --
   SDecRightUS,     // ������ --
   SAddUS,          // +=
   SSubUS,          // -=
   SMulUS,          // *=
   SDivUS,          // /=
   SModUS,          // %=
   SAndUS,          // &=
   SOrUS,           // |=
   SXorUS,          // ^=
   SLeftUS,         // <<=
   SRightUS,        // >>=

   SMulS,           // *=
   SDivS,           // /=
   SModS,           // %=
   SLeftS,          // <<=
   SRightS,         // >>=

   // ������� �����������
   Sd2f,
   Sd2i,
   Sd2l,
   Sf2d,
   Sf2i,
   Sf2l,
   Si2d,
   Si2f,
   Si2l,
   Sl2d, 
   Sl2f,
   Sl2i,
   Sui2d,
   Sui2f,
   Sui2l,
//   Sul2d,
//   Sul2f,
//   Sul2i,

   SSizeof,      // ������ ����
   SArgsCount,   // ���������� ���������� ����������
   SArgsGet,     // �������� i-� ��������
   SGetText,     // �������� ������� �����
   SGetID,       // ��������� ID �� �����
   SGetIDCall,   // ��������� ID �� ����� � ����������
   SGetVM,       // �������� ������������� ����������� ������

   SNop,         //  ����� - ������ �������
   SVarsInit,    // �������������� ����� ���������� cmd 1 - ����� �����
   SSubCall,     // ����� ��������� �������. cmd 1 - ���������� ��� goto.
   SSubRet,      // ���������� ���������� ������������ dword  cmd 1
   SSubPar,      // ���������� ��������� � ����������. cmd 1 - ����� ����� 
                 // ����������-���������� ��� ������ ����������.
                 // cmd 2 - ���������� ���������� dword
   SSubReturn,   // ����� �� ����������
   SPtrGlobal,   // �������� ��������� �� ���������� ���������� cmd 1 - ������������ ����������
   SCmdLoad,     // ������������ ��������� � ����. ��� �������� �������������� � SDwLoad 
   SCmdCall,     // ����� ������� �� ���� �� ����� cmd 1 - ���������� dword ���������� �����������.
                 // ��� ������ ��������� ����� ����
//   SSizeof,      // ������ ����
//   SArgsCount,   // ���������� ���������� ����������
//   SArgsGet,     // �������� i-� ��������
//   SGetVM,       // �������� ������������� ����������� ������
   STypeInit,    // ���������������� ���������� ��������� � id ���� 
   STypeMustInit,// ������ ��� ����� ������� ������������� ��� ��������������� 0 init /1 deinit + id ����
   STypeMustDel, // ������ ��� ����� ������� ������������� ��� ��������������� 0 init /1 deinit + id ����
   STypeDelete,  // ���������� ���������� ��������� � id ���� 
//   SGetText,     // �������� ������� �����
   SSetTextPtr,  // ����� ������ �� SPtrDataSize 
   SSetTextClear,// ����� ������ �� str � �������� str
   SSetText,     // ����� ������ �� str 
   SCollectAdd,  // �������� �������� � ��������� cmd - 1 - dword ���������� dwords � ����� �� �������� 
                 // ����������� ���������
                 // � ����� val1 ... vali + < ���������� dwords ��� val( byte ) + type of val (3 ����) > 
   SException,   // �������� ������� ��������� ����������
   SThrow,       // ��������� ����������
   SCallFunc,
   SCallStd,
   SReturn,      //  ����� �� �������

   // ������� ����
   SByteSign,    // �� ������ ��������� �����!
   SByte,
   SShort,
   SUShort,
   SInt,
   SUInt,
   SFloat,        
   SLong,         // 64-��������� ����
   SULong,
   SDouble,
   SBuf,
   SStr,
   SCollection,   // ��� ���������
   SReserved,     // ��� ��� �������������� �����
//   SCollection,   // ��� ���������
   SLast,

   SPtrStr = 253,    // ������ ���� ������ � ������
}
*/