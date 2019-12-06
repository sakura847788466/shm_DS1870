#include "stdafx.h"
#include "WDevObj.h"

HINSTANCE CWDevObj::hinstLib = NULL;
WDEVOBJ_FUNC CWDevObj::wDevObj_func;

BOOL CWDevObj::initClass(LPCTSTR dllpath)
{
	if (!CWDevObj::hinstLib)
	{
		TCHAR mStr[MAX_PATH] = {_T('\0')};
		if (dllpath)
		{
			PathAppend(mStr,dllpath);
		}

		if (S_OK != ::CoInitializeEx(NULL, COINIT_MULTITHREADED))
		{
			//CFG_LOGMSG_F(_T("CoInitializeEx Fail\r\n"));
		}

		if(PathAppend(mStr, _T("WDevObj.dll")))
			return CWDevObj::loadLib(mStr);
	}

	return FALSE;
}
BOOL CWDevObj::uinitClass()
{
	if (CWDevObj::hinstLib)
	{
		::CoUninitialize();

		::memset(&wDevObj_func, 0, sizeof(wDevObj_func));
	
		BOOL retVal = ::FreeLibrary(CWDevObj::hinstLib);
		CWDevObj::hinstLib = NULL;
		return retVal;
	}
	return TRUE;
}
BOOL CWDevObj::startRun()
{
	if (!this->hPThread)
	{
		this->hPThread = CreateThread(NULL, 0, this->threadProc,	//立即运行 CREATE_SUSPENDED 
										(void*)this, 0, &this->threadID);
		this->thrdExit = FALSE;
	}
	return this->hPThread ? TRUE : FALSE;
}
void CWDevObj::closeRun()
{
	if (!this->hPThread)
		return;
	
	this->thrdExit = TRUE;
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(this->hPThread, 5000)) //INFINITE))//;
	{
			//this->appendLogMsg(_T("更 新 线 程 正 常 关 闭"));
	} else if (TerminateThread(this->hPThread, -1))
	{
		//this->appendLogMsg(_T("更 新 线 程 异 常 关 闭"));
	} else
	{
		//this->appendLogMsg(_T("更 新 线 程 无 法 关 闭"));
	}

	if (this->hPThread)
	{
		CloseHandle(this->hPThread);
		this->hPThread = NULL;
	}
	this->thrdExit = FALSE;
}
BOOL CWDevObj::runProc()
{
	return 0;
}
BOOL CWDevObj::loadLib(LPCTSTR path)
{
	DBG_ASSERT(path);

	::memset(&wDevObj_func,0,sizeof(wDevObj_func));

	CWDevObj::hinstLib = LoadLibrary(path);//_T("WDevObj.dll"));
	if (!CWDevObj::hinstLib)
		return FALSE;
	
	wDevObj_func.EnumDevPath = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_EnumDevPath);
	wDevObj_func.EnumProtoCode = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_EnumProtoCode);
	wDevObj_func.OpenDev = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_OpenDev);
	wDevObj_func.CloseDev = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_CloseDev);
	wDevObj_func.GetDevHandle = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_GetDevHandle);
	wDevObj_func.DevIoCtrl = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_DevIoCtrl);
	wDevObj_func.Write = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_Write);
	wDevObj_func.WriteEx = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_WriteEx);
	wDevObj_func.Read = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_Read);
	wDevObj_func.OpenLog = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_OpenLog);
	wDevObj_func.SetLogRecord = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_SetLogRecord);
	wDevObj_func.GetLogRecord = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_GetLogRecord);
	wDevObj_func.CloseLog = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_CloseLog);
	wDevObj_func.OpenDfu = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_OpenDfu);
	wDevObj_func.CloseDfu = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_CloseDfu);
	wDevObj_func.fwInfo = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_fwInfo);
	wDevObj_func.DFUStart = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_DFUStart);
	wDevObj_func.LoadDevCfg = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_LoadDevCfg);
	wDevObj_func.GetDevCfgInfo = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_GetDevCfgInfo);
	wDevObj_func.SetDevCfgInfo = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_SetDevCfgInfo);
	wDevObj_func.devRawDats = DLLImport_FUNC(CWDevObj::hinstLib, dllFunc_devRawDats);
	//if (!wDevObj_func.OpenLog(_T("D:\\123")))
	{
		//TRACE(_T("OpenLog Fail\r\n"));
	}

	return TRUE;
}

DWORD CWDevObj::threadProc(void * param)
{
	CWDevObj *lpObj = reinterpret_cast<CWDevObj*>(param);
	DBG_ASSERT(lpObj);

	lpObj->runProc();

	if (!lpObj->isThrdExit())
	{
		CloseHandle(lpObj->hPThread);
		lpObj->hPThread = NULL;
	}
	
	return lpObj->threadID;
}
LPCTSTR CWDevObj::getDevCmdStr(WORD idx)
{
	static LPCTSTR cmdStr[] = {
		DEV_GET_MODEL,
		DEV_GET_DEVNO,
		DEV_GET_PROTVER,
		DEV_CMD_CONNT,
		DEV_CMD_UNCONNT,

		DEV_SET_PSW,
		DEV_GET_USERDAT,
		DEV_SET_USERDAT,
		DEV_GET_DEVSTAT,
		DEV_GET_PWSSTAT,
		DEV_SET_ENCRYPT,
		DEV_GET_DEVINFO,
		DEV_CMD_RESETCFG,
		DEV_CMD_CLSBUF,
		DEV_GET_STATISINFO,
		DEV_GET_MAINTAININFO,
		DEV_CMD_RESTART,
		DEV_CMD_CHKSLF,
		DEV_GET_WORKMODE,
		DEV_SET_WORKMODE,
		DEV_GET_VERINFO,

		DEV_GET_CFGINFOS,
		DEV_SET_CFGINFOS,
		DEV_GET_CFGFMT,
		DEV_SET_SYSPARAM,
		DEV_GET_SYSPARAM,
		DEV_SET_OPER,

		DEV_CMD_CUSTOMIZE };

	if (idx < sizeof(cmdStr) / sizeof(*cmdStr))
		return cmdStr[idx];

	return NULL;
}
const BYTE* CWDevObj::sendDevCmdReq(LPCTSTR cmdCodeStr,
	const BYTE * cmdDats, WORD datLen, WORD &ackLen, BYTE *errCode)
{
	DEVACK_INFO ackInfo;

	DBG_ASSERT(this->pHandle != INVALID_PORT_HANDLE && cmdCodeStr);

	ackInfo.bufLen = sizeof(this->ackBuf);
	ackInfo.lpBuf = this->ackBuf;
	ackInfo.datLen = 0;
	ackInfo.ackCode = -1;

	if (errCode)
		*errCode = 0;

	if (this->DevIoCtrl(cmdCodeStr, cmdDats, datLen, &ackInfo))
	{
		if (!ackInfo.ackCode)
		{
			ackLen = ackInfo.datLen;
			return this->ackBuf;
		} else if ((ackInfo.ackCode == HCTRL_ERR_UNCONNT) && ::_tcscmp(cmdCodeStr, DEV_CMD_CONNT))
		{
			if (this->DevIoCtrl(DEV_CMD_CONNT, NULL, 0, &ackInfo))
			{
				if (!ackInfo.ackCode)
				{
					if (this->DevIoCtrl(cmdCodeStr, cmdDats, datLen, &ackInfo))
					{
						if (!ackInfo.ackCode)
						{
							ackLen = ackInfo.datLen;
							return this->ackBuf;
						}
					}
				}
			}
		}
	}

	if (errCode)
		*errCode = ackInfo.ackCode;

	return NULL;
}
/*
BOOL CWDevObj::DevIoCtrl(LPCTSTR codeStr, CONST BYTE *inDats, DWORD inLen, OUT DEVACK_INFO *outDats,DWORD reqMode)
{
//	DBG_ASSERT(codeStr);

	if(!reqMode)
	{
		return (wDevObj_func.DevIoCtrl && this->pHandle != INVALID_PORT_HANDLE) ? 
			wDevObj_func.DevIoCtrl(this->pHandle, codeStr, inDats, inLen, outDats) : FALSE;
	}

	if (!outDats)
		return FALSE;
	
	DEVREQ_INFO2 sDevDat;

	sDevDat.cmdCodeStr = codeStr;
	sDevDat.lpDat = inDats;
	sDevDat.datLen = inLen;

	return this->devRawDats(&sDevDat, outDats, reqMode);
	
}*/
