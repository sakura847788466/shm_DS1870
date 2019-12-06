#pragma once
#include "afxwin.h"


// CPrinterMaintenanceDialog 对话框

class CPrinterMaintenanceDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrinterMaintenanceDialog)

public:
	CPrinterMaintenanceDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrinterMaintenanceDialog();

// 对话框数据
	enum { IDD = IDD_PRINTERMAINTENANCEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnCleanPrinter();
    afx_msg void OnBnClickedBtnPrintTestCard();
    afx_msg void OnBnClickedBtnEraseCard();
    afx_msg void OnBnClickedBtnGetPrinterStatus();
    CString m_printerStatus;
    int m_xOffset;
    int m_yOffset;
    int m_chroma;
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
};
