object TableForm: TTableForm
  Left = 558
  Top = 246
  Width = 749
  Height = 604
  Caption = 'Tische'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 209
    Height = 577
    Align = alLeft
    Caption = 'Panel1'
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 207
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object DBNavigator1: TDBNavigator
        Left = 8
        Top = 8
        Width = 136
        Height = 25
        DataSource = RoomSource
        VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
        TabOrder = 0
      end
    end
    object DBGrid1: TDBGrid
      Left = 1
      Top = 42
      Width = 207
      Height = 534
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
  end
  object Panel3: TPanel
    Left = 209
    Top = 0
    Width = 532
    Height = 577
    Align = alClient
    TabOrder = 1
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 530
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object DBNavigator2: TDBNavigator
        Left = 8
        Top = 8
        Width = 240
        Height = 25
        DataSource = TableSource
        TabOrder = 0
      end
    end
    object DBGrid2: TDBGrid
      Left = 1
      Top = 42
      Width = 530
      Height = 534
      Align = alClient
      DataSource = TableSource
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'TISCH'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PERSONEN'
          Visible = True
        end>
    end
  end
  object RoomSource: TDataSource
    DataSet = RoomTable
    Left = 32
    Top = 88
  end
  object RoomTable: TTable
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
    Left = 104
    Top = 88
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
  object TableSource: TDataSource
    DataSet = TableTable
    Left = 232
    Top = 88
  end
  object TableTable: TTable
    AfterInsert = TableTableAfterInsert
    OnPostError = TableTablePostError
    DatabaseName = 'GASTHAUS'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'RAUM'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'TISCH'
        Attributes = [faRequired]
        DataType = ftString
        Size = 16
      end
      item
        Name = 'PERSONEN'
        Attributes = [faRequired]
        DataType = ftString
        Size = 16
      end>
    IndexDefs = <
      item
        Name = 'TableTableIndex1'
        Fields = 'ID'
        Options = [ixPrimary, ixUnique]
      end
      item
        Name = 'RAUMTISCHIDX'
        Fields = 'RAUM'
        Options = [ixCaseInsensitive]
      end>
    IndexName = 'RAUMTISCHIDX'
    MasterFields = 'ID'
    MasterSource = RoomSource
    StoreDefs = True
    TableName = 'TISCH'
    UpdateMode = upWhereKeyOnly
    Left = 304
    Top = 88
    object TableTableID: TIntegerField
      FieldName = 'ID'
      Required = True
    end
    object TableTableRAUM: TIntegerField
      FieldName = 'RAUM'
      Required = True
    end
    object TableTableTISCH: TStringField
      DisplayLabel = 'Tisch'
      FieldName = 'TISCH'
      Required = True
      Size = 16
    end
    object TableTablePERSONEN: TStringField
      DisplayLabel = 'Personen'
      FieldName = 'PERSONEN'
      Required = True
      Size = 16
    end
  end
end
