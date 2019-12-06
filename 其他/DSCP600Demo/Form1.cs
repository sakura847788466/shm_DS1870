using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Text;
using System.IO;

namespace DSCP600Demo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void btEnumPrinter_Click(object sender, EventArgs e)
        {
            cbBPrinterName.Items.Clear();
            uint reault = DC3300Help.D300CSetIOTimeout(100, 100);
            string printers = DC3300Help.DSEnumPrinter();
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
                    cbBPrinterName.Items.Add(printersList[i]);
                }
                if (printersList.Length > 0)
                {
                    cbBPrinterName.Text = printersList[0];
                }
            }
            
            reault = DC3300Help.D300CSetIOTimeout(3000, 3000);

        }

        public void ShowResult(string content,uint result)
        {
            rTBResult.AppendText("【"+DateTime.Now.ToString() + "】" + content + (result == 0 ? "成功" : "失败") + "\r\n");
            if (result != 0)
            {
                rTBResult.AppendText("返回结果：" + DC3300Help.GetErrorMess(result) + "\r\n");
            }
        }

        private void btOpenPrinter_Click(object sender, EventArgs e)
        {
            String enumResult = cbBPrinterName.Text;
            enumResult = enumResult.Replace("\r", "");
            enumResult = enumResult.Replace("\n","");
            uint result = DC3300Help.D300COpenPrinter(enumResult);
            ShowResult(((Button)sender).Text,result);
        }

        private void rTBResult_TextChanged(object sender, EventArgs e)
        {
            rTBResult.ScrollToCaret();
        }

        private void btClose_Click(object sender, EventArgs e)
        {
            DC3300Help.DSClosePrinter();
        }

        private void btStopPrint_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CAbortPrinting();
            ShowResult(((Button)sender).Text, result);

        }

        private void btD300CPrintImage_Click(object sender, EventArgs e)
        {
            if (tBFrontSideImgPath.Text.Trim() == "")
            {
                rTBResult.AppendText("请选择正面图片文件\r\n");
                return;
            }
            if (tBbackSideSideImgPath.Text.Trim() == "")
            {
                rTBResult.AppendText("请选择反面图片文件\r\n");
                return;
            }
            if (cbBF_rotation.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择正面旋转角度\r\n");
                return;
            }
            if (cbBB_rotation.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择反面旋转角度\r\n");
                return;
            }
            if (cbBF_ScalingMode.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择正面拉伸模式\r\n");
                return;
            }
            if (cbBB_ScalingMode.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择反面拉伸模式\r\n");
                return;
            }
            if (cbBF_colorMode.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择正面打印颜色模式\r\n");
                return;
            }
            if (cbBB_colorMode.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择反面打印颜色模式\r\n");
                return;
            }
            uint result = DC3300Help.D300CPrintImage(tBFrontSideImgPath.Text, tBbackSideSideImgPath.Text, cbBF_rotation.SelectedIndex,
                cbBB_rotation.SelectedIndex, cbBF_ScalingMode.SelectedIndex, cbBB_ScalingMode.SelectedIndex, cbBF_colorMode.SelectedIndex,cbBB_colorMode.SelectedIndex);
            ShowResult(((Button)sender).Text, result);

        }

        private void btFrontSideImgPath_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "image files (*.jpg)|*.jpg|(*.jpeg)|*.jpeg|(*.png)|*.png|(*.bmp)|*.bmp";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                tBFrontSideImgPath.Text = ofd.FileName;
            }
        }

        private void btbackSideSideImgPath_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "image files (*.jpg)|*.jpg|(*.jpeg)|*.jpeg|(*.png)|*.png|(*.bmp)|*.bmp";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                tBbackSideSideImgPath.Text = ofd.FileName;
            }
        }

        private void btD300CPrintTestCard_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CPrintTestCard();
            ShowResult(((Button)sender).Text, result);

        }

        private void btD300CPrintBegin_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CPrintBegin();
            ShowResult(((Button)sender).Text, result);
        }

        private void btReadD300COvercoatThickness_Click(object sender, EventArgs e)
        {
            byte value = 0;
            uint result = DC3300Help.D300COvercoatThickness(0,ref value);
            ShowResult(((Button)sender).Text, result);
            if (result == 0)
            {
                rTBResult.AppendText("覆膜厚度：" + value.ToString() + "\r\n");
            }
        }

        private void btSetD300COvercoatThickness_Click(object sender, EventArgs e)
        {
            byte value = 0;
            if (byte.TryParse(tBD300COvercoatThickness.Text,out value) == false)
            {
                rTBResult.AppendText("请输入覆膜厚度，类型为byte\r\n");
                return;
            }
            uint result = DC3300Help.D300COvercoatThickness(1, ref value);
            ShowResult(((Button)sender).Text, result);
        }

        private void btD300CPrintEnd_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CPrintEnd();
            ShowResult(((Button)sender).Text, result);
        }

        private void btD300CFlipCard_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CFlipCard();
            ShowResult(((Button)sender).Text, result);
        }

        private void btD300CUpdateCardSetup_Click(object sender, EventArgs e)
        {
            if (cbBCardType.SelectedIndex == -1)
            {
                rTBResult.AppendText("请卡片类型\r\n");
                return;
            }
            if (cbBStdCardExitPos.SelectedIndex == -1)
            {
                rTBResult.AppendText("请正常出卡口\r\n");
                return;
            }
            if (cbBErrCardExitPos.SelectedIndex == -1)
            {
                rTBResult.AppendText("请异常出卡口\r\n");
                return;
            }
            if (cbBSetCardPos.SelectedIndex == -1)
            {
                rTBResult.AppendText("请装卡方式\r\n");
                return;
            }
            ushort CardType = (ushort)cbBCardType.SelectedIndex, StdCardExitPos = (ushort)cbBStdCardExitPos.SelectedIndex,
            ErrCardExitPos = (ushort)cbBErrCardExitPos.SelectedIndex, SetCardPos = (ushort)cbBSetCardPos.SelectedIndex;

            uint result = DC3300Help.D300CUpdateCardSetup(ref CardType, ref StdCardExitPos, ref ErrCardExitPos, ref SetCardPos);
            ShowResult(((Button)sender).Text, result);
        }

        private void btD300CGetCardSetup_Click(object sender, EventArgs e)
        {
            ushort CardType = 0, StdCardExitPos = 0, ErrCardExitPos = 0, SetCardPos = 0;
            long result = DC3300Help.D300CGetCardSetup(ref CardType,out StdCardExitPos,out ErrCardExitPos,out SetCardPos);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                cbBCardType.SelectedIndex = CardType;
                cbBStdCardExitPos.SelectedIndex = StdCardExitPos;
                cbBErrCardExitPos.SelectedIndex = ErrCardExitPos;
                cbBSetCardPos.SelectedIndex = SetCardPos;
            }
        }

        private void btD300CGetPrinterStatus_Click(object sender, EventArgs e)
        {
            short shellTemp =0, headTemp = 0;
            uint mainStatus = 0,subStatus =0, errorStatus=0, warningStatus;
            byte MainCode = 0,SubCode=0;
            uint result = DC3300Help.D300CGetPrinterStatus(out shellTemp, out headTemp, out mainStatus, out subStatus, out errorStatus, out warningStatus, out MainCode, out SubCode);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                rTBResult.AppendText("打印机内部温度:" + shellTemp.ToString().Insert(2,".") +"℃\r\n");
                rTBResult.AppendText("打印头温度:" + headTemp.ToString().Insert(2, ".") + "\r\n");
                rTBResult.AppendText("打印机主状态码:" + mainStatus.ToString() + "\r\n");
                rTBResult.AppendText("打印机错误码:" + errorStatus.ToString() + "\r\n");
                rTBResult.AppendText("打印机警告码::" + warningStatus.ToString() + "\r\n");
                rTBResult.AppendText("MainCode:" + MainCode.ToString() + "\r\n");
                rTBResult.AppendText("SubCode:" + SubCode.ToString() + "\r\n");
            }
        }

        private void btD300CUpdateRibbonSetup_Click(object sender, EventArgs e)
        {
            ushort RibbonType = 0,RbNearEnd = 0;
            if (ushort.TryParse(tBRbNearEnd.Text,out RbNearEnd) == false)
            {
                rTBResult.AppendText("请设置色带将尽的阈值，0——100 之间的整数，代表 0%~100%。\r\n");
                return;
            }
            uint result = DC3300Help.D300CUpdateRibbonSetup(ref RibbonType,ref RbNearEnd);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CGetPrinterInfo_Click(object sender, EventArgs e)
        {
            uint headPrintCount = 0, printerPrintCount = 0, FWVer =0, FPGAVer =0;
            int SnLen = 0;
            char PrinterSN = ' ';
            uint result = DC3300Help.D300CGetPrinterInfo(out headPrintCount,out printerPrintCount,out FWVer,out PrinterSN,ref SnLen,out FPGAVer);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                rTBResult.AppendText("打印头已打数:" + headPrintCount.ToString() + "\r\n");
                rTBResult.AppendText("打印机已打数:" + printerPrintCount.ToString() + "\r\n");
                rTBResult.AppendText("固件主版本号:" + FWVer.ToString() + "\r\n");
                rTBResult.AppendText("打印机序列号:" + PrinterSN.ToString() + "\r\n");
                rTBResult.AppendText("PrinterSN Buffer区块大小，至少 大于等于7:" + SnLen.ToString() + "\r\n");
                rTBResult.AppendText("FPGA版本号:" + FPGAVer.ToString() + "\r\n");
            }
        }

        private void btD300CGetRibbonSetup_Click(object sender, EventArgs e)
        {
            ushort RibbonType = 0, RbNearEnd = 0;
            uint result = DC3300Help.D300CGetRibbonSetup(out RibbonType, out RbNearEnd);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                rTBResult.AppendText("色带色带将尽的阈值:" + RbNearEnd.ToString() + "\r\n");                                
            }
        }

        private void btD300CGetRibbonFilmSurplus_Click(object sender, EventArgs e)
        {
            ushort ribbonSurplus = 0;
            uint result = DC3300Help.D300CGetRibbonFilmSurplus(out ribbonSurplus);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                rTBResult.AppendText("色带剩余量:" + ribbonSurplus.ToString() + "\r\n");                
            }

        }

        private void btD300CPrinterHaveCard_Click(object sender, EventArgs e)
        {
            int flag = 0;
            uint result = DC3300Help.D300CPrinterHaveCard(out flag);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                string hadCard = "打印机" + (flag == 1?"有卡":"无卡");
                rTBResult.AppendText(hadCard + "\r\n");                
            }
        }

        private void btD300CGetImageSetup_Click(object sender, EventArgs e)
        {
            byte YBalanceSetting = 0, MBalanceSetting = 0, CBalanceSetting = 0, KBalanceSetting = 0, OverCoatSetting = 0;
            uint result = DC3300Help.D300CGetImageSetup(out YBalanceSetting,out MBalanceSetting,out CBalanceSetting,out KBalanceSetting,out OverCoatSetting);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                tBYBalanceSetting.Text = YBalanceSetting.ToString();
                tBMBalanceSetting.Text = MBalanceSetting.ToString();
                tBCBalanceSetting.Text = CBalanceSetting.ToString();
                tBKBalanceSetting.Text = KBalanceSetting.ToString();
                tBOverCoatSetting.Text = OverCoatSetting.ToString();
            }
        }

        private void btD300CUpdateImageSetup_Click(object sender, EventArgs e)
        {
            string YBalanceSetting = tBYBalanceSetting.Text,
                MBalanceSetting = tBMBalanceSetting.Text,
                CBalanceSetting = tBCBalanceSetting.Text,
                KBalanceSetting = tBKBalanceSetting.Text,
                OverCoatSetting = tBOverCoatSetting.Text;
            uint result = DC3300Help.D300CUpdateImageSetup(YBalanceSetting, MBalanceSetting, CBalanceSetting, KBalanceSetting, OverCoatSetting);
            ShowResult(((Button)sender).Text, (uint)result);


            //byte YBalanceSetting = 25,
            //    MBalanceSetting = 25,
            //    CBalanceSetting = 25,
            //    KBalanceSetting = 25,
            //    OverCoatSetting = 25;
            //uint result = DC3300Help.D300CUpdateImageSetup(YBalanceSetting, MBalanceSetting, CBalanceSetting, KBalanceSetting, OverCoatSetting);
            //ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawSetCardRect_Click(object sender, EventArgs e)
        {
            double w =0,h=0;
            if (double.TryParse(tBCardWidth.Text,out w) == false)
            {
                rTBResult.AppendText("请输入正确的卡宽度，类型为double" + "\r\n");
                tBCardWidth.Focus();
                return;
            }
            if (double.TryParse(tBCardHeight.Text, out h) == false)
            {
                rTBResult.AppendText("请输入正确的卡高度，类型为double" + "\r\n");
                tBCardHeight.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawSetCardRect(w,h);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CBeginDraw_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CBeginDraw();
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawText_Click(object sender, EventArgs e)
        {
            double ox=0, oy=0, w = 0, h =0;
            string data = tBString.Text.Trim();
            if (double.TryParse(tBox.Text,out ox) == false)
            {
                rTBResult.AppendText("请输入正确的左上角 X 坐标，类型为double" + "\r\n");
                tBox.Focus();
                return;
            }
            if (double.TryParse(tBoy.Text, out oy) == false)
            {
                rTBResult.AppendText("请输入正确的左上角 Y 坐标，类型为double" + "\r\n");
                tBoy.Focus();
                return;
            }
            if (double.TryParse(tBStringW.Text, out w) == false)
            {
                rTBResult.AppendText("请输入正确的区域宽度，类型为double" + "\r\n");
                tBStringW.Focus();
                return;
            }
            if (double.TryParse(tBStringH.Text, out h) == false)
            {
                rTBResult.AppendText("请输入正确的区域高度，类型为double" + "\r\n");
                tBStringH.Focus();
                return;
            }
            if (data == "")
            {
                rTBResult.AppendText("请输入绘制文本" + "\r\n");
                tBString.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawText(ox,oy,w,h,data);
            ShowResult(((Button)sender).Text, (uint)result);

        }

        private void btDS600EndDraw_Click(object sender, EventArgs e)
        {
            string tempImg = "aa";
            IntPtr ptrIn = System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(tempImg);
            uint result = DC3300Help.DS600EndDraw(ref ptrIn);
            
            if (result == 0)
            {
                string retlust = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(ptrIn);
                if (File.Exists(retlust) == false)
                {
                    rTBResult.AppendText("【" + DateTime.Now.ToString() + "】结束绘图失败，文件不存在。\r\n");
                    return;
                }
                result = DC3300Help.D300CPrintImage(retlust, "", 0, 0, 0, 0, 0, 0);
                ShowResult(((Button)sender).Text, result);
                rTBResult.AppendText("绘图文件名：" + retlust + "\r\n");
                //File.Delete(retlust);
            }
            

            ShowResult(((Button)sender).Text, (uint)result);

        }

        private void btD300CDrawSetTextDecorate_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CDrawSetTextDecorate(cBBold.Checked,cBItalic.Checked,cBUnderLine.Checked);
            ShowResult(((Button)sender).Text, (uint)result);

        }

        private void btD300CDrawSetTextDirection_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CDrawSetTextDirection(cBisLandScape.Checked, cBisReverseSequence.Checked, cBisAutoLineFeed.Checked, cBisLayDown.Checked);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawSetFont_Click(object sender, EventArgs e)
        {
            string fontName = cbBFontName.Text.Trim();
            float fontSize = 0;
            if (fontName == "")
            {
                rTBResult.AppendText("请选择绘制字体名称" + "\r\n");
                return;
            }
            if (float.TryParse(tBFontSize.Text,out fontSize) == false)
            {
                rTBResult.AppendText("请输入绘制字体大小，类型float" + "\r\n");
                tBFontSize.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawSetFont(fontName,fontSize);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawSetTextColor_Click(object sender, EventArgs e)
        {
            byte r = 0, g = 0, b = 0;
            if (byte.TryParse(tBFontRed.Text,out r) == false)
            {
                rTBResult.AppendText("请输入红色分量值，类型byte" + "\r\n");
                tBFontRed.Focus();
                return;
            }
            if (byte.TryParse(tBFontGreen.Text, out r) == false)
            {
                rTBResult.AppendText("请输入绿色分量值，类型byte" + "\r\n");
                tBFontGreen.Focus();
                return;
            }
            if (byte.TryParse(tBFontBlue.Text, out r) == false)
            {
                rTBResult.AppendText("请输入蓝色分量值，类型byte" + "\r\n");
                tBFontBlue.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawSetTextColor(r,g,b);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawSetSpacing_Click(object sender, EventArgs e)
        {
            double lineSpacing = 0,charSpacing = 0;
            if (double.TryParse(tBlineSpacing.Text,out lineSpacing) == false)
            {
                rTBResult.AppendText("请输入正确的行间距，单位 n 倍行距，类型double" + "\r\n");
                tBlineSpacing.Focus();
                return;
            }
            if (double.TryParse(tBcharSpacing.Text, out charSpacing) == false)
            {
                rTBResult.AppendText("请输入正确的字间距，单位 n 磅，类型double" + "\r\n");
                tBcharSpacing.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawSetSpacing(lineSpacing,charSpacing);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawBarCode_Click(object sender, EventArgs e)
        {
            double ox = 0,oy = 0,w =0, h = 0;
            string data = tBBarcodeText.Text.Trim();
            int barcodeMultiplier = 0;
            if (double.TryParse(tBBarcodeX.Text,out ox) == false)
            {
                rTBResult.AppendText("请输入正确的X坐标，类型double" + "\r\n");
                tBBarcodeX.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeY.Text, out oy) == false)
            {
                rTBResult.AppendText("请输入正确的Y坐标，类型double" + "\r\n");
                tBBarcodeY.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeW.Text, out w) == false)
            {
                rTBResult.AppendText("请输入宽度，类型double" + "\r\n");
                tBBarcodeW.Focus();
                return;
            }
            if (double.TryParse(tBBarcodeH.Text, out h) == false)
            {
                rTBResult.AppendText("请输入高度，类型double" + "\r\n");
                tBBarcodeH.Focus();
                return;
            }
            if (data == "")
            {
                rTBResult.AppendText("请输条码内容" + "\r\n");
                tBBarcodeText.Focus();
                return;
            }
            if (cbBBarcodeType.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择条码类型" + "\r\n");
                return;
            }
            if (int.TryParse(tBbarcodeMultiplier.Text,out barcodeMultiplier) == false)
            {
                rTBResult.AppendText("请输入正确的放大倍数，类型int" + "\r\n");
                tBbarcodeMultiplier.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawBarCode(ox,oy,w,h,data,cbBBarcodeType.SelectedIndex,
                cBShowBarcodeText.Checked,cBisUnderText.Checked,barcodeMultiplier);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawClear_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CDrawClear();
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btD300CDrawQR_Click(object sender, EventArgs e)
        {
            double ox = 0, oy=0, w=0, h =0;
            string data = tBQRText.Text.Trim();
            int errLev = 0;
            if (double.TryParse(tBQRX.Text,out ox) == false)
            {
                rTBResult.AppendText("请输入正确的X坐标，类型double" + "\r\n");
                tBQRX.Focus();
                return;
            }
            if (double.TryParse(tBQRY.Text, out oy) == false)
            {
                rTBResult.AppendText("请输入正确的Y坐标，类型double" + "\r\n");
                tBQRY.Focus();
                return;
            }
            if (double.TryParse(tBQRW.Text, out w) == false)
            {
                rTBResult.AppendText("请输入宽度，类型double" + "\r\n");
                tBQRW.Focus();
                return;
            }
            if (double.TryParse(tBQRH.Text, out h) == false)
            {
                rTBResult.AppendText("请输入高度，类型double" + "\r\n");
                tBQRH.Focus();
                return;
            }
            if (data == "")
            {
                rTBResult.AppendText("请输二维码内容" + "\r\n");
                tBQRText.Focus();
                return;
            }
            if (cbBQRerrLev.SelectedIndex == -1)
            {
                rTBResult.AppendText("请选择容错率" + "\r\n");
                return;
            }
            uint result = DC3300Help.D300CDrawQR(ox, oy, w, h, data, errLev, cBQRAutoFill.Checked);
            ShowResult(((Button)sender).Text, (uint)result);

        }

        private void btD300CDrawSetBarCodeColor_Click(object sender, EventArgs e)
        {
            byte R = 0,G = 0,B = 0;
            if (byte.TryParse(tBR.Text,out R) == false)
            {
                rTBResult.AppendText("请输入红色值，类型byte" + "\r\n");
                tBR.Focus();
                return;
            }
            if (byte.TryParse(tBG.Text, out G) == false)
            {
                rTBResult.AppendText("请输入绿色值，类型byte" + "\r\n");
                tBG.Focus();
                return;
            }
            if (byte.TryParse(tBB.Text, out B) == false)
            {
                rTBResult.AppendText("请输入蓝色值，类型byte" + "\r\n");
                tBB.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawSetBarCodeColor(R,G,B);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btimagefile_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "image files (*.jpg)|*.pjg|(*.png)|*.png|(*.jpeg)|*.jpeg|(*.bmp)|*.bmp|All files (*.*)|*.*";
            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                tBDrawImagePath.Text = ofd.FileName;
            }
        }

        private void btD300CDrawImage_Click(object sender, EventArgs e)
        {
            double ox =0, oy=0, w=0, h=0;
            string imagefile = tBDrawImagePath.Text.Trim();
            if (double.TryParse(tBD300CDrawImageX.Text, out ox) == false)
            {
                rTBResult.AppendText("请输入正确的X坐标，类型double" + "\r\n");
                tBD300CDrawImageX.Focus();
                return;
            }
            if (double.TryParse(tBD300CDrawImageY.Text, out oy) == false)
            {
                rTBResult.AppendText("请输入正确的Y坐标，类型double" + "\r\n");
                tBD300CDrawImageY.Focus();
                return;
            }
            if (double.TryParse(tBD300CDrawImageW.Text, out w) == false)
            {
                rTBResult.AppendText("请输入宽度，类型double" + "\r\n");
                tBD300CDrawImageW.Focus();
                return;
            }
            if (double.TryParse(tBD300CDrawImageH.Text, out h) == false)
            {
                rTBResult.AppendText("请输入高度，类型double" + "\r\n");
                tBD300CDrawImageH.Focus();
                return;
            }
            if (imagefile == "")
            {
                rTBResult.AppendText("请输入图片路径" + "\r\n");
                tBDrawImagePath.Focus();
                return;
            }
            uint result = DC3300Help.D300CDrawImage(ox, oy, w, h, imagefile, cBisautofill.Checked, cbBrotation.SelectedIndex);
            ShowResult(((Button)sender).Text, (uint)result);

        }

        private void btD300CDrawInSession_Click(object sender, EventArgs e)
        {
            bool flag = false;
            uint result = DC3300Help.D300CDrawInSession(ref flag);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result == 0)
            {
                rTBResult.AppendText("正在绘图" + "\r\n");
            }
            else
                rTBResult.AppendText("不是正在绘图" + "\r\n");

        }

        private void btD300CSetIOTimeout_Click(object sender, EventArgs e)
        {
            int readTimeout = 0,writeTimeout = 0;
            if (int.TryParse(tBreadTimeout.Text,out readTimeout) == false)
            {
                rTBResult.AppendText("请输入读超时，单位为毫秒，类型为int" + "\r\n");
                tBreadTimeout.Focus();
                return;
            }
            if (int.TryParse(tBwriteTimeout.Text, out readTimeout) == false)
            {
                rTBResult.AppendText("请输入写超时，单位为毫秒，类型为int" + "\r\n");
                tBwriteTimeout.Focus();
                return;
            }
            uint result = DC3300Help.D300CSetIOTimeout(readTimeout,writeTimeout);
            ShowResult(((Button)sender).Text, (uint)result);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            IntPtr i = (System.IntPtr)0;
            uint result = DC3300Help.D300CToBad(i);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            IntPtr i = (System.IntPtr)0;
            uint result = DC3300Help.D300CToGood(i);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FontFamily[] font = GetSystemFont();
            for (int i = 0; i < font.Length; i++)
            {
                cbBFontName.Items.Add(font[i].Name);
            }
        }
        private FontFamily[] GetSystemFont()
        {
            //获取系统已经安装的字体
            InstalledFontCollection MyFont = new InstalledFontCollection();
            FontFamily[] MyFontFamilies = MyFont.Families;
            return MyFontFamilies;
        }

        private void btDrawTest_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CDrawText(14.5, 13, 35, 4.5, "证件样卡");
            result = DC3300Help.D300CDrawText(14.5, 19, 6, 4.5, "女");
            result = DC3300Help.D300CDrawText(30.5, 19, 21, 4.5, "汉族");
            result = DC3300Help.D300CDrawText(14.5, 25, 42, 4.5, "441900198309172787");
            result = DC3300Help.D300CDrawText(14.5, 31, 42, 4.5, "广州市天河区龙洞西街30号");
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CDrawSetFont("微软雅黑", 12);
            DC3300Help.D300CDrawText(10, 20, 50, 12, "卡号：0475000782");
            DC3300Help.D300CDrawImage(48, 10, 30, 30, @"C:\Users\HuanBiao\Desktop\tou.jpg", false, 0);
            DC3300Help.D300CDrawText(10, 32, 50, 12, "电话：137-2404-2408");
            DC3300Help.D300CDrawSetFont("微软雅黑", 20);
            DC3300Help.D300CDrawText(30, 5, 30, 20, "羊城通");
        }

        private void btD300CAddNoOverCoatRgn_Click(object sender, EventArgs e)
        {
            double ox = 0, oy = 0, w = 0, h = 0;
            if (double.TryParse(tBD300CAddNoOverCoatRgnX.Text, out ox) == false)
            {
                rTBResult.AppendText("请输入正确的X坐标，类型double" + "\r\n");
                tBD300CAddNoOverCoatRgnX.Focus();
                return;
            }
            if (double.TryParse(tBD300CAddNoOverCoatRgnY.Text, out oy) == false)
            {
                rTBResult.AppendText("请输入正确的Y坐标，类型double" + "\r\n");
                tBD300CAddNoOverCoatRgnY.Focus();
                return;
            }
            if (double.TryParse(tBD300CAddNoOverCoatRgnW.Text, out w) == false)
            {
                rTBResult.AppendText("请输入宽度，类型double" + "\r\n");
                tBD300CAddNoOverCoatRgnW.Focus();
                return;
            }
            if (double.TryParse(tBD300CAddNoOverCoatRgnH.Text, out h) == false)
            {
                rTBResult.AppendText("请输入高度，类型double" + "\r\n");
                tBD300CAddNoOverCoatRgnH.Focus();
                return;
            }
            uint result = DC3300Help.D300CAddNoOverCoatRgn(ox, oy, w, h, cbBD300CAddNoOverCoatRgnRotation.SelectedIndex);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btGX_Click(object sender, EventArgs e)
        {
            uint result = DC3300Help.D300CDrawSetFont("微软雅黑", 8);
            DC3300Help.D300CDrawText(20, 5, 30, 4, "张三8号雅黑加粗");
            DC3300Help.D300CDrawImage(53, 3, 23, 30, @"E:\HB\壁挂式查询机\InfoEQM_HT20180601\InfoEQM\bin\Debug\Face.jpg", false, 0);
            DC3300Help.D300CDrawText(20, 10, 8, 4, "女");
            DC3300Help.D300CDrawText(39, 10, 10, 4, "汉族");
            DC3300Help.D300CDrawText(20, 15.5, 9.5, 4, "1998");
            DC3300Help.D300CDrawText(33.5, 15.5, 4, 4, "12");
            DC3300Help.D300CDrawText(42, 15.5, 10, 4, "13");
            DC3300Help.D300CDrawText(20, 20.7, 33, 4, "440110199812132345");
            result = DC3300Help.D300CDrawText(20, 26, 33, 8, "广西省南宁市西乡塘区灵厢路东三巷6号");
            result = DC3300Help.D300CAddNoOverCoatRgn(19, 34.5, 64, 19, 0);
            ShowResult(((Button)sender).Text, (uint)result);
        }

        private void btGetSensorStatus_Click(object sender, EventArgs e)
        {
            uint value = 0;
            uint result = DC3300Help.D300CGetSensorStatus(4,ref value);
            ShowResult(((Button)sender).Text, (uint)result);
            if (result != 0)
            {
                rTBResult.AppendText("获取传感失败：" +DC3300Help.GetErrorMess(result) +"\r\n");
            }
            rTBResult.AppendText(value.ToString());
            if (value != 0) rTBResult.AppendText("卡盒无卡\r\n");
            else rTBResult.AppendText("卡盒有卡\r\n");
        }
    }
}
