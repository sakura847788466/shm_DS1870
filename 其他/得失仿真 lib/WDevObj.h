#ifndef _DEVOBJ_H_
#define _DEVOBJ_H_

#include "WDevDef.h"
#ifdef _USRDLL
#undef _USRDLL
#endif
#include "WDevDll.h"

#define DBG_ASSERT	_ASSERT

/* 数据采集时的消息事件
WPARAM ==	0 :表示接收到采样数据
			1 :表示采样结束
LPARAM == 指向DEVACK_INFO的指针
		WPARAM为0时，DEVACK_INFO中lpBuf为收到的数据，datLen为数据长度。
		WPARAM为1时，lpBuf为指向SMPL_INFO的指针表示采样到的数据长度和校验码。
*/
#define WDEV_DUMP_MSG (WM_USER + 0x101)
	
	
/* 发送/接收数据的消息事件
*/
#define WDEV_DATA_MSG (WM_USER + 0x102)

class CWDevObj{
public:
	CWDevObj() : pHandle(INVALID_PORT_HANDLE)
			   , hPThread(NULL)

	{
	}

	virtual ~CWDevObj()
	{
		this->closeRun();
		/*if(this->hinstLib)
		{
			::FreeLibrary(this->hinstLib);
			CWDevObj::hinstLib = NULL;
		}*/
	};
	inline void attach(PORT_HANDLE p);
	inline void detach(void);
	inline PORT_HANDLE getHandle() { return this->pHandle; }
	static BOOL initClass(LPCTSTR dllpath = NULL);
	static BOOL uinitClass();
	
	inline WORD EnumDevPath(WORD portType, OUT LPTSTR pathStr, IN OUT DWORD &sizes,WORD vID,WORD pID);
	inline LPCTSTR EnumProtoCode(WORD idx,WORD &code);
	inline PORT_HANDLE OpenDev(CONST LPPORTINFO lpInfo);
	//inline 
	/* reqMode = 0 : 从设备中获取数据,
				RAWMODE_DEV_REQ : 转换为设备数据
				RAWMODE_DEV_RESP : 转换为用户数据
	*/
	BOOL DevIoCtrl(LPCTSTR codeStr, CONST BYTE *inDats, DWORD inLen, OUT DEVACK_INFO *outDats);
	inline BOOL Write(CONST BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd = NULL);
	inline BOOL WriteEx(CONST BYTE *inDats, DWORD inLen, DWORD modeTag, OUT void *lpOut = NULL);
	inline BOOL Read( BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd = NULL);
	inline BOOL CloseDev(void);
	inline HANDLE GetDevHandle(WORD pType = PORTINFO_PMODE_DATA);
	inline BOOL OpenLog(LPCTSTR filePath);
	inline void SetLogRecord(LPCTSTR str, BOOL newLine, BOOL timeMode, BOOL saveEn = FALSE);
	inline void CloseLog(void);
	inline LPCTSTR GetLogRecord(DWORD &cnts,BOOL reset);
	inline BOOL OpenDfu(LPCTSTR filePath,HWND hWnd);
	inline BOOL CloseDfu(void);
	inline BOOL fwInfo(DFU_FWINFO & fwInfo, BOOL getMode);
	inline BOOL DFUStart(DWORD tag = 0);
	inline BOOL LoadDevCfg(LPCTSTR xmlPath);
	inline BOOL GetDevCfgInfo(void *lpParam, LPTSTR buf, IN OUT WORD &cnts, WORD tag,WORD noLoad);
	inline BOOL SetDevCfgInfo(LPCTSTR name, LPCTSTR val,WORD cnts, WORD saveToDev);
	inline BOOL devRawDats(DEVREQ_INFO2 *reqDat, DEVACK_INFO2 *ackDats, DWORD reqMode);

	static LPCTSTR getDevCmdStr(WORD idx);

	const BYTE* sendDevCmdReq(LPCTSTR cmdCodeStr,
		const BYTE * cmdDats, WORD datLen, WORD &ackLen, BYTE *errCode = NULL);
protected:
	
protected:
	
	CWDevObj(const CWDevObj&) {};   
	CWDevObj &operator= (const CWDevObj&) {};  

	BOOL startRun();
	void closeRun();
	virtual BOOL runProc();

	static BOOL loadLib(LPCTSTR path);	
	BOOL isThrdExit() { return this->thrdExit; }
protected:	
	static HINSTANCE hinstLib;
	static WDEVOBJ_FUNC wDevObj_func;
	PORT_HANDLE pHandle;

private:

	DWORD	threadID;
	HANDLE	hPThread;
	BOOL	thrdExit;
	
	BYTE ackBuf[HCTRL_CMD_DATLEN];

	static DWORD WINAPI threadProc(void *param);
};


inline void CWDevObj::attach(PORT_HANDLE p)
{
	DBG_ASSERT(this->pHandle == INVALID_PORT_HANDLE);

	this->pHandle = p;
}
inline void CWDevObj::detach(void)
{
	this->pHandle = INVALID_PORT_HANDLE;
}
inline WORD CWDevObj::EnumDevPath(WORD portType, OUT LPTSTR pathStr, IN OUT DWORD &sizes,WORD vID,WORD pID)
{
	return wDevObj_func.EnumDevPath ? 
		wDevObj_func.EnumDevPath(portType, pathStr, sizes,vID,pID) : 0;
}
inline LPCTSTR CWDevObj::EnumProtoCode(WORD idx,WORD &code)
{
	return wDevObj_func.EnumProtoCode ? 
		wDevObj_func.EnumProtoCode(idx, code) : NULL;
}
inline PORT_HANDLE CWDevObj::OpenDev(CONST LPPORTINFO lpInfo)
{
	if (wDevObj_func.OpenDev)
	{
		this->pHandle = wDevObj_func.OpenDev(lpInfo);
		return this->pHandle;
	}
	return INVALID_PORT_HANDLE;
}

inline BOOL CWDevObj::DevIoCtrl( LPCTSTR codeStr, CONST BYTE *inDats, DWORD inLen, OUT DEVACK_INFO *outDats)
{
	return (wDevObj_func.DevIoCtrl && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.DevIoCtrl(this->pHandle, codeStr, inDats, inLen,outDats) : FALSE;
}
inline BOOL CWDevObj::Write(CONST BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd)
{
	return (wDevObj_func.Write && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.Write(this->pHandle, inDats, inLen, outLen, lpOvlpd) : FALSE;
}
inline BOOL CWDevObj::WriteEx(CONST BYTE *inDats, DWORD inLen, DWORD modeTag, OUT void *lpOut)
{
	return (wDevObj_func.WriteEx) ?
		wDevObj_func.WriteEx(this->pHandle, inDats, inLen, modeTag, lpOut) : FALSE;
}
inline BOOL CWDevObj::Read(BYTE *inDats, DWORD inLen, OUT DWORD *outLen, OVERLAPPED *lpOvlpd)
{
	return (wDevObj_func.Read && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.Read(this->pHandle, inDats, inLen, outLen, lpOvlpd) : FALSE;
}
inline BOOL CWDevObj::CloseDev()
{
	BOOL retVal = FALSE;
	if (wDevObj_func.CloseDev && this->pHandle != INVALID_PORT_HANDLE)
	{
		retVal = wDevObj_func.CloseDev(this->pHandle);
		this->pHandle = INVALID_PORT_HANDLE;
	}
	return retVal;
}
inline HANDLE CWDevObj::GetDevHandle(WORD pType)
{
	return  (wDevObj_func.GetDevHandle && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.GetDevHandle(this->pHandle, pType) : INVALID_HANDLE_VALUE;
}
inline BOOL CWDevObj::OpenLog(LPCTSTR filePath)
{
	return wDevObj_func.OpenLog ? 
		wDevObj_func.OpenLog(filePath) : FALSE;
}
inline void CWDevObj::SetLogRecord(LPCTSTR str, BOOL newLine, BOOL timeMode, BOOL saveEn)
{
	if(wDevObj_func.SetLogRecord)
		wDevObj_func.SetLogRecord(str, newLine, timeMode,saveEn);
}
inline void CWDevObj::CloseLog()
{
	if( wDevObj_func.CloseLog) 
		wDevObj_func.CloseLog();
}
inline LPCTSTR CWDevObj::GetLogRecord(DWORD &cnts,BOOL reset)
{
	return wDevObj_func.GetLogRecord ? 
		wDevObj_func.GetLogRecord(cnts, reset) : NULL;
}
inline BOOL CWDevObj::OpenDfu(LPCTSTR filePath,HWND hWnd)
{
	return (wDevObj_func.OpenDfu && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.OpenDfu(this->pHandle,filePath,hWnd) : FALSE;
}
inline BOOL CWDevObj::CloseDfu(void)
{
	return (wDevObj_func.CloseDfu && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.CloseDfu(this->pHandle) : FALSE;
}
inline BOOL CWDevObj::fwInfo(DFU_FWINFO & fwInfo, BOOL getMode)
{
	return (wDevObj_func.fwInfo && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.fwInfo(this->pHandle, fwInfo, getMode) : FALSE;
}
inline BOOL CWDevObj::DFUStart(DWORD tag)
{
	return (wDevObj_func.DFUStart && this->pHandle != INVALID_PORT_HANDLE) ?
		wDevObj_func.DFUStart(this->pHandle,tag) : FALSE;
}

inline BOOL CWDevObj::LoadDevCfg(LPCTSTR xmlPath)
{
	return wDevObj_func.LoadDevCfg ?
		wDevObj_func.LoadDevCfg(this->pHandle,xmlPath) : FALSE;
}

inline BOOL CWDevObj::GetDevCfgInfo(void* lpParam, LPTSTR buf, IN OUT WORD & cnts, WORD tag,WORD noLoad)
{
	return (wDevObj_func.GetDevCfgInfo) ?
		wDevObj_func.GetDevCfgInfo(this->pHandle, lpParam, buf, cnts, tag,noLoad) : FALSE;
}

inline BOOL CWDevObj::SetDevCfgInfo(LPCTSTR name, LPCTSTR val, WORD cnts, WORD saveToDev)
{
	return (wDevObj_func.GetDevCfgInfo) ?
		wDevObj_func.SetDevCfgInfo(this->pHandle, name, val, cnts, saveToDev) : FALSE;
}

inline BOOL CWDevObj::devRawDats(DEVREQ_INFO2 * inDat, DEVACK_INFO2 * outDats, DWORD modeTag)
{
	return (wDevObj_func.devRawDats) ?
		wDevObj_func.devRawDats(inDat, outDats, modeTag) : FALSE;
}

#endif