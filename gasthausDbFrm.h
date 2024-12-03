//---------------------------------------------------------------------------

#ifndef gasthausDbFrmH
#define gasthausDbFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "dbConvertFrm.h"
//---------------------------------------------------------------------------
class TGasthausDbForm : public TDbConvertForm
{
__published:	// Von der IDE verwaltete Komponenten
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
	__fastcall TGasthausDbForm(TComponent* Owner);
	virtual const char *getAliasName( void ) const;
};
//---------------------------------------------------------------------------
extern PACKAGE TGasthausDbForm *GasthausDbForm;
//---------------------------------------------------------------------------
#endif
