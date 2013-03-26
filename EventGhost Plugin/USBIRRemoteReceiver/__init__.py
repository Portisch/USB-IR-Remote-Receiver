import eg

eg.RegisterPlugin(
    name = "USB IR Remote Receiver",
    author = "Portisch",
    version = "0.0.1",
    kind = "remote",
    description = (
        'EventGhost Plugin for the multiprotocol infrared '
        '<a href="http://www.mikrocontroller.net/articles/USB_IR_Remote_Receiver">USB IR Remote Receiver</a>.'
        )
)

import ctypes
import os
from ctypes import *

class USBIRRemoteReceiver(eg.PluginBase):

    def ReceivedIRCode(self, Protocol, Address, Command, Flags):
        self.TriggerEvent("Protocol: " + Protocol + ", Address: 0x" + Address + ", Command: 0x" + Command)

    def __init__(self):
        print ("USBIRRemoteReceiver: Plugin gets loaded.")
        print ("USBIRRemoteReceiver: Actual path: " + os.path.dirname(os.path.abspath(__file__)))
        print ("USBIRRemoteReceiver: Try to load ''USB_IR_Remote_Receiver.dll''")
        self.DLLfilename = os.path.dirname(os.path.abspath(__file__)) + ("\USB_IR_Remote_Receiver.dll")
        print self.DLLfilename
        if os.path.isfile(self.DLLfilename):
            self.PluginFound = True
            self.dll = ctypes.windll.LoadLibrary(self.DLLfilename)               
            print ("USBIRRemoteReceiver: USB_IR_Remote_Receiver.dll found and loaded!")
            self.dll.PluginName.restype = c_char_p
            print ("USBIRRemoteReceiver: DLL Plugin Name: " + self.dll.PluginName())            
            self.dll.Version.restype = c_char_p
            print ("USBIRRemoteReceiver: DLL Plugin Version: " + self.dll.Version())
            self.dll.Copyright.restype = c_char_p
            print ("USBIRRemoteReceiver: DLL Plugin Copyright: " + self.dll.Copyright())
            self.dll.Initialized = False
            print ("USBIRRemoteReceiver: Init of USB IR Remote Receiver finished!")
        else:
            self.PluginFound = False
            print ("USBIRRemoteReceiver: USB_IR_Remote_Receiver.dll not found!")         
    def __start__(self):
        if self.PluginFound:        
            if not self.dll.Initialized:
                # funtion prototype
                prototype = WINFUNCTYPE(None, c_char_p, c_char_p, c_char_p, c_char_p)
                # create callback function            
                self.MyIRCallback = prototype(self.ReceivedIRCode)        
                self.dll.InitPAnsiChar(self.MyIRCallback)
                self.dll.Initialized = True
                print ("USBIRRemoteReceiver: Plugin got enabled")
            else:
                print ("USBIRRemoteReceiver: Plugin already enabled!")

    def __stop__(self):
        if self.PluginFound:
            self.dll.InitPAnsiChar(None)
            self.dll.Initialized = False
            print ("USBIRRemoteReceiver: Plugin got disabled")

    def __close__(self):
        if self.PluginFound:
            if self.dll.Initialized:
                self.dll.InitPAnsiChar(None)
                self.dll.Initialized = False
            ctypes.windll.kernel32.CloseHandle(self.dll._handle)
            print ("USBIRRemoteReceiver: USB_IR_Remote_Receiver.DLL is unloaded!")        

    def Configure(self, *args):        
        panel = eg.ConfigPanel()
        if self.PluginFound:
            if self.dll.Initialized:
                ButtonLabel = 'Show Settings/Option Dialog of Plugin'
            else:
                ButtonLabel = 'Plugin is not enabled! Can not show Settings/Option Dialog\n\nEnable the Plugin first!'
        else:
            ButtonLabel = 'USB_IR_Remote_Receiver.DLL not found!\n\nThe DLL should be located at:\n' + self.DLLfilename
        self.ShowSettingsButton = wx.Button(panel, id=-1, label=ButtonLabel)
        self.ShowSettingsButton.Bind(wx.EVT_BUTTON, self.ShowSettingsButtonClick)
        if not self.PluginFound:
            self.ShowSettingsButton.Disable()
        panel.sizer.Add(self.ShowSettingsButton, 1, wx.EXPAND)           
        while panel.Affirmed():
            panel.SetResult()

    def ShowSettingsButtonClick(self,event):
        try:
            if self.PluginFound:
                self.dll.ShowSettings.restype = None
                self.dll.ShowSettings(eg.app.hwnd)       
        except:
            print ("USBIRRemoteReceiver: Error showing Settings/Options dialog")


        


