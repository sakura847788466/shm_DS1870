
// ClientDemo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "ClientDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define JOB_LIST_FILE "\\CPSDK.ClientDemo.JobList.dat"

Server::Server() : port(0) {}

const CStringA &Server::GetIp() const { return ip; }

int Server::GetPort() const { return port; }

BOOL Server::Set(LPCSTR ip, int port)
{
    BOOL bSameIp = (this->ip == ip);
    BOOL bSamePort = (this->port == port);

    if (bSameIp && bSamePort)
        return TRUE;

    if (!bSamePort) {
        this->port = port;
    }

    if (!bSameIp) {
        this->ip = ip;
    }
    
    return 0;// == ::DASSetNetworkParams((char *)ip, port);
}

BOOL Server::SetIp(LPCSTR ip)
{
    if (this->ip == ip)
        return TRUE;

    this->ip = ip;
    return 0;// == ::DASSetNetworkParams((char *)ip, this->port);
}

BOOL Server::SetPort(int port)
{
    if (this->port == port)
        return TRUE;

    this->port = port;
    return 0;// == ::DASSetNetworkParams((char *)(LPCSTR)this->ip, this->port);
}

void Job::Reset()
{
    // imagePath = "";
    // copyCount = 1;
    priority = 0;
    printDirection = CD_PD_HORIZONTAL;
    halftoneMethod = CD_HM_ERROR_DIFFUSION;
    halftoneThreshold = 128;
    eraseMethod = CD_EM_ERASE_ALL;
    erasePath = "";
    printSpeed = 10;
    printContrast = 10;
    printTemperature = 10;
    eraseTemperature = 10;
    cardType = CD_CT_MITSUBISHI_BLACK;
    feedMode = CD_FM_AUTO;
    ejectMode = CD_EJM_AUTO;
}

int JobInfo::currentIndex = 1;

LPCTSTR JobInfo::GetStatusName()
{
    switch (jobStatus) {
    case JS_DONE:
        return _T("已完成");
    case JS_WAITING:
        return _T("正在排队");
    case JS_SUSPENDED:
        return _T("已暂停");
    case JS_ERROR:
        return _T("出错");
    case JS_TERMINATED:
        return _T("已终止");
    case JS_PRINTING:
        return _T("正在打印");
    default:
        return _T("未知");
    }
}

void JobInfo::UpdateStatus()
{

}

// CClientDemoApp

BEGIN_MESSAGE_MAP(CClientDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CClientDemoApp 构造

CClientDemoApp::CClientDemoApp()
    : m_quitJobMonitor(FALSE), m_jobMonitorThread(nullptr)
{

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(222409);
	//// 支持重新启动管理器
	//m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	//// 将所有UI初始化放置在 InitInstance 中
 //   GetServer().Set("127.0.0.1", 9301);

 //   // 任务
    auto &job = GetCurrentJob();
    job.Reset();

 //   //LoadJobList();
 //   // 启动任务监控线程
 //   //m_jobMonitorThread = new CWinThread(MonitorJobsThreadProc, this);
 //  // m_jobMonitorThread->m_bAutoDelete = TRUE;
 //  // m_jobMonitorThread->CreateThread();
}

CClientDemoApp::~CClientDemoApp()
{
	//CMFCVisualManager::DestroyInstance();
    //HANDLE copy = m_jobMonitorThread->m_hThread;
    //m_quitJobMonitor = TRUE;
    //::WaitForSingleObject(copy, INFINITE);
    //SaveJobList();
}


// 唯一的一个 CClientDemoApp 对象

CClientDemoApp theApp;

// CClientDemoApp 初始化

BOOL CClientDemoApp::ExitInstance()
{
	::DASExit();

	CMFCVisualManager::DestroyInstance();
	return __super::ExitInstance();
}


BOOL CClientDemoApp::InitInstance()
{
	::DASInit();
//	EnableMemLeakCheck();
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	// SetRegistryKey(_T("得实CPSDK客户端DEMO"));

	CClientDemoDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL) {
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}

Server& CClientDemoApp::GetServer()
{
    return this->m_server;
}

Printer& CClientDemoApp::GetPrinter()
{
    return this->m_printer;
}

Job& CClientDemoApp::GetCurrentJob()
{
    return this->m_job;
}

JobList CClientDemoApp::GetJobListCopy()
{
    CSingleLock lock(&m_jobListCS, TRUE);
    return m_jobList;
}

static std::string GetAppDataPath()
{
    const char *varName = "LOCALAPPDATA";
    DWORD size;
    size = ::GetEnvironmentVariableA(varName, nullptr, 0);
    if (!size) {
        varName = "APPDATA";
        size = ::GetEnvironmentVariableA(varName, nullptr, 0);
    }
    if (!size) {
        return "";
    }
    std::string result(size, '\0');
    ::GetEnvironmentVariableA(varName, &result[0], (DWORD)result.size());
    result.resize(::strlen(result.data()));

	OutputDebugStringA(result.c_str());

    return result;
}

static std::string EscapeWhiteSpace(const std::string &s)
{
    // 0x20 SP -> '\' 's'
    // 0x0D CR -> '\' 'r'
    // 0x0A LF -> '\' 'n'
    // 0x09 HT -> '\' 't'
    // 0x0B VT -> '\' 'v'
    std::string result;
    for (size_t i = 0; i < s.size(); ++i) {
        switch (s[i]) {
        case 0x20:
            result.push_back('\\');
            result.push_back('s');
            break;
        case 0x0D:
            result.push_back('\\');
            result.push_back('r');
            break;
        case 0x0A:
            result.push_back('\\');
            result.push_back('n');
            break;
        case 0x09:
            result.push_back('\\');
            result.push_back('t');
            break;
        case 0x0B:
            result.push_back('\\');
            result.push_back('v');
            break;
        case '\\':
            result.push_back('\\');
            result.push_back('\\');
            break;
        default:
            result.push_back(s[i]);
            break;
        }
    }

    return result;
}

static std::string UnescapeWhiteSpace(const std::string &s)
{
    std::string result;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\') {
            ++i;
            if (i < s.size()) {
                switch (s[i]) {
                case 's':
                    result.push_back(0x20);
                    break;
                case 'r':
                    result.push_back(0x0D);
                    break;
                case 'n':
                    result.push_back(0x0A);
                    break;
                case 't':
                    result.push_back(0x09);
                    break;
                case 'v':
                    result.push_back(0x0B);
                    break;
                default:
                    result.push_back('\\');
                    break;
                }
            } else {
                return result;
            }
        } else {
            result.push_back(s[i]);
        }
    }

    return result;
}

void CClientDemoApp::RemoveFinishedJobs()
{
    CSingleLock lock(&m_jobListCS, TRUE);
    for (auto i = m_jobList.begin(); i != m_jobList.end();) {
        switch (i->second.jobStatus) {
        case JS_DONE:
        case JS_TERMINATED:
            i = m_jobList.erase(i);
            break;
        default:
            ++i;
            break;
        }
    }
}

void CClientDemoApp::RemoveAllJobs()
{
    CSingleLock lock(&m_jobListCS, TRUE);
    m_jobList.clear();
}

void CClientDemoApp::SaveJobList()
{
    std::string appDataPath = GetAppDataPath();
    appDataPath.append(JOB_LIST_FILE);
    std::ofstream file(appDataPath, std::ios::out | std::ios::trunc | std::ios::binary);
    auto list = GetJobListCopy();
    auto savejob = [&file](ConstJobListItem &item) {
        auto &job = item.second;
        file << job.index << ' '
            << EscapeWhiteSpace((LPCSTR)job.uuid) << ' '
            << job.submitDate << ' '
            << EscapeWhiteSpace((LPCSTR)job.printer) << ' '
            << EscapeWhiteSpace((LPCSTR)job.printerModel) << ' '
            << job.jobStatus << ' '
            << job.copyCount << ' '
            << job.printedCopyCount << ' '
            << job.priority;
        file << std::endl;
    };

    std::for_each(m_jobList.begin(), m_jobList.end(), savejob);
    file.flush();
    file.close();
}

void CClientDemoApp::LoadJobList()
{
    std::string appDataPath = GetAppDataPath();
    appDataPath.append(JOB_LIST_FILE);
    std::ifstream file(appDataPath);
    
    int maxIndex = 0;
    while (file.good()) {
        std::string line;
        std::getline(file, line);
        std::stringstream lineStream(line, std::ios::in | std::ios::binary);
        JobInfo job;
        {
            std::string uuid, printer, printerModel;
            if ((lineStream >> job.index) &&
                (lineStream >> uuid) &&
                (lineStream >> job.submitDate) &&
                (lineStream >> printer) &&
                (lineStream >> printerModel) &&
                (lineStream >> job.jobStatus) &&
                (lineStream >> job.copyCount) &&
                (lineStream >> job.printedCopyCount) &&
                (lineStream >> job.priority)) {
                job.uuid = UnescapeWhiteSpace(uuid).data();
                job.printer = UnescapeWhiteSpace(printer).data();
                job.printerModel = UnescapeWhiteSpace(printerModel).data();
                AddToJobList(job);
                if (job.index > maxIndex) {
                    maxIndex = job.index;
                }
            }
        }
    }
    JobInfo::currentIndex = maxIndex + 1;

    file.close();
}

void CClientDemoApp::MergeJobListUpdates(JobList &updates)
{
    CSingleLock lock(&m_jobListCS, TRUE);
    for (auto i = updates.begin(); i != updates.end(); ++i) {
        auto j = m_jobList.find(i->first);
        if (j != m_jobList.end()) {
            auto &src = i->second;
            auto &dst = j->second;
            dst.jobStatus = src.jobStatus;
            dst.printedCopyCount = src.printedCopyCount;
            dst.priority = src.priority;
            dst.printerStatus = src.printerStatus;
        }
    }
}

JobInfo* CClientDemoApp::FindJobInfoByIndex(int index)
{
    CSingleLock lock(&m_jobListCS, TRUE);

    auto pred = [index](const JobListItem &j) {
        return j.second.index == index;
    };
    auto iter = std::find_if(m_jobList.begin(), m_jobList.end(), pred);
    if (iter != m_jobList.end()) {
        return &iter->second;
    }

    return nullptr;
}

void CClientDemoApp::AddToJobList(const JobInfo &info)
{
    CSingleLock lock(&m_jobListCS, TRUE);
    m_jobList.insert(std::make_pair(info.index, info));
}

CString CClientDemoApp::FormatTime(time_t local)
{
    return CTime(local).Format(_TEXT("%Y/%m/%d %H:%M:%S"));
}

CString CClientDemoApp::TranslateErrorCode(uint32_t code)
{
    CString result;
    result.Format(_T("(0x%08X)"), code);
    switch (code) {
	case DS_CPSDK_INVALID_ARG:
		return result + _T("无效的参数");
	case DS_CPSDK_INVALID_ARG_BUFFER_TOO_LOW:
		return result + _T("缓冲区太小");
	case DS_CPSDK_INVALID_ARG_IS_NULL:
		return result + _T("参数为空");
	case DS_CPSDK_INVALID_ARG_FORMAT_ERROR:
		return result + _T("参数的格式不正确");
	case DS_CPSDK_INVALID_ARG_LENGTH_ERROR:
		return result + _T("参数长度不正确");
	case DS_CPSDK_INVALID_ARG_NOT_SUPPORT:
		return result + _T("不支持的选项");
	case DS_CPSDK_INVALID_ARG_OUT_OF_RANGE:
		return result + _T("参数超出范围");
	case DS_CPSDK_INVALID_ARG_TOO_LONG:
		return result + _T("参数太长");
	case DS_CPSDK_INVALID_ARG_CONFIG_NULL:
		return result + _T("打印机配置表中没有条目");
	case DS_CPSDK_INVALID_ARG_BUFFER_TOO_BIG:
		return result + _T("要求分配的缓冲区太大");
	case DS_CPSDK_INVALID_ARG_SEQUENCE_ERROR:
		return result + _T("调用顺序不正确");
	case DS_CPSDK_INVALID_ARG_FILE_NO_FOUND:
		return result + _T("无法打开文件：找不到文件或没有合适的权限");
	case DS_CPSDK_CLIENT_MALLOC_FAILURE0:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE1:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE2:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE3:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE4:
		return result + _T("内存不足");
	case DS_CPSDK_CLIENT_TLS_OUT_OF_INDEXES:
		return result + _T("线程局部存储索引(TLS index)耗尽");
	case DS_CPSDK_INVALID_ARG_OUT_OF_HEADERSIZE:
	case DS_CPSDK_CLIENT_MAC_ERROR:
		return result + _T("服务器返回的响应无效");
	case DS_CPSDK_CLIENT_JOB_NULL:
		return result + _T("打印任务没有内容");
	case DS_CPSDK_TCP_CREATE_SOCKET_FAILURE:
		return result + _T("无法创建套接字");
	case DS_CPSDK_TCP_CONNECT_SOCKET_FAILURE:
		return result + _T("无法连接到服务器");
	case DS_CPSDK_TCP_SEND_SOCKET_FAILURE:
	case DS_CPSDK_TCP_READ_SOCKET_FAILURE:
		return result + _T("通信失败");
	case DS_CPSDK_USB_CreateFile_FAILURE:
	case DS_CPSDK_USB_WriteFile_FAILURE:
		return result + _T("USB通信失败");
	case DS_CPSDK_SERVICE_CREATE_SOCKET_FAILURE:
		return result + _T("系统资源不足，无法发起与服务器的通信");
	case DS_CPSDK_SERVICE_CONNECT_SOCKET_FAILURE:
		return result + _T("连接服务器失败，请检查服务器的IP和端口以及防火墙设置");
	case DS_CPSDK_SERVICE_SEND_SOCKET_FAILURE:
		return result + _T("向服务器发送数据失败");
	case DS_CPSDK_SERVICE_READ_SOCKET_FAILURE:
		return result + _T("从服务器读取数据失败");
	case DS_CPSDK_PrinterName_IS_NULL:
		return result + _T("打印机名称为空");
	case DS_CPSDK_Card_IS_NULL:
		return result + _T("图像数据不符合要求");
	case DS_CPSDK_Printer_Is_Not_Ready:
		return  _T("发生了如下情况之一：打印机忙、非空、必须清洁、前盖打开、打印机出错、卡盒装卡且卡盒无卡。");
	case DS_CPSDK_Request_NOT_SUPPORT:
		return result + _T("系统不支持该请求");
	case DS_CPSDK_HID_NO_FOUND:
		return result + _T("找不到HID设备");
	case DS_CPSDK_SERVER_UNKNOWN_ERROR:
		return result + _T("在服务器上发生了未知的错误，请查看服务器上的Windows事件日志");
	case DS_CPSDK_SERVER_NOT_IMPLEMENTED:
		return result + _T("服务器尚未实现该功能");
	case DS_CPSDK_SERVER_INVALID_FORMAT:
		return result + _T("发送到服务器请求未通过服务器的校验");
	case DS_CPSDK_SERVER_PRINTER_NOT_FOUND:
		return result + _T("服务器上不存在此名称的打印机");
	case DS_CPSDK_SERVER_JOB_NOT_FOUND:
		return result + _T("服务器上没有对应于此ID的打印任务");
	case DS_CPSDK_SERVER_JOB_TERMINATED:
		return result + _T("打印任务已被终止");
	case DS_CPSDK_SERVER_JOB_DONE:
		return result + _T("打印任务已成功完成");
	case DS_CPSDK_SERVER_JOB_PRINTING:
		return result + _T("打印任务已经处于打印中");
	case DS_CPSDK_SERVER_INVALID_PRINTER_NAME:
		return result + _T("打印机名称中含有无效字符");
	case DS_CPSDK_SERVER_JOB_ERROR:
		return result + _T("打印任务遇到未知错误，请终止或恢复该任务");
	case DS_CPSDK_SERVER_INVALID_MODEL:
		return result + _T("打印机型号无效");
	case DS_CPSDK_SERVER_INVALID_CONN_STRING:
		return result + _T("无效的打印机连接字符串");
	case DS_CPSDK_SERVER_DUPLICATE_NAME:
		return result + _T("打印机配置列表中存在至少一对同名的打印机");
	case DS_CPSDK_SERVER_DUPLICATE_CONN_STRING:
		return result + _T("打印机配置列表中存在至少一对连接串相同的打印机");
	case DS_CPSDK_SERVER_PRINTING_LAST_CARD:
		return result + _T("正在打印任务中的最后一张卡片，无法暂停或终止");
	case DS_CPSDK_SERVER_COPY_COUNT_ZERO:
		return result + _T("提交的打印任务中打印份数为0");
	case DS_CPSDK_SERVER_PRINTER_OFFLINE:
		return result + _T("打印机已下线");
	case DS_CPSDK_SERVER_JOB_WAITING:
		return result + _T("打印任务已经处于等待执行状态");
	case DS_CPSDK_SERVER_JOB_SUSPENDED:
		return result + _T("打印任务已经处于暂停状态");
	case DS_CPSDK_SERVER_PRINTER_IN_USE:
		return result + _T("打印机正在使用中");
	case DS_CPSDK_SERVER_PRINTER_QUEUE_FULL:
		return result + _T("打印机队列满");
    }

    return result;
}

CString CClientDemoApp::GetVersion()
{
    CString versionString;
    HMODULE module = ::GetModuleHandleW(nullptr);
    WCHAR modulePath[MAX_PATH];
    DWORD versionSize;
    CStringA versionBuffer;
    VS_FIXEDFILEINFO *versionInfo;

    ::GetModuleFileNameW(module, modulePath, sizeof(modulePath) / sizeof(WCHAR));

    {
        DWORD unused;
        versionSize = ::GetFileVersionInfoSizeW(modulePath, &unused);
        if (!versionSize) {
            return _T("");
        }
    }
    
    char *p = versionBuffer.GetBuffer((int)versionSize);
    ::GetFileVersionInfoW(modulePath, 0, versionSize, p);

    {
        UINT unused;
        ::VerQueryValueW(p, L"\\", (LPVOID*)&versionInfo, &unused);
    }
    versionString.Format(_T("%u.%u.%u.%u"),
        (versionInfo->dwProductVersionMS) >> 16,
        (versionInfo->dwProductVersionMS) & 0xFFFF,
        (versionInfo->dwProductVersionLS) >> 16,
        (versionInfo->dwProductVersionLS) & 0xFFFF);
    versionBuffer.ReleaseBuffer((int)versionSize);
    return versionString;
}

struct PrinterStatusTracker
{
    CStringA name;
    CStringA model;
    CStringA status;

    bool operator < (const PrinterStatusTracker &that) {
        return this->name < that.name;
    }

    void QueryStatus()
    {
        uint32_t ret;
        //ret = DASSetNetworkParams(
        //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(), GetApp().GetServer().GetPort());
        ret = ::DASSetPrinterName(
            (LPSTR)(LPCSTR)name, (LPSTR)(LPCSTR)model);

		if  ( ret != DS_CPSDK_OK ){
			status = "无法查询";
		}else{
			uint64_t statusWord;
			ret = ::DASFetchPrinterStatus(&statusWord);
			if (0 == ret) {

				auto cls = ::DASGetCleaningStatus(statusWord);
				auto fcm = ::DASGetFeedCardMode(statusWord);
				auto cbs = ::DASGetPrinterStatus_CardBoxStatus(statusWord);
				auto fcs = ::DASGetPrinterStatus_FrontCoverStatus(statusWord);
				auto bs  = ::DASGetRecvBufferStatus(statusWord);
				uint32_t code = DASGetPrinterStatus_ErrorNo(statusWord);

				if (fcs == 1) { status = "前盖打开"; return; }
				if (cls == 2) { status = "必须清洁"; return; }
				if ((fcm == 0 && cbs == 1)) { status = "卡盒缺卡"; return; }
				if (bs != 1 && // 接收缓存非空
					(fcm == 2 && cbs == 1 && code == 0x1) || // 自动进卡，卡盒和卡道都无卡
					(fcm == 1 && code == 0x1)){ // 手动进卡，卡道无卡
					status = "等待进卡"; return;
				}

				switch (code) {
				case 0:
				case 1:
				case 5:
					status = "正常";
					break;
				case 2:
					status = "卡片堵塞";
					break;
				case 3:
					status = "无法复位";
					break;
				case 4:
					status = "遇到无效指令";
					break;
				case 6:
					status = "前盖打开";
					break;
				case 7:
					status = "等待手工出卡";
					break;
				case 8:
					status = "印头过热";
					break;
				case 9:
					status = "印头过冷";
					break;
				case 10:
					status = "印头传感器失效";
					break;
				case 11:
					status = "主板传感器失效";
					break;
				case 12:
					status = "内部存储器故障";
					break;
				default:
					status = "未知状态";
					break;
				}
			} else if (ret == DS_CPSDK_SERVER_PRINTER_OFFLINE) {
				status = "离线";
			} else {
				status = "无法查询";
			}
    }
  }
};



UINT CClientDemoApp::MonitorJobs()
{
    auto me = reinterpret_cast<volatile CClientDemoApp*>(this);
    while (!me->m_quitJobMonitor) {

        DWORD startTime = GetTickCount();
        auto list = GetJobListCopy();
        std::map<CStringA, PrinterStatusTracker> trackers;

        // 更新任务状态
        for (auto i = list.begin(); i != list.end(); ++i) {
            auto &j = i->second;
            if (trackers.count(j.printer) == 0) {
                PrinterStatusTracker tracker = {
                    j.printer, j.printerModel, "正常"
                };
                trackers.insert(std::make_pair(j.printer, tracker));
            }
            // 检测是否要退出
            if (me->m_quitJobMonitor)
                return 0;
            if (j.jobStatus != JS_DONE && j.jobStatus != JS_TERMINATED)
                j.UpdateStatus();
        }

        // 查询打印机状态
        for (auto it = trackers.begin(); it != trackers.end(); ++it) {
            if (me->m_quitJobMonitor)
                return 0;
            it->second.QueryStatus();
        }
        
        // 将打印机状态写回任务
        for (auto i = list.begin(); i != list.end(); ++i) {
            auto &j = i->second;
            if (trackers.count(j.printer)) {
                j.printerStatus = trackers[j.printer].status;
            }
        }

        MergeJobListUpdates(list);

        // 每个循环最短 3 秒
        DWORD usedTime = GetTickCount() - startTime;
        if (usedTime < 3000)
            SleepEx(3000 - usedTime, FALSE);
    }
    return 0;
}

UINT CClientDemoApp::MonitorJobsThreadProc(LPVOID param)
{
    auto _this = reinterpret_cast<CClientDemoApp*>(param);
    return _this->MonitorJobs();
}

CClientDemoApp& GetApp()
{
    return *dynamic_cast<CClientDemoApp*>(::AfxGetApp());
}