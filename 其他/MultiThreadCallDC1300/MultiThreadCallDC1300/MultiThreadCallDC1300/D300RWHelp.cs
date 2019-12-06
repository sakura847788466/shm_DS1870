using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MultiThreadCallDC1300
{
    public sealed class D300RWHelp
    {
        /// <summary>
        /// 动态库加载后调用此函数用于初始化等工作
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASInit")]
        public static extern UInt32 DASInit();

        /// <summary>
        /// 动态库卸载前调用此函数用于清理数据等工作
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASExit")]
        public static extern UInt32 DASExit();


        /// <summary>
        /// 枚举打印机
        /// </summary>
        /// <param name="PrinterConnectString">返回枚举到的打印机连接串</param>
        /// <param name="ConnStringlen">缓冲区长度，(出参)见《约定一》</param>
        /// <param name="PrinterType">打印机类型 1：仅 USB 打印机；2：仅网络打印机；3：所有打印机</param>
        /// <returns>成功返回 0；错误见错误码《附录 1》</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASEnumPrinter")]
        public static extern UInt32 DASEnumPrinter(byte[] PrinterConnectString, ref int ConnStringlen, [InAttribute()]int PrinterType);






        #region 套打函数
        /// <summary>
        /// 设置卡片尺寸
        /// 1、卡片宽度和高度设置成 CR80 实际大小 85.6*54mm；
        /// 2、设置成 54*85.6 时，为纵向卡片
        /// </summary>
        /// <param name="w">卡片宽度，单位 mm</param>
        /// <param name="h">卡片高度，单位 mm</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetCardSize")]
        public static extern UInt32 DASsetCardSize([InAttribute()]double w, [InAttribute()]double h);

        /// <summary>
        /// 设置卡片保护区，此区域内不擦除不打印
        /// </summary>
        /// <param name="left">左上角 X 坐标，单位 mm</param>
        /// <param name="top">左上角 Y 坐标，单位 mm</param>
        /// <param name="w">宽度，单位 mm</param>
        /// <param name="h">高度，单位 mm</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASaddProtectedRect")]
        public static extern UInt32 DASaddProtectedRect([InAttribute()]double left, [InAttribute()]double top, [InAttribute()]double w, [InAttribute()]double h); // 单位mm

        /// <summary>
        /// 设置字体，不设置则采用默认：0
        /// </summary>
        /// <param name="fontName">字体名称，匹配系统已安装的字体</param>
        /// <param name="size">字体大小</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetFont", CallingConvention = CallingConvention.StdCall)]
        public static extern UInt32 DASsetFont([InAttribute()]string fontName, [InAttribute()]double size);

        /// <summary>
        /// 设置文本画笔颜色，不设置则采用默认：黑色
        /// </summary>
        /// <param name="r">红色亮度</param>
        /// <param name="g">绿色亮度</param>
        /// <param name="b">蓝色亮度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetTextColor")]
        public static extern UInt32 DASsetTextColor([InAttribute()]byte r, [InAttribute()]byte g, [InAttribute()]byte b);

        /// <summary>
        /// 设置一维码、二维码画笔颜色，不设置则采用默认
        /// </summary>
        /// <param name="r">红色亮度</param>
        /// <param name="g">绿色亮度</param>
        /// <param name="b">蓝色亮度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetBarCodeColor")]
        public static extern UInt32 DASsetBarCodeColor([InAttribute()]byte r, [InAttribute()]byte g, [InAttribute()]byte b);

        /// <summary>
        /// 设置字体修饰
        /// </summary>
        /// <param name="isStrong">加粗设置 Ture：加粗;false：不加粗</param>
        /// <param name="isItalic">斜体设置 true：字体为斜体;false：字体不添加斜体</param>
        /// <param name="isUnderline">下划线设置 true：添加下划线;false：不添加下划线</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetTextDecorate")]
        public static extern UInt32 DASsetTextDecorate([InAttribute()]bool isStrong, [InAttribute()]bool isItalic, [InAttribute()]bool isUnderline);

        /// <summary>
        /// 设置文本方向
        /// </summary>
        /// <param name="isLandScape">)打印方向 true：横向;false：纵向</param>
        /// <param name="isReverseSequence">打印顺序 true：逆序打印;false：正序打印</param>
        /// <param name="isAutoLineFeed">自动换行设置 true：自动换行;false：截断</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetTextDirection")]
        public static extern UInt32 DASsetTextDirection([InAttribute()]bool isLandScape, [InAttribute()]bool isReverseSequence, [InAttribute()]bool isAutoLineFeed);
        /// <summary>
        /// 设置行间距、字间距，单位 mm
        /// </summary>
        /// <param name="LineSpacing">行间距，单位 mm</param>
        /// <param name="CharSpacing">字间距，单位 mm</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetSpacing")]
        public static extern UInt32 DASsetSpacing([InAttribute()]double LineSpacing, [InAttribute()]double CharSpacing);
        /// <summary>
        /// 打印文本块,单位mm
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="gbkText">文本快，GBK 编码</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawText")]
        public static extern UInt32 DASdrawText([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]string gbkText); // 单位mm

        /// <summary>
        /// 打印文本块并旋转,单位mm
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="gbkText">文本快，GBK 编码</param>
        /// <param name="ratition">旋转角度  0：0 度；1：90 度；2：180 度；3：270 度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawTextForRotation")]
        public static extern UInt32 DASdrawTextForRotation([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width,
            [InAttribute()]double height, [InAttribute()]string gbkText, [InAttribute()]int ratition);


        /// <summary>
        /// 绘制二维码
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="data">文本块，GBK 编码</param>
        /// <param name="errLev">0 = 容错率(7%)
        /// 1 = 容错率(15%)
        /// 2 = 容错率(25%)
        /// 3 = 容错率(30%)</param>
        /// <param name="nVersion">生成 QR 码时所需要的版本号</param>
        /// <param name="isAutoFill">自动填充设置 true</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawQRbyVersion")]
        public static extern UInt32 DASdrawQRbyVersion([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]string data, [InAttribute()]int errLev, [InAttribute()]int nVersion, [InAttribute()]bool isAutoFill);// 单位mm

        /// <summary>
        /// 绘制二维码并旋转
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="data">文本块，GBK 编码</param>
        /// <param name="errLev">0 = 容错率(7%)
        /// 1 = 容错率(15%)
        /// 2 = 容错率(25%)
        /// 3 = 容错率(30%)</param>
        /// <param name="nVersion">生成 QR 码时所需要的版本号</param>
        /// <param name="isAutoFill">自动填充设置 true</param>
        /// <param name="rotation">角度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawQRForRotation")]
        public static extern UInt32 DASdrawQRForRotation([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]string data, [InAttribute()]int errLev, [InAttribute()]int nVersion, [InAttribute()]bool isAutoFill, [InAttribute()]int rotation);// 单位mm


        /// <summary>
        /// 设置仅擦不打印区域，单位 mm
        /// </summary>
        /// <param name="left">左上角 x 坐标，单位 mm</param>
        /// <param name="top">左上角 y 坐标，单位 mm</param>
        /// <param name="w">宽度，单位 mm</param>
        /// <param name="h">高度，单位 mm</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASaddNeedEraseRect")]
        public static extern UInt32 DASaddNeedEraseRect([InAttribute()]double left, [InAttribute()]double top, [InAttribute()]double w, [InAttribute()]double h);

        /// <summary>
        /// 绘制图片
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="imagefile">图片文件路径</param>
        /// <param name="isPastePhoto">true：贴图 false：白色透明，灰度为 255 的白色</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawImage")]
        public static extern UInt32 DASdrawImage([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]string imagefile, [InAttribute()]bool isPastePhoto); // 单位mm

        /// <summary>
        /// 绘制图片并旋转
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="imagefile">图片文件路径</param>
        /// <param name="isPastePhoto">true：贴图 false：白色透明，灰度为 255 的白色</param>
        /// <param name="rotation">旋转度数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawImageForRotation")]
        public static extern UInt32 DASdrawImageForRotation([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]string imagefile, [InAttribute()]bool isPastePhoto, [InAttribute()]int rotation); // 单位mm


        /*
        barcodeType: bar code type:
            0 = code 39 (3 of 9 alphanumeric)
            1 = 2/5 interleave (numeric, even, >=5 )
            2 = UPC – E (numeric 7 digits encoded)
            3. = EAN8 (numeric 7 digits encoded) 
            4. = EAN13 (numeric 12 digits encoded)
            5. = UPC – A (numeric 12 digits encoded)
            6. = 93 code
            7 = code 128 C w/o check digits (numeric only, even number printed)
            8 = code 128 B w/o check digits (numeric)
        */
        /// <summary>
        /// 绘制一维码
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="barcodeType">条码类型
        /// 0 = 39 码
        /// 1 = 交叉 25 码
        /// 2 = UPC-E 码
        /// 3 = EAN8 码
        /// 4 = EAN13 码
        /// 5 = UPC-A 码
        /// 6 = 93 码
        /// 7 = code 128 C 码
        /// 8 = code 128 B 码</param>
        /// <param name="data">文本块,GBK 编码</param>
        /// <param name="isText">true：显示文本 false：不显示文本</param>
        /// <param name="isUnderText">true：文字显示在条码下方 false：文字不显示在条码下方</param>
        /// <param name="barcodeMultiplier">放大倍数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawBarCode")]
        public static extern UInt32 DASdrawBarCode([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]int barcodeType, [InAttribute()]string data, [InAttribute()]bool isText, [InAttribute()]bool isUnderText, [InAttribute()]int barcodeMultiplier);

        /// <summary>
        /// 绘制一维码并旋转
        /// </summary>
        /// <param name="x">左上角 x 坐标，单位 mm</param>
        /// <param name="y">左上角 y 坐标，单位 mm</param>
        /// <param name="width">宽度，单位 mm</param>
        /// <param name="height">高度，单位 mm</param>
        /// <param name="barcodeType">条码类型
        /// 0 = 39 码
        /// 1 = 交叉 25 码
        /// 2 = UPC-E 码
        /// 3 = EAN8 码
        /// 4 = EAN13 码
        /// 5 = UPC-A 码
        /// 6 = 93 码
        /// 7 = code 128 C 码
        /// 8 = code 128 B 码</param>
        /// <param name="data">文本块,GBK 编码</param>
        /// <param name="isText">true：显示文本 false：不显示文本</param>
        /// <param name="isUnderText">true：文字显示在条码下方 false：文字不显示在条码下方</param>
        /// <param name="barcodeMultiplier">放大倍数</param>
        /// <param name="rotation">旋转度数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawBarCodeForRotation")]
        public static extern UInt32 DASdrawBarCodeForRotation([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]int barcodeType, [InAttribute()]string data, [InAttribute()]bool isText, [InAttribute()]bool isUnderText, [InAttribute()]int barcodeMultiplier, [InAttribute()]int rotation);

        #endregion


        //////////////////////////////////////////////////////////////////////////
        //errLev: 
        //  0 = Error Rate (7%)
        //	1 = Error Rate (15%)
        //	2 = Error Rate (25%)
        //	3 = Error Rate (30%)
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASdrawQR")]
        public static extern UInt32 DASdrawQR([InAttribute()]double x, [InAttribute()]double y, [InAttribute()]double width, [InAttribute()]double height, [InAttribute()]string data, [InAttribute()]int errLev, [InAttribute()]bool isAutoFill);// 单位mm



        /// <summary>
        /// 生成打印数据
        /// </summary>
        /// <param name="isFrontSide"></param>
        /// <param name="AutoGenerateMask">擦除位置 true：根据绘图内容擦除指定区域 false：全擦</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASBuildGraphicsData")]
        public static extern UInt32 DASBuildGraphicsData([InAttribute()]bool isFrontSide, [InAttribute()]bool AutoGenerateMask);

        /// <summary>
        /// 生成打印数据
        /// </summary>
        /// <param name="isFrontSide"></param>
        /// <param name="AutoGenerateMask">擦除位置 true：根据绘图内容擦除指定区域 false：全擦</param>
        /// <param name="rotation">旋转角度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASBuildGraphicsDataForRotation")]
        public static extern UInt32 DASBuildGraphicsDataForRotation([InAttribute()]bool isFrontSide, [InAttribute()]bool AutoGenerateMask,int rotation);


        /// <summary>
        /// 设置指定的打印机
        /// </summary>
        /// <param name="PrinterName">打印机的名称</param>
        /// <param name="PrinterType">打印机类型，例：D300RW</param>
        /// <returns>成功返回 0；错误见错误码《附录 1》</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetPrinterName")]
        public static extern UInt32 DASSetPrinterName([InAttribute()]string PrinterName, [InAttribute()]string PrinterType);

        /// <summary>
        /// 设置黑色打印方式
        /// </summary>
        /// <param name="method">黑色打印方式 0：代表阈值；1：误差扩散(默认)</param>
        /// <returns>成功返回 0；错误见错误码《附录 1》</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetBlackPrintMethod")]
        public static extern UInt32 DASSetBlackPrintMethod([InAttribute()]int method);

        //0：代表二值 1：误差扩散
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetRibbon")]
        public static extern UInt32 DASSetRibbon([InAttribute()]int method);

        /// <summary>
        /// 设置打印图片  为了提高打印效果，图片的宽高比应接近于卡片的宽高比(85.6*54mm)
        /// 取值范围1～4，D300RW 默认4
        /// </summary>
        /// <param name="Side"></param>
        /// <param name="BmpFile">打印的图片文件</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetGraphicDataByFile")]
        public static extern UInt32 DASSetGraphicDataByFile([InAttribute()]int Side, [InAttribute()]string BmpFile);

        /// <summary>
        /// 设置擦除图片 0：正面  1：反面
        /// </summary>
        /// <param name="BmpFile">擦除图片文件,格式为 1016X648(像素点)单色 bmp 文件</param>
        /// <param name="Eraseflag">1：不擦除;0：擦除</param>
        /// <returns>成功返回 0；错误见错误码《附录 1》</returns>

        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetEraseDataByFile")]
        public static extern UInt32 DASSetEraseDataByFile([InAttribute()]string BmpFile, [InAttribute()]int Eraseflag);

        //1:不擦除 0：擦除
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetCopies")]
        public static extern UInt32 DASSetCopies([InAttribute()]int nCopies);
        /// <summary>
        /// 设置打印阈值  取值范围1～65535
        /// </summary>
        /// <param name="threshold">阈值范围，取值范围 0~255，默认 128</param>
        /// <returns></returns>

        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetNthreshold")]
        public static extern UInt32 DASSetNthreshold([InAttribute()]int threshold);

        /// <summary>
        /// 设置打印方向 取值范围0～255
        /// </summary>
        /// <param name="Print_Direction">0：纵向;1：横向(默认)</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetPrintDirection")]
        public static extern UInt32 DASSetPrintDirection([InAttribute()]int Print_Direction);
        /// <summary>
        /// 打印卡片,将已经绘制好的内存区域送到打印机；
        /// </summary>
        /// <returns>返回 0 表示提交打印机成功</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASPrintCard")]
        public static extern UInt32 DASPrintCard();




        /// <summary>
        /// 设置打印速度
        /// </summary>
        /// <param name="Para">打印速度数值,取值范围：1~20 默认 10</param>
        /// <returns>成功返回 0；错误见错误码《附录 1》</returns>

        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetPrintSpeed")]
        public static extern UInt32 DASSetPrintSpeed([InAttribute()]int Para);
        /// <summary>
        /// 设置卡片对比度   取值范围0～20默认10
        /// </summary>
        /// <param name="Para">卡片对比度数值,取值范围：1~20 默认 10</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetCardContrast")]
        public static extern UInt32 DASSetCardContrast([InAttribute()]int Para);
        /// <summary>
        /// 设置打印温度 取值范围0～20默认10
        /// </summary>
        /// <param name="Para">打印温度数值,取值范围：1~20 默认 10</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetPrintTemperature")]
        public static extern UInt32 DASSetPrintTemperature([InAttribute()]int Para);
        /// <summary>
        /// 设置擦除温度 取值范围0～20默认10
        /// </summary>
        /// <param name="temprature">擦除温度数值,取值范围：1~20 默认 10</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetEraseTemperature")]
        public static extern UInt32 DASSetEraseTemperature([InAttribute()]int temprature);

        #region 杂项函数
        /// <summary>
        /// 擦除卡片
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASEraseCard")]
        public static extern UInt32 DASEraseCard();
        /// <summary>
        /// 清洁打印机
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASCleanPrinter")]
        public static extern UInt32 DASCleanPrinter();

        /// <summary>
        /// 打印技术测试卡
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASPrintTechnicalTestCard")]
        public static extern UInt32 DASPrintTechnicalTestCard();


        /// <summary>
        /// 打印测试卡
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASPrintTestCard")]
        public static extern UInt32 DASPrintTestCard();

        /// <summary>
        /// 获取 SDK 版本
        /// </summary>
        /// <param name="Version">版本号</param>
        /// <param name="length">版本号长度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetSDKVersion")]
        public static extern UInt32 DASGetSDKVersion(byte[] Version, ref int length);

        /// <summary>
        /// 设置打印头方向偏移，打印机重启后生效
        /// </summary>
        /// <param name="nOffset">打印头方向偏移量 范围：-20~20</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetXoffset")]
        public static extern UInt32 DASsetXoffset([InAttribute()]int nOffset);

        /// <summary>
        /// 设置进卡方向偏移，打印机重启后生效
        /// </summary>
        /// <param name="nOffset">进卡方向偏移量 范围-8~8</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetYoffset")]
        public static extern UInt32 DASsetYoffset([InAttribute()]int nOffset);

        /// <summary>
        /// 设置打印浓度，打印机重启后生效
        /// </summary>
        /// <param name="nChrome">打印浓度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASsetPrintChroma")]
        public static extern UInt32 DASsetPrintChroma([InAttribute()]int nChrome);





        #endregion



        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASInitPrinter")]
        public static extern UInt32 DASInitPrinter([InAttribute()]int Option);



        /// <summary>
        /// 打印机卡片设置
        /// </summary>
        /// <param name="CardType">卡片类型
        /// 0 = mblack ：三菱黑 Mitsubishi black(默认)
        /// 1 = mblue ：三菱蓝 Mitsubishi blue
        /// 2 = rblack ：薄卡 This card
        /// 90 = custom1 ：自定义 1 Custom 1
        /// 91 = custom2 ：自定义 2 Custom 2
        /// 92 = custom3 ：自定义 3 Custom 3</param>
        /// <param name="FrontDecurlStep">/*--正面展平步数*/</param>
        /// <param name="BackDecurlStep">/*--背面展平步数*/</param>
        /// <param name="StandardCardExitPositon">/*--标准出卡位置0-接收盒，1-手动*/</param>
        /// <param name="ErrorCardExitPositon"> /*--故障出卡位置*/</param>
        /// <param name="SetCardPositon">/* --设置进卡位置0-传送盒，1-手动，2-自动*//param>
        /// <param name="CardEjectSide">/*--出卡时卡面方向*/</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DAS_CardSet")]
        public static extern UInt32 DAS_CardSet
        (
            [InAttribute()]	int CardType,
            [InAttribute()]	int FrontDecurlStep,
            [InAttribute()]	int BackDecurlStep,
            [InAttribute()]	int StandardCardExitPositon,
            [InAttribute()]	int ErrorCardExitPositon,
            [InAttribute()]	int SetCardPositon,
            [InAttribute()]	int CardEjectSide
        );





        #region 获取打印机状态及其相关辅助函数



        /// <summary>
        /// 获取打印机状态
        /// </summary>
        /// <param name="status">)8 字节整数，将该整数传入辅助函数获取相关信息</param>
        /// <returns>1：风扇开启；0：风扇关闭；</returns>

        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASFetchPrinterStatus")]
        public static extern UInt32 DASFetchPrinterStatus(out UInt64 status);

        /// <summary>
        /// 获取错误号
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns>0、就绪；
        ///	1、缺卡错；
        ///	2、卡卡错；
        ///	3、归位错；
        ///	4、译码错；
        ///	5、卡片延时；
        ///	6、前盖打开错；
        ///	7、出卡错；
        ///	8、印头高温错；
        ///	9、印头低温错；
        ///	10、印头传感器错；
        ///	11、传感器错；
        ///	12、Flash错;</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterStatus_ErrorNo")]
        public static extern UInt32 DASGetPrinterStatus_ErrorNo([InAttribute()] UInt64 status);

        /// <summary>
        /// 获取进卡方式
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns> 0—卡盒装卡，1—手动装卡，2—自动装卡；</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetFeedCardMode")]
        public static extern UInt32 DASGetFeedCardMode([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取清洁状态
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns>0—不需清洁，1—建议清洁，2—必须清洁；</returns> 
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetCleaningStatus")]
        public static extern UInt32 DASGetCleaningStatus([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取风扇状态
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns> 1—风扇开启，0—风扇关闭；</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetFanStatus")]
        public static extern UInt32 DASGetFanStatus([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取卡盒状态
        /// </summary>
        /// <param name="status">)8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns>1—卡盒缺卡，0—卡盒有卡；</returns> 
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterStatus_CardBoxStatus")]
        public static extern UInt32 DASGetPrinterStatus_CardBoxStatus([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取前盖状态
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns> 1—前盖打开，0—前盖闭合；</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterStatus_FrontCoverStatus")]
        public static extern UInt32 DASGetPrinterStatus_FrontCoverStatus([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取缓冲区状态
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns> 2--接受缓存满，1—接收缓存空，0—接收缓存不满不空</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetRecvBufferStatus")]
        public static extern UInt32 DASGetRecvBufferStatus([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取忙状态
        /// </summary>
        /// <param name="status">8 字节整数，DASFetchPrinterStatus 返回的 8 字节整数</param>
        /// <returns> 1—打印机忙，  0—打印机空闲</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetBusyStatus")]
        public static extern UInt32 DASGetBusyStatus([InAttribute()]UInt64 status);

        /// <summary>
        /// 获取装卡模式
        /// </summary>
        /// <param name="Pattern">装卡模式 0：自动模式;1：指令模式</param>
        /// <returns>成功返回 0；</returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetFeedCardPattern")]
        public static extern UInt32 DASGetFeedCardPattern(out int Pattern);

        /// <summary>
        /// 设置装卡模式
        /// </summary>
        /// <param name="Pattern">装卡模式0：自动模式;1：指令模式</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetFeedCardPattern")]
        public static extern UInt32 DASSetFeedCardPattern(int Pattern);

        /// <summary>
        /// 获取打印机序列号
        /// </summary>
        /// <param name="SerialNumber">打印机序列号</param>
        /// <param name="len">缓存区长度，(出参)详见《约定一》</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterSerialNumber")]
        public static extern UInt32 DASGetPrinterSerialNumber(byte[] SerialNumber, ref int len);

        /// <summary>
        /// 获取打印头序列号
        /// </summary>
        /// <param name="SerialNumber">返回打印机序列号</param>
        /// <param name="len">缓存区长度，(出参)详见《约定一》</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterHeadSerialNumber")]
        public static extern UInt32 DASGetPrinterHeadSerialNumber(byte[] SerialNumber, ref int len);

        /// <summary>
        /// 获取用户区数据
        /// </summary>
        /// <param name="UserData">返回打印机序列号</param>
        /// <param name="len">缓存区长度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterUserData")]
        public static extern UInt32 DASGetPrinterUserData(byte[] UserData, ref int len);

        /// <summary>
        /// 获取卡片位置
        /// </summary>
        /// <param name="CardPos">卡片位置
        /// bit0：sens1 状态，1--有卡，0--没卡；
        /// bit1：sens2 状态，1--闭合，0--开盖；
        /// bit2：sens3 状态，1--有卡，0--没卡；
        /// bit3：sens4 状态，1--打印头未归位，0--打印头已归位；
        /// bit4：sens5 状态，1--卡盒有卡，0--卡盒没卡；
        /// bit5~7：预留；</param>
        /// <param name="len">缓存区长度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrinterCardPos", CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern UInt32 DASGetPrinterCardPos(byte[] CardPos, ref int len);

        /// <summary>
        /// 获取打印头温度
        /// </summary>
        /// <param name="Temperature">打印头温度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrtHeadTemperature")]
        public static extern UInt32 DASGetPrtHeadTemperature(out int Temperature);


        /// <summary>
        /// 获取装卡次数
        /// </summary>
        /// <param name="PrtCardTotal">装卡次数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetLoadCardTotal")]
        public static extern UInt32 DASGetLoadCardTotal(out int PrtCardTotal);

        /// <summary>
        /// 获取卡片打印总数
        /// </summary>
        /// <param name="PrtCardTotal">卡片打印总数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetPrtCardTotal")]
        public static extern UInt32 DASGetPrtCardTotal(out int PrtCardTotal);

        /// <summary>
        /// 获取下次清洁前可打印次数
        /// </summary>
        /// <param name="CanPrintTotalPreClean">下次清洁前可打印次数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASCanPrintTotalPreClean")]
        public static extern UInt32 DASCanPrintTotalPreClean(out int CanPrintTotalPreClean);

        /// <summary>
        /// 获取清洁总数
        /// </summary>
        /// <param name="CleanTotal">卡片清洁总数</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASCleanTotal")]
        public static extern UInt32 DASCleanTotal(out int CleanTotal);

        /// <summary>
        /// 装卡指令
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetManualCard")]
        public static extern UInt32 DASSetManualCard();

        /// <summary>
        /// 获取打印机运行信息
        /// </summary>
        /// <param name="InfoType">打印机信息
        /// infoType = 1，获取打印机机型
        /// infoType = 2，获取打印机序列号
        /// infoType = 3，获取打印机版本号
        /// infoType = 4，获取打印头更换次数
        /// infoType = 5，获取打印头序列号
        /// infoType = 6，获取当前打印头最大清洁插卡数
        /// infoType = 7，获取当前打印头插卡总数
        /// infoType = 8，获取当前打印头清洁次数
        /// infoType = 9，获取当前机器最大清洁插卡数
        /// infoType = 10，获取当前机器插卡
        /// infoType = 11，获取当前机器清洁次数</param>
        /// <param name="RunningInfoString">运行信息</param>
        /// <param name="Infolen">长度</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASGetRunningInfo")]
        public static extern UInt32 DASGetRunningInfo([InAttribute()]int InfoType, byte[] RunningInfoString, ref int Infolen);


        /// <summary>
        /// 重启打印机
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASRebootPrinter")]
        public static extern UInt32 DASRebootPrinter();

        /// <summary>
        /// 设置用户数据区
        /// </summary>
        /// <param name="FeederFlag">用户设置的数据</param>
        /// <param name="length">用户设置的数据长度，该长度最长为 50 个字节</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetUserData")]
        public static extern UInt32 DASSetUserData(byte[] FeederFlag, int length);

        /// <summary>
        /// 设置卡盒配置与进卡方向
        /// </summary>
        /// <param name="FeederFlag">卡盒配置 0：移除卡盒;1：装配卡盒</param>
        /// <param name="OutCardDir">进卡方向 0：前出卡;1：后出卡</param>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASSetCardBoxEjectCard")]
        public static extern UInt32 DASSetCardBoxEjectCard([InAttribute()]int FeederFlag, [InAttribute()]int OutCardDir);

        /// <summary>
        /// 排出卡片
        /// </summary>
        /// <returns></returns>
        [DllImport("DS_iomem_suv.dll", EntryPoint = "DASRejectCard")]
        public static extern UInt32 DASRejectCard();

        #endregion



        #region 转换函数

        public static string ToErrorString(UInt32 error)
        {
            string value = "";
            switch (error)
            {
                case 0: value = ""; break;
                case 0X10000000: value = "参数无效"; break;
                case 0X10000001: value = "接收缓冲区太小"; break;
                case 0X10000002: value = "参数为空"; break;
                case 0X10000003: value = "参数格式错误"; break;
                case 0X10000004: value = "参数长度错误"; break;
                case 0X10000005: value = "系统不支持"; break;
                case 0X10000006: value = "参数超出范围"; break;
                case 0X10000007: value = "接收缓冲区太小 "; break;
                case 0X10000008: value = "参数太长"; break;
                case 0X10000009: value = "打印机配置空"; break;
                case 0X1000000a: value = "缓冲区太大"; break;
                case 0X1000000b: value = "调用顺序错 "; break;
                case 0X1000000c: value = "没有找到相应的文件"; break;
                case 0X20000000: value = "客户端一般错误  "; break;
                case 0X28000000: 
                case 0X28000001: 
                case 0X28000002: 
                case 0X28000003: 
                case 0X28000004: value = "内存分配失败 "; break;
                case 0X28000005: value = "TLS 超出索引范围  "; break;
                case 0X28000006: value = "报文校验错误"; break;
                case 0X28000007: value = "作业为空  "; break;
                case 0X28000008: value = "创建 SOCKET 失败"; break;
                case 0X28000009: value = "SOCKET 连接失败  "; break;
                case 0X28000010: value = "SOCKET 发送数据失败"; break;
                case 0X28000011: value = "SOCKET 接收数据失败 "; break;
                case 0X28000012: value = "创建 USB 文件失败"; break;
                case 0X28000013: value = "USB 写文件失败 "; break;
                case 0X28000015: value = "创建 SOCKET 失败 "; break;
                case 0X28000016: value = "SOCKET 连接失败 "; break;
                case 0X28000017: value = "SOCKET 发送数据失败 "; break;
                case 0X28000018: value = "SOCKET 接收数据失败 "; break;
                case 0X28000019: value = "打印机名称为空 "; break;
                case 0X2800001a: value = "打印的卡片为空 "; break;
                case 0X2800001b: value = "厂商请求失败 "; break;
                case 0X2800001c: value = "打印机未准备好"; break;
                case 0X2800001d: value = "不支持的请求 "; break;
                case 0X2800001e: value = "打印机非空"; break;
                case 0X2800001f: value = "UDP 请求失败"; break;
                case 0X28000020: value = "UDP 请求超时 "; break;
                case 0X28000021: value = "没有找到 HID 设备"; break;
                case 0X28000022: value = "打印机无响应"; break;
                case 0X27000000: value = "套打类错误 "; break;
                case 0X27000001: value = "图形初始化失败"; break;
                case 0X27000002: value = "不能在保护区绘制"; break;
                case 0X27000003: value = "创建 QR 码失败 "; break;
                case 0X27000004: value = "卡片尺寸不支持"; break;
                case 0X27000005: value = "卡片类型不支持"; break;
                case 0X27000006: value = "卡片尺寸已经设置 "; break;
                case 0X27000007: value = "超过可打印区域 "; break;
                default:
                    value = "未知错误";
                    break;
            }
            return value;
        }


        /// <summary>
        /// 转为打印机状态错误
        /// </summary>
        /// <param name="status"></param>
        /// <returns></returns>
        public static string ToPrinterStatusErrorString(uint status)
        {
            string value = "";
            switch (status)
            {
                case 0: value = "就绪"; break;
                case 1: value = "缺卡错"; break;
                case 2: value = "卡卡错"; break;
                case 3: value = "归位错"; break;
                case 4: value = "译码错"; break;
                case 5: value = "卡片延时"; break;
                case 6: value = "前盖打开错"; break;
                case 7: value = "出卡错"; break;
                case 8: value = "印头高温错"; break;
                case 9: value = "印头低温错"; break;
                case 10: value = "印头传感器错"; break;
                case 11: value = "Flash错"; break;
                default:
                    value = "其他未知错误";
                    break;
            }
            return value;
        }

        /// <summary>
        /// 转为进卡模式
        /// </summary>
        /// <param name="feedCardMode">进卡模式值</param>
        /// <returns></returns>
        public static string ToFeedCardModeString(uint feedCardMode)
        {
            string mode = "";
            switch (feedCardMode)
            {
                case 0: mode = "卡盒装卡"; break;
                case 1: mode = "手动装卡"; break;
                case 2: mode = "自动装卡"; break;
                default:
                     mode = "未知模式"; 
                    break;
            }
            return mode;
        }

        /// <summary>
        /// 转换清洁状态
        /// </summary>
        /// <param name="cleaningStatus"></param>
        /// <returns></returns>
        public static string ToCleaningStatusString(uint cleaningStatus)
        {
            string status = "";
            switch (cleaningStatus)
            {
                case 0: status = "不需清洁"; break;
                case 1: status = "建议清洁"; break;
                case 2: status = "必须清洁"; break;
                default:
                    status = "未知清洁状态"; 
                    break;
            }
            return status;
        }

        /// <summary>
        /// 转换风扇状态
        /// </summary>
        /// <param name="ganStatus"></param>
        /// <returns></returns>
        public static string ToFanStatusString(uint ganStatus)
        {
            string status = "";
            switch (ganStatus)
            {
                case 0: status = "风扇关闭"; break;
                case 1: status = "风扇开启"; break;
                default:
                    status = "未知风扇状态"; 
                    break;
            }
            return status;
        }
        /// <summary>
        /// 转换卡盒状态
        /// </summary>
        /// <param name="cardBoxStatus"></param>
        /// <returns></returns>
        public static string ToPrinterStatus_CardBoxStatusString(uint cardBoxStatus)
        {
            string status = "";
            switch (cardBoxStatus)
            {
                case 0: status = "卡盒有卡"; break;
                case 1: status = "卡盒缺卡"; break;
                default:
                    status = "未知卡盒状态"; 
                    break;
            }
            return status;
        }

        /// <summary>
        /// 转换为前盖状态
        /// </summary>
        /// <param name="frontCoverStatus"></param>
        /// <returns></returns>
        public static string ToGetPrinterStatus_FrontCoverStatusString(uint frontCoverStatus)
        {
            string status = "";
            switch (frontCoverStatus)
            {
                case 0: status = "前盖闭合"; break;
                case 1: status = "前盖打开"; break;
                default:
                    status = "未知前盖状态"; 
                    break;
            }
            return status;
        }

        /// <summary>
        /// 转换接收缓冲区状态
        /// </summary>
        /// <param name="recvBufferStatus"></param>
        /// <returns></returns>
        public static string ToRecvBufferStatusString(uint recvBufferStatus)
        {
            string status = "";
            switch (recvBufferStatus)
            {
                case 0: status = "接收缓存不满"; break;
                case 1: status = "接收缓存空"; break;
                case 2: status = "接收缓存满"; break;
                default:
                    status = "未知接收缓存状态"; 
                    break;
            }
            return status;
        }

        /// <summary>
        /// 转换打印机忙状态
        /// </summary>
        /// <param name="busyStatus"></param>
        /// <returns></returns>
        public static string ToBusyStatusString(uint busyStatus)
        {
            string status = "";
            switch (busyStatus)
            {
                case 0: status = "打印机空闲"; break;
                case 1: status = "打印机忙"; break;
                default:
                    status = "未知打印机忙状态"; 
                    break;
            }
            return status;
        }

        /// <summary>
        /// 转换装卡模式
        /// </summary>
        /// <param name="feedCardPattern"></param>
        /// <returns></returns>
        public static string ToFeedCardPatternString(int feedCardPattern)
        {
            string status = "";
            switch (feedCardPattern)
            {
                case 0: status = "自动模式"; break;
                case 1: status = "指令模式"; break;
                default:
                    status = "未知装卡模式"; 
                    break;
            }
            return status;
        }
        #endregion
    }
}
