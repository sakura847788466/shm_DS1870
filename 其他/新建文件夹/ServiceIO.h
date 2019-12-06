#pragma once
#ifndef  _SERVICE_H_
#define  _SERVICE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
	void __stdcall  DASInit();
	void __stdcall  DASExit();

	//出参：0 自动模式  1 手动模式
	uint32_t __stdcall  DASGetFeedCardPattern(int *Pattern);
	//入参：0 自动模式  1 手动模式
	uint32_t __stdcall  DASSetFeedCardPattern(int Pattern);
	uint32_t __stdcall  DASGetPrinterSerialNumber(unsigned char *SN,int *length);
	uint32_t __stdcall  DASGetPrinterHeadSerialNumber(unsigned char *SN,int *length);
	uint32_t __stdcall  DASGetPrinterUserData(unsigned char *UserData,int *length);
	/*
	CardPos：卡片位置
	bit0 : sens1状态，1—有卡，0—没卡；
	bit1 : sens2状态，1—闭合，0—开盖；
	bit2 : sens3状态，1—有卡，0—没卡；
	bit3 : sens4状态，0—印头已归位，1—印头未归位；
	bit4 : sens5状态，1—卡盒有卡，0—卡盒没卡；
	bit5~7:预留；
	*/
	uint32_t __stdcall  DASGetPrinterCardPos(unsigned char *CardPos,int *length);
	uint32_t __stdcall  DASGetPrtHeadTemperature(int *Temperature);
	uint32_t __stdcall  DASGetLoadCardTotal(int *LoadCardTotal);
	uint32_t __stdcall  DASGetPrtCardTotal(int *PrtCardTotal);
	uint32_t __stdcall  DASCanPrintTotalPreClean(int *CanPrintTotalPreClean);
	uint32_t __stdcall  DASCleanTotal(int *CleanTotal);

	//set manual FeedCard
	uint32_t __stdcall  DASSetManualCard();
	/*
	4、增加读取机器运行信息的指令：
	n = 1，获取打印机机型；
	n = 2，获取打印机序列号；
	n = 3，获取打印机版本号；
	n = 4，获取打印机印头更换次数；
	n = 5，获取打印机印头ID；
	n = 6，获取当前印头最大清洁插卡数；
	n = 7，获取当前印头插卡总数；
	n = 8，获取当前印头清洁次数；
	n = 9，获取当前机器最大清洁插卡数；
	n = 10，获取当前机器插卡；
	n = 11，获取当前机器清洁次数；
	*/
	uint32_t __stdcall  DASGetRunningInfo(int p_infoType,unsigned char *p_acRecv,int *Recvedlen);
	uint32_t __stdcall  DASRebootPrinter();
	uint32_t __stdcall  DASSetUserData(unsigned char *UserData,int length);

	/*
	功能： 设置卡盒、出卡方向
	FeederFlag:  0---移除卡盒，1---装配卡盒；
	OutCardDir： 0---前出卡，1---后出卡；
	备注：设置成后出卡时，卡盒应相应设成移除状态；
	*/
	uint32_t __stdcall  DASSetCardBoxEjectCard(int FeederFlag ,int OutCardDir);
	uint32_t __stdcall  DASRejectCard();

	/*
	功能： 打印机清除打印缓存，
	参数：
	* n=0:清除发送缓冲，
	* n=1:清除接收缓冲，
	* n= 2:清除接收发送缓冲；
	*/
	uint32_t __stdcall   DASInitPrinter(int Option);

	/*范围20~-20*/
	uint32_t __stdcall   DASGetXoffset(int *nOffset);
	/*范围8~-8*/
	uint32_t __stdcall   DASGetYoffset(int *nOffset);
	/*范围20~-20*/
	uint32_t __stdcall   DASGetPrintChroma(int *nChrome);
	/*范围20~-20*/
	uint32_t __stdcall   DASsetXoffset(int nOffset);
	/*范围8~-8*/
	uint32_t __stdcall   DASsetYoffset(int nOffset);
	/*范围20~-20*/
	uint32_t __stdcall   DASsetPrintChroma(int  nChrome);



	//GDI
	uint32_t __stdcall   DASsetCardSize(double w, double h);
	uint32_t __stdcall   DASaddProtectedRect(double left, double top,double w, double h); // 单位mm
	uint32_t __stdcall   DASaddNeedEraseRect(double left, double top,double w, double h);



	//设置字体，不设置将采用默认
	uint32_t __stdcall   DASsetFont(const char* fontName,double size);
	//设置画笔颜色，不设置将采用默认
	uint32_t __stdcall   DASsetTextColor(unsigned char r,unsigned char g,unsigned char b);
	//设置字体修饰
	uint32_t __stdcall   DASsetTextDecorate(bool isStrong,bool isItalic,bool isUnderline);
	//设置文本方向
	uint32_t __stdcall   DASsetTextDirection(bool isLandScape,bool isReverseSequence,bool isAutoLineFeed);
	//设置行间距、字间距
	uint32_t __stdcall   DASsetSpacing(double LineSpacing,double CharSpacing);
	//打印文本块,单位毫米
	uint32_t __stdcall   DASdrawText(double x,double y,double width,double height,const char* gbkText); // 单位mm
	uint32_t __stdcall   DASdrawTextForRotation(double x,double y,double width,double height,const char* gbkText,int rotation); // 单位mm
	uint32_t __stdcall   DASdrawTextW(double x,double y,double width,double height,const WCHAR* Text); // 单位mm
	//
	uint32_t __stdcall   DASdrawImage(double x,double y,double width,double height,const char* imagefile,bool isPhoto); // 单位mm
	uint32_t __stdcall   DASdrawImageForRotation(double x,double y,double width,double height,const char* imagefile,bool isPhoto,int rotation);
	uint32_t __stdcall   DASdrawBase64ImageForRotation(double x,double y,double width,double height,const char* Base64img, const char *imgsuffix, bool isPhoto,int rotation);

	//errLev: 
	//  0 = Error Rate (7%)
	//	1 = Error Rate (15%)
	//	2 = Error Rate (25%)
	//	3 = Error Rate (30%)
	uint32_t  __stdcall    DASdrawQR(double x,double y,double width,double height,const char* data, int errLev,bool isAutoFill);// 单位mm
	uint32_t  __stdcall    DASdrawQRForRotation(double x,double y,double width,double height,const char* data, int errLev,bool isAutoFill,int rotation);// 单位mm
	uint32_t  __stdcall    DASdrawQRbyVersion(double x,double y,double width,double height,const char* data, int errLev,int nVersion,bool isAutoFill,int rotation = 0);// 单位mm
	uint32_t  __stdcall    DASsetBarCodeColor(unsigned char r,unsigned char g,unsigned char b);
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
	uint32_t __stdcall   DASdrawBarCode(double x,double y,double width,double height,int barcodeType, const char* data, bool isText,bool isUnderText,int barcodeMultiplier);
	uint32_t __stdcall   DASdrawBarCodeForRotation(double x,double y,double width,double height,int barcodeType, const char* data, bool isText,bool isUnderText,int barcodeMultiplier,int rotation);
	uint32_t __stdcall   DASBuildGraphicsData(bool isFrontSide,bool  AutoGenerateMask);
	uint32_t __stdcall   DASBuildGraphicsDataForRotation(bool isFrontSide,bool  AutoGenerateMask,int rotation);


	//TCPIP, SDK--->Service
	uint32_t __stdcall   DASGetSDKVersion(unsigned char *Version,int *length);

	//JOB IF,  SDK ---> Service
	uint32_t __stdcall   DASSetPrinterName(const char * PrinterName,const char *PrinterType);

	uint32_t __stdcall   DASSetBlackPrintMethod(int method);
	//0：代表二值 1：误差扩散

	uint32_t __stdcall   DASSetRibbon(int method);
	//取值范围1～4，D300RW 默认4
	uint32_t __stdcall   DASSetGraphicDataByFile(int Side,const char *BmpFile);
	//0：正面  1：反面
	uint32_t __stdcall   DASSetEraseDataByFile(const char *BmpFile,int Eraseflag);
	//1:不擦除 0：擦除
	uint32_t __stdcall   DASSetCopies(int nCopies);
	//取值范围1～65535
	uint32_t __stdcall   DASSetNthreshold(int threshold);
	//取值范围0～255
	uint32_t __stdcall   DASSetPrintDirection(int Print_Direction);
	//0：纵向 1：横向
	uint32_t __stdcall   DASPrintCard();

	uint32_t __stdcall   DASPrintCard2();
	uint32_t __stdcall   DAS_Card_Printer(unsigned char *pPrintData,int datalength);

	//PrinterType   1:Only_Enum_USB_Printer   2:Only_Enum_TCP_Printer  3:all Printer
	uint32_t __stdcall DASEnumPrinter(char *PrinterConnectString,int *ConnStringlen,int  PrinterType);

	//follow for  D300 
	uint32_t __stdcall   DASSetPrintSpeed(int Para);
	//取值范围0～20默认10
	uint32_t __stdcall   DASSetCardContrast(int Para);
	//取值范围0～20默认10
	uint32_t __stdcall   DASSetPrintTemperature(int Para);
	//取值范围0～20默认10
	uint32_t __stdcall   DASSetEraseTemperature(int  temprature);
	//取值范围0～20默认10
	uint32_t __stdcall   DASEraseCard();
	uint32_t __stdcall   DASCleanPrinter();
	uint32_t __stdcall   DASPrintTestCard();
	uint32_t __stdcall   DASPrintTechnicalTestCard();

	//Direct Type
	uint32_t __stdcall DAS_CardSet								 
		(
		int  CardType,       				
		int  FrontDecurlStep,     /*--正面展平步数*/
		int  BackDecurlStep,     /*--背面展平步数*/
		int  StandardCardExitPositon,      /*--标准出卡位置0-接收盒，1-手动*/								
		int  ErrorCardExitPositon,      /*--故障出卡位置*/
		int  SetCardPositon,     /* --设置进卡位置0-传送盒，1-手动，2-自动*/								
		int  CardEjectSide           /*--出卡时卡面方向*/
		);



	//获取打印机状态及其相关辅助函数
	uint32_t __stdcall DASFetchPrinterStatus(uint64_t *status);
	//	ErrNo：
	//	0、就绪；
	//	1、缺卡错；
	//	2、卡卡错；
	//	3、归位错；
	//	4、译码错；
	//	5、卡片延时；
	//	6、前盖打开错；
	//	7、出卡错；
	//	8、印头高温错；
	//	9、印头低温错；
	//	10、印头传感器错；
	//	11、传感器错；
	//	12、Flash错;
	uint32_t __stdcall DASGetPrinterStatus_ErrorNo(uint64_t status);
	// 0—卡盒装卡，1—手动装卡，2—自动装卡；
	uint32_t __stdcall DASGetFeedCardMode(uint64_t status);
	// 0—不需清洁，1—建议清洁，2—必须清洁；
	uint32_t __stdcall DASGetCleaningStatus(uint64_t status);
	// 1—风扇开启，0—风扇关闭；
	uint32_t __stdcall DASGetFanStatus(uint64_t status);
	// 1—卡盒缺卡，0—卡盒有卡；
	uint32_t __stdcall DASGetPrinterStatus_CardBoxStatus(uint64_t status);
	// 1—前盖打开，0—前盖闭合；
	uint32_t __stdcall DASGetPrinterStatus_FrontCoverStatus(uint64_t status);
	// 2--接受缓存满，1—接收缓存空，0—接收缓存不满不空
	uint32_t __stdcall DASGetRecvBufferStatus(uint64_t status);
	// 1—打印机忙，  0—打印机空闲
	uint32_t __stdcall DASGetBusyStatus(uint64_t status);


	uint32_t __stdcall   DASGetKey(byte level, char *buf, int nLen);
	uint32_t __stdcall   DASSetKey(byte level,char *key1, int nLen1,char *key2, int nLen2);
	uint32_t __stdcall   DASGetPrinterHeadID_B(char *buf, int nLen);
	uint32_t __stdcall   DASSetPrinterHeadID_B(char *buf, int nLen);
	uint32_t __stdcall   DASSetPrinterHeadID_A(char *buf_A, int nLen_A,char *buf_B, int nLen_B);

	//读取擦除温度 0--20
	uint32_t __stdcall DASGetEraseTemperature(BYTE *flag);
	//读取打印速度 0--20
	uint32_t __stdcall DASGetPrintSpeed(BYTE *flag);
	//读取打印温度 0--20
	uint32_t __stdcall DASGetPrintTemperature(BYTE *flag);
	//读取手动排卡 *flag : 0无效 ，1有效
	uint32_t __stdcall DASGetEjectMode(BYTE *flag);
	//设置手动排卡 flag : 0无效 ，1有效
	uint32_t __stdcall DASSetEjectMode(BYTE flag);
	//DASSetEjectMode 设置手动排卡模式有效时，使用这个接口退卡
	uint32_t __stdcall DASEject();
	uint32_t __stdcall   DASdrawTextW2(double x,double y,double width,double height,const WCHAR* text, bool eraseRect);
	uint32_t __stdcall   DASdrawText2(double x,double y,double width,double height,const char* gbkText,bool earseRect);
	uint32_t __stdcall   DASdrawImage2(double x,double y,double width,double height,const char* imagefile,bool isPhoto,bool eraseRect);
	uint32_t __stdcall   DASBuildGraphicsDataForRotation2(bool isFrontSide,bool  AutoGenerateMask,int rotation);
	uint32_t __stdcall   DASBuildGraphicsOnlyPrint(bool isFrontSide);
	uint32_t __stdcall DASSetPrintSpeed_NoReset(byte spd);
	uint32_t __stdcall DASSetCardContrast_NoReset(byte tmp);
	uint32_t __stdcall DASSetPrintTemperature_NoReset(byte tmp);
	uint32_t __stdcall DASSetEraseTemperature_NoReset(byte tmp);
	uint32_t __stdcall DASSetCardExitPositon(byte Pos);
	uint32_t __stdcall DASSetCardInjectPositon(byte Pos);
	uint32_t __stdcall DASSetCardType(byte cardType);
	uint32_t __stdcall DASClosePrinter();
	uint32_t __stdcall DSSetKey2(char *buf);
	uint32_t __stdcall DSWriteLicense(const unsigned char* licStr, const uint32_t len);
	uint32_t __stdcall DSReadLicense(unsigned char* licStr, uint32_t * len);
#ifdef __cplusplus
}
#endif
#endif