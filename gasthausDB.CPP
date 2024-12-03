//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("gasthausDB.res");
USEFORM("..\GAKLIB\Repository\dbConvertFrm.cpp", DbConvertForm);
USEFORM("gasthausDbFrm.cpp", GasthausDbForm);
USELIB("..\..\Object\gaklib\gaklib_bcb.lib");
USEFORM("..\GAKLIB\Repository\Config.cpp", ConfigDataModule); /* TDataModule: File Type */
USEFORM("..\GAKLIB\Repository\LoginDlg.cpp", LoginForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "Gasthaus Reservierung DB Manager";
		Application->CreateForm(__classid(TGasthausDbForm), &GasthausDbForm);
		Application->CreateForm(__classid(TDbConvertForm), &DbConvertForm);
		Application->CreateForm(__classid(TConfigDataModule), &ConfigDataModule);
		Application->CreateForm(__classid(TLoginForm), &LoginForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------

