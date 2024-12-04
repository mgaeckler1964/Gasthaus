//---------------------------------------------------------------------------
#include <stdlib.h>

#include <vcl.h>

#include <gak/string.h>

#pragma hdrstop

#include "Config.h"
#include "ConfFrm.h"
#include "MainFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define company "Gäckler Software"
#define app "Gasthaus Reservierung"

TConfigForm *ConfigForm;

using namespace gak;

static AnsiString readRegistration( const char *var, bool publicVal = FALSE )
{
	long		openResult;
	HKEY		softKey;
	HKEY		companyKey;
	HKEY		appKey;

	DWORD		typeVar;
	char		valueBuff[1024];
	DWORD		valueSize;
	bool		valueFound = FALSE;
	AnsiString	result = "";

	valueSize = sizeof( valueBuff ) -1;

	openResult = RegOpenKeyEx(	publicVal	? HKEY_LOCAL_MACHINE
											: HKEY_CURRENT_USER,
								"SOFTWARE", 0,
								KEY_READ, &softKey );
	if( openResult == ERROR_SUCCESS )
	{
		openResult = RegOpenKeyEx(	softKey,
									company, 0,
									KEY_READ,
									&companyKey );
		if( openResult == ERROR_SUCCESS )
		{
			openResult = RegOpenKeyEx(	companyKey,
										app, 0,
										KEY_READ,
										&appKey );
			if( openResult == ERROR_SUCCESS )
			{
				openResult = RegQueryValueEx( appKey, (char *)var, NULL,
											&typeVar, (LPBYTE)valueBuff, &valueSize );
				if( openResult == ERROR_SUCCESS
				&&  valueSize > 0
				&&  typeVar == REG_SZ )
					valueFound = TRUE;

				RegCloseKey( appKey );
			}

			RegCloseKey( companyKey );
		}
		RegCloseKey( softKey );
	}

	if( valueFound )
		result = valueBuff;
	else if( !publicVal )
		result = readRegistration( var, TRUE );

	return result;
}

static void writeRegistration( bool publicVal, const char *var, const char *value )
{
	DWORD			dummy;
	long			openResult;
	HKEY			softKey;
	HKEY			companyKey;
	HKEY			appKey;

	DWORD			valueSize;

	valueSize = strlen( value ) +1;

	openResult = RegOpenKeyEx(	publicVal	? HKEY_LOCAL_MACHINE
											: HKEY_CURRENT_USER,
								"SOFTWARE", 0,
								KEY_CREATE_SUB_KEY, &softKey );
	if( openResult == ERROR_SUCCESS )
	{
		openResult = RegCreateKeyEx(	softKey, company, 0, "",
										REG_OPTION_NON_VOLATILE,
										KEY_ALL_ACCESS,
										NULL,
										&companyKey,
										&dummy );
		if( openResult == ERROR_SUCCESS )
		{
			openResult = RegCreateKeyEx(	companyKey, app, 0, "",
											REG_OPTION_NON_VOLATILE,
											KEY_ALL_ACCESS,
											NULL,
											&appKey,
											&dummy );
			if( openResult == ERROR_SUCCESS )
			{
				RegSetValueEx( appKey, (char *)var, 0,
								REG_SZ, (LPBYTE)value, valueSize );

				RegCloseKey( appKey );
			}

			RegCloseKey( companyKey );
		}
		RegCloseKey( softKey );
	}
}

//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonBrowseListLogoClick(TObject *)
{
	OpenPictureDlg->FileName = ListLogoEdit->Text;
	if( OpenPictureDlg->Execute() )
	{
		ListLogoEdit->Text = OpenPictureDlg->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::FormCreate(TObject *)
{
	AnsiString	value;

	value = readRegistration( "ListLogo" );
	ListLogoEdit->Text = value;

	value = readRegistration( "CardLogo" );
	CardLogoEdit->Text = value;

	value = readRegistration( "DoubledEntries" );
	if( value.Length() )
		doubleEdit->Color = (TColor)atol( value.c_str() );
	else
		doubleEdit->Color = clGreen;

	value = readRegistration( "CompleteEntries" );
	if( value.Length() )
		completeEdit->Color = (TColor)atol( value.c_str() );
	else
		completeEdit->Color = clRed;

	value = readRegistration( "ConferenceEntries" );
	if( value.Length() )
		ConferenceEdit->Color = (TColor)atol( value.c_str() );
	else
		ConferenceEdit->Color = clLime;

	value = readRegistration( "OptionalEntries" );
	if( value.Length() )
		optionEdit->Color = (TColor)atol( value.c_str() );
	else
		optionEdit->Color = clSilver;

	value = readRegistration( "UnfinishedEntries" );
	if( value.Length() )
		notOkEdit->Color = (TColor)atol( value.c_str() );
	else
		notOkEdit->Color = clBlue;

	value = readRegistration( "DeletedEntries" );
	if( value.Length() )
		DeletedEdit->Color = (TColor)atol( value.c_str() );
	else
		DeletedEdit->Color = clFuchsia;

	value = readRegistration( "RepeatedEntries" );
	if( value.Length() )
		StammtischEdit->Text = value;
	else
		StammtischEdit->Text = "100";

	STRING reportPath = ConfigDataModule->GetValue(
		"reportPath", "reports\\"
	);
	EditReports->Text = (const char *)reportPath;
}

//---------------------------------------------------------------------------
void __fastcall TConfigForm::ButtonOKClick(TObject *)
{
	char	tmpBuff[32];

	writeRegistration( true, "ListLogo", ListLogoEdit->Text.c_str() );
	writeRegistration( true, "CardLogo", CardLogoEdit->Text.c_str() );
	writeRegistration( true, "DoubledEntries", ltoa( doubleEdit->Color, tmpBuff, 10 ) );
	writeRegistration( true, "CompleteEntries", ltoa( completeEdit->Color, tmpBuff, 10 ) );
	writeRegistration( true, "ConferenceEntries", ltoa( ConferenceEdit->Color, tmpBuff, 10 ) );
	writeRegistration( true, "OptionalEntries", ltoa( optionEdit->Color, tmpBuff, 10 ) );
	writeRegistration( true, "UnfinishedEntries", ltoa( notOkEdit->Color, tmpBuff, 10 ) );
	writeRegistration( true, "RepeatedEntries", StammtischEdit->Text.c_str() );
	writeRegistration( true, "DeletedEntries", DeletedEdit->Text.c_str() );

	STRING reportPath = EditReports->Text.c_str();
	if( !reportPath.isEmpty() && !reportPath.endsWith( DIRECTORY_DELIMITER ) )
		reportPath += DIRECTORY_DELIMITER;

	ConfigDataModule->SetValue( "reportPath", reportPath );
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonSelectDoubleClick(TObject *)
{
	ColorDialog->Color = doubleEdit->Color;
	if( ColorDialog->Execute() )
		doubleEdit->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonSelectCompleteClick(TObject *)
{
	ColorDialog->Color = completeEdit->Color;
	if( ColorDialog->Execute() )
		completeEdit->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonSelectNotOKClick(TObject *)
{
	ColorDialog->Color = notOkEdit->Color;
	if( ColorDialog->Execute() )
		notOkEdit->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonBrowseCardLogoClick(TObject *)
{
	OpenPictureDlg->FileName = CardLogoEdit->Text;
	if( OpenPictureDlg->Execute() )
	{
		CardLogoEdit->Text = OpenPictureDlg->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonSelectOptionClick(TObject *)
{
	ColorDialog->Color = optionEdit->Color;
	if( ColorDialog->Execute() )
		optionEdit->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonSelectConferenceClick(TObject *)
{
	ColorDialog->Color = ConferenceEdit->Color;
	if( ColorDialog->Execute() )
		ConferenceEdit->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ButtonSelectDeletedClick(TObject *)
{
	ColorDialog->Color = DeletedEdit->Color;
	if( ColorDialog->Execute() )
		DeletedEdit->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

