object MainForm: TMainForm
  Left = 241
  Top = 97
  Width = 969
  Height = 468
  Caption = 'Gasthausreservierung'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = True
  Position = poDefault
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 953
    Height = 121
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 12
      Width = 25
      Height = 13
      Caption = 'Filter:'
    end
    object Label2: TLabel
      Left = 688
      Top = 12
      Width = 51
      Height = 13
      Caption = 'Sortierung:'
    end
    object TerminLabel: TLabel
      Left = 8
      Top = 96
      Width = 79
      Height = 24
      Caption = 'Termine'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object DBText1: TDBText
      Left = 472
      Top = 32
      Width = 49
      Height = 17
      Alignment = taRightJustify
      DataField = 'PERSONEN'
      DataSource = SumSource
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 528
      Top = 32
      Width = 67
      Height = 16
      Caption = 'Personen'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CountLabel: TLabel
      Left = 600
      Top = 32
      Width = 111
      Height = 16
      Caption = 'Reservierungen'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object DateComboBox: TComboBox
      Left = 40
      Top = 8
      Width = 137
      Height = 21
      Style = csDropDownList
      DropDownCount = 9
      ItemHeight = 13
      TabOrder = 0
      OnChange = DateComboBoxChange
      Items.Strings = (
        'Alle Tage'
        'Heute'
        'Morgen'
        'Diese Woche'
        'Nächste Woche'
        'Dieser Monat'
        'Nächster Monat'
        'Ein Tag'
        'Ein Zeitraum')
    end
    object SortComboBox: TComboBox
      Left = 752
      Top = 8
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = SortComboBoxChange
      Items.Strings = (
        'Datum/Raum/Tisch'
        'Name/Datum/Uhrzeit'
        'Datum/Uhrzeit')
    end
    object ButtonNew: TButton
      Left = 8
      Top = 64
      Width = 161
      Height = 25
      Caption = 'Neue Reservierung'
      TabOrder = 6
      OnClick = ButtonNewClick
    end
    object ButtonEdit: TButton
      Left = 176
      Top = 64
      Width = 161
      Height = 25
      Caption = 'Reservierung Bearbeiten'
      TabOrder = 7
      OnClick = ButtonEditClick
    end
    object ButtonReload: TButton
      Left = 344
      Top = 64
      Width = 161
      Height = 25
      Caption = 'Reservierungen neu laden'
      TabOrder = 8
      OnClick = ButtonReloadClick
    end
    object RaeumeComboBox: TComboBox
      Left = 184
      Top = 8
      Width = 137
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      OnChange = RaeumeComboBoxChange
    end
    object StartDatePicker: TDateTimePicker
      Left = 40
      Top = 32
      Width = 209
      Height = 21
      CalAlignment = dtaLeft
      Date = 36412
      Time = 36412
      DateFormat = dfLong
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
      OnCloseUp = StartDatePickerCloseUp
    end
    object EndDatePicker: TDateTimePicker
      Left = 256
      Top = 32
      Width = 209
      Height = 21
      CalAlignment = dtaLeft
      Date = 36412
      Time = 36412
      DateFormat = dfLong
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 5
      OnCloseUp = EndDatePickerCloseUp
    end
    object TimeComboBox: TComboBox
      Left = 328
      Top = 8
      Width = 137
      Height = 21
      Style = csDropDownList
      DropDownCount = 9
      ItemHeight = 13
      TabOrder = 9
      OnChange = TimeComboBoxChange
      Items.Strings = (
        'Alle Zeiten'
        'Mittags (bis 16 Uhr)'
        'Abends (ab 16 Uhr)'
        'bis 12 Uhr'
        '12 - 14 Uhr'
        '14 - 16 Uhr'
        '16 - 18 Uhr'
        '18 - 20 Uhr'
        'ab 20 Uhr')
    end
    object EditName: TEdit
      Left = 472
      Top = 8
      Width = 209
      Height = 21
      TabOrder = 2
      OnChange = EditNameChange
    end
  end
  object ReservationGrid: TDBGrid
    Left = 0
    Top = 121
    Width = 953
    Height = 288
    Align = alClient
    DataSource = reservatSource
    DefaultDrawing = False
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDrawColumnCell = ReservationGridDrawColumnCell
    Columns = <
      item
        Expanded = False
        FieldName = 'Datum'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Raum'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Uhrzeit'
        Width = 32
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Personen'
        Width = 32
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Tisch'
        Width = 32
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Status'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'func_status'
        Title.Caption = 'Funktion'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Anlass'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ext_bemerk'
        Title.Caption = 'Serviceanleitung'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'int_bemerk'
        Title.Caption = 'Besonderheiten'
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Telefon'
        Width = 100
        Visible = True
      end>
  end
  object reservatSource: TDataSource
    DataSet = reservatQuery
    Left = 96
    Top = 224
  end
  object reservatQuery: TQuery
    AfterOpen = reservatQueryAfterOpen
    AfterScroll = reservatQueryAfterScroll
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      'select  r.ID,'
      #9#9'r.Datum,'
      #9#9'z.name Raum,'
      #9#9't.Tisch,'
      #9#9'r.Uhrzeit,'
      #9#9'r.Name,'
      #9#9'r.Status,'
      #9#9'r.func_status,'
      #9#9'r.Anlass,'
      #9#9'r.int_bemerk,'
      #9#9'r.ext_bemerk,'
      #9#9'r.Personen,'
      #9#9'r.Telefon,'
      #9#9'r.Kompletter_Raum,'
      #9#9'r.Link'
      'from'#9'reservat r, tisch t, raum z'
      'where'#9'r.tisch = t.id and'
      #9#9't.raum = z.id'
      ''
      ' '
      ' '
      ' '
      ' '
      ' ')
    Left = 32
    Top = 224
    object reservatQueryID: TIntegerField
      FieldName = 'ID'
      Origin = 'reservat.Id'
    end
    object reservatQueryDatum: TDateTimeField
      DisplayWidth = 12
      FieldName = 'Datum'
      Origin = 'reservat.Datum'
      DisplayFormat = 'DD. MM. YYYY'
    end
    object reservatQueryRaum: TStringField
      FieldName = 'Raum'
      Origin = 'raum.Name'
      Size = 255
    end
    object reservatQueryTisch: TStringField
      FieldName = 'Tisch'
      Origin = 'tisch.Tisch'
      Size = 16
    end
    object reservatQueryUhrzeit: TDateTimeField
      FieldName = 'Uhrzeit'
      Origin = 'reservat.Uhrzeit'
      DisplayFormat = 'HH:MM'
    end
    object reservatQueryName: TStringField
      FieldName = 'Name'
      Origin = 'reservat.Name'
      Size = 64
    end
    object reservatQueryStatus: TStringField
      FieldName = 'Status'
      Origin = 'reservat.Status'
      Size = 16
    end
    object reservatQueryfunc_status: TStringField
      FieldName = 'func_status'
      Origin = 'reservat.Func_status'
      Size = 16
    end
    object reservatQueryAnlass: TStringField
      FieldName = 'Anlass'
      Origin = 'reservat.Anlass'
      Size = 255
    end
    object reservatQueryint_bemerk: TStringField
      FieldName = 'int_bemerk'
      Origin = 'reservat.Int_bemerk'
      Size = 255
    end
    object reservatQueryext_bemerk: TStringField
      FieldName = 'ext_bemerk'
      Origin = 'reservat.Ext_bemerk'
      Size = 255
    end
    object reservatQueryPersonen: TSmallintField
      FieldName = 'Personen'
      Origin = 'reservat.Personen'
    end
    object reservatQueryTelefon: TStringField
      FieldName = 'Telefon'
      Origin = 'reservat.Telefon'
      Size = 64
    end
    object reservatQueryLink: TIntegerField
      FieldName = 'Link'
      Origin = 'reservat.Link'
    end
    object reservatQueryKompletter_Raum: TStringField
      FieldName = 'Kompletter_Raum'
      Origin = 'reservat.Kompletter_raum'
      Size = 1
    end
  end
  object MainMenu: TMainMenu
    Left = 176
    Top = 168
    object Datei1: TMenuItem
      Caption = '&Datei'
      object Drucken1: TMenuItem
        Caption = '&Drucken'
        object EinzelneKarte1: TMenuItem
          Caption = '&Einzelne Karte'
          OnClick = EinzelneKarte1Click
        end
        object Tischkarte1: TMenuItem
          Caption = '&Tischkarten'
          OnClick = Tischkarte1Click
        end
        object N4: TMenuItem
          Caption = '-'
        end
        object Liste1: TMenuItem
          Caption = 'Einfache &Liste'
          OnClick = Liste1Click
        end
        object GruppierteListe1: TMenuItem
          Caption = '&Gruppierte Liste'
          OnClick = GruppierteListe1Click
        end
      end
      object Diagramm1: TMenuItem
        Caption = 'Ü&bersicht...'
        OnClick = Diagramm1Click
      end
      object FreieTische1: TMenuItem
        Caption = '&Freie Tische...'
        OnClick = FreieTische1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Ende1: TMenuItem
        Caption = '&Ende'
        OnClick = Ende1Click
      end
    end
    object Bearbeiten1: TMenuItem
      Caption = '&Bearbeiten'
      object Duplicate: TMenuItem
        Caption = '&Duplizieren'
        OnClick = DuplicateClick
      end
      object GotoCopy: TMenuItem
        Caption = '&Zur Kopie'
        OnClick = GotoCopyClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Stammtische1: TMenuItem
        Caption = '&Stammtische'
        OnClick = Stammtische1Click
      end
      object Berechnungstarten1: TMenuItem
        Caption = '&Berechnung starten'
        OnClick = Berechnungstarten1Click
      end
      object Berechnungbeenden1: TMenuItem
        Caption = 'B&erechnung beenden'
        OnClick = Berechnungbeenden1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object AlteResLschen1: TMenuItem
        Caption = '&Alte Res. Löschen'
        OnClick = AlteResLschen1Click
      end
    end
    object MenuSQLreports: TMenuItem
      Caption = '&SQL Berichte'
    end
    object MenuHTMLreports: TMenuItem
      Caption = '&HTML Berichte'
    end
    object Einrichtung1: TMenuItem
      Caption = '&Einrichtung'
      object Rume1: TMenuItem
        Caption = '&Räume...'
        OnClick = Rume1Click
      end
      object Tische1: TMenuItem
        Caption = '&Tische...'
        OnClick = Tische1Click
      end
      object Zeichnen1: TMenuItem
        Caption = 'Zeichnen...'
        OnClick = Zeichnen1Click
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object Termine1: TMenuItem
        Caption = '&Feiertage/Messen/Termine...'
        OnClick = Termine1Click
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object Optionen1: TMenuItem
        Caption = '&Optionen...'
        OnClick = Optionen1Click
      end
    end
    object Hilfe1: TMenuItem
      Caption = '&Info!'
      OnClick = berGasthaus1Click
    end
  end
  object ScheduleQuery: TQuery
    DatabaseName = 'Gasthaus'
    SQL.Strings = (
      'select'#9'distinct beschreibung'
      'from'#9'termine'
      'where'#9'(Art = '#39'Fest'#39' and tag = :theDay and monat = :theMonth)'
      'or'#9#9'(StartDatum <= :theDate1 and EndeDatum >= :theDate2)'
      ' ')
    Left = 32
    Top = 272
    ParamData = <
      item
        DataType = ftInteger
        Name = 'theDay'
        ParamType = ptInput
        Value = 0
      end
      item
        DataType = ftInteger
        Name = 'theMonth'
        ParamType = ptInput
        Value = 0
      end
      item
        DataType = ftDateTime
        Name = 'theDate1'
        ParamType = ptInput
        Value = 0d
      end
      item
        DataType = ftDateTime
        Name = 'theDate2'
        ParamType = ptInput
        Value = 0d
      end>
  end
  object sumQuery: TQuery
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      'select  sum( r.Personen ) personen'
      'from'#9'reservat r'
      ''
      ' '
      ' ')
    Left = 32
    Top = 168
  end
  object SumSource: TDataSource
    DataSet = sumQuery
    Left = 96
    Top = 168
  end
  object GasthausDB: TDatabase
    Connected = True
    DatabaseName = 'Gasthaus'
    SessionName = 'Default'
    Left = 96
    Top = 272
  end
end
