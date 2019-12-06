
// ClientDemo.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "crtdbg.h"
inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
// We need :

// 1) Server object to represent the server we are talking to.
//    we assume there be only one server, when you change the
//    server ip and port, it is interpreted as a server side
//    configuration change instead of switching to another
//    server
class Server
{
    CStringA ip;
    int      port;
public:
    Server();
    const CStringA &GetIp() const;
    int             GetPort() const;
    BOOL            Set(LPCSTR ip, int port);
    BOOL            SetIp(LPCSTR ip);
    BOOL            SetPort(int port);
};

// 2) Printer object to represent the printer we are using.
struct Printer
{
    CStringA name;
    CStringA connection;
    CStringA model;
};

// 3) A Job object to represent the job we are about to print.
struct Job
{
    CStringA imagePath;              // 支持BMP、PNG、JPEG、GIF(第一帧)
    int      copyCount;              // 0 ~ 65535

    int      priority;               // 0 ~ 10

    #define  CD_PD_VERTICAL         0 // 纵向
    #define  CD_PD_HORIZONTAL       1 // 横向
    int      printDirection;

    #define  CD_HM_THRESHOLDING     0 // 阈值法
    #define  CD_HM_ERROR_DIFFUSION  1 // 误差扩散
    int      halftoneMethod;
    int      halftoneThreshold;       // 黑白阈值, 0 ~ 65535

    #define  CD_EM_NO_ERASE         0 // 不擦除，ERASE_FLAG = 1
    #define  CD_EM_ERASE_ALL        1 // 擦除所有，ERASE_FLAG = 0
    #define  CD_EM_USE_MASK         2 // 使用掩码，ERASE_FLAG = 0

    int      eraseMethod;
    CStringA erasePath;

    int      printSpeed;              // 0 ~ 20，无单位
    int      printContrast;           // 0 ~ 20，无单位
    int      printTemperature;        // 0 ~ 20，无单位
    int      eraseTemperature;        // 0 ~ 20，无单位

    #define  CD_CT_MITSUBISHI_BLACK 0 // 三菱黑
    #define  CD_CT_MITSUBISHI_BLUE  1 // 三菱蓝
    #define  CD_CT_EXTRA_THIN       2 // 极薄
    int      cardType;

    #define  CD_FM_FEED_BOX         0 // 卡盒进卡
    #define  CD_FM_MANUAL           1 // 手动进卡
    #define  CD_FM_AUTO             2 // 自动感应(卡盒非空则从卡盒进卡)
    int      feedMode;

    #define  CD_EJM_AUTO            0 // 自动弹出
    #define  CD_EJM_MANUAL          1 // 手动拔出
    int      ejectMode;

    void Reset();
};

// 4) A JobInfo list to represent jobs we've sent to the server
//    so that we can track their status.
struct JobInfo
{
    // 客户端维护的信息
    int      index;
    static int currentIndex;
    time_t   submitDate;
    CStringA printerModel;
    CStringA printerStatus;

    // 服务器保存的任务信息
    CStringA uuid; // 尽管UUID是JOB的唯一标识，我们无需在界面上向用户展示UUID
    CStringA printer;
    int      copyCount;
    int      printedCopyCount;
    int      priority;

    // JOB状态
    #define  JS_DONE                0
    #define  JS_WAITING             1
    #define  JS_SUSPENDED           2
    #define  JS_TERMINATED          4
    #define  JS_PRINTING            5
    #define  JS_ERROR               3
    int      jobStatus;

    // 将状态值翻译成状态名
    LPCTSTR  GetStatusName();

    // 从服务器更新JOB状态
    void     UpdateStatus();

    // 事实上对每个info对象都应该用锁保护，
    // 但因为被修改的内容都不是带有资源的POD对象，
    // 所以此处省略 ...
};

// CClientDemoApp:
// 有关此类的实现，请参阅 ClientDemo.cpp
//
typedef int     JobListKey;
typedef JobInfo JobListVal;
typedef std::pair<JobListKey, JobListVal> JobListItem;
typedef std::pair<const JobListKey, JobListVal> ConstJobListItem;
typedef std::map<JobListKey, JobListVal> JobList;

class CClientDemoApp : public CWinApp
{
public:
	CClientDemoApp();
    ~CClientDemoApp();

// 重写
public:
	virtual BOOL  InitInstance();
	virtual BOOL  ExitInstance();
// 实现
	DECLARE_MESSAGE_MAP()

public:
    Server&   GetServer();
    Printer&  GetPrinter();
    Job&      GetCurrentJob();
    JobList   GetJobListCopy();
    void      MergeJobListUpdates(JobList &updates);
    JobInfo*  FindJobInfoByIndex(int index);
    void      AddToJobList(const JobInfo &);
    void      RemoveFinishedJobs();
    void      RemoveAllJobs();
    void      SaveJobList();
    void      LoadJobList();

    CString   FormatTime(time_t local);
    CString   TranslateErrorCode(uint32_t);
    CString   GetVersion();

private:
    Server           m_server; // 当前服务器
    Printer          m_printer; // 当前打印机
    Job              m_job; // 当前任务

    JobList          m_jobList; // 任务列表
    CCriticalSection m_jobListCS; // 任务列表临界区

    BOOL             m_quitJobMonitor;
    CWinThread      *m_jobMonitorThread; // 监控任务状态
private:
    UINT            MonitorJobs();
    static UINT     MonitorJobsThreadProc(LPVOID);
};

CClientDemoApp& GetApp();

extern CClientDemoApp theApp;
