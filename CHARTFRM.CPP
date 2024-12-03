//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChartFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChartForm *ChartForm;
//---------------------------------------------------------------------------
__fastcall TChartForm::TChartForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TChartForm::FormShow(TObject *Sender)
{
	roomsChart->Align = alClient;
	personsChart->Align = alClient;
	RoomsClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TChartForm::FormClose(TObject *, TCloseAction &)
{
	roomsQuery->Close();
	personsQuery->Close();
}
//---------------------------------------------------------------------------

void __fastcall TChartForm::RoomsClick(TObject *)
{
	personsChart->Visible = false;
	personsQuery->Close();
	roomsQuery->Open();
	roomsChart->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TChartForm::PersonsClick(TObject *)
{
	roomsChart->Visible = false;
	roomsQuery->Close();
	personsQuery->Open();
	personsChart->Visible = true;
}
//---------------------------------------------------------------------------

