#pragma once

// ------tag--------
#define DEVCFG_FMT_INFO		0x00
#define DEVCFG_VAL_INFO		0x01

#ifdef _USRDLL
#define DllExport   __declspec( dllexport )
#define DllExport_C_STDCALL(type)	extern "C" DllExport type __stdcall
DllExport_C_STDCALL(BOOL)
dllFunc_OpenLog(LPCTSTR filePath);
#else
#include "WDevDef.h"
extern "C"
{
#define DllImport_C_STDCALL(type,funcName)	 type (__stdcall *funcName)
#define DLLImport_FUNC(hLib,fName) (fName)GetProcAddress(hLib, #fName)
/* 枚举设备的路径
输入 --
	portType	: 设备端口类型
			包括 - HID_PORT、USBPRN_PORT、NET_PORT、NET_CPORT、NET_DPORT
	pathStr		: 路径缓冲
	sizes		: 缓冲大小，字符单位
	vID			: 枚举相同的vID，0表示任意。
	pID			: 同vID
输出 --
	pathStr 	: 路径字符，已多字符串的形式存放，字符串之间以0分割，以00结束
	sizes		: 路径字符的总长度，字符单位，含结束00
返回 --
	0表示失败，非0表示枚举到的路径数；
注:
	当枚举网络设备(NET_PORT、NET_CPORT、NET_DPORT)时,vID用于设置设备的UDP端口号。
*/
typedef DllImport_C_STDCALL(WORD, dllFunc_EnumDevPath)(WORD portType, OUT LPTSTR pathStr,IN OUT DWORD &sizes,WORD vID,WORD pID);

typedef DllImport_C_STDCALL(LPCTSTR, dllFunc_EnumProtoCode)(WORD idx,WORD &code);

/* 打开设备端口
输入 --
	lpInfo		: 设备端口信息
返回 --
	成功则返回端口句柄,否则返回INVLAID_PORT_HANDLE；
注:
	最多可以同时打开10个设备端口，一个有效的句柄代表一个设备端口。
	可以设置PORTINFO中portMode为控制端口PORTINFO_PMODE_CTRL、数据端口PORTINFO_PMODE_DATA或两者同时有效的方式打开设备。
*/
typedef DllImport_C_STDCALL(PORT_HANDLE, dllFunc_OpenDev)(CONST LPPORTINFO lpInfo);

/* 打开设备控制数据
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	ctrlCode	: 设备提供的控制功能码。
	inDats		: 命令码所携带的数据。
	inLen		: 携带的数据长度，字节单位。
输出 --
	outDats		: 设备执行控制码时，设备的应答数据。
返回 --
	成功则TRUE,否则FALSE；
注:
	必须打开设备的控制端口。
	当ctrlCodeStr为“CTRL_DEVCMD_ST”，inDtas[0]的应为设备命令码。
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_DevIoCtrl)(PORT_HANDLE pHandle, LPCTSTR ctrlCodeStr, CONST BYTE *inDats, DWORD inLen, OUT DEVACK_INFO *outDats);

/* 写数据到设备的数据端口
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	inDats		: 需要写到设备的数据。
	inLen		: 数据长度，字节单位。
输出 --
	outLen		: 实际写到设备的数据长度。
返回 --
	成功则TRUE,否则FALSE；
注:
	必须打开设备的数据端口。
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_Write)(PORT_HANDLE pHandle, CONST BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd);

#define WREX_MODETAG_VERIFY	0x01	//检验数据帧的完整性，需要完整接受
#define WREX_MODETAG_BMP	0x02	//数据帧为设备位图
typedef DllImport_C_STDCALL(BOOL, dllFunc_WriteEx)(PORT_HANDLE pHandle, CONST BYTE *inDats, DWORD inLen, DWORD modeTag, OUT void *lpOut);

/* 读数据从设备的数据端口
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	inDats		: 需要接收设备数据的缓冲。
	inLen		: 缓冲长度，字节单位。
输出 --
	outLen		: 实际读到设备的数据长度。
返回 --
	成功则TRUE,否则FALSE；
注:
	必须打开设备的数据端口。
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_Read)(PORT_HANDLE pHandle, BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd);

/* 关闭设备端口
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
返回 --
	成功则TRUE,否则FALSE；
注:
	设备的数据/控制端口都将关闭，并释放设备句柄，如果有设备打开将重新被使用。
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_CloseDev)(PORT_HANDLE pHandle);

/* 获取端口的系统设备句柄
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	pType		: 端口类型，PORTINFO_PMODE_DATA表示数据端口，
						   PORTINFO_PMODE_CTRL表示控制端口。
返回 --
	INVALID_HANDLE_VALUE表示FALSE；
注:
*/
typedef DllImport_C_STDCALL(HANDLE, dllFunc_GetDevHandle)(PORT_HANDLE pHandle, WORD pType);

/* 启用设备日志
输入 --
	filePath	: 日志文件路径。
返回 --
	成功则TRUE,否则FALSE；
注:
	相同的日志路径，打开时将被覆盖。
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_OpenLog)(LPCTSTR filePath);

/* 输出字符信息到设备日志
输入 --
	str			: 字符信息。
	newLine		: TRUE表示添加换行到字符结尾。
	timeMode 	: 添加时间到字符的开头。
	saveEn		: TRUE表示将缓存的信息保存到日志文件中。
返回 --
	无
注:
*/
typedef DllImport_C_STDCALL(void, dllFunc_SetLogRecord)(LPCTSTR str, BOOL newLine, BOOL timeMode, BOOL saveEn);

/* 关闭设备日志
*/
typedef DllImport_C_STDCALL(void, dllFunc_CloseLog)(void);

/* 获取日志中的字符信息
输入 --
	reset	: TRUE表示清除记录缓存。
输出 --
	字符信息长度，字符数。
返回 --
	字符信息。
注:
*/
typedef DllImport_C_STDCALL(LPCTSTR, dllFunc_GetLogRecord)(DWORD &cnts,BOOL reset);

/* 启动固件更新
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	filePath	: 固件的文件路径。
	hWnd		: 接收固件更新消息的窗口句柄。
返回 --
	成功则TRUE,否则FALSE；
注:
	必须打开设备的控制端口。
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_OpenDfu)(PORT_HANDLE pHandle, LPCTSTR filePath,HWND hWnd);

/* 关闭固件更新
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
返回 --
	成功则TRUE,否则FALSE；
注:
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_CloseDfu)(PORT_HANDLE pHandle);

/* 获取固件信息
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	fwInfo		: 固件信息
	getMode		: TRUE表示从固件中获取，FALSE表示设置。
输出 --
	fwInfo		: getMode为TRUE时，获取的固件信息。
返回 --
	成功则TRUE,否则FALSE；
注:
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_fwInfo)(PORT_HANDLE pHandle, IN OUT DFU_FWINFO & fwInfo, BOOL getMode);

/* 开始固件更新
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	tags		: 标识
输出 --
	fwInfo		: getMode为TRUE时，获取的固件信息。
返回 --
	成功则TRUE,否则FALSE；
注:
	tags可按或(or)设置，包括 
		DFU_TAG_RESTART 表示更新后需启动设备
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_DFUStart)(PORT_HANDLE pHandle, DWORD tags);

/* 加载设备配置的格式信息
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	xmlPath		: 格式信息的文件路径 

返回 --
	成功则TRUE,否则FALSE；
注:
	格式信息以XML的格式表述，如果设备pHandle有效，则从设备中加载，此时设备应处于连接状态。
	否则从xmlPath中加载。	
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_LoadDevCfg)(PORT_HANDLE pHandle, LPCTSTR xmlPath);

/* 获取设备配置数据
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	lpParam		: 配置项 
	buf			: 数据缓冲
	cnts		: 缓冲长度，字符数
	tag			: 为DEVCFG_FMT_INFO表示获取格式信息，DEVCFG_VAL_INFO表示获取配置数据。
	noLoad		: 0表示从设备中加载所有配置数据。
返回 --
	成功则TRUE,否则FALSE；
注:
	当tag等于DEVCFG_FMT_INFO时，lpParam为指向(WORD*)的配置项索引号，tag等于DEVCFG_VAL_INFO时
	lpParam为指向字符串(LPCTSTR)的配置项名。
	返回FALSE时，如果cnts也为0表示超出配置项的范围获取失败，cnts不为0表示需要缓冲的长度。	
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_GetDevCfgInfo)(PORT_HANDLE pHandle,void* lpParam, OUT LPTSTR buf, IN OUT WORD &cnts, WORD tag, WORD noLoad);

/* 设置设备配置数据
输入 --
	pHandle		: 由dllFunc_OpenDev返回的设备端口句柄。
	name		: 配置项名称 
	val			: 数据值，以字符串形式表示。
	cnts		: 无效
	saveToDev	: 将配置数据发送到设备。
	
返回 --
	成功则TRUE,否则FALSE；
注:	
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_SetDevCfgInfo)(PORT_HANDLE pHandle,LPCTSTR name, LPCTSTR val, WORD cnts, WORD saveToDev);
}

/* 将用户数据解析成设备请求数据,或设备数据解析成用户数据
输入 -- 
	inDats	: 用户数据
	inLen	: 数据长度
	outDats	: 解析数据缓冲
	outLen	: IN为数据缓冲长度，OUT为数据长度
	modeTag	: 解析标识

注：
	modeTag为
	1、RAWMODE_DEV_REQ时,inDats应为指向DEVREQ_INFO的数据结构，outDats应为接收数据缓冲,outLen为数据长度。
	2、RAWMODE_DEV_RESP时,inDats为数据，inLen为数据长度，outDats应为DEVACK_INFO数据结构。
*/
//#define RAWMODE_DEV_REQ		0x01	//解析成设备请求
//#define RAWMODE_DEV_RESP		0x02	//解析设备响应数据
typedef DllImport_C_STDCALL(BOOL, dllFunc_devRawDats)(DEVREQ_INFO2 *inDat,DEVACK_INFO2 *outDats,DWORD modeTag);

//typedef DllImport_C_STDCALL(BOOL, dllFunc_devRawDats)(IN const void *inDat, WORD inLen, OUT void *outDats, IN OUT WORD &outLen, DWORD modeTag);




#define DLLFUNC(fName) dllFunc_##fName\
 fName

typedef struct _WDEVOBJ_FUNC {
	DLLFUNC(EnumDevPath);
	DLLFUNC(EnumProtoCode);
	DLLFUNC(OpenDev);
	DLLFUNC(CloseDev);
	DLLFUNC(GetDevHandle);
	DLLFUNC(DevIoCtrl);
	DLLFUNC(Write);
	DLLFUNC(WriteEx);
	DLLFUNC(Read);
	DLLFUNC(OpenLog);
	DLLFUNC(SetLogRecord);
	DLLFUNC(GetLogRecord);
	DLLFUNC(CloseLog);
	DLLFUNC(OpenDfu);
	DLLFUNC(CloseDfu);
	DLLFUNC(fwInfo);
	DLLFUNC(DFUStart);
	DLLFUNC(LoadDevCfg);
	DLLFUNC(GetDevCfgInfo);
	DLLFUNC(SetDevCfgInfo);
	DLLFUNC(devRawDats);
}WDEVOBJ_FUNC;

#endif
