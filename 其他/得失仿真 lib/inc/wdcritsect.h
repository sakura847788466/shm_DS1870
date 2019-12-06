#ifndef _WDCRITSECT_H_
#define _WDCRITSECT_H_
#include <WinBase.h>

class CWDCritSect {
public:
	CWDCritSect()
	{
		this->enable = FALSE;
		if (InitializeCriticalSectionAndSpinCount(&mCritSect,
												   0x00000400))
		{
			//CLASS_LOGMSG_F(_T("InitializeCriticalSectionAndSpinCount Fail\r\n"));
			this->enable = TRUE;
		} else
		{
			ATLTRACE(_T("InitializeCriticalSectionAndSpinCount Fail\r\n"));
		}
	}
	~CWDCritSect()
	{
		if(this->enable)
			DeleteCriticalSection(&mCritSect);

		this->enable = FALSE;
	}
	void Enter()
	{
		if (this->enable)
			EnterCriticalSection(&mCritSect);
	}
	void Leave()
	{
		if (this->enable)
			LeaveCriticalSection(&mCritSect);
	}
	BOOL isEnable() { return this->enable; }
private:
	CRITICAL_SECTION mCritSect;
	BOOL enable;
};

class CAutoCrit{
public:
	CAutoCrit(CWDCritSect *lp) : lpAutoSect(lp)
	{
		if(lp && lp->isEnable())
			lpAutoSect->Enter();
	}
	~CAutoCrit()
	{
		if(this->lpAutoSect && this->lpAutoSect->isEnable())
			lpAutoSect->Leave();
	}
private:
	CWDCritSect *lpAutoSect;
};
#endif
