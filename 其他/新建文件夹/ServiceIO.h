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

	//���Σ�0 �Զ�ģʽ  1 �ֶ�ģʽ
	uint32_t __stdcall  DASGetFeedCardPattern(int *Pattern);
	//��Σ�0 �Զ�ģʽ  1 �ֶ�ģʽ
	uint32_t __stdcall  DASSetFeedCardPattern(int Pattern);
	uint32_t __stdcall  DASGetPrinterSerialNumber(unsigned char *SN,int *length);
	uint32_t __stdcall  DASGetPrinterHeadSerialNumber(unsigned char *SN,int *length);
	uint32_t __stdcall  DASGetPrinterUserData(unsigned char *UserData,int *length);
	/*
	CardPos����Ƭλ��
	bit0 : sens1״̬��1���п���0��û����
	bit1 : sens2״̬��1���պϣ�0�����ǣ�
	bit2 : sens3״̬��1���п���0��û����
	bit3 : sens4״̬��0��ӡͷ�ѹ�λ��1��ӡͷδ��λ��
	bit4 : sens5״̬��1�������п���0������û����
	bit5~7:Ԥ����
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
	4�����Ӷ�ȡ����������Ϣ��ָ�
	n = 1����ȡ��ӡ�����ͣ�
	n = 2����ȡ��ӡ�����кţ�
	n = 3����ȡ��ӡ���汾�ţ�
	n = 4����ȡ��ӡ��ӡͷ����������
	n = 5����ȡ��ӡ��ӡͷID��
	n = 6����ȡ��ǰӡͷ������忨����
	n = 7����ȡ��ǰӡͷ�忨������
	n = 8����ȡ��ǰӡͷ��������
	n = 9����ȡ��ǰ����������忨����
	n = 10����ȡ��ǰ�����忨��
	n = 11����ȡ��ǰ������������
	*/
	uint32_t __stdcall  DASGetRunningInfo(int p_infoType,unsigned char *p_acRecv,int *Recvedlen);
	uint32_t __stdcall  DASRebootPrinter();
	uint32_t __stdcall  DASSetUserData(unsigned char *UserData,int length);

	/*
	���ܣ� ���ÿ��С���������
	FeederFlag:  0---�Ƴ����У�1---װ�俨�У�
	OutCardDir�� 0---ǰ������1---�������
	��ע�����óɺ����ʱ������Ӧ��Ӧ����Ƴ�״̬��
	*/
	uint32_t __stdcall  DASSetCardBoxEjectCard(int FeederFlag ,int OutCardDir);
	uint32_t __stdcall  DASRejectCard();

	/*
	���ܣ� ��ӡ�������ӡ���棬
	������
	* n=0:������ͻ��壬
	* n=1:������ջ��壬
	* n= 2:������շ��ͻ��壻
	*/
	uint32_t __stdcall   DASInitPrinter(int Option);

	/*��Χ20~-20*/
	uint32_t __stdcall   DASGetXoffset(int *nOffset);
	/*��Χ8~-8*/
	uint32_t __stdcall   DASGetYoffset(int *nOffset);
	/*��Χ20~-20*/
	uint32_t __stdcall   DASGetPrintChroma(int *nChrome);
	/*��Χ20~-20*/
	uint32_t __stdcall   DASsetXoffset(int nOffset);
	/*��Χ8~-8*/
	uint32_t __stdcall   DASsetYoffset(int nOffset);
	/*��Χ20~-20*/
	uint32_t __stdcall   DASsetPrintChroma(int  nChrome);



	//GDI
	uint32_t __stdcall   DASsetCardSize(double w, double h);
	uint32_t __stdcall   DASaddProtectedRect(double left, double top,double w, double h); // ��λmm
	uint32_t __stdcall   DASaddNeedEraseRect(double left, double top,double w, double h);



	//�������壬�����ý�����Ĭ��
	uint32_t __stdcall   DASsetFont(const char* fontName,double size);
	//���û�����ɫ�������ý�����Ĭ��
	uint32_t __stdcall   DASsetTextColor(unsigned char r,unsigned char g,unsigned char b);
	//������������
	uint32_t __stdcall   DASsetTextDecorate(bool isStrong,bool isItalic,bool isUnderline);
	//�����ı�����
	uint32_t __stdcall   DASsetTextDirection(bool isLandScape,bool isReverseSequence,bool isAutoLineFeed);
	//�����м�ࡢ�ּ��
	uint32_t __stdcall   DASsetSpacing(double LineSpacing,double CharSpacing);
	//��ӡ�ı���,��λ����
	uint32_t __stdcall   DASdrawText(double x,double y,double width,double height,const char* gbkText); // ��λmm
	uint32_t __stdcall   DASdrawTextForRotation(double x,double y,double width,double height,const char* gbkText,int rotation); // ��λmm
	uint32_t __stdcall   DASdrawTextW(double x,double y,double width,double height,const WCHAR* Text); // ��λmm
	//
	uint32_t __stdcall   DASdrawImage(double x,double y,double width,double height,const char* imagefile,bool isPhoto); // ��λmm
	uint32_t __stdcall   DASdrawImageForRotation(double x,double y,double width,double height,const char* imagefile,bool isPhoto,int rotation);
	uint32_t __stdcall   DASdrawBase64ImageForRotation(double x,double y,double width,double height,const char* Base64img, const char *imgsuffix, bool isPhoto,int rotation);

	//errLev: 
	//  0 = Error Rate (7%)
	//	1 = Error Rate (15%)
	//	2 = Error Rate (25%)
	//	3 = Error Rate (30%)
	uint32_t  __stdcall    DASdrawQR(double x,double y,double width,double height,const char* data, int errLev,bool isAutoFill);// ��λmm
	uint32_t  __stdcall    DASdrawQRForRotation(double x,double y,double width,double height,const char* data, int errLev,bool isAutoFill,int rotation);// ��λmm
	uint32_t  __stdcall    DASdrawQRbyVersion(double x,double y,double width,double height,const char* data, int errLev,int nVersion,bool isAutoFill,int rotation = 0);// ��λmm
	uint32_t  __stdcall    DASsetBarCodeColor(unsigned char r,unsigned char g,unsigned char b);
	/*
	barcodeType: bar code type:
	0 = code 39 (3 of 9 alphanumeric)
	1 = 2/5 interleave (numeric, even, >=5 )
	2 = UPC �C E (numeric 7 digits encoded)
	3. = EAN8 (numeric 7 digits encoded) 
	4. = EAN13 (numeric 12 digits encoded)
	5. = UPC �C A (numeric 12 digits encoded)
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
	//0�������ֵ 1�������ɢ

	uint32_t __stdcall   DASSetRibbon(int method);
	//ȡֵ��Χ1��4��D300RW Ĭ��4
	uint32_t __stdcall   DASSetGraphicDataByFile(int Side,const char *BmpFile);
	//0������  1������
	uint32_t __stdcall   DASSetEraseDataByFile(const char *BmpFile,int Eraseflag);
	//1:������ 0������
	uint32_t __stdcall   DASSetCopies(int nCopies);
	//ȡֵ��Χ1��65535
	uint32_t __stdcall   DASSetNthreshold(int threshold);
	//ȡֵ��Χ0��255
	uint32_t __stdcall   DASSetPrintDirection(int Print_Direction);
	//0������ 1������
	uint32_t __stdcall   DASPrintCard();

	uint32_t __stdcall   DASPrintCard2();
	uint32_t __stdcall   DAS_Card_Printer(unsigned char *pPrintData,int datalength);

	//PrinterType   1:Only_Enum_USB_Printer   2:Only_Enum_TCP_Printer  3:all Printer
	uint32_t __stdcall DASEnumPrinter(char *PrinterConnectString,int *ConnStringlen,int  PrinterType);

	//follow for  D300 
	uint32_t __stdcall   DASSetPrintSpeed(int Para);
	//ȡֵ��Χ0��20Ĭ��10
	uint32_t __stdcall   DASSetCardContrast(int Para);
	//ȡֵ��Χ0��20Ĭ��10
	uint32_t __stdcall   DASSetPrintTemperature(int Para);
	//ȡֵ��Χ0��20Ĭ��10
	uint32_t __stdcall   DASSetEraseTemperature(int  temprature);
	//ȡֵ��Χ0��20Ĭ��10
	uint32_t __stdcall   DASEraseCard();
	uint32_t __stdcall   DASCleanPrinter();
	uint32_t __stdcall   DASPrintTestCard();
	uint32_t __stdcall   DASPrintTechnicalTestCard();

	//Direct Type
	uint32_t __stdcall DAS_CardSet								 
		(
		int  CardType,       				
		int  FrontDecurlStep,     /*--����չƽ����*/
		int  BackDecurlStep,     /*--����չƽ����*/
		int  StandardCardExitPositon,      /*--��׼����λ��0-���պУ�1-�ֶ�*/								
		int  ErrorCardExitPositon,      /*--���ϳ���λ��*/
		int  SetCardPositon,     /* --���ý���λ��0-���ͺУ�1-�ֶ���2-�Զ�*/								
		int  CardEjectSide           /*--����ʱ���淽��*/
		);



	//��ȡ��ӡ��״̬������ظ�������
	uint32_t __stdcall DASFetchPrinterStatus(uint64_t *status);
	//	ErrNo��
	//	0��������
	//	1��ȱ����
	//	2��������
	//	3����λ��
	//	4�������
	//	5����Ƭ��ʱ��
	//	6��ǰ�Ǵ򿪴�
	//	7��������
	//	8��ӡͷ���´�
	//	9��ӡͷ���´�
	//	10��ӡͷ��������
	//	11����������
	//	12��Flash��;
	uint32_t __stdcall DASGetPrinterStatus_ErrorNo(uint64_t status);
	// 0������װ����1���ֶ�װ����2���Զ�װ����
	uint32_t __stdcall DASGetFeedCardMode(uint64_t status);
	// 0��������࣬1��������࣬2��������ࣻ
	uint32_t __stdcall DASGetCleaningStatus(uint64_t status);
	// 1�����ȿ�����0�����ȹرգ�
	uint32_t __stdcall DASGetFanStatus(uint64_t status);
	// 1������ȱ����0�������п���
	uint32_t __stdcall DASGetPrinterStatus_CardBoxStatus(uint64_t status);
	// 1��ǰ�Ǵ򿪣�0��ǰ�Ǳպϣ�
	uint32_t __stdcall DASGetPrinterStatus_FrontCoverStatus(uint64_t status);
	// 2--���ܻ�������1�����ջ���գ�0�����ջ��治������
	uint32_t __stdcall DASGetRecvBufferStatus(uint64_t status);
	// 1����ӡ��æ��  0����ӡ������
	uint32_t __stdcall DASGetBusyStatus(uint64_t status);


	uint32_t __stdcall   DASGetKey(byte level, char *buf, int nLen);
	uint32_t __stdcall   DASSetKey(byte level,char *key1, int nLen1,char *key2, int nLen2);
	uint32_t __stdcall   DASGetPrinterHeadID_B(char *buf, int nLen);
	uint32_t __stdcall   DASSetPrinterHeadID_B(char *buf, int nLen);
	uint32_t __stdcall   DASSetPrinterHeadID_A(char *buf_A, int nLen_A,char *buf_B, int nLen_B);

	//��ȡ�����¶� 0--20
	uint32_t __stdcall DASGetEraseTemperature(BYTE *flag);
	//��ȡ��ӡ�ٶ� 0--20
	uint32_t __stdcall DASGetPrintSpeed(BYTE *flag);
	//��ȡ��ӡ�¶� 0--20
	uint32_t __stdcall DASGetPrintTemperature(BYTE *flag);
	//��ȡ�ֶ��ſ� *flag : 0��Ч ��1��Ч
	uint32_t __stdcall DASGetEjectMode(BYTE *flag);
	//�����ֶ��ſ� flag : 0��Ч ��1��Ч
	uint32_t __stdcall DASSetEjectMode(BYTE flag);
	//DASSetEjectMode �����ֶ��ſ�ģʽ��Чʱ��ʹ������ӿ��˿�
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