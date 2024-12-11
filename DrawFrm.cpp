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

#include "DrawFrm.h"
#include "GasthausDM.h"

using namespace gak;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDrawingForm *DrawingForm;
//---------------------------------------------------------------------------
__fastcall TDrawingForm::TDrawingForm(TComponent* Owner)
	: TForm(Owner)
{
	drawMode = WAITING;
}
//---------------------------------------------------------------------------
void __fastcall TDrawingForm::PaintBoxMouseUp(TObject *,
	  TMouseButton Button, TShiftState , int X, int Y)
{
	if( Button == mbLeft )
	{
		int roomIdx = ComboBoxRooms->ItemIndex;
		if( roomIdx >= 0 )
		{
			Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

			if( RadioButtonRoom->Checked )
			{
				if( drawMode == WAITING )
				{
					PREC_POINT	nextPoint;

					ROOM_INFO	&theRoom = rooms[roomIdx];

					theRoom.points.clear();

					nextPoint.x = X;
					nextPoint.y = Y;

					theRoom.points.addElement( nextPoint );

					drawMode = NEXT_ROOM_POINT;

					lastMousePos.x = -1;
					lastMousePos.y = -1;
				}
				else if( drawMode == NEXT_ROOM_POINT )
				{
					PREC_POINT	nextPoint;

					ROOM_INFO	&theRoom = rooms[roomIdx];

					nextPoint.x = X;
					nextPoint.y = Y;

					theRoom.points.addElement( nextPoint );

					if( theRoom.points.size() < 3 )
					{
						lastMousePos.x = -1;
						lastMousePos.y = -1;
					}
				}
			}
			else if( drawMode == NEXT_TABLE_POINT )
			{
				int tableIdx =  ComboBoxTables->ItemIndex;
				if( tableIdx >= 0 )
				{
					ROOM_INFO	&theRoom = rooms[roomIdx];
					TABLE_INFO	&theTable = theRoom.tables[tableIdx];

					if( RadioButtonSquareTable->Checked )
						theTable.shape = SQUARE_TABLE;
					else if( RadioButtonCombiTable->Checked )
						theTable.shape = COMBI_TABLE;
					else if( RadioButtonCircleTable->Checked )
						theTable.shape = CIRCLE_TABLE;

					theTable.left = min( (int)firstMousePos.x, X );
					theTable.right = max( (int)firstMousePos.x, X );
					theTable.top = min( (int)firstMousePos.y, Y );
					theTable.bottom = max( (int)firstMousePos.y, Y );

					if( theTable.shape == COMBI_TABLE )
					{
						bool	tableFound = false;
						double	newTop = paintBoxHeight;
						double	newBottom = 0;
						double	newLeft = paintBoxWidth;
						double	newRight = 0;

						for( size_t i=0; i<theRoom.tables.size(); i++ )
						{
							if( i != (size_t)tableIdx )
							{
								TABLE_INFO	&otherTable = theRoom.tables[i];
								if( isInRect( otherTable, theTable ) )
								{
									newTop = min( newTop, otherTable.top );
									newBottom = max( newBottom, otherTable.bottom );
									newLeft = min( newLeft, otherTable.left );
									newRight = max( newRight, otherTable.right );
									tableFound = true;
								}
							}
						}
						if( tableFound )
						{
							theTable.left = newLeft-1;
							theTable.right = newRight+1;
							theTable.top = newTop-1;
							theTable.bottom = newBottom+1;
						}
						else
						{
							theTable.left = 0;
							theTable.right = 0;
							theTable.top = 0;
							theTable.bottom = 0;
						}
					}
					drawMode = WAITING;
					PaintBox->Invalidate();
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDrawingForm::PaintBoxMouseMove(TObject *,
	  TShiftState , int X, int Y)
{
	TCanvas	*canvas = PaintBox->Canvas;

	int roomIdx = ComboBoxRooms->ItemIndex;
	if( roomIdx >= 0 )
	{
		Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

		if( RadioButtonRoom->Checked && drawMode == NEXT_ROOM_POINT )
		{
			ROOM_INFO	&theRoom = rooms[roomIdx];
			size_t		numPoints = theRoom.points.size();
			PREC_POINT	&last = theRoom.points[numPoints-1];

			canvas->Pen->Width = 1;
			canvas->Pen->Color = clBlack;
			canvas->Pen->Mode = pmNot;

			if( lastMousePos.x >= 0 && lastMousePos.y >= 0 )
			{
				canvas->MoveTo( last.x, last.y );
				canvas->LineTo( lastMousePos.x, lastMousePos.y );
				if( numPoints > 1 )
				{
					PREC_POINT &first = theRoom.points[0];
					canvas->LineTo( first.x, first.y );
				}
			}

			canvas->MoveTo( last.x, last.y );
			canvas->LineTo( X, Y );
			if( numPoints > 1 )
			{
				PREC_POINT &first = theRoom.points[0];
				canvas->LineTo( first.x, first.y );
			}
			lastMousePos.x = X;
			lastMousePos.y = Y;
		}
		else if( drawMode == NEXT_TABLE_POINT )
		{
			int tableIdx =  ComboBoxTables->ItemIndex;
			if( tableIdx >= 0 )
			{
				canvas->Pen->Width = 1;
				canvas->Pen->Color = clBlack;
				canvas->Pen->Mode = pmNot;

				if( lastMousePos.x >= 0 && lastMousePos.y >= 0 )
				{
					if( RadioButtonSquareTable->Checked
					||  RadioButtonCombiTable->Checked )
					{
						canvas->Rectangle(
							firstMousePos.x, firstMousePos.y,
							lastMousePos.x, lastMousePos.y
						);
					}
					else
					{
						canvas->Ellipse(
							firstMousePos.x, firstMousePos.y,
							lastMousePos.x, lastMousePos.y
						);
					}
				}
				lastMousePos.x = X;
				lastMousePos.y = Y;
				if( RadioButtonSquareTable->Checked
				||  RadioButtonCombiTable->Checked )
				{
					canvas->Rectangle(
						firstMousePos.x, firstMousePos.y,
						lastMousePos.x, lastMousePos.y
					);
				}
				else
				{
					canvas->Ellipse(
						firstMousePos.x, firstMousePos.y,
						lastMousePos.x, lastMousePos.y
					);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDrawingForm::PaintBoxPaint(TObject *)
{
	TSize	textSize;
	int 	textLeft, textTop;
	TCanvas	*canvas = PaintBox->Canvas;

	canvas->Pen->Mode = pmCopy;
	canvas->Brush->Color = clWhite;

	int roomIdx = ComboBoxRooms->ItemIndex;
	if( roomIdx >= 0 )
	{
		Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

		ROOM_INFO	&theRoom = rooms[roomIdx];

		if( theRoom.points.size() > 1 )
		{
			canvas->Pen->Color = clGray;
			canvas->Pen->Width = 3;
			for( size_t i=0; i<theRoom.points.size(); i++ )
			{
				PREC_POINT &coordinates = theRoom.points[i];

				if( !i )
					canvas->MoveTo( coordinates.x, coordinates.y );
				else
					canvas->LineTo( coordinates.x, coordinates.y );
			}
			if( theRoom.points.size() > 2 )
			{
				PREC_POINT &coordinates = theRoom.points[0];

				canvas->LineTo( coordinates.x, coordinates.y );
			}
		}
		canvas->Pen->Color = clBlack;
		canvas->Pen->Width = 1;
		for( size_t i=0; i<theRoom.tables.size(); i++ )
		{
			TABLE_INFO	&theTable = theRoom.tables[i];
			if( theTable.left > 0
			||  theTable.top > 0
			||  theTable.right > 0
			||  theTable.bottom > 0 )
			{

				if( theTable.shape == CIRCLE_TABLE )
				{
					canvas->Ellipse(
						theTable.left, theTable.top,
						theTable.right, theTable.bottom
					);
				}
				else if( theTable.shape == SQUARE_TABLE )
				{
					canvas->Rectangle(
						theTable.left, theTable.top,
						theTable.right, theTable.bottom
					);
				}
				else if( theTable.shape == COMBI_TABLE )
				{
					TPoint	polyLine[5];

					makePoints( theTable, polyLine );
					canvas->Polyline( polyLine, 4 );
				}

				textSize = canvas->TextExtent( (const char *)theTable.name );
				if( theTable.shape != COMBI_TABLE )
				{
					textLeft = (theTable.left + theTable.right - textSize.cx)/2;
					textTop = (theTable.top + theTable.bottom - textSize.cy)/2;
				}
				else
				{
					textLeft = theTable.left+1;
					textTop = theTable.top+1;
				}

				canvas->TextOut( textLeft, textTop, (const char *)theTable.name );
			}
		}
	}
	paintBoxWidth = PaintBox->Width;
	paintBoxHeight = PaintBox->Height;
}
//---------------------------------------------------------------------------
void __fastcall TDrawingForm::FormKeyPress(TObject *, char &Key)
{

	if( Key == 27 )
	{
		ResetDrawMode( NULL );
	}
	else if( Key == '\b' && drawMode == WAITING )
	{
		int roomIdx = ComboBoxRooms->ItemIndex;
		if( roomIdx >= 0 )
		{
			int tableIdx =  ComboBoxTables->ItemIndex;
			if( tableIdx >= 0 )
			{
				Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

				ROOM_INFO	&theRoom = rooms[roomIdx];
				TABLE_INFO	&theTable = theRoom.tables[tableIdx];

				theTable.left = theTable.right =
				theTable.top = theTable.bottom = 0;

				ResetDrawMode( NULL );
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDrawingForm::FormShow(TObject *)
{
	paintBoxWidth = PaintBox->Width;
	paintBoxHeight = PaintBox->Height;

	GasthausDataModule->loadRooms( ComboBoxRooms, paintBoxWidth, paintBoxHeight );

	ComboBoxRooms->ItemIndex = 0;
	ComboBoxRoomsChange( ComboBoxRooms );
}
//---------------------------------------------------------------------------

void __fastcall TDrawingForm::ComboBoxRoomsChange(TObject *)
{
	int roomIdx = ComboBoxRooms->ItemIndex;
	if( roomIdx >= 0 )
	{
		GasthausDataModule->loadTables(
			roomIdx, ComboBoxTables, paintBoxWidth, paintBoxHeight
		);
	}

	drawMode = WAITING;
	PaintBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TDrawingForm::PaintBoxMouseDown(TObject *,
	  TMouseButton Button, TShiftState , int X, int Y)
{
	if( Button == mbLeft )
	{
		int roomIdx = ComboBoxRooms->ItemIndex;
		int tableIdx = ComboBoxTables->ItemIndex;
		if( roomIdx >= 0 && tableIdx >= 0 )
		{
			if( RadioButtonSquareTable->Checked
			||  RadioButtonCombiTable->Checked
			||  RadioButtonCircleTable->Checked )
			{
				firstMousePos.x = X;
				firstMousePos.y = Y;

				lastMousePos.x = -1;
				lastMousePos.y = -1;

				drawMode = NEXT_TABLE_POINT;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDrawingForm::FormResize(TObject *)
{
	doEnterFunction("TDrawingForm::FormResize");
	int paintBoxWidth = PaintBox->Width;
	int paintBoxHeight = PaintBox->Height;

	doLogValue( this->paintBoxWidth );
	doLogValue( this->paintBoxHeight );
	doLogValue( paintBoxWidth );
	doLogValue( paintBoxHeight );

	Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

	for( size_t	roomIdx=0; roomIdx<rooms.size(); roomIdx++ )
	{
		ROOM_INFO	&theRoom = rooms[roomIdx];

		for( size_t pointIdx=0; pointIdx<theRoom.points.size(); pointIdx++ )
		{
			PREC_POINT	&thePoint = theRoom.points[pointIdx];

			doLogValue( thePoint.x );
			thePoint.x = toScreen(
				paintBoxWidth, toNormal( this->paintBoxWidth, thePoint.x )
			);
			doLogValue( thePoint.x );
			doLogValue( thePoint.y );
			thePoint.y = toScreen(
				paintBoxHeight, toNormal( this->paintBoxHeight, thePoint.y )
			);
			doLogValue( thePoint.y );
		}
		for( size_t tableIdx=0; tableIdx<theRoom.tables.size(); tableIdx++ )
		{
			TABLE_INFO	&theTable = theRoom.tables[tableIdx];

			theTable.left = toScreen(
				paintBoxWidth, toNormal( this->paintBoxWidth, theTable.left )
			);
			theTable.right = toScreen(
				paintBoxWidth, toNormal( this->paintBoxWidth, theTable.right )
			);
			theTable.top = toScreen(
				paintBoxHeight, toNormal( this->paintBoxHeight, theTable.top )
			);
			theTable.bottom = toScreen(
				paintBoxHeight, toNormal( this->paintBoxHeight, theTable.bottom )
			);
		}
	}
	this->paintBoxWidth = paintBoxWidth;
	this->paintBoxHeight = paintBoxHeight;
}
//---------------------------------------------------------------------------


void __fastcall TDrawingForm::FormClose(TObject *,
      TCloseAction &Action)
{
	TQuery	*updateSQL = new TQuery( this );
	updateSQL->DatabaseName = "Gasthaus";

	Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

	for( size_t	roomIdx=0; roomIdx<rooms.size(); roomIdx++ )
	{
		ROOM_INFO	&theRoom = rooms[roomIdx];

		updateSQL->SQL->Clear();
		updateSQL->SQL->Add(
			"delete from RAUM_POS where RAUM = :raumID"
		);
		updateSQL->Params->Items[0]->AsInteger = theRoom.ID;
		updateSQL->ExecSQL();

		if( theRoom.points.size() > 2 )
		{
			updateSQL->SQL->Clear();
			updateSQL->SQL->Add(
				"insert into RAUM_POS "
				"(RAUM, NUMMER, X_POS, Y_POS ) "
				"values "
				"(:RAUM, :NUMMER, :X_POS, :Y_POS ) "
			);
			updateSQL->Params->Items[0]->AsInteger = theRoom.ID;

			for( size_t pointIdx=0; pointIdx<theRoom.points.size(); pointIdx++ )
			{
				PREC_POINT	&thePoint = theRoom.points[pointIdx];

				updateSQL->Params->Items[1]->AsInteger = pointIdx;
				updateSQL->Params->Items[2]->AsInteger = toNormal( paintBoxWidth, thePoint.x ) + 0.5;
				updateSQL->Params->Items[3]->AsInteger = toNormal( paintBoxHeight, thePoint.y ) + 0.5;
				updateSQL->ExecSQL();
			}
		}

		updateSQL->SQL->Clear();
		updateSQL->SQL->Add(
			"update TISCH "
			"set left_pos = :leftPos, right_pos = :rightPos, "
				"top_pos = :topPos, bottom_pos = :bottomPos, "
				"shape = :theShape "
			"where ID = :theTable"
		);

		for( size_t tableIdx=0; tableIdx<theRoom.tables.size(); tableIdx++ )
		{
			TABLE_INFO	&theTable = theRoom.tables[tableIdx];

			updateSQL->Params->Items[0]->AsInteger = toNormal( paintBoxWidth, theTable.left ) + 0.5;
			updateSQL->Params->Items[1]->AsInteger = toNormal( paintBoxWidth, theTable.right ) + 0.5;
			updateSQL->Params->Items[2]->AsInteger = toNormal( paintBoxHeight, theTable.top ) + 0.5;
			updateSQL->Params->Items[3]->AsInteger = toNormal( paintBoxHeight, theTable.bottom ) + 0.5;
			updateSQL->Params->Items[4]->AsInteger = theTable.shape;
			updateSQL->Params->Items[5]->AsInteger = theTable.ID;

			updateSQL->ExecSQL();
		}
	}

	delete updateSQL;

	Action = caHide;
}
//---------------------------------------------------------------------------

void __fastcall TDrawingForm::ResetDrawMode(TObject *)
{
	int roomIdx = ComboBoxRooms->ItemIndex;
	if( roomIdx >= 0 )
	{
		Array<ROOM_INFO> &rooms = GasthausDataModule->getRooms();
		ROOM_INFO	&theRoom = rooms[roomIdx];
		if( theRoom.points.size() < 3 )
		{
			theRoom.points.clear();
		}
	}

	drawMode = WAITING;
	PaintBox->Invalidate();
}
//---------------------------------------------------------------------------

