//---------------------------------------------------------------------------
#ifndef SchedFrmH
#define SchedFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TScheduleFrm : public TForm
{
__published:	// IDE-managed Components
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TDBEdit *DBEdit1;
	TDateTimePicker *startDatePicker;
	TDateTimePicker *EndDatePicker;
	TDBComboBox *ArtComboBox;
	TDataSource *ScheduleSource;
	TTable *ScheduleTable;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TStringField *ScheduleTableArt;
	TSmallintField *ScheduleTableTag;
	TSmallintField *ScheduleTableMonat;
	TStringField *ScheduleTableBeschreibung;
	TIntegerField *ScheduleTableId;
	TDateTimeField *ScheduleTableStartDatum;
	TDateTimeField *ScheduleTableEndeDatum;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ArtComboBoxChange(TObject *Sender);
	void __fastcall startDatePickerCloseUp(TObject *Sender);
	void __fastcall EndDatePickerCloseUp(TObject *Sender);
	void __fastcall ScheduleTableAfterScroll(TDataSet *DataSet);
	void __fastcall ScheduleTableAfterInsert(TDataSet *DataSet);
	void __fastcall ScheduleTableBeforePost(TDataSet *DataSet);
	void __fastcall ScheduleTablePostError(TDataSet *DataSet,
          EDatabaseError *E, TDataAction &Action);
private:	// User declarations
	void enableDisableEndDate( void );
public:		// User declarations
	__fastcall TScheduleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScheduleFrm *ScheduleFrm;
//---------------------------------------------------------------------------
#endif
