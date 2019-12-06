#include "stdafx.h"
#include "WDevCfg.h"


LPCTSTR CWDevCfg::getCfgItem(WORD idx,CString *valStr)
{
	POSITION pos = this->itemList.FindIndex(idx);

	if (pos)
	{
		CWDCfgItem *lpItem = &this->itemList.GetAt(pos);
		if (valStr)
			*valStr = lpItem->getItemVal(FALSE);
		return lpItem->getItemName();
	}

	return NULL;
}
CWDCfgItem * CWDevCfg::getCfgItemObj(WORD idx)
{
	POSITION pos = this->itemList.FindIndex(idx);

	if (pos)
	{
		return &this->itemList.GetAt(pos);
	}
	return NULL;
}
BOOL CWDevCfg::setCfgItem(WORD idx, LPCTSTR valStr)
{
	ASSERT(valStr);

	POSITION pos = this->itemList.FindIndex(idx);

	if (pos)
	{
		CWDCfgItem *lpItem = &this->itemList.GetAt(pos);
		return lpItem->setItemVal(valStr);
	}

	return FALSE;
}
#define HID_HS_PKTSIZE			(265)
#define HID_HS_REPORTID   		(0xa6)
BOOL CWDevCfg::transmitToDev(BYTE *datBuf, DWORD len,DWORD &realCnts,BYTE wrMode)
{
	HANDLE hPort = this->GetDevHandle(PORTINFO_PMODE_CTRL);
	OVERLAPPED mOverlapped;
	DWORD m, repeats = 0,timeout = 2000;
	BYTE  hid_dat[HID_HS_PKTSIZE];
	WORD n;

	realCnts = 0;
	if ((hPort == INVALID_HANDLE_VALUE) || !(datBuf && len))
		return FALSE;

	mOverlapped.Internal = 0;
	mOverlapped.InternalHigh = 0;
	mOverlapped.Offset = 0;
	mOverlapped.OffsetHigh = 0;
	mOverlapped.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!mOverlapped.hEvent)
		return FALSE;

	if (wrMode == 1)
	{
		hid_dat[0] = HID_HS_REPORTID;
		hid_dat[1] = 0;	//reverse
		n = (HID_HS_PKTSIZE - 4);
		if (len < n)
			n = len;
		hid_dat[2] = (BYTE)(n >> 8);
		hid_dat[3] = (BYTE)n;
		memcpy(&hid_dat[4], datBuf, n);

		if (WriteFile(hPort,
			hid_dat,
			HID_HS_PKTSIZE,
			&realCnts,
			&mOverlapped))
		{
			//nums = len;
			//::CloseHandle(mOverlapped.hEvent);
			goto HID_OK;
			//return TRUE;
		}
	} else if (wrMode == 0)
	{
		if (ReadFile(hPort,
			hid_dat,
			HID_HS_PKTSIZE,
			&realCnts,
			&mOverlapped))
		{

			//return TRUE;
			goto HID_OK;
		}
	}

WAIT_OBJ:
	m = WaitForSingleObjectEx(mOverlapped.hEvent, timeout, FALSE);

	if (m == WAIT_OBJECT_0)
	{
		if (GetOverlappedResult(hPort, &mOverlapped, &realCnts, FALSE))
		{
			if (!realCnts)
			{
				//DBG_TRACE(_T("SLDFJSLFJD\n"));
			}
			goto HID_OK;
			//return TRUE;
		}
	} else if (m == WAIT_FAILED)
	{
		//CBPORT_LOGMSG_F(_T("syncIOAccess WAIT_FAILED\r\n"));

	} else if (m == WAIT_TIMEOUT)
	{
		if ((wrMode == 1) && repeats < 3)
		{
			Sleep(100);
			repeats++;
			goto WAIT_OBJ;
		}
		//
		if (wrMode == 1)
		{
			
			//CBPORT_LOGMSG_F(_T("syncIOAccess write timeout \r\n"));
		}
	} else
	{
		//CBPORT_LOGMSG_F(_T("syncIOAccess fail 0x%x\r\n"), m);
	}

	::CloseHandle(mOverlapped.hEvent);

	::CancelIo(hPort);

	return FALSE;

HID_OK:
	if (!wrMode && realCnts)
	{
		n = (hid_dat[2] << 8) + hid_dat[3];
		if (n > len)
		{
			realCnts = 0;
			::CloseHandle(mOverlapped.hEvent);
			return FALSE;
		}
		memcpy(datBuf, &hid_dat[4], n);
		realCnts = n;
	}
	::CloseHandle(mOverlapped.hEvent);
	return TRUE;
}
#if 1
BOOL CWDevCfg::mkDevDats(LPCTSTR cmdStr, 
						BYTE *cmdParam, WORD dLen, 
						BYTE* ackBuf, WORD &ackLen,WORD mode)
{
	DWORD cnt;
	DEVREQ_INFO2 reqInfo;
	DEVACK_INFO2 ackInfo;
	BYTE cmdBuf[259],dats[259];
	
	reqInfo.cmdCodeStr = cmdStr;
	reqInfo.lpDat = cmdParam;
	reqInfo.datLen = dLen;
	reqInfo.datIdx = 0;

	if (mode == RAWMODE_DEV_CFGXML || mode == RAWMODE_DEV_CFGDAT)
	{
		return this->devRawDats(&reqInfo, NULL, mode);
	} else if(mode == RAWMODE_DEV_MKCFGDAT)
	{
		/*ackInfo.ackCode = 0;
		ackInfo.bufLen = ackLen;
		ackInfo.datIdx = 0;
		ackInfo.lpBuf = ackBuf;*/
		if(this->devRawDats(&reqInfo, NULL, mode))
		{
			ackLen = reqInfo.datLen;
			return TRUE;
		}
		return FALSE;
	}

	ackInfo.lpBuf = ackBuf;//cmdBuf;
	ackInfo.bufLen = ackLen;//sizeof(cmdBuf);
	ackInfo.datIdx = 0;
	
	if (!this->devRawDats(&reqInfo,NULL, RAWMODE_DEV_REQ))
		return FALSE;
	
	if (this->transmitToDev(reqInfo.devPktBuf, reqInfo.pktDatLen, cnt, 1))
	{
		if (this->transmitToDev(ackInfo.devPktBuf, sizeof(ackInfo.devPktBuf), cnt, 0))
		{	
			ackInfo.pktDatLen = (WORD)cnt;
			ackInfo.ackCode = 0;
			ackInfo.datIdx = 0;
			if (!this->devRawDats(NULL, &ackInfo, RAWMODE_DEV_RESP) )
				return FALSE;
			if (ackInfo.ackCode)// ||ackInfo.pktDatLen < )
				return FALSE;

			ackLen = ackInfo.datIdx;//ackInfo.pktDatLen;
			//TRACE(_T("ofs(%d),cnt(%d)\n"), ofs, cnt);
			return TRUE;
		}
	}
	return FALSE;
}
#endif
BOOL CWDevCfg::writeDevDats(LPCTSTR cmdStr, BYTE * reqDats, WORD dLen, WORD mode)
{
	DEVREQ_INFO2 reqInfo;
	DEVACK_INFO2 ackInfo;
	DWORD cnt;
	BOOL f = FALSE;
	WORD idx;
	BYTE ofs[2];

	reqInfo.cmdCodeStr = cmdStr;
	reqInfo.lpDat = reqDats;
	reqInfo.datLen = dLen;
	reqInfo.pktDatLen = 0;
	reqInfo.datIdx = 0;

	ackInfo.lpBuf = ofs;
	ackInfo.bufLen = 2;
	ackInfo.datIdx = 0;
	ackInfo.pktDatLen = 0;
	
	idx = 0;
	do{

		reqInfo.datIdx = idx;
		if (this->devRawDats(&reqInfo, NULL, RAWMODE_DEV_REQ))
		{
			if (this->transmitToDev(reqInfo.devPktBuf, reqInfo.pktDatLen, cnt, 1))
			{
				if (this->transmitToDev(ackInfo.devPktBuf, sizeof(ackInfo.devPktBuf), cnt, 0))
				{
					ackInfo.pktDatLen = (WORD)cnt;
					ackInfo.datIdx = 0;
					if (this->devRawDats(NULL, &ackInfo, RAWMODE_DEV_RESP))
					{
						f = (ackInfo.ackCode) ? FALSE : TRUE;
						idx += (ofs[0] << 8) + ofs[1];
					}
				} 
			}
		}
	}while (f && (reqInfo.datIdx < reqInfo.datLen));

	return f;//FALSE;
}
BOOL CWDevCfg::readDevDats(LPCTSTR cmdStr,
						 BYTE* ackBuf, WORD &ackLen, WORD mode)
{
	DWORD cnt;
	DEVREQ_INFO2 reqInfo;
	DEVACK_INFO2 ackInfo;

	WORD idx = 0;
	BYTE ofs[2];

	ofs[0] = ofs[1] = 0;
	reqInfo.cmdCodeStr = cmdStr;
	reqInfo.lpDat = ofs;
	reqInfo.datLen = 2;
	reqInfo.pktDatLen = 0;

	ackInfo.lpBuf = ackBuf;
	ackInfo.bufLen = ackLen;
	ackInfo.datIdx = 0;
	ackInfo.pktDatLen = 0;
	
	do
	{
		reqInfo.datIdx = 0;
		if (!this->devRawDats(&reqInfo, NULL, RAWMODE_DEV_REQ))
			return FALSE;

		if (this->transmitToDev(reqInfo.devPktBuf, reqInfo.pktDatLen, cnt, 1))
		{
			if (this->transmitToDev(ackInfo.devPktBuf,sizeof(ackInfo.devPktBuf), cnt, 0))
			{
				ackInfo.pktDatLen = (WORD)cnt;
				if (!this->devRawDats(NULL, &ackInfo, RAWMODE_DEV_RESP))
					return FALSE;

				if(ackInfo.ackCode)
					return FALSE;

				if( cnt <= 4)
					break;

				ofs[0] = (BYTE)(ackInfo.datIdx >> 8);
				ofs[1] = (BYTE)ackInfo.datIdx;
			}else
				return FALSE;
		}else
			return FALSE;
	}while (ackInfo.datIdx < ackLen);

	ackLen = ackInfo.datIdx;

	return TRUE;
}

BOOL CWDevCfg::readDevDats(LPCTSTR cmdStr, BYTE *param,BYTE pLen,
						   BYTE* ackBuf, WORD &ackLen, WORD mode)
{
	DWORD cnt;
	DEVREQ_INFO2 reqInfo;
	DEVACK_INFO2 ackInfo;

	WORD idx = 0;

	reqInfo.cmdCodeStr = cmdStr;
	reqInfo.lpDat = param;
	reqInfo.datLen = pLen;
	reqInfo.pktDatLen = 0;

	ackInfo.lpBuf = ackBuf;
	ackInfo.bufLen = ackLen;
	ackInfo.datIdx = 0;
	ackInfo.pktDatLen = 0;

	reqInfo.datIdx = 0;
	if (this->devRawDats(&reqInfo, NULL, RAWMODE_DEV_REQ))
	{
		if (this->transmitToDev(reqInfo.devPktBuf, reqInfo.pktDatLen, cnt, 1))
		{
			if (this->transmitToDev(ackInfo.devPktBuf, sizeof(ackInfo.devPktBuf), cnt, 0))
			{
				ackInfo.pktDatLen = (WORD)cnt;
				if (!this->devRawDats(NULL, &ackInfo, RAWMODE_DEV_RESP))
					return FALSE;

				ackLen = ackInfo.datIdx;
				return  (ackInfo.ackCode) ? FALSE : TRUE;
			} 
		} 
	} 
	return FALSE;
}
BOOL CWDevCfg::rawLoadCfgInfo(BYTE *datBuf, DWORD len, WORD mode)
{
	BYTE *lpD = datBuf;
	LPCTSTR cmdStr;
	BOOL retVal = FALSE;
	WORD m = 0, n = 0;
	
	switch (mode)
	{
	case RAWMODE_DEV_MKCFGDAT:
		if (this->mkDevDats(NULL,datBuf, (WORD)len,NULL, n, RAWMODE_DEV_MKCFGDAT))
		{
			if (this->writeDevDats(DEV_SET_CFGINFOS, datBuf, n, RAWMODE_DEV_MKCFGDAT))
			{
				m = 0xffff;
				retVal = this->writeDevDats(DEV_SET_CFGINFOS, (BYTE*)&m, 2, RAWMODE_DEV_MKCFGDAT);
			}
		}
		
		break;
	case RAWMODE_DEV_CFGDAT:
		n = (WORD)len;
		if (this->readDevDats(DEV_GET_CFGINFOS, datBuf, n, RAWMODE_DEV_CFGDAT))
			retVal = this->mkDevDats(NULL, datBuf, n, NULL, n, RAWMODE_DEV_CFGDAT);
		break;
	case RAWMODE_DEV_CFGXML:
		XMLCFG_HDPKT xmlPkt;
		cmdStr = DEV_GET_CFGFMT;
		n = sizeof(XMLCFG_HDPKT);
		if (!this->readDevDats(DEV_GET_CFGFMT,NULL,0, (BYTE*)&xmlPkt, n, 0))
			break;

		memcpy(lpD, (void*)&xmlPkt, n);
		lpD = datBuf + n;
		n = xmlPkt.len;
		if (this->readDevDats(DEV_GET_CFGFMT, lpD, n, 0))
		{
			n += sizeof(XMLCFG_HDPKT);
			retVal = this->mkDevDats(NULL, datBuf, n, NULL, m, RAWMODE_DEV_CFGXML);
		}
		break;
	default:
		break;
	}

	return retVal;
}
#if 0
BOOL CWDevCfg::rawLoadCfgInfo(BYTE *datBuf,DWORD len,WORD mode)
{
	DWORD cnt, ofs;
	LPCTSTR cmdStr;
	WORD m,n;
	BYTE buf[255],*lpD = datBuf;// , cmdBuf[16];

	if (mode == RAWMODE_DEV_MKCFGDAT)
	{
		n = len;
		if (!this->mkDevDats(NULL, NULL, 0, datBuf, n, RAWMODE_DEV_MKCFGDAT))
			return FALSE;

		cmdStr = DEV_SET_CFGINFOS;
		len = n;
	} else if (mode == RAWMODE_DEV_CFGDAT)
		cmdStr = DEV_GET_CFGINFOS;
	else if (mode == RAWMODE_DEV_CFGXML)
	{
		XMLCFG_HDPKT xmlPkt;
		cmdStr = DEV_GET_CFGFMT;
		n = sizeof(XMLCFG_HDPKT);
		if (!this->mkDevDats(cmdStr, NULL, 0, (BYTE*)&xmlPkt, n, 0))
			return FALSE;

		memcpy(lpD, (void*)&xmlPkt, n);
		lpD = datBuf + n;
		n = xmlPkt.len;
		if (readDevDats(DEV_GET_CFGFMT, lpD, n, 0))
		{
			n += sizeof(XMLCFG_HDPKT);
			return this->mkDevDats(NULL, datBuf, n, NULL, m, RAWMODE_DEV_CFGXML);
		}
		return FALSE;
	}else
		return FALSE;

	ofs = 0;
	while(ofs < len)
	{
		buf[0] = (BYTE)(ofs >> 8);
		buf[1] = (BYTE)ofs;

		n = len - ofs;
		if (mode == RAWMODE_DEV_MKCFGDAT)
		{
			if (n > 253)
				n = 253;
			
			memcpy(&buf[2], &lpD[ofs], n);
			if (!this->mkDevDats(cmdStr, buf, n + 2, (BYTE*)&m, n, 0))
				break;
			n = htons(m);
		}else
		{
			if (!(this->mkDevDats(cmdStr, buf, 2, &lpD[ofs], n, 0) && n))
				break;
		}

		ofs += n;
	}

	if (!ofs)
		return FALSE;

	if (mode == RAWMODE_DEV_CFGDAT)
	{
		if (!this->mkDevDats(NULL, datBuf, ofs, NULL, n, mode))
			return FALSE;
	}else if (mode == RAWMODE_DEV_CFGXML)
	{
		ofs += sizeof(XMLCFG_HDPKT);
		if (!this->mkDevDats(NULL, datBuf, ofs, NULL, n, mode))
			return FALSE;
	} else if (mode == RAWMODE_DEV_MKCFGDAT)
	{
		buf[0] = buf[1] = 0xff;
		if (!this->mkDevDats(cmdStr, buf, 2, NULL, n, 0))
			return FALSE;
	}
	return  TRUE;
}
#endif
BOOL CWDevCfg::loadCfgInfo(void)
{
	CWDCfgItem *lpItem, mItem;
	WORD  n,idx = 0;
	TCHAR buf[ITEMFMT_SLCT_MAXLEN + 128];
	BYTE load = 0;

	this->itemList.RemoveAll();

	if (this->rawMode)
	{
		n = sizeof(buf);
		if (!this->rawLoadCfgInfo((BYTE*)buf, n, RAWMODE_DEV_CFGDAT))
			return FALSE;

		load = 1;
	}

	do
	{	
		n = _countof(buf);
		if (this->GetDevCfgInfo(&idx, buf, n, DEVCFG_FMT_INFO, load))
		{
			if (mItem.fmtStr2itemFmt(buf))
			{
				this->itemList.AddTail(mItem);
			} 
		} else if (n)
		{
			TRACE(_T("sprintf_s : i < 0 cnt = %d;\r\n"), n);
		} else
		{
			break;
		}
		idx++;
		load = 1;
	} while (1);

	//idx = 0;
	POSITION pos = this->itemList.GetHeadPosition();
	while (pos)
	{
		lpItem = &this->itemList.GetNext(pos);
		n = _countof(buf);
		if (this->GetDevCfgInfo((void*)lpItem->getItemName(), buf, n, DEVCFG_VAL_INFO, 1))
		{
			lpItem->setItemVal(buf);
		}
	}
	return TRUE;
}

BOOL CWDevCfg::loadCfgXml(LPCTSTR path)
{
	TCHAR buf[CFGPKT_MAXLEN];
	if (this->rawMode)
	{
		return this->rawLoadCfgInfo((BYTE*)buf, _countof(buf), RAWMODE_DEV_CFGXML);
	}
	return this->LoadDevCfg(path);
}

BOOL CWDevCfg::saveCfgInfo()
{
	CWDCfgItem *lpItem;
	POSITION pos = this->itemList.GetHeadPosition();
		
	while(pos)
	{
		lpItem = &this->itemList.GetNext(pos);
		if (!this->SetDevCfgInfo(lpItem->getItemName(),lpItem->getItemVal(), 0, 0))
		{
			TRACE(_T("SetDevCfgInfo fail\n"));
		}
	}
	if(this->rawMode)
	{
		BYTE buf[CFGPKT_MAXLEN];
		WORD n = CFGPKT_MAXLEN;

		this->rawLoadCfgInfo(buf,n, RAWMODE_DEV_MKCFGDAT);

	}else
		this->SetDevCfgInfo(NULL, NULL, 0, 1);

	return TRUE;
}
