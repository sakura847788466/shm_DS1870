#pragma once

#include "WDevDef.h"

class CDSDevBmp
{
public:
	CDSDevBmp();
	virtual ~CDSDevBmp();


	//inline void setDevInfo(DSEMUL_DEVINFO_PAGE *pageInfo, DEVPROP_PRNOUT *prnProp);
	void showBkImg();
	BOOL loadBkImg(LPCTSTR path, WORD tag = 0);

	BOOL creatDsBmpDC(CDC *pDC,DSEMUL_DEVINFO_PAGE &pInfo);
	const DEV_BMP* makeDsBmp(DEVPROP_PRNOUT *prnProp);
	CDC* operator->() { return &devCDC; };
	operator CDC * () { return &devCDC; };
	const DEV_BMP* getDevBmp() { return this->lpDevBmp; };
	void getPageSize(SIZE &s) 
	{ 
		s.cx = (this->pageInfo.pageW[0] << 8) + this->pageInfo.pageW[1]; 
		s.cy = (this->pageInfo.pageH[0] << 8) + this->pageInfo.pageH[1];
	}
private:
	BOOL loadImgBmp(BYTE * imgBuf, DWORD pW, DWORD pH);// , RECT & imgRect);

	DEV_BMP *lpDevBmp;
	//DEVPROP_PRNOUT prnProp;
	DSEMUL_DEVINFO_PAGE pageInfo;

	
	CDC	devCDC;
	CDC bkBmpDC;
	CFont mFont;
	CPen devPen;
};

