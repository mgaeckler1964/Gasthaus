//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SelCdFrm.h"
#include "CardRep.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelCardForm *SelCardForm;
//---------------------------------------------------------------------------
__fastcall TSelCardForm::TSelCardForm(TComponent* Owner)
	: TForm(Owner)
{
	reservationId = 0;
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button1Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 0 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button2Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 1 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button3Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 2 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button4Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 3 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button5Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 4 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button6Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 5 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button7Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 6 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button8Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 7 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button9Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 8 );
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSelCardForm::Button10Click(TObject *)
{
	CardReport->setSqlText( reservationId );
	CardReport->previewReport( 9 );
	Close();
}
//---------------------------------------------------------------------------
