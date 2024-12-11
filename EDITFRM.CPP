/*
		Project:		GASTHAUS
		Module:			
		Description:	
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Austria, Linz ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/

//---------------------------------------------------------------------------
#include <math.h>

#include <vcl.h>
#pragma hdrstop
#include <shellapi.h>

#include "EditFrm.h"
#include "MainFrm.h"
#include "gr_utils.h"
#include "SelectFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace gak;

TEditForm *EditForm;

//---------------------------------------------------------------------------
__fastcall TEditForm::TEditForm(TComponent* Owner)
	: TForm(Owner)
{
	currentReservation = 0;
	currentDate = 0;
	currentTable = 0;
}
//---------------------------------------------------------------------------
void TEditForm::transfer2Controls( void )
{
	TTime		selTime;

	selTime = ReservationQueryUhrzeit->AsDateTime;
	TimePicker->Time = selTime;

	selTime = ReservationQueryEnde->AsDateTime;
	EndTimePicker->Time = selTime;

	if( (double)ReservationQueryDatum->AsDateTime > 0 )
		DatePicker->Date = ReservationQueryDatum->AsDateTime;
}

//---------------------------------------------------------------------------
void TEditForm::transfer2Table( void )
{
	TTime		selTime;

	selTime = TimePicker->Time - floor( TimePicker->Time );
	ReservationQueryUhrzeit->AsDateTime = selTime;

	selTime = EndTimePicker->Time - floor( EndTimePicker->Time );
	ReservationQueryEnde->AsDateTime = selTime;

	ReservationQueryDatum->AsDateTime = DatePicker->Date;
}

//---------------------------------------------------------------------------
void TEditForm::duplicateReservation( bool includeLink )
{
	TQuery	*newReservation;
	bool	srcIsOpen;
	int		linkId;

	srcIsOpen = ReservationQuery->Active;
	if( !srcIsOpen )
		ReservationQuery->Open();

	if( includeLink )
		linkId = ReservationQueryLink->AsInteger;

	if( !includeLink || !linkId )	// source not yet linked
	{
		newReservation = new TQuery( Application );
		if( newReservation )
		{
			newReservation->DatabaseName = "GASTHAUS";
			newReservation->SQL->Add( "select * from reservat" );
			newReservation->RequestLive = true;
			newReservation->Open();
			newReservation->Insert();

			newReservation->FieldByName( "ID" )->AsInteger = getNewMaxValue( "reservat", "id" );
			newReservation->FieldByName( "Datum" )->AsDateTime = ReservationQueryDatum->AsDateTime;
			newReservation->FieldByName( "Uhrzeit" )->AsDateTime = ReservationQueryUhrzeit->AsDateTime;
			newReservation->FieldByName( "Ende" )->AsDateTime = ReservationQueryEnde->AsDateTime;
			newReservation->FieldByName( "Tisch" )->AsInteger = ReservationQueryTisch->AsInteger;
			newReservation->FieldByName( "Name" )->AsString = ReservationQueryName->AsString;
			newReservation->FieldByName( "Personen" )->AsInteger = ReservationQueryPersonen->AsInteger;
			newReservation->FieldByName( "Kuerzel" )->AsString = ReservationQueryKuerzel->AsString;
			newReservation->FieldByName( "Status" )->AsString = ReservationQueryStatus->AsString;
			if( includeLink )
				newReservation->FieldByName( "Link" )->AsInteger = currentReservation;
			newReservation->FieldByName( "Telefon" )->AsString = ReservationQueryTelefon->AsString;
			newReservation->FieldByName( "Anlass" )->AsString = ReservationQueryAnlass->AsString;
			newReservation->FieldByName( "Ext_bemerk" )->AsString = ReservationQueryExt_bemerk->AsString;
			newReservation->FieldByName( "Int_bemerk" )->AsString = ReservationQueryInt_bemerk->AsString;
			newReservation->FieldByName( "Kompletter_raum" )->AsString = ReservationQueryKompletter_raum->AsString;
			newReservation->Post();
			if( includeLink )
				linkId = newReservation->FieldByName( "ID" )->AsInteger;
			newReservation->Close();

			if( includeLink )
			{
				ReservationQuery->Edit();
				ReservationQueryLink->AsInteger = linkId;
				ReservationQuery->Post();
			}

			delete newReservation;
		}
	}

	if( !srcIsOpen )
		ReservationQuery->Close();
}
//---------------------------------------------------------------------------
void TEditForm::setReservation( long reservationId )
{
	currentReservation = reservationId;
	ReservationQuery->Close();
	ReservationQuery->SQL->Clear();
	ReservationQuery->SQL->Add( "select * from RESERVAT" );
	if( currentReservation )
	{
		ReservationQuery->SQL->Add( "where ID = :theId" );
		ReservationQuery->Params->Items[0]->AsInteger = currentReservation;
	}
}

//---------------------------------------------------------------------------
void TEditForm::findRoom( void )
{
	RoomsComboBox->ItemIndex = GasthausDataModule->findRoomForTable( ReservationQueryTisch->AsInteger );
	fillTables();
}

//---------------------------------------------------------------------------
void TEditForm::fillTables( void )
{
	TableQuery->Close();
	TableQuery->Params->Items[0]->AsInteger = GasthausDataModule->getRoomID(
		RoomsComboBox->ItemIndex
	);
	TableQuery->Open();
}

//---------------------------------------------------------------------------

void __fastcall TEditForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	int		theButton;
	if( ReservationQuery->State == dsEdit || ReservationQuery->State == dsInsert )
	{
		theButton =	Application->MessageBox(
			"Wollen Sie die Änderungen speichern?",
			"Warnung", MB_YESNOCANCEL|MB_ICONQUESTION
		);
		if( theButton == IDNO )
			ReservationQuery->Cancel();
		else if( theButton == IDYES )
			ButtonSaveClick( Sender );
	}

	if( ReservationQuery->State != dsEdit && ReservationQuery->State != dsInsert )
	{
		ReservationQuery->Close();
		TableQuery->Close();

		MainForm->clrTableFilter();
	}
	else
		Action = caNone;
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::ButtonSaveClick(TObject *Sender)
{
	bool	reservationOK = true;

	if( ReservationQuery->State == dsEdit || ReservationQuery->State == dsInsert )
	{
		// remove link to repeated reservations
		if( ReservationQueryLink->AsInteger < 0 )
			ReservationQueryLink->Clear();

		if(ReservationQueryId->IsNull )
			ReservationQueryId->AsInteger = getNewMaxValue("reservat", "id" );

		transfer2Table();

		if( !DBCheckBoxComplete->Checked )
		{
			int freeSpace = GasthausDataModule->getFreePlaces(
				RoomsComboBox->ItemIndex,
				ReservationQueryTisch->AsInteger,
				ReservationQueryDatum->AsDateTime,
				ReservationQueryUhrzeit->AsDateTime,
				ReservationQueryEnde->AsDateTime,
				ReservationQueryId->AsInteger
			);
			if( freeSpace >= 0 && freeSpace < ReservationQueryPersonen->AsInteger )
			{
				AnsiString	message;
				message.printf(
					"Für diesen Tisch gibt es nur %d Plätze. "
					"Wollen Sie trotzdem speichern?",
					freeSpace
				);
				if(
					Application->MessageBox(
						message.c_str(), "Gasthausreservierung", MB_YESNO|MB_ICONWARNING
					) == IDNO
				)
					reservationOK = false;
			}
		}
		else
		{
			int numPersons = GasthausDataModule->getReservations(
				RoomsComboBox->ItemIndex,
				ReservationQueryDatum->AsDateTime,
				ReservationQueryUhrzeit->AsDateTime,
				ReservationQueryEnde->AsDateTime,
				ReservationQueryId->AsInteger
			);
			if( numPersons )
			{
				AnsiString	message;
				message.printf(
					"Dieser Raum ist bereits mit %d Personen besetzt. "
					"Wollen Sie trotzdem speichern?",
					numPersons
				);
				if(
					Application->MessageBox(
						message.c_str(), "Gasthausreservierung", MB_YESNO|MB_ICONWARNING
					) == IDNO
				)
					reservationOK = false;
			}
		}

		if( reservationOK )
		{
			CUSTOMER	newClient(ReservationQueryName->AsString.c_str());
			size_t		pos = clients.findElement( newClient );
			if( pos == (size_t)-1 )
			{
				newClient.telefon = ReservationQueryTelefon->AsString.c_str();
				clients.addElement( newClient );
			}
			ReservationQuery->Post();
		}
	}

	if( reservationOK )
	{
		currentReservation = ReservationQueryId->AsInteger;

		if( ReservationQueryStatus->AsString == "Doppelt" )
			duplicateReservation( true );

		if( Sender == ButtonSave )
			Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::ButtonCancelClick(TObject *)
{
	ReservationQuery->Cancel();
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::FormShow(TObject *)
{
	LabelLastUser->Caption = "";
	GasthausDataModule->loadRooms( RoomsComboBox, 0, 0 );

	RoomsComboBox->ItemIndex = -1;

	if( !clients.size() )
	{
		CUSTOMER	client;

		for(
			NameQuery->Open();
			!NameQuery->Eof;
			NameQuery->Next()
		)
		{
			client.name = NameQueryNAME->AsString.c_str();
			client.telefon = NameQueryTELEFON->AsString.c_str();
			clients.addElement( client );
		}
		NameQuery->Close();
	}
	ReservationQuery->Open();
	if( !currentReservation )
	{
		ReservationQuery->Insert();
		DatePicker->Date = currentDate;
		ReservationQueryDatum->AsDateTime = currentDate;
		ReservationQueryErfassungsDatum->AsDateTime = TDateTime::CurrentDate();
		ReservationQueryKompletter_raum->AsBoolean = false;
		if( currentTable > 0 )
		{
			ReservationQueryTisch->AsInteger = currentTable;
			findRoom();
		}
		changePhone = true;
	}
	else
	{
		findRoom();

		changePhone = ReservationQueryTelefon->AsString.Length() > 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::RoomsComboBoxChange(TObject *)
{
	fillTables();
	ReservationQuery->Edit();
	ReservationQueryTisch->Clear();
	MainForm->RaeumeComboBox->ItemIndex = RoomsComboBox->ItemIndex+1;
	MainForm->restartQuery();
}
//---------------------------------------------------------------------------
void __fastcall TEditForm::DatePickerCloseUp(TObject *)
{
	ReservationQuery->Edit();

	MainForm->DateComboBox->ItemIndex = 7;
	MainForm->StartDatePicker->Date = DatePicker->Date;
	MainForm->genSqlDates();
}
//---------------------------------------------------------------------------


void __fastcall TEditForm::DBLookupComboBoxTischCloseUp(TObject *)
{
	MainForm->setTableFilter(ReservationQueryTisch->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::ReservationQueryAfterScroll(TDataSet *)
{
	transfer2Controls();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::TimePickerChange(TObject *)
{
	ReservationQuery->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::ReservationQueryAfterCancel(TDataSet *)
{
	transfer2Controls();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::ReservationQueryBeforePost(TDataSet *)
{
	transfer2Table();
}
//---------------------------------------------------------------------------


void __fastcall TEditForm::ChangeMenuClick(TObject *Sender)
{
	if( OpenDialog->Execute() )
	{
		ReservationQuery->Edit();
		ReservationQueryFunktion->AsString = OpenDialog->FileName;
		OpenMenuClick( Sender );
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::OpenMenuClick(TObject *Sender)
{
	if( ReservationQueryFunktion->IsNull )
		ChangeMenuClick( Sender );
	else
	{
		ShellExecute( NULL, "open",
			ReservationQueryFunktion->AsString.c_str(),
			"",
			"",
			SW_SHOW );
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::DeleteMenuClick(TObject *)
{
	ReservationQueryFunktion->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TEditForm::ButtonSelectClick(TObject *)
{
	TTime		startTime, endTime;
	int			numPersons;

	startTime = TimePicker->Time - floor( TimePicker->Time );
	endTime = EndTimePicker->Time - floor( EndTimePicker->Time );
	numPersons =  ReservationQueryPersonen->AsInteger;
	if( !numPersons )
	{
		DBEditPersonen->SetFocus();
/*@*/	throw Exception( "Bitte geben Sie erst die Anzahl der Personen ein" );
	}

	SelectForm->setSelection(
		ReservationQueryId->AsInteger,		
		RoomsComboBox->ItemIndex,
		DatePicker->Date, startTime, endTime, numPersons
	);
	if( SelectForm->ShowModal() == mrOk )
	{
		RoomsComboBox->ItemIndex = SelectForm->getSelectedRoom();
		RoomsComboBoxChange( NULL );

		ReservationQueryTisch->AsInteger = SelectForm->getSelectedTable();

	}
}
//---------------------------------------------------------------------------



void __fastcall TEditForm::DBEditNameKeyPress(TObject *, char &Key)
{
	STRING text = DBEditName->Text.c_str();

	if( DBEditName->SelStart + DBEditName->SelLength >= text.strlen() )
	{
		text.cut( DBEditName->SelStart );
		text += Key;
		CUSTOMER	client( text );
		size_t	pos = clients.findInsertPos( client );
		if( pos )
			pos--;
		for( size_t i=pos; i<clients.size(); i++ )
		{
			const CUSTOMER	&client = clients[i];
			if( client.name.beginsWith( text ) )
			{
				DBEditName->Text = (const char *)client.name;
				DBEditName->SelStart = text.strlen();
				DBEditName->SelLength = client.name.strlen() - text.strlen();
				if( changePhone )
					ReservationQueryTelefon->AsString = (const char *)client.telefon;

				Key = 0;
/*v*/			break;
			}
		}
	}
	if( changePhone && Key )
		ReservationQueryTelefon->AsString = "";
}
//---------------------------------------------------------------------------


void __fastcall TEditForm::ClearUser(TDataSet *)
{
	if( LabelLastUser->Caption == "" )
	{
		LabelLastUser->Caption = ReservationQueryKuerzel->AsString;
		ReservationQueryKuerzel->AsString = "";
	}
}
//---------------------------------------------------------------------------




