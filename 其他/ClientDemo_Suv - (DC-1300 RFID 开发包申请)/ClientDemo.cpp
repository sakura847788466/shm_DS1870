
// ClientDemo.cpp : ����Ӧ�ó��������Ϊ��
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
        return _T("�����");
    case JS_WAITING:
        return _T("�����Ŷ�");
    case JS_SUSPENDED:
        return _T("����ͣ");
    case JS_ERROR:
        return _T("����");
    case JS_TERMINATED:
        return _T("����ֹ");
    case JS_PRINTING:
        return _T("���ڴ�ӡ");
    default:
        return _T("δ֪");
    }
}

void JobInfo::UpdateStatus()
{

}

// CClientDemoApp

BEGIN_MESSAGE_MAP(CClientDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CClientDemoApp ����

CClientDemoApp::CClientDemoApp()
    : m_quitJobMonitor(FALSE), m_jobMonitorThread(nullptr)
{

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(222409);
	//// ֧����������������
	//m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	//// ������UI��ʼ�������� InitInstance ��
 //   GetServer().Set("127.0.0.1", 9301);

 //   // ����
    auto &job = GetCurrentJob();
    job.Reset();

 //   //LoadJobList();
 //   // �����������߳�
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


// Ψһ��һ�� CClientDemoApp ����

CClientDemoApp theApp;

// CClientDemoApp ��ʼ��

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
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	// SetRegistryKey(_T("��ʵCPSDK�ͻ���DEMO"));

	CClientDemoDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL) {
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
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
		return result + _T("��Ч�Ĳ���");
	case DS_CPSDK_INVALID_ARG_BUFFER_TOO_LOW:
		return result + _T("������̫С");
	case DS_CPSDK_INVALID_ARG_IS_NULL:
		return result + _T("����Ϊ��");
	case DS_CPSDK_INVALID_ARG_FORMAT_ERROR:
		return result + _T("�����ĸ�ʽ����ȷ");
	case DS_CPSDK_INVALID_ARG_LENGTH_ERROR:
		return result + _T("�������Ȳ���ȷ");
	case DS_CPSDK_INVALID_ARG_NOT_SUPPORT:
		return result + _T("��֧�ֵ�ѡ��");
	case DS_CPSDK_INVALID_ARG_OUT_OF_RANGE:
		return result + _T("����������Χ");
	case DS_CPSDK_INVALID_ARG_TOO_LONG:
		return result + _T("����̫��");
	case DS_CPSDK_INVALID_ARG_CONFIG_NULL:
		return result + _T("��ӡ�����ñ���û����Ŀ");
	case DS_CPSDK_INVALID_ARG_BUFFER_TOO_BIG:
		return result + _T("Ҫ�����Ļ�����̫��");
	case DS_CPSDK_INVALID_ARG_SEQUENCE_ERROR:
		return result + _T("����˳����ȷ");
	case DS_CPSDK_INVALID_ARG_FILE_NO_FOUND:
		return result + _T("�޷����ļ����Ҳ����ļ���û�к��ʵ�Ȩ��");
	case DS_CPSDK_CLIENT_MALLOC_FAILURE0:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE1:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE2:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE3:
	case DS_CPSDK_CLIENT_MALLOC_FAILURE4:
		return result + _T("�ڴ治��");
	case DS_CPSDK_CLIENT_TLS_OUT_OF_INDEXES:
		return result + _T("�ֲ߳̾��洢����(TLS index)�ľ�");
	case DS_CPSDK_INVALID_ARG_OUT_OF_HEADERSIZE:
	case DS_CPSDK_CLIENT_MAC_ERROR:
		return result + _T("���������ص���Ӧ��Ч");
	case DS_CPSDK_CLIENT_JOB_NULL:
		return result + _T("��ӡ����û������");
	case DS_CPSDK_TCP_CREATE_SOCKET_FAILURE:
		return result + _T("�޷������׽���");
	case DS_CPSDK_TCP_CONNECT_SOCKET_FAILURE:
		return result + _T("�޷����ӵ�������");
	case DS_CPSDK_TCP_SEND_SOCKET_FAILURE:
	case DS_CPSDK_TCP_READ_SOCKET_FAILURE:
		return result + _T("ͨ��ʧ��");
	case DS_CPSDK_USB_CreateFile_FAILURE:
	case DS_CPSDK_USB_WriteFile_FAILURE:
		return result + _T("USBͨ��ʧ��");
	case DS_CPSDK_SERVICE_CREATE_SOCKET_FAILURE:
		return result + _T("ϵͳ��Դ���㣬�޷��������������ͨ��");
	case DS_CPSDK_SERVICE_CONNECT_SOCKET_FAILURE:
		return result + _T("���ӷ�����ʧ�ܣ������������IP�Ͷ˿��Լ�����ǽ����");
	case DS_CPSDK_SERVICE_SEND_SOCKET_FAILURE:
		return result + _T("���������������ʧ��");
	case DS_CPSDK_SERVICE_READ_SOCKET_FAILURE:
		return result + _T("�ӷ�������ȡ����ʧ��");
	case DS_CPSDK_PrinterName_IS_NULL:
		return result + _T("��ӡ������Ϊ��");
	case DS_CPSDK_Card_IS_NULL:
		return result + _T("ͼ�����ݲ�����Ҫ��");
	case DS_CPSDK_Printer_Is_Not_Ready:
		return  _T("�������������֮һ����ӡ��æ���ǿա�������ࡢǰ�Ǵ򿪡���ӡ����������װ���ҿ����޿���");
	case DS_CPSDK_Request_NOT_SUPPORT:
		return result + _T("ϵͳ��֧�ָ�����");
	case DS_CPSDK_HID_NO_FOUND:
		return result + _T("�Ҳ���HID�豸");
	case DS_CPSDK_SERVER_UNKNOWN_ERROR:
		return result + _T("�ڷ������Ϸ�����δ֪�Ĵ�����鿴�������ϵ�Windows�¼���־");
	case DS_CPSDK_SERVER_NOT_IMPLEMENTED:
		return result + _T("��������δʵ�ָù���");
	case DS_CPSDK_SERVER_INVALID_FORMAT:
		return result + _T("���͵�����������δͨ����������У��");
	case DS_CPSDK_SERVER_PRINTER_NOT_FOUND:
		return result + _T("�������ϲ����ڴ����ƵĴ�ӡ��");
	case DS_CPSDK_SERVER_JOB_NOT_FOUND:
		return result + _T("��������û�ж�Ӧ�ڴ�ID�Ĵ�ӡ����");
	case DS_CPSDK_SERVER_JOB_TERMINATED:
		return result + _T("��ӡ�����ѱ���ֹ");
	case DS_CPSDK_SERVER_JOB_DONE:
		return result + _T("��ӡ�����ѳɹ����");
	case DS_CPSDK_SERVER_JOB_PRINTING:
		return result + _T("��ӡ�����Ѿ����ڴ�ӡ��");
	case DS_CPSDK_SERVER_INVALID_PRINTER_NAME:
		return result + _T("��ӡ�������к�����Ч�ַ�");
	case DS_CPSDK_SERVER_JOB_ERROR:
		return result + _T("��ӡ��������δ֪��������ֹ��ָ�������");
	case DS_CPSDK_SERVER_INVALID_MODEL:
		return result + _T("��ӡ���ͺ���Ч");
	case DS_CPSDK_SERVER_INVALID_CONN_STRING:
		return result + _T("��Ч�Ĵ�ӡ�������ַ���");
	case DS_CPSDK_SERVER_DUPLICATE_NAME:
		return result + _T("��ӡ�������б��д�������һ��ͬ���Ĵ�ӡ��");
	case DS_CPSDK_SERVER_DUPLICATE_CONN_STRING:
		return result + _T("��ӡ�������б��д�������һ�����Ӵ���ͬ�Ĵ�ӡ��");
	case DS_CPSDK_SERVER_PRINTING_LAST_CARD:
		return result + _T("���ڴ�ӡ�����е����һ�ſ�Ƭ���޷���ͣ����ֹ");
	case DS_CPSDK_SERVER_COPY_COUNT_ZERO:
		return result + _T("�ύ�Ĵ�ӡ�����д�ӡ����Ϊ0");
	case DS_CPSDK_SERVER_PRINTER_OFFLINE:
		return result + _T("��ӡ��������");
	case DS_CPSDK_SERVER_JOB_WAITING:
		return result + _T("��ӡ�����Ѿ����ڵȴ�ִ��״̬");
	case DS_CPSDK_SERVER_JOB_SUSPENDED:
		return result + _T("��ӡ�����Ѿ�������ͣ״̬");
	case DS_CPSDK_SERVER_PRINTER_IN_USE:
		return result + _T("��ӡ������ʹ����");
	case DS_CPSDK_SERVER_PRINTER_QUEUE_FULL:
		return result + _T("��ӡ��������");
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
			status = "�޷���ѯ";
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

				if (fcs == 1) { status = "ǰ�Ǵ�"; return; }
				if (cls == 2) { status = "�������"; return; }
				if ((fcm == 0 && cbs == 1)) { status = "����ȱ��"; return; }
				if (bs != 1 && // ���ջ���ǿ�
					(fcm == 2 && cbs == 1 && code == 0x1) || // �Զ����������кͿ������޿�
					(fcm == 1 && code == 0x1)){ // �ֶ������������޿�
					status = "�ȴ�����"; return;
				}

				switch (code) {
				case 0:
				case 1:
				case 5:
					status = "����";
					break;
				case 2:
					status = "��Ƭ����";
					break;
				case 3:
					status = "�޷���λ";
					break;
				case 4:
					status = "������Чָ��";
					break;
				case 6:
					status = "ǰ�Ǵ�";
					break;
				case 7:
					status = "�ȴ��ֹ�����";
					break;
				case 8:
					status = "ӡͷ����";
					break;
				case 9:
					status = "ӡͷ����";
					break;
				case 10:
					status = "ӡͷ������ʧЧ";
					break;
				case 11:
					status = "���崫����ʧЧ";
					break;
				case 12:
					status = "�ڲ��洢������";
					break;
				default:
					status = "δ֪״̬";
					break;
				}
			} else if (ret == DS_CPSDK_SERVER_PRINTER_OFFLINE) {
				status = "����";
			} else {
				status = "�޷���ѯ";
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

        // ��������״̬
        for (auto i = list.begin(); i != list.end(); ++i) {
            auto &j = i->second;
            if (trackers.count(j.printer) == 0) {
                PrinterStatusTracker tracker = {
                    j.printer, j.printerModel, "����"
                };
                trackers.insert(std::make_pair(j.printer, tracker));
            }
            // ����Ƿ�Ҫ�˳�
            if (me->m_quitJobMonitor)
                return 0;
            if (j.jobStatus != JS_DONE && j.jobStatus != JS_TERMINATED)
                j.UpdateStatus();
        }

        // ��ѯ��ӡ��״̬
        for (auto it = trackers.begin(); it != trackers.end(); ++it) {
            if (me->m_quitJobMonitor)
                return 0;
            it->second.QueryStatus();
        }
        
        // ����ӡ��״̬д������
        for (auto i = list.begin(); i != list.end(); ++i) {
            auto &j = i->second;
            if (trackers.count(j.printer)) {
                j.printerStatus = trackers[j.printer].status;
            }
        }

        MergeJobListUpdates(list);

        // ÿ��ѭ����� 3 ��
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