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
#ifndef EditFrmH
#define EditFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>

#include <gak/ci_string.h>
#include <gak/sortedArray.h>

//---------------------------------------------------------------------------
struct CUSTOMER
{
	gak::CI_STRING	name, telefon;

	CUSTOMER( void ){};
	CUSTOMER( const gak::CI_STRING &newName ) : name( newName ) {};

	int compare( const CUSTOMER &c2 )
	{
		return strcmpi( name, c2.name );
	}
};

class TEditForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *ReservationSource;
	TDBEdit *DBEditName;
	TDBEdit *DBEditPersonen;
	TDBLookupComboBox *DBLookupComboBoxTisch;
	TQuery *TableQuery;
	TDataSource *TableSource;
	TDBEdit *DBEditTelefon;
	TComboBox *RoomsComboBox;
	TDBComboBox *DBComboBoxStatus;
	TDBEdit *DBEditKuerzel;
	TDBMemo *DBMemoInternalRemarks;
	TDBMemo *DBMemoExternalRemarks;
	TDBCheckBox *DBCheckBoxComplete;
	TButton *FunctionButton;
	TDBComboBox *DBComboBoxFunctionStatus;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TDBEdit *DBEditAnlass;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TButton *ButtonSave;
	TButton *ButtonCancel;
	TQuery *ReservationQuery;
	TDateTimePicker *DatePicker;
	TDBEdit *DBEditErfassungsDatum;
	TOpenDialog *OpenDialog;
	TDateTimePicker *TimePicker;
	TDateTimeField *ReservationQueryDatum;
	TDateTimeField *ReservationQueryErfassungsDatum;
	TDateTimeField *ReservationQueryUhrzeit;
	TIntegerField *ReservationQueryTisch;
	TStringField *ReservationQueryName;
	TSmallintField *ReservationQueryPersonen;
	TStringField *ReservationQueryKuerzel;
	TStringField *ReservationQueryStatus;
	TIntegerField *ReservationQueryLink;
	TStringField *ReservationQueryTelefon;
	TStringField *ReservationQueryAnlass;
	TStringField *ReservationQueryExt_bemerk;
	TStringField *ReservationQueryInt_bemerk;
	TStringField *ReservationQueryFunktion;
	TStringField *ReservationQueryFunc_status;
	TStringField *ReservationQueryKompletter_raum;
	TIntegerField *ReservationQueryId;
	TDateTimePicker *EndTimePicker;
	TDateTimeField *ReservationQueryEnde;
	TPopupMenu *PopupMenu1;
	TMenuItem *OpenMenu;
	TMenuItem *ChangeMenu;
	TMenuItem *DeleteMenu;
	TButton *ButtonSelect;
	TQuery *NameQuery;
	TStringField *NameQueryNAME;
	TStringField *NameQueryTELEFON;
	TLabel *LabelLastUser;
	TIntegerField *TableQueryID;
	TStringField *TableQueryTISCH;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RoomsComboBoxChange(TObject *Sender);

	void __fastcall DatePickerCloseUp(TObject *Sender);
	void __fastcall DBLookupComboBoxTischCloseUp(TObject *Sender);
	void __fastcall ReservationQueryAfterScroll(TDataSet *DataSet);
	void __fastcall TimePickerChange(TObject *Sender);
	void __fastcall ReservationQueryAfterCancel(TDataSet *DataSet);
	void __fastcall ReservationQueryBeforePost(TDataSet *DataSet);
	void __fastcall ChangeMenuClick(TObject *Sender);
	void __fastcall OpenMenuClick(TObject *Sender);
	void __fastcall DeleteMenuClick(TObject *Sender);
	void __fastcall ButtonSelectClick(TObject *Sender);
	void __fastcall DBEditNameKeyPress(TObject *Sender, char &Key);
	void __fastcall ClearUser(TDataSet *DataSet);
private:	// User declarations
	long		currentReservation;
	TDateTime	currentDate;
	long		currentTable;
	void transfer2Controls( void );
	void transfer2Table( void );
	void findRoom( void );
	void fillRooms( void );
	void fillTables( void );

	gak::SortedArray<CUSTOMER>	clients;
	bool						changePhone;

public:		// User declarations
	void setReservation( long reservationId );
	void newReservation( TDateTime newDefaultDate, long tableId = 0 )
	{
		setReservation( 0 );
		currentDate = newDefaultDate;
		currentTable = tableId;
	}
	void duplicateReservation( bool includeLink );

	__fastcall TEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditForm *EditForm;
//---------------------------------------------------------------------------
#endif
