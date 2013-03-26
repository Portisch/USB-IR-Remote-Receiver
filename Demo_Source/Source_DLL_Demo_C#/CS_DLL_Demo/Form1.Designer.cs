namespace CS_DLL_Demo
{
    partial class frmMain
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.btCloseDevice = new System.Windows.Forms.Button();
            this.btOpenPAnsiChar = new System.Windows.Forms.Button();
            this.btShowSettings = new System.Windows.Forms.Button();
            this.txtMessages = new System.Windows.Forms.TextBox();
            this.btOpenNative = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btCloseDevice
            // 
            this.btCloseDevice.Enabled = false;
            this.btCloseDevice.Location = new System.Drawing.Point(351, 12);
            this.btCloseDevice.Name = "btCloseDevice";
            this.btCloseDevice.Size = new System.Drawing.Size(107, 64);
            this.btCloseDevice.TabIndex = 9;
            this.btCloseDevice.Text = "Close Device";
            this.btCloseDevice.UseVisualStyleBackColor = true;
            this.btCloseDevice.Click += new System.EventHandler(this.btCloseDevice_Click);
            // 
            // btOpenPAnsiChar
            // 
            this.btOpenPAnsiChar.Location = new System.Drawing.Point(125, 12);
            this.btOpenPAnsiChar.Name = "btOpenPAnsiChar";
            this.btOpenPAnsiChar.Size = new System.Drawing.Size(107, 64);
            this.btOpenPAnsiChar.TabIndex = 8;
            this.btOpenPAnsiChar.Text = "Open Device PAnsiChar";
            this.btOpenPAnsiChar.UseVisualStyleBackColor = true;
            this.btOpenPAnsiChar.Click += new System.EventHandler(this.btOpenPAnsiChar_Click);
            // 
            // btShowSettings
            // 
            this.btShowSettings.Enabled = false;
            this.btShowSettings.Location = new System.Drawing.Point(238, 12);
            this.btShowSettings.Name = "btShowSettings";
            this.btShowSettings.Size = new System.Drawing.Size(107, 64);
            this.btShowSettings.TabIndex = 7;
            this.btShowSettings.Text = "Show Settings";
            this.btShowSettings.UseVisualStyleBackColor = true;
            this.btShowSettings.Click += new System.EventHandler(this.btShowSettings_Click);
            // 
            // txtMessages
            // 
            this.txtMessages.Location = new System.Drawing.Point(12, 91);
            this.txtMessages.Multiline = true;
            this.txtMessages.Name = "txtMessages";
            this.txtMessages.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtMessages.Size = new System.Drawing.Size(446, 425);
            this.txtMessages.TabIndex = 6;
            this.txtMessages.TextChanged += new System.EventHandler(this.txtMessages_TextChanged);
            // 
            // btOpenNative
            // 
            this.btOpenNative.Location = new System.Drawing.Point(12, 12);
            this.btOpenNative.Name = "btOpenNative";
            this.btOpenNative.Size = new System.Drawing.Size(107, 64);
            this.btOpenNative.TabIndex = 5;
            this.btOpenNative.Text = "Open Device Native";
            this.btOpenNative.UseVisualStyleBackColor = true;
            this.btOpenNative.Click += new System.EventHandler(this.btOpenNative_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(470, 528);
            this.Controls.Add(this.btCloseDevice);
            this.Controls.Add(this.btOpenPAnsiChar);
            this.Controls.Add(this.btShowSettings);
            this.Controls.Add(this.txtMessages);
            this.Controls.Add(this.btOpenNative);
            this.Name = "frmMain";
            this.Text = "C#-DLL-Demo";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btCloseDevice;
        private System.Windows.Forms.Button btOpenPAnsiChar;
        private System.Windows.Forms.Button btShowSettings;
        private System.Windows.Forms.TextBox txtMessages;
        private System.Windows.Forms.Button btOpenNative;

    }
}

