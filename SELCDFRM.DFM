object SelCardForm: TSelCardForm
  Left = 629
  Top = 179
  BorderStyle = bsDialog
  Caption = 'Tischkarte drucken'
  ClientHeight = 205
  ClientWidth = 189
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 16
    Top = 8
    Width = 75
    Height = 25
    Caption = '1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button3: TButton
    Left = 16
    Top = 40
    Width = 75
    Height = 25
    Caption = '3'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button5: TButton
    Left = 16
    Top = 72
    Width = 75
    Height = 25
    Caption = '5'
    TabOrder = 4
    OnClick = Button5Click
  end
  object Button7: TButton
    Left = 16
    Top = 104
    Width = 75
    Height = 25
    Caption = '7'
    TabOrder = 6
    OnClick = Button7Click
  end
  object Button9: TButton
    Left = 16
    Top = 136
    Width = 75
    Height = 25
    Caption = '9'
    TabOrder = 8
    OnClick = Button9Click
  end
  object Button2: TButton
    Left = 96
    Top = 8
    Width = 75
    Height = 25
    Caption = '2'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button4: TButton
    Left = 96
    Top = 40
    Width = 75
    Height = 25
    Caption = '4'
    TabOrder = 3
    OnClick = Button4Click
  end
  object Button6: TButton
    Left = 96
    Top = 72
    Width = 75
    Height = 25
    Caption = '6'
    TabOrder = 5
    OnClick = Button6Click
  end
  object Button8: TButton
    Left = 96
    Top = 104
    Width = 75
    Height = 25
    Caption = '8'
    TabOrder = 7
    OnClick = Button8Click
  end
  object Button10: TButton
    Left = 96
    Top = 136
    Width = 75
    Height = 25
    Caption = '10'
    TabOrder = 9
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 57
    Top = 168
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Schlie�en'
    ModalResult = 2
    TabOrder = 10
  end
end
