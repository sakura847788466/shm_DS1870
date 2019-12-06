#ifndef _WDEVCFG_H
#define _WDEVCFG_H
#include "WDevObj.h"

typedef struct _ITEM_FMT {
	TCHAR name[ITEMFMT_NAME_LEN + 1]; // 配置项的名称，需是唯一的。
	BYTE fmtType;
	union {
		LONG minVal;
		WORD slctCnts;	
	};
	union {
		LONG maxVal;
		WORD resvr;
	};
	WORD fmtTag;
}ITEM_FMT, *LPITEM_FMT;

typedef struct _ITEM_INFO {
	BYTE fmtType;
	union {
		LONG minVal;
		WORD slctCnts;
	};
	union {
		LONG maxVal;
		WORD resvr;
	};
	WORD fmtTag;
	LPCTSTR slctDat;
}ITEM_INFO;
class CWDCfgItem {
public :
	CWDCfgItem()
	{
		::memset(&this->mItemFmt, 0, sizeof(this->mItemFmt));
	}
	CWDCfgItem(const CWDCfgItem& item)
	{
		this->mItemFmt = item.mItemFmt;
		this->datStr = item.datStr;
		this->itemVal = item.itemVal;
	}
	~CWDCfgItem()
	{
	}
	
	CWDCfgItem& operator=(const CWDCfgItem& item)
	{
		this->mItemFmt = item.mItemFmt;
		this->datStr = item.datStr;
		this->itemVal = item.itemVal;
		return *this;

	}
	BOOL fmtStr2itemFmt(LPCTSTR lpFmtStr)
	{
		LPCTSTR sep = _T(",");
		CString nameStr, valStr, mStr = lpFmtStr;
		int n, curPos = 0;

		memset((void*)&mItemFmt, 0, sizeof(mItemFmt));

		CString resToken = mStr.Tokenize(sep, curPos);

		while (resToken != _T(""))
		{
			if (getItemKey(resToken, nameStr, valStr))
			{
				if (nameStr == XML_ITEM_NAME)
					::_tcscpy_s(mItemFmt.name, _countof(mItemFmt.name), (LPCTSTR)valStr);
				else if (nameStr == XML_ITEM_TYPE)
				{
					n = ::_ttoi((LPCTSTR)valStr);
					if (n > 0)
						mItemFmt.fmtType = (BYTE)n;
				} else if (nameStr == XML_ITEM_MAXVAL)
				{
					mItemFmt.maxVal = ::_ttoi((LPCTSTR)valStr);
				} else if (nameStr == XML_ITEM_MINVAL)
				{
					mItemFmt.minVal = ::_ttoi((LPCTSTR)valStr);
				} else if (nameStr == XML_ITEM_DATSLCT)
				{
					this->datStr = valStr;
				} else if (nameStr == XML_ITEM_PROP)
				{
					n = ::_ttoi((LPCTSTR)valStr);
					if (n > 0)
						mItemFmt.fmtTag = (WORD)n;
				}
			}

			resToken = mStr.Tokenize(sep, curPos);
		}
		return TRUE;
	}
	LPCTSTR getItemName()
	{
		return this->mItemFmt.name;
	}
	CString getItemVal(BOOL valMode = TRUE)
	{
		if (valMode || this->mItemFmt.fmtType != ITEMFMT_TYPE_SLCT)
			return this->itemVal;

		CString mStr = this->itemVal;
		this->slctItemTxtToIdx(mStr,FALSE);
		return mStr;
	}
	BOOL getItemInfo(ITEM_INFO *lpInfo)
	{
		lpInfo->fmtTag = mItemFmt.fmtTag;
		lpInfo->fmtType = mItemFmt.fmtType;
		lpInfo->maxVal = lpInfo->maxVal;
		lpInfo->minVal = lpInfo->minVal;
		return TRUE;
	}
	BOOL getSlctDat(WORD idx, CString &valStr)
	{
		LPCTSTR sep = _T(";");
		int curPos = 0;
		CString mStr = this->datStr;
		CString resToken = mStr.Tokenize(sep, curPos);

		while (idx && resToken != _T(""))
		{
			resToken = mStr.Tokenize(sep, curPos);
			idx--;
		}
		if (!idx && resToken != _T(""))
		{
			valStr = resToken;
			return TRUE;
		}
		return FALSE;
	}
	BOOL getSlctDat(LPCTSTR valStr,int &slctIdx)
	{
		LPCTSTR sep = _T(";");
		int curPos = 0;
		CString mStr = this->datStr;
		CString resToken = mStr.Tokenize(sep, curPos);

		slctIdx = 0;
		while (resToken != _T(""))
		{
			if (resToken == valStr)
				return TRUE;
	
			resToken = mStr.Tokenize(sep, curPos);
			slctIdx++;
		}
		return FALSE;
	}
	BOOL setItemVal(LPCTSTR valStr)
	{
		if(valStr)
		{
			this->itemVal = valStr;
			if (this->mItemFmt.fmtType == ITEMFMT_TYPE_SLCT)
				return slctItemTxtToIdx(this->itemVal);
				
			return TRUE;
		}
		return FALSE;
	}
private :
	BOOL slctItemTxtToIdx(CString &mVal,BOOL txtMode = TRUE)
	{
		if (this->mItemFmt.fmtType != ITEMFMT_TYPE_SLCT)
			return FALSE ;
		
		int i;
		if (txtMode)
		{
			if (this->getSlctDat(mVal, i))
			{
				mVal.Format(_T("%d"), i);
				return TRUE;
			}
		} else
		{
			i = ::_ttoi(this->itemVal);
			return  this->getSlctDat(i, mVal);
		}
		return FALSE;
	}

	BOOL getItemKey(CString &key, CString &name, CString &val)
	{
		LPCTSTR sep = _T("=");
		int curPos = 0;

		name = key.Tokenize(sep, curPos);
		val = key.Tokenize(sep, curPos);;
		
		name.Trim();
		val.Trim();
		return TRUE;
	}
private:
	ITEM_FMT mItemFmt;	// 配置项的格式信息
	CString datStr;
	CString itemVal;		// 配置项的数据值，长度不超过CFGITEM_VAL_MAXLEN
};

class CWDevCfg : public CWDevObj
{
public:
	CWDevCfg(BOOL mode = FALSE) 
	{
		this->rawMode = mode;
	};
	virtual ~CWDevCfg(){};

	LPCTSTR getCfgItem(WORD idx, CString *valStr = NULL);
	CWDCfgItem* getCfgItemObj(WORD idx);
	BOOL setCfgItem(WORD idx, LPCTSTR valStr);
	BOOL transmitToDev(BYTE * datBuf, DWORD len, DWORD &realCnts, BYTE wrMode);
	BOOL mkDevDats(LPCTSTR cmdStr,  BYTE * dats, WORD dLen, BYTE * userBuf, WORD & bufLen, WORD mode);
	BOOL writeDevDats(LPCTSTR cmdStr, BYTE * reqDats, WORD dLen, WORD mode);
	BOOL readDevDats(LPCTSTR cmdStr, BYTE * ackBuf, WORD & ackLen, WORD mode);
	BOOL readDevDats(LPCTSTR cmdStr, BYTE * param, BYTE pLen, BYTE * ackBuf, WORD & ackLen, WORD mode);
	BOOL rawLoadCfgInfo(BYTE *datBuf, DWORD len, WORD mode);
	BOOL loadCfgInfo(void);
	BOOL loadCfgXml(LPCTSTR path);
	BOOL saveCfgInfo();
	void setRawMode(BOOL m) { this->rawMode = m; };
public :
	/*void attach(PORT_HANDLE p)
	{
		this->pHandle = p;
	}
	void detach(void)
	{
		this->pHandle = INVALID_PORT_HANDLE;

	}*/
private:
	CList<CWDCfgItem, CWDCfgItem> itemList;

	BOOL rawMode;
};

#endif
