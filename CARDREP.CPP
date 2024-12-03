//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CardRep.h"
#include "ConfFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// must conform to the settings in the report:
#define WIDTH		105
#define HEIGTH		57
#define TOP_MARGIN	6
#define LEFT_MARGIN	0

TCardReport *CardReport;

//---------------------------------------------------------------------------
__fastcall TCardReport::TCardReport(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TCardReport::setSqlText( const TQuery *source )
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Text = source->SQL->Text;
	Query->Params->Assign( source->Params );
}
void TCardReport::setSqlText( int reservationId )
{
	Query->Close();
	Query->SQL->Clear();
	Query->SQL->Add( "select  r.Datum," );
	Query->SQL->Add( "		z.name Raum," );
	Query->SQL->Add( "		t.Tisch," );
	Query->SQL->Add( "		r.Uhrzeit," );
	Query->SQL->Add( "		r.Name," );
	Query->SQL->Add( "		r.Status," );
	Query->SQL->Add( "		r.Anlass," );
	Query->SQL->Add( "		r.ext_bemerk," );
	Query->SQL->Add( "		r.Personen," );
	Query->SQL->Add( "		r.Telefon" );
	Query->SQL->Add( "from	reservat r, tisch t, raum z" );
	Query->SQL->Add( "where	r.tisch = t.id and" );
	Query->SQL->Add( "		t.raum = z.id and" );
	Query->SQL->Add( "		r.id = :theResId" );
	Query->Params->Items[0]->AsInteger = reservationId;
}

void TCardReport::previewReport( int cardId )
{
	AnsiString	logoFile;

	if( cardId % 2 )
		QuickRep->Page->LeftMargin = LEFT_MARGIN + WIDTH;
	else
		QuickRep->Page->LeftMargin = LEFT_MARGIN;

	QuickRep->Page->TopMargin = TOP_MARGIN + (int)(cardId / 2) * HEIGTH;

	logoFile = ConfigForm->CardLogoEdit->Text;
	if( logoFile.Length() )
		ImageHeader->Picture->LoadFromFile( logoFile );

	Query->Close();
	Query->Open();
	QuickRep->Preview();
}

