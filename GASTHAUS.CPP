//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("gasthaus.res");
USEFORM("MainFrm.cpp", MainForm);
USEFORM("EditFrm.cpp", EditForm);
USEFORM("RoomFrm.cpp", RoomForm);
USEFORM("TableFrm.cpp", TableForm);
USEFORM("SchedFrm.cpp", ScheduleFrm);
USEFORM("RepFrm.cpp", RepeatedForm);
USEFORM("GroupRep.cpp", GroupReport);
USEFORM("CardRep.cpp", CardReport);
USEFORM("SelCdFrm.cpp", SelCardForm);
USEFORM("AboutFrm.cpp", AboutBox);
USEFORM("ConfFrm.cpp", ConfigForm);
USEFORM("FreeFrm.cpp", FreeForm);
USEFORM("TableRep.cpp", TableReport);
USEFORM("ChartFrm.cpp", ChartForm);
USEUNIT("gr_utils.cpp");
USELIB("..\..\Object\gaklib\gaklib_bcb.lib");
USEFORM("SelectFrm.cpp", SelectForm);
USEFORM("DrawFrm.cpp", DrawingForm);
USEFORM("..\GAKLIB\Repository\Config.cpp", ConfigDataModule); /* TDataModule: File Type */
USEFORM("..\GAKLIB\Repository\LicFrm.cpp", LicenceForm);
USEFORM("GasthausDM.cpp", GasthausDataModule); /* TDataModule: File Type */
//---------------------------------------------------------------------------
char	dbAliasName[256];
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdLine, int)
{
	strcpy(dbAliasName, cmdLine);
	try
	{
		Application->Initialize();
		Application->Title = "Gasthausreservierung";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TEditForm), &EditForm);
		Application->CreateForm(__classid(TRoomForm), &RoomForm);
		Application->CreateForm(__classid(TTableForm), &TableForm);
		Application->CreateForm(__classid(TScheduleFrm), &ScheduleFrm);
		Application->CreateForm(__classid(TRepeatedForm), &RepeatedForm);
		Application->CreateForm(__classid(TGroupReport), &GroupReport);
		Application->CreateForm(__classid(TCardReport), &CardReport);
		Application->CreateForm(__classid(TSelCardForm), &SelCardForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TConfigForm), &ConfigForm);
		Application->CreateForm(__classid(TFreeForm), &FreeForm);
		Application->CreateForm(__classid(TTableReport), &TableReport);
		Application->CreateForm(__classid(TChartForm), &ChartForm);
		Application->CreateForm(__classid(TSelectForm), &SelectForm);
		Application->CreateForm(__classid(TDrawingForm), &DrawingForm);
		Application->CreateForm(__classid(TConfigDataModule), &ConfigDataModule);
		Application->CreateForm(__classid(TLicenceForm), &LicenceForm);
		Application->CreateForm(__classid(TGasthausDataModule), &GasthausDataModule);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
