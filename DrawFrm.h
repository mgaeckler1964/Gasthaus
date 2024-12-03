//---------------------------------------------------------------------------

#ifndef DrawFrmH
#define DrawFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>

#include <gak/array.h>
//---------------------------------------------------------------------------
typedef enum
{
	WAITING, NEXT_ROOM_POINT, NEXT_TABLE_POINT
} DRAW_MODE;
//---------------------------------------------------------------------------
class TDrawingForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPaintBox *PaintBox;
	TComboBox *ComboBoxRooms;
	TComboBox *ComboBoxTables;
	TRadioButton *RadioButtonRoom;
	TRadioButton *RadioButtonSquareTable;
	TRadioButton *RadioButtonCircleTable;
	TRadioButton *RadioButtonCombiTable;
	void __fastcall PaintBoxMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall PaintBoxMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y);
	void __fastcall PaintBoxPaint(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboBoxRoomsChange(TObject *Sender);
	void __fastcall PaintBoxMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ResetDrawMode(TObject *Sender);
private:	// User declarations
	DRAW_MODE			drawMode;
	POINT				firstMousePos, lastMousePos;

	int					paintBoxWidth, paintBoxHeight;

public:		// User declarations
	__fastcall TDrawingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDrawingForm *DrawingForm;
//---------------------------------------------------------------------------

#endif
