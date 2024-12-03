//---------------------------------------------------------------------
#include <stdio.h>

#include <vcl.h>
#pragma hdrstop

#include "AboutFrm.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------


void __fastcall TAboutBox::FormCreate(TObject *)
{
	DWORD	dummy1, versionInfoSize;
	UINT	dummy2;
	char	tmpBuffer[128];

	Caption = Application->Title;
	ProductName->Caption = Application->Title;
	versionInfoSize = GetFileVersionInfoSize(
		Application->ExeName.c_str(), &dummy1
	);
	if( versionInfoSize )
	{
		void *data = malloc( versionInfoSize );
		if( data )
		{
			VS_FIXEDFILEINFO	*fixedFileInfo;

			GetFileVersionInfo( Application->ExeName.c_str(), 0L, versionInfoSize, data );
			if( VerQueryValue( data, "\\", (void **)&fixedFileInfo, &dummy2 ) )
			{
				sprintf(
					tmpBuffer,
					"%u.%u.%u.%u",
					(unsigned int)(fixedFileInfo->dwFileVersionMS >> 16),
					(unsigned int)(fixedFileInfo->dwFileVersionMS & 0xFFFF),
					(unsigned int)(fixedFileInfo->dwFileVersionLS >> 16),
					(unsigned int)(fixedFileInfo->dwFileVersionLS & 0xFFFF)
				);
				Version->Caption = tmpBuffer;
			}
			free( data );
		}
	}
}
//---------------------------------------------------------------------------

