// PrinterPickerDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PrinterPickerDialog.h"
#include "afxdialogex.h"

#define TIMER_WORKER       1 // ��̨�߳�״̬���¼�ʱ��

// CPrinterPickerDialog �Ի���

IMPLEMENT_DYNAMIC(CPrinterPickerDialog, CDialog)

CPrinterPickerDialog::CPrinterPickerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrinterPickerDialog::IDD, pParent), task(nullptr)
{

}

CPrinterPickerDialog::~CPrinterPickerDialog()
{
}

void CPrinterPickerDialog::WorkerBegin(LPCTSTR taskName, TaskProc taskProc, EndTaskProc endTaskProc)
{
    ASSERT(task == nullptr);
    task.reset(new Task);
    task->me = this;
    task->taskName = taskName;
    task->taskProc = taskProc;
    task->endTaskProc = endTaskProc;

    worker.reset(new CWinThread(WorkerProc, task.get()));
    worker->m_bAutoDelete = false;
    CWnd::SetTimer(TIMER_WORKER, 500, nullptr);
    worker->CreateThread();
}

UINT CPrinterPickerDialog::WorkerProc(LPVOID _task)
{
    Task *task = reinterpret_cast<Task*>(_task);
    return (task->me->*(task->taskProc))();
}

void CPrinterPickerDialog::ClearPrinterPicker()
{
    while (m_listPrinterPicker.GetCount()) {
        m_listPrinterPicker.DeleteString(0);
    }
}

void CPrinterPickerDialog::AddToPrinterPicker(Printer *p)
{
    int index = m_listPrinterPicker.AddString(CString(p->name));
    m_listPrinterPicker.SetItemDataPtr(index, p);
}
//#define OUTTER_NAME
#ifdef OUTTER_NAME
#define  Printer_D300RW  "DC-1300"
#else
#define  Printer_D300RW  "D300RW"
#endif
void CPrinterPickerDialog::ParsePrinterList(CStringA list)
{
	std::unique_ptr<char[]> p(new char[list.GetLength()+1]);
	memset(p.get(),0,list.GetLength()+1);
	memcpy(p.get(),list.GetBuffer(0),list.GetLength());
	list.ReleaseBuffer();

	const char *split = "\n";
	char *pNext = NULL;
	char *pointer = strtok_s( p.get(), split,&pNext);

	while(pointer){
		Printer prt;
		prt.name = pointer;
		prt.connection = pointer;
		prt.model = Printer_D300RW;
		printerList.AddTail(prt);
		pointer = strtok_s(NULL, split,&pNext);
	}
}


void CPrinterPickerDialog::EnableControls()
{
    // �������õĿؼ�
    //m_btnRefreshPrinterList.EnableWindow(TRUE);
    m_listPrinterPicker.EnableWindow(TRUE);
    //m_btnCancel.EnableWindow(TRUE);
    //m_txtNewPrinterName.EnableWindow(TRUE);
    //m_ipNewPrinterAddress.EnableWindow(TRUE);
    //m_txtNewPrinterPort.EnableWindow(TRUE);
    //m_btnAddPrinter.EnableWindow(TRUE);

    // �ָ�ԭ��ѡ����Ŀ������ѡ������Ŀ
    if (printerList.GetCount() && m_listPrinterPicker.GetCurSel() == LB_ERR) {
        // �ȳ���ѡ��ԭ����ѡ����Ŀ���ٳ��Ե�һ��
        if (LB_ERR == m_listPrinterPicker.SelectString(0, originallySelected)) {
            CString selected;
            m_listPrinterPicker.GetText(0, selected);
            m_listPrinterPicker.SelectString(0, selected);
        }
    }
    
    // �����Ƿ���ѡ����Ŀ�����Ƿ����á�ȷ�����͡��Ƴ���
    int index = m_listPrinterPicker.GetCurSel();
    if (index != LB_ERR) {
        m_btnOK.EnableWindow(TRUE);
        Printer *p = reinterpret_cast<Printer*>(
            m_listPrinterPicker.GetItemDataPtr(index)
            );
        // ֻҪ�����Զ�ö�ٳ����Ĵ�ӡ���������Ƴ�
        if (p->name.Left(6).CompareNoCase("[ENUM]") != 0) {
            m_btnRemovePrinter.EnableWindow(TRUE);
        }
    }
}

void CPrinterPickerDialog::DisableControls()
{
    int index = m_listPrinterPicker.GetCurSel();
    if (index != LB_ERR) {
        m_listPrinterPicker.GetText(index, originallySelected);
    } else {
        originallySelected = "";
    }
	m_btnOK.EnableWindow(FALSE);
	m_btnCancel.EnableWindow(FALSE);
	m_btnRemovePrinter.EnableWindow(FALSE);
	m_btnAddPrinter.EnableWindow(FALSE);
	m_btnRefreshPrinterList.EnableWindow(FALSE);
	m_listPrinterPicker.EnableWindow(FALSE);
	m_txtNewPrinterName.EnableWindow(FALSE);
	m_ipNewPrinterAddress.EnableWindow(FALSE);
	m_txtNewPrinterPort.EnableWindow(FALSE);
}

void CPrinterPickerDialog::EnumPrinterBegin()
{
    //DisableControls();
    WorkerBegin(_T("ˢ�´�ӡ���б�"),
        &CPrinterPickerDialog::EnumPrinter,
        &CPrinterPickerDialog::EnumPrinterEnd);
}

void CPrinterPickerDialog::EnumPrinterEnd(DWORD ret)
{
    // ��¼��ԭ�ȱ���Ĵ�ӡ��
    CString originallySelected;
    {
        int index = m_listPrinterPicker.GetCurSel();
        if (index != LB_ERR) {
            m_listPrinterPicker.GetText(index, originallySelected);
        }
    }

    ClearPrinterPicker();
    if (ret == 0) {
        // ��ѯ�ɹ������´�ӡ���б�
        ParsePrinterList(listString);
        if ( printerList.GetSize() ) {
            auto pos = printerList.GetHeadPosition();
            while (pos) {
                auto &p = printerList.GetNext(pos);
                AddToPrinterPicker(&p);
            }
        }
        m_staStatus.SetWindowText(_T("��ӡ���б���ˢ�¡�"));
    } else {
        m_staStatus.SetWindowText(_T("ˢ�´�ӡ���б�ʧ�ܣ�") +
            GetApp().TranslateErrorCode(ret));
    }
    //EnableControls();
}

UINT CPrinterPickerDialog::EnumPrinter()
{
    int      listSize=512;
    uint32_t ret;

	std::unique_ptr<char[]> p(new char[listSize]);
	memset(p.get(),0,listSize);

    while (true) {
        ret = ::DASEnumPrinter( p.get(), &listSize,3);

        if (ret != DS_CPSDK_INVALID_ARG_BUFFER_TOO_LOW)    break;

        listSize *= 2;
		p.reset(new char[listSize*2]);
    }

    if (ret == 0) {
        listString.Format("%s",p.get());
    }
	OutputDebugStringA( "1" );
	OutputDebugStringA( p.get() );
	OutputDebugStringA( "2" );
    return ret;
}

void CPrinterPickerDialog::AddToServerBegin()
{
    //CString nameT, portT;
    //CStringA port;
    //m_txtNewPrinterName.GetWindowText(nameT);
    //m_txtNewPrinterPort.GetWindowText(portT);
    //port = portT;
    //printerName = nameT;
    //printerConn = "tcp://";
    //BYTE ip[4];
    //m_ipNewPrinterAddress.GetAddress(ip[0], ip[1], ip[2], ip[3]);
    //printerConn.AppendFormat("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    //printerConn.AppendFormat(":%s", (LPCSTR)port);
    //printerModel = "D300RW"; // Ŀǰֻ֧�� D300RW

    //DisableControls();
    //WorkerBegin(_T("��������ӡ��"),
    //    &CPrinterPickerDialog::AddToServer, 
    //    &CPrinterPickerDialog::AddToServerEnd);
}

void CPrinterPickerDialog::AddToServerEnd(DWORD ret)
{
	if  (ret == 0){
		m_staStatus.SetWindowText(_T("��Ӵ�ӡ���ɹ���"));
	}
    //if (ret == 0) {
    //    // ��ӵ��б�
    //    Printer newPrinter;
    //    newPrinter.name = printerName;
    //    newPrinter.connection = printerConn;
    //    newPrinter.model = printerModel;
    //    auto pos = printerList.AddTail(newPrinter);
    //    AddToPrinterPicker(&printerList.GetAt(pos));
    //    m_staStatus.SetWindowText(_T("��Ӵ�ӡ���ɹ���"));
    //} else {
    //    m_staStatus.SetWindowText(_T("��Ӵ�ӡ��ʧ�ܣ�"));
    //}

    //EnableControls();
}

UINT CPrinterPickerDialog::AddToServer()
{
	return 0;
    //// �����еĿ����ô�ӡ������ӵ������б���
    //POSITION pos = printerList.GetHeadPosition();
    //while (pos) {
    //    auto &p = printerList.GetNext(pos);
    //    if (p.name.Left(6) != "[ENUM]") {
    //        ::DASConfigPrinter(
    //            (LPSTR)(LPCSTR)p.name,
    //            (LPSTR)(LPCSTR)p.connection,
    //            (LPSTR)(LPCSTR)p.model);
    //    }
    //}

    //// ���´�ӡ��������ӵ������б���
    //if (0 != ::DASConfigPrinter(
    //    (LPSTR)(LPCSTR)printerName,
    //    (LPSTR)(LPCSTR)printerConn,
    //    (LPSTR)(LPCSTR)printerModel)) {
    //    // ʧ�ܵ���������ò����ڵ�IP��մ�ӡ�������б�
    //    ::DASSetNetworkParams("169.254.0.1", 9301);
    //} else {
    //    ::DASSetNetworkParams(
    //        (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //        GetApp().GetServer().GetPort());
    //}

    //// �����������б� *�滻* ԭ������
    //return ::DASConfigPrinterAll();
}

void CPrinterPickerDialog::RemoveFromServerBegin()
{
   //int index = m_listPrinterPicker.GetCurSel();
    //CString removedPrinterNameT;
    //m_listPrinterPicker.GetText(index, removedPrinterNameT);
    //removedPrinterName = removedPrinterNameT;
    //DisableControls();
    //WorkerBegin(_T("�Ƴ���ӡ��"),
    //    &CPrinterPickerDialog::RemoveFromServer,
    //    &CPrinterPickerDialog::RemoveFromServerEnd);
}

void CPrinterPickerDialog::RemoveFromServerEnd(DWORD ret)
{
	if  (ret == 0){
		m_staStatus.SetWindowText(_T("��Ӵ�ӡ���ɹ���"));
	}
	//if (ret == 0) {
    //    // ��ѡ����ȥ���ô�ӡ��
    //    for (int i = 0; i < m_listPrinterPicker.GetCount(); ++i) {
    //        CString rpnT;
    //        CStringA rpnA;
    //        m_listPrinterPicker.GetText(i, rpnT);
    //        rpnA = rpnT;
    //        if (rpnA == removedPrinterName) {
    //            m_listPrinterPicker.DeleteString(i);
    //            break;
    //        }
    //    }
    //    // �Ӵ�ӡ����ϸ�嵥��ȥ���ô�ӡ��
    //    POSITION pos = printerList.GetHeadPosition();
    //    while (pos) {
    //        POSITION currentPos = pos;
    //        auto &p = printerList.GetNext(pos);
    //        if (p.name == removedPrinterName) {
    //            printerList.RemoveAt(currentPos);
    //            break;
    //        }
    //    }
    //    m_staStatus.SetWindowText(_T("�Ƴ���ӡ���ɹ���"));
    //} else {
    //    m_staStatus.SetWindowText(_T("�Ƴ���ӡ��ʧ�ܣ�"));
    //}
    //EnableControls();
}

UINT CPrinterPickerDialog::RemoveFromServer()
{
	return 0;
    //POSITION pos = printerList.GetHeadPosition();

    //while (pos) {
    //    auto &p = printerList.GetNext(pos);
    //    // �������Ƴ��Ĵ�ӡ��
    //    if (p.name == removedPrinterName) {
    //        continue;
    //    }
    //    // �����Զ�ö�ٵĴ�ӡ��
    //    if (p.name.Left(6) == "[ENUM]") {
    //        continue;
    //    }
    //    ::DASConfigPrinter(
    //        (LPSTR)(LPCSTR)p.name,
    //        (LPSTR)(LPCSTR)p.connection,
    //        (LPSTR)(LPCSTR)p.model);
    //}

    //auto &server = GetApp().GetServer();

    //::DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)server.GetIp(),
    //    server.GetPort());

    //return ::DASConfigPrinterAll();
}

void CPrinterPickerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STA_PRINTER_PICKER_STATUS, m_staStatus);
	DDX_Control(pDX, IDC_LIST_PRINTER_PICKER, m_listPrinterPicker);
	//DDX_Control(pDX, IDC_BTN_REFRESH_PRINTER_LIST, m_btnRefreshPrinterList);
	//DDX_Control(pDX, IDC_BTN_REMOVE_PRINTER, m_btnRemovePrinter);
	//DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//DDX_Control(pDX, IDOK, m_btnOK);
	//DDX_Control(pDX, IDC_BTN_ADD_PRINTER, m_btnAddPrinter);
	//DDX_Control(pDX, IDC_TXT_PRINTER_NAME, m_txtNewPrinterName);
	//DDX_Control(pDX, IDC_TXT_NEW_PRINTER_ADDRESS, m_ipNewPrinterAddress);
	//DDX_Control(pDX, IDC_TXT_NEW_PRINTER_PORT, m_txtNewPrinterPort);
	DDX_Control(pDX, IDC_BUTTON2, m_btnOK);
}

BOOL CPrinterPickerDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
   // m_txtNewPrinterPort.SetWindowText(_T("9100"));
    EnumPrinterBegin();
    return TRUE;
}

BEGIN_MESSAGE_MAP(CPrinterPickerDialog, CDialog)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BTN_REFRESH_PRINTER_LIST, &CPrinterPickerDialog::OnBnClickedBtnRefreshPrinterList)
    ON_BN_CLICKED(IDC_BTN_ADD_PRINTER, &CPrinterPickerDialog::OnBnClickedBtnAddPrinter)
    ON_LBN_SELCHANGE(IDC_LIST_PRINTER_PICKER, &CPrinterPickerDialog::OnLbnSelchangeListPrinterPicker)
    ON_BN_CLICKED(IDC_BTN_REMOVE_PRINTER, &CPrinterPickerDialog::OnBnClickedBtnRemovePrinter)
    //ON_BN_CLICKED(IDOK, &CPrinterPickerDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CPrinterPickerDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CPrinterPickerDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPrinterPickerDialog ��Ϣ�������
void CPrinterPickerDialog::OnTimer(UINT_PTR nIDEvent)
{
    ASSERT(task);
    if (WaitForSingleObject(worker->m_hThread, 0) == WAIT_OBJECT_0) {
        KillTimer(nIDEvent);
        DWORD ret;
        ::GetExitCodeThread(worker->m_hThread, &ret);
        (this->*(task->endTaskProc))(ret);
        worker.reset(nullptr);
        task.reset(nullptr);
    } else {
        numDots = numDots % 6 + 1;
        CString statusText = _T("����") + task->taskName;
        for (int i = 0; i < numDots; ++i) {
            statusText.AppendChar(_T('.'));
        }
        m_staStatus.SetWindowText(statusText);
    }
    CDialog::OnTimer(nIDEvent);
}

void CPrinterPickerDialog::OnBnClickedBtnRefreshPrinterList()
{
    EnumPrinterBegin();
}

void CPrinterPickerDialog::OnBnClickedBtnAddPrinter()
{
    //DWORD unused;
    //if (m_ipNewPrinterAddress.GetAddress(unused) != 4) {
    //    MessageBox(_T("���Ƚ���ӡ����IP��ַ��д������"));
    //    return;
    //}
    //AddToServerBegin();
}

void CPrinterPickerDialog::OnLbnSelchangeListPrinterPicker()
{
   // EnableControls();
}

void CPrinterPickerDialog::OnBnClickedBtnRemovePrinter()
{
   // RemoveFromServerBegin();
}

void CPrinterPickerDialog::OnBnClickedOk()
{
    auto * selected = reinterpret_cast<Printer *>(m_listPrinterPicker.GetItemDataPtr(
        m_listPrinterPicker.GetCurSel()
        ));
    auto & p = GetApp().GetPrinter();
    p = *selected;
    CDialog::OnOK();
}

void CPrinterPickerDialog::OnBnClickedCancel()
{
    CDialog::OnCancel();
}


void CPrinterPickerDialog::OnBnClickedButton2()
{
	auto * selected = reinterpret_cast<Printer *>(m_listPrinterPicker.GetItemDataPtr(
		m_listPrinterPicker.GetCurSel()
		));
	auto & p = GetApp().GetPrinter();
	
	if  ( m_listPrinterPicker.GetCurSel() == -1 ){
		MessageBoxA(NULL,"��ѡ��һ����ӡ��","ѡ���ӡ��",MB_OK);
	}else{
		p = *selected;
		CDialog::OnOK();
	}

}
