#include "stdafx.h"
#include "WDevIO.h"

BOOL CWDevIO::wrIOToDev(const BYTE *lpDat,DWORD datLen, DWORD & itemID, HWND hWnd, BOOL buffMode)
{
	DEVIO_ITEM item;
	
	DBG_ASSERT(lpDat && datLen);
	
	if (this->pHandle == INVALID_PORT_HANDLE)
		return FALSE;

	memset((void*)&item, 0, sizeof(item));

	item.lpDats = lpDat;
	item.datLen = datLen;
	item.itemID = this->ItemNo;
	item.hWnd = hWnd;

	if (!wrQueue.addItem(&item,buffMode))
	{
		return FALSE;
	}
	
	this->openQueue(DEVIO_WRITE_QUE);

	this->ItemNo++;
	
	return this->openQueue(DEVIO_WRITE_QUE);
}

BOOL CWDevIO::openQueue(BYTE rdWr)
{
	BOOL retVal = TRUE;

	if ((rdWr & DEVIO_WRITE_QUE) && !this->hWrThread)
	{
		this->hWrThread = CreateThread(NULL, 0, this->wrThreadProc,	
			(void*)this, 0, &this->wrThrdID);
		this->wrThrdExit = FALSE;
		retVal = this->hWrThread ? TRUE : FALSE;
	}
	if ((rdWr & DEVIO_READ_QUE) && !this->hRdThread)
	{
		this->hRdThread = CreateThread(NULL, 0, this->rdThreadProc,
			(void*)this, 0, &this->rdThrdID);
		this->rdThrdExit = FALSE;
		retVal = (retVal && this->hRdThread) ? TRUE : FALSE;
	}
	return retVal;
}

BOOL CWDevIO::closeQueue(BYTE rdWr)
{
	if ((rdWr & DEVIO_WRITE_QUE) && this->hWrThread)
	{
		this->wrThrdExit = TRUE;
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(this->hWrThread, 5000)) //INFINITE))//;
		{
			//this->appendLogMsg(_T("更 新 线 程 正 常 关 闭"));
		} else if (TerminateThread(this->hWrThread, -1))
		{
			//this->appendLogMsg(_T("更 新 线 程 异 常 关 闭"));
		} else
		{
			//this->appendLogMsg(_T("更 新 线 程 无 法 关 闭"));
		}
		if (this->hWrThread)
		{
			CloseHandle(this->hWrThread);
			this->hWrThread = NULL;
		}
		this->wrThrdExit = FALSE;
	}
	if ((rdWr & DEVIO_READ_QUE) && this->hRdThread)
	{
		this->rdThrdExit = TRUE;
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(this->hRdThread, 8000)) //INFINITE))//;
		{
			//this->appendLogMsg(_T("更 新 线 程 正 常 关 闭"));
		} else if (TerminateThread(this->hRdThread, -1))
		{
			//this->appendLogMsg(_T("更 新 线 程 异 常 关 闭"));
		} else
		{
			//this->appendLogMsg(_T("更 新 线 程 无 法 关 闭"));
		}
		if (this->hRdThread)
		{
			CloseHandle(this->hRdThread);
			this->hRdThread = NULL;
		}
		this->rdThrdExit = FALSE;
	}

	return 0;
}

DWORD CWDevIO::wrThreadProc(void * param)
{
	CWDevIO *lpObj = reinterpret_cast<CWDevIO*>(param);
	LPDEVIO_ITEM lpItem = NULL;
	LPBYTE lpD;
	static DEVIO_MSG devIOmsg;
	int len = 0;
	DWORD num;
	BOOL postFlag = FALSE;

	devIOmsg.stat = 0;
	while (!lpObj->wrThrdExit)
	{
		lpItem = (LPDEVIO_ITEM)lpObj->wrQueue;
		if (lpItem && lpItem->hWnd && !postFlag)
		{
			devIOmsg.datsCnts = lpItem->datLen;
			devIOmsg.datsIdx = lpItem->datIdx;
			devIOmsg.itemID = lpItem->itemID;
			::PostMessage(lpItem->hWnd, WDEVIO_MSG, 0, (LPARAM)&devIOmsg);
			postFlag = TRUE;
			
		}
		
		if (devIOmsg.stat)
			break;

		len = lpObj->wrQueue.getItemDats(lpD, NULL);
		if(len > 0)
		{
			//if (len > 0x4000)	//一次发送的数据不能太大,否则容易超时.
				//len = 0x4000;

			if (lpObj->Write(lpD, len, &num, NULL))
			{
				lpObj->wrQueue.outItemDats(num);
				
			} else
			{
				devIOmsg.stat = 1;
			}
			postFlag = FALSE;
		} else if (len == -1)
		{ // queue empty
			break;
		}else //if (len == -3 )
		{ // no more data,get next item
			if (!lpObj->wrQueue.actItem(ACT_IOITEM_NEXT))
				break;
		}
	}
	
	if(lpObj->hWrThread)
	{
		CloseHandle(lpObj->hWrThread);
		lpObj->hWrThread = NULL;
	}
	return lpObj->wrThrdID;
}

DWORD CWDevIO::rdThreadProc(void * param)
{
	return 0;
}
