//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "gasthausDbFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dbConvertFrm"
#pragma resource "*.dfm"
TGasthausDbForm *GasthausDbForm;
//---------------------------------------------------------------------------
__fastcall TGasthausDbForm::TGasthausDbForm(TComponent* Owner)
	: TDbConvertForm(Owner)
{
}
//---------------------------------------------------------------------------
const char *TGasthausDbForm::getAliasName( void ) const
{
	return "GASTHAUS";
}
//---------------------------------------------------------------------------
