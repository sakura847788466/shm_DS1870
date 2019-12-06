
// ClientDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
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
    CStringA imagePath;              // ֧��BMP��PNG��JPEG��GIF(��һ֡)
    int      copyCount;              // 0 ~ 65535

    int      priority;               // 0 ~ 10

    #define  CD_PD_VERTICAL         0 // ����
    #define  CD_PD_HORIZONTAL       1 // ����
    int      printDirection;

    #define  CD_HM_THRESHOLDING     0 // ��ֵ��
    #define  CD_HM_ERROR_DIFFUSION  1 // �����ɢ
    int      halftoneMethod;
    int      halftoneThreshold;       // �ڰ���ֵ, 0 ~ 65535

    #define  CD_EM_NO_ERASE         0 // ��������ERASE_FLAG = 1
    #define  CD_EM_ERASE_ALL        1 // �������У�ERASE_FLAG = 0
    #define  CD_EM_USE_MASK         2 // ʹ�����룬ERASE_FLAG = 0

    int      eraseMethod;
    CStringA erasePath;

    int      printSpeed;              // 0 ~ 20���޵�λ
    int      printContrast;           // 0 ~ 20���޵�λ
    int      printTemperature;        // 0 ~ 20���޵�λ
    int      eraseTemperature;        // 0 ~ 20���޵�λ

    #define  CD_CT_MITSUBISHI_BLACK 0 // �����
    #define  CD_CT_MITSUBISHI_BLUE  1 // ������
    #define  CD_CT_EXTRA_THIN       2 // ����
    int      cardType;

    #define  CD_FM_FEED_BOX         0 // ���н���
    #define  CD_FM_MANUAL           1 // �ֶ�����
    #define  CD_FM_AUTO             2 // �Զ���Ӧ(���зǿ���ӿ��н���)
    int      feedMode;

    #define  CD_EJM_AUTO            0 // �Զ�����
    #define  CD_EJM_MANUAL          1 // �ֶ��γ�
    int      ejectMode;

    void Reset();
};

// 4) A JobInfo list to represent jobs we've sent to the server
//    so that we can track their status.
struct JobInfo
{
    // �ͻ���ά������Ϣ
    int      index;
    static int currentIndex;
    time_t   submitDate;
    CStringA printerModel;
    CStringA printerStatus;

    // �����������������Ϣ
    CStringA uuid; // ����UUID��JOB��Ψһ��ʶ�����������ڽ��������û�չʾUUID
    CStringA printer;
    int      copyCount;
    int      printedCopyCount;
    int      priority;

    // JOB״̬
    #define  JS_DONE                0
    #define  JS_WAITING             1
    #define  JS_SUSPENDED           2
    #define  JS_TERMINATED          4
    #define  JS_PRINTING            5
    #define  JS_ERROR               3
    int      jobStatus;

    // ��״ֵ̬�����״̬��
    LPCTSTR  GetStatusName();

    // �ӷ���������JOB״̬
    void     UpdateStatus();

    // ��ʵ�϶�ÿ��info����Ӧ������������
    // ����Ϊ���޸ĵ����ݶ����Ǵ�����Դ��POD����
    // ���Դ˴�ʡ�� ...
};

// CClientDemoApp:
// �йش����ʵ�֣������ ClientDemo.cpp
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

// ��д
public:
	virtual BOOL  InitInstance();
	virtual BOOL  ExitInstance();
// ʵ��
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
    Server           m_server; // ��ǰ������
    Printer          m_printer; // ��ǰ��ӡ��
    Job              m_job; // ��ǰ����

    JobList          m_jobList; // �����б�
    CCriticalSection m_jobListCS; // �����б��ٽ���

    BOOL             m_quitJobMonitor;
    CWinThread      *m_jobMonitorThread; // �������״̬
private:
    UINT            MonitorJobs();
    static UINT     MonitorJobsThreadProc(LPVOID);
};

CClientDemoApp& GetApp();

extern CClientDemoApp theApp;
