object ConfigForm: TConfigForm
  Left = 672
  Top = 169
  BorderStyle = bsDialog
  Caption = 'Optionen'
  ClientHeight = 360
  ClientWidth = 458
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 14
    Width = 48
    Height = 13
    Caption = 'Listenlogo'
  end
  object Label2: TLabel
    Left = 8
    Top = 78
    Width = 37
    Height = 13
    Caption = 'Doppelt'
  end
  object Label3: TLabel
    Left = 8
    Top = 110
    Width = 41
    Height = 13
    Caption = 'Komplett'
  end
  object Label4: TLabel
    Left = 8
    Top = 206
    Width = 62
    Height = 13
    Caption = 'Nicht erledigt'
  end
  object Label5: TLabel
    Left = 8
    Top = 46
    Width = 51
    Height = 13
    Caption = 'Kartenlogo'
  end
  object Label6: TLabel
    Left = 8
    Top = 174
    Width = 31
    Height = 13
    Caption = 'Option'
  end
  object Label7: TLabel
    Left = 8
    Top = 300
    Width = 60
    Height = 13
    Caption = 'Stammtische'
  end
  object Label8: TLabel
    Left = 8
    Top = 142
    Width = 37
    Height = 13
    Caption = 'Tagung'
  end
  object Label9: TLabel
    Left = 8
    Top = 238
    Width = 39
    Height = 13
    Caption = 'Storniert'
  end
  object Label10: TLabel
    Left = 8
    Top = 270
    Width = 39
    Height = 13
    Caption = 'Berichte'
  end
  object ListLogoEdit: TEdit
    Left = 80
    Top = 10
    Width = 265
    Height = 21
    TabOrder = 0
  end
  object ButtonBrowseListLogo: TButton
    Left = 352
    Top = 8
    Width = 97
    Height = 25
    Caption = '&Durchsuchen...'
    TabOrder = 1
    OnClick = ButtonBrowseListLogoClick
  end
  object ButtonOK: TButton
    Left = 8
    Top = 328
    Width = 75
    Height = 25
    Caption = '&OK'
    Default = True
    ModalResult = 1
    TabOrder = 18
    OnClick = ButtonOKClick
  end
  object ButtonSelectDouble: TButton
    Left = 352
    Top = 72
    Width = 97
    Height = 25
    Caption = '&W�hlen...'
    TabOrder = 5
    OnClick = ButtonSelectDoubleClick
  end
  object ButtonSelectComplete: TButton
    Left = 352
    Top = 104
    Width = 97
    Height = 25
    Caption = 'W�&hlen...'
    TabOrder = 7
    OnClick = ButtonSelectCompleteClick
  end
  object ButtonSelectNotOK: TButton
    Left = 352
    Top = 200
    Width = 97
    Height = 25
    Caption = 'W�hle&n...'
    TabOrder = 13
    OnClick = ButtonSelectNotOKClick
  end
  object doubleEdit: TEdit
    Left = 80
    Top = 74
    Width = 265
    Height = 21
    TabStop = False
    Enabled = False
    ReadOnly = True
    TabOrder = 4
  end
  object completeEdit: TEdit
    Left = 80
    Top = 106
    Width = 265
    Height = 21
    TabStop = False
    Enabled = False
    ReadOnly = True
    TabOrder = 6
  end
  object notOkEdit: TEdit
    Left = 80
    Top = 202
    Width = 265
    Height = 21
    TabStop = False
    Enabled = False
    ReadOnly = True
    TabOrder = 12
  end
  object ButtonCancel: TButton
    Left = 88
    Top = 328
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'A&bbruch'
    ModalResult = 2
    TabOrder = 19
  end
  object ButtonBrowseCardLogo: TButton
    Left = 352
    Top = 40
    Width = 97
    Height = 25
    Caption = 'D&urchsuchen...'
    TabOrder = 3
    OnClick = ButtonBrowseCardLogoClick
  end
  object CardLogoEdit: TEdit
    Left = 80
    Top = 42
    Width = 265
    Height = 21
    TabOrder = 2
  end
  object ButtonSelectOption: TButton
    Left = 352
    Top = 168
    Width = 97
    Height = 25
    Caption = 'W�hl&en...'
    TabOrder = 11
    OnClick = ButtonSelectOptionClick
  end
  object optionEdit: TEdit
    Left = 80
    Top = 170
    Width = 265
    Height = 21
    TabStop = False
    Enabled = False
    ReadOnly = True
    TabOrder = 10
  end
  object StammtischEdit: TEdit
    Left = 80
    Top = 296
    Width = 121
    Height = 21
    TabOrder = 17
  end
  object ConferenceEdit: TEdit
    Left = 80
    Top = 138
    Width = 265
    Height = 21
    TabStop = False
    Enabled = False
    ReadOnly = True
    TabOrder = 8
  end
  object ButtonSelectConference: TButton
    Left = 352
    Top = 136
    Width = 97
    Height = 25
    Caption = 'W�h&len...'
    TabOrder = 9
    OnClick = ButtonSelectConferenceClick
  end
  object DeletedEdit: TEdit
    Left = 80
    Top = 234
    Width = 265
    Height = 21
    TabStop = False
    Enabled = False
    ReadOnly = True
    TabOrder = 14
  end
  object ButtonSelectDeleted: TButton
    Left = 352
    Top = 232
    Width = 97
    Height = 25
    Caption = 'W�hle&n...'
    TabOrder = 15
    OnClick = ButtonSelectDeletedClick
  end
  object EditReports: TEdit
    Left = 80
    Top = 266
    Width = 265
    Height = 21
    TabOrder = 16
  end
  object OpenPictureDlg: TOpenPictureDialog
    Filter = 
      'All (*.bmp;*.ico;*.emf;*.wmf)|*.bmp;*.ico;*.emf;*.wmf|Bitmaps (*' +
      '.bmp)|*.bmp|Icons (*.ico)|*.ico|Enhanced Metafiles (*.emf)|*.emf' +
      '|Metafiles (*.wmf)|*.wmf'
    Left = 224
    Top = 232
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    Left = 176
    Top = 232
  end
end
