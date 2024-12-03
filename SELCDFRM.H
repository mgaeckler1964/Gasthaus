//---------------------------------------------------------------------------
#ifndef SelCdFrmH
#define SelCdFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSelCardForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button3;
	TButton *Button5;
	TButton *Button7;
	TButton *Button9;
	TButton *Button2;
	TButton *Button4;
	TButton *Button6;
	TButton *Button8;
	TButton *Button10;
	TButton *Button11;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
private:	// User declarations
	int	reservationId;

	void printCard( int cardId );
public:		// User declarations
	__fastcall TSelCardForm(TComponent* Owner);

	void selectCard( int reservationId )
	{
		this->reservationId = reservationId;
		ShowModal();
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TSelCardForm *SelCardForm;
//---------------------------------------------------------------------------
#endif
