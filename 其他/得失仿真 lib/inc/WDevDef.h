/*
�ṩ���û�ʹ�õ������Ͷ���
*/

#ifndef _WDEVDLL_H_
#define _WDEVDLL_H_

#include "WDevCmdSet.h"

typedef unsigned char u8;
typedef unsigned short  u16;
typedef unsigned long u32;
typedef signed long s32;
typedef signed short s16;
typedef signed char s8;

#define HCTRL_GET_VAL32(x)	(u32)((*(x) << 24)+ (*((x) + 1) << 16) + (*((x) + 2) << 8) + *((x) + 3) )
#define HCTRL_GET_VAL16(x)	(u16)((*(x) << 8)+ *((x) + 1))
#define HCTRL_SET_VAL32(x,v) {\
	*(x) = (u8)((v) >> 24);\
	*((x) + 1) = (u8)((v) >> 16);\
	*((x) + 2) = (u8)((v) >> 8);\
	*((x) + 3) = (u8)(v);\
}
#define HCTRL_SET_SETVAL16(x,v) {\
	*(x) = (u8)((v) >> 8);\
	*((x) + 1) = (u8)(v);\
}

#define HCTRL_H2L16(n)	(u16)(((u16)(n) >> 8) | ((u16)(n) << 8))
#define HCTRL_H2L32(n)	(u32)((((u32)(n)) >> 24) | \
						((((u32)(n)) & 0xff0000) >> 8) |\
						(((n) & 0xff00) << 8) | (((n) & 0xff) << 24))


#define HCTRL_H2LS16(n)	(s16)((((s16)(n) >> 8) & 0xff) | ((((s16)(n)) << 8) & 0xff00))
#define HCTRL_H2LS32(n)	(s32)(((((s32)(n)) >> 24) & 0xff) | \
						((((s32)(n)) >> 8) & 0xff00) |\
						(((s32)(n) << 8) & 0xff0000) | (((s32)(n)  << 24)& 0xff000000))

//--------------------------------

typedef struct _DEVACK_INFO {
	BYTE *lpBuf;		//�豸���ص�����
	WORD bufLen;		//�����С
	WORD datLen;		//���ݳ���

	BYTE ackCode;			//Ӧ����,0��ʾ�ɹ�
}DEVACK_INFO;

typedef struct _DEVREQ_INFO {
	/*LPCTSTR*/
	const TCHAR *cmdCodeStr;//�������
							//�������ΪCTRL_DEVCMD_STʱ,��ʾ�豸����,lpDat[0]��Ϊ������0x80 ~ 0x9f
	const BYTE *lpDat;		//�豸��������
	WORD datLen;			//���ݳ���
}DEVREQ_INFO;


typedef struct _DEVACK_INFO2 {
	BYTE *lpBuf;		//�û����ݻ���
	DWORD bufLen;		//�����С
	DWORD datIdx;		//���ݳ���

	BYTE devPktBuf[512];	//�豸���ص�

	WORD pktDatLen;
	BYTE ackCode;			//Ӧ����,0��ʾ�ɹ�
}DEVACK_INFO2;

typedef struct _DEVREQ_INFO2 {
	const TCHAR *cmdCodeStr;//�������
							//�������ΪCTRL_DEVCMD_STʱ,��ʾ�豸����,lpDat[0]��Ϊ������0x80 ~ 0x9f
	BYTE *lpDat;		//�豸��������
	DWORD datLen;			//���ݳ���
	DWORD datIdx;
	BYTE devPktBuf[512];	//�豸���ݰ�
	WORD pktDatLen;
}DEVREQ_INFO2;

#define RAWMODE_DEV_REQ			0x01	//�������豸����
#define RAWMODE_DEV_RESP		0x02	//�����豸��Ӧ����
#define RAWMODE_DEV_CFGXML		0x03	//����XML
#define RAWMODE_DEV_CFGDAT		0x04	//�����豸��������
#define RAWMODE_DEV_MKCFGDAT	0x05	//�γ��豸��������

//--------portMode---------------
#define PORTINFO_PMODE_DATA		0x01
#define PORTINFO_PMODE_CTRL		0x02

#define PORTINFO_PMODE_ALL		0x03

typedef struct _PORTINFO {
	//LPCTSTR	path;
	const TCHAR *path;
	LONG readTimeout;
	LONG writeTimeout;

	WORD portType;	//����ָ��path������豸����
	WORD portMode;	//ָ����Ҫ���豸�Ķ˿ڣ��������ݿںͿ��ƿڡ�
}PORTINFO, *LPPORTINFO;
//----portType------------
#define INVALID_PORT	0x0000
#define UART_PORT		0x0100
#define LPT_PORT		0x0200

#define USB_PORT		0x0300
	#define USBPRN_PORT		0x0301
	#define HID_PORT		0x0302
#define NET_PORT		0x0400
	#define NET_DPORT		0x0401
	#define NET_CPORT		0x0402

typedef int PORT_HANDLE;
#define INVALID_PORT_HANDLE (-1)

//-------DFUStart:tag-------------------
#define DFU_TAG_RESTART		(0x01)	//���º������豸

#define DFU_FWTAG_LEN		32
typedef struct _DFU_FWINFO {
	BYTE dfuID[5];
	BYTE ver[4];
	BYTE fwDesc[DFU_FWTAG_LEN + 1];
}DFU_FWINFO;

#define DFU_PRGS_SIZE		100

#define PARAM_TEXTSTR		0x01
#define PARAM_PRGS			0x02
#define MSG_WDFU_ERRCODE	(WM_USER + 0x100)
#define MSG_WDFU_PROGRESS_BEGIN 0x20000
#define MSG_WDFU_PROGRESS_END   0x20064
#define WM_USER  0X0400

//--------CFG XML------------------------
#define XML_CFGID_DESC	"xmlCfgDoc01"
#define XML_CFGID_LEN	11
typedef struct XML_CFG_HDPKT {
	BYTE	ID[12];
	WORD	len;
	WORD	crc16;
}XMLCFG_HDPKT;

#define XML_ITEM_NAME		_T("Name")	//������������ͬ
#define XML_ITEM_CURRVAL	_T("CurrVal")
#define XML_ITEM_LEN		_T("Bits")
#define XML_ITEM_TYPE		_T("Type")
#define XML_ITEM_MAXVAL		_T("MaxVal")
#define XML_ITEM_MINVAL		_T("MinVal")
#define XML_ITEM_CHRNUMS	_T("CharNums")
#define XML_ITEM_PROP		_T("Tag")
#define XML_ITEM_DATSLCT	_T("Datas")
#define XML_ITEM_OFS		_T("Ofs")


#define SEPS_CHAR		_T(';')

#define ITEMFMT_NAME_LEN	(20)
#define ITEMFMT_SLCT_MAXLEN	(1024)

//----fmtType-----------------
#define ITEMFMT_TYPE_NONE	0
#define ITEMFMT_TYPE_VAL	1
#define ITEMFMT_TYPE_STR	2
#define ITEMFMT_TYPE_SLCT	3

//------fmtTag----------------
#define ITEMFMT_TAG_LH		(0x0001)	// ����ֵ�Ĵ�ŷ�ʽΪ��λ��ǰ����λ�ں�(2byte,4byte)
#define ITEMFMT_TAG_HEX		(0x0002)	// ����ֵ��ʮ���������ݸ�ʽ���

//---------------------------------------------------------
#define CFGPKT_MAXLEN		4096	// ���ð�����󳤶�(bytes)
#define CFGITEM_VAL_MAXLEN	1024	//�������������ֵ����󳤶�(bytes)

#define CFGITEM_VAL_NONE	0
#define CFGITEM_VAL_LONG	1
#define CFGITEM_VAL_STR		2

//----------------�豸��̬������Ϣ-------------------
#define DEVINFO_TYPE_NONE		0
#define	DEVINFO_TYPE_GEN		0x01	//ͨ����Ϣ
#define DEVINFO_TYPE_PORT		0x02	//�豸�Ľӿ���Ϣ
#define DEVINFO_TYPE_PAGE		0x03	//ҳ����Ϣ
#define DEVINFO_TYPE_MEDIA		0x04	//��ӡ�����Ϣ
#define DEVINFO_MAX_TYPE		DEVINFO_TYPE_MEDIA

//��˸�ʽ
typedef struct _DSEMUL_DEVINFO_ITEM {
	u8 size;
	u8 itemType;	//
	u8 info_dats[1];
}DSEMUL_DEVINFO_ITEM;

#define DEVINFO_TYPE_D300	(0x01)
typedef struct _DSEMUL_DEVICE_INFO {
	u8 infoType[2];
	u8 itemCnts;
	u8 revs;
	DSEMUL_DEVINFO_ITEM infoItem[1];
}DSEMUL_DEV_INFO;

#define DEVINFO_GEN_SEP	(';')
typedef struct _DSEMUL_DEVINFO_GEN {
	u8 size;
	u8 itemType;		//	DSEMUL_SYSINFO_GEN
	u8 sep;
	//�豸�ͺ�;���к�;ͨѶ�汾��;�̼��汾��;������;��ע;
	u8 info_desc[1];	//240
}DSEMUL_DEVINFO_GEN;

typedef struct _DSEMUL_DEVINFO_PORT {
	u8 size;
	u8 itemType;		//	DSEMUL_DEVINFO_PORT
	u8 recvBufSize[4]; 	//
	u8 frameBufSize[4];	//size = 0��ʾ֧��֡����

	u8 cmprType;		//֡������Чʱ������ʹ��ѹ��
}DSEMUL_DEVINFO_PORT;

//------------------
#define DEVINFO_DSBMP_NONE	0
#define DEVINFO_DSBMP_EN	1
//----bmpType-------------
#define BMP_RASTER_FMT	(1)	//��դλͼ
#define BMP_24PRN_FMT	(2)
typedef struct _DSEMUL_DEVINFO_PAGE {
	u8 size;
	u8 itemType;		//	DSEMUL_DEVINFO_PAGE
	u8 pageW[2]; 		//
	u8 pageH[2];		// size = 0��ʾ֧��֡����
	u8 pMrg[4];			// ҳ��߽磬��������
	u8 xDpi;
	u8 yDpi;
	u8 bpps;
	u8 bmpType;			//λͼ��ʽ,��դ,24���ӡ
	u8 dsBmp;
}DSEMUL_DEVINFO_PAGE;
typedef struct _DSEMUL_DEVINFO_MEDIA {
	u8 size;
	u8 itemType;		//	DSEMUL_DEVINFO_MEDIA

}DSEMUL_DEVINFO_MEDIA;

//-------�豸����ʱ��ϵͳ��������----------------
#define BMP_DEVPROP_NONE		0xff
#define BMP_DEVPROP_PRN			0x81	//print out param
#define SYS_MAX_PARAMPROP		BMP_DEVPROP_PRN

//-------ϵͳ״̬--------------------------
#define DEVSTAT_TYPE_GEN	0x30	//ϵͳ״̬
#define	DEVSTAT_TYPE_FAULT	0x31	//ϵͳ�쳣״̬
#define DEVSTAT_TYPE_PROC	0x32	//���ݴ���
#define DEVSTAT_TYPE_PRNOUT	0x33	//��е����/������״̬
#define DEVSTAT_TYPE_PORT	0x34	//���ݽ��ա�����״̬

//-------GEN_STAT------------
#define GEN_SYSSTAT_IDLE	0	//���У��ȴ�ָ��
#define GEN_SYSSTAT_WORKING	1	//��������
#define GEN_SYSSTAT_READY	2	//����
#define GEN_SYSSTAT_BUSY	3	//���ݽ���
#define GEN_SYSSTAT_PAUSE	4	//��ͣ

#define GEN_SYSSTAT_ERR		0xff//�쳣

typedef struct _DSEMUL_GEN_STAT {
	u8 size;
	u8 itemType;	//	DEVSTAT_TYPE_GEN
	u8 sysStat;		// ϵͳ����״̬
	u8 errCode[2];	//�����
}DSEMUL_GEN_STAT;

typedef struct _DSEMUL_FAULT_STAT {
	u8 size;
	u8 itemType;	//	DEVSTAT_TYPE_FAULT
	u8 faultNo;		//

}DSEMUL_FAULT_STAT;
typedef struct _DSEMUL_PROC_STAT {
	u8 size;
	u8 itemType;	//	DEVSTAT_TYPE_PROC

	u8 procStat;	// ���ݴ���״̬
	u8 jobNumber[2];	//��ҵ��
	u8 frmIdx[2];		//��ҵ�е�������

	u8 errCode;
}DSEMUL_PROC_STAT;
typedef struct _DSEMUL_PRNOUT_STAT {
	u8 size;
	u8 itemType;		//	DEVSTAT_TYPE_PROC
	u8 prnStat;			//
	u8 qCnts;			//��ӡ������

	u8 jobNumber[2];	//��ҵ��
	u8 frmIdx[2];		//��ҵ�е�������
	u8 temp;			//��ӡͷ�¶ȣ�-1 ��ʾʧ��
	u8 sensor[4];
}DSEMUL_PRNOUT_STAT;
typedef struct _DSEMUL_PORT_STAT {
	u8 size;
	u8 itemType;		//	DEVSTAT_TYPE_PORT

	u8 portStat;		//
	u8 recvRate[2];		//���ջ�������ݱ���(ǧ�ֱ�)
	u8 recvSpace[4];	//���ջ����ʣ��ռ�
	u8 sendDats[4];
}DSEMUL_PORT_STAT;

//-------�豸����ʱ��ϵͳ��������----------------
#define BMP_DEVPROP_NONE		0xff
#define BMP_DEVPROP_PRN			0x81	//print out param
#define SYS_MAX_PARAMPROP		BMP_DEVPROP_PRN

#define BMP_DEVPROP_BKNONE	0	//����������
#define BMP_DEVPROP_BKFULL	1	//��Ƭȫ������
#define	BMP_DEVPROP_BKBMP	2	//��ǰ��λͼ��С����
#define	BMP_DEVPROP_BKUSER	3	//���û��Զ���λͼ����

#define BMP_DEVPROP_PMODE_PRINT		0	//��ӡ�Ҳ���
#define BMP_DEVPROP_PMODE_ERASE		1	//ֻ����
#define	BMP_DEVPROP_PMODE_PRNONLY	2	//ֻ��ӡ

#define BMP_DEVPROP_NONE		0xff
#define BMP_DEVPROP_PRN			0x81	//print out param
#define SYS_MAX_PARAMPROP		BMP_DEVPROP_PRN
typedef struct _DEVPROP_PRNOUT {
	u8	propSize;	//�ṹ��Ĵ�С

	u8	devType;	//BMP_DEVPROP_PRN
	u8	bkBmpID;	//BMP_DEVPROP_BKNONE
	u8	cardType;	// ������ -- 0:mblack, 1:mblue,2:rblack
	u8	cardInputMode;// ������ʽ -- 0:AutoFeed, 1:manual Feed , 2:Auto Select
	u8	cardOutputMode;// ������ʽ -- 0:װ���н���,1:�ֶ�����,2:���˿�,3:���˿�
	u8	printTemp;	// ��ӡ�¶� -- 0 <= t <= 20
	u8	printContrast;// ��ӡ�Աȶ� -- 0 <= t <= 20
	u8	printSpeed;	// ��ӡ�ٶ� -- 0 <= s <= 20
	u8	grayTemp;	// �Ҷ��¶� -- 0 <= t <= 20
	u8	graySpeed;	// �����ٶ� -- 0 <= s <= 20
	u8	eraseTemp;	// ���ò����¶� -- 0 <= t <= 20
	u8	printMode;	// 0:Card Print, 1:Card Erase
	u8	revs[3];
}DEVPROP_PRNOUT;

typedef struct _DEVPROP_INFO
{
	u16 size;
	u8 revs[2];
	DEVPROP_PRNOUT prnProp;
}DEVPROP_INFO;

//--------------------------------------------
#define	DEVBMP_ID		0x4250
typedef struct _DEV_BMP {
	u16	ID;		//
	u16	dpi;	//��ӡ�豸���dpi
	u16	posX;	//���Ͻ�����
	u16	posY;

	u16	pixelW;
	u16 txPixelH;	//ǰ��λͼ��
	u16 bkPixelH;	//����λͼ��
	u8	bpps;		//������ɫ���(bits)
	u8 bmpType;	//�豸λͼ���ͣ�1����դλͼ
	u8	revs[4];

	DEVPROP_INFO devInfo;
	u8 BmpDats[1];	//ǰ���ͱ���λͼ����
}DEV_BMP;

typedef struct _UNCMPR_INFO {
	u32 cmprLen;			//ѹ�����ݳ���
	u32	uncmprLen;			//��ѹ������ݳ���
	u32 resultTag;			//
	u32 stat;
	u16	jobNumber;
	u16	frmIdx;
	u8 cmprType;			//ѹ������
	void *userParm;
}UNCMPR_INFO;

#endif

