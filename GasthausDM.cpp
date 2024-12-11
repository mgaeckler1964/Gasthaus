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

#include "GasthausDM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGasthausDataModule *GasthausDataModule;
//---------------------------------------------------------------------------
__fastcall TGasthausDataModule::TGasthausDataModule(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void TGasthausDataModule::loadRooms(
	TComboBox *ComboBoxRooms, int paintBoxWidth, int paintBoxHeight
)
{
	ComboBoxRooms->Items->Clear();
	rooms.clear();

	for(
		OpenRoom();
		!RoomTable->Eof;
		RoomTable->Next()
	)
	{
		ROOM_INFO	newInfo;

		newInfo.ID = RoomTableID->AsInteger;
		newInfo.name = RoomTableNAME->AsString.c_str();

		if( paintBoxWidth && paintBoxHeight )
		{
			newInfo.points.clear();

			for(
				OpenPoints( newInfo.ID );
				!PointTable->Eof;
				PointTable->Next()
			)
			{
				PREC_POINT	newPoint;

				newPoint.x = toScreen( paintBoxWidth, PointTableX_POS->AsInteger );
				newPoint.y = toScreen( paintBoxHeight, PointTableY_POS->AsInteger );

				newInfo.points.addElement( newPoint );
			}
			PointTable->Close();
		}

		rooms.addElement( newInfo );

		ComboBoxRooms->Items->Add( RoomTableNAME->AsString );
	}
	RoomTable->Close();
}
//---------------------------------------------------------------------------
void TGasthausDataModule::loadTables(
	int roomIdx, TComboBox *ComboBoxTable, int paintBoxWidth, int paintBoxHeight
)
{
	ROOM_INFO	&theRoom = rooms[roomIdx];

	if( !theRoom.tables.size() )
	{
		TABLE_INFO	tableInfo;

		for(
			OpenTables( theRoom.ID );
			!TableTable->Eof;
			TableTable->Next()
		)
		{
			tableInfo.ID = TableTableID->AsInteger;
			tableInfo.name = TableTableTISCH->AsString.c_str();
			tableInfo.personenStr = TableTablePERSONEN->AsString.c_str();
			tableInfo.besetzt = 0;
			tableInfo.personenI = atoi( tableInfo.personenStr );
			tableInfo.shape = (TABLE_SHAPE)TableTableSHAPE->AsInteger;
			if( paintBoxWidth && paintBoxHeight )
			{
				tableInfo.left = toScreen(
					paintBoxWidth, TableTableLEFT_POS->AsInteger
				);
				tableInfo.top = toScreen(
					paintBoxHeight, TableTableTOP_POS->AsInteger
				);
				tableInfo.right = toScreen(
					paintBoxWidth, TableTableRIGHT_POS->AsInteger
				);
				tableInfo.bottom = toScreen(
					paintBoxHeight, TableTableBOTTOM_POS->AsInteger
				);
			}
			else
			{
				tableInfo.left = TableTableLEFT_POS->AsInteger;
				tableInfo.top = TableTableTOP_POS->AsInteger;
				tableInfo.right = TableTableRIGHT_POS->AsInteger;
				tableInfo.bottom = TableTableBOTTOM_POS->AsInteger;
			}

			theRoom.tables.addElement( tableInfo );

		}
		TableTable->Close();
	}

	if( ComboBoxTable )
	{
		ComboBoxTable->Items->Clear();
		for( size_t i=0; i<theRoom.tables.size(); i++ )
		{
			const TABLE_INFO	&tableInfo = theRoom.tables[i];
			ComboBoxTable->Items->Add( (const char *)tableInfo.name );
		}

		ComboBoxTable->ItemIndex = 0;
	}
}
//---------------------------------------------------------------------------

void TGasthausDataModule::loadTableUsage(
	int roomIdx,
	TDate selDatum,
	TTime selStartTime, TTime selEndTime,
	int selId,
	bool forTableSelect
)
{
	ROOM_INFO	&theRoom = rooms[roomIdx];

	TQuery	*checkSQL = new TQuery( this );
	checkSQL->DatabaseName = "Gasthaus";
	checkSQL->SQL->Add(
		"select UHRZEIT, ENDE, PERSONEN, ID, KOMPLETTER_RAUM "
		"from RESERVAT "
		"where TISCH=:theTableId "
		"and DATUM=:selDate "
		"and STATUS<>'Storniert' "
	);


	TDateTime	selStartDateTime = selDatum + selStartTime;
	TDateTime	selEndDateTime = selDatum + selEndTime;

	if( selEndDateTime < selStartDateTime )
		selEndDateTime += 1.0;

	for(
		size_t tableIdx=0;
		tableIdx<theRoom.tables.size();
		tableIdx++
	)
	{
		TABLE_INFO	&tableInfo = theRoom.tables[tableIdx];

		tableInfo.besetzt = 0;
	}
	for(
		size_t tableIdx=0;
		tableIdx<theRoom.tables.size();
		tableIdx++
	)
	{
		TABLE_INFO	&tableInfo = theRoom.tables[tableIdx];

		checkSQL->Params->Items[0]->AsInteger = tableInfo.ID;
		checkSQL->Params->Items[1]->AsDate = selDatum;
		for(
			checkSQL->Open();
			!checkSQL->Eof;
			checkSQL->Next()
		)
		{
			int id = checkSQL->Fields->Fields[3]->AsInteger;

			if( id != selId )
			{
				TDateTime	tableStartDateTime = selDatum + checkSQL->Fields->Fields[0]->AsDateTime;
				TDateTime	tableEndDateTime = selDatum + checkSQL->Fields->Fields[1]->AsDateTime;
				if( tableEndDateTime < tableStartDateTime )
					tableEndDateTime += 1.0;

				if( tableEndDateTime < selStartDateTime )
/*^*/				continue;
				if( tableStartDateTime > selEndDateTime )
/*^*/				continue;

				AnsiString	entireRoomStr = checkSQL->Fields->Fields[4]->AsString;
				bool		entireRoom = (entireRoomStr == "T");
				if( entireRoom )
				{
					if( forTableSelect )
					{
						for(
							size_t tableIdx=0;
							tableIdx<theRoom.tables.size();
							tableIdx++
						)
						{
							TABLE_INFO	&tableInfo = theRoom.tables[tableIdx];
							tableInfo.besetzt += checkSQL->Fields->Fields[2]->AsInteger;
						}
					}
					else
						tableInfo.besetzt += checkSQL->Fields->Fields[2]->AsInteger;
				}
				else if( tableInfo.shape == COMBI_TABLE )
				{
					tableInfo.besetzt += checkSQL->Fields->Fields[2]->AsInteger;
					if( forTableSelect )
					{
						for(
							size_t tableIdx=0;
							tableIdx<theRoom.tables.size();
							tableIdx++
						)
						{
							TABLE_INFO	&subTableInfo = theRoom.tables[tableIdx];
							if( subTableInfo.shape != COMBI_TABLE
							&& isInRect( subTableInfo, tableInfo ) )
								subTableInfo.besetzt += checkSQL->Fields->Fields[2]->AsInteger;
						}
					}
				}
				else
				{
					tableInfo.besetzt += checkSQL->Fields->Fields[2]->AsInteger;
					if( forTableSelect )
					{
						for(
							size_t tableIdx=0;
							tableIdx<theRoom.tables.size();
							tableIdx++
						)
						{
							TABLE_INFO	&subTableInfo = theRoom.tables[tableIdx];
							doLogValue( subTableInfo.name );
							if( subTableInfo.shape == COMBI_TABLE
							&&  isInRect( tableInfo, subTableInfo ) )
							{
								doLogValue( subTableInfo.besetzt );
								if( !subTableInfo.personenI )
									subTableInfo.besetzt += checkSQL->Fields->Fields[2]->AsInteger;
								else
									subTableInfo.besetzt = subTableInfo.personenI;
								doLogValue( subTableInfo.besetzt );
							}
						}
					}
				}
			}
		}
		checkSQL->Close();
	}

	delete checkSQL;
}
//---------------------------------------------------------------------------
void TGasthausDataModule::loadTables(
	int roomIdx,
	TComboBox *ComboBoxTable, int paintBoxWidth, int paintBoxHeight,
	TDate selDatum,
	TTime selStartTime, TTime selEndTime,
	int selId
)
{
	bool		loadUsage;
	ROOM_INFO	&theRoom = rooms[roomIdx];

	loadUsage = !theRoom.tables.size();
	if( loadUsage || ComboBoxTable )
		loadTables( roomIdx, ComboBoxTable, paintBoxWidth, paintBoxHeight );
	if( loadUsage )
	{
		loadTableUsage(
			roomIdx,
			selDatum,
			selStartTime, selEndTime,
			selId,
			true
		);
	}
}
//---------------------------------------------------------------------------
int TGasthausDataModule::getRoomForTable( int tableID )
{
	TQuery	*theQuery;
	int		roomID = 0;

	theQuery = new TQuery( Application );
	if( theQuery )
	{
		theQuery->DatabaseName = "GASTHAUS";
		theQuery->UniDirectional = true;
		theQuery->RequestLive = false;

		theQuery->SQL->Add(
			"select raum from tisch where id = :theTable"
		);
		theQuery->Params->Items[0]->AsInteger = tableID;

		theQuery->Open();
		if( !theQuery->Eof )
			roomID = theQuery->Fields->Fields[0]->AsInteger;

		theQuery->Close();

		delete theQuery;
	}

	return roomID;
}
//---------------------------------------------------------------------------
int TGasthausDataModule::findRoom( int roomID )
{
	int roomIdx;
	for( roomIdx=rooms.size()-1; roomIdx >= 0; roomIdx-- )
	{
		ROOM_INFO	&theRoom = rooms[roomIdx];
		if( theRoom.ID == roomID )
/*v*/		break;
	}

	return roomIdx;
}
//---------------------------------------------------------------------------
int TGasthausDataModule::getFreePlaces(
	int roomIdx, int tableID,
	TDate selDatum,
	TTime selStartTime, TTime selEndTime,
	int selId
)
{
	int freeSpace = 0;

	loadTables( roomIdx, NULL, 0, 0 );
	loadTableUsage( roomIdx, selDatum, selStartTime, selEndTime, selId, true );
	ROOM_INFO	&theRoom = rooms[roomIdx];
	for( size_t tableIdx = 0; tableIdx < theRoom.tables.size(); tableIdx++ )
	{
		const TABLE_INFO &theTable = theRoom.tables[tableIdx];
		if( theTable.ID == tableID )
		{
			if( theTable.personenI )
			{
				freeSpace = theTable.personenI - theTable.besetzt;
				if( freeSpace < 0 )
					freeSpace = 0;
			}
			else
				freeSpace = -1;
			break;
		}
	}

	return freeSpace;
}
//---------------------------------------------------------------------------
int TGasthausDataModule::getReservations(
	int roomIdx,
	TDate selDatum,
	TTime selStartTime, TTime selEndTime,
	int selId
)
{
	int	numPersons = 0;

	loadTables( roomIdx, NULL, 0, 0 );
	loadTableUsage( roomIdx, selDatum, selStartTime, selEndTime, selId, false );
	ROOM_INFO	&theRoom = rooms[roomIdx];
	for( size_t tableIdx = 0; tableIdx < theRoom.tables.size(); tableIdx++ )
	{
		const TABLE_INFO &theTable = theRoom.tables[tableIdx];
		numPersons += theTable.besetzt;
	}

	return numPersons;
}
//---------------------------------------------------------------------------

