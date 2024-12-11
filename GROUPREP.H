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
#ifndef GroupRepH
#define GroupRepH
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
class TGroupReport : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *QuickRep;
	TQuery *Query;
	TQRBand *QRBand1;
	TQRDBText *QRDBText1;
	TQRDBText *QRDBText4;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRDBText *QRDBText7;
	TQRDBText *QRDBText8;
	TQRDBText *QRDBText9;
	TQRBand *QRBand3;
	TQRLabel *QRLabel11;
	TQRSysData *QRSysData1;
	TQRDBText *QRDBText10;
	TQRBand *QRBand4;
	TQRExpr *QRExpr1;
	TQRLabel *QRLabel10;
	TQRGroup *QRGroup1;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRBand *QRBand2;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel6;
	TQRLabel *QRLabel7;
	TQRLabel *QRLabel8;
	TQRLabel *QRLabel9;
	TQRLabel *QRLabel5;
	TQRDBText *QRDBText11;
	TQRImage *ImageHeader;
	TQRLabel *QRLabel2;
private:	// User declarations
public:		// User declarations
	__fastcall TGroupReport(TComponent* Owner);
	void setSqlText( const TQuery *source );
	void previewReport( void );
};
//---------------------------------------------------------------------------
extern PACKAGE TGroupReport *GroupReport;
//---------------------------------------------------------------------------
#endif
