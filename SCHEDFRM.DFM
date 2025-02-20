object ScheduleFrm: TScheduleFrm
  Left = 347
  Top = 263
  BorderStyle = bsDialog
  Caption = 'Feiertage, Messen, Termine'
  ClientHeight = 276
  ClientWidth = 462
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
  object Label1: TLabel
    Left = 152
    Top = 40
    Width = 16
    Height = 13
    Caption = 'Art:'
  end
  object Label2: TLabel
    Left = 152
    Top = 72
    Width = 34
    Height = 13
    Caption = 'Datum:'
  end
  object Label3: TLabel
    Left = 152
    Top = 128
    Width = 68
    Height = 13
    Caption = 'Beschreibung:'
  end
  object DBNavigator1: TDBNavigator
    Left = 8
    Top = 8
    Width = 240
    Height = 25
    DataSource = ScheduleSource
    TabOrder = 0
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 40
    Width = 145
    Height = 233
    TabStop = False
    DataSource = ScheduleSource
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Beschreibung'
        Visible = True
      end>
  end
  object DBEdit1: TDBEdit
    Left = 232
    Top = 128
    Width = 217
    Height = 21
    DataField = 'Beschreibung'
    DataSource = ScheduleSource
    TabOrder = 4
  end
  object startDatePicker: TDateTimePicker
    Left = 232
    Top = 72
    Width = 217
    Height = 21
    CalAlignment = dtaLeft
    Date = 36412.9158412847
    Time = 36412.9158412847
    DateFormat = dfLong
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 2
    OnCloseUp = startDatePickerCloseUp
  end
  object EndDatePicker: TDateTimePicker
    Left = 232
    Top = 96
    Width = 217
    Height = 21
    CalAlignment = dtaLeft
    Date = 36412.9159257407
    Time = 36412.9159257407
    DateFormat = dfLong
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 3
    OnCloseUp = EndDatePickerCloseUp
  end
  object ArtComboBox: TDBComboBox
    Left = 232
    Top = 40
    Width = 217
    Height = 21
    Style = csDropDownList
    DataField = 'Art'
    DataSource = ScheduleSource
    ItemHeight = 13
    Items.Strings = (
      'Fest'
      'Variable'
      'Zeitraum')
    TabOrder = 1
    OnChange = ArtComboBoxChange
  end
  object ScheduleSource: TDataSource
    DataSet = ScheduleTable
    Left = 256
    Top = 8
  end
  object ScheduleTable: TTable
    AfterInsert = ScheduleTableAfterInsert
    BeforePost = ScheduleTableBeforePost
    AfterScroll = ScheduleTableAfterScroll
    OnPostError = ScheduleTablePostError
    DatabaseName = 'GASTHAUS'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'ART'
        Attributes = [faRequired]
        DataType = ftString
        Size = 16
      end
      item
        Name = 'TAG'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'MONAT'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'STARTDATUM'
        Attributes = [faRequired]
        DataType = ftDateTime
      end
      item
        Name = 'ENDEDATUM'
        Attributes = [faRequired]
        DataType = ftDateTime
      end
      item
        Name = 'BESCHREIBUNG'
        Attributes = [faRequired]
        DataType = ftString
        Size = 64
      end>
    IndexDefs = <
      item
        Name = 'DATUMIDX'
        Fields = 'MONAT;TAG'
      end
      item
        Name = 'SYS_C0033641'
        Fields = 'ID'
        Options = [ixUnique]
      end>
    IndexName = 'DATUMIDX'
    StoreDefs = True
    TableName = 'TERMINE'
    UpdateMode = upWhereKeyOnly
    Left = 328
    Top = 8
    object ScheduleTableArt: TStringField
      FieldName = 'Art'
      Size = 16
    end
    object ScheduleTableTag: TSmallintField
      FieldName = 'Tag'
    end
    object ScheduleTableMonat: TSmallintField
      FieldName = 'Monat'
    end
    object ScheduleTableBeschreibung: TStringField
      FieldName = 'Beschreibung'
      Size = 64
    end
    object ScheduleTableId: TIntegerField
      FieldName = 'Id'
      Required = True
    end
    object ScheduleTableStartDatum: TDateTimeField
      FieldName = 'StartDatum'
      Required = True
    end
    object ScheduleTableEndeDatum: TDateTimeField
      FieldName = 'EndeDatum'
      Required = True
    end
  end
end
