#include "stdafx.h"
#include "DSDevBmp.h"
#include "DsImg_API.h"

DWORD getBitSpaceLen(const BYTE *lpDat, DWORD dLen, DWORD *s);
void bmpSet(u8 *lpBmp, u16 bmpW, u16 bmpH, u16 posX, u16 len, u8 mode);
BYTE getBitSpaceIdx(BYTE dat, BYTE left);
void bitCopy(u8 *lpD, u8 *lpS, u8 ofs, u16 bLen);
void bitSet(u8 *lpBuf, u16 ofs, u16 len, u8 mode);
void bmpCopy(u8 *lpDest, u8 *lpSrc, u16 orgX, u16 orgY, u16 sW, u16 sH, u16 srcBmpByteW);


BYTE getBitSpaceIdx(BYTE dat, BYTE left)
{
	BYTE i = 0;

	do
	{
		if (left)
		{
			if (dat & 0x80)
				break;
		} else
		{
			if (dat & 0x01)
				break;
		}

		i++;

		if (left)
			dat <<= 1;
		else
			dat >>= 1;
	} while (i < 8);

	return i;
}
DWORD getBitSpaceLen(const BYTE *lpDat, DWORD dLen, DWORD *s)
{
	const BYTE *lpR = lpDat + dLen - 1;
	DWORD lbits = 0, rbits = 0;

	while (lpDat <= lpR)
	{
		if (*lpDat)
		{
			lbits += getBitSpaceIdx(*lpDat, 1);
			break;
		} else
		{
			lbits += 8;
		}
		lpDat++;
	}
	if (s)
	{
		while (lpDat <= lpR)
		{
			if (*lpR)
			{
				rbits += getBitSpaceIdx(*lpR, 0);
				break;
			} else
			{
				rbits += 8;
			}
			lpR--;
		}
		*s = rbits;
	}

	return lbits;
}

void bitCopy(u8 *lpD, u8 *lpS, u8 ofs, u16 bLen)
{
	union {
		u32 dats;
		struct {
			u8 buf[4];
		};
	}shift_buf;

	s32 mask;
	u16 byteLen = bLen >> 3;

	ofs &= 0x07;
	if (!ofs && byteLen)
	{
		memcpy(lpD, lpS, byteLen);
		lpD += byteLen;
		lpS += byteLen;
		bLen &= 0x07;
	}

	while (bLen >= 24)
	{
		shift_buf.buf[3] = *lpS++;
		shift_buf.buf[2] = *lpS++;
		shift_buf.buf[1] = *lpS++;
		shift_buf.buf[0] = *lpS;//++;//0;

		shift_buf.dats <<= ofs;

		*lpD++ = shift_buf.buf[3];
		*lpD++ = shift_buf.buf[2];
		*lpD++ = shift_buf.buf[1];
		//*lpD = shift_buf.buf[0];
		bLen -= 24;
	}

	if (bLen)
	{
		mask = 0x80000000;
		mask >>= (bLen - 1);

		shift_buf.buf[3] = *lpS++;
		shift_buf.buf[2] = *lpS++;
		shift_buf.buf[1] = *lpS;
		shift_buf.buf[0] = 0;

		shift_buf.dats <<= ofs;
		shift_buf.dats &= mask;

		*lpD++ = shift_buf.buf[3];
		bLen += ofs;
		if (bLen > 8)
			*lpD++ = shift_buf.buf[2];
		if (bLen > 16)
			*lpD++ = shift_buf.buf[1];
		if (bLen > 24)
			*lpD++ = shift_buf.buf[0];
	}
}
void bitSet(u8 *lpBuf, u16 ofs, u16 len, u8 mode)
{
	u16 byte_len, bit_len;

	lpBuf += ofs >> 3;
	ofs &= 0x07;


	byte_len = (len + 7) >> 3;
	bit_len = len & 0x07;

	if (byte_len)
	{
		memset(lpBuf, mode ? 0xff : 0, byte_len);
		//lpBuf += byte_len;
	}
	if (ofs)
	{
		*lpBuf &= (0xff >> ofs);
	}
	if (bit_len)
	{
		*(lpBuf + byte_len - 1) &= (0xff << (8 - bit_len));
	}
}

/*
* tag ： bit0 = 1 ，未填充位清0
*/
void bmpCopy(u8 *lpDest, u8 *lpSrc, u16 orgX, u16 orgY, u16 sW, u16 sH, u16 srcBmpByteW)
{
	//u8 *lpDRow;
	u16 rIdx;
	u16 dRow = (sW + 7) >> 3;// sRow = ((sW + 16) >> 3) << 1;

	lpSrc += (orgY * srcBmpByteW) + (orgX >> 3);
	orgX &= 0x07;

	//	lpDRow = lpDest + (orgX >> 3);
	//orgX &= 0x07;

	//if (tag & 0x01)
	{
		memset(lpDest, 0, sH * dRow);
	}

	rIdx = 0;
	while (rIdx < sH)
	{
		bitCopy(lpDest, lpSrc, orgX, sW);

		lpDest += dRow;
		lpSrc += srcBmpByteW;
		rIdx++;
	}
}
void bmpSet(u8 *lpBmp, u16 bmpW, u16 bmpH, u16 posX, u16 len, u8 mode)
{
	u16 i, byteW = (bmpW + 7) >> 3;

	if ((posX + len) > bmpW)
		len = bmpW - posX;

	lpBmp += (posX >> 3);
	posX &= 0x07;
	mode &= 0x01;
	for (i = 0; i < bmpH; i++)
	{
		bitSet(lpBmp, posX, len, mode);
		lpBmp += byteW;
	}
}
CDSDevBmp::CDSDevBmp()
{
	this->lpDevBmp = NULL;
}

CDSDevBmp::~CDSDevBmp()
{
	if (this->lpDevBmp)
		delete[]this->lpDevBmp;
}
BOOL CDSDevBmp::loadImgBmp(BYTE *imgBuf, DWORD pW, DWORD pH)//,RECT &imgRect)
{
	DWORD len, bW_s, bW_d, i;
	BYTE *bmpBuf;
	BOOL f = FALSE, retVal = FALSE;
	
	ASSERT(imgBuf && pW && pH);

	bW_d = bW_s = (pW + 7) >> 3;
	if (bW_s & 0x01)
		bW_d += 1;

	len = bW_d * pH;
	bmpBuf = new BYTE[len];
	if (!bmpBuf)
		return FALSE;

	if (bW_d != bW_s)
	{
		for (i = 0; i < pH; i++)
			memcpy(&bmpBuf[i * bW_d], &imgBuf[i * bW_s], bW_s);
	}

	for (i = 0; i < len; i++) bmpBuf[i] = ~bmpBuf[i];

	SIZE s;
	this->getPageSize(s);
	CBitmap imgBmp;
	if (imgBmp.CreateBitmap(s.cx, s.cy, 1, 1, bmpBuf))
	{
		if (this->bkBmpDC.GetSafeHdc())
			this->bkBmpDC.DeleteDC();

		if (this->bkBmpDC.CreateCompatibleDC(&this->devCDC))
		{
			this->bkBmpDC.SelectObject(&imgBmp);

			retVal = TRUE;
		}
	}

	delete[]bmpBuf;

	return retVal;
}
void CDSDevBmp::showBkImg()
{
	SIZE s;
	if(this->devCDC.GetSafeHdc() && this->bkBmpDC.GetSafeHdc())
	{
		this->getPageSize(s);
		this->devCDC.BitBlt(0,0,s.cx,s.cy,
			&this->bkBmpDC, 0, 0, SRCCOPY);
	}
}
BOOL CDSDevBmp::loadBkImg(LPCTSTR path,WORD tag)
{
	DS_PARAMETER bmpInfo;
	CDSImage_API imgApi;

	if (!this->devCDC.GetSafeHdc())
		return FALSE;

	CBitmap *lpBmp = this->devCDC.GetCurrentBitmap();
	if (!lpBmp)
		return FALSE;
	
	BITMAP dcBmpInfo;
	if (!lpBmp->GetBitmap(&dcBmpInfo))
		return FALSE;

	SIZE s;

	this->getPageSize(s);
	bmpInfo.devp.58 = dcBmpInfo.bmBitsPixel;
	bmpInfo.devp.nWidth = s.cx;// imgR.right - imgR.left;// .bmWidth;
	bmpInfo.devp.nHeight = s.cy;// imgR.bottom - imgR.top;// dcBmpInfo.bmHeight;
	bmpInfo.devp.dmPrintQuality = 0;// this->lpDevBmp->dpi;
	bmpInfo.devp.dmYResolution = 0;// this->lpDevBmp->dpi;
	bmpInfo.devp.dmTag = 0x01;
	bmpInfo.RGBParameter = NULL;
	bmpInfo.RGBPalete = NULL;

	if (imgApi.LoadMyBitmap(path, bmpInfo))
	{
		BYTE *lp = imgApi.GetBits();
		DWORD n = imgApi.GetLength();

		if (lp && n)
		{
			return loadImgBmp(lp, bmpInfo.devp.nWidth, bmpInfo.devp.nHeight);
			//onDevPaint();
		}
	}
	return FALSE;
}

BOOL CDSDevBmp::creatDsBmpDC(CDC *pDC,DSEMUL_DEVINFO_PAGE & pInfo)
{
	//DWORD len = (((bmpRect.right + 15) >> 4) << 1)* bmpRect.bottom;
	BOOL retVal = FALSE;
	DWORD w = (pInfo.pageW[0] << 8) + pInfo.pageW[1];
	DWORD h = (pInfo.pageH[0] << 8) + pInfo.pageH[1];
	DWORD len = ((( w * pInfo.bpps + 15) >> 4) << 1)* h;
	BYTE *bmpBuf = new BYTE[len];

	if (!bmpBuf)
		return FALSE;
	
	memset(bmpBuf, 0xff, len);

	CBitmap devBmp;
	if (devBmp.CreateBitmap(w, h, 1, pInfo.bpps, bmpBuf))
	{
		if (this->devCDC.CreateCompatibleDC(pDC))
		{
			mFont.CreatePointFont(180, _T("黑体"), &this->devCDC);

			this->devCDC.SelectObject(&mFont);
			this->devCDC.SetBkColor(RGB(255, 255, 255));

			this->devCDC.SelectObject(&devBmp);
			retVal = TRUE;
			this->pageInfo = pInfo;
		}
	}

	delete[]bmpBuf;
	return retVal;
}

const DEV_BMP* CDSDevBmp::makeDsBmp(DEVPROP_PRNOUT * prnProp)
{
	BITMAP bmpInfo;
	CBitmap *lpBmp = this->devCDC.GetCurrentBitmap();

	if (lpBmp && !lpBmp->GetBitmap(&bmpInfo))
		return NULL;

	UINT len = bmpInfo.bmWidthBytes * bmpInfo.bmHeight;
	BYTE *lpD,*lp = new BYTE[len];
	if (!lp)
		return NULL;
	
	lpD = lp;
	DWORD m = lpBmp->GetBitmapBits(len, lp);
	DWORD i, lbits, rbits;
	DWORD l, r, u, b;
	for (i = 0; i < m; i++)	lp[i] = ~lp[i];

	l = r = u = -1;
	b = 0;
	for (i = 0; i < bmpInfo.bmHeight; i++)
	{
		lbits = getBitSpaceLen(lp, bmpInfo.bmWidthBytes, &rbits);
		if ((lbits + rbits) >= (bmpInfo.bmWidthBytes << 3))
		{

		} else
		{
			if (u == -1)
				u = i;

			if (lbits < l)
				l = lbits;
			if (rbits < r)
				r = rbits;

			if (i > b)
				b = i;
		}
		lp += bmpInfo.bmWidthBytes;
	}

	lbits = (bmpInfo.bmWidthBytes << 3) - r - l;
	rbits = b - u + 1;
	b = (lbits + 7) >> 3;

	len = b * (rbits + 0) + sizeof(DEV_BMP);
	if (this->lpDevBmp)
		delete[]this->lpDevBmp;

	this->lpDevBmp = (DEV_BMP*)new BYTE[len];
	if (!this->lpDevBmp)
	{
		delete[]lpD;
		return NULL;
	}
	this->lpDevBmp->ID = DEVBMP_ID;		//
	this->lpDevBmp->dpi = 203;	//打印设备最大dpi
	this->lpDevBmp->bmpType = BMP_RASTER_FMT;
	this->lpDevBmp->bpps = bmpInfo.bmBitsPixel;

	this->lpDevBmp->posX = l;
	this->lpDevBmp->posY = u;
	this->lpDevBmp->pixelW = lbits;// (bmpInfo.bmWidthBytes << 3) - r - l;
	this->lpDevBmp->bkPixelH = 0;
	this->lpDevBmp->txPixelH = rbits;// b - u + 1;

	bmpCopy(this->lpDevBmp->BmpDats, lpD,
		this->lpDevBmp->posX, this->lpDevBmp->posY,
		this->lpDevBmp->pixelW, this->lpDevBmp->txPixelH,
		bmpInfo.bmWidthBytes);


	i = b * this->lpDevBmp->txPixelH;
	memset(&this->lpDevBmp->BmpDats[i], 0, b * this->lpDevBmp->bkPixelH);
	bmpSet(&this->lpDevBmp->BmpDats[i], this->lpDevBmp->pixelW,
		this->lpDevBmp->bkPixelH, 0, this->lpDevBmp->pixelW, 1);

	this->lpDevBmp->devInfo.size = 4;
	this->lpDevBmp->devInfo.revs[0] = this->lpDevBmp->devInfo.revs[1] = 0;
	if (prnProp)
	{
		this->lpDevBmp->devInfo.prnProp = *prnProp;
		this->lpDevBmp->devInfo.size += prnProp->propSize;	
	} 
	delete[]lpD;
	return this->lpDevBmp;
}
