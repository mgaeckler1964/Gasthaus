object SelectForm: TSelectForm
  Left = 829
  Top = 564
  Width = 683
  Height = 352
  Caption = 'Tischauswahl'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyPress = FormKeyPress
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox: TPaintBox
    Left = 0
    Top = 41
    Width = 675
    Height = 284
    Align = alClient
    OnMouseUp = PaintBoxMouseUp
    OnPaint = PaintBoxPaint
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 675
    Height = 41
    Align = alTop
    TabOrder = 0
    object ComboBoxRooms: TComboBox
      Left = 8
      Top = 8
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = ComboBoxRoomsChange
    end
  end
end
