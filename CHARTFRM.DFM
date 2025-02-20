object ChartForm: TChartForm
  Left = 312
  Top = 193
  Width = 544
  Height = 391
  Caption = '�bersicht'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object roomsChart: TDBChart
    Left = 0
    Top = -24
    Width = 532
    Height = 137
    AllowPanning = pmNone
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    BackWall.Color = clBtnFace
    BackWall.Pen.Visible = False
    Title.Text.Strings = (
      'TDBChart')
    Title.Visible = False
    AxisVisible = False
    BackColor = clBtnFace
    Chart3DPercent = 1
    ClipPoints = False
    Frame.Visible = False
    ScaleLastPage = False
    View3DOptions.Elevation = 315
    View3DOptions.Orthogonal = False
    View3DOptions.Perspective = 0
    View3DOptions.Rotation = 360
    View3DWalls = False
    BevelOuter = bvNone
    PopupMenu = PopupMenu1
    TabOrder = 0
    Visible = False
    object Series1: TPieSeries
      Marks.ArrowLength = 8
      Marks.Visible = True
      DataSource = roomsQuery
      SeriesColor = clRed
      XLabelsSource = 'Raum'
      Circled = True
      OtherSlice.Text = 'Other'
      PieValues.DateTime = False
      PieValues.Name = 'Pie'
      PieValues.Multiplier = 1
      PieValues.Order = loNone
      PieValues.ValueSource = 'ANZAHL'
    end
  end
  object personsChart: TDBChart
    Left = 0
    Top = 216
    Width = 532
    Height = 144
    AllowPanning = pmNone
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    BackWall.Color = clBtnFace
    BackWall.Pen.Visible = False
    Title.Text.Strings = (
      'TDBChart')
    Title.Visible = False
    AxisVisible = False
    BackColor = clBtnFace
    Chart3DPercent = 1
    ClipPoints = False
    Frame.Visible = False
    ScaleLastPage = False
    View3DOptions.Elevation = 315
    View3DOptions.Orthogonal = False
    View3DOptions.Perspective = 0
    View3DOptions.Rotation = 360
    View3DWalls = False
    BevelOuter = bvNone
    PopupMenu = PopupMenu1
    TabOrder = 1
    Visible = False
    object PieSeries1: TPieSeries
      Marks.ArrowLength = 8
      Marks.Visible = True
      DataSource = personsQuery
      SeriesColor = clRed
      XLabelsSource = 'name'
      Circled = True
      OtherSlice.Text = 'Other'
      PiePen.Style = psDash
      PiePen.Visible = False
      PieValues.DateTime = False
      PieValues.Name = 'Pie'
      PieValues.Multiplier = 1
      PieValues.Order = loNone
      PieValues.ValueSource = 'ANZAHL'
    end
  end
  object personsQuery: TQuery
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      'select  name,'
      #9#9'sum( Personen ) SUMME,'
      #9#9'count(*) ANZAHL'
      'from'#9'reservat'
      'group by name'
      'order by 3 desc'
      ''
      ' '
      ' '
      ' '
      ' ')
    Left = 24
    Top = 232
  end
  object PopupMenu1: TPopupMenu
    Left = 88
    Top = 16
    object Rooms: TMenuItem
      Caption = 'R�ume'
      OnClick = RoomsClick
    end
    object Persons: TMenuItem
      Caption = 'Personen'
      OnClick = PersonsClick
    end
  end
  object roomsQuery: TQuery
    DatabaseName = 'GASTHAUS'
    SQL.Strings = (
      'select  z.name Raum,'
      #9#9'sum( r.Personen ) Personen,'
      #9#9'count(*) ANZAHL'
      'from'#9'reservat r, tisch t, raum z'
      'where'#9'r.tisch = t.id and'
      #9#9't.raum = z.id'
      'group by z.name'
      'order by 3 desc'
      ''
      ' '
      ' '
      ' '
      ' '
      ' '
      ' '
      ' ')
    Left = 16
    Top = 24
  end
end
