using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace DSCP600Demo
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void btEnumPrinter_Click(object sender, EventArgs e)
        {
            long reault = DSCP600Help.DS600SetIOTimeout(100, 100);
            string printers = DSCP600Help.DS600EnumPrinter(1);
            if (printers == null)
            {
                rTBResult.AppendText("未连接直印打印机\r\n");
                return;
            }
            else
            {
                string[] printersList = printers.Split('\n');
                for (int i = 0; i < printersList.Length; i++)
                {
                    cbBPerinterName.Items.Add(printersList[i]);
                }
                if (printersList.Length > 0)
                {
                    cbBPerinterName.Text = printersList[0];
                }
            }

            reault = DSCP600Help.DS600SetIOTimeout(3000, 3000);

        }

        private void rTBResult_TextChanged(object sender, EventArgs e)
        {
            rTBResult.ScrollToCaret();
        }

        private void btOpen_Click(object sender, EventArgs e)
        {
            uint result = (uint)DSCP600Help.D300COpenPrinter(cbBPerinterName.Text);
            ShowResult(((Button)sender).Text, result);
        }

        private void btClose_Click(object sender, EventArgs e)
        {
            DSCP600Help.DS600ClosePrinter();
            rTBResult.AppendText("【" + DateTime.Now.ToString() + "】关闭打印机\r\n");
        }

        public void ShowResult(string content, uint result)
        {
            rTBResult.AppendText("【" + DateTime.Now.ToString() + "】" + content + (result == 0 ? "成功" : "失败") + "\r\n");
           
        }

        private void btDSAIOMoveCardToColorPrintFromCardBox_Click(object sender, EventArgs e)
        {
            int result = DSCP600Help.DSAIOMoveToColor();
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btDSAIOMoveCardToExitFromColorPrint_Click(object sender, EventArgs e)
        {
            //int result = DSCP600Help.DSAIOMoveCardToExitFromColorPrint();
            //ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btDSAIOMoveCardToReadCardFromCardBox_Click(object sender, EventArgs e)
        {
            int result = DSCP600Help.DSAIOMoveToRead(0);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btDSAIOMoveCardToColorFromReadCard_Click(object sender, EventArgs e)
        {
            int result = DSCP600Help.DSAIOMoveToColor();
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btDSAIOReadCardPosition_Click(object sender, EventArgs e)
        {
            int result = DSCP600Help.DSAIOGetPosition();
            string temp = "";
            if (result == 0) temp = "打印机内部无卡";
            else if (result == 1) temp = "D300C 打印位";
            else if (result == 2) temp = "D300RW 打印位";
            else temp = "读取卡片位置失败";
            rTBResult.AppendText("【" + DateTime.Now.ToString() + "】" + temp+ "\r\n");
        }

        private void btDSAIOReadStatus_Click(object sender, EventArgs e)
        {
            int lenght =  1000;
            byte[] data = new byte[lenght];
            int result = DSCP600Help.DSAIOGetStatus(data, lenght);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                string temp = "";
                if (data[6] == 0XFF) temp = "卡片位置状态：未知状态";
                if (data[6] == 0X00) temp = "卡片位置状态：打印机内部无卡";
                if (data[6] == 0X01) temp = "卡片位置状态：彩色打印位";
                if (data[6] == 0X02) temp = "卡片位置状态：读卡器位";
                rTBResult.AppendText("【" + DateTime.Now.ToString() + "】" + temp + "\r\n");
            }
        }

        private void btDSAIOPrinterRelevancy_Click(object sender, EventArgs e)
        {
            int lenght = 1000;
            byte[] data = new byte[lenght];
            int result = DSCP600Help.DSAIOGetCacheTemp(data, lenght);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                string temp = "";
                double t1 = ((data[11] << 8 & 0xFF00) + (data[10] & 0xFF)) / 100;//当前环境温度：t1/100
                temp += "\r\n当前环境温度：" + t1.ToString();
                double t2 = ((data[15] << 8 & 0xFF00) + (data[14] & 0xFF)) / 100;//当前印头温度：t2/100
                temp += "\r\n当前打印头温度：" + t2.ToString();
                if (data[39] == 0x00) temp += "\r\n缓存满";
                else if (data[39] == 0x01) temp += "\r\n缓存可以存储 1 面打印数据";
                else if (data[39] == 0x02) temp += "\r\n缓存可以存储 2 面打印数据";
                rTBResult.AppendText( temp + "\r\n");
            }
        }

        private void btDSAIOCardSetRead_Click(object sender, EventArgs e)
        {
            int lenght = 1000;
            byte[] rcv = new byte[lenght];
            int result = DSCP600Help.DSAIOGetEjectPos(rcv, lenght);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                string temp = "";
                if (rcv[14] == 0x00) temp += "\r\n前方出卡";
                else if (rcv[14] == 0x01) temp += "\r\n后方出卡";
                rTBResult.AppendText(temp + "\r\n");
            }


            //int lenght = 1000;
            //byte[] rcv = new byte[lenght];
            //int result = DSCP600Help.DSAIOCardSet(false, rcv, lenght, 0, 0, 0, 0);
            //ShowResult(((Button)sender).Text, (uint)result);
            //if (result == 0)
            //{
            //    string temp = "";
            //    if (rcv[10] == 0x00) temp += "\r\n卡片类型:PVC";
            //    else if (rcv[10] == 0x01) temp += "\r\n卡片类型:PET";
            //    else if (rcv[10] == 0x02) temp += "\r\n卡片类型:PET-G";
            //    else if (rcv[10] == 0x03) temp += "\r\n卡片类型:卡片 1";
            //    else if (rcv[10] == 0x04) temp += "\r\n卡片类型:卡片 2";
            //    else if (rcv[10] == 0x05) temp += "\r\n卡片类型:卡片 3";
                
            //    if(rcv[14] == 0x00) temp += "\r\n标准卡前方出卡";
            //    else if (rcv[14] == 0x01) temp += "\r\n标准卡后方出卡";

            //    if (rcv[18] == 0x00) temp += "\r\n异常卡前方出卡";
            //    else if (rcv[18] == 0x01) temp += "\r\n异常卡后方出卡";

            //    if (rcv[22] == 0x00) temp += "\r\n送卡方式普通送卡";
            //    rTBResult.AppendText(temp + "\r\n");
            //}
        }

        private void btDSAIOCardSetWrite_Click(object sender, EventArgs e)
        {
            int lenght = 1000;
            byte[] rcv = new byte[lenght];
            int result = DSCP600Help.DSAIOSetEjectPos((ushort)cbBExit.SelectedIndex);
            ShowResult(((Button)sender).Text, (uint)result);
            


            //int lenght = 1000;
            //byte[] rcv = new byte[lenght];
            //int result = DSCP600Help.DSAIOCardSet(true, rcv, lenght, 0, (ushort)cbBExit.SelectedIndex, (ushort)cbBExit.SelectedIndex, 0);
            //ShowResult(((Button)sender).Text, (uint)result);
            //if (result == 0)
            //{
            //    string temp = "";
            //    if (rcv[10] == 0x00) temp += "\r\n卡片类型:PVC";
            //    else if (rcv[10] == 0x01) temp += "\r\n卡片类型:PET";
            //    else if (rcv[10] == 0x02) temp += "\r\n卡片类型:PET-G";
            //    else if (rcv[10] == 0x03) temp += "\r\n卡片类型:卡片 1";
            //    else if (rcv[10] == 0x04) temp += "\r\n卡片类型:卡片 2";
            //    else if (rcv[10] == 0x05) temp += "\r\n卡片类型:卡片 3";

            //    if (rcv[14] == 0x00) temp += "\r\n标准卡前方出卡";
            //    else if (rcv[14] == 0x01) temp += "\r\n标准卡后方出卡";

            //    if (rcv[18] == 0x00) temp += "\r\n异常卡前方出卡";
            //    else if (rcv[18] == 0x01) temp += "\r\n异常卡后方出卡";

            //    if (rcv[22] == 0x00) temp += "\r\n送卡方式普通送卡";
            //    rTBResult.AppendText(temp + "\r\n");
            //}
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            cbBExit.SelectedIndex = 0;
        }
    }
}
