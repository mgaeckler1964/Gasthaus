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
