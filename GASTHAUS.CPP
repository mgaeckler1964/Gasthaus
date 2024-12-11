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
#include <vcl.h>
#pragma hdrstop
USERES("gasthaus.res");
USEFORM("MainFrm.cpp", MainForm);
USEFORM("EditFrm.cpp", EditForm);
USEFORM("RoomFrm.cpp", RoomForm);
USEFORM("TableFrm.cpp", TableForm);
USEFORM("SchedFrm.cpp", ScheduleFrm);
USEFORM("RepFrm.cpp", RepeatedForm);
USEFORM("GroupRep.cpp", GroupReport);
USEFORM("CardRep.cpp", CardReport);
USEFORM("SelCdFrm.cpp", SelCardForm);
USEFORM("AboutFrm.cpp", AboutBox);
USEFORM("ConfFrm.cpp", ConfigForm);
USEFORM("FreeFrm.cpp", FreeForm);
USEFORM("TableRep.cpp", TableReport);
USEFORM("ChartFrm.cpp", ChartForm);
USEUNIT("gr_utils.cpp");
USELIB("..\..\Object\gaklib\gaklib_bcb.lib");
USEFORM("SelectFrm.cpp", SelectForm);
USEFORM("DrawFrm.cpp", DrawingForm);
USEFORM("..\GAKLIB\Repository\Config.cpp", ConfigDataModule); /* TDataModule: File Type */
USEFORM("GasthausDM.cpp", GasthausDataModule); /* TDataModule: File Type */
//---------------------------------------------------------------------------
char	dbAliasName[256];
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdLine, int)
{
	strcpy(dbAliasName, cmdLine);
	try
	{
		Application->Initialize();
		Application->Title = "Gasthausreservierung";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TEditForm), &EditForm);
		Application->CreateForm(__classid(TRoomForm), &RoomForm);
		Application->CreateForm(__classid(TTableForm), &TableForm);
		Application->CreateForm(__classid(TScheduleFrm), &ScheduleFrm);
		Application->CreateForm(__classid(TRepeatedForm), &RepeatedForm);
		Application->CreateForm(__classid(TGroupReport), &GroupReport);
		Application->CreateForm(__classid(TCardReport), &CardReport);
		Application->CreateForm(__classid(TSelCardForm), &SelCardForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TConfigForm), &ConfigForm);
		Application->CreateForm(__classid(TFreeForm), &FreeForm);
		Application->CreateForm(__classid(TTableReport), &TableReport);
		Application->CreateForm(__classid(TChartForm), &ChartForm);
		Application->CreateForm(__classid(TSelectForm), &SelectForm);
		Application->CreateForm(__classid(TDrawingForm), &DrawingForm);
		Application->CreateForm(__classid(TConfigDataModule), &ConfigDataModule);
		Application->CreateForm(__classid(TGasthausDataModule), &GasthausDataModule);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
