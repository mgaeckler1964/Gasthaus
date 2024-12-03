//---------------------------------------------------------------------------
#ifndef RepFrmH
#define RepFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TRepeatedForm : public TForm
{
__published:	// IDE-managed Components
	TComboBox *RepeatComboBox;
	TComboBox *WeekDayComboBox;
	TComboBox *CounterComboBox;
	TComboBox *MonthComboBox;
	TLabel *Label1;
	TLabel *DayLabel;
	TLabel *MonthLabel;
	TDataSource *RepResSource;
	TTable *RepResTable;
	TDBGrid *DBGrid1;
	TDBEdit *MonthDayEdit;
	TDBNavigator *DBNavigator1;
	TLabel *Label4;
	TDBEdit *DBEdit2;
	TDBEdit *DBEdit4;
	TDBEdit *DBEdit5;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TComboBox *RoomsComboBox;
	TDBComboBox *DBComboBox1;
	TDBLookupComboBox *DBLookupComboBox1;
	TDBCheckBox *DBCheckBox1;
	TDBEdit *DBEdit6;
	TDBEdit *DBEdit7;
	TLabel *Label8;
	TLabel *Label9;
	TDBMemo *DBMemo2;
	TLabel *Label10;
	TDBMemo *DBMemo3;
	TQuery *TableQuery;
	TDataSource *TableSource;
	TLabel *Label11;
	TBevel *Bevel1;
	TLabel *DayMonthLabel;
	TDBEdit *DBEdit1;
	TDateTimePicker *TimePicker;
	TStringField *RepResTableWiederholung;
	TSmallintField *RepResTableWochenTag;
	TSmallintField *RepResTableMonatsTag;
	TSmallintField *RepResTableMonat;
	TSmallintField *RepResTableZaehler;
	TDateTimeField *RepResTableLetzterEintrag;
	TDateTimeField *RepResTableUhrzeit;
	TIntegerField *RepResTableTisch;
	TStringField *RepResTableName;
	TSmallintField *RepResTablePersonen;
	TStringField *RepResTableKuerzel;
	TStringField *RepResTableStatus;
	TStringField *RepResTableTelefon;
	TStringField *RepResTableAnlass;
	TStringField *RepResTableExt_bemerk;
	TStringField *RepResTableInt_bemerk;
	TStringField *RepResTableKompletter_raum;
	TIntegerField *RepResTableID;
	TDateTimePicker *EndTimePicker;
	TDateTimeField *RepResTableEnde;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RoomsComboBoxChange(TObject *Sender);
	void __fastcall RepResTableAfterScroll(TDataSet *DataSet);
	void __fastcall RepResTableBeforePost(TDataSet *DataSet);
	void __fastcall RepResTableAfterInsert(TDataSet *DataSet);
	
	void __fastcall RepeatComboBoxChange(TObject *Sender);
	void __fastcall CounterComboBoxChange(TObject *Sender);
	void __fastcall WeekDayComboBoxChange(TObject *Sender);
	void __fastcall MonthComboBoxChange(TObject *Sender);
	void __fastcall RepResTableAfterCancel(TDataSet *DataSet);
	void __fastcall RepResTableBeforeDelete(TDataSet *DataSet);
	void __fastcall TimePickerChange(TObject *Sender);
	void __fastcall RepResTablePostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
	
private:	// User declarations
	void removeReservations( void );
	void findRoom( void );
	void fillRooms( void );
	void fillTables( void );
	void enableDisableControls( void );

	void transfer2Controls( void );
	void transfer2Table( void );
public:		// User declarations
	__fastcall TRepeatedForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRepeatedForm *RepeatedForm;
//---------------------------------------------------------------------------
#endif
