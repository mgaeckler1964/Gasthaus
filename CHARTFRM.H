//---------------------------------------------------------------------------
#ifndef ChartFrmH
#define ChartFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <DBChart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TChartForm : public TForm
{
__published:	// IDE-managed Components
	TDBChart *roomsChart;
	TPieSeries *Series1;
	TQuery *personsQuery;
	TPopupMenu *PopupMenu1;
	TMenuItem *Rooms;
	TMenuItem *Persons;
	TDBChart *personsChart;
	TQuery *roomsQuery;
	TPieSeries *PieSeries1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RoomsClick(TObject *Sender);
	void __fastcall PersonsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TChartForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChartForm *ChartForm;
//---------------------------------------------------------------------------
#endif
