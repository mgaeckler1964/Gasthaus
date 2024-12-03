//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GroupRep.h"
#include "ConfFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGroupReport *GroupReport;
//---------------------------------------------------------------------------
__fastcall TGroupReport::TGroupReport(TComponent* Owner)
	: TForm(Owner)
{
}

void TGroupReport::setSqlText( const TQuery *source )
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Text = source->SQL->Text;
	Query->Params->Assign( source->Params );
}

void TGroupReport::previewReport( void )
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

