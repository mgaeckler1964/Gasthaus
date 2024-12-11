/*
		Project:		GASTHAUS
		Module:			
		Description:	
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2024 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Austria, Linz ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/

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

