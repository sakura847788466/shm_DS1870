#include "stdafx.h"
#include "WDevDump.h"

BOOL CWDevDump::open(LPCTSTR path,HWND mWnd )
{
	DBG_ASSERT(path);
	
	if(this->fHandle != INVALID_HANDLE_VALUE)
		return FALSE;

	if (!this->devDumpMode())
		return FALSE;

	this->fHandle = ::CreateFile(path,
						GENERIC_WRITE,
						NULL,
						NULL,
						CREATE_ALWAYS , NULL, NULL);

	if(this->fHandle == INVALID_HANDLE_VALUE) 
		return FALSE ;
		
	this->hWnd = mWnd;
	if (!this->startRun())
	{
		::CloseHandle(this->fHandle);
		this->fHandle = INVALID_HANDLE_VALUE;
	}
	this->mSmplInfo.recvCnts = 0;
	this->mSmplInfo.chksum = 0;

	return TRUE;
}
void CWDevDump::close()
{
	this->closeRun();

	this->saveDump();

	if(this->fHandle != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(this->fHandle);
		this->fHandle = INVALID_HANDLE_VALUE;
	}
}

BOOL CWDevDump::runProc()
{
	int i;
	//HANDLE rdEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);


	this->dumpIdx = 0;
	while (!this->isThrdExit())
	{
		ackInfo.lpBuf = &this->dumpBuf[this->dumpIdx];
		ackInfo.bufLen = DUMP_BUF_LEN - this->dumpIdx;
		ackInfo.datLen = 0;

		if (this->DevIoCtrl(_T("WDEV_DUMP"), NULL, 0, &ackInfo))
		{
			if (ackInfo.datLen)
			{
				this->mSmplInfo.recvCnts += ackInfo.datLen;
				this->mSmplInfo.errCode = ackInfo.ackCode;
				if(this->hWnd)
					::PostMessage(this->hWnd, WDEV_DUMP_MSG, 0, (LPARAM)&this->mSmplInfo);

				this->dumpIdx += ackInfo.datLen;
				
				i = 0;
				while (i < ackInfo.datLen)
					this->mSmplInfo.chksum += ackInfo.lpBuf[i++];

				if ((this->dumpIdx + 512) > DUMP_BUF_LEN)
					this->saveDump();
			}
		}
	}

	this->saveDump();

	if (this->devDumpMode(TRUE))
	{	
		//ackInfo.lpBuf = (BYTE*)&this->mSmplInfo;
		//ackInfo.ackCode = 0;
	} else
	{
	}
		//ackInfo.ackCode = 1;

	if (this->hWnd)
		PostMessage(this->hWnd, WDEV_DUMP_MSG, 1, (LPARAM)&this->mSmplInfo);

	return TRUE;
}

BOOL CWDevDump::saveDump()
{
	DWORD num,i = 0;

	if (this->fHandle != INVALID_HANDLE_VALUE)
	{
		while(this->dumpIdx)
		{
			if (WriteFile(this->fHandle, &this->dumpBuf[i], this->dumpIdx, &num, NULL) && num)
			{
				this->dumpIdx -= num;
				i += num;
			} else
				break;
		}
	}

	this->dumpIdx = 0;
	return TRUE;
}

BOOL CWDevDump::devDumpMode(BOOL exitMode)
{
	DEVACK_INFO ackInfo;
	DWORD len, sum;
	BYTE n,buf[16];
	
	ackInfo.lpBuf = buf;
	ackInfo.bufLen = sizeof(buf);
	ackInfo.datLen = 0;
	this->mSmplInfo.errCode = 0x8000;

	n = exitMode ? DSINFO_MODE_NORMAL : DSINFO_MODE_SAMPLE;
	if (this->DevIoCtrl(_T("CTRL_CMDSET_WORKMODE"), &n, 1, &ackInfo))
	{
		if (!ackInfo.ackCode)
		{
			this->mSmplInfo.errCode = 0;
			if(exitMode)
			{
				if (ackInfo.datLen == 9)
				{
					len = HCTRL_GET_VAL32(&ackInfo.lpBuf[1]);
					sum = HCTRL_GET_VAL32(&ackInfo.lpBuf[5]);
					if (len == this->mSmplInfo.recvCnts &&
						sum == this->mSmplInfo.chksum)
						return TRUE;
				}
				return FALSE;
			}
			return TRUE;
		}
	}
	return FALSE;
}
