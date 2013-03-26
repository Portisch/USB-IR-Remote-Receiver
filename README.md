USB-IR-Remote-Receiver
======================

Ein Infrarot-Multiprotokoll-Decoder in Kombination mit IRMP von Frank M. und V-USB für die USB Schnittstelle

http://www.mikrocontroller.net/articles/USB_IR_Remote_Receiver


02.01.2012	DLL: 	• v1.0.0.14, IR Polling entfernt, IRMP Logging per USB hinzugefügt 
		AVR: 	• v1.8, IR Polling entfernt, IRMP Logging per USB hinzugefügt. Source für AVR Studio v5 konvertiert.

26.10.2011	DLL: 	• v1.0.0.13, Neue Irmp Protokolle in die Standard Liste aufgenommen
		AVR: 	• v1.7, IRMP Update auf 20.09.2011, neues Protokoll RUWIDO, KATHREIN, NEC16, NEC42, LEGO und THOMSON.

14.07.2011	DLL: 	• v1.0.0.12, Problem mit EventGhost behoben

28.02.2011	Demo: 	• neuen Demo Source für Visual Studio 2008 C# aufgenommen. Danke an Michael Kipp für seine Arbeit

27.02.2011	DLL: 	• v1.0.0.11, Problem mit EventGhost behoben, Problem mit InitNative/InitPAnsiChar behoben

04.02.2011	AVR: 	• v1.6, Source und Release für Atmega8/Atmega168p.
			• bootLoadHID v1.1 Source und Release für Atmega8/Atmega168p.

27.01.2011	DLL:	• v1.0.0.10, Neue Irmp Protokolle in die Standard Liste aufgenommen.
		AVR:	• v1.5, IRMP Update auf 18.01.2011, neues Protokoll RC6A, JVC und NIKON.

28.06.2010	DLL:	• v1.0.0.9, Neue Irmp Protokolle in die Standard Liste aufgenommen.
		AVR:	• v1.4, IRMP Update auf 26.06.2010, neues Protokoll FDC und RCCAR.

06.06.2010	DLL:	• v1.0.0.8, Protokolle die in der INI Datei fehlen werden nun automatisch eingetragen. Neue Irmp Protokolle in die Standard Liste aufgenommen.
		AVR:	• v1.3, IRMP Update auf 02.06.2010, neues Protokoll NOKIA und SIEMENS

18.05.2010	DLL:	• v1.0.0.7, Grundig Protokoll für INI-Datei aufgenommen. Bei fehlender INI-Datei werden die Protokolle automatisch eingetragen. Beim manuellen Einfügen von "GRUNDIG=15" kann auch die alte v1.0.0.6 weiter verwendet werden. Siehe INI Beschreibung.
		AVR:	• v1.2, IRMP Update auf 17.05.2010, neues Protokoll GRUNDIG, Bugfix SAMSUNG32

09.05.2010	DLL:	• v1.0.0.6, Bugfix für Standby - die Verbindung zum Gerät wurde nicht richtig getrennt
		Sonstiges:
			• Plugin für EventGhost wurde hinzugefügt
			• Dokumentation überarbeitet

02.05.2010	Dokumentation überarbeitet, PonyProg2000 im Schaltplan aufgenommen.

28.04.2010	DLL:	• v1.0.0.5, Möglichkeit um die Firmware über den Settings/Optionen Dialog auf den Mikrochip programmieren zu können hinzugefügt.
		AVR:	• Bugfix der Entprellung
			• Irmp Version Update auf 28.04.2010
			• modifizierter bootloadHID um über den Settings/Optionen Dialog eine neue Firmware aufspielen zu können

23.04.2010	DLL:	• v1.0.0.4, Tasten Unterdrückung für träge Host Anwendung hinzugefügt
			• Bugfix für Settings/Optionen Dialog und DVBViewer
		AVR:	• Bugfix der Entprellung wenn die Taste länger als 255 Wiederholungen gedrückt war
 			• Erkennung/Auswertung des PowerOn IR-Code optimiert	

16.04.2010	DLL:	• v1.0.0.3, InitNative, InitPAnsiChar und Girder Unterstützung hinzugefügt
		AVR:	• Irmp Version Update auf 16.04.2010

12.04.2010	AVR:	• Irmp Version Update auf 12.04.2010, neues Protokoll B&Q

