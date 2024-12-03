//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "RoomFrm.h"

#include "gr_utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRoomForm *RoomForm;
//---------------------------------------------------------------------------
__fastcall TRoomForm::TRoomForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRoomForm::FormShow(TObject *)
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
}
//---------------------------------------------------------------------------

void __fastcall TRoomForm::FormClose(TObject *, TCloseAction &)
{
	RoomTable->Close();
}
//---------------------------------------------------------------------------


void __fastcall TRoomForm::RoomTablePostError(TDataSet *,
	  EDatabaseError *, TDataAction &Action)
{
	if( Action == daFail )
	{
		if( RoomTableID->AsInteger == 1 )
		{
			RoomTableID->AsInteger = getNewMaxValue( "raum", "id" );
			Action = daRetry;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TRoomForm::RoomTableAfterInsert(TDataSet *)
{
	RoomTableID->AsInteger = 1;
}
//---------------------------------------------------------------------------

