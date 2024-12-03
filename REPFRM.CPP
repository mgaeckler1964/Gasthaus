//---------------------------------------------------------------------------
#include <math.h>
#include <vcl.h>
#pragma hdrstop

#include "RepFrm.h"
#include "gr_utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRepeatedForm *RepeatedForm;
//---------------------------------------------------------------------------
__fastcall TRepeatedForm::TRepeatedForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TRepeatedForm::removeReservations( void )
{
	TQuery	*delSql;

	delSql = new TQuery( Application );
	if( delSql )
	{
		delSql->DatabaseName = "GASTHAUS";
		delSql->SQL->Add( "delete from reservat where link = :theId" );
		delSql->Params->Items[0]->AsInteger = -RepResTableID->AsInteger;
		delSql->ExecSQL();

		delete delSql;
	}
}
//---------------------------------------------------------------------------
void TRepeatedForm::enableDisableControls( void )
{
	if( RepeatComboBox->ItemIndex == 0 )	// täglich
	{
		DayLabel->Visible = false;
		CounterComboBox->Visible = false;
		WeekDayComboBox->Visible = false;

		MonthLabel->Visible = false;
		MonthDayEdit->Visible = false;
		DayMonthLabel->Visible = false;
		MonthComboBox->Visible = false;
	}
	else if( RepeatComboBox->ItemIndex == 1 )	// Wöchentlich
	{
		DayLabel->Visible = true;
		CounterComboBox->Visible = false;
		WeekDayComboBox->Left = RepeatComboBox->Left;
		WeekDayComboBox->Visible = true;

		MonthLabel->Visible = false;
		MonthDayEdit->Visible = false;
		DayMonthLabel->Visible = false;
		MonthComboBox->Visible = false;
	}
	else if( RepeatComboBox->ItemIndex == 2 )	// Monatlich
	{
		DayLabel->Visible = true;
		CounterComboBox->Visible = true;
		WeekDayComboBox->Left = MonthComboBox->Left;
		WeekDayComboBox->Visible = true;

		MonthLabel->Visible = true;
		MonthDayEdit->Visible = true;
		DayMonthLabel->Caption = "eines Monats.";
		DayMonthLabel->Visible = true;
		MonthComboBox->Visible = false;
	}
	else if( RepeatComboBox->ItemIndex == 3 )	// Jährlich
	{
		DayLabel->Visible = true;
		CounterComboBox->Visible = true;
		WeekDayComboBox->Left = MonthComboBox->Left;
		WeekDayComboBox->Visible = true;

		MonthLabel->Visible = true;
		MonthDayEdit->Visible = true;
		DayMonthLabel->Caption = "im Monat";
		DayMonthLabel->Visible = true;
		MonthComboBox->Visible = true;
	}
	if( CounterComboBox->Visible )
	{
		if( !CounterComboBox->ItemIndex )
		{
			WeekDayComboBox->Visible = false;
			MonthDayEdit->Visible = true;
		}
		else
		{
			WeekDayComboBox->Visible = true;
			MonthDayEdit->Visible = false;
		}
	}
}

void TRepeatedForm::findRoom( void )
{
	TQuery	*theQuery;
	int		index;

	theQuery = new TQuery( Application );
	if( theQuery )
	{
		theQuery->DatabaseName = "GASTHAUS";
		//theQuery->UniDirectional = true;
		theQuery->RequestLive = false;

		theQuery->SQL->Add( "select distinct r.name" );
		theQuery->SQL->Add( "from raum r, tisch t" );
		theQuery->SQL->Add( "where r.id = t.raum and t.id = :theTable" );
		theQuery->Params->Items[0]->AsInteger = RepResTableTisch->AsInteger;

		theQuery->Open();
		if( !theQuery->Eof )
		{
			index = RoomsComboBox->Items->IndexOf( theQuery->Fields->Fields[0]->AsString );
			if( index >= 0 )
			{
				RoomsComboBox->ItemIndex = index;
				fillTables();
			}
		}
		theQuery->Close();

		delete theQuery;
	}
}

void TRepeatedForm::fillRooms( void )
{
	TQuery	*theQuery;

	RoomsComboBox->Items->Clear();

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
			RoomsComboBox->Items->Add( theQuery->Fields->Fields[0]->AsString );
			theQuery->Next();
		}
		theQuery->Close();

		delete theQuery;
	}
}

void TRepeatedForm::fillTables( void )
{
	TableQuery->Close();
	TableQuery->SQL->Clear();
	TableQuery->SQL->Add( "select distinct t.tisch || ' (' || t.personen || ' Pers. )' Tisch, t.ID" );
	TableQuery->SQL->Add( "from	tisch t, raum r" );
	TableQuery->SQL->Add( "where t.raum = r.id and r.name = :derRaum" );

	TableQuery->Params->Items[0]->AsString = RoomsComboBox->Items->Strings[RoomsComboBox->ItemIndex];
	TableQuery->Open();
}

void TRepeatedForm::transfer2Controls( void )
{
	int		counter;
	TTime	selTime;

	if( RepResTable->RecordCount )
	{
		RepeatComboBox->ItemIndex = RepResTableWiederholung->AsInteger;
		counter = RepResTableZaehler->AsInteger;
		if( counter < 0 )
			counter = 4 - counter;

		CounterComboBox->ItemIndex = counter;
		WeekDayComboBox->ItemIndex = RepResTableWochenTag->AsInteger-1;
		MonthComboBox->ItemIndex = RepResTableMonat->AsInteger -1;

		findRoom();

		selTime = RepResTableUhrzeit->AsDateTime;
		TimePicker->Time = selTime;

		selTime = RepResTableEnde->AsDateTime;
		EndTimePicker->Time = selTime;
	}
	enableDisableControls();
}
void TRepeatedForm::transfer2Table( void )
{
	int		counter;
	TTime	selTime;


	RepResTableWiederholung->AsInteger = RepeatComboBox->ItemIndex;

	counter = CounterComboBox->ItemIndex;
	if( counter > 4 )
		counter = 4 - counter;

	RepResTableZaehler->AsInteger = counter;

	RepResTableWochenTag->AsInteger = WeekDayComboBox->ItemIndex+1;
	RepResTableMonat->AsInteger = MonthComboBox->ItemIndex +1;

	selTime = TimePicker->Time - floor( TimePicker->Time );
	RepResTableUhrzeit->AsDateTime = selTime;

	selTime = EndTimePicker->Time - floor( EndTimePicker->Time );
	RepResTableEnde->AsDateTime = selTime;
}

//---------------------------------------------------------------------------
void __fastcall TRepeatedForm::FormShow(TObject *)
{
	fillRooms();

	RepResTable->Open();
	if( !RepResTable->RecordCount )
		RepResTable->Insert();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::FormClose(TObject *,
	  TCloseAction &)
{
	RepResTable->Close();
	TableQuery->Close();
}
//---------------------------------------------------------------------------



void __fastcall TRepeatedForm::RoomsComboBoxChange(TObject *)
{
	fillTables();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::RepResTableAfterScroll(TDataSet *)
{
	transfer2Controls();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::RepResTableBeforePost(TDataSet *)
{
	if( MonthDayEdit->Visible )
	{
		if( MonthDayEdit->Field->IsNull || MonthDayEdit->Field->AsInteger == 0 )
		{
			Application->MessageBox( "Geben Sie einen Monatstag ein", "Fehler", 0 );
			Abort();
		}
		if( MonthDayEdit->Field->AsInteger < 1 || MonthDayEdit->Field->AsInteger > 31 )
		{
			Application->MessageBox( "Geben Sie einen Monatstag zwischen 1 und 31 ein", "Fehler", 0 );
			Abort();
		}
	}
	if( WeekDayComboBox->Visible && WeekDayComboBox->ItemIndex < 0 )
	{
		Application->MessageBox( "Geben Sie einen Wochentag ein", "Fehler", 0 );
		Abort();
	}
	if( MonthComboBox->Visible && MonthComboBox->ItemIndex < 0 )
	{
		Application->MessageBox( "Geben Sie einen Monat ein", "Fehler", 0 );
		Abort();
	}

	transfer2Table();

	// remove entries in reservation table
	RepResTableLetzterEintrag->Clear();
	removeReservations();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::RepResTableAfterInsert(TDataSet *)
{
	RepResTableID->AsInteger = 1;
	RepResTableWiederholung->AsInteger = 0;
	RepeatComboBox->ItemIndex = 0;
	RepResTableKompletter_raum->AsBoolean = false;
	TableQuery->Close();
	RoomsComboBox->ItemIndex = -1;
	TimePicker->Time = 0;
	enableDisableControls();
}

//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::RepeatComboBoxChange(TObject *)
{
	RepResTable->Edit();
	enableDisableControls();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::CounterComboBoxChange(TObject *)
{
	enableDisableControls();
	RepResTable->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::WeekDayComboBoxChange(TObject *)
{
	RepResTable->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::MonthComboBoxChange(TObject *)
{
	RepResTable->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::RepResTableAfterCancel(TDataSet *)
{
	transfer2Controls();
}
//---------------------------------------------------------------------------


void __fastcall TRepeatedForm::RepResTableBeforeDelete(TDataSet *)
{
	removeReservations();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::TimePickerChange(TObject *)
{
	RepResTable->Edit();
	transfer2Table();
}
//---------------------------------------------------------------------------

void __fastcall TRepeatedForm::RepResTablePostError(TDataSet *,
	  EDatabaseError *, TDataAction &Action)
{
	if( Action == daFail )
	{
		if( RepResTableID->AsInteger == 1 )
		{
			RepResTableID->AsInteger = getNewMaxValue("stamm", "id" );
			Action = daRetry;
		}
	}
}
//---------------------------------------------------------------------------

