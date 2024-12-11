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

#ifndef GasthausDMH
#define GasthausDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>

#include <gak/string.h>
#include <gak/array.h>

//---------------------------------------------------------------------------
typedef enum
{
	SQUARE_TABLE, CIRCLE_TABLE, COMBI_TABLE
} TABLE_SHAPE;
//---------------------------------------------------------------------------
struct TABLE_INFO
{
	int 			ID;
	gak::STRING		name, personenStr;
	int				besetzt, personenI;

	TABLE_SHAPE		shape;
	double			left, top, right, bottom;
};
//---------------------------------------------------------------------------
struct PREC_POINT
{
	double	x, y;
};
//---------------------------------------------------------------------------
struct ROOM_INFO
{
	int						ID;
	gak::STRING				name;
	gak::Array<PREC_POINT>	points;
	gak::Array<TABLE_INFO>	tables;
};
//---------------------------------------------------------------------------
inline double toScreen( int screenSize, double value )
{
	value = (value * screenSize) / 64000;

	return value;
}
//---------------------------------------------------------------------------
inline double toNormal( int screenSize, double value )
{
	value = (value * 64000) / screenSize;

	return value;
}
//---------------------------------------------------------------------------
inline void makePoints( const TABLE_INFO &theTable, TPoint polyLine[5] )
{
	polyLine[0].x = theTable.left;
	polyLine[0].y = theTable.top;
	polyLine[1].x = theTable.right;
	polyLine[1].y = theTable.top;
	polyLine[2].x = theTable.right;
	polyLine[2].y = theTable.bottom;
	polyLine[3].x = theTable.left;
	polyLine[3].y = theTable.bottom;
	polyLine[4].x = theTable.left;
	polyLine[4].y = theTable.top;
}
//---------------------------------------------------------------------------
inline bool isInRect( const TPoint &mousePos, const TABLE_INFO &theTable )
{
	doEnterFunction("isInRect( const TPoint &mousePos, const TABLE_INFO &theTable )");

	bool result = true;

	doLogValue( mousePos.x );
	doLogValue( mousePos.y );
	doLogValue( theTable.top );
	doLogValue( theTable.bottom );
	doLogValue( theTable.left );
	doLogValue( theTable.right );

	if( mousePos.y < (int)(theTable.top-0.5) )
	{
		doLogPosition();
		result = false;
	}
	else if( mousePos.y > (int)(theTable.bottom+0.5) )
	{
		doLogPosition();
		result = false;
	}
	else if( mousePos.x < (int)(theTable.left-0.5) )
	{
		doLogPosition();
		result = false;
	}
	else if( mousePos.x > (int)(theTable.right+0.5) )
	{
		doLogPosition();
		result = false;
	}

	doLogValue( result );
	return result;
}
//---------------------------------------------------------------------------
inline bool isInRect( const TABLE_INFO &theTable, const TABLE_INFO &theCombiTable )
{
	doEnterFunction("isInRect( const TABLE_INFO &theTable, const TABLE_INFO &theCombiTable )");

	TPoint	polyLine[5];
	bool	result = true;

	makePoints( theTable, polyLine );
	for( size_t i=0; i<4; i++ )
	{
		result = isInRect( polyLine[i], theCombiTable );
		if( !result )
/*v*/		break;
	}

	doLogValue( result );
	return result;
}

//---------------------------------------------------------------------------
class TGasthausDataModule : public TDataModule
{
__published:	// IDE-managed Components
	TTable *RoomTable;
	TIntegerField *RoomTableID;
	TStringField *RoomTableNAME;
	TTable *TableTable;
	TIntegerField *TableTableID;
	TIntegerField *TableTableRAUM;
	TStringField *TableTableTISCH;
	TStringField *TableTablePERSONEN;
	TIntegerField *TableTableLEFT_POS;
	TIntegerField *TableTableRIGHT_POS;
	TIntegerField *TableTableTOP_POS;
	TIntegerField *TableTableBOTTOM_POS;
	TIntegerField *TableTableSHAPE;
	TTable *PointTable;
	TIntegerField *PointTableRAUM;
	TIntegerField *PointTableNUMMER;
	TIntegerField *PointTableX_POS;
	TIntegerField *PointTableY_POS;
private:	// User declarations
	gak::Array<ROOM_INFO>	rooms;
public:		// User declarations
	__fastcall TGasthausDataModule(TComponent* Owner);

	void OpenRoom( void )
	{
		try
		{
			RoomTable->Open();
		}
		catch( ... )
		{
			RoomTable->IndexName = "RAUM_NAME_IDX";
			RoomTable->Open();
		}
	}
	void OpenPoints( int roomID )
	{
		AnsiString	filter;

		filter.sprintf( "RAUM=%d", roomID );
		PointTable->Filter = filter;
		PointTable->Filtered = true;

		PointTable->Open();
	}
	void OpenTables( int roomID )
	{
		AnsiString	filter;

		filter.sprintf( "RAUM=%d", roomID );
		TableTable->Filter = filter;
		TableTable->Filtered = true;

		TableTable->Open();
	}
	void loadTableUsage(
		int roomIdx,
		TDate selDatum,
		TTime selStartTime, TTime selEndTime,
		int selId,
		bool forTableSelect
	);
	void loadRooms(
		TComboBox *ComboBoxRooms, int painBoxWidth, int paintBoxHeight
	);
	void loadTables(
		int roomIdx, TComboBox *ComboBoxTable, int paintBoxWidth, int paintBoxHeight
	);
	void loadTables(
		int roomIdx,
		TComboBox *ComboBoxTable, int paintBoxWidth, int paintBoxHeight,
		TDate selDatum,
		TTime selStartTime, TTime selEndTime,
		int selId
	);
	gak::Array<ROOM_INFO> &getRooms( void )
	{
		return rooms;
	}
	int getRoomID( int roomIdx )
	{
		return rooms[roomIdx].ID;
	}
	int getRoomForTable( int tableID );
	int findRoom( int roomID );
	int findRoomForTable( int tableID )
	{
		return findRoom( getRoomForTable( tableID ) );
	}
	int getFreePlaces(
		int roomIdx, int tableID,
		TDate selDatum,
		TTime selStartTime, TTime selEndTime,
		int selId
	);
	int getReservations(
		int roomIdx,
		TDate selDatum,
		TTime selStartTime, TTime selEndTime,
		int selId
	);
};
//---------------------------------------------------------------------------
extern PACKAGE TGasthausDataModule *GasthausDataModule;
//---------------------------------------------------------------------------
#endif
