//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectFrm.h"
#include "GasthausDM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelectForm *SelectForm;
//---------------------------------------------------------------------------
__fastcall TSelectForm::TSelectForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSelectForm::PaintBoxPaint(TObject *)
{
	TCanvas	*canvas = PaintBox->Canvas;
	TSize	textSize;
	int 	textLeft, textTop;

	int roomIdx = ComboBoxRooms->ItemIndex;
	if( roomIdx >= 0 )
	{
		ARRAY<ROOM_INFO> &rooms = GasthausDataModule->getRooms();
		ROOM_INFO	&theRoom = rooms[roomIdx];

		if( theRoom.points.getNumElements() > 1 )
		{
			canvas->Pen->Color = clGray;
			canvas->Pen->Width = 3;
			for( size_t i=0; i<theRoom.points.getNumElements(); i++ )
			{
				PREC_POINT &coordinates = theRoom.points[i];

				if( !i )
					canvas->MoveTo( coordinates.x, coordinates.y );
				else
					canvas->LineTo( coordinates.x, coordinates.y );
			}
			if( theRoom.points.getNumElements() > 2 )
			{
				PREC_POINT &coordinates = theRoom.points[0];

				canvas->LineTo( coordinates.x, coordinates.y );
			}
		}

		canvas->Pen->Color = clBlack;
		canvas->Pen->Width = 1;
		for( size_t i=0; i<theRoom.tables.getNumElements(); i++ )
		{
			TABLE_INFO	&theTable = theRoom.tables[i];
			if( theTable.left > 0
			||  theTable.top > 0
			||  theTable.right > 0
			||  theTable.bottom > 0 )
			{
				if( !theTable.personenI )
				{
					if( !theTable.besetzt )
						canvas->Brush->Color = clGreen;
					else
						canvas->Brush->Color = clRed;
				}
				else
				{
					if( theTable.personenI - theTable.besetzt >= numPersons )
					{
						if( !theTable.besetzt )
							canvas->Brush->Color = clGreen;
						else
							canvas->Brush->Color = clYellow;
					}
					else
						canvas->Brush->Color = clRed;
				}

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

				AnsiString	label;
				label.sprintf(
					"%s (%d/%s)",
					(const char *)theTable.name,
					theTable.besetzt,
					(const char *)theTable.personenStr
				);
				textSize = canvas->TextExtent( label );
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
				canvas->TextOut( textLeft, textTop, label );
			}
		}
	}
	paintBoxWidth = PaintBox->Width;
	paintBoxHeight = PaintBox->Height;
}
//---------------------------------------------------------------------------
void __fastcall TSelectForm::FormKeyPress(TObject *, char &Key)
{
	if( Key == 27 )
	{
		ModalResult = mrCancel;
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSelectForm::FormShow(TObject *)
{
	paintBoxWidth = PaintBox->Width;
	paintBoxHeight = PaintBox->Height;

	GasthausDataModule->loadRooms( ComboBoxRooms, paintBoxWidth, paintBoxHeight );

	ComboBoxRooms->ItemIndex = selectedRoom;
	ComboBoxRoomsChange( ComboBoxRooms );
}
//---------------------------------------------------------------------------

void __fastcall TSelectForm::ComboBoxRoomsChange(TObject *)
{
	doEnterFunction("TSelectForm::ComboBoxRoomsChange");

	int roomIdx = ComboBoxRooms->ItemIndex;
	if( roomIdx >= 0 )
	{
		GasthausDataModule->loadTables(
			roomIdx, NULL, paintBoxWidth, paintBoxHeight,
			selDatum,
			selStartTime, selEndTime,
			selId
		);
	}

	PaintBox->Invalidate();
	doShowLog();
}
//---------------------------------------------------------------------------


void __fastcall TSelectForm::FormResize(TObject *)
{
	int paintBoxWidth = PaintBox->Width;
	int paintBoxHeight = PaintBox->Height;

	ARRAY<ROOM_INFO> &rooms = GasthausDataModule->getRooms();

	for( size_t	roomIdx=0; roomIdx<rooms.getNumElements(); roomIdx++ )
	{
		ROOM_INFO	&theRoom = rooms[roomIdx];

		for( size_t pointIdx=0; pointIdx<theRoom.points.getNumElements(); pointIdx++ )
		{
			PREC_POINT	&thePoint = theRoom.points[pointIdx];

			thePoint.x = toScreen(
				paintBoxWidth, toNormal( this->paintBoxWidth, thePoint.x )
			);
			thePoint.y = toScreen(
				paintBoxHeight, toNormal( this->paintBoxHeight, thePoint.y )
			);
		}
		for( size_t tableIdx=0; tableIdx<theRoom.tables.getNumElements(); tableIdx++ )
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
void __fastcall TSelectForm::PaintBoxMouseUp(TObject *,
	  TMouseButton Button, TShiftState , int X, int Y)
{
	if( Button == mbLeft )
	{
		int roomIdx = ComboBoxRooms->ItemIndex;
		if( roomIdx >= 0 )
		{
			int			combiRoom = -1;
			int			combiTable = -1;

			ARRAY<ROOM_INFO> &rooms = GasthausDataModule->getRooms();
			ROOM_INFO	&theRoom = rooms[roomIdx];

			TPoint	theMouse;
			theMouse.x = X;
			theMouse.y = Y;

			for( size_t tableIdx=0; tableIdx<theRoom.tables.getNumElements(); tableIdx++ )
			{
				TABLE_INFO	&theTable = theRoom.tables[tableIdx];

				if( isInRect( theMouse, theTable )
				&& (
					!theTable.personenI
					|| theTable.personenI-theTable.besetzt >= numPersons
				) )
				{
					if( theTable.shape == COMBI_TABLE )
					{
						combiRoom = roomIdx;
						combiTable = theTable.ID;
					}
					else
					{
						selectedRoom = roomIdx;
						selectedTable = theTable.ID;
						ModalResult = mrOk;
/***/					return;
					}
				}
			}

			if( combiRoom >= 0 && combiTable >= 0 )
			{
				selectedRoom = combiRoom;
				selectedTable = combiTable;
				ModalResult = mrOk;
			}
		}
	}
}
//---------------------------------------------------------------------------
