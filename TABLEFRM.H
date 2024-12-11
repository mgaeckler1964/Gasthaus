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
#ifndef TableFrmH
#define TableFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TTableForm : public TForm
{
__published:	// IDE-managed Components
	TDataSource *RoomSource;
	TTable *RoomTable;
	TDataSource *TableSource;
	TTable *TableTable;
	TPanel *Panel1;
	TPanel *Panel2;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TPanel *Panel3;
	TPanel *Panel4;
	TDBNavigator *DBNavigator2;
	TDBGrid *DBGrid2;
	TIntegerField *RoomTableID;
	TStringField *RoomTableNAME;
	TIntegerField *TableTableID;
	TIntegerField *TableTableRAUM;
	TStringField *TableTableTISCH;
	TStringField *TableTablePERSONEN;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TableTableAfterInsert(TDataSet *DataSet);
	void __fastcall TableTablePostError(TDataSet *DataSet, EDatabaseError *E,
          TDataAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TTableForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTableForm *TableForm;
//---------------------------------------------------------------------------
#endif
