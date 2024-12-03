object GasthausDataModule: TGasthausDataModule
  OldCreateOrder = False
  Left = 773
  Top = 181
  Height = 508
  Width = 643
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
    ReadOnly = True
    StoreDefs = True
    TableName = 'RAUM'
    UpdateMode = upWhereKeyOnly
    Left = 48
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
  object TableTable: TTable
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
      end
      item
        Name = 'LEFT_POS'
        DataType = ftInteger
      end
      item
        Name = 'RIGHT_POS'
        DataType = ftInteger
      end
      item
        Name = 'TOP_POS'
        DataType = ftInteger
      end
      item
        Name = 'BOTTOM_POS'
        DataType = ftInteger
      end
      item
        Name = 'SHAPE'
        DataType = ftInteger
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
    ReadOnly = True
    StoreDefs = True
    TableName = 'TISCH'
    UpdateMode = upWhereKeyOnly
    Left = 128
    Top = 64
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
    object TableTableLEFT_POS: TIntegerField
      FieldName = 'LEFT_POS'
    end
    object TableTableRIGHT_POS: TIntegerField
      FieldName = 'RIGHT_POS'
    end
    object TableTableTOP_POS: TIntegerField
      FieldName = 'TOP_POS'
    end
    object TableTableBOTTOM_POS: TIntegerField
      FieldName = 'BOTTOM_POS'
    end
    object TableTableSHAPE: TIntegerField
      FieldName = 'SHAPE'
    end
  end
  object PointTable: TTable
    DatabaseName = 'GASTHAUS'
    TableName = 'RAUM_POS'
    Left = 48
    Top = 128
    object PointTableRAUM: TIntegerField
      FieldName = 'RAUM'
      Required = True
    end
    object PointTableNUMMER: TIntegerField
      FieldName = 'NUMMER'
      Required = True
    end
    object PointTableX_POS: TIntegerField
      FieldName = 'X_POS'
      Required = True
    end
    object PointTableY_POS: TIntegerField
      FieldName = 'Y_POS'
      Required = True
    end
  end
end
