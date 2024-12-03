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
