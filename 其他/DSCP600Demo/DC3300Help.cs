using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace DSCP600Demo
{
    public class DC3300Help
    {
        private const string dllName = "DSCP600.dll";//直印机
        private const string AIDdllName = ".\\AIO\\DSCP600.dll";//一体机

        #region 连接打印机
        
        //获取打印机列表，打印机数量，打印机类型
        [DllImport(dllName ,CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern string DSEnumPrinter();

        /// <summary>
        /// 打开打印机
        /// </summary>
        /// <param name="printerName">打印机名称</param>
        /// <returns>成功返回 0;则返回非 0，具体参见附录 1 错误码</returns>
        [DllImport(dllName)]
        public static extern uint D300COpenPrinter(string printerName);

        /// <summary>
        /// 关闭打印机
        /// </summary>
        [DllImport(dllName)]
        public static extern void DSClosePrinter();

        #endregion

        #region 打印相关命令

        /// <summary>
        /// 打印图像(如果打印机打印位无卡将自动进卡，有卡则直接进行打印；打印完成之后不会自动退卡，请调用D300CToGood()或D300CToBad()来退到好卡口或坏卡口。)
        /// </summary>
        /// <param name="FrontSideImgPath">指定正面打印图片的路径</param>
        /// <param name="backSideSideImgPath">指定背面打印图片的路径</param>
        /// <param name="F_rotation">正面旋转之后打印，取值范围及含义如下：
        /// 0：不旋转；
        /// 1：旋转 90 度（逆时针）；
        /// 2：旋转 180 度（逆时针）；
        /// 3：旋转 270 度（逆时针）。</param>
        /// <param name="B_rotation">反面旋转之后打印，取值范围及含义同上。</param>
        /// <param name="F_ScalingMode">正面图片拉伸模式，取值定义如下：
        /// 0：拉伸铺满；
        /// 1：居中铺满；
        /// 2：原始比例铺满。</param>
        /// <param name="B_ScalingMode">反面图片拉伸模式，取值范围及含义同上</param>
        /// <param name="F_colorMode">正面图片打印颜色模式，取值定义如下：
        /// 0：使用 YMC 混色打印；
        /// 1：纯黑色使用 K 色打印，其余颜色使用 YMC 混色；
        /// 2：仅用 K 色打印，半色调方式为阈值；
        /// 3：仅用 K 色打印，半色调方式为误差扩散；
        /// 4：仅用 K 色打印，半色调方式为有序抖动。</param>
        /// <param name="B_colorMode">背面图片打印颜色模式，取值定义同 F_colorMode；</param>
        /// <param name="printToImg">恒为 false</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CPrintImage(string FrontSideImgPath, string backSideSideImgPath, int F_rotation,int B_rotation,int F_ScalingMode,int B_ScalingMode,int F_colorMode,int B_colorMode,bool printToImg = false);

        /// <summary>
        /// 中止打印
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CAbortPrinting();

        /// <summary>
        /// 打印测试卡
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CPrintTestCard();

        /// <summary>
        /// 进卡（执行进卡动作。进卡位置请用 D300CInjectPosition 来设置）
        /// </summary>
        /// <param name="mode">恒为0</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CPrintBegin(int mode = 0);

        /// <summary>
        /// 出卡到好卡口(三合一读卡器机型用)
        /// </summary>
        /// <param name="handle">读卡器句柄，该句柄由D300COpenReader() 获取</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CToGood(IntPtr handle);

        /// <summary>
        /// 出卡到坏卡口(三合一读卡器机型用)
        /// </summary>
        /// <param name="handle">读卡器句柄，该句柄由D300COpenReader() 获取</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CToBad(IntPtr handle);

        /// <summary>
        /// 读卡器前端夹卡超时退卡
        /// </summary>
        /// <param name="handle">读卡器句柄，该句柄由D300COpenReader() 获取</param>
        /// <param name="timeout">夹卡超时时间，单位：秒</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CEjectCardFront(IntPtr handle, byte timeout);

        /// <summary>
        /// 设置打印机覆膜厚度
        /// </summary>
        /// <param name="mode">0：读取当前覆膜厚度，1：设置覆膜层厚度</param>
        /// <param name="thickness">覆膜层厚度，mode 为0时，用于接收读取的厚度值；mode 为1 时，用于传入要设置的值。</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300COvercoatThickness(int mode, ref byte thickness);

        /// <summary>
        /// 打印机退卡
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CPrintEnd();

        /// <summary>
        /// 翻转卡片
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CFlipCard();

        /// <summary>
        /// 设置进出卡位置
        /// </summary>
        /// <param name="CardType">卡片类型 PVC:0x00 / PET:0x01 PET-G:0x02/ PC:0x03</param>
        /// <param name="StdCardExitPos">设置正常出卡口，前方出卡后:0x00 后方出卡后:0x01</param>
        /// <param name="ErrCardExitPos">设置异常出卡口，前方出卡后:0x00 后方出卡后:0x01</param>
        /// <param name="SetCardPos">设置装卡方式 ，普通送卡:0x00 ，翻转送卡:0x01 （装卡后送到翻转器翻转后，再返回等待打印位置）</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CUpdateCardSetup(ref ushort CardType,ref ushort StdCardExitPos,ref ushort ErrCardExitPos,ref ushort SetCardPos);

        /// <summary>
        /// 读取进出卡位置
        /// </summary>
        /// <param name="CardType">卡片类型 PVC:0x00 / PET:0x01 PET-G:0x02/ PC:0x03</param>
        /// <param name="StdCardExitPos">读取正常出卡口，前方出卡后:0x00 后方出卡后:0x01</param>
        /// <param name="ErrCardExitPos">读取异常出卡口，前方出卡后:0x00 后方出卡后:0x01</param>
        /// <param name="SetCardPos">读取装卡方式 ，普通送卡:0x00 ，翻转送卡:0x01 （装卡后送到翻转器翻转后，再返回等待打印位置）</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern long D300CGetCardSetup(ref ushort CardType,out ushort StdCardExitPos,out ushort ErrCardExitPos,out ushort SetCardPos);

        #endregion

        #region 打印机状态
        /// <summary>
        /// 获取打印机的状态、温度信息
        /// 1. 返回的温度值是实际温度值乘以 100，例如返回 3100 表示 31.00℃。
        /// 2. 打印机的主状态码、错误码和警告码如附录2，也可以使用 D300CIsXXX
        /// 系列函数帮助解析；
        /// </summary>
        /// <param name="shellTemp">返回打印机内部温度</param>
        /// <param name="headTemp">返回打印头温度</param>
        /// <param name="mainStatus">返回打印机主状态码</param>
        /// <param name="subStatus">保留，置 0</param>
        /// <param name="errorStatus">返回打印机错误码</param>
        /// <param name="warningStatus">返回打印机警告码</param>
        /// <param name="MainCode">返回 MainCode</param>
        /// <param name="SubCode">返回 SubCode</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CGetPrinterStatus(out short shellTemp, out short headTemp, out uint mainStatus, out uint subStatus, out uint errorStatus, out uint warningStatus, out byte MainCode, out byte SubCode);

        /// <summary>
        /// 更新色带信息(当色带剩余量低于该阈值，打印机将判定色带将尽。)
        /// </summary>
        /// <param name="RibbonType">色带类型，不需设置此项时填 NULL</param>
        /// <param name="RbNearEnd">设定色带将尽的阈值，不需设置此项时填 NULL。取值范围：0——100 之间的整数，代表 0%~100%。</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CUpdateRibbonSetup(ref ushort RibbonType,ref ushort RbNearEnd);

        /// <summary>
        /// 获取打印机的相关信息
        /// </summary>
        /// <param name="headPrintCount">返回打印头已打数</param>
        /// <param name="printerPrintCount">返回打印机已打数</param>
        /// <param name="FWVer">返回固件主版本号</param>
        /// <param name="PrinterSN">返回打印机序列号</param>
        /// <param name="SnLen">PrinterSN Buffer区块大小，至少 大于等于7</param>
        /// <param name="FPGAVer">返回FPGA版本号</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CGetPrinterInfo(out uint headPrintCount,out uint printerPrintCount,out uint FWVer,out char PrinterSN,ref int SnLen,out uint FPGAVer);

        /// <summary>
        /// 获取色带剩余量
        /// </summary>
        /// <param name="ribbonSurplus">返回色带剩余量，范围： 0——100 之间的整数，代表 0%~100%。</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CGetRibbonFilmSurplus(out ushort ribbonSurplus);

        /// <summary>
        /// 获取色带信息(当色带剩余量低于该阈值，打印机将判定色带将尽。)
        /// </summary>
        /// <param name="ribbonType">色带类型， 不获取此项时填 NULL</param>
        /// <param name="rbNearEnd">获取色带将尽的阈值，不获取此项时填 NULL。取值范围： 0——100 之间的整数，代表 0%~100%。</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CGetRibbonSetup(out ushort ribbonType, out ushort rbNearEnd);

        /// <summary>
        /// 读卡器是否有卡
        /// </summary>
        /// <param name="handle">读卡器句柄</param>
        /// <param name="flag">如果有卡，flag接收到1，否则为0</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CReaderHaveCard(IntPtr handle,out int flag);

        /// <summary>
        /// 打印机是否有卡
        /// </summary>
        /// <param name="flag">如果有卡，flag接收到1，否则为0</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CPrinterHaveCard(out int flag);

        /// <summary>
        /// 获取打印机色彩设置
        /// </summary>
        /// <param name="YBalanceSetting">黄色颜色平衡，取值 ±64</param>
        /// <param name="MBalanceSetting">品红色颜色平衡，取值 ±64</param>
        /// <param name="CBalanceSetting">青色颜色平衡，取值 ±64</param>
        /// <param name="KBalanceSetting">黑色颜色平衡，取值 ±64</param>
        /// <param name="OverCoatSetting">OverCoat颜色平衡，取值 ±64</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CGetImageSetup(out byte YBalanceSetting, out byte MBalanceSetting, out byte CBalanceSetting, out byte KBalanceSetting, out byte OverCoatSetting);

        /// <summary>
        /// 打印机色彩设置
        /// </summary>
        /// <param name="YBalanceSetting">黄色颜色平衡，取值 ±64</param>
        /// <param name="MBalanceSetting">品红色颜色平衡，取值 ±64</param>
        /// <param name="CBalanceSetting">青色颜色平衡，取值 ±64</param>
        /// <param name="KBalanceSetting">黑色颜色平衡，取值 ±64</param>
        /// <param name="OverCoatSetting">OverCoat颜色平衡，取值 ±64</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CUpdateImageSetup(string YBalanceSetting,string MBalanceSetting,string CBalanceSetting,string KBalanceSetting,string OverCoatSetting);

        /// <summary>
        /// 获取传感器的状态
        /// </summary>
        /// <param name="SensorID"></param>
        /// <param name="SensorVal"></param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CGetSensorStatus(uint SensorID, ref uint SensorVal);

        #endregion

        #region 套打接口

        /// <summary>
        /// 设置卡片尺寸（请在 D300CBeginDraw 前调用）
        /// </summary>
        /// <param name="w">卡片宽度，单位 mm。</param>
        /// <param name="h">卡片高度，单位 mm。</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetCardRect(double w, double h);

        /// <summary>
        /// 开始绘图(请在绘制所有元素（文本、一维码、二维码）之前，调用该接口。)
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CBeginDraw();

        /// <summary>
        /// 绘制文本(请在使用本接口前，调用相关设置字体样式的接口)
        /// </summary>
        /// <param name="ox">指定用于绘制文本的区域左上角 X 坐标，单位：mm</param>
        /// <param name="oy">指定用于绘制文本的区域左上角 Y 坐标，单位：mm</param>
        /// <param name="w">指定用于绘制文本的区域宽度，单位：mm。</param>
        /// <param name="h">指定用于绘制文本的区域高度，单位：mm</param>
        /// <param name="data">指定要绘制的文本</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawText(double ox,double oy,double w,double h,string data);

        /// <summary>
        /// 结束绘图
        /// </summary>
        /// <param name="tempImg">指向一个字串指针，用于接收产生临时图片文件的路径，调用者应负责销毁该临时文件。
        /// 在使用完该函数传出的字串后，请使用 D300CFreeString 释放。</param>
        /// <param name="tagName">在tempImg前加入自定义标识。比如tagName 为NULL时，*tempImg是 abc.bmp,当tagName=“正面”时,则最终结果微：正面_abc.bmp.</param>
        /// <returns></returns>
        [DllImport(dllName, CharSet = CharSet.Auto)]
        public static extern uint DS600EndDraw(ref IntPtr tempImg, string tagName = null);

        /// <summary>
        /// 设置字体风格(请在使用 D300CDrawText 接口前调用)
        /// </summary>
        /// <param name="isStrong">指定是否以粗体绘制</param>
        /// <param name="isItalic">指定是否以斜体绘制</param>
        /// <param name="isUnderline">指定绘制的字体是否加下划线</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetTextDecorate(bool isStrong,bool isItalic,bool isUnderline);

        /// <summary>
        /// 设置文本格式：平躺字体、反向输出、自动换行(请在使用 D300CDrawText 接口前调用)
        /// </summary>
        /// <param name="isLandScape">是否横向绘制文本</param>
        /// <param name="isReverseSequence">是否反向绘制文本</param>
        /// <param name="isAutoLineFeed">是 否 在 文 本 块 内 自 动 换 行 ， 文 本 块 大 小 由D300CDrawText 定义</param>
        /// <param name="isLayDown">是否字体平躺</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetTextDirection(bool isLandScape,bool isReverseSequence,bool isAutoLineFeed,bool isLayDown);

        /// <summary>
        /// 设置字体及字号大小(请在使用 D300CDrawText 接口前调用)
        /// </summary>
        /// <param name="fontName">指定要绘制的字体</param>
        /// <param name="size">指定字体大小</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetFont(string fontName,float size);

        /// <summary>
        /// 设置字体的颜色(请在使用 D300CDrawText 接口前调用)
        /// </summary>
        /// <param name="R">指定字体颜色的红色分量值，取值范围 0~255</param>
        /// <param name="G">指定字体颜色的绿色分量值，取值范围 0~255</param>
        /// <param name="B">指定字体颜色的蓝色分量值，取值范围 0~255</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetTextColor(byte R,byte G,byte B);

        /// <summary>
        /// 设置字间距、行间距(请在使用 D300CDrawText 接口前调用)
        /// </summary>
        /// <param name="lineSpacing">指定文本块的行间距，单位 n 倍行距</param>
        /// <param name="charSpacing">指定文本块的字间距，单位 n 磅</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetSpacing(double lineSpacing, double charSpacing);

        /// <summary>
        /// 绘制一维码
        /// </summary>
        /// <param name="ox">指定用于绘制一维码的区域左上角 x 坐标，单位 mm</param>
        /// <param name="oy">指定用于绘制一维码的区域左上角 y 坐标，单位 mm</param>
        /// <param name="w">指定用于绘制一维码的区域宽度，单位 mm</param>
        /// <param name="h">指定用于绘制一维码的区域高度，单位 mm</param>
        /// <param name="data">文本块，用于标识人工识别符</param>
        /// <param name="barcodeType">指定绘制条码的类型，取值范围及含义如下：
        /// 0 = 39 码
        /// 1 = 交叉 25 码
        /// 2 = UPC–E 码
        /// 3. = EAN8 码
        /// 4. = EAN13 码
        /// 5. = UPC–A 码
        /// 6. = 93 码
        /// 7= code 128 C 码
        /// 8 = code 128 B 码</param>
        /// <param name="isText">是否显示人工识别符</param>
        /// <param name="isUnderText">人工识别符在条码下方</param>
        /// <param name="barcodeMultiplier">放大倍数</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawBarCode(double ox,double oy,double w,double h,string data,int barcodeType,bool isText,bool isUnderText,int barcodeMultiplier);

        /// <summary>
        /// 清除绘图缓存(调用该接口清除本次绘图的内容。如需再次绘图，请使用 D300CBeginDraw 重新开始)
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawClear();

        /// <summary>
        /// 绘制二维码
        /// </summary>
        /// <param name="ox">指定用于绘制二维码的区域左上角 X 坐标，单位 mm</param>
        /// <param name="oy">指定用于绘制二维码的区域左上角 Y 坐标，单位 mm</param>
        /// <param name="w">指定用于绘制二维码的区域宽度，单位 mm</param>
        /// <param name="h">指定用于绘制二维码的区域高度，单位 mm</param>
        /// <param name="data">指定二维码的内容</param>
        /// <param name="errLev">指定二维码的容错率，取值范围及含义如下：
        /// 0 = 容错率 (7%)
        /// 1 = 容错率(15%)
        /// 2= 容错率(25%)
        /// 3 = 容错率(30%)</param>
        /// <param name="isAutoFill">保留，传 true 即可</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawQR(double ox,double oy,double w,double h,string data,int errLev,bool isAutoFill);

        /// <summary>
        /// 设置条码、二维码颜色(请在使用 D300CDrawBarCode、D300CDrawQR 接口之前调用)
        /// </summary>
        /// <param name="R">指定条码、二维码颜色的红色分量值，取值范围 0~255</param>
        /// <param name="G">指定条码、二维码颜色的绿色分量值，取值范围 0~255</param>
        /// <param name="B">指定条码、二维码颜色的蓝色分量值，取值范围 0~255</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawSetBarCodeColor(byte R,byte G,byte B);

        /// <summary>
        /// 绘制图块
        /// </summary>
        /// <param name="ox">指定用于绘制图块的区域左上角 X 坐标，单位 mm</param>
        /// <param name="oy">指定用于绘制图块的区域左上角 Y 坐标，单位 mm</param>
        /// <param name="w">指定用于绘制图块的区域宽度，单位 mm</param>
        /// <param name="h">指定用于绘制图块的区域高度，单位 mm</param>
        /// <param name="imagefile">指定图块路径</param>
        /// <param name="isautofill">true 贴图 false 白色透传</param>
        /// <param name="rotation">旋转角度：0：不旋转，1:90度，2:180度，3:270度</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawImage( double ox,double oy,double w,double h,string imagefile,bool isautofill,int rotation = 0);

        /// <summary>
        /// 判断是否正在绘图(在 D300CBeginDraw 和 D300CEndDraw 之间的任何时候，都是在绘图阶段中，此时调用该函数，flag 返回为 true；否则返回为 false.)
        /// </summary>
        /// <param name="flag">指向 bool 的指针，用于接收是否处于一个绘图阶段中</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CDrawInSession(ref bool flag);

        /// <summary>
        /// 添加无O层区域(无覆膜区域)
        /// </summary>
        /// <param name="ox">x坐标</param>
        /// <param name="oy">y坐标</param>
        /// <param name="w">宽度</param>
        /// <param name="h">高度</param>
        /// <param name="rotation">旋转角度：0 无旋转；1 90读；2 180度；3 270度</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CAddNoOverCoatRgn(double ox, double oy, double w, double h,int rotation);

        #endregion

        #region 八、特殊命令
        /// <summary>
        /// 设置 IO 操作超时时间(默 认的读写超时值均为 3000 毫秒)
        /// </summary>
        /// <param name="readTimeout">设置读操作超时值，单位毫秒</param>
        /// <param name="writeTimeout">设置写操作超时值，单位毫秒</param>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern uint D300CSetIOTimeout(int readTimeout,int writeTimeout);
        #endregion

        #region 错误码
        public static string GetErrorMess(uint errorValue)
        {
            string errorMess = "";
            switch (errorValue)
            {
                case 0x00000000: errorMess = "成功"; break;
                case 0x10000000: errorMess = "参数无效"; break;
                case 0x10000001: errorMess = "接收缓冲区太小"; break;
                case 0x10000002: errorMess = "参数为空"; break;
                case 0x10000003: errorMess = "参数格式错误"; break;
                case 0x10000004: errorMess = "参数长度错误"; break;
                case 0x10000005: errorMess = "系统不支持"; break;
                case 0x10000006: errorMess = "参数超出范围"; break;
                case 0x10000007: errorMess = "接收缓冲区太小"; break;
                case 0x10000008: errorMess = "参数太长"; break;
                case 0x10000009: errorMess = "打印机配置空"; break;
                case 0x1000000a: errorMess = "缓冲区太大"; break;
                case 0x1000000B: errorMess = "调用顺序错"; break;
                case 0x1000000c: errorMess = "没有找到相应的文件"; break;
                case 0x20000000: errorMess = "客户端一般错误"; break;
                case 0x28000000: errorMess = "内存分配失败"; break;
                case 0x28000001: errorMess = "内存分配失败"; break;
                case 0x28000002: errorMess = "内存分配失败"; break;
                case 0x28000003: errorMess = "内存分配失败"; break;
                case 0x28000004: errorMess = "内存分配失败"; break;
                case 0x28000005: errorMess = "TLS 超出索引范围"; break;
                case 0x28000006: errorMess = "报文校验错误"; break;
                case 0x28000007: errorMess = "作业为空"; break;
                case 0x28000008: errorMess = "创建 SOCKET 失败 "; break;
                case 0x28000009: errorMess = "SOCKET 连接失败"; break;
                case 0x28000010: errorMess = "SOCKET 发送数据失败"; break;
                case 0x28000011: errorMess = "SOCKET 接收数据失败 "; break;
                case 0x28000012: errorMess = "创建 USB 文件失败"; break;
                case 0x28000013: errorMess = "USB 写文件失败"; break;
                case 0x28000015: errorMess = "创建 SOCKET 失败"; break;
                case 0x28000016: errorMess = "SOCKET 连接失败"; break;
                case 0x28000017: errorMess = "SOCKET 发送数据失败"; break;
                case 0x28000018: errorMess = "SOCKET 接收数据失败"; break;
                case 0x28000019: errorMess = "打印机名称为空"; break;
                case 0x2800001a: errorMess = "打印的卡片为空"; break;
                case 0x2800001b: errorMess = "厂商请求失败"; break;
                case 0x2800001c: errorMess = "打印机未准备好"; break;
                case 0x2800001d: errorMess = "不支持的请求"; break;
                case 0x2800001e: errorMess = "打印机非空"; break;
                case 0x2800001f: errorMess = "UDP 请求失败"; break;
                case 0x28000020: errorMess = "UDP 请求超时"; break;
                case 0x28000021: errorMess = "HID 设备未找到 "; break;
                case 0x28000022: errorMess = "打印机未响应"; break;
                case 0x27000000: errorMess = "套打类错误 "; break;
                case 0x27000001: errorMess = "图形初始化失败"; break;
                case 0x27000002: errorMess = "不能在保护区绘制"; break;
                case 0x27000003: errorMess = "创建 QR 码失败 "; break;
                case 0x27000004: errorMess = "卡片尺寸不支持"; break;
                case 0x27000005: errorMess = "卡片类型不支持"; break;
                case 0x27000006: errorMess = "卡片尺寸已经设置 "; break;
                case 0x27000007: errorMess = "超过可打印区域"; break;
                case 0x30000000: errorMess = "未知错误"; break;
                case 0x30000001: errorMess = "SERVICE 未生效"; break;
                case 0x30000002: errorMess = "无效的格式"; break;
                case 0x30000003: errorMess = "没有找到指定的打印机"; break;
                case 0x30000004: errorMess = "没有找到指定的作业 "; break;
                case 0x30000005: errorMess = "指定的作业已经终止"; break;
                case 0x30000006: errorMess = "指定的作业已完成"; break;
                case 0x30000007: errorMess = "指定的作业正在打印"; break;
                case 0x30000008: errorMess = "无效的打印机名"; break;
                case 0x30000009: errorMess = "指定的作业无效"; break;
                case 0x3000000a: errorMess = "无效的型号"; break;
                case 0x3000000b: errorMess = "无效的连接串"; break;
                case 0x3000000c: errorMess = "名字重复"; break;
                case 0x3000000d: errorMess = "连接串重复"; break;
                case 0x3000000e: errorMess = "正在打印最后一张卡片"; break;
                case 0x3000000f: errorMess = "作业数量为零"; break;
                case 0x30000010: errorMess = "打印机离线 "; break;
                case 0x30000011: errorMess = "指定的打印作业正在排队 "; break;
                case 0x30000012: errorMess = "指定的作业已暂停"; break;
                case 0x29000001: errorMess = "读卡器打开失败"; break;
                case 0x29000002: errorMess = "读卡器读写失败"; break;
                case 0x29000003: errorMess = "读卡器库函数失败"; break;
                case 0x29000004: errorMess = "读卡器未打开"; break;
                case 0x29000005: errorMess = "读卡器内部有卡"; break;
                case 0x29000006: errorMess = "读卡器内部没有卡"; break;
                case 0x29000007: errorMess = "系统 API 出错 "; break;
                case 0x29000008: errorMess = "未加载 dcrf32.dll "; break;
                case 0x29000009: errorMess = "关闭读卡器失败 "; break;
                case 0x2900000a: errorMess = "打印机内部有卡"; break;
                default:
                    errorMess = "其他位置错误";
                    break;
            }
            return errorMess;
        }
        #endregion


        //#region 一体机接口
        ///// <summary>
        ///// 从卡盒移卡到彩色打印位
        ///// </summary>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOMoveCardToColorPrintFromCardBox();

        ///// <summary>
        ///// 从彩色打印位排卡
        ///// </summary>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOMoveCardToExitFromColorPrint();

        ///// <summary>
        ///// 从卡盒移卡到读卡位
        ///// </summary>
        ///// <param name="cardType">卡片类型 0：非接 1：接触式 2：磁条卡</param>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOMoveCardToReadCardFromCardBox(int cardType);

        ///// <summary>
        ///// 从读卡位移卡到彩色打印位
        ///// </summary>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOMoveCardToColorFromReadCard();

        ///// <summary>
        ///// 读取卡片位置
        ///// </summary>
        ///// <returns>0:打印机内部无卡 1:彩色打印位 2:读卡位 -1:读取失败</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOReadCardPosition();

        ///// <summary>
        ///// 读取打印机状态
        ///// 注意：
        ///// 判断第七个字节 rcv[6]
        ///// 0xFF 卡片位置状态：未知状态
        ///// 0x00 卡片位置状态：打印机内部无卡
        ///// 0x01 卡片位置状态：彩色打印位
        ///// 0x02 卡片位置状态：读卡器位
        ///// </summary>
        ///// <param name="rcv">数据接收区域,长度一般大于等于 40</param>
        ///// <param name="rcvLength">数据接收区域大小</param>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOReadStatus(byte[] rcv, int rcvLength);

        ///// <summary>
        ///// 打印机关联,该接口与 DSAIOReadStatus 同时使用。
        ///// 注意：
        ///// *相关数据计算方式
        ///// double t1=(rcv[11]<<8&0xFF00)+(rcv[10]&0xFF);当前环境温度：t1/100
        ///// double t2 = (rcv[15]<<8&0xFF00)+(rcv[14]&0xFF);当前印头温度：t2/100
        ///// if(rcv[39] == 0x00)"缓存满"
        ///// else if(rcv[39] == 0x01)缓存可以存储 1 面打印数据"
        ///// else if(rcv[39] == 0x02)"缓存可以存储 2 面打印数据"
        ///// */
        ///// </summary>
        ///// <param name="rcv">数据接收区域,长度一般大于等于 40</param>
        ///// <param name="rcvLength">数据接收区域大小</param>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOPrinterRelevancy(byte[] rcv, int rcvLength);

        ///// <summary>
        ///// 读取/写入卡片设置
        ///// 注意：
        ///// 读取操作时关键数据位含义：
        ///// if(rcv[10] == 0x00)
        ///// PVC
        ///// else if(rcv[10] == 0x01)
        ///// PET
        ///// else if(rcv[10] == 0x02)
        ///// PET-G
        ///// else if(rcv[10] == 0x03)
        ///// 卡片 1
        ///// else if(rcv[10] == 0x04)
        ///// 卡片 2
        ///// else if(rcv[10] == 0x05)
        ///// 卡片 3
        ///// if(rcv[14] == 0x00)
        ///// 标准卡前方出卡
        ///// else if(rcv[14] == 0x01)
        ///// 标准卡后方出卡
        ///// if(rcv[18] == 0x00)
        ///// 异常卡前方出卡
        ///// else if(rcv[18] == 0x01)
        ///// 异常卡后方出卡
        ///// if(rcv[22] == 0x00)
        ///// 送卡方式普通送卡
        ///// </summary>
        ///// <param name="writeOrRead">true 为写操作，false 为读操作</param>
        ///// <param name="rcv">数据接收区域,长度一般大于等于 40</param>
        ///// <param name="rcvLength">数据接收区域大小</param>
        ///// <param name="cardType">卡片类型
        ///// 0：PVC
        ///// 1：PET
        ///// 2：PET-G
        ///// 3：卡片 1
        ///// 4：卡片 2
        ///// 5：卡片 3</param>
        ///// <param name="standardExit">标准排卡方式 0：前方出卡 1：后方出卡</param>
        ///// <param name="errorExit">异常排卡方式 0：前方出卡 1：后方出卡</param>
        ///// <param name="setCardPos">:送卡方式 0-普通送卡</param>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(AIDdllName)]
        //public static extern int DSAIOCardSet(bool writeOrRead, byte[] rcv, int rcvLength, ushort cardType, ushort standardExit, ushort errorExit, ushort setCardPos);

        //#endregion
    }
}
