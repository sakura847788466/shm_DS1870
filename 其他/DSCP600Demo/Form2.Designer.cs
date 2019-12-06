namespace DSCP600Demo
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btEnumPrinter = new System.Windows.Forms.Button();
            this.cbBPerinterName = new System.Windows.Forms.ComboBox();
            this.btClose = new System.Windows.Forms.Button();
            this.btOpen = new System.Windows.Forms.Button();
            this.btDSAIOMoveCardToColorPrintFromCardBox = new System.Windows.Forms.Button();
            this.btDSAIOMoveCardToExitFromColorPrint = new System.Windows.Forms.Button();
            this.btDSAIOMoveCardToReadCardFromCardBox = new System.Windows.Forms.Button();
            this.btDSAIOMoveCardToColorFromReadCard = new System.Windows.Forms.Button();
            this.btDSAIOReadCardPosition = new System.Windows.Forms.Button();
            this.btDSAIOReadStatus = new System.Windows.Forms.Button();
            this.btDSAIOPrinterRelevancy = new System.Windows.Forms.Button();
            this.btDSAIOCardSetRead = new System.Windows.Forms.Button();
            this.btDSAIOCardSetWrite = new System.Windows.Forms.Button();
            this.rTBResult = new System.Windows.Forms.RichTextBox();
            this.cbBExit = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // btEnumPrinter
            // 
            this.btEnumPrinter.Location = new System.Drawing.Point(12, 12);
            this.btEnumPrinter.Name = "btEnumPrinter";
            this.btEnumPrinter.Size = new System.Drawing.Size(75, 23);
            this.btEnumPrinter.TabIndex = 0;
            this.btEnumPrinter.Text = "枚举";
            this.btEnumPrinter.UseVisualStyleBackColor = true;
            this.btEnumPrinter.Click += new System.EventHandler(this.btEnumPrinter_Click);
            // 
            // cbBPerinterName
            // 
            this.cbBPerinterName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbBPerinterName.FormattingEnabled = true;
            this.cbBPerinterName.Location = new System.Drawing.Point(104, 14);
            this.cbBPerinterName.Name = "cbBPerinterName";
            this.cbBPerinterName.Size = new System.Drawing.Size(181, 20);
            this.cbBPerinterName.TabIndex = 1;
            // 
            // btClose
            // 
            this.btClose.Location = new System.Drawing.Point(404, 14);
            this.btClose.Name = "btClose";
            this.btClose.Size = new System.Drawing.Size(75, 23);
            this.btClose.TabIndex = 2;
            this.btClose.Text = "关闭";
            this.btClose.UseVisualStyleBackColor = true;
            this.btClose.Click += new System.EventHandler(this.btClose_Click);
            // 
            // btOpen
            // 
            this.btOpen.Location = new System.Drawing.Point(309, 14);
            this.btOpen.Name = "btOpen";
            this.btOpen.Size = new System.Drawing.Size(75, 23);
            this.btOpen.TabIndex = 3;
            this.btOpen.Text = "打开";
            this.btOpen.UseVisualStyleBackColor = true;
            this.btOpen.Click += new System.EventHandler(this.btOpen_Click);
            // 
            // btDSAIOMoveCardToColorPrintFromCardBox
            // 
            this.btDSAIOMoveCardToColorPrintFromCardBox.Location = new System.Drawing.Point(104, 66);
            this.btDSAIOMoveCardToColorPrintFromCardBox.Name = "btDSAIOMoveCardToColorPrintFromCardBox";
            this.btDSAIOMoveCardToColorPrintFromCardBox.Size = new System.Drawing.Size(181, 23);
            this.btDSAIOMoveCardToColorPrintFromCardBox.TabIndex = 4;
            this.btDSAIOMoveCardToColorPrintFromCardBox.Text = "从卡盒移卡到彩色打印位";
            this.btDSAIOMoveCardToColorPrintFromCardBox.UseVisualStyleBackColor = true;
            this.btDSAIOMoveCardToColorPrintFromCardBox.Click += new System.EventHandler(this.btDSAIOMoveCardToColorPrintFromCardBox_Click);
            // 
            // btDSAIOMoveCardToExitFromColorPrint
            // 
            this.btDSAIOMoveCardToExitFromColorPrint.Location = new System.Drawing.Point(104, 108);
            this.btDSAIOMoveCardToExitFromColorPrint.Name = "btDSAIOMoveCardToExitFromColorPrint";
            this.btDSAIOMoveCardToExitFromColorPrint.Size = new System.Drawing.Size(181, 23);
            this.btDSAIOMoveCardToExitFromColorPrint.TabIndex = 5;
            this.btDSAIOMoveCardToExitFromColorPrint.Text = "从彩色打印位排卡";
            this.btDSAIOMoveCardToExitFromColorPrint.UseVisualStyleBackColor = true;
            this.btDSAIOMoveCardToExitFromColorPrint.Click += new System.EventHandler(this.btDSAIOMoveCardToExitFromColorPrint_Click);
            // 
            // btDSAIOMoveCardToReadCardFromCardBox
            // 
            this.btDSAIOMoveCardToReadCardFromCardBox.Location = new System.Drawing.Point(104, 149);
            this.btDSAIOMoveCardToReadCardFromCardBox.Name = "btDSAIOMoveCardToReadCardFromCardBox";
            this.btDSAIOMoveCardToReadCardFromCardBox.Size = new System.Drawing.Size(181, 23);
            this.btDSAIOMoveCardToReadCardFromCardBox.TabIndex = 6;
            this.btDSAIOMoveCardToReadCardFromCardBox.Text = "从卡盒移卡到读卡位";
            this.btDSAIOMoveCardToReadCardFromCardBox.UseVisualStyleBackColor = true;
            this.btDSAIOMoveCardToReadCardFromCardBox.Click += new System.EventHandler(this.btDSAIOMoveCardToReadCardFromCardBox_Click);
            // 
            // btDSAIOMoveCardToColorFromReadCard
            // 
            this.btDSAIOMoveCardToColorFromReadCard.Location = new System.Drawing.Point(104, 194);
            this.btDSAIOMoveCardToColorFromReadCard.Name = "btDSAIOMoveCardToColorFromReadCard";
            this.btDSAIOMoveCardToColorFromReadCard.Size = new System.Drawing.Size(181, 23);
            this.btDSAIOMoveCardToColorFromReadCard.TabIndex = 7;
            this.btDSAIOMoveCardToColorFromReadCard.Text = "从读卡位移卡到彩色打印位";
            this.btDSAIOMoveCardToColorFromReadCard.UseVisualStyleBackColor = true;
            this.btDSAIOMoveCardToColorFromReadCard.Click += new System.EventHandler(this.btDSAIOMoveCardToColorFromReadCard_Click);
            // 
            // btDSAIOReadCardPosition
            // 
            this.btDSAIOReadCardPosition.Location = new System.Drawing.Point(309, 66);
            this.btDSAIOReadCardPosition.Name = "btDSAIOReadCardPosition";
            this.btDSAIOReadCardPosition.Size = new System.Drawing.Size(98, 23);
            this.btDSAIOReadCardPosition.TabIndex = 8;
            this.btDSAIOReadCardPosition.Text = "读取卡片位置";
            this.btDSAIOReadCardPosition.UseVisualStyleBackColor = true;
            this.btDSAIOReadCardPosition.Click += new System.EventHandler(this.btDSAIOReadCardPosition_Click);
            // 
            // btDSAIOReadStatus
            // 
            this.btDSAIOReadStatus.Location = new System.Drawing.Point(309, 108);
            this.btDSAIOReadStatus.Name = "btDSAIOReadStatus";
            this.btDSAIOReadStatus.Size = new System.Drawing.Size(98, 23);
            this.btDSAIOReadStatus.TabIndex = 9;
            this.btDSAIOReadStatus.Text = "读取打印机状态";
            this.btDSAIOReadStatus.UseVisualStyleBackColor = true;
            this.btDSAIOReadStatus.Click += new System.EventHandler(this.btDSAIOReadStatus_Click);
            // 
            // btDSAIOPrinterRelevancy
            // 
            this.btDSAIOPrinterRelevancy.Location = new System.Drawing.Point(309, 149);
            this.btDSAIOPrinterRelevancy.Name = "btDSAIOPrinterRelevancy";
            this.btDSAIOPrinterRelevancy.Size = new System.Drawing.Size(98, 23);
            this.btDSAIOPrinterRelevancy.TabIndex = 10;
            this.btDSAIOPrinterRelevancy.Text = "打印机关联";
            this.btDSAIOPrinterRelevancy.UseVisualStyleBackColor = true;
            this.btDSAIOPrinterRelevancy.Click += new System.EventHandler(this.btDSAIOPrinterRelevancy_Click);
            // 
            // btDSAIOCardSetRead
            // 
            this.btDSAIOCardSetRead.Location = new System.Drawing.Point(425, 66);
            this.btDSAIOCardSetRead.Name = "btDSAIOCardSetRead";
            this.btDSAIOCardSetRead.Size = new System.Drawing.Size(98, 23);
            this.btDSAIOCardSetRead.TabIndex = 11;
            this.btDSAIOCardSetRead.Text = "读卡片设置";
            this.btDSAIOCardSetRead.UseVisualStyleBackColor = true;
            this.btDSAIOCardSetRead.Click += new System.EventHandler(this.btDSAIOCardSetRead_Click);
            // 
            // btDSAIOCardSetWrite
            // 
            this.btDSAIOCardSetWrite.Location = new System.Drawing.Point(425, 194);
            this.btDSAIOCardSetWrite.Name = "btDSAIOCardSetWrite";
            this.btDSAIOCardSetWrite.Size = new System.Drawing.Size(98, 23);
            this.btDSAIOCardSetWrite.TabIndex = 12;
            this.btDSAIOCardSetWrite.Text = "写卡片设置";
            this.btDSAIOCardSetWrite.UseVisualStyleBackColor = true;
            this.btDSAIOCardSetWrite.Click += new System.EventHandler(this.btDSAIOCardSetWrite_Click);
            // 
            // rTBResult
            // 
            this.rTBResult.Location = new System.Drawing.Point(104, 226);
            this.rTBResult.Name = "rTBResult";
            this.rTBResult.Size = new System.Drawing.Size(419, 96);
            this.rTBResult.TabIndex = 13;
            this.rTBResult.Text = "";
            this.rTBResult.TextChanged += new System.EventHandler(this.rTBResult_TextChanged);
            // 
            // cbBExit
            // 
            this.cbBExit.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbBExit.FormattingEnabled = true;
            this.cbBExit.Items.AddRange(new object[] {
            "前方出卡",
            "后方出卡"});
            this.cbBExit.Location = new System.Drawing.Point(338, 196);
            this.cbBExit.Name = "cbBExit";
            this.cbBExit.Size = new System.Drawing.Size(81, 20);
            this.cbBExit.TabIndex = 14;
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(560, 334);
            this.Controls.Add(this.cbBExit);
            this.Controls.Add(this.rTBResult);
            this.Controls.Add(this.btDSAIOCardSetWrite);
            this.Controls.Add(this.btDSAIOCardSetRead);
            this.Controls.Add(this.btDSAIOPrinterRelevancy);
            this.Controls.Add(this.btDSAIOReadStatus);
            this.Controls.Add(this.btDSAIOReadCardPosition);
            this.Controls.Add(this.btDSAIOMoveCardToColorFromReadCard);
            this.Controls.Add(this.btDSAIOMoveCardToReadCardFromCardBox);
            this.Controls.Add(this.btDSAIOMoveCardToExitFromColorPrint);
            this.Controls.Add(this.btDSAIOMoveCardToColorPrintFromCardBox);
            this.Controls.Add(this.btOpen);
            this.Controls.Add(this.btClose);
            this.Controls.Add(this.cbBPerinterName);
            this.Controls.Add(this.btEnumPrinter);
            this.Name = "Form2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "一体机测试工具";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btEnumPrinter;
        private System.Windows.Forms.ComboBox cbBPerinterName;
        private System.Windows.Forms.Button btClose;
        private System.Windows.Forms.Button btOpen;
        private System.Windows.Forms.Button btDSAIOMoveCardToColorPrintFromCardBox;
        private System.Windows.Forms.Button btDSAIOMoveCardToExitFromColorPrint;
        private System.Windows.Forms.Button btDSAIOMoveCardToReadCardFromCardBox;
        private System.Windows.Forms.Button btDSAIOMoveCardToColorFromReadCard;
        private System.Windows.Forms.Button btDSAIOReadCardPosition;
        private System.Windows.Forms.Button btDSAIOReadStatus;
        private System.Windows.Forms.Button btDSAIOPrinterRelevancy;
        private System.Windows.Forms.Button btDSAIOCardSetRead;
        private System.Windows.Forms.Button btDSAIOCardSetWrite;
        private System.Windows.Forms.RichTextBox rTBResult;
        private System.Windows.Forms.ComboBox cbBExit;
    }
}