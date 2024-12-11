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
