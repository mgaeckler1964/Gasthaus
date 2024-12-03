//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FreeFrm.h"
#include "EditFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFreeForm *FreeForm;
//---------------------------------------------------------------------------
__fastcall TFreeForm::TFreeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFreeForm::FormShow(TObject *)
{
	FreeQuery->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFreeForm::FormClose(TObject *, TCloseAction &)
{
	FreeQuery->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFreeForm::Button1Click(TObject *)
{
	if( !EditForm->Visible )
		EditForm->newReservation( FreeQuery->Params->Items[0]->AsDate, FreeQueryID->AsInteger );
	EditForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFreeForm::Button2Click(TObject *)
{
	FreeQuery->Close();
	FreeQuery->Open();
}
//---------------------------------------------------------------------------

