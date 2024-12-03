//---------------------------------------------------------------------------

#ifndef SelectFrmH
#define SelectFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>

#include <gak/array.h>

#include "DrawFrm.h"

#include "GasthausDM.h"

//---------------------------------------------------------------------------
class TSelectForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPaintBox *PaintBox;
	TComboBox *ComboBoxRooms;
	void __fastcall PaintBoxPaint(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboBoxRoomsChange(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall PaintBoxMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
	int					paintBoxWidth, paintBoxHeight, selectedRoom, selId,
						selectedTable, numPersons;
	TDate				selDatum;
	TTime				selStartTime, selEndTime;

public:		// User declarations
	__fastcall TSelectForm(TComponent* Owner);
	void setSelection(
		int reservatId, int roomIdx,
		TDate selDatum, TTime selStartTime, TTime selEndTime, int numPersons
	)
	{
		selId = reservatId;
		selectedRoom = roomIdx;
		this->selDatum = selDatum;
		this->selStartTime = selStartTime;
		this->selEndTime = selEndTime;
		this->numPersons = numPersons;
	}

	int getSelectedRoom( void ) const
	{
		return selectedRoom;
	}
	int getSelectedTable( void ) const
	{
		return selectedTable;
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectForm *SelectForm;
//---------------------------------------------------------------------------
#endif
