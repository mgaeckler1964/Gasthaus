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
#ifndef SchedFrmH
#define SchedFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TScheduleFrm : public TForm
{
__published:	// IDE-managed Components
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TDBEdit *DBEdit1;
	TDateTimePicker *startDatePicker;
	TDateTimePicker *EndDatePicker;
	TDBComboBox *ArtComboBox;
	TDataSource *ScheduleSource;
	TTable *ScheduleTable;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TStringField *ScheduleTableArt;
	TSmallintField *ScheduleTableTag;
	TSmallintField *ScheduleTableMonat;
	TStringField *ScheduleTableBeschreibung;
	TIntegerField *ScheduleTableId;
	TDateTimeField *ScheduleTableStartDatum;
	TDateTimeField *ScheduleTableEndeDatum;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ArtComboBoxChange(TObject *Sender);
	void __fastcall startDatePickerCloseUp(TObject *Sender);
	void __fastcall EndDatePickerCloseUp(TObject *Sender);
	void __fastcall ScheduleTableAfterScroll(TDataSet *DataSet);
	void __fastcall ScheduleTableAfterInsert(TDataSet *DataSet);
	void __fastcall ScheduleTableBeforePost(TDataSet *DataSet);
	void __fastcall ScheduleTablePostError(TDataSet *DataSet,
          EDatabaseError *E, TDataAction &Action);
private:	// User declarations
	void enableDisableEndDate( void );
public:		// User declarations
	__fastcall TScheduleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScheduleFrm *ScheduleFrm;
//---------------------------------------------------------------------------
#endif
