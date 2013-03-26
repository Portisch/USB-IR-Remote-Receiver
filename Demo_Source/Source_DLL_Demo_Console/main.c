/////////////////////////////////////////////////////////////////
// example how to load and work with the "USB IR Remote Receiver"
// this example is written with Visual Studio 2008
// (c) by Portisch 2010
/////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>

// DLL Version
typedef char* (__stdcall *impVersion)(void);
// DLL Copyright
typedef char* (__stdcall *impCopyright)(void);
// DLL PluginName
typedef char* (__stdcall *impPluginName)(void);

// DLL Option dialog
typedef void (__stdcall *impShowSettings)(HWND);

// native IR Data by PAnsiChar
typedef void CALLBACK CallBackPAnsiChar(char*, char*, char*, char*);
typedef int (__stdcall *impInitPAnsiChar)(CallBackPAnsiChar);

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;

// native IR Data init
#pragma pack(1) // set pack alignment to 1 padding byte
typedef struct
{
	BYTE Protocol;
	WORD Address;
	WORD Command;
	BYTE Flags;
} IRMP_DATA;
#pragma pack() // default alignment

typedef void CALLBACK CallBackIRData(IRMP_DATA);
typedef int (__stdcall *impInitIRData)(CallBackIRData);

CALLBACK MyCallBackPAnsiChar(char* Protocol, char* Address, char* Command, char* Flags)
{
	printf("\nIR Data received: Protocol: %s, Address: 0x%s, Command: 0x%s, Flags: 0x%s", Protocol, Address, Command, Flags);
}

CALLBACK MyCallBackIRData(IRMP_DATA ir_code)
{
	printf("\nIR Data received: Protocol: 0x%02X, Address: 0x%04X, Command: 0x%04X, Flags: 0x%02X", ir_code.Protocol, ir_code.Address, ir_code.Command, ir_code.Flags);
}
 
int main(int argc, char **argv)
{
	impVersion Version = NULL;
	impCopyright Copyright = NULL;
	impPluginName PluginName = NULL;
	impInitPAnsiChar InitPAnsiChar = NULL;
	impInitIRData InitNative = NULL;
	impShowSettings ShowSettings = NULL;
	
	char ch;
	HWND hwnd;
	char * Buffer;
 
	// Load DLL file
	HINSTANCE hinstLib = LoadLibrary(TEXT("USB_IR_Remote_Receiver.dll"));
	if (hinstLib == NULL) {
		printf("\nERROR: unable to load DLL\n");
		return 1;
	}

	// Get function pointer PluginName
	PluginName = (impPluginName)GetProcAddress(hinstLib, "PluginName");
	if (PluginName == NULL) {
		printf("\nERROR: unable to find DLL function\n");
		FreeLibrary(hinstLib);
		return 1;
	}
 
	// Get function pointer Version
	Version = (impVersion)GetProcAddress(hinstLib, "Version");
	if (Version == NULL) {
		printf("\nERROR: unable to find DLL function\n");
		FreeLibrary(hinstLib);
		return 1;
	}
 
	// Get function pointer Copyright
	Copyright = (impCopyright)GetProcAddress(hinstLib, "Copyright");
	if (Copyright == NULL) {
		printf("\nERROR: unable to find DLL function\n");
		FreeLibrary(hinstLib);
		return 1;
	}

	// Get function pointer ShowSettings
	ShowSettings = (impShowSettings)GetProcAddress(hinstLib, "ShowSettings");
	if (ShowSettings == NULL) {
		printf("\nERROR: unable to find DLL function\n");
		FreeLibrary(hinstLib);
		return 1;
	}

	// Call function.
	Buffer = PluginName();
	// Display result
	printf("\nThe DLL PluginName is: %s\n", Buffer);

	// Call function.
	Buffer = Version();
	// Display result
	printf("\nThe DLL version is: %s\n", Buffer);

	// Call function.
	Buffer = Copyright();
	// Display result
	printf("\nThe DLL Copyright is: %s\n", Buffer);

	printf("\nPlease define if DLL init by native IR Data or by PAnsiChar!");
	printf("\nPress [1] for native IR Data");
	printf("\nPress [2] for IR Data in PAnsiChar");
	printf("\n\nPlease enter a command!");

	ch = getch();
	switch(ch)
	{
		case '1':
					// Get function pointer InitNative
					InitNative = (impInitPAnsiChar)GetProcAddress(hinstLib, "InitNative");
					if (InitNative == NULL) {
						printf("\nERROR: unable to find DLL function\n");
						FreeLibrary(hinstLib);
						return 1;
					}

					if (InitNative(*MyCallBackIRData))
					{
						printf("\nInit DLL with InitIRData successfull");
					}
					else
					{
						// Unload DLL file
						FreeLibrary(hinstLib);
						return 0;
					}
				break;
		case '2':
					// Get function pointer InitPAnsiChar
					InitPAnsiChar = (impInitPAnsiChar)GetProcAddress(hinstLib, "InitPAnsiChar");
					if (InitPAnsiChar == NULL) {
						printf("\nERROR: unable to find DLL function\n");
						FreeLibrary(hinstLib);
						return 1;
					}

					if (InitPAnsiChar(*MyCallBackPAnsiChar))
					{
						printf("\nInit DLL with InitPAnsiChar successfull");
					}
					else
					{
						// Unload DLL file
						FreeLibrary(hinstLib);
						return 0;
					}
				break;
	}

	printf("\n\nPress [s] to show settings dialog");
	printf("\nPress [x] to exit");
	printf("\n\nPlease enter a command!");

	// get hwnd from console window
	hwnd = GetConsoleWindow();

	// repeat until exit
	while(1)
	{
		ch = getch();
		switch(ch)
		{
			// show settings/options dialog of DLL
			case 's':
					//show settings dialog of DLL
					ShowSettings(&hwnd);
					break;
			// exit program
			case 'x':
					if (InitNative != NULL)
						InitNative(NULL);
					if (InitPAnsiChar != NULL)
						InitPAnsiChar(NULL);
					// Unload DLL file
					FreeLibrary(hinstLib);
					return 0;
		}
	}
	return 0;
}