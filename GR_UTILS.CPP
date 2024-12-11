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

#include <stdio.h>
#include <vcl.h>
#include <dbtables.hpp>

#pragma hdrstop

#include "gr_utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

static void nextMonth( unsigned short *year, unsigned short *month )
{
	(*month)++;
	if( *month > 12 )
	{
		*month = 1;
		(*year)++;
	}
}

static TDateTime nextMonth( TDateTime date )
{
	unsigned short	year, month, day;

	date.DecodeDate( &year, &month, &day );
	nextMonth( &year, &month );
	date = EncodeDate( year, month, day );

	return date;
}

static TDateTime nextYear( TDateTime date )
{
	unsigned short	year, month, day;

	date.DecodeDate( &year, &month, &day );
	year++;
	date = EncodeDate( year, month, day );

	return date;
}

static TDateTime findDayOfMonth( TDateTime date, int dayOfWeek )
{
	unsigned short	year, month, day;
	int				curDow;

	date.DecodeDate( &year, &month, &day );

	date = EncodeDate( year, month, 1 );

	curDow = date.DayOfWeek();
	if( curDow <= dayOfWeek )
		date += dayOfWeek - curDow;
	else
		date += 7 - (curDow-dayOfWeek);

	return date;
}

static TDateTime findDayOfMonth( TDateTime date, int counter, int dayOfWeek )
{
	if( counter > 0 )
	{
		date = findDayOfMonth( date, dayOfWeek );
		if( counter > 1 )
			date += 7*(counter-1);
	}
	else
	{
		date = findDayOfMonth( nextMonth( date ), dayOfWeek );
		date += 7*counter;
	}
	return date;
}

//---------------------------------------------------------------------------

long getNewMaxValue( const char *table, const char *field )
{
	TQuery	*maxSql;
	long	newMaxVal = 1;
	char	sqlText[256];

	maxSql = new TQuery(Application);
	if( maxSql )
	{
		maxSql->DatabaseName = "GASTHAUS";
		maxSql->UniDirectional = true;
		sprintf( sqlText, "select max(%s) from %s", field, table );
		maxSql->SQL->Add( sqlText );
		maxSql->Open();
		if( !maxSql->Eof )
		{
			newMaxVal = maxSql->Fields->Fields[0]->AsInteger;
			newMaxVal++;
		}
		maxSql->Close();

		delete maxSql;
	}

	return newMaxVal;
}

//---------------------------------------------------------------------------
static bool threadRunning = false;
static bool doTerminateThread = false;

DWORD WINAPI performGetRepeatedReservations( LPVOID _numDays )
{
	int				numDays = (int)_numDays;

	TQuery			*repResQuery;
	TQuery			*reservatQuery;
	TDateTime		today = TDateTime::CurrentDate();
	TDateTime		maxDate = today + numDays;
	TDateTime		tmpDate, lastDate;

	int				i, rc;
	int				repeatMode, WeekDay, MonthDay, Month, counter, dow;
	unsigned short	theDay, theMonth, theYear;

	long			newId;

	repResQuery = new TQuery( Application );
	if( repResQuery )
	{
		reservatQuery = new TQuery( Application );
		if( reservatQuery )
		{
			reservatQuery->DatabaseName = "GASTHAUS";
			repResQuery->DatabaseName = "GASTHAUS";

			reservatQuery->RequestLive = true;
			repResQuery->RequestLive = true;

			reservatQuery->SQL->Add( "select * from RESERVAT" );
			repResQuery->SQL->Add( "select * from STAMM "
									"where LETZTEREINTRAG is null or "
									"LETZTEREINTRAG < :maxDate" );

			repResQuery->Params->Items[0]->AsDate = maxDate;

			//reservatQuery->UniDirectional = true;
			//repResQuery->UniDirectional = true;

			reservatQuery->Open();
			repResQuery->Open();
			rc = repResQuery->RecordCount;
			for( i=0; i<rc && !doTerminateThread; i++ )
			//while( !repResQuery->Eof )		// did not work ?
			{
				if( repResQuery->FieldByName( "LetzterEintrag" )->IsNull )
					lastDate = TDateTime::CurrentDate();
				else
					lastDate = repResQuery->FieldByName( "LetzterEintrag" )->AsDateTime;

				repeatMode	= repResQuery->FieldByName( "Wiederholung" )->AsInteger;
				WeekDay		= repResQuery->FieldByName( "WochenTag" )->AsInteger;
				MonthDay	= repResQuery->FieldByName( "MonatsTag" )->AsInteger;
				Month		= repResQuery->FieldByName( "Monat" )->AsInteger;
				counter		= repResQuery->FieldByName( "Zaehler" )->AsInteger;

				while( lastDate < maxDate && !doTerminateThread )
				{
					// calculate the next ocurence of the reservation
					switch( repeatMode )
					{
						case 0:		// dayly
						{
							lastDate += 1;
							break;
						}
						case 1:		// weekly
						{
							dow = lastDate.DayOfWeek();
							if( dow < WeekDay )
								lastDate += WeekDay - dow;
							else
								lastDate += 7 - (dow-WeekDay);
							break;
						}
						case 2:		// monthly
						{
							if( !counter )
							{
								lastDate.DecodeDate( &theYear, &theMonth, &theDay );
								if( theDay >= MonthDay )
								{
									nextMonth( &theYear, &theMonth );
								}
								lastDate = EncodeDate( theYear, theMonth, (unsigned short)MonthDay );
							}
							else
							{
								tmpDate = findDayOfMonth( lastDate, counter, WeekDay );
								while( tmpDate <= lastDate || tmpDate <= today )
									tmpDate = findDayOfMonth( nextMonth( tmpDate ), counter, WeekDay );
								lastDate = tmpDate;
							}
							break;
						}
						case 3:		// jährlich
						{
							lastDate.DecodeDate( &theYear, &theMonth, &theDay );
							if( !counter )
							{
								tmpDate = EncodeDate( theYear, (unsigned short)Month, (unsigned short)MonthDay );
								if( tmpDate <= lastDate )
								{
									theYear++;
									lastDate = EncodeDate( theYear, (unsigned short)Month, (unsigned short)MonthDay );
								}
								else
									lastDate = tmpDate;
							}
							else
							{
								tmpDate = findDayOfMonth( EncodeDate( theYear, (unsigned short)Month, 1 ), counter, WeekDay );
								while( tmpDate <= lastDate || tmpDate <= today )
									tmpDate = findDayOfMonth( nextYear( tmpDate ), counter, WeekDay );
								lastDate = tmpDate;
							}
							break;
						}
					}
					if( lastDate > today )
					{
						reservatQuery->Insert();
						reservatQuery->FieldByName( "Datum" )->AsDateTime = lastDate;
						reservatQuery->FieldByName( "Uhrzeit" )->AsDateTime = repResQuery->FieldByName( "Uhrzeit" )->AsDateTime;
						reservatQuery->FieldByName( "Ende" )->AsDateTime = repResQuery->FieldByName( "Ende" )->AsDateTime;
						reservatQuery->FieldByName( "Tisch" )->AsInteger = repResQuery->FieldByName( "Tisch" )->AsInteger;
						reservatQuery->FieldByName( "Name" )->AsString = repResQuery->FieldByName( "Name" )->AsString;
						reservatQuery->FieldByName( "Personen" )->AsInteger = repResQuery->FieldByName( "Personen" )->AsInteger;
						reservatQuery->FieldByName( "Kuerzel")->AsString = repResQuery->FieldByName( "Kuerzel")->AsString;
						reservatQuery->FieldByName( "Status")->AsString = repResQuery->FieldByName( "Status")->AsString;
						reservatQuery->FieldByName( "Telefon")->AsString = repResQuery->FieldByName( "Telefon")->AsString;
						reservatQuery->FieldByName( "Anlass")->AsString = repResQuery->FieldByName( "Anlass")->AsString;
						reservatQuery->FieldByName( "Ext_Bemerk")->AsString = repResQuery->FieldByName( "Ext_Bemerk")->AsString;
						reservatQuery->FieldByName( "Int_Bemerk")->AsString = repResQuery->FieldByName( "Int_Bemerk")->AsString;
						reservatQuery->FieldByName( "Kompletter_Raum")->AsBoolean = repResQuery->FieldByName( "Kompletter_Raum")->AsBoolean;
						reservatQuery->FieldByName( "Link" )->AsInteger = -repResQuery->FieldByName( "ID")->AsInteger;

						try
						{
							newId = getNewMaxValue( "reservat", "id" );
							reservatQuery->FieldByName( "id" )->AsInteger = newId;
							reservatQuery->Post();
						}
						catch( ... )
						{
							// an exception occured try it again next time
							reservatQuery->Cancel();
							lastDate -= 1;
							break;
						}
					}
				}

				try
				{
					repResQuery->Edit();
					repResQuery->FieldByName( "LetzterEintrag" )->AsDateTime = lastDate;
					repResQuery->Post();

					repResQuery->Next();
				}
				catch( ... )
				{
					// an exception occured try it again next time
					repResQuery->Cancel();
					break;
				}
			}

			reservatQuery->Close();
			repResQuery->Close();

			delete reservatQuery;
		}
		delete repResQuery;
	}

	threadRunning = false;

	return 0;
}

void terminateThread( void )
{
	doTerminateThread = true;
}

bool isThreadRunning( void )
{
	return threadRunning;
}

void getRepeatedReservations( int numDays )
{
	// perform action in the background
	// but do not call the function twice
	DWORD	threadId;

	if( !threadRunning )
	{
		threadRunning = true;
		doTerminateThread = false;
		CreateThread( NULL, 10240, performGetRepeatedReservations, (LPVOID)numDays, 0, &threadId );
	}
}

