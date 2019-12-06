#pragma once


// CPasswordAlter 对话框

class CPasswordAlter : public CPropertyPage
{
	DECLARE_DYNAMIC(CPasswordAlter)

public:
	CPasswordAlter();
	virtual ~CPasswordAlter();

// 对话框数据
	enum { IDD = PrinterHeader_and_key1_key2_setup };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	CString m_strPwd1;
	CString m_strPwd2;
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton22();
	CString m_PrinterHeadID_B;
	afx_msg void OnBnClickedButton24();
	CString m_printerHeadNumber_A;
	afx_msg void OnBnClickedButton23();
};
