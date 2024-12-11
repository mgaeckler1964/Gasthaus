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

