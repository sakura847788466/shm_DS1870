using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Text;

namespace D300RWDemo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //int length = 1000;
            //byte[] prtlist = new byte[length];
            //uint result = D300RWHelp.DASEnumPrinter(prtlist,ref length,1);
            //if (result == 0)
            //{
            //    string printList = Encoding.ASCII.GetString(prtlist,0,length);
            //    string[] split = printList.Split('\n');
            //    for (int i = 0; i < split.Length; i++)
            //    {
            //        cbBPrintName.Items.Add(split[i].Trim('\0'));
            //    }
            //    if (cbBPrintName.Items.Count > 0)
            //    {
            //        cbBPrintName.SelectedIndex = 0;
            //    }
            //}

            //FontFamily[] font = GetSystemFont();
            //for (int i = 0; i < font.Length; i++)
            //{
            //    cbBsetFont.Items.Add(font[i].Name);
            //}
        }

        private FontFamily[] GetSystemFont()
        {
            //获取系统已经安装的字体
            InstalledFontCollection MyFont = new InstalledFontCollection();
            FontFamily[] MyFontFamilies = MyFont.Families;
            return MyFontFamilies;
        }

        private void ShowReuslt(uint result,string content)
        {
            rTBShowResult.AppendText(content + (result == 0?"成功":"失败") + "\r\n");
            rTBShowResult.ScrollToCaret();
        }
        private void btOpen_Click(object sender, EventArgs e)
        {
            System.UInt16 ush = 0;
            int result = D300RWHelp.DAS_RFIDTag_SetReadPower(ush);
            //uint result = D300RWHelp.DASSetPrinterName(cbBPrintName.Text.Trim(),"D300RW");
            //ShowReuslt(result,((Button)sender).Text);
        }

        private void btInit_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASInit();
            ShowReuslt(result, ((Button)sender).Text);
        }

        private void btGetStatus_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetPrinterStatus_ErrorNo(status);
                rTBShowResult.AppendText("状态：" + D300RWHelp.ToPrinterStatusErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }



        private void btGetInCardMode_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetFeedCardMode(status);
                rTBShowResult.AppendText("进卡模式：" + D300RWHelp.ToFeedCardModeString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetCleaningStatus_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetCleaningStatus(status);
                rTBShowResult.AppendText("清洁状态：" + D300RWHelp.ToCleaningStatusString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetFanStatus_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetFanStatus(status);
                rTBShowResult.AppendText("风扇状态：" + D300RWHelp.ToFanStatusString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
            
        }

        private void btGetPrinterStatus_CardBoxStauts_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetPrinterStatus_CardBoxStatus(status);
                rTBShowResult.AppendText("卡盒状态：" + D300RWHelp.ToPrinterStatus_CardBoxStatusString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetPrinterStatus_FrontCoverStatus_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetPrinterStatus_FrontCoverStatus(status);
                rTBShowResult.AppendText("前盖状态：" + D300RWHelp.ToGetPrinterStatus_FrontCoverStatusString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetRecvBufferStatus_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetRecvBufferStatus(status);
                rTBShowResult.AppendText("缓冲区状态：" + D300RWHelp.ToRecvBufferStatusString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btClose_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASExit();
            ShowReuslt(result, ((Button)sender).Text);
        }

        private void btGetBusyStatus_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                result = D300RWHelp.DASGetBusyStatus(status);
                rTBShowResult.AppendText("忙状态：" + D300RWHelp.ToBusyStatusString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetFeedCardPattern_Click(object sender, EventArgs e)
        {
            ulong status = 0;
            uint result = D300RWHelp.DASFetchPrinterStatus(out status);
            if (result == 0)
            {
                int model = -1;
                result = D300RWHelp.DASGetFeedCardPattern(out model);
                if (result == 0)
                {
                    rTBShowResult.AppendText("装卡模式：" + D300RWHelp.ToFeedCardPatternString(model) + "\r\n");
                }
                else
                {
                    rTBShowResult.AppendText("获取装卡模式错误：" + D300RWHelp.ToErrorString(result) + "\r\n");
                }
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btSetFeedCardPattern_Click(object sender, EventArgs e)
        {
            if (cbBSetFeedCardPattern.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择装卡模式\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetFeedCardPattern(cbBSetFeedCardPattern.SelectedIndex);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置装卡模式错误：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
            else
            {
                ShowReuslt(result, ((Button)sender).Text);
            }
        }

        private void btGetPrinterSerialNumber_Click(object sender, EventArgs e)
        {
            int length = 100;
            byte[] data = new byte[100];
            uint result = D300RWHelp.DASGetPrinterSerialNumber(data,ref length);
            if (result == 0)
            {
                string sn = Encoding.ASCII.GetString(data, 0, length).Trim('\0'); ;
                rTBShowResult.AppendText("打印机序列号：" + sn + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
            else
            {
                rTBShowResult.AppendText("获取打印机序列号失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetPrinterHeadSerialNumber_Click(object sender, EventArgs e)
        {
            int length = 100;
            byte[] data = new byte[100];
            uint result = D300RWHelp.DASGetPrinterHeadSerialNumber(data, ref length);
            if (result == 0)
            {
                string sn = Encoding.ASCII.GetString(data, 0, length).Trim('\0'); ;
                rTBShowResult.AppendText("打印头序列号：" + sn + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
            else
            {
                rTBShowResult.AppendText("获取打印头序列号失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetPrinterUserData_Click(object sender, EventArgs e)
        {
            int length = 100;
            byte[] data = new byte[100];
            uint result = D300RWHelp.DASGetPrinterUserData(data, ref length);
            if (result == 0)
            {
                string sn = Encoding.ASCII.GetString(data, 0, length).Trim('\0'); ;
                rTBShowResult.AppendText("用户区数据：" + sn + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
            else
            {
                rTBShowResult.AppendText("获取用户区数据失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetPrinterCardPos_Click(object sender, EventArgs e)
        {
            int length = 8;
            byte[] data = new byte[length];
            byte c = 0;
            uint result = D300RWHelp.DASGetPrinterCardPos(data, ref length);
            if (result == 0 && length > 0)
            {
                string cardPos = "";
                if ((data[0] & 0X01) == 1) cardPos += "sens1有卡";
                else cardPos += "sens1没卡";
                if ((data[0] & 0X02) == 2) cardPos += "，sens2闭合";
                else cardPos += "，sens2开盖";
                if ((data[0] & 0X04) == 4) cardPos += "，sens3有卡";
                else cardPos += "，sens3没卡";
                if ((data[0] & 0X08) == 8) cardPos += "，打印头未归位";
                else cardPos += "，打印头已归位";
                if ((data[0] & 0X10) == 16) cardPos += "，卡盒有卡。";
                else cardPos += "，卡盒没卡。";
                string sn = Encoding.ASCII.GetString(data, 0, length).Trim('\0'); ;
                rTBShowResult.AppendText("卡片位置：" + cardPos + "\r\n");
            }
            else
            {
                rTBShowResult.AppendText("获取卡片位置失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
            rTBShowResult.ScrollToCaret();
        }

        private void btGetPrtHeadTemperature_Click(object sender, EventArgs e)
        {
            int temperature = -1;
            uint result = D300RWHelp.DASGetPrtHeadTemperature(out temperature);
            if (result == 0) 
                rTBShowResult.AppendText("打印头温度：" + temperature.ToString() + "\r\n");
            else
                rTBShowResult.AppendText("获取打印头温度失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            rTBShowResult.ScrollToCaret();
        }

        private void btGetLoadCardTotal_Click(object sender, EventArgs e)
        {
            int loadCardTotal = -1;
            uint result = D300RWHelp.DASGetLoadCardTotal(out loadCardTotal);
            if (result == 0)
                rTBShowResult.AppendText("装卡次数：" + loadCardTotal.ToString() + "\r\n");
            else
                rTBShowResult.AppendText("获取装卡次数失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            rTBShowResult.ScrollToCaret();
        }

        private void btGetPrtCardTotal_Click(object sender, EventArgs e)
        {
            int PrtCardTotal = -1;
            uint result = D300RWHelp.DASGetPrtCardTotal(out PrtCardTotal);
            if (result == 0)
                rTBShowResult.AppendText("卡片打印总数：" + PrtCardTotal.ToString() + "\r\n");
            else
                rTBShowResult.AppendText("获取卡片打印总数失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            rTBShowResult.ScrollToCaret();
        }

        private void btCanPrintTotalPreClean_Click(object sender, EventArgs e)
        {
            int canPrintTotalPreClean = -1;
            uint result = D300RWHelp.DASCanPrintTotalPreClean(out canPrintTotalPreClean);
            if (result == 0)
                rTBShowResult.AppendText("下次清洁前可打印次数：" + canPrintTotalPreClean.ToString() + "\r\n");
            else
                rTBShowResult.AppendText("获取下次清洁前可打印次数失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            rTBShowResult.ScrollToCaret();
        }

        private void btCleanTotal_Click(object sender, EventArgs e)
        {
            int cleanTotal = -1;
            uint result = D300RWHelp.DASCleanTotal(out cleanTotal);
            if (result == 0)
                rTBShowResult.AppendText("清洁总数：" + cleanTotal.ToString() + "\r\n");
            else
                rTBShowResult.AppendText("获取清洁总数失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            rTBShowResult.ScrollToCaret();
        }

        private void btSetManualCard_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASSetManualCard();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("装卡指令失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetRunningInfo_Click(object sender, EventArgs e)
        {
            if (cbBGetRunningInfo.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择运行信息\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            int length = 100;
            byte[] data = new byte[length];
            uint result = D300RWHelp.DASGetRunningInfo(cbBGetRunningInfo.SelectedIndex+1,data,ref length);
            if (result == 0)
            {
                
                if (cbBGetRunningInfo.SelectedIndex + 1 == 4 || cbBGetRunningInfo.SelectedIndex + 1 > 5)
                {
                    long no = BitConverter.ToInt64(data, 0);
                    rTBShowResult.AppendText(cbBGetRunningInfo.Text + "：" + no.ToString() + "\r\n");

                }
                else
                {
                    string value = Encoding.ASCII.GetString(data, 0, length).Trim('\0');
                    rTBShowResult.AppendText(cbBGetRunningInfo.Text + "：" + value + "\r\n");
                }
                
            }
            else
            {
                rTBShowResult.AppendText(cbBGetRunningInfo.Text+"失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
            rTBShowResult.ScrollToCaret();
        }

        private void btRebootPrinter_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASRebootPrinter();
            ShowReuslt(result, ((Button)sender).Text);
        }

        private void btSetUserData_Click(object sender, EventArgs e)
        {
            byte[] data = Encoding.ASCII.GetBytes(tBSetUserData.Text.Trim()) ;
            uint result = D300RWHelp.DASSetUserData(data,data.Length);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置用户数据区失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btSetCardBoxEjectCard_Click(object sender, EventArgs e)
        {
            if (cbBFeederFlag.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请设置卡盒配置方式\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            if (cbBOutCardDir.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请设置进卡方式\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetCardBoxEjectCard(cbBFeederFlag.SelectedIndex,cbBOutCardDir.SelectedIndex);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置卡盒配置和进卡方式配置失败："+D300RWHelp.ToErrorString(result)+"\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btRejectCard_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASRejectCard();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("排除卡片失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btEraseCard_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASEraseCard();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("擦除卡片失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btCleanPrinter_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASCleanPrinter();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("清洁打印机失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btPrintTechnicalTestCard_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASPrintTechnicalTestCard();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("打印技术测试卡失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btPrintTestCard_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASPrintTestCard();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("打印测试卡失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                rTBShowResult.ScrollToCaret();
            }
        }

        private void btGetSDKVersion_Click(object sender, EventArgs e)
        {
            int length = 100;
            byte[] data = new  byte[length];
            uint result = D300RWHelp.DASGetSDKVersion(data,ref length);
            if (result != 0)
            {
                rTBShowResult.AppendText("获取SDK版本失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
            else
            {
                string value = Encoding.ASCII.GetString(data,0,length).Trim('\0');
                rTBShowResult.AppendText("获取SDK版本：" + value + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetXoffset_Click(object sender, EventArgs e)
        {
            int offset = (int)nUDsetXoffset.Value;
            uint result = D300RWHelp.DASsetXoffset(offset);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置打印头方向偏移失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                
            }
            else
            {
                rTBShowResult.AppendText("需要重启打印机才能生效\r\n");
            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetYoffset_Click(object sender, EventArgs e)
        {
            int offset = (int)nUDsetYoffset.Value;
            uint result = D300RWHelp.DASsetYoffset(offset);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置进卡方向偏移失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            else
            {
                rTBShowResult.AppendText("需要重启打印机才能生效\r\n");
            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetPrintChroma_Click(object sender, EventArgs e)
        {
            int offset = (int)nUDsetYoffset.Value;
            uint result = D300RWHelp.DASsetPrintChroma(offset);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置打印浓度失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            else
            {
                rTBShowResult.AppendText("需要重启打印机才能生效\r\n");
            }
            rTBShowResult.ScrollToCaret();
        }

        private void btSetBlackPrintMethod_Click(object sender, EventArgs e)
        {
            if (cbBSetBlackPrintMethod.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择黑色打印方式\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetBlackPrintMethod(cbBSetBlackPrintMethod.SelectedIndex);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置黑色打印方式失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btSetGraphicDataByFile_Click(object sender, EventArgs e)
        {
            string file  ="";
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "bmp files (*.bmp)|*.bmp";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                file = ofd.FileName;
                uint result = D300RWHelp.DASSetGraphicDataByFile(0, file);
                ShowReuslt(result, ((Button)sender).Text);
                if (result != 0)
                {
                    rTBShowResult.AppendText("设置打印图片失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

                }
                rTBShowResult.ScrollToCaret();
            }
            
        }

        private void btSetEraseDataByFile_Click(object sender, EventArgs e)
        {
            if (cbBEraseflag.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择擦除方式\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "bmp files (*.bmp)|*.bmp";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string file = ofd.FileName;
                uint result = D300RWHelp.DASSetEraseDataByFile(file, cbBEraseflag.SelectedIndex);
                ShowReuslt(result, ((Button)sender).Text);
                if (result != 0)
                {
                    rTBShowResult.AppendText("设置擦除图片失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

                }
                rTBShowResult.ScrollToCaret();
            }
            
        }

        private void btSetNthreshold_Click(object sender, EventArgs e)
        {
            int value = (int)nUDSetNthreshold.Value;
            uint result = D300RWHelp.DASSetNthreshold(value);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置打印阈值失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btSetPrintDirection_Click(object sender, EventArgs e)
        {
            if (cbBSetPrintDirection.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择打印方向\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetPrintDirection(cbBSetPrintDirection.SelectedIndex);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置打印方向失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
            else
            {
                rTBShowResult.AppendText("设置失败，该函数在指定图片打印时有效，套打时无效。\r\n");
            }

            rTBShowResult.ScrollToCaret();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (cbBCardType.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择卡片类型\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            if (cbBStandardCardExitPositon.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择标准出卡位置\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            if (cbBSetCardPosition.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择进卡位置\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            int cardType = cbBCardType.SelectedIndex;
            if (cardType == 3) cardType = 90;
            if (cardType == 4) cardType = 91;
            if (cardType == 5) cardType = 92;
            uint result = D300RWHelp.DAS_CardSet(cardType,0,0,cbBStandardCardExitPositon.SelectedIndex,0,cbBSetCardPosition.SelectedIndex,0);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("打印卡片设置失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();

        }

        private void btSetPrintSpeed_Click(object sender, EventArgs e)
        {
            if (cbBSetPrintSpeed.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择打印速度\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetPrintSpeed(Convert.ToInt32(cbBSetPrintSpeed.Text));
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置打印速度失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btSetCardContrast_Click(object sender, EventArgs e)
        {
            if (cbBSetCardContrast.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择卡片对比度\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetCardContrast(Convert.ToInt32(cbBSetCardContrast.Text));
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置卡片对比度失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btSetPrintTemperature_Click(object sender, EventArgs e)
        {
            if (cbBSetPrintTemperature.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择打印温度\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetPrintTemperature(Convert.ToInt32(cbBSetPrintTemperature.Text));
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置打印温度失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btSetEraseTemperture_Click(object sender, EventArgs e)
        {
            if (cbBSetEraseTemperture.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择擦除温度\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            uint result = D300RWHelp.DASSetEraseTemperature(Convert.ToInt32(cbBSetEraseTemperture.Text));
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置擦除温度失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btPrintCard_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASPrintCard();
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("打印卡片失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetCardSize_Click(object sender, EventArgs e)
        {
            double width = 0;
            double height = 0;
            if (double.TryParse(tBCardWidth.Text,out width) == false)
            {
                rTBShowResult.AppendText("卡片宽度数值不对\r\n");
                rTBShowResult.ScrollToCaret();
                tBCardWidth.Focus();
                return;
            }
            if (double.TryParse(tBCardHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("卡片高度数值不对\r\n");
                rTBShowResult.ScrollToCaret();
                tBCardHeight.Focus();
                return;
            }
            uint result = D300RWHelp.DASsetCardSize(width,height);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置卡片尺寸失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btaddProtectedRect_Click(object sender, EventArgs e)
        {
            double x = 0;
            double y = 0;
            double width = 0;
            double height = 0;
            if (double.TryParse(tBProtectedRectWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("宽度数值不对\r\n");
                rTBShowResult.ScrollToCaret();
                tBProtectedRectWidth.Focus();
                return;
            }
            if (double.TryParse(tBProtectedRectHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("高度数值不对\r\n");
                rTBShowResult.ScrollToCaret();
                tBProtectedRectHeight.Focus();
                return;
            }
            if (double.TryParse(tBProtectedRectX.Text, out width) == false)
            {
                rTBShowResult.AppendText("X坐标数值不对\r\n");
                rTBShowResult.ScrollToCaret();
                tBProtectedRectX.Focus();
                return;
            }
            if (double.TryParse(tBProtectedRectY.Text, out height) == false)
            {
                rTBShowResult.AppendText("Y坐标数值不对\r\n");
                rTBShowResult.ScrollToCaret();
                tBProtectedRectY.Focus();
                return;
            }

            uint result = D300RWHelp.DASaddProtectedRect(x,y,width,height);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置卡片保护区失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetFont_Click(object sender, EventArgs e)
        {
            if (cbBsetFont.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择字体\r\n");
                rTBShowResult.ScrollToCaret();
                return;
            }
            double fontSize = 0;
            if (double.TryParse(tBFontSize.Text,out fontSize) == false)
            {
                rTBShowResult.AppendText("请输入字体大小，类型为double\r\n");
                rTBShowResult.ScrollToCaret();
                tBFontSize.Focus();
                return;
            }

            uint result = D300RWHelp.DASsetFont(cbBsetFont.Text,fontSize);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置字体失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetTextColor_Click(object sender, EventArgs e)
        {
            byte red = 0, green = 0, blue = 0;
            if (byte.TryParse(tBRedColor.Text, out red) == false)
            {
                rTBShowResult.AppendText("请输入红色字体亮度，范围为0-255\r\n");
                rTBShowResult.ScrollToCaret();
                tBRedColor.Focus();
                return;
            }

            if (byte.TryParse(tBGreenColor.Text, out green) == false)
            {
                rTBShowResult.AppendText("请输入绿色字体亮度，范围为0-255\r\n");
                rTBShowResult.ScrollToCaret();
                tBGreenColor.Focus();
                return;
            }

            if (byte.TryParse(tBBlueColor.Text, out green) == false)
            {
                rTBShowResult.AppendText("请输入蓝色字体亮度，范围为0-255\r\n");
                rTBShowResult.ScrollToCaret();
                tBBlueColor.Focus();
                return;
            }
            uint result = D300RWHelp.DASsetTextColor(red,green,blue);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置字体颜色失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void setBarCodeColor_Click(object sender, EventArgs e)
        {
            byte red = 0, green = 0, blue = 0;
            if (byte.TryParse(tBSetBarcodeRed.Text, out red) == false)
            {
                rTBShowResult.AppendText("请输入红色字体亮度，范围为0-255\r\n");
                rTBShowResult.ScrollToCaret();
                tBSetBarcodeRed.Focus();
                return;
            }

            if (byte.TryParse(tBSetBarcodeGreen.Text, out green) == false)
            {
                rTBShowResult.AppendText("请输入绿色字体亮度，范围为0-255\r\n");
                rTBShowResult.ScrollToCaret();
                tBSetBarcodeGreen.Focus();
                return;
            }

            if (byte.TryParse(tBSetBarcodeBlue.Text, out green) == false)
            {
                rTBShowResult.AppendText("请输入蓝色字体亮度，范围为0-255\r\n");
                rTBShowResult.ScrollToCaret();
                tBSetBarcodeBlue.Focus();
                return;
            }
            uint result = D300RWHelp.DASsetBarCodeColor(red, green, blue);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置一维码、二维码画笔颜色失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetTextDecorate_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASsetTextDecorate(cBBold.Checked,cBItalic.Checked,cBUnderLine.Checked);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置字体修饰失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void rTBShowResult_TextChanged(object sender, EventArgs e)
        {
            rTBShowResult.ScrollToCaret();
        }

        private void btsetTextDirection_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASsetTextDirection(cBLandScape.Checked, cBReverseSequence.Checked, cBAutoFeed.Checked);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置字体方向失败：" + D300RWHelp.ToErrorString(result) + "\r\n");

            }
            rTBShowResult.ScrollToCaret();
        }

        private void btsetSpacing_Click(object sender, EventArgs e)
        {
            double lineSpace = 0, charSapce = 0;
            if (double.TryParse(tBLintSpace.Text,out lineSpace) == false)
            {
                rTBShowResult.AppendText("请输入正确的行间距，类型为double\r\n");
                tBLintSpace.Focus();
                return;
            }
            if (double.TryParse(tBCharSpace.Text, out charSapce) == false)
            {
                rTBShowResult.AppendText("请输入正确的字间距，类型为double\r\n");
                tBCharSpace.Focus();
                return;
            }
            uint result = D300RWHelp.DASsetSpacing(lineSpace,charSapce);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置行间距和字间距失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btdrawText_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0,height = 0;
            if (double.TryParse(tBdrawTextX.Text,out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBdrawTextX.Focus();
                return;
            }
            if (double.TryParse(tBdrawTextY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBdrawTextY.Focus();
                return;
            }
            if (double.TryParse(tBdrawTextWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBdrawTextWidth.Focus();
                return;
            }
            if (double.TryParse(tBdrawTextHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBdrawTextHeight.Focus();
                return;
            }
            if (tBgbkText.Text.Trim() == "")
            {
                rTBShowResult.AppendText("请输入文本块\r\n");
                tBgbkText.Focus();
                return;
            }
            uint result = D300RWHelp.DASdrawText(x,y,width,height,tBgbkText.Text);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("打印文本块失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }



        private void btdrawTextForRotation_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            if (double.TryParse(tBdrawTextX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBdrawTextX.Focus();
                return;
            }
            if (double.TryParse(tBdrawTextY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBdrawTextY.Focus();
                return;
            }
            if (double.TryParse(tBdrawTextWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBdrawTextWidth.Focus();
                return;
            }
            if (double.TryParse(tBdrawTextHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBdrawTextHeight.Focus();
                return;
            }
            if (tBgbkText.Text.Trim() == "")
            {
                rTBShowResult.AppendText("请输入文本块\r\n");
                tBgbkText.Focus();
                return;
            }
            if (cbBRotation.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请旋转旋转的角度\r\n");
                return;
            }

            uint result = D300RWHelp.DASdrawTextForRotation(x, y, width, height, tBgbkText.Text,cbBRotation.SelectedIndex);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("打印文本块并旋转失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btDrawQR_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            int version = 0;
            if (double.TryParse(tBDrawQRX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBDrawQRX.Focus();
                return;
            }
            if (double.TryParse(tBDrawQRY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBDrawQRY.Focus();
                return;
            }
            if (double.TryParse(tBDrawQRWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBDrawQRWidth.Focus();
                return;
            }
            if (double.TryParse(tBDrawQRHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBDrawQRHeight.Focus();
                return;
            }
            if (tBQR.Text.Trim() == "")
            {
                rTBShowResult.AppendText("请输入文本块\r\n");
                tBQR.Focus();
                return;
            }
            if (int.TryParse(tBVersion.Text,out version) == false)
            {
                rTBShowResult.AppendText("请输入QR版本号，类型为int\r\n");
                tBVersion.Focus();
                return;
            }

            if (cbBErrLev.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择容错率\r\n");
                return;
            }

            uint result = D300RWHelp.DASdrawQRbyVersion(x, y, width, height, tBgbkText.Text,version, cbBErrLev.SelectedIndex,cBQRAutoFill.Checked);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("绘制二维码失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btDrawQRForRotation_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            int version = 0;
            if (double.TryParse(tBDrawQRX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBDrawQRX.Focus();
                return;
            }
            if (double.TryParse(tBDrawQRY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBDrawQRY.Focus();
                return;
            }
            if (double.TryParse(tBDrawQRWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBDrawQRWidth.Focus();
                return;
            }
            if (double.TryParse(tBDrawQRHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBDrawQRHeight.Focus();
                return;
            }
            if (tBQR.Text.Trim() == "")
            {
                rTBShowResult.AppendText("请输入文本块\r\n");
                tBQR.Focus();
                return;
            }
            if (int.TryParse(tBVersion.Text, out version) == false)
            {
                rTBShowResult.AppendText("请输入QR版本号，类型为int\r\n");
                tBVersion.Focus();
                return;
            }

            if (cbBErrLev.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择容错率\r\n");
                return;
            }
            if (cbBQRotation.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择旋转角度\r\n");
                return;
            }

            uint result = D300RWHelp.DASdrawQRForRotation(x, y, width, height, tBgbkText.Text, version, cbBErrLev.SelectedIndex, cBQRAutoFill.Checked, cbBQRotation.SelectedIndex);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("绘制二维码并旋转失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btaddNeedEraseRect_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            if (double.TryParse(tBaddNeedEraseRectX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBaddNeedEraseRectX.Focus();
                return;
            }
            if (double.TryParse(tBaddNeedEraseRectY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBaddNeedEraseRectY.Focus();
                return;
            }
            if (double.TryParse(tBaddNeedEraseRectWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBaddNeedEraseRectWidth.Focus();
                return;
            }
            if (double.TryParse(tBaddNeedEraseRectHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBaddNeedEraseRectHeight.Focus();
                return;
            }

            uint result = D300RWHelp.DASaddNeedEraseRect(x, y, width, height);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("设置仅擦不打印区域失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btdrawImage_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            if (double.TryParse(tBdrawImageX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBdrawImageX.Focus();
                return;
            }
            if (double.TryParse(tBdrawImageY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBdrawImageY.Focus();
                return;
            }
            if (double.TryParse(tBdrawImageWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBdrawImageWidth.Focus();
                return;
            }
            if (double.TryParse(tBdrawImageHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBdrawImageHeight.Focus();
                return;
            }
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                uint result = D300RWHelp.DASdrawImage(x, y, width, height, ofd.FileName, cBIsPhoto.Checked);
                ShowReuslt(result, ((Button)sender).Text);
                if (result != 0)
                {
                    rTBShowResult.AppendText("绘制图片失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                }
            }
            
        }

        private void btdrawImageForRotation_Click(object sender, EventArgs e)
        {


            double x = 0, y = 0, width = 0, height = 0;
            if (double.TryParse(tBdrawImageX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBdrawImageX.Focus();
                return;
            }
            if (double.TryParse(tBdrawImageY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBdrawImageY.Focus();
                return;
            }
            if (double.TryParse(tBdrawImageWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBdrawImageWidth.Focus();
                return;
            }
            if (double.TryParse(tBdrawImageHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBdrawImageHeight.Focus();
                return;
            }

            if (cbBDrawImageRotation.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择旋转的度数，类型为double\r\n");
                return;
            }

            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "image files (*.jpg)|*.pjg|(*.png)|*.png|(*.jpeg)|*.jpeg|(*.bmp)|*.bmp|All files (*.*)|*.*";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                uint result = D300RWHelp.DASdrawImageForRotation(x, y, width, height, ofd.FileName, cBIsPhoto.Checked, cbBDrawImageRotation.SelectedIndex);
                ShowReuslt(result, ((Button)sender).Text);
                if (result != 0)
                {
                    rTBShowResult.AppendText("绘制图片并旋转失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
                }
            }
        }

        private void btdrawBarCode_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            if (double.TryParse(tBBarcodeX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBBarcodeX.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBBarcodeY.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBBarcodeWidth.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBBarcodeHeight.Focus();
                return;
            }

            if (cbBbarcodeType.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择条码类型\r\n");
                return;
            }

            if (tBBarcodeText.Text.Trim() == "")
            {
                rTBShowResult.AppendText("请输入条码内容\r\n");
                return;
            }
            int multiplier = 0;
            if (int.TryParse(tBBarcodeMultiplier.Text, out multiplier)==false)
            {
                rTBShowResult.AppendText("请输入放大倍数，类型为int\r\n");
                return;
            }

            uint result = D300RWHelp.DASdrawBarCode(x, y, width, height, cbBbarcodeType.SelectedIndex, tBBarcodeText.Text.Trim(),cBShowBarcodeText.Checked,cBIsUnderText.Checked,multiplier);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("绘制条码失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btdrawBarCodeForRotation_Click(object sender, EventArgs e)
        {
            double x = 0, y = 0, width = 0, height = 0;
            if (double.TryParse(tBBarcodeX.Text, out x) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角x坐标，类型为double\r\n");
                tBBarcodeX.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeY.Text, out y) == false)
            {
                rTBShowResult.AppendText("请输入正确的左上角y坐标，类型为double\r\n");
                tBBarcodeY.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeWidth.Text, out width) == false)
            {
                rTBShowResult.AppendText("请输入正确的宽度，类型为double\r\n");
                tBBarcodeWidth.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeHeight.Text, out height) == false)
            {
                rTBShowResult.AppendText("请输入正确的高度，类型为double\r\n");
                tBBarcodeHeight.Focus();
                return;
            }

            if (cbBbarcodeType.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择条码类型\r\n");
                return;
            }

            if (tBBarcodeText.Text.Trim() == "")
            {
                rTBShowResult.AppendText("请输入条码内容\r\n");
                return;
            }
            int multiplier = 0;
            if (int.TryParse(tBBarcodeMultiplier.Text, out multiplier))
            {
                rTBShowResult.AppendText("请输入放大倍数，类型为int\r\n");
                return;
            }
            if (cbBBarcodeRotation.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请旋转条码旋转角度\r\n");
                return;
            }

            uint result = D300RWHelp.DASdrawBarCodeForRotation(x, y, width, height, cbBbarcodeType.SelectedIndex, tBBarcodeText.Text.Trim(), cBShowBarcodeText.Checked, cBIsUnderText.Checked, multiplier,cbBBarcodeRotation.SelectedIndex);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText("绘制条码并旋转失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btBuildGraphicsData_Click(object sender, EventArgs e)
        {
            uint result = D300RWHelp.DASBuildGraphicsData(true, cbAutoGenerateMask.Checked);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText(((Button)sender).Text + "失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }

        private void btBuildGraphicsDataForRotation_Click(object sender, EventArgs e)
        {
            if (cbBDataRotation.SelectedIndex == -1)
            {
                rTBShowResult.AppendText("请选择旋转角度\r\n");
                return;
            }
            uint result = D300RWHelp.DASBuildGraphicsDataForRotation(true, cbAutoGenerateMask.Checked,cbBDataRotation.SelectedIndex);
            ShowReuslt(result, ((Button)sender).Text);
            if (result != 0)
            {
                rTBShowResult.AppendText(((Button)sender).Text + "失败：" + D300RWHelp.ToErrorString(result) + "\r\n");
            }
        }
    }
}
