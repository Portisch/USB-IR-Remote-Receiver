using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;

namespace CS_DLL_Demo
{
    public class USB_IRRR
    {
        private bool NativeMode = false;    // true = Native mode; false = PAnsiChar mode
        private dlgtNative Native;          // reference for Native mode delegate
        private dlgtPAnsiChar PAnsiChar;    // reference for PAnsiChar mode delegate

        private frmMain MainForm;             // an instance of the main form for updating the textBox
        private delegate void UpdateForm(bool ClearFirst, string Text); // delegate to the update method

        // constructor: get the reference of the calling form
        public USB_IRRR(frmMain _mainform)
        {
            MainForm = _mainform;
        }

        #region Import/Invoke functions from DLL

        const string USB_IRRR_DllName = "USB_IR_Remote_Receiver.dll"; // name of the DLL

        // DLL plugin name
        [DllImport(USB_IRRR_DllName,
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.StdCall,
            EntryPoint = "PluginName")]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string PluginName();
        
        // DLL version
        [DllImport(USB_IRRR_DllName,
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.StdCall,
            EntryPoint = "Version")]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string Version();

        // DLL copyright
        [DllImport(USB_IRRR_DllName,
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.StdCall,
            EntryPoint = "Copyright")]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string Copyright();

        // DLL show settings dialog
        [DllImport(USB_IRRR_DllName,
            CallingConvention = CallingConvention.StdCall,
            EntryPoint = "ShowSettings")]
        private static extern void ShowSettings(int hwnd);

        // DLL init Native mode
        [DllImport(USB_IRRR_DllName,
            CallingConvention = CallingConvention.StdCall,
            EntryPoint = "InitNative")]
        private static extern bool InitNative(dlgtNative dlgt);

        // DLL init PAnsiChar mode
        [DllImport(USB_IRRR_DllName,
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.StdCall,
            EntryPoint = "InitPAnsiChar")]
        private static extern bool InitPAnsiChar(dlgtPAnsiChar dlgt);

        #endregion

        #region Struct for native mode and delegates for both modes

        // struct for native IR data callback
        [StructLayout(LayoutKind.Explicit)]
        private struct IrmpData
        {
            [MarshalAs(UnmanagedType.U1), FieldOffset(0)]public byte Protocol;
            [MarshalAs(UnmanagedType.U2), FieldOffset(1)]public ushort Address;
            [MarshalAs(UnmanagedType.U2), FieldOffset(3)]public ushort Command;
            [MarshalAs(UnmanagedType.U1), FieldOffset(5)]public byte Flags;
        }

        // delegate for Native mode
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void dlgtNative(IrmpData ir_code);

        // delegate for PAnsiChar mode
        private delegate void dlgtPAnsiChar(
                [MarshalAs(UnmanagedType.LPStr), Out]string Protocol,
                [MarshalAs(UnmanagedType.LPStr), Out]string Address,
                [MarshalAs(UnmanagedType.LPStr), Out]string Command,
                [MarshalAs(UnmanagedType.LPStr), Out]string Flags);

        #endregion

        // callback function for Native mode
        private void MyCallBackNative(IrmpData ir_code)
        {
            UpdateForm update = new UpdateForm(MainForm.UpdateMessageBox);

            MainForm.Invoke(update, false,
                 String.Format("Protocol=0x{0}, Address=0x{1}, Command=0x{2}, Flags=0x{3}\r\n",
                    ir_code.Protocol.ToString("X2"), ir_code.Address.ToString("X4"),
                    ir_code.Command.ToString("X4"), ir_code.Flags.ToString("X2")));
        }

        // callback function for PAnsiChar mode
        private void MyCallBackPAnsiChar(string Protocol, string Address, string Command, string Flags)
        {
            UpdateForm update = new UpdateForm(MainForm.UpdateMessageBox);

            MainForm.Invoke(update, false,
                String.Format("Protocol={0}, Address={1}, Command={2}, Flags={3}\r\n",
                    Protocol, Address, Command, Flags));
        }

        // method to open device in Native mode
        public bool OpenNative()
        {
            NativeMode = true;
            return OpenIRCom();
        }

        // method to open device in PAnsiChar mode
        public bool OpenPAnsiChar()
        {
            NativeMode = false;
            return OpenIRCom();
        }

        // open device; mode is selected depending on state of NativeData
        // => see OpenNative() and OpenPAnsiChar()
        private bool OpenIRCom()
        {
            UpdateForm update = new UpdateForm(MainForm.UpdateMessageBox);

            try
            {
                if (NativeMode == true)
                {
                    Native = new dlgtNative(MyCallBackNative);
                    return InitNative(Native);
                }
                else
                {
                    PAnsiChar = new dlgtPAnsiChar(MyCallBackPAnsiChar);
                    return InitPAnsiChar(PAnsiChar);
                }
            }
            catch (DllNotFoundException)
            {
                MainForm.Invoke(update, true,
                    String.Format("ERROR: unable to find DLL '{0}'!\r\n", USB_IRRR_DllName));
                return false;
            }
            catch (SEHException)
            {
                MainForm.Invoke(update, true,
                    String.Format("ERROR: SEHException occured!\r\nRestart the application to change the mode or use a DLL version above 1.0.0.10."));
                return false;
            }
        }

        // method to open settings dialog
        public void OpenSettingsDialog(int hwnd)
        {
            ShowSettings(hwnd);
        }

        // method to close device and to delete references
        public bool CloseDevice()
        {
            try
            {
                if (NativeMode)
                {
                    Native = null;
                    return InitNative(null);
                }
                else
                {
                    PAnsiChar = null;
                    return InitPAnsiChar(null);
                }
            }
            catch //(DllNotFoundException)
            {
                return false;
            }
        }
    }
}
