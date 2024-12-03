//---------------------------------------------------------------------------
#ifndef TableFrmH
#define TableFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TTableForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *RoomSource;
	TTable *RoomTable;
	TDataSource *TableSource;
	TTable *TableTable;
	TPanel *Panel1;
	TPanel *Panel2;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TPanel *Panel3;
	TPanel *Panel4;
	TDBNavigator *DBNavigator2;
	TDBGrid *DBGrid2;
	TIntegerField *RoomTableID;
	TStringField *RoomTableNAME;
	TIntegerField *TableTableID;
	TIntegerField *TableTableRAUM;
	TStringField *TableTableTISCH;
	TStringField *TableTablePERSONEN;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TableTableAfterInsert(TDataSet *DataSet);
	void __fastcall TableTablePostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TTableForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTableForm *TableForm;
//---------------------------------------------------------------------------
#endif
