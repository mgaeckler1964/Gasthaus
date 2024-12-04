//---------------------------------------------------------------------------
#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *ReservationGrid;
	TLabel *Label1;
	TComboBox *DateComboBox;
	TLabel *Label2;
	TComboBox *SortComboBox;
	TButton *ButtonNew;
	TButton *ButtonEdit;
	TButton *ButtonReload;
	TDataSource *reservatSource;
	TQuery *reservatQuery;
	TComboBox *RaeumeComboBox;
	TMainMenu *MainMenu;
	TMenuItem *Datei1;
	TMenuItem *Bearbeiten1;
	TMenuItem *Hilfe1;
	TMenuItem *Einrichtung1;
	TMenuItem *Rume1;
	TMenuItem *Tische1;
	TMenuItem *Ende1;
	TDateTimePicker *StartDatePicker;
	TDateTimePicker *EndDatePicker;
	TMenuItem *Termine1;
	TQuery *ScheduleQuery;
	TLabel *TerminLabel;
	TMenuItem *Stammtische1;
	TQuery *sumQuery;
	TDataSource *SumSource;
	TDBText *DBText1;
	TLabel *Label3;
	TMenuItem *Drucken1;
	TMenuItem *N1;
	TMenuItem *Tischkarte1;
	TMenuItem *Liste1;
	TMenuItem *EinzelneKarte1;
	TMenuItem *Duplicate;
	TMenuItem *AlteResLschen1;
	TMenuItem *GotoCopy;
	TMenuItem *N2;
	TMenuItem *N3;
	TComboBox *TimeComboBox;
	TMenuItem *GruppierteListe1;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *Optionen1;
	TMenuItem *FreieTische1;
	TLabel *CountLabel;
	TMenuItem *Diagramm1;
	TDatabase *GasthausDB;
	TIntegerField *reservatQueryID;
	TDateTimeField *reservatQueryDatum;
	TStringField *reservatQueryRaum;
	TStringField *reservatQueryTisch;
	TDateTimeField *reservatQueryUhrzeit;
	TStringField *reservatQueryName;
	TStringField *reservatQueryStatus;
	TStringField *reservatQueryfunc_status;
	TStringField *reservatQueryAnlass;
	TStringField *reservatQueryint_bemerk;
	TStringField *reservatQueryext_bemerk;
	TSmallintField *reservatQueryPersonen;
	TStringField *reservatQueryTelefon;
	TIntegerField *reservatQueryLink;
	TStringField *reservatQueryKompletter_Raum;
	TMenuItem *Berechnungstarten1;
	TMenuItem *Berechnungbeenden1;
	TMenuItem *Zeichnen1;
	TMenuItem *N6;
	TEdit *EditName;
	TMenuItem *MenuSQLreports;
	TMenuItem *MenuHTMLreports;
	void __fastcall Rume1Click(TObject *Sender);
	void __fastcall Tische1Click(TObject *Sender);

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SortComboBoxChange(TObject *Sender);
	void __fastcall Ende1Click(TObject *Sender);
	void __fastcall RaeumeComboBoxChange(TObject *Sender);
	void __fastcall DateComboBoxChange(TObject *Sender);

	void __fastcall StartDatePickerCloseUp(TObject *Sender);
	void __fastcall EndDatePickerCloseUp(TObject *Sender);
	void __fastcall Termine1Click(TObject *Sender);
	void __fastcall reservatQueryAfterScroll(TDataSet *DataSet);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);

	void __fastcall ReservationGridDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall Stammtische1Click(TObject *Sender);
	void __fastcall Liste1Click(TObject *Sender);
	void __fastcall Tischkarte1Click(TObject *Sender);
	void __fastcall EinzelneKarte1Click(TObject *Sender);
	void __fastcall berGasthaus1Click(TObject *Sender);
	void __fastcall DuplicateClick(TObject *Sender);
	
	void __fastcall GotoCopyClick(TObject *Sender);
	void __fastcall ButtonReloadClick(TObject *Sender);
	void __fastcall AlteResLschen1Click(TObject *Sender);
	void __fastcall TimeComboBoxChange(TObject *Sender);
	
	void __fastcall GruppierteListe1Click(TObject *Sender);
	void __fastcall Optionen1Click(TObject *Sender);
	
	void __fastcall FreieTische1Click(TObject *Sender);
	void __fastcall reservatQueryAfterOpen(TDataSet *DataSet);
	void __fastcall Diagramm1Click(TObject *Sender);
	void __fastcall Berechnungstarten1Click(TObject *Sender);
	void __fastcall Berechnungbeenden1Click(TObject *Sender);
	void __fastcall Zeichnen1Click(TObject *Sender);
	void __fastcall EditNameChange(TObject *Sender);
private:	// User declarations
	TDateTime	startDate, endDate, lastDate;
	TDateTime	startTime, endTime;

	int			tableFilter;

	void checkEvents( bool ignoreLastDate = false );
	void genSqlCode( void );
	void fillRaeume( void );
	void gotoReservation( int reservationId );
	void deleteReservation( int reservationId = 0 );
	void __fastcall SqlReportClick(TObject *Sender);
	void __fastcall HtmlReportClick(TObject *Sender);
public:		// User declarations
	void genSqlDates( void );
	void restartQuery( bool genSql = true );
	void setTableFilter( int theTable )
	{
		tableFilter = theTable;
		restartQuery();
	}
	void clrTableFilter( void )
	{
		tableFilter = 0;
		restartQuery();
	}
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
