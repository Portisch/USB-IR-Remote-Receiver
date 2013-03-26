unit UnitDemo;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

//type def for Irmp IR-Data:
type
  TIRData = packed record
    Protocol : Byte;
    Address : Word;
    Command : Word;
    Flags : Byte;
  end;


  //option form of DLL:
  TShowSettings = procedure(Handle: Integer); stdcall;
  //name of plugin
  TPluginName = function():PAnsiChar; stdcall;
  //plugin version
  TPluginVersion = function():PAnsiChar; stdcall;
  //plugin Copyright
  TCopyright = function():PAnsiChar; stdcall;

  //----------------------------------------------------------------------------
  // Use the init procedures (TInitNative or TInitPAnsiChar)
  // to open and handle the device!
  //
  // Before unloading the DLL the init procedure should be called again with NIL
  // to close the device and clean up memory!
  //----------------------------------------------------------------------------

  //receive inputs as PAnsiChar, like NEC, 0x1000, 0x001B
  TCallbackPAnsiChar = procedure(Protocol, Adress, Command, Flags : PAnsiChar); stdcall;
  TInitPAnsiChar = function (Callback : TCallbackPAnsiChar):Boolean; stdcall;

  //native receive inputs as type TIRData:
  TCallbackNative = procedure(IRCode : TIRData); stdcall;
  TInitNative = function (Callback : TCallbackNative):Boolean; stdcall;

type
  TMain = class(TForm)
    btLoadDLL: TButton;
    btInitNativeIRData: TButton;
    LogMemo: TMemo;
    btShowSettings: TButton;
    Panel1: TPanel;
    btInitPAnsiChar: TButton;
    procedure btLoadDLLClick(Sender: TObject);
    procedure OnDestroy(Sender: TObject);
    procedure btInitNativeIRDataClick(Sender: TObject);
    procedure btShowSettingsClick(Sender: TObject);
    procedure btInitPAnsiCharClick(Sender: TObject);
  private
    { Private-Deklarationen }
    hDLL : THandle;                   //DLL Handle
    InitNative : TInitNative;
    InitPAnsiChar : TInitPAnsiChar;

    ShowSettings : TShowSettings;
    PluginName : TPluginName;
    PluginVersion : TPluginVersion;
    Copyright : TCopyright;
  public
    { Public-Deklarationen }
  end;

  //callback procedure for receiving native IRData with type TIRData:
  procedure CallbackNative(IRCode : TIRData); stdcall;
  //callback procedure for receiving IR-Command with PAnsiChar:
  procedure CallbackPAnsiChar(Protocol, Adress, Command, Flags : PAnsiChar); stdcall;


const
  USBIRRemoteReceiver = 'USB_IR_Remote_Receiver.dll';

//irmp const only needed for native IRData:
const
  IRMP_SIRCS_PROTOCOL       = 1;
  IRMP_NEC_PROTOCOL         = 2;
  IRMP_SAMSUNG_PROTOCOL     = 3;
  IRMP_MATSUSHITA_PROTOCOL  = 4;
  IRMP_KASEIKYO_PROTOCOL    = 5;
  IRMP_RECS80_PROTOCOL      = 6;
  IRMP_RC5_PROTOCOL         = 7;
  IRMP_DENON_PROTOCOL       = 8;
  IRMP_RC6_PROTOCOL         = 9;
  IRMP_SAMSUNG32_PROTOCOL   = 10;
  IRMP_APPLE_PROTOCOL       = 11;
  IRMP_RECS80EXT_PROTOCOL   = 12;
  IRMP_NUBERT_PROTOCOL      = 13;

var
  Main: TMain;

implementation

{$R *.dfm}
//------------------------ NATIVE IRDATA ---------------------------------------
//needed for native IRData, transform const Protocol to string
function GetIRProtocol(Index: Integer): String;
begin
  case Index of
    0 : Result := 'Unkown';
    IRMP_SIRCS_PROTOCOL : Result := 'SIRCS';
    IRMP_NEC_PROTOCOL : Result := 'NEC';
    IRMP_SAMSUNG_PROTOCOL : Result := 'SAMSUNG';
    IRMP_MATSUSHITA_PROTOCOL : Result := 'MATSUSHITA';
    IRMP_KASEIKYO_PROTOCOL : Result := 'KASEIKYO';
    IRMP_RECS80_PROTOCOL : Result := 'RECS80';
    IRMP_RC5_PROTOCOL : Result := 'RC5';
    IRMP_DENON_PROTOCOL : Result := 'DENON';
    IRMP_RC6_PROTOCOL : Result := 'RC6';
    IRMP_SAMSUNG32_PROTOCOL : Result := 'SAMSUNG32';
    IRMP_APPLE_PROTOCOL : Result := 'APPLE';
    IRMP_RECS80EXT_PROTOCOL : Result := 'RECS80EXT';
    IRMP_NUBERT_PROTOCOL : Result := 'NUBERT';
    else
      Result := 'Undefined';
  end;
end;

//------------------------ NATIVE IRDATA ---------------------------------------
//Callback for DLL, it will receive type TIRData
procedure CallbackNative(IRCode : TIRData); stdcall;
begin
  Main.LogMemo.Lines.Add('Native Code Received:' + #13#10
    + #9 + GetIRProtocol(IRCode.Protocol) + #13#10
    + #9 + '0x' + IntToHex(IRCode.Address, 4) + #13#10
    + #9 + '0x' + IntToHex(IRCode.Command, 4) + #13#10
    + #9 + '0x' + IntToHex(IRCode.Flags, 2));
end;

//------------------------ NATIVE IRDATA ---------------------------------------
//button init DLL for native data receive
procedure TMain.btInitNativeIRDataClick(Sender: TObject);
begin
  if hDLL <> 0 then
  begin
    @InitNative := GetProcAddress(hDLL, 'InitNative');

    if Assigned(InitNative) then
    begin
      If InitNative(@CallbackNative) then
      begin
        btShowSettings.Enabled := True;
        btInitPAnsiChar.Enabled := False;
        LogMemo.Lines.Add('InitNative is used!');
      end;
    end;
  end;
end;

//---------------------------- PAnsiChar ---------------------------------------
//Callback for DLL, it will receive Protocol, Adress, Command  as PAnsiChar
procedure CallbackPAnsiChar(Protocol, Adress, Command, Flags : PAnsiChar); stdcall;
begin
  Main.LogMemo.Lines.Add('PAnsiChar Code Received:' + #13#10
    + #9 + Protocol + #13#10
    + #9 + Adress + #13#10
    + #9 + Command + #13#10
    + #9 + Flags);
end;

//---------------------------- PAnsiChar ---------------------------------------
//button init DLL for PAnsiChar data receive
procedure TMain.btInitPAnsiCharClick(Sender: TObject);
begin
  if hDLL <> 0 then
  begin
    @InitPAnsiChar := GetProcAddress(hDLL, 'InitPAnsiChar');

    if Assigned(InitPAnsiChar) then
    begin
      If InitPAnsiChar(@CallbackPAnsiChar) then
      begin
        btShowSettings.Enabled := True;
        btInitNativeIRData.Enabled := False;
        LogMemo.Lines.Add('InitPAnsiChar is used!');
      end;
    end;
  end;
end;


//---------------------------- General ---------------------------------------
//button to load DLL
//Assign ShowSettings to show options dialog of DLL
procedure TMain.btLoadDLLClick(Sender: TObject);
begin
  if hDLL = 0 then
  begin

    hDLL := LoadLibrary(USBIRRemoteReceiver);

    if hDLL <> 0 then
    begin
      btInitNativeIrData.Enabled := True;
      btInitPAnsiChar.Enabled := True;

      //load stettings dialog:
      @ShowSettings := GetProcAddress(hDLL, 'ShowSettings');
      //load other functions
      @PluginName := GetProcAddress(hDLL, 'PluginName');
      @PluginVersion := GetProcAddress(hDLL, 'Version');
      @Copyright := GetProcAddress(hDLL, 'Copyright');


      LogMemo.Lines.Add('''USB_IR_Remote_Receiver.dll'' loaded successfully!');
      LogMemo.Lines.Add('Plugin name: ' + PluginName);
      LogMemo.Lines.Add('Plugin version: ' + PluginVersion);
      LogMemo.Lines.Add('Copyright: ' + Copyright);
    end;
  end;

end;

//---------------------------- General ---------------------------------------
//button to show options dialog of DLL
procedure TMain.btShowSettingsClick(Sender: TObject);
begin
  if Assigned(ShowSettings) then
    ShowSettings(Self.Handle);
end;

procedure TMain.OnDestroy(Sender: TObject);
begin
  //------------------------ NATIVE IRDATA -------------------------------------
  //If native was used, set InitNative(NIL) to close device
  if Assigned(InitNative) then
      InitNative(NIL);

  //---------------------------- PAnsiChar -------------------------------------
  //If native was used, set InitPAnsiChar(NIL) to close device
  if Assigned(InitPAnsiChar) then
    InitPAnsiChar(NIL);

  //unload DLL
  if hDLL <> 0 then
    FreeLibrary(hDLL);
end;

end.
