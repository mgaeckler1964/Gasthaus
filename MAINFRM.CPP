//---------------------------------------------------------------------------
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <vcl.h>

#include <gak/date.h>
#include <gak/vcl_tools.h>

#pragma hdrstop

#include "MainFrm.h"
#include "RoomFrm.h"
#include "TableFrm.h"
#include "SchedFrm.h"
#include "EditFrm.h"
#include "RepFrm.h"
#include "TableRep.h"
#include "GroupRep.h"
#include "CardRep.h"
#include "SelCdFrm.h"
#include "AboutFrm.h"
#include "ConfFrm.h"
#include "FreeFrm.h"
#include "ChartFrm.h"
#include "gr_utils.h"
#include "DrawFrm.h"
#include "Config.h"
#include "LicFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

#define LICENCE_CODE		59834981L

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	lastDate = 0;
	tableFilter = 0;
}
//---------------------------------------------------------------------------
void TMainForm::checkEvents( bool ignoreLastDate )
{
	TDateTime		currentDate;
	unsigned short	year, month, day;
	AnsiString		termine = "";

	if( reservatQuery->RecordCount > 0 )
		currentDate = reservatQueryDatum->AsDateTime;
	else
		currentDate = StartDatePicker->Date;

	if( ignoreLastDate || currentDate != lastDate )
	{
		lastDate = currentDate;
		currentDate.DecodeDate( &year, &month, &day );

		GAK_DATE	gakDate(day, (GAK_MONTH)month, year);
		termine = gakDate.holiday();
		if( termine > "" )
			termine += " ";

		ScheduleQuery->Params->Items[0]->AsInteger = day;
		ScheduleQuery->Params->Items[1]->AsInteger = month;
		ScheduleQuery->Params->Items[2]->AsDateTime = currentDate;
		ScheduleQuery->Params->Items[3]->AsDateTime = currentDate;

		if( !ScheduleQuery->Prepared )
			ScheduleQuery->Prepare();
		ScheduleQuery->Open();
		while( !ScheduleQuery->Eof )
		{
			termine += ScheduleQuery->Fields->Fields[0]->AsString + " ";
			ScheduleQuery->Next();
		}
		ScheduleQuery->Close();

		TerminLabel->Caption = termine;
	}
	if( reservatQueryLink->AsInteger > 0 )
		GotoCopy->Enabled = true;
	else
		GotoCopy->Enabled = false;
}

//---------------------------------------------------------------------------
void TMainForm::deleteReservation( int reservationId )
{
	TQuery	*delSQL;

	delSQL = new TQuery( Application );
	if( delSQL )
	{
		delSQL->DatabaseName = "GASTHAUS";
		delSQL->SQL->Add( "delete from reservat where" );
		if( reservationId )
		{
			delSQL->SQL->Add( "id = :theId" );
			delSQL->Params->Items[0]->AsInteger = reservationId;
		}
		else
		{
			delSQL->SQL->Add( "Datum < :theDate" );
			delSQL->Params->Items[0]->AsDateTime = TDateTime::CurrentDate()-30;
		}
		delSQL->ExecSQL();
		delete delSQL;
	}
	restartQuery(false);
}
//---------------------------------------------------------------------------
void TMainForm::gotoReservation( int reservationId )
{
	reservatQuery->DisableControls();
	reservatQuery->First();
	while( !reservatQuery->Eof && reservatQueryID->AsInteger != reservationId )
		reservatQuery->Next();
	reservatQuery->EnableControls();
}

//---------------------------------------------------------------------------
void TMainForm::fillRaeume( void )
{
	TQuery	*theQuery;

	RaeumeComboBox->Items->Clear();
	RaeumeComboBox->Items->Add( "Alle Räume" );

	theQuery = new TQuery( Application );
	if( theQuery )
	{
		theQuery->DatabaseName = "GASTHAUS";
		theQuery->UniDirectional = true;
		theQuery->RequestLive = false;
		theQuery->SQL->Add( "select distinct name from raum" );
		theQuery->Open();
		while( !theQuery->Eof )
		{
			//RaeumeComboBox->Items->Add( theQuery->Fields[0]->AsString );
			RaeumeComboBox->Items->Add( theQuery->Fields->Fields[0]->AsString );
			theQuery->Next();
		}
		theQuery->Close();

		delete theQuery;
	}
	RaeumeComboBox->ItemIndex = 0;
}

//---------------------------------------------------------------------------
void TMainForm::genSqlDates( void )
{
	unsigned short	day, month, year;

	switch( DateComboBox->ItemIndex )
	{
		case 0:		// Alles
			StartDatePicker->Visible = false;
			EndDatePicker->Visible = false;
			break;
		case 1:		// Heute
			startDate = TDateTime::CurrentDate();
			endDate = TDateTime::CurrentDate();

			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = false;
			StartDatePicker->Date = startDate;
			EndDatePicker->Visible = false;
			break;

		case 2:		// Morgen
			startDate = TDateTime::CurrentDate() + 1;
			endDate = TDateTime::CurrentDate() + 1;

			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = false;
			StartDatePicker->Date = startDate;
			EndDatePicker->Visible = false;
			break;

		case 3:		// Diese Woche
			startDate = TDateTime::CurrentDate();
			startDate -= startDate.DayOfWeek()-2;
			endDate = startDate + 6;

			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = false;
			StartDatePicker->Date = startDate;
			EndDatePicker->Visible = true;
			EndDatePicker->Enabled = false;
			EndDatePicker->Date = endDate;
			break;

		case 4:		// Nächste Woche
			startDate = TDateTime::CurrentDate();
			startDate += 7-startDate.DayOfWeek() +2;
			endDate = startDate + 6;

			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = false;
			StartDatePicker->Date = startDate;
			EndDatePicker->Visible = true;
			EndDatePicker->Enabled = false;
			EndDatePicker->Date = endDate;
			break;

		case 5:		// Dieser Monat
			startDate = TDateTime::CurrentDate();
			startDate.DecodeDate( &year, &month, &day );
			startDate = EncodeDate( year, month, 1 );
			month++;
			if( month > 12 )
			{
				month = 1;
				year++;
			}
			endDate = EncodeDate( year, month, 1 );
			endDate--;

			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = false;
			StartDatePicker->Date = startDate;
			EndDatePicker->Visible = true;
			EndDatePicker->Enabled = false;
			EndDatePicker->Date = endDate;
			break;

		case 6:		// Nächster Monat
			startDate = TDateTime::CurrentDate();
			startDate.DecodeDate( &year, &month, &day );
			month++;
			if( month > 12 )
			{
				month = 1;
				year++;
			}
			startDate = EncodeDate( year, month, 1 );
			month++;
			if( month > 12 )
			{
				month = 1;
				year++;
			}
			endDate = EncodeDate( year, month, 1 );
			endDate--;

			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = false;
			StartDatePicker->Date = startDate;
			EndDatePicker->Visible = true;
			EndDatePicker->Enabled = false;
			EndDatePicker->Date = endDate;
			break;

		case 7:		// Ein Tag
			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = true;

			startDate = StartDatePicker->Date;
			endDate = StartDatePicker->Date;

			EndDatePicker->Visible = false;
			break;

		case 8:		// Frei
			StartDatePicker->Visible = true;
			StartDatePicker->Enabled = true;

			EndDatePicker->Visible = true;
			EndDatePicker->Enabled = true;

			startDate = StartDatePicker->Date;
			endDate = EndDatePicker->Date;
			if( endDate < startDate )
			{
				endDate = startDate;
				EndDatePicker->Date = startDate;
			}
			break;

		default:
		   DateComboBox->ItemIndex = 0;
	}
	restartQuery();
}

//---------------------------------------------------------------------------
void TMainForm::genSqlCode( void )
{
	sumQuery->SQL->Clear();
	sumQuery->SQL->Add( "select sum( r.Personen ) personen" );
	sumQuery->SQL->Add( "from	reservat r, tisch t, raum z" );
	sumQuery->SQL->Add( "where	r.tisch = t.id and" );
	sumQuery->SQL->Add( "t.raum = z.id" );

	reservatQuery->SQL->Clear();
	reservatQuery->SQL->Add( "select  r.id, r.Datum," );
	reservatQuery->SQL->Add( "z.name Raum," );
	reservatQuery->SQL->Add( "t.Tisch," );
	reservatQuery->SQL->Add( "r.Uhrzeit," );
	reservatQuery->SQL->Add( "r.Name," );
	reservatQuery->SQL->Add( "r.Status," );
	reservatQuery->SQL->Add( "r.func_status," );
	reservatQuery->SQL->Add( "r.Anlass," );
	reservatQuery->SQL->Add( "r.ext_bemerk," );
	reservatQuery->SQL->Add( "r.int_bemerk," );
	reservatQuery->SQL->Add( "r.Personen," );
	reservatQuery->SQL->Add( "r.Telefon," );
	reservatQuery->SQL->Add( "r.Kompletter_Raum," );
	reservatQuery->SQL->Add( "r.Link" );
	reservatQuery->SQL->Add( "from	reservat r, tisch t, raum z" );
	reservatQuery->SQL->Add( "where	r.tisch = t.id and" );
	reservatQuery->SQL->Add( "t.raum = z.id" );

	if( DateComboBox->ItemIndex )
	{
		reservatQuery->SQL->Add( "and r.datum >= :startDate and r.datum <= :endDate" );
		sumQuery->SQL->Add( "and r.datum >= :startDate and r.datum <= :endDate" );
	}

	if( RaeumeComboBox->ItemIndex > 0 )
	{
		AnsiString	tmp = "and z.name = '";
		tmp += RaeumeComboBox->Items->Strings[RaeumeComboBox->ItemIndex];
		tmp += "'";
		reservatQuery->SQL->Add( tmp );
		sumQuery->SQL->Add( tmp );
	}

	switch( TimeComboBox->ItemIndex )
	{
		case 1:		// Mittags
			startTime = EncodeTime( 0, 0, 0, 0 );
			endTime = EncodeTime( 16, 0, 0, 0 );
			break;
		case 2:		// Abends
			startTime = EncodeTime( 16, 0, 0, 0 );
			endTime = EncodeTime( 23, 59, 59, 999 );
			break;
		case 3:		// - 12
			startTime = EncodeTime( 0, 0, 0, 0 );
			endTime = EncodeTime( 12, 0, 0, 0 );
			break;
		case 4:		// 12 - 14
			startTime = EncodeTime( 12, 0, 0, 0 );
			endTime = EncodeTime( 14, 0, 0, 0 );
			break;
		case 5:		// 14 - 16
			startTime = EncodeTime( 14, 0, 0, 0 );
			endTime = EncodeTime( 16, 0, 0, 0 );
			break;
		case 6:		// 16 - 18
			startTime = EncodeTime( 16, 0, 0, 0 );
			endTime = EncodeTime( 18, 0, 0, 0 );
			break;
		case 7:		// 18 - 20
			startTime = EncodeTime( 18, 0, 0, 0 );
			endTime = EncodeTime( 20, 0, 0, 0 );
			break;
		case 8:		// 20 -
			startTime = EncodeTime( 20, 0, 0, 0 );
			endTime = EncodeTime( 23, 59, 59, 999 );
			break;
		default:
			startTime = 0;
			endTime = 0;
			TimeComboBox->ItemIndex = 0;
			break;
	}
	if( TimeComboBox->ItemIndex )
	{
		reservatQuery->SQL->Add( "and (r.uhrzeit >= :theStartTime and r.uhrZeit < :theEndTime)" );
		sumQuery->SQL->Add( "and (r.uhrzeit >= :theStartTime and r.uhrZeit < :theEndTime)" );
	}

	if( tableFilter )
	{
		reservatQuery->SQL->Add( "and t.id = :theTable" );
		sumQuery->SQL->Add( "and t.id = :theTable" );
	}

	AnsiString	nameFilter = EditName->Text;
	if( nameFilter > "" )
	{
		reservatQuery->SQL->Add( "and r.name like '%' || :nameFilter || '%' " );
		sumQuery->SQL->Add( "and r.name like '%' || :nameFilter || '%' " );
	}

	if( SortComboBox->ItemIndex == 0 )
		reservatQuery->SQL->Add( "order by r.datum, z.name, t.tisch, r.uhrzeit" );
	else if( SortComboBox->ItemIndex == 1 )
		reservatQuery->SQL->Add( "order by r.name, r.datum, r.uhrzeit, z.name, t.tisch" );
	else if( SortComboBox->ItemIndex == 2 )
		reservatQuery->SQL->Add( "order by r.datum, r.uhrzeit, z.name, t.tisch" );

	if( DateComboBox->ItemIndex )
	{
		reservatQuery->ParamByName( "startDate" )->AsDate = startDate;
		reservatQuery->ParamByName( "endDate" )->AsDate = endDate;

		sumQuery->ParamByName( "startDate" )->AsDate = startDate;
		sumQuery->ParamByName( "endDate" )->AsDate = endDate;
	}

	if( TimeComboBox->ItemIndex )
	{
		reservatQuery->ParamByName( "theStartTime" )->AsDateTime = startTime;
		reservatQuery->ParamByName( "theEndTime" )->AsDateTime = endTime;

		sumQuery->ParamByName( "theStartTime" )->AsDateTime = startTime;
		sumQuery->ParamByName( "theEndTime" )->AsDateTime = endTime;
	}

	if( tableFilter )
	{
		reservatQuery->ParamByName( "theTable" )->AsInteger = tableFilter;
		sumQuery->ParamByName( "theTable" )->AsInteger = tableFilter;
	}
	if( nameFilter > "" )
	{
		reservatQuery->ParamByName( "nameFilter" )->AsString = nameFilter;
		sumQuery->ParamByName( "nameFilter" )->AsString = nameFilter;
	}
}

//---------------------------------------------------------------------------
void TMainForm::restartQuery( bool genSql )
{
	reservatQuery->Close();
	sumQuery->Close();
	if( genSql )
		genSqlCode();

	reservatQuery->Open();
	sumQuery->Open();

	checkEvents();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Rume1Click(TObject *)
{
	RoomForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Tische1Click(TObject *)
{
	TableForm->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SqlReportClick(TObject *Sender)
{
	STRING theReport = ConfigDataModule->GetValue( GasthausDB, "reportPath", "reports\\" );
	theReport += ((TMenuItem*)Sender)->Caption.c_str();

	theReport = makeFullPath( (STRING)Application->ExeName.c_str(), theReport );

	STRING theReportCmd = "srxViewer.exe GASTHAUS \"";
	theReportCmd += theReport;
	theReportCmd += '\"';

	WinExec( theReportCmd, SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HtmlReportClick(TObject *Sender)
{
	STRING theReport = ConfigDataModule->GetValue( GasthausDB, "reportPath", "reports\\" );
	STRING	selXSL = ((TMenuItem*)Sender)->Caption.c_str();
	theReport += selXSL;

	theReport = makeFullPath( (STRING)Application->ExeName.c_str(), theReport );

	STRING	destXSL = getenv( "TMP" );
	destXSL += DIRECTORY_DELIMITER;
	STRING destXML = destXSL;
	destXSL += selXSL;
	destXML += "gasthaus.xml";

	fcopy( theReport, destXSL );
	XML_ANY	*theData = exportTable2XML( reservatQuery, "gasthaus", "reservierung", 3 );

	if( theData )
	{
		STRING	xmlCode = theData->generateDoc( "", selXSL );
		doLogString( xmlCode );
		ofstream	fStream( destXML );
		if( fStream.is_open() )
			fStream << xmlCode;
		delete theData;
	}
	ShellExecute( NULL, "open", destXML, "", "", SW_SHOW );
}
//---------------------------------------------------------------------------
extern char	dbAliasName[];

void __fastcall TMainForm::FormShow(TObject *)
{
	if( *dbAliasName )
		GasthausDB->AliasName = dbAliasName;

	try
	{
		GasthausDB->Open();
	}
	catch(const Exception &E)
	{
		Application->MessageBox(
			"Kann Gasthaus Datenbank nicht öffnen.", "Schwerer Fehler",
			MB_OK
		);
		abort();
	}

	LicenceForm->readLicence( "Gasthaus", LICENCE_CODE );
	if( !LicenceForm->checkLicence( LICENCE_CODE ) )
		LicenceForm->ShowModal();

	if( !LicenceForm->checkLicence( LICENCE_CODE ) )
	{
		Close();
/*@*/	return;
	}

	while( true )
	{
		AnsiString	tmp, product = LicenceForm->productEdit->Text;
		AnsiString	error = "";
		int			dashPos = product.LastDelimiter( "-" );

		if( dashPos > 0 )
		{
			AnsiString		dateStr = product.SubString( dashPos+1, product.Length() - dashPos );
			int				lastMonth, lastYear;

			sscanf( dateStr.c_str(), "%d:%d", &lastMonth, &lastYear );

			TDateTime		now = TDateTime::CurrentDate();
			unsigned short	thisYear, thisMonth, dummy;
			now.DecodeDate( &thisYear, &thisMonth, &dummy );

			if( thisYear > lastYear
			|| (thisYear == lastYear && thisMonth > lastMonth) )
			{
				error = "Testlizenz abgelaufen";
			}

			product = product.SubString( 1, dashPos-1 );
		}

		if( product != "GasthausSQL" && product != "Gasthaus" )
			error = "Falscher Produktcode";
		else if( product != "GasthausSQL" && GasthausDB->IsSQLBased )
			error = "Keine gültige Lizenz für die Verwendung dieser Datenbank";

		if( error.Length() )
		{
			Application->MessageBox(
				error.c_str(), "Fehler", MB_ICONSTOP
			);
			if( LicenceForm->ShowModal() == mrOk )
/*^*/			continue;
			else
			{
				Close();
/*@*/			return;
			}
		}

		if( product == "GasthausSQL" )
		{
			AnsiString newCaption = Caption;
			newCaption += " Client/Server";
			Caption = newCaption;
			Application->Title = newCaption;
		}

		break;
	}


	getRepeatedReservations(atoi( ConfigForm->StammtischEdit->Text.c_str() ));

	StartDatePicker->Date = TDateTime::CurrentDate();
	EndDatePicker->Date = TDateTime::CurrentDate();

	DateComboBox->ItemIndex = 7;
	TimeComboBox->ItemIndex = 0;
	SortComboBox->ItemIndex = 0;

	fillRaeume();

	genSqlDates();

	if( ConfigDataModule->GetDBVersion( GasthausDB ) != 2 )
	{
		Application->MessageBox(
			"Falsche Datenbankversion", "Gasthaus", MB_OK|MB_ICONSTOP
		);
		Application->Terminate();
//		exit( -1 );
	}

	ARRAY_OF_STRINGS	reports;
	STRING 	reportPath = ConfigDataModule->GetValue( GasthausDB, "reportPath", "reports\\" );
	STRING reportPattern = reportPath + "*.srx";
	reportPattern = makeFullPath( (STRING)Application->ExeName.c_str(), reportPattern );

	findFiles( reportPattern, reports );

	MenuSQLreports->AutoHotkeys = maManual;
	for( size_t i=0; i<reports.getNumElements(); i++ )
	{
		TMenuItem *newMenu = new TMenuItem( this );
		newMenu->AutoHotkeys = maManual;
		newMenu->Caption = (const char *)reports[i];
		newMenu->OnClick = SqlReportClick;

		MenuSQLreports->Add( newMenu );
	}

	reports.clear();
	reportPattern = reportPath + "*.xsl";
	reportPattern = makeFullPath( (STRING)Application->ExeName.c_str(), reportPattern );
	findFiles( reportPattern, reports );

	MenuHTMLreports->AutoHotkeys = maManual;
	for( size_t i=0; i<reports.getNumElements(); i++ )
	{
		TMenuItem *newMenu = new TMenuItem( this );
		newMenu->AutoHotkeys = maManual;
		newMenu->Caption = (const char *)reports[i];
		newMenu->OnClick = HtmlReportClick;

		MenuHTMLreports->Add( newMenu );
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *, TCloseAction &)
{
	terminateThread();

	while( isThreadRunning() )
	{
		Sleep( 2000 );
		terminateThread();
	}

	reservatQuery->Close();
	sumQuery->Close();
	GasthausDB->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SortComboBoxChange(TObject *)
{
	restartQuery();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Ende1Click(TObject *)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RaeumeComboBoxChange(TObject *)
{
	restartQuery();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DateComboBoxChange(TObject *)
{
	genSqlDates();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StartDatePickerCloseUp(TObject *)
{
	genSqlDates();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EndDatePickerCloseUp(TObject *)
{
	genSqlDates();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Termine1Click(TObject *)
{
	ScheduleFrm->ShowModal();
	checkEvents( true );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::reservatQueryAfterScroll(TDataSet *)
{
	checkEvents();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonNewClick(TObject *)
{
	TDateTime currentDate;

	if( !reservatQuery->Eof && !reservatQuery->Bof )
		currentDate = reservatQueryDatum->AsDateTime;
	else
		currentDate = StartDatePicker->Date;

	if( !EditForm->Visible )
		EditForm->newReservation( currentDate );
	EditForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonEditClick(TObject *)
{
	if( !EditForm->Visible )
		EditForm->setReservation( reservatQueryID->AsInteger );
	EditForm->Show();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ReservationGridDrawColumnCell(TObject *,
	  const TRect &Rect, int DataCol, TColumn *Column,
	  TGridDrawState State)
{
	TGridDrawState	empty;

	if( State == empty )
	{
		if( reservatQueryStatus->AsString == "Storniert" )
			ReservationGrid->Canvas->Brush->Color = ConfigForm->DeletedEdit->Color;
		else if( reservatQueryfunc_status->AsString == "Nicht erledigt" )
			ReservationGrid->Canvas->Brush->Color = ConfigForm->notOkEdit->Color;
		else if( reservatQueryStatus->AsString == "Option" )
			ReservationGrid->Canvas->Brush->Color = ConfigForm->optionEdit->Color;
		else if( reservatQueryStatus->AsString == "Tagung" )
			ReservationGrid->Canvas->Brush->Color = ConfigForm->ConferenceEdit->Color;
		else if( reservatQueryKompletter_Raum->AsBoolean )
			ReservationGrid->Canvas->Brush->Color = ConfigForm->completeEdit->Color;
		else if( reservatQueryLink->AsInteger > 0 )
			ReservationGrid->Canvas->Brush->Color = ConfigForm->doubleEdit->Color;
	}
	ReservationGrid->DefaultDrawColumnCell( Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Stammtische1Click(TObject *)
{
	RepeatedForm->ShowModal();
	getRepeatedReservations(atoi( ConfigForm->StammtischEdit->Text.c_str() ));

	restartQuery( false );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Liste1Click(TObject *)
{
	TableReport->setSqlText( reservatQuery );
	TableReport->previewReport();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Tischkarte1Click(TObject *)
{
	CardReport->setSqlText( reservatQuery );
	CardReport->previewReport();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EinzelneKarte1Click(TObject *)
{
	SelCardForm->selectCard( reservatQueryID->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::berGasthaus1Click(TObject *)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DuplicateClick(TObject *)
{
	int	curId = reservatQueryID->AsInteger;
	EditForm->setReservation( reservatQueryID->AsInteger );
	EditForm->duplicateReservation( false );
	restartQuery( false );
	gotoReservation( curId );
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::GotoCopyClick(TObject *)
{
	int	linkId = reservatQueryLink->AsInteger;
	if( linkId > 0 )
		gotoReservation( linkId );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonReloadClick(TObject *)
{
	int	curId = reservatQueryID->AsInteger;
	restartQuery(false);
	gotoReservation( curId );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AlteResLschen1Click(TObject *)
{
	deleteReservation();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimeComboBoxChange(TObject *)
{
	genSqlDates();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::GruppierteListe1Click(TObject *)
{
	SortComboBox->ItemIndex = 0;
	restartQuery( true );

	GroupReport->setSqlText( reservatQuery );
	GroupReport->previewReport();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Optionen1Click(TObject *)
{
	ConfigForm->ShowModal();
	ReservationGrid->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FreieTische1Click(TObject *)
{
	TDateTime currentDate;

	if(
		Application->MessageBox(
			"Dies kann sehr lange dauern. Wollen Sie das Formular öffnen?",
			"Warnung",
			MB_OKCANCEL|MB_ICONQUESTION
		) == ID_OK
	)
	{
		if( !reservatQuery->Eof && !reservatQuery->Bof )
			currentDate = reservatQueryDatum->AsDateTime;
		else
			currentDate = StartDatePicker->Date;

		FreeForm->FreeQuery->Close();
		FreeForm->FreeQuery->SQL->Clear();
		FreeForm->FreeQuery->SQL->Add(
			"select distinct rx.name, tx.tisch, tx.personen, tx.id "
			"from raum rx, tisch tx "
			"where tx.raum = rx.id"
		);
		FreeForm->FreeQuery->SQL->Add( "and not exists (" );
		FreeForm->FreeQuery->SQL->Add(
			"select * "
			"from reservat r "
			"where r.tisch = tx.id and r.datum = :curDate"
		);
		if( (double)startTime != 0.0 || (double)endTime != 0.0 )
			FreeForm->FreeQuery->SQL->Add(
				"and r.uhrzeit >= :sTime and r.uhrzeit <= :eTime"
			);
		FreeForm->FreeQuery->SQL->Add( ")" );

		if( RaeumeComboBox->ItemIndex > 0 )
		{
			AnsiString	tmp = "and rx.name = '";
			tmp += RaeumeComboBox->Items->Strings[RaeumeComboBox->ItemIndex];
			tmp += "'";

			FreeForm->FreeQuery->SQL->Add( tmp );
		}

		FreeForm->FreeQuery->Params->Items[0]->AsDate = currentDate;
		if( (double)startTime != 0.0 || (double)endTime != 0.0 )
		{
			FreeForm->FreeQuery->Params->Items[1]->AsDateTime = startTime;
			FreeForm->FreeQuery->Params->Items[2]->AsDateTime = endTime;
		}

		FreeForm->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::reservatQueryAfterOpen(TDataSet *)
{
	int		count = reservatQuery->RecordCount;
	char	tmpBuff[64];
	char	*reservat;

	reservat = count != 1 ? "Reservierungen" : "Reservierung";
	sprintf( tmpBuff, "%d %s", count, reservat );
	CountLabel->Caption = tmpBuff;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Diagramm1Click(TObject *)
{
	if( Application->MessageBox("Dies kann sehr lange dauern. "
							"Wollen Sie das Formular öffnen?",
							"Warnung",
							MB_OKCANCEL|MB_ICONQUESTION ) == ID_OK )
		ChartForm->Show();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Berechnungstarten1Click(TObject *)
{
	getRepeatedReservations(atoi( ConfigForm->StammtischEdit->Text.c_str() ));

	restartQuery( false );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Berechnungbeenden1Click(TObject *)
{
	terminateThread();

	while( isThreadRunning() )
	{
		Sleep( 1000 );
		terminateThread();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Zeichnen1Click(TObject *)
{
	DrawingForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditNameChange(TObject *)
{
	restartQuery();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Lizenz1Click(TObject *)
{
	LicenceForm->ShowModal();	
}
//---------------------------------------------------------------------------





