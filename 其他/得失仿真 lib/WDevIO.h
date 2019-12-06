#ifndef _WDEVIO_H
#define _WDEVIO_H
#include "WDevObj.h"

#define WDEVIO_MSG (WM_USER + 0x301)

typedef struct _DEVIO_MSG_INFO {
	DWORD itemID;
	DWORD datsIdx;
	DWORD datsCnts;
	BYTE	stat;		//0 - ²Ù×÷OK
}DEVIO_MSG;

//--------tag----------------
#define ITEM_TAG_BUFFMODE	0x01

typedef struct _DEVIO_ITEM{
	HWND	hWnd;
	const BYTE 	*lpDats;
	DWORD 	datLen;
	DWORD 	datIdx;
	DWORD 	tag;
	WORD	reptNums;
	WORD 	reptIdx;
	
	DWORD itemID;
}DEVIO_ITEM,*LPDEVIO_ITEM;

#define DEVIO_MAX_ITEM	16
#define DEVIO_CNTS_MASK	(DEVIO_MAX_ITEM - 1)
class CDevIOQueue
{
public :
	CDevIOQueue() : itemIn(0)
				  , itemOut(0)
	{
	};
	
	~CDevIOQueue(){ QueRelease ();};
	
	BOOL addItem(DEVIO_ITEM *lpItem, BOOL buffMode)
	{
		if (!(lpItem->lpDats && lpItem->datLen))
			return FALSE;

		if(this->isQueFull())
			return FALSE;
		
		this->ioItem[this->itemIn] = *lpItem;
		if (buffMode)
		{
			this->ioItem[this->itemIn].lpDats = new BYTE[lpItem->datLen];
			if(!this->ioItem[this->itemIn].lpDats)
				return FALSE;

			memcpy((BYTE*)this->ioItem[this->itemIn].lpDats,lpItem->lpDats,lpItem->datLen);
			
			this->ioItem[this->itemIn].tag |= ITEM_TAG_BUFFMODE;
		}
		
		this->itemIn = (this->itemIn + 1) & DEVIO_CNTS_MASK;
		
		return TRUE;
	}
	operator LPDEVIO_ITEM() //const
	{
		if (this->isQueEmpty())
			return NULL;

		return (LPDEVIO_ITEM)&this->ioItem[this->itemOut];
	}
	int getItemDats(LPBYTE &lpDat,DWORD *lpItemID)
	{
		int cnts = 0;
		
		if(this->isQueEmpty())
			return -1;

		if (!(this->ioItem[this->itemOut].lpDats && this->ioItem[this->itemOut].datLen))
			return -2;
			
		if(this->ioItem[this->itemOut].datIdx >= this->ioItem[this->itemOut].datLen)
			return -3;	//no more dats
			
		cnts = this->ioItem[this->itemOut].datLen - this->ioItem[this->itemOut].datIdx;
		lpDat = (LPBYTE)this->ioItem[this->itemOut].lpDats;
		
		if(lpItemID)
			*lpItemID = this->ioItem[this->itemOut].itemID;
			
		DBG_ASSERT(lpDat);

		lpDat += this->ioItem[this->itemOut].datIdx;
		return cnts;
	}
	BOOL outItemDats(int cnts)
	{
		if(this->isQueEmpty())
			return FALSE;
		
		cnts += this->ioItem[this->itemOut].datIdx;
		if( cnts >= this->ioItem[this->itemOut].datLen)
			this->ioItem[this->itemOut].datIdx = this->ioItem[this->itemOut].datLen;
		else if(cnts <= 0)
			this->ioItem[this->itemOut].datIdx = 0;
		else
			this->ioItem[this->itemOut].datIdx = cnts;
			
		return TRUE;
	}
	
	#define ACT_IOITEM_RESET	0
	#define ACT_IOITEM_CMPLT	1
	#define ACT_IOITEM_NEXT		2
	BOOL actItem(WORD actMode)
	{
		BOOL retVal = FALSE;
		
		if(this->isQueEmpty())
			return FALSE;
			
		switch(actMode)
		{
		case ACT_IOITEM_RESET:
			retVal = this->resetItem();
			break;
		case  ACT_IOITEM_CMPLT:
			retVal = this->releaseItem();
			break;
		case ACT_IOITEM_NEXT:
			retVal = this->nextItem();
			break;
		}
		return retVal;
	}
	
protected:
	CDevIOQueue(const CDevIOQueue&) {};   
	CDevIOQueue &operator= (const CDevIOQueue&) {};

	BOOL ItemTag_isBufMode(WORD idx)
	{
		if(idx < DEVIO_MAX_ITEM)
		{
			return (this->ioItem[idx].tag & ITEM_TAG_BUFFMODE) ? TRUE : FALSE;
		}
		return FALSE;
	}
	BOOL releaseItem()
	{	
		if (ItemTag_isBufMode(this->itemOut))
		{
			if(this->ioItem[this->itemOut].lpDats)
				delete []this->ioItem[this->itemOut].lpDats;
		}

		memset(&this->ioItem[this->itemOut],sizeof(DEVIO_ITEM),0);

		this->itemOut = (this->itemOut + 1) & DEVIO_CNTS_MASK;

		return TRUE;
	}
	
	BOOL resetItem()
	{
		this->ioItem[this->itemOut].datIdx = 0;
		this->ioItem[this->itemOut].reptIdx = 0;
		return TRUE;
	}
	BOOL nextItem()
	{
		if(this->ioItem[this->itemOut].datIdx >= this->ioItem[this->itemOut].datLen)
		{
			if(!(this->ioItem[this->itemOut].reptIdx < this->ioItem[this->itemOut].reptNums))
			{
				this->releaseItem();
				if(this->isQueEmpty())
					return FALSE;
				return TRUE;
			}
			this->ioItem[this->itemOut].reptIdx++;
			this->ioItem[this->itemOut].datIdx = 0;	
		}
		return TRUE;
	}
	BOOL isQueEmpty()
	{
		return (this->itemIn == this->itemOut) ? TRUE : FALSE;
	}
	BOOL isQueFull()
	{
		return (((this->itemIn + 1) & DEVIO_CNTS_MASK) == this->itemOut ) ?
				TRUE : FALSE;
	}
	void QueRelease()
	{
		for (WORD i = 0; i < DEVIO_MAX_ITEM; i++)
		{
			if(isQueEmpty())
				break;

			releaseItem();
		}
	}
	
private:		
	DEVIO_ITEM ioItem[DEVIO_MAX_ITEM];
	WORD itemIn;
	WORD itemOut;

	//CWDCritSect itemSect;
};

#define DEVIO_WRITE_QUE		1
#define DEVIO_READ_QUE		2
#define DEVIO_RDWR_QUE		3
class CWDevIO : public CWDevObj
{
public:
	CWDevIO() : hRdThread(NULL)
			  , hWrThread(NULL)
	{
		this->ItemNo = 0x1;
	}
	virtual ~CWDevIO()
	{
		this->closeQueue(DEVIO_RDWR_QUE);
	};

	BOOL wrIOToDev(const BYTE *lpDat, DWORD datLen, DWORD & itemID,HWND hWnd = NULL,BOOL buffMode = FALSE);
protected:

	BOOL openQueue(BYTE rdWr = DEVIO_WRITE_QUE);
	BOOL closeQueue(BYTE rdWr = DEVIO_WRITE_QUE);

	CDevIOQueue wrQueue;
	HANDLE hWrThread;
	BOOL	wrThrdExit;
	DWORD	wrThrdID;
	static DWORD WINAPI wrThreadProc(void *param);

	CDevIOQueue rdQueue;
	HANDLE hRdThread;
	BOOL	rdThrdExit;
	DWORD	rdThrdID;
	static DWORD WINAPI rdThreadProc(void *param);

private:
	DWORD	ItemNo;

	
	
};

#endif
