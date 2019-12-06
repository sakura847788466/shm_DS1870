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
/* ö���豸��·��
���� --
	portType	: �豸�˿�����
			���� - HID_PORT��USBPRN_PORT��NET_PORT��NET_CPORT��NET_DPORT
	pathStr		: ·������
	sizes		: �����С���ַ���λ
	vID			: ö����ͬ��vID��0��ʾ���⡣
	pID			: ͬvID
��� --
	pathStr 	: ·���ַ����Ѷ��ַ�������ʽ��ţ��ַ���֮����0�ָ��00����
	sizes		: ·���ַ����ܳ��ȣ��ַ���λ��������00
���� --
	0��ʾʧ�ܣ���0��ʾö�ٵ���·������
ע:
	��ö�������豸(NET_PORT��NET_CPORT��NET_DPORT)ʱ,vID���������豸��UDP�˿ںš�
*/
typedef DllImport_C_STDCALL(WORD, dllFunc_EnumDevPath)(WORD portType, OUT LPTSTR pathStr,IN OUT DWORD &sizes,WORD vID,WORD pID);

typedef DllImport_C_STDCALL(LPCTSTR, dllFunc_EnumProtoCode)(WORD idx,WORD &code);

/* ���豸�˿�
���� --
	lpInfo		: �豸�˿���Ϣ
���� --
	�ɹ��򷵻ض˿ھ��,���򷵻�INVLAID_PORT_HANDLE��
ע:
	������ͬʱ��10���豸�˿ڣ�һ����Ч�ľ������һ���豸�˿ڡ�
	��������PORTINFO��portModeΪ���ƶ˿�PORTINFO_PMODE_CTRL�����ݶ˿�PORTINFO_PMODE_DATA������ͬʱ��Ч�ķ�ʽ���豸��
*/
typedef DllImport_C_STDCALL(PORT_HANDLE, dllFunc_OpenDev)(CONST LPPORTINFO lpInfo);

/* ���豸��������
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	ctrlCode	: �豸�ṩ�Ŀ��ƹ����롣
	inDats		: ��������Я�������ݡ�
	inLen		: Я�������ݳ��ȣ��ֽڵ�λ��
��� --
	outDats		: �豸ִ�п�����ʱ���豸��Ӧ�����ݡ�
���� --
	�ɹ���TRUE,����FALSE��
ע:
	������豸�Ŀ��ƶ˿ڡ�
	��ctrlCodeStrΪ��CTRL_DEVCMD_ST����inDtas[0]��ӦΪ�豸�����롣
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_DevIoCtrl)(PORT_HANDLE pHandle, LPCTSTR ctrlCodeStr, CONST BYTE *inDats, DWORD inLen, OUT DEVACK_INFO *outDats);

/* д���ݵ��豸�����ݶ˿�
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	inDats		: ��Ҫд���豸�����ݡ�
	inLen		: ���ݳ��ȣ��ֽڵ�λ��
��� --
	outLen		: ʵ��д���豸�����ݳ��ȡ�
���� --
	�ɹ���TRUE,����FALSE��
ע:
	������豸�����ݶ˿ڡ�
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_Write)(PORT_HANDLE pHandle, CONST BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd);

#define WREX_MODETAG_VERIFY	0x01	//��������֡�������ԣ���Ҫ��������
#define WREX_MODETAG_BMP	0x02	//����֡Ϊ�豸λͼ
typedef DllImport_C_STDCALL(BOOL, dllFunc_WriteEx)(PORT_HANDLE pHandle, CONST BYTE *inDats, DWORD inLen, DWORD modeTag, OUT void *lpOut);

/* �����ݴ��豸�����ݶ˿�
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	inDats		: ��Ҫ�����豸���ݵĻ��塣
	inLen		: ���峤�ȣ��ֽڵ�λ��
��� --
	outLen		: ʵ�ʶ����豸�����ݳ��ȡ�
���� --
	�ɹ���TRUE,����FALSE��
ע:
	������豸�����ݶ˿ڡ�
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_Read)(PORT_HANDLE pHandle, BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd);

/* �ر��豸�˿�
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
���� --
	�ɹ���TRUE,����FALSE��
ע:
	�豸������/���ƶ˿ڶ����رգ����ͷ��豸�����������豸�򿪽����±�ʹ�á�
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_CloseDev)(PORT_HANDLE pHandle);

/* ��ȡ�˿ڵ�ϵͳ�豸���
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	pType		: �˿����ͣ�PORTINFO_PMODE_DATA��ʾ���ݶ˿ڣ�
						   PORTINFO_PMODE_CTRL��ʾ���ƶ˿ڡ�
���� --
	INVALID_HANDLE_VALUE��ʾFALSE��
ע:
*/
typedef DllImport_C_STDCALL(HANDLE, dllFunc_GetDevHandle)(PORT_HANDLE pHandle, WORD pType);

/* �����豸��־
���� --
	filePath	: ��־�ļ�·����
���� --
	�ɹ���TRUE,����FALSE��
ע:
	��ͬ����־·������ʱ�������ǡ�
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_OpenLog)(LPCTSTR filePath);

/* ����ַ���Ϣ���豸��־
���� --
	str			: �ַ���Ϣ��
	newLine		: TRUE��ʾ��ӻ��е��ַ���β��
	timeMode 	: ���ʱ�䵽�ַ��Ŀ�ͷ��
	saveEn		: TRUE��ʾ���������Ϣ���浽��־�ļ��С�
���� --
	��
ע:
*/
typedef DllImport_C_STDCALL(void, dllFunc_SetLogRecord)(LPCTSTR str, BOOL newLine, BOOL timeMode, BOOL saveEn);

/* �ر��豸��־
*/
typedef DllImport_C_STDCALL(void, dllFunc_CloseLog)(void);

/* ��ȡ��־�е��ַ���Ϣ
���� --
	reset	: TRUE��ʾ�����¼���档
��� --
	�ַ���Ϣ���ȣ��ַ�����
���� --
	�ַ���Ϣ��
ע:
*/
typedef DllImport_C_STDCALL(LPCTSTR, dllFunc_GetLogRecord)(DWORD &cnts,BOOL reset);

/* �����̼�����
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	filePath	: �̼����ļ�·����
	hWnd		: ���չ̼�������Ϣ�Ĵ��ھ����
���� --
	�ɹ���TRUE,����FALSE��
ע:
	������豸�Ŀ��ƶ˿ڡ�
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_OpenDfu)(PORT_HANDLE pHandle, LPCTSTR filePath,HWND hWnd);

/* �رչ̼�����
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
���� --
	�ɹ���TRUE,����FALSE��
ע:
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_CloseDfu)(PORT_HANDLE pHandle);

/* ��ȡ�̼���Ϣ
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	fwInfo		: �̼���Ϣ
	getMode		: TRUE��ʾ�ӹ̼��л�ȡ��FALSE��ʾ���á�
��� --
	fwInfo		: getModeΪTRUEʱ����ȡ�Ĺ̼���Ϣ��
���� --
	�ɹ���TRUE,����FALSE��
ע:
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_fwInfo)(PORT_HANDLE pHandle, IN OUT DFU_FWINFO & fwInfo, BOOL getMode);

/* ��ʼ�̼�����
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	tags		: ��ʶ
��� --
	fwInfo		: getModeΪTRUEʱ����ȡ�Ĺ̼���Ϣ��
���� --
	�ɹ���TRUE,����FALSE��
ע:
	tags�ɰ���(or)���ã����� 
		DFU_TAG_RESTART ��ʾ���º��������豸
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_DFUStart)(PORT_HANDLE pHandle, DWORD tags);

/* �����豸���õĸ�ʽ��Ϣ
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	xmlPath		: ��ʽ��Ϣ���ļ�·�� 

���� --
	�ɹ���TRUE,����FALSE��
ע:
	��ʽ��Ϣ��XML�ĸ�ʽ����������豸pHandle��Ч������豸�м��أ���ʱ�豸Ӧ��������״̬��
	�����xmlPath�м��ء�	
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_LoadDevCfg)(PORT_HANDLE pHandle, LPCTSTR xmlPath);

/* ��ȡ�豸��������
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	lpParam		: ������ 
	buf			: ���ݻ���
	cnts		: ���峤�ȣ��ַ���
	tag			: ΪDEVCFG_FMT_INFO��ʾ��ȡ��ʽ��Ϣ��DEVCFG_VAL_INFO��ʾ��ȡ�������ݡ�
	noLoad		: 0��ʾ���豸�м��������������ݡ�
���� --
	�ɹ���TRUE,����FALSE��
ע:
	��tag����DEVCFG_FMT_INFOʱ��lpParamΪָ��(WORD*)�������������ţ�tag����DEVCFG_VAL_INFOʱ
	lpParamΪָ���ַ���(LPCTSTR)������������
	����FALSEʱ�����cntsҲΪ0��ʾ����������ķ�Χ��ȡʧ�ܣ�cnts��Ϊ0��ʾ��Ҫ����ĳ��ȡ�	
*/
typedef DllImport_C_STDCALL(BOOL,dllFunc_GetDevCfgInfo)(PORT_HANDLE pHandle,void* lpParam, OUT LPTSTR buf, IN OUT WORD &cnts, WORD tag, WORD noLoad);

/* �����豸��������
���� --
	pHandle		: ��dllFunc_OpenDev���ص��豸�˿ھ����
	name		: ���������� 
	val			: ����ֵ�����ַ�����ʽ��ʾ��
	cnts		: ��Ч
	saveToDev	: ���������ݷ��͵��豸��
	
���� --
	�ɹ���TRUE,����FALSE��
ע:	
*/
typedef DllImport_C_STDCALL(BOOL, dllFunc_SetDevCfgInfo)(PORT_HANDLE pHandle,LPCTSTR name, LPCTSTR val, WORD cnts, WORD saveToDev);
}

/* ���û����ݽ������豸��������,���豸���ݽ������û�����
���� -- 
	inDats	: �û�����
	inLen	: ���ݳ���
	outDats	: �������ݻ���
	outLen	: INΪ���ݻ��峤�ȣ�OUTΪ���ݳ���
	modeTag	: ������ʶ

ע��
	modeTagΪ
	1��RAWMODE_DEV_REQʱ,inDatsӦΪָ��DEVREQ_INFO�����ݽṹ��outDatsӦΪ�������ݻ���,outLenΪ���ݳ��ȡ�
	2��RAWMODE_DEV_RESPʱ,inDatsΪ���ݣ�inLenΪ���ݳ��ȣ�outDatsӦΪDEVACK_INFO���ݽṹ��
*/
//#define RAWMODE_DEV_REQ		0x01	//�������豸����
//#define RAWMODE_DEV_RESP		0x02	//�����豸��Ӧ����
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
