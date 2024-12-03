object DrawingForm: TDrawingForm
  Left = 217
  Top = 160
  Width = 683
  Height = 352
  Caption = 'Räume zeichnen'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
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
    Color = clBtnFace
    ParentColor = False
    OnMouseDown = PaintBoxMouseDown
    OnMouseMove = PaintBoxMouseMove
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
    object ComboBoxTables: TComboBox
      Left = 160
      Top = 8
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      OnChange = ResetDrawMode
    end
    object RadioButtonRoom: TRadioButton
      Left = 320
      Top = 8
      Width = 57
      Height = 17
      Caption = 'Raum'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = ResetDrawMode
    end
    object RadioButtonSquareTable: TRadioButton
      Left = 376
      Top = 8
      Width = 89
      Height = 17
      Caption = 'Recht. Tisch'
      TabOrder = 3
      OnClick = ResetDrawMode
    end
    object RadioButtonCircleTable: TRadioButton
      Left = 464
      Top = 8
      Width = 89
      Height = 17
      Caption = 'Runder Tisch'
      TabOrder = 4
      OnClick = ResetDrawMode
    end
    object RadioButtonCombiTable: TRadioButton
      Left = 552
      Top = 8
      Width = 81
      Height = 17
      Caption = 'Kombination'
      TabOrder = 5
      OnClick = ResetDrawMode
    end
  end
end
