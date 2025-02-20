object RepeatedForm: TRepeatedForm
  Left = 421
  Top = 150
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderStyle = bsDialog
  Caption = 'Stammtische'
  ClientHeight = 453
  ClientWidth = 617
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
    Left = 136
    Top = 40
    Width = 69
    Height = 13
    Caption = 'Wiederholung:'
  end
  object DayLabel: TLabel
    Left = 136
    Top = 64
    Width = 59
    Height = 13
    Caption = 'Wochentag:'
  end
  object MonthLabel: TLabel
    Left = 136
    Top = 88
    Width = 33
    Height = 13
    Caption = 'Monat:'
  end
  object Label4: TLabel
    Left = 136
    Top = 136
    Width = 81
    Height = 13
    Caption = 'Name/Personen:'
  end
  object Label5: TLabel
    Left = 136
    Top = 160
    Width = 39
    Height = 13
    Caption = 'Telefon:'
  end
  object Label6: TLabel
    Left = 136
    Top = 184
    Width = 62
    Height = 13
    Caption = 'Raum/Tisch:'
  end
  object Label7: TLabel
    Left = 136
    Top = 208
    Width = 67
    Height = 13
    Caption = 'Status/K�rzel:'
  end
  object Label8: TLabel
    Left = 136
    Top = 232
    Width = 34
    Height = 13
    Caption = 'Anlass:'
  end
  object Label9: TLabel
    Left = 136
    Top = 256
    Width = 77
    Height = 13
    Caption = 'Besonderheiten:'
  end
  object Label10: TLabel
    Left = 136
    Top = 352
    Width = 82
    Height = 13
    Caption = 'Serviceanleitung:'
  end
  object Label11: TLabel
    Left = 384
    Top = 40
    Width = 36
    Height = 13
    Caption = 'Uhrzeit:'
  end
  object Bevel1: TBevel
    Left = 136
    Top = 120
    Width = 473
    Height = 1
  end
  object DayMonthLabel: TLabel
    Left = 264
    Top = 91
    Width = 63
    Height = 13
    Caption = 'eines Monats'
  end
  object RepeatComboBox: TComboBox
    Left = 232
    Top = 40
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
    OnChange = RepeatComboBoxChange
    Items.Strings = (
      'T�glich'
      'W�chentlich'
      'Monatlich'
      'J�hrlich'
      ' ')
  end
  object WeekDayComboBox: TComboBox
    Left = 384
    Top = 64
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 4
    OnChange = WeekDayComboBoxChange
    Items.Strings = (
      'Sonntag'
      'Montag'
      'Dienstag'
      'Mittwoch'
      'Donnerstag'
      'Freitag'
      'Samstag')
  end
  object CounterComboBox: TComboBox
    Left = 232
    Top = 64
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 3
    OnChange = CounterComboBoxChange
    Items.Strings = (
      ''
      'ersten'
      'zweiten'
      'dritten'
      'vierten'
      'letzten'
      'vorletzten')
  end
  object MonthComboBox: TComboBox
    Left = 384
    Top = 88
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    OnChange = MonthComboBoxChange
    Items.Strings = (
      'Januar'
      'Februar'
      'M�rz'
      'April'
      'Mai'
      'Juni'
      'Juli'
      'August'
      'September'
      'Oktober'
      'November'
      'Dezember')
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 129
    Height = 453
    TabStop = False
    Align = alLeft
    DataSource = RepResSource
    TabOrder = 18
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Name'
        Visible = True
      end>
  end
  object MonthDayEdit: TDBEdit
    Left = 232
    Top = 88
    Width = 25
    Height = 21
    DataField = 'MonatsTag'
    DataSource = RepResSource
    TabOrder = 5
  end
  object DBNavigator1: TDBNavigator
    Left = 136
    Top = 8
    Width = 230
    Height = 25
    DataSource = RepResSource
    TabOrder = 19
  end
  object DBEdit2: TDBEdit
    Left = 232
    Top = 136
    Width = 345
    Height = 21
    DataField = 'Name'
    DataSource = RepResSource
    TabOrder = 7
  end
  object DBEdit4: TDBEdit
    Left = 584
    Top = 136
    Width = 25
    Height = 21
    DataField = 'Personen'
    DataSource = RepResSource
    TabOrder = 8
  end
  object DBEdit5: TDBEdit
    Left = 232
    Top = 160
    Width = 377
    Height = 21
    DataField = 'Telefon'
    DataSource = RepResSource
    TabOrder = 9
  end
  object RoomsComboBox: TComboBox
    Left = 232
    Top = 184
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 10
    OnChange = RoomsComboBoxChange
  end
  object DBComboBox1: TDBComboBox
    Left = 232
    Top = 208
    Width = 145
    Height = 21
    Style = csDropDownList
    DataField = 'Status'
    DataSource = RepResSource
    ItemHeight = 13
    Items.Strings = (
      'Fest'
      'Variabel'
      'Tagung'
      'Option')
    TabOrder = 13
  end
  object DBLookupComboBox1: TDBLookupComboBox
    Left = 384
    Top = 184
    Width = 121
    Height = 21
    DataField = 'Tisch'
    DataSource = RepResSource
    KeyField = 'ID'
    ListField = 'Tisch'
    ListSource = TableSource
    TabOrder = 11
  end
  object DBCheckBox1: TDBCheckBox
    Left = 512
    Top = 184
    Width = 113
    Height = 17
    Caption = 'Kompletter Raum'
    DataField = 'Kompletter_raum'
    DataSource = RepResSource
    TabOrder = 12
    ValueChecked = 'T'
    ValueUnchecked = 'F'
  end
  object DBEdit6: TDBEdit
    Left = 384
    Top = 208
    Width = 225
    Height = 21
    DataField = 'Kuerzel'
    DataSource = RepResSource
    TabOrder = 14
  end
  object DBEdit7: TDBEdit
    Left = 231
    Top = 232
    Width = 377
    Height = 21
    DataField = 'Anlass'
    DataSource = RepResSource
    TabOrder = 15
  end
  object DBMemo2: TDBMemo
    Left = 232
    Top = 256
    Width = 377
    Height = 89
    DataField = 'Int_bemerk'
    DataSource = RepResSource
    TabOrder = 16
  end
  object DBMemo3: TDBMemo
    Left = 232
    Top = 352
    Width = 377
    Height = 89
    DataField = 'Ext_bemerk'
    DataSource = RepResSource
    TabOrder = 17
  end
  object DBEdit1: TDBEdit
    Left = 376
    Top = 8
    Width = 153
    Height = 21
    TabStop = False
    DataField = 'LetzterEintrag'
    DataSource = RepResSource
    ReadOnly = True
    TabOrder = 0
  end
  object TimePicker: TDateTimePicker
    Left = 424
    Top = 40
    Width = 73
    Height = 21
    CalAlignment = dtaLeft
    Date = 36538
    Time = 36538
    DateFormat = dfShort
    DateMode = dmUpDown
    Kind = dtkTime
    ParseInput = False
    TabOrder = 2
    OnChange = TimePickerChange
  end
  object EndTimePicker: TDateTimePicker
    Left = 504
    Top = 40
    Width = 73
    Height = 21
    CalAlignment = dtaLeft
    Date = 36538
    Time = 36538
    DateFormat = dfShort
    DateMode = dmUpDown
    Kind = dtkTime
    ParseInput = False
    TabOrder = 20
    OnChange = TimePickerChange
  end
  object RepResSource: TDataSource
    DataSet = RepResTable
    Left = 24
    Top = 32
  end
  object RepResTable: TTable
    AfterInsert = RepResTableAfterInsert
    BeforePost = RepResTableBeforePost
    AfterCancel = RepResTableAfterCancel
    BeforeDelete = RepResTableBeforeDelete
    AfterScroll = RepResTableAfterScroll
    OnPostError = RepResTablePostError
    DatabaseName = 'GASTHAUS'
    FieldDefs = <
      item
        Name = 'ID'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'WIEDERHOLUNG'
        Attributes = [faRequired]
        DataType = ftString
        Size = 16
      end
      item
        Name = 'WOCHENTAG'
        DataType = ftInteger
      end
      item
        Name = 'MONATSTAG'
        DataType = ftInteger
      end
      item
        Name = 'MONAT'
        DataType = ftInteger
      end
      item
        Name = 'ZAEHLER'
        DataType = ftInteger
      end
      item
        Name = 'LETZTEREINTRAG'
        DataType = ftDateTime
      end
      item
        Name = 'UHRZEIT'
        Attributes = [faRequired]
        DataType = ftDateTime
      end
      item
        Name = 'ENDE'
        DataType = ftDateTime
      end
      item
        Name = 'TISCH'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NAME'
        Attributes = [faRequired]
        DataType = ftString
        Size = 64
      end
      item
        Name = 'PERSONEN'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'KUERZEL'
        Attributes = [faRequired]
        DataType = ftString
        Size = 8
      end
      item
        Name = 'STATUS'
        Attributes = [faRequired]
        DataType = ftString
        Size = 16
      end
      item
        Name = 'TELEFON'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'ANLASS'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'EXT_BEMERK'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'INT_BEMERK'
        DataType = ftString
        Size = 255
      end
      item
        Name = 'KOMPLETTER_RAUM'
        DataType = ftString
        Size = 1
      end>
    IndexDefs = <
      item
        Name = 'STAMMNAMEIDX'
        Fields = 'NAME'
      end
      item
        Name = 'STAMM_TISCH_IDX'
        Fields = 'TISCH'
      end
      item
        Name = 'SYS_C0033650'
        Fields = 'ID'
        Options = [ixUnique]
      end>
    IndexName = 'STAMMNAMEIDX'
    StoreDefs = True
    TableName = 'STAMM'
    UpdateMode = upWhereKeyOnly
    Left = 24
    Top = 88
    object RepResTableWiederholung: TStringField
      FieldName = 'Wiederholung'
      Required = True
      Size = 16
    end
    object RepResTableWochenTag: TSmallintField
      FieldName = 'WochenTag'
    end
    object RepResTableMonatsTag: TSmallintField
      FieldName = 'MonatsTag'
    end
    object RepResTableMonat: TSmallintField
      FieldName = 'Monat'
    end
    object RepResTableZaehler: TSmallintField
      FieldName = 'Zaehler'
    end
    object RepResTableLetzterEintrag: TDateTimeField
      FieldName = 'LetzterEintrag'
    end
    object RepResTableUhrzeit: TDateTimeField
      FieldName = 'Uhrzeit'
      Required = True
    end
    object RepResTableTisch: TIntegerField
      FieldName = 'Tisch'
      Required = True
    end
    object RepResTableName: TStringField
      FieldName = 'Name'
      Required = True
      Size = 64
    end
    object RepResTablePersonen: TSmallintField
      FieldName = 'Personen'
      Required = True
    end
    object RepResTableKuerzel: TStringField
      FieldName = 'Kuerzel'
      Required = True
      Size = 8
    end
    object RepResTableStatus: TStringField
      FieldName = 'Status'
      Required = True
      Size = 16
    end
    object RepResTableTelefon: TStringField
      FieldName = 'Telefon'
      Size = 64
    end
    object RepResTableAnlass: TStringField
      FieldName = 'Anlass'
      Size = 255
    end
    object RepResTableExt_bemerk: TStringField
      FieldName = 'Ext_bemerk'
      Size = 255
    end
    object RepResTableInt_bemerk: TStringField
      FieldName = 'Int_bemerk'
      Size = 255
    end
    object RepResTableKompletter_raum: TStringField
      FieldName = 'Kompletter_raum'
      Size = 1
    end
    object RepResTableID: TIntegerField
      FieldName = 'ID'
      Required = True
    end
    object RepResTableEnde: TDateTimeField
      FieldName = 'Ende'
    end
  end
  object TableQuery: TQuery
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      
        'select'#9'distinct tisch || '#39' ('#39' || Personen || '#39' Pers. )'#39' Tisch, I' +
        'D'
      'from'#9'tisch'
      ' ')
    Left = 408
    Top = 264
  end
  object TableSource: TDataSource
    DataSet = TableQuery
    Left = 464
    Top = 256
  end
end
