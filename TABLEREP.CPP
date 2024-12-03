//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TableRep.h"
#include "ConfFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTableReport *TableReport;
//---------------------------------------------------------------------------
__fastcall TTableReport::TTableReport(TComponent* Owner)
	: TForm(Owner)
{
}
void TTableReport::setSqlText( const TQuery *source )
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Text = source->SQL->Text;
	Query->Params->Assign( source->Params );
}

void TTableReport::previewReport( void )
{
	AnsiString	logoFile;

	Query->Close();

	logoFile = ConfigForm->ListLogoEdit->Text;
	if( logoFile.Length() )
		ImageHeader->Picture->LoadFromFile( logoFile );

	Query->Open();
	QuickRep->Preview();
}

//---------------------------------------------------------------------------


