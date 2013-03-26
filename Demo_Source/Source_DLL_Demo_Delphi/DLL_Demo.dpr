program DLL_Demo;

uses
  Forms,
  UnitDemo in 'UnitDemo.pas' {Main};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TMain, Main);
  Application.Run;
end.
