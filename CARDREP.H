//---------------------------------------------------------------------------
#ifndef CardRepH
#define CardRepH
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
class TCardReport : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *QuickRep;
	TQRBand *QRBand1;
	TQRLabel *QRLabel1;
	TQuery *Query;
	TQRDBText *QRDBText1;
	TQRDBText *QRDBText2;
	TQRLabel *QRLabel2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRDBText *QRDBText7;
	TQRDBText *QRDBText8;
	TQRImage *ImageHeader;
private:	// User declarations
public:		// User declarations
	__fastcall TCardReport(TComponent* Owner);
	void setSqlText( const TQuery *source );
	void setSqlText( int reservationId );
	void previewReport( int cardId = 0 );
};
//---------------------------------------------------------------------------
extern PACKAGE TCardReport *CardReport;
//---------------------------------------------------------------------------
#endif
