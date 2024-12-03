//---------------------------------------------------------------------------
#ifndef RoomFrmH
#define RoomFrmH
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
class TRoomForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *RoomSource;
	TTable *RoomTable;
	TPanel *Panel1;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TIntegerField *RoomTableID;
	TStringField *RoomTableNAME;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RoomTablePostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
	void __fastcall RoomTableAfterInsert(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TRoomForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRoomForm *RoomForm;
//---------------------------------------------------------------------------
#endif
