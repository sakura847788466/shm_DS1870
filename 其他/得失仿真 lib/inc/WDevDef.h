/*
提供给用户使用的声明和定义
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
	BYTE *lpBuf;		//设备返回的数据
	WORD bufLen;		//缓冲大小
	WORD datLen;		//数据长度

	BYTE ackCode;			//应答码,0表示成功
}DEVACK_INFO;

typedef struct _DEVREQ_INFO {
	/*LPCTSTR*/
	const TCHAR *cmdCodeStr;//命令符，
							//当命令符为CTRL_DEVCMD_ST时,表示设备命令,lpDat[0]则为命令码0x80 ~ 0x9f
	const BYTE *lpDat;		//设备请求数据
	WORD datLen;			//数据长度
}DEVREQ_INFO;


typedef struct _DEVACK_INFO2 {
	BYTE *lpBuf;		//用户数据缓冲
	DWORD bufLen;		//缓冲大小
	DWORD datIdx;		//数据长度

	BYTE devPktBuf[512];	//设备返回的

	WORD pktDatLen;
	BYTE ackCode;			//应答码,0表示成功
}DEVACK_INFO2;

typedef struct _DEVREQ_INFO2 {
	const TCHAR *cmdCodeStr;//命令符，
							//当命令符为CTRL_DEVCMD_ST时,表示设备命令,lpDat[0]则为命令码0x80 ~ 0x9f
	BYTE *lpDat;		//设备请求数据
	DWORD datLen;			//数据长度
	DWORD datIdx;
	BYTE devPktBuf[512];	//设备数据包
	WORD pktDatLen;
}DEVREQ_INFO2;

#define RAWMODE_DEV_REQ			0x01	//解析成设备请求
#define RAWMODE_DEV_RESP		0x02	//解析设备响应数据
#define RAWMODE_DEV_CFGXML		0x03	//加载XML
#define RAWMODE_DEV_CFGDAT		0x04	//加载设备配置数据
#define RAWMODE_DEV_MKCFGDAT	0x05	//形成设备配置数据

//--------portMode---------------
#define PORTINFO_PMODE_DATA		0x01
#define PORTINFO_PMODE_CTRL		0x02

#define PORTINFO_PMODE_ALL		0x03

typedef struct _PORTINFO {
	//LPCTSTR	path;
	const TCHAR *path;
	LONG readTimeout;
	LONG writeTimeout;

	WORD portType;	//用于指定path代表的设备类型
	WORD portMode;	//指定需要打开设备的端口，包括数据口和控制口。
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
#define DFU_TAG_RESTART		(0x01)	//更新后重启设备

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

#define XML_ITEM_NAME		_T("Name")	//子项名不能相同
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
#define ITEMFMT_TAG_LH		(0x0001)	// 数据值的存放方式为低位在前，高位在后(2byte,4byte)
#define ITEMFMT_TAG_HEX		(0x0002)	// 数据值以十六进制数据格式存放

//---------------------------------------------------------
#define CFGPKT_MAXLEN		4096	// 配置包的最大长度(bytes)
#define CFGITEM_VAL_MAXLEN	1024	//　配置项的数据值的最大长度(bytes)

#define CFGITEM_VAL_NONE	0
#define CFGITEM_VAL_LONG	1
#define CFGITEM_VAL_STR		2

//----------------设备静态属性信息-------------------
#define DEVINFO_TYPE_NONE		0
#define	DEVINFO_TYPE_GEN		0x01	//通用信息
#define DEVINFO_TYPE_PORT		0x02	//设备的接口信息
#define DEVINFO_TYPE_PAGE		0x03	//页面信息
#define DEVINFO_TYPE_MEDIA		0x04	//打印输出信息
#define DEVINFO_MAX_TYPE		DEVINFO_TYPE_MEDIA

//大端格式
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
	//设备型号;序列号;通讯版本号;固件版本号;主板编号;备注;
	u8 info_desc[1];	//240
}DSEMUL_DEVINFO_GEN;

typedef struct _DSEMUL_DEVINFO_PORT {
	u8 size;
	u8 itemType;		//	DSEMUL_DEVINFO_PORT
	u8 recvBufSize[4]; 	//
	u8 frameBufSize[4];	//size = 0表示支持帧传输

	u8 cmprType;		//帧传输有效时，才能使用压缩
}DSEMUL_DEVINFO_PORT;

//------------------
#define DEVINFO_DSBMP_NONE	0
#define DEVINFO_DSBMP_EN	1
//----bmpType-------------
#define BMP_RASTER_FMT	(1)	//光栅位图
#define BMP_24PRN_FMT	(2)
typedef struct _DSEMUL_DEVINFO_PAGE {
	u8 size;
	u8 itemType;		//	DSEMUL_DEVINFO_PAGE
	u8 pageW[2]; 		//
	u8 pageH[2];		// size = 0表示支持帧传输
	u8 pMrg[4];			// 页面边界，左上右下
	u8 xDpi;
	u8 yDpi;
	u8 bpps;
	u8 bmpType;			//位图格式,光栅,24针打印
	u8 dsBmp;
}DSEMUL_DEVINFO_PAGE;
typedef struct _DSEMUL_DEVINFO_MEDIA {
	u8 size;
	u8 itemType;		//	DSEMUL_DEVINFO_MEDIA

}DSEMUL_DEVINFO_MEDIA;

//-------设备运行时的系统参数属性----------------
#define BMP_DEVPROP_NONE		0xff
#define BMP_DEVPROP_PRN			0x81	//print out param
#define SYS_MAX_PARAMPROP		BMP_DEVPROP_PRN

//-------系统状态--------------------------
#define DEVSTAT_TYPE_GEN	0x30	//系统状态
#define	DEVSTAT_TYPE_FAULT	0x31	//系统异常状态
#define DEVSTAT_TYPE_PROC	0x32	//数据处理
#define DEVSTAT_TYPE_PRNOUT	0x33	//机械控制/传感器状态
#define DEVSTAT_TYPE_PORT	0x34	//数据接收、发送状态

//-------GEN_STAT------------
#define GEN_SYSSTAT_IDLE	0	//空闲，等待指令
#define GEN_SYSSTAT_WORKING	1	//处理数据
#define GEN_SYSSTAT_READY	2	//就绪
#define GEN_SYSSTAT_BUSY	3	//数据将满
#define GEN_SYSSTAT_PAUSE	4	//暂停

#define GEN_SYSSTAT_ERR		0xff//异常

typedef struct _DSEMUL_GEN_STAT {
	u8 size;
	u8 itemType;	//	DEVSTAT_TYPE_GEN
	u8 sysStat;		// 系统运行状态
	u8 errCode[2];	//错误号
}DSEMUL_GEN_STAT;

typedef struct _DSEMUL_FAULT_STAT {
	u8 size;
	u8 itemType;	//	DEVSTAT_TYPE_FAULT
	u8 faultNo;		//

}DSEMUL_FAULT_STAT;
typedef struct _DSEMUL_PROC_STAT {
	u8 size;
	u8 itemType;	//	DEVSTAT_TYPE_PROC

	u8 procStat;	// 数据处理状态
	u8 jobNumber[2];	//作业号
	u8 frmIdx[2];		//作业中的索引号

	u8 errCode;
}DSEMUL_PROC_STAT;
typedef struct _DSEMUL_PRNOUT_STAT {
	u8 size;
	u8 itemType;		//	DEVSTAT_TYPE_PROC
	u8 prnStat;			//
	u8 qCnts;			//打印任务数

	u8 jobNumber[2];	//作业号
	u8 frmIdx[2];		//作业中的索引号
	u8 temp;			//打印头温度，-1 表示失败
	u8 sensor[4];
}DSEMUL_PRNOUT_STAT;
typedef struct _DSEMUL_PORT_STAT {
	u8 size;
	u8 itemType;		//	DEVSTAT_TYPE_PORT

	u8 portStat;		//
	u8 recvRate[2];		//接收缓冲的数据比例(千分比)
	u8 recvSpace[4];	//接收缓冲的剩余空间
	u8 sendDats[4];
}DSEMUL_PORT_STAT;

//-------设备运行时的系统参数属性----------------
#define BMP_DEVPROP_NONE		0xff
#define BMP_DEVPROP_PRN			0x81	//print out param
#define SYS_MAX_PARAMPROP		BMP_DEVPROP_PRN

#define BMP_DEVPROP_BKNONE	0	//不擦除背景
#define BMP_DEVPROP_BKFULL	1	//卡片全部擦除
#define	BMP_DEVPROP_BKBMP	2	//按前景位图大小擦除
#define	BMP_DEVPROP_BKUSER	3	//按用户自定的位图擦除

#define BMP_DEVPROP_PMODE_PRINT		0	//打印且擦除
#define BMP_DEVPROP_PMODE_ERASE		1	//只擦除
#define	BMP_DEVPROP_PMODE_PRNONLY	2	//只打印

#define BMP_DEVPROP_NONE		0xff
#define BMP_DEVPROP_PRN			0x81	//print out param
#define SYS_MAX_PARAMPROP		BMP_DEVPROP_PRN
typedef struct _DEVPROP_PRNOUT {
	u8	propSize;	//结构体的大小

	u8	devType;	//BMP_DEVPROP_PRN
	u8	bkBmpID;	//BMP_DEVPROP_BKNONE
	u8	cardType;	// 卡类型 -- 0:mblack, 1:mblue,2:rblack
	u8	cardInputMode;// 进卡方式 -- 0:AutoFeed, 1:manual Feed , 2:Auto Select
	u8	cardOutputMode;// 出卡方式 -- 0:装卡盒接收,1:手动接收,2:后退卡,3:不退卡
	u8	printTemp;	// 打印温度 -- 0 <= t <= 20
	u8	printContrast;// 打印对比度 -- 0 <= t <= 20
	u8	printSpeed;	// 打印速度 -- 0 <= s <= 20
	u8	grayTemp;	// 灰度温度 -- 0 <= t <= 20
	u8	graySpeed;	// 擦除速度 -- 0 <= s <= 20
	u8	eraseTemp;	// 设置擦除温度 -- 0 <= t <= 20
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
	u16	dpi;	//打印设备最大dpi
	u16	posX;	//左上角坐标
	u16	posY;

	u16	pixelW;
	u16 txPixelH;	//前景位图高
	u16 bkPixelH;	//背景位图高
	u8	bpps;		//像素颜色深度(bits)
	u8 bmpType;	//设备位图类型，1：光栅位图
	u8	revs[4];

	DEVPROP_INFO devInfo;
	u8 BmpDats[1];	//前景和背景位图数据
}DEV_BMP;

typedef struct _UNCMPR_INFO {
	u32 cmprLen;			//压缩数据长度
	u32	uncmprLen;			//解压后的数据长度
	u32 resultTag;			//
	u32 stat;
	u16	jobNumber;
	u16	frmIdx;
	u8 cmprType;			//压缩类型
	void *userParm;
}UNCMPR_INFO;

#endif

