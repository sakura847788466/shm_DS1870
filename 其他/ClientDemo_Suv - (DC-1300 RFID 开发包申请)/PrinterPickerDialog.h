#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPrinterPickerDialog 对话框

class CPrinterPickerDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrinterPickerDialog)

public:
	CPrinterPickerDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrinterPickerDialog();

// 对话框数据
	enum { IDD = IDD_PRINTERPICKERDIALOG };

private:
    // 后台线程，与服务的交互在这个线程里执行。
    std::unique_ptr<CWinThread> worker;
    // 当有后台任务时展现给用户一个活动的“...”的视觉提示。
    int            numDots;
    // 单独的打印机信息列表是为了保证工作线程不调用UI功能。
    CList<Printer> printerList;

// 工作线程操作
private:
    typedef UINT (CPrinterPickerDialog::*TaskProc)();
    typedef void (CPrinterPickerDialog::*EndTaskProc)(DWORD ret);
    struct Task
    {
        CPrinterPickerDialog *me;
        CString               taskName;
        TaskProc              taskProc;
        EndTaskProc           endTaskProc;
    };
    std::unique_ptr<Task> task;
    void WorkerBegin(LPCTSTR taskName, TaskProc taskProc, EndTaskProc endTaskProc);
    static UINT WorkerProc(LPVOID);

private:
    void ClearPrinterPicker();
    void AddToPrinterPicker(Printer *p);
    void ParsePrinterList(CStringA list);

    CString originallySelected;
    void EnableControls();
    void DisableControls();

    // 枚举打印机的异步接口
    CStringA listString; // 由 EnumPrinter() 填写
    void EnumPrinterBegin();
    void EnumPrinterEnd(DWORD ret);
    UINT EnumPrinter();

    // 添加打印机的异步接口
    CStringA printerName;  // 由 AddToServerBegin() 填写
    CStringA printerConn;  // 由 AddToServerBegin() 填写
    CStringA printerModel; // 由 AddToServerBegin() 填写
    void AddToServerBegin();
    void AddToServerEnd(DWORD ret);
    UINT AddToServer();

    // 移除打印机
    CStringA removedPrinterName;
    void RemoveFromServerBegin();
    void RemoveFromServerEnd(DWORD ret);
    UINT RemoveFromServer();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    CStatic m_staStatus;
    CListBox m_listPrinterPicker;
    CButton m_btnRefreshPrinterList;
    CButton m_btnRemovePrinter;
    CButton m_btnCancel;
    CButton m_btnAddPrinter;
    CEdit m_txtNewPrinterName;
    CIPAddressCtrl m_ipNewPrinterAddress;
    CEdit m_txtNewPrinterPort;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedBtnRefreshPrinterList();
    afx_msg void OnBnClickedBtnAddPrinter();
    afx_msg void OnLbnSelchangeListPrinterPicker();
    afx_msg void OnBnClickedBtnRemovePrinter();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	CButton m_btnOK;
};
