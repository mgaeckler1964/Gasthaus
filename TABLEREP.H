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
#ifndef TableRepH
#define TableRepH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <quickrpt.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TTableReport : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *QuickRep;
	TQuery *Query;
	TQRBand *bData;
	TQRDBText *fName;
	TQRDBText *fDatum;
	TQRDBText *fRoom;
	TQRDBText *fTime;
	TQRDBText *fPersons;
	TQRDBText *fTable;
	TQRDBText *fStatus;
	TQRDBText *fReason;
	TQRDBText *fIntBemerk;
	TQRBand *bPageFooter;
	TQRLabel *QRLabel11;
	TQRSysData *QRSysData1;
	TQRDBText *fExtBemerk;
	TQRBand *bPageHeader;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabel5;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel6;
	TQRLabel *QRLabel7;
	TQRLabel *QRLabel8;
	TQRLabel *QRLabel9;
	TQRLabel *QRLabel2;
	TQRLabel *QRLabel3;
	TQRBand *bSummary;
	TQRExpr *QRExpr1;
	TQRLabel *QRLabel10;
	TQRImage *ImageHeader;
	TQRDBText *fFuncStatus;
	TQRLabel *QRLabel12;
	TQRLabel *QRLabel13;
private:	// User declarations
public:		// User declarations
	__fastcall TTableReport(TComponent* Owner);
	void setSqlText( const TQuery *source );
	void previewReport( void );
};
//---------------------------------------------------------------------------
extern PACKAGE TTableReport *TableReport;
//---------------------------------------------------------------------------
#endif
