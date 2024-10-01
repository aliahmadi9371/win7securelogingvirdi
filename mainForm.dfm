object MForm: TMForm
  AlignWithMargins = True
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'SecureLogIn'
  ClientHeight = 596
  ClientWidth = 1226
  Color = clBtnHighlight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1226
    Height = 596
    Align = alClient
    TabOrder = 0
    DesignSize = (
      1226
      596)
    object Image1: TImage
      Left = 1
      Top = 1
      Width = 1224
      Height = 594
      Align = alClient
      AutoSize = True
      Center = True
      Stretch = True
      Transparent = True
      ExplicitLeft = 2
    end
    object Label1: TLabel
      Left = 537
      Top = 544
      Width = 11
      Height = 38
      Anchors = [akLeft, akTop, akRight, akBottom]
      BiDiMode = bdRightToLeft
      Font.Charset = ARABIC_CHARSET
      Font.Color = clBlue
      Font.Height = -32
      Font.Name = 'A Iranian Sans'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
    end
    object Label2: TLabel
      Left = 480
      Top = 1
      Width = 13
      Height = 43
      Anchors = [akLeft, akTop, akRight, akBottom]
      BiDiMode = bdRightToLeft
      Font.Charset = ARABIC_CHARSET
      Font.Color = clRed
      Font.Height = -37
      Font.Name = 'A Iranian Sans'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
    end
    object Panel2: TPanel
      Left = 376
      Top = 355
      Width = 266
      Height = 41
      AutoSize = True
      TabOrder = 0
      object Image2: TImage
        Left = 1
        Top = 1
        Width = 264
        Height = 39
        Align = alClient
        Stretch = True
        ExplicitLeft = 241
        ExplicitTop = -23
      end
      object Label3: TLabel
        Left = 1
        Top = 1
        Width = 8
        Height = 24
        Font.Charset = ARABIC_CHARSET
        Font.Color = clNavy
        Font.Height = -21
        Font.Name = 'A Iranian Sans'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object Memo: TMemo
      Left = 1
      Top = 50
      Width = 360
      Height = 532
      Lines.Strings = (
        'App State'
        ''
        '')
      TabOrder = 1
      Visible = False
    end
  end
end
