//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TableFrm.h"
#include "gr_utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTableForm *TableForm;
//---------------------------------------------------------------------------
__fastcall TTableForm::TTableForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTableForm::FormShow(TObject *)
{
	try
	{
		RoomTable->Open();
	}
	catch( ... )
	{
		RoomTable->IndexName = "RAUM_NAME_IDX";
		RoomTable->Open();
	}
	TableTable->Open();
}
//---------------------------------------------------------------------------

void __fastcall TTableForm::FormClose(TObject *, TCloseAction &)
{
	TableTable->Close();
	RoomTable->Close();
}
//---------------------------------------------------------------------------

void __fastcall TTableForm::TableTableAfterInsert(TDataSet *)
{
	TableTableID->AsInteger = 1;
}
//---------------------------------------------------------------------------

void __fastcall TTableForm::TableTablePostError(TDataSet *,
	  EDatabaseError *, TDataAction &Action)
{
	if( Action == daFail )
	{
		if( TableTableID->AsInteger == 1 )
		{
			TableTableID->AsInteger = getNewMaxValue( "tisch", "id" );
			Action = daRetry;
		}
	}
}
//---------------------------------------------------------------------------

