object RoomForm: TRoomForm
  Left = 610
  Top = 378
  Width = 311
  Height = 293
  Caption = 'Räume'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 303
    Height = 41
    Align = alTop
    TabOrder = 0
    object DBNavigator1: TDBNavigator
      Left = 8
      Top = 8
      Width = 240
      Height = 25
      DataSource = RoomSource
      TabOrder = 0
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 303
    Height = 225
    Align = alClient
    DataSource = RoomSource
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'NAME'
        Visible = True
      end>
  end
  object RoomSource: TDataSource
    DataSet = RoomTable
    Left = 16
    Top = 64
  end
  object RoomTable: TTable
    AfterInsert = RoomTableAfterInsert
    OnPostError = RoomTablePostError
    DatabaseName = 'GASTHAUS'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NAME'
        Attributes = [faRequired]
        DataType = ftString
        Size = 255
      end>
    IndexDefs = <
      item
        Name = 'RoomTableIndex1'
        Fields = 'ID'
        Options = [ixPrimary, ixUnique]
      end
      item
        Name = 'NAME'
        Fields = 'NAME'
      end>
    IndexName = 'NAME'
    StoreDefs = True
    TableName = 'RAUM'
    UpdateMode = upWhereKeyOnly
    Left = 56
    Top = 64
    object RoomTableID: TIntegerField
      FieldName = 'ID'
      Required = True
    end
    object RoomTableNAME: TStringField
      DisplayLabel = 'Name'
      FieldName = 'NAME'
      Required = True
      Size = 255
    end
  end
end
