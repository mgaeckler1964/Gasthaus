//---------------------------------------------------------------------------
#ifndef ConfFrmH
#define ConfFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TConfigForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *ListLogoEdit;
	TButton *ButtonBrowseListLogo;
	TOpenPictureDialog *OpenPictureDlg;
	TButton *ButtonOK;
	TColorDialog *ColorDialog;
	TButton *ButtonSelectComplete;
	TButton *ButtonSelectNotOK;
	TButton *ButtonSelectDouble;
	TEdit *doubleEdit;
	TLabel *Label2;
	TEdit *completeEdit;
	TLabel *Label3;
	TEdit *notOkEdit;
	TLabel *Label4;
	TButton *ButtonCancel;
	TButton *ButtonBrowseCardLogo;
	TEdit *CardLogoEdit;
	TLabel *Label5;
	TButton *ButtonSelectOption;
	TEdit *optionEdit;
	TLabel *Label6;
	TEdit *StammtischEdit;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *ConferenceEdit;
	TButton *ButtonSelectConference;
	TLabel *Label9;
	TEdit *DeletedEdit;
	TButton *ButtonSelectDeleted;
	TLabel *Label10;
	TEdit *EditReports;
	void __fastcall ButtonBrowseListLogoClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonOKClick(TObject *Sender);
	
	void __fastcall ButtonSelectDoubleClick(TObject *Sender);
	void __fastcall ButtonSelectCompleteClick(TObject *Sender);
	void __fastcall ButtonSelectNotOKClick(TObject *Sender);
	void __fastcall ButtonBrowseCardLogoClick(TObject *Sender);
	void __fastcall ButtonSelectOptionClick(TObject *Sender);
	void __fastcall ButtonSelectConferenceClick(TObject *Sender);
	void __fastcall ButtonSelectDeletedClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TConfigForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
