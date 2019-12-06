
// ToolRWLicenseDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "resource.h"

// CToolRWLicenseDlg 对话框
class CToolRWLicenseDlg : public CDialogEx
{
// 构造
public:
	CToolRWLicenseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOOLRWLICENSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CListBox m_printlist;
	void output(const CString str);
	CEdit m_output;
	afx_msg void OnBnClickedButton3();
	DWORD SetPrinterName();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	CButton m_epcid_isstring;
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton15();
};
