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

#include "SchedFrm.h"
#include "gr_utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TScheduleFrm *ScheduleFrm;
//---------------------------------------------------------------------------
__fastcall TScheduleFrm::TScheduleFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TScheduleFrm::enableDisableEndDate( void )
{
	if( ArtComboBox->ItemIndex == 2 )
		EndDatePicker->Visible = true;
	else
		EndDatePicker->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::FormShow(TObject *)
{
	ScheduleTable->Open();
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::FormClose(TObject *,
	  TCloseAction &)
{
	ScheduleTable->Close();
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::ArtComboBoxChange(TObject *)
{
	enableDisableEndDate();
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::startDatePickerCloseUp(TObject *)
{
	if( ScheduleTable->State != dsEdit && ScheduleTable->State != dsInsert )
		ScheduleTable->Edit();

	ScheduleTableStartDatum->AsDateTime = startDatePicker->Date;
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::EndDatePickerCloseUp(TObject *)
{
	if( ScheduleTable->State != dsEdit && ScheduleTable->State != dsInsert )
		ScheduleTable->Edit();

	ScheduleTableEndeDatum->AsDateTime = EndDatePicker->Date;
}
//---------------------------------------------------------------------------


void __fastcall TScheduleFrm::ScheduleTableAfterScroll(TDataSet *)
{
	enableDisableEndDate();
	startDatePicker->Date = ScheduleTableStartDatum->AsDateTime;
	EndDatePicker->Date = ScheduleTableEndeDatum->AsDateTime;
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::ScheduleTableAfterInsert(TDataSet *)
{
	ScheduleTableId->AsInteger = 1;
	ArtComboBox->ItemIndex = 0;
	ScheduleTableArt->AsString = "Fest";
	startDatePicker->Date = TDateTime::CurrentDate();
	ScheduleTableStartDatum->AsDateTime = TDateTime::CurrentDate();
	EndDatePicker->Date = TDateTime::CurrentDate();
	ScheduleTableEndeDatum->AsDateTime = TDateTime::CurrentDate();
	enableDisableEndDate();
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::ScheduleTableBeforePost(TDataSet *)
{
	unsigned short	year, month, day;
	TDateTime		startDate, current;

	current = TDateTime::CurrentDate();
	startDate = ScheduleTableStartDatum->AsDateTime;
	startDate.DecodeDate( &year, &month, &day );
	ScheduleTableTag->AsInteger = day;
	ScheduleTableMonat->AsInteger = month;

	if( ScheduleTableArt->AsString != "Zeitraum" )
		ScheduleTableEndeDatum->AsDateTime = startDate;
}
//---------------------------------------------------------------------------

void __fastcall TScheduleFrm::ScheduleTablePostError(TDataSet *,
	  EDatabaseError *, TDataAction &Action)
{
	if( Action == daFail )
	{
		if( ScheduleTableId->AsInteger == 1 )
		{
			ScheduleTableId->AsInteger = getNewMaxValue( "termine", "id" );
			Action = daRetry;
		}
	}
}
//---------------------------------------------------------------------------

