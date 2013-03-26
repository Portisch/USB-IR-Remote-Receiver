object Main: TMain
  Left = 0
  Top = 0
  Caption = 'DLL Demo'
  ClientHeight = 304
  ClientWidth = 552
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnDestroy = OnDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object LogMemo: TMemo
    Left = 137
    Top = 0
    Width = 415
    Height = 304
    Align = alClient
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 137
    Height = 304
    Align = alLeft
    TabOrder = 1
    object btInitNativeIRData: TButton
      Left = 8
      Top = 39
      Width = 113
      Height = 25
      Caption = 'InitNative IRData'
      Enabled = False
      TabOrder = 0
      OnClick = btInitNativeIRDataClick
    end
    object btLoadDLL: TButton
      Left = 8
      Top = 8
      Width = 113
      Height = 25
      Caption = 'load DLL'
      TabOrder = 1
      OnClick = btLoadDLLClick
    end
    object btShowSettings: TButton
      Left = 8
      Top = 128
      Width = 113
      Height = 25
      Caption = 'Show Settings'
      Enabled = False
      TabOrder = 2
      OnClick = btShowSettingsClick
    end
    object btInitPAnsiChar: TButton
      Left = 8
      Top = 70
      Width = 113
      Height = 25
      Caption = 'Init PAnsiChar'
      Enabled = False
      TabOrder = 3
      OnClick = btInitPAnsiCharClick
    end
  end
end
