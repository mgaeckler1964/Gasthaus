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
