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
