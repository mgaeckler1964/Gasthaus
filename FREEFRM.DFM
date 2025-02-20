object FreeForm: TFreeForm
  Left = 378
  Top = 258
  Width = 350
  Height = 341
  Caption = 'Freie Tische'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 334
    Height = 261
    Align = alClient
    DataSource = DataSource1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'NAME'
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TISCH'
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PERSONEN'
        Width = 80
        Visible = True
      end>
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 334
    Height = 41
    Align = alTop
    TabOrder = 1
    object Button1: TButton
      Left = 8
      Top = 8
      Width = 153
      Height = 25
      Caption = 'Neue Reservierung'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 168
      Top = 8
      Width = 153
      Height = 25
      Caption = 'Neu Laden'
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object FreeQuery: TQuery
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      'select distinct rx.name, tx.tisch, tx.personen, tx.id'
      'from raum rx, tisch tx'
      'where tx.raum = rx.id'
      ' '
      ' ')
    Left = 24
    Top = 48
    object FreeQueryNAME: TStringField
      DisplayLabel = 'Name'
      FieldName = 'NAME'
      Origin = '"raum.DB".NAME'
      Size = 255
    end
    object FreeQueryTISCH: TStringField
      DisplayLabel = 'Tisch'
      FieldName = 'TISCH'
      Origin = '"raum.DB".NAME'
      Size = 16
    end
    object FreeQueryPERSONEN: TStringField
      DisplayLabel = 'Personenzahl'
      FieldName = 'PERSONEN'
      Origin = '"raum.DB".NAME'
      Size = 16
    end
    object FreeQueryID: TIntegerField
      FieldName = 'id'
    end
  end
  object DataSource1: TDataSource
    DataSet = FreeQuery
    Left = 88
    Top = 48
  end
end
