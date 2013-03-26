using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CS_DLL_Demo
{
    public partial class frmMain : Form
    {
        // create a reference; without it a CallbackOnCollectedDelegate-MDA will appear later
        USB_IRRR usb_irrr;

        public frmMain()
        {
            InitializeComponent();
            usb_irrr = new USB_IRRR(this);
        }

        // open device in Native mode
        private void btOpenNative_Click(object sender, EventArgs e)
        {
            if (usb_irrr.OpenNative())
            {
                txtMessages.Text = "";
                txtMessages.Text += "Plugin Name: " + USB_IRRR.PluginName() + "\r\n";
                txtMessages.Text += "Plugin Version: " + USB_IRRR.Version() + "\r\n";
                txtMessages.Text += "Plugin Copyright: " + USB_IRRR.Copyright() + "\r\n";
                txtMessages.Text += "InitNative is used!\r\n";
                btShowSettings.Enabled = true;
                btCloseDevice.Enabled = true;
                btOpenNative.Enabled = false;
                btOpenPAnsiChar.Enabled = false;
            }
        }

        // open device in PAnsiChar mode
        private void btOpenPAnsiChar_Click(object sender, EventArgs e)
        {
            if (usb_irrr.OpenPAnsiChar())
            {
                txtMessages.Text = "";
                txtMessages.Text += "Plugin Name: " + USB_IRRR.PluginName() + "\r\n";
                txtMessages.Text += "Plugin Version: " + USB_IRRR.Version() + "\r\n";
                txtMessages.Text += "Plugin Copyright: " + USB_IRRR.Copyright() + "\r\n";
                txtMessages.Text += "InitPAnsiChar is used!\r\n";
                btShowSettings.Enabled = true;
                btCloseDevice.Enabled = true;
                btOpenNative.Enabled = false;
                btOpenPAnsiChar.Enabled = false;
            }
        }

        // show settings dialog
        private void btShowSettings_Click(object sender, EventArgs e)
        {
            usb_irrr.OpenSettingsDialog(this.Handle.ToInt32());
        }

        // close device
        private void btCloseDevice_Click(object sender, EventArgs e)
        {
            if (usb_irrr.CloseDevice())
            {
                txtMessages.Text = "Device has been closed!";
                btShowSettings.Enabled = false;
                btCloseDevice.Enabled = false;
                btOpenNative.Enabled = true;
                btOpenPAnsiChar.Enabled = true;
            }
        }

        // update the content of the TextBox w/o clearing it first
        public void UpdateMessageBox(bool ClearFirst, string Text)
        {
            if (ClearFirst == true)
            {
                txtMessages.Clear();
            }

            txtMessages.AppendText(Text);
        }

        // always scroll to the end of the textBox
        private void txtMessages_TextChanged(object sender, EventArgs e)
        {
            txtMessages.SelectionStart = txtMessages.Text.Length;
            txtMessages.ScrollToCaret();
        }

        // close device and delete reference on application exit
        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            usb_irrr.CloseDevice();
            usb_irrr = null;
        }
    }
}
