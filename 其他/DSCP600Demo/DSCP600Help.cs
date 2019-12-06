using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace DSCP600Demo
{
    public class DSCP600Help
    {
        private const string dllName = ".\\AIO\\DSCP600.dll";


        #region 连接打印机

        /// <summary>
        /// 枚举打印机
        /// </summary>
        /// <param name="printerType">1：USB 打印机；2：网络打印机；3：USB 打印机和网络打印机都枚举；</param>
        /// <returns>成功返回如下形式的字串：
        /// {“RtnCode”:0,
        /// ”NumberOfPrinters”:1,
        /// ”PrinterList”:”DS 7600@USB001”}
        /// 其中：
        /// RtnCode ：表示本次调用的错误码，因为是调用成功，所以值 为 0；
        /// NumberOfPrinters：表示枚举到的打印机数目，这里为 1 台；
        /// PrinterList：打印机列表，表示枚举到的所有打印机；若有多台打印机，
        /// 将以”\r\n”分割。；</returns>
        [DllImport(dllName)]
        public static extern string DS600EnumPrinter(long printerType);

        /// <summary>
        /// 打开打印机
        /// </summary>
        /// <param name="printerName">打印机名称</param>
        /// <returns>成功返回 0;则返回非 0，具体参见附录 1 错误码</returns>
        [DllImport(dllName)]
        public static extern long D300COpenPrinter(string printerName);

        /// <summary>
        /// 从打印机列表中得到打印机
        /// </summary>
        /// <param name="printerList">DS600EnumPrinter 函数返回的打印机列表；</param>
        /// <param name="index">指定要得到打印机信息中第几台的信息，第一台为0，最后一台为 DS600EnumPrinter 返回的 NumberOfPrinters 减 1。</param>
        /// <returns>如果 index 在 0 到 NumberOfPrinters-1 范围内，则返回对应的打印机名称；否则函数返回空串。</returns>
        [DllImport(dllName)]
        public static extern string DS600GetPrinterListItem(string printerList,long index);

        /// <summary>
        /// 关闭打印机
        /// </summary>
        [DllImport(dllName)]
        public static extern void DS600ClosePrinter();

        /// <summary>
        /// 设置IO操作超时时间
        /// </summary>
        /// <param name="readTimeout">设置读操作超时值，单位毫秒</param>
        /// <param name="writeTimeout">设置写操作超时值，单位毫秒</param>
        /// <returns>成功，返回0；</returns>
        [DllImport(dllName)]
        public static extern long DS600SetIOTimeout(long readTimeout, long writeTimeout);

        /// <summary>
        /// 释放字符串
        /// </summary>
        /// <param name="pString">相关返回字串信息的函数返回的字串(如 DS600EnumPrinter传出参数，DS600GetPrinterListItem 的返回值)</param>
        [DllImport(dllName)]
        public static extern void DS600FreeString(string pString);

        #endregion


        /// <summary>
        /// 从卡盒移卡到彩色打印位
        /// </summary>
        /// <returns>成功返回的数值大于 0；失败返回 0</returns>
        [DllImport(dllName)]
        public static extern int DSAIOMoveToColor();


        /// <summary>
        /// 排卡
        /// </summary>
        /// <returns></returns>
        [DllImport(dllName)]
        public static extern int DSAIOEjectCard();

        /// <summary>
        /// 从卡盒移卡到读卡位
        /// </summary>
        /// <param name="cardType">卡片类型 0：非接 1：接触式 2：磁条卡</param>
        /// <returns>成功返回的数值大于 0；失败返回 0</returns>
        [DllImport(dllName)]
        public static extern int DSAIOMoveToRead(int cardType);

        /// <summary>
        /// 从读卡位移卡到彩色打印位
        /// </summary>
        /// <returns>成功返回的数值大于 0；失败返回 0</returns>
        [DllImport(dllName)]
        public static extern int DSAIOMoveToColorFromRead();




        ///// <summary>
        ///// 从彩色打印位排卡
        ///// </summary>
        ///// <returns>成功返回的数值大于 0；失败返回 0</returns>
        //[DllImport(dllName)]
        //public static extern int DSAIOMoveCardToExitFromColorPrint();

        /// <summary>
        /// 读取卡片位置
        /// </summary>
        /// <returns>0:缺卡 1:D300C 打印位 2:D300RW 打印位 -1:读取失败</returns>
        [DllImport(dllName)]
        public static extern int DSAIOGetPosition();


        /// <summary>
        /// 读取打印机状态
        /// 注意：
        /// 判断第七个字节 rcv[6]
        /// 0xFF 卡片位置状态：未知状态
        /// 0x00 卡片位置状态：打印机内部无卡
        /// 0x01 卡片位置状态：彩色打印位
        /// 0x02 卡片位置状态：读卡器位
        /// </summary>
        /// <param name="rcv">数据接收区域,长度一般大于等于 40</param>
        /// <param name="rcvLength">数据接收区域大小</param>
        /// <returns>成功返回的数值大于 0；失败返回 0</returns>
        [DllImport(dllName)]
        public static extern int DSAIOGetStatus(byte[] rcv, int rcvLength);

        /// <summary>
        /// 写入排卡设置
        /// </summary>
        /// <param name="standardExit">排卡 0-前方出卡 1-后方出卡</param>
        /// <returns>0 成功，不为 0 失败</returns>
        [DllImport(dllName)]
        public static extern int DSAIOSetEjectPos(ushort standardExit);

        /// <summary>
        /// 读取排卡设置
        /// </summary>
        /// <param name="rcv">
        /// if(rcv[14] == 0x00)
        /// 前方出卡
        /// else if(rcv[14] == 0x01)
        /// 后方出卡</param>
        /// <param name="rcvLength">数据接收区域大小</param>
        /// <returns>0 成功，不为 0 失败</returns>
        [DllImport(dllName)]
        public static extern int DSAIOGetEjectPos(byte[] rcv, int rcvLength);


        /// <summary>
        /// 打印机关联,该接口与 DSAIOReadStatus 同时使用。
        /// 注意：
        /// *相关数据计算方式
        /// double t1=(rcv[11]<<8&0xFF00)+(rcv[10]&0xFF);当前环境温度：t1/100
        /// double t2 = (rcv[15]<<8&0xFF00)+(rcv[14]&0xFF);当前印头温度：t2/100
        /// if(rcv[39] == 0x00)"缓存满"
        /// else if(rcv[39] == 0x01)缓存可以存储 1 面打印数据"
        /// else if(rcv[39] == 0x02)"缓存可以存储 2 面打印数据"
        /// */
        /// </summary>
        /// <param name="rcv">数据接收区域,长度一般大于等于 40</param>
        /// <param name="rcvLength">数据接收区域大小</param>
        /// <returns>成功返回的数值大于 0；失败返回 0</returns>
        [DllImport(dllName)]
        public static extern int DSAIOGetCacheTemp(byte[] rcv, int rcvLength);

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
        //[DllImport(dllName)]
        //public static extern int DSAIOCardSet(bool writeOrRead, byte[] rcv, int rcvLength, ushort cardType, ushort standardExit, ushort errorExit, ushort setCardPos);




    }
}
