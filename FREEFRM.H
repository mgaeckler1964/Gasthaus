//---------------------------------------------------------------------------
#ifndef FreeFrmH
#define FreeFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFreeForm : public TForm
{
__published:	// IDE-managed Components
	TQuery *FreeQuery;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TStringField *FreeQueryNAME;
	TStringField *FreeQueryTISCH;
	TStringField *FreeQueryPERSONEN;
	TIntegerField *FreeQueryID;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFreeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFreeForm *FreeForm;
//---------------------------------------------------------------------------
#endif
