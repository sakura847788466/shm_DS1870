#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPrinterPickerDialog �Ի���

class CPrinterPickerDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrinterPickerDialog)

public:
	CPrinterPickerDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrinterPickerDialog();

// �Ի�������
	enum { IDD = IDD_PRINTERPICKERDIALOG };

private:
    // ��̨�̣߳������Ľ���������߳���ִ�С�
    std::unique_ptr<CWinThread> worker;
    // ���к�̨����ʱչ�ָ��û�һ����ġ�...�����Ӿ���ʾ��
    int            numDots;
    // �����Ĵ�ӡ����Ϣ�б���Ϊ�˱�֤�����̲߳�����UI���ܡ�
    CList<Printer> printerList;

// �����̲߳���
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

    // ö�ٴ�ӡ�����첽�ӿ�
    CStringA listString; // �� EnumPrinter() ��д
    void EnumPrinterBegin();
    void EnumPrinterEnd(DWORD ret);
    UINT EnumPrinter();

    // ��Ӵ�ӡ�����첽�ӿ�
    CStringA printerName;  // �� AddToServerBegin() ��д
    CStringA printerConn;  // �� AddToServerBegin() ��д
    CStringA printerModel; // �� AddToServerBegin() ��д
    void AddToServerBegin();
    void AddToServerEnd(DWORD ret);
    UINT AddToServer();

    // �Ƴ���ӡ��
    CStringA removedPrinterName;
    void RemoveFromServerBegin();
    void RemoveFromServerEnd(DWORD ret);
    UINT RemoveFromServer();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
