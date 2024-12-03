object EditForm: TEditForm
  Left = 221
  Top = 449
  Width = 598
  Height = 444
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Reservierung bearbeiten'
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
    Left = 8
    Top = 8
    Width = 72
    Height = 13
    Caption = 'Datum/Uhrzeit:'
  end
  object Label2: TLabel
    Left = 8
    Top = 32
    Width = 81
    Height = 13
    Caption = 'Name/Personen:'
  end
  object Label3: TLabel
    Left = 8
    Top = 56
    Width = 39
    Height = 13
    Caption = 'Telefon:'
  end
  object Label4: TLabel
    Left = 8
    Top = 80
    Width = 62
    Height = 13
    Caption = 'Raum/Tisch:'
  end
  object Label5: TLabel
    Left = 8
    Top = 104
    Width = 67
    Height = 13
    Caption = 'Status/Kürzel:'
  end
  object Label6: TLabel
    Left = 8
    Top = 128
    Width = 34
    Height = 13
    Caption = 'Anlass:'
  end
  object Label7: TLabel
    Left = 8
    Top = 152
    Width = 77
    Height = 13
    Caption = 'Besonderheiten:'
  end
  object Label8: TLabel
    Left = 8
    Top = 248
    Width = 82
    Height = 13
    Caption = 'Serviceanleitung:'
  end
  object Label9: TLabel
    Left = 8
    Top = 348
    Width = 79
    Height = 13
    Anchors = [akLeft, akBottom]
    Caption = 'Funktion/Status:'
  end
  object LabelLastUser: TLabel
    Left = 496
    Top = 8
    Width = 68
    Height = 13
    Caption = 'LabelLastUser'
  end
  object DBEditName: TDBEdit
    Left = 104
    Top = 32
    Width = 441
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    DataField = 'Name'
    DataSource = ReservationSource
    TabOrder = 3
    OnKeyPress = DBEditNameKeyPress
  end
  object DBEditPersonen: TDBEdit
    Left = 552
    Top = 32
    Width = 25
    Height = 21
    Anchors = [akTop, akRight]
    DataField = 'Personen'
    DataSource = ReservationSource
    TabOrder = 4
  end
  object DBLookupComboBoxTisch: TDBLookupComboBox
    Left = 256
    Top = 80
    Width = 121
    Height = 21
    DataField = 'Tisch'
    DataSource = ReservationSource
    KeyField = 'ID'
    ListField = 'Tisch'
    ListSource = TableSource
    TabOrder = 7
    OnCloseUp = DBLookupComboBoxTischCloseUp
  end
  object DBEditTelefon: TDBEdit
    Left = 104
    Top = 56
    Width = 473
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    DataField = 'Telefon'
    DataSource = ReservationSource
    TabOrder = 5
  end
  object RoomsComboBox: TComboBox
    Left = 104
    Top = 80
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    OnChange = RoomsComboBoxChange
  end
  object DBComboBoxStatus: TDBComboBox
    Left = 104
    Top = 104
    Width = 145
    Height = 21
    Style = csDropDownList
    DataField = 'Status'
    DataSource = ReservationSource
    ItemHeight = 13
    Items.Strings = (
      'Fest'
      'Variabel'
      'Doppelt'
      'Tagung'
      'Option'
      'Storniert')
    TabOrder = 10
  end
  object DBEditKuerzel: TDBEdit
    Left = 256
    Top = 104
    Width = 121
    Height = 21
    DataField = 'Kuerzel'
    DataSource = ReservationSource
    TabOrder = 11
  end
  object DBMemoInternalRemarks: TDBMemo
    Left = 104
    Top = 152
    Width = 473
    Height = 89
    Anchors = [akLeft, akTop, akRight]
    DataField = 'Int_bemerk'
    DataSource = ReservationSource
    TabOrder = 14
  end
  object DBMemoExternalRemarks: TDBMemo
    Left = 104
    Top = 248
    Width = 473
    Height = 89
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataField = 'Ext_bemerk'
    DataSource = ReservationSource
    TabOrder = 15
  end
  object DBCheckBoxComplete: TDBCheckBox
    Left = 384
    Top = 80
    Width = 113
    Height = 17
    Caption = 'Kompletter Raum'
    DataField = 'Kompletter_raum'
    DataSource = ReservationSource
    TabOrder = 8
    ValueChecked = 'T'
    ValueUnchecked = 'F'
  end
  object FunctionButton: TButton
    Left = 104
    Top = 348
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Funktion...'
    PopupMenu = PopupMenu1
    TabOrder = 16
    OnClick = OpenMenuClick
  end
  object DBComboBoxFunctionStatus: TDBComboBox
    Left = 184
    Top = 348
    Width = 145
    Height = 21
    Style = csDropDownList
    Anchors = [akLeft, akBottom]
    DataField = 'Func_status'
    DataSource = ReservationSource
    ItemHeight = 13
    Items.Strings = (
      ''
      'Nicht erledigt'
      'Erledigt')
    PopupMenu = PopupMenu1
    TabOrder = 17
  end
  object DBEditAnlass: TDBEdit
    Left = 103
    Top = 128
    Width = 473
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    DataField = 'Anlass'
    DataSource = ReservationSource
    TabOrder = 13
  end
  object ButtonSave: TButton
    Left = 8
    Top = 380
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = 'Speichern'
    TabOrder = 18
    OnClick = ButtonSaveClick
  end
  object ButtonCancel: TButton
    Left = 88
    Top = 380
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Cancel = True
    Caption = 'Verwerfen'
    TabOrder = 19
    OnClick = ButtonCancelClick
  end
  object DatePicker: TDateTimePicker
    Left = 104
    Top = 8
    Width = 241
    Height = 21
    CalAlignment = dtaLeft
    Date = 36415
    Time = 36415
    DateFormat = dfLong
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 0
    OnCloseUp = DatePickerCloseUp
  end
  object DBEditErfassungsDatum: TDBEdit
    Left = 384
    Top = 104
    Width = 193
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    DataField = 'ErfassungsDatum'
    DataSource = ReservationSource
    ReadOnly = True
    TabOrder = 12
  end
  object TimePicker: TDateTimePicker
    Left = 351
    Top = 8
    Width = 66
    Height = 21
    CalAlignment = dtaLeft
    Date = 36526
    Time = 36526
    DateFormat = dfShort
    DateMode = dmUpDown
    Kind = dtkTime
    ParseInput = False
    TabOrder = 1
    OnChange = TimePickerChange
  end
  object EndTimePicker: TDateTimePicker
    Left = 423
    Top = 8
    Width = 66
    Height = 21
    CalAlignment = dtaLeft
    Date = 36526
    Time = 36526
    DateFormat = dfShort
    DateMode = dmUpDown
    Kind = dtkTime
    ParseInput = False
    TabOrder = 2
    OnChange = TimePickerChange
  end
  object ButtonSelect: TButton
    Left = 496
    Top = 80
    Width = 75
    Height = 21
    Caption = 'Auswahl...'
    TabOrder = 9
    OnClick = ButtonSelectClick
  end
  object ReservationSource: TDataSource
    DataSet = ReservationQuery
    Left = 256
    Top = 368
  end
  object TableQuery: TQuery
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      
        'select'#9'distinct t.tisch || '#39' ('#39' || t.personen || '#39' Pers. )'#39' TISC' +
        'H, t.ID'
      'from'#9'tisch t'
      'where'#9't.raum = :derRaum'
      ' '
      ' ')
    Left = 448
    Top = 360
    ParamData = <
      item
        DataType = ftInteger
        Name = 'derRaum'
        ParamType = ptInput
      end>
    object TableQueryID: TIntegerField
      FieldName = 'ID'
      Origin = 'GASTHAUS."tisch.DB".ID'
    end
    object TableQueryTISCH: TStringField
      FieldName = 'TISCH'
      Origin = 'GASTHAUS."tisch.DB".TISCH'
      Size = 42
    end
  end
  object TableSource: TDataSource
    DataSet = TableQuery
    Left = 400
    Top = 344
  end
  object ReservationQuery: TQuery
    AfterInsert = ClearUser
    AfterEdit = ClearUser
    BeforePost = ReservationQueryBeforePost
    AfterCancel = ReservationQueryAfterCancel
    AfterScroll = ReservationQueryAfterScroll
    DatabaseName = 'GASTHAUS'
    RequestLive = True
    SQL.Strings = (
      'select * from RESERVAT')
    UpdateMode = upWhereKeyOnly
    Left = 320
    Top = 368
    object ReservationQueryDatum: TDateTimeField
      FieldName = 'Datum'
      Origin = '"reservat.DB".Datum'
      Required = True
    end
    object ReservationQueryErfassungsDatum: TDateTimeField
      FieldName = 'ErfassungsDatum'
      Origin = '"reservat.DB".ErfassungsDatum'
    end
    object ReservationQueryUhrzeit: TDateTimeField
      FieldName = 'Uhrzeit'
      Origin = '"reservat.DB".Uhrzeit'
      Required = True
    end
    object ReservationQueryTisch: TIntegerField
      FieldName = 'Tisch'
      Origin = '"reservat.DB".Tisch'
      Required = True
    end
    object ReservationQueryName: TStringField
      FieldName = 'Name'
      Origin = '"reservat.DB".Name'
      Required = True
      Size = 64
    end
    object ReservationQueryPersonen: TSmallintField
      FieldName = 'Personen'
      Origin = '"reservat.DB".Personen'
      Required = True
    end
    object ReservationQueryKuerzel: TStringField
      FieldName = 'Kuerzel'
      Origin = '"reservat.DB".Kuerzel'
      Required = True
      Size = 8
    end
    object ReservationQueryStatus: TStringField
      FieldName = 'Status'
      Origin = '"reservat.DB".Status'
      Required = True
      Size = 16
    end
    object ReservationQueryLink: TIntegerField
      FieldName = 'Link'
      Origin = '"reservat.DB".Link'
    end
    object ReservationQueryTelefon: TStringField
      FieldName = 'Telefon'
      Origin = '"reservat.DB".Telefon'
      Size = 64
    end
    object ReservationQueryAnlass: TStringField
      FieldName = 'Anlass'
      Origin = '"reservat.DB".Anlass'
      Size = 255
    end
    object ReservationQueryExt_bemerk: TStringField
      FieldName = 'Ext_bemerk'
      Origin = '"reservat.DB".Ext_bemerk'
      Size = 255
    end
    object ReservationQueryInt_bemerk: TStringField
      FieldName = 'Int_bemerk'
      Origin = '"reservat.DB".Int_bemerk'
      Size = 255
    end
    object ReservationQueryFunktion: TStringField
      FieldName = 'Funktion'
      Origin = '"reservat.DB".Funktion'
      Size = 255
    end
    object ReservationQueryFunc_status: TStringField
      FieldName = 'Func_status'
      Origin = '"reservat.DB".Func_status'
      Size = 16
    end
    object ReservationQueryKompletter_raum: TStringField
      FieldName = 'Kompletter_raum'
      Origin = '"reservat.DB".Kompletter_raum'
      Size = 1
    end
    object ReservationQueryId: TIntegerField
      FieldName = 'Id'
      Origin = '"reservat.DB".Id'
      Required = True
    end
    object ReservationQueryEnde: TDateTimeField
      FieldName = 'Ende'
      Origin = '"reservat.DB".Ende'
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'DOC'
    Filter = 'Alle Dateien|*.*|MS-Word|*.DOC|MS-Write|*.WRI|StarWriter|*.SDW'
    Left = 360
    Top = 344
  end
  object PopupMenu1: TPopupMenu
    Left = 16
    Top = 312
    object OpenMenu: TMenuItem
      Caption = 'Öffnen'
      OnClick = OpenMenuClick
    end
    object ChangeMenu: TMenuItem
      Caption = 'Ändern'
      OnClick = ChangeMenuClick
    end
    object DeleteMenu: TMenuItem
      Caption = 'Löschen'
      OnClick = DeleteMenuClick
    end
  end
  object NameQuery: TQuery
    DatabaseName = 'GASTHAUS'
    RequestLive = True
    SQL.Strings = (
      'select NAME, max(TELEFON) as TELEFON'
      'from RESERVAT'
      'group by NAME'
      ' ')
    UpdateMode = upWhereKeyOnly
    Left = 520
    Top = 344
    object NameQueryNAME: TStringField
      FieldName = 'NAME'
      Origin = 'GASTHAUS."RESERVAT.DB".NAME'
      Size = 64
    end
    object NameQueryTELEFON: TStringField
      FieldName = 'TELEFON'
      Origin = 'GASTHAUS."RESERVAT.DB".TELEFON'
      Size = 64
    end
  end
end
