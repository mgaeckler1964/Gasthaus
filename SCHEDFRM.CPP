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

