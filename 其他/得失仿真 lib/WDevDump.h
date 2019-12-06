#ifndef _WDEVDUMP_H
#define _WDEVDUMP_H
#include "WDevObj.h"

//#define WDEV_DUMP_MSG (WM_USER + 0x101)

#define DUMP_BUF_LEN	(4 * 1024)
typedef struct _SMPL_INFO {
	DWORD recvCnts;
	DWORD chksum;
	DWORD errCode;
}SMPL_INFO;
class CWDevDump : public CWDevObj
{
public:
	CWDevDump() : fHandle(INVALID_HANDLE_VALUE)
				, hWnd(NULL)
				, dumpIdx(0)
				, bufLen(DUMP_BUF_LEN)
	{};
	virtual ~CWDevDump(){};

	BOOL open(LPCTSTR path,HWND mWnd = NULL);
	void close();

protected:
	virtual BOOL runProc();
	BOOL saveDump();
	BOOL devDumpMode(BOOL exitMode = FALSE);

private:
	HANDLE fHandle;
	HWND	hWnd;
	
	BYTE dumpBuf[DUMP_BUF_LEN];
	DWORD dumpIdx;
	DWORD bufLen;
	
	
	SMPL_INFO mSmplInfo;
	DEVACK_INFO ackInfo;
};
#endif
