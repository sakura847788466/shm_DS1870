
// clientDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CclientDemoDlg 对话框
class CClientDemoDlg : public CDialogEx
{
// 构造
public:
	CClientDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
    void     InitPrinterControls();
    void     InitJobControls();

    bool     printByDrawing;
    CImage   image;
    void     DisplayImage();
    void     RotateImage();
    RECT     CalcStretchedRect(int outputWidth, int outputHeight);
    void     StretchImage(int outputWidth, int outputHeight);
    void     TryEnablePrint();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

    CEdit m_txtPrinterName;
    CButton m_btnShowPrinterPicker;
    CButton m_btnShowPrinterMaintenanceDlg;
    CButton m_btnSelectImage;
    CEdit m_txtImagePath;
    CButton m_btnEditImage;
    CEdit m_txtCopyCount;
    CButton m_btnPrint;
    CButton m_btnShowPrintOptionDlg;

    afx_msg void OnBnClickedBtnShowPrinterPicker();
    afx_msg void OnBnClickedBtnSelectImage();
    CStatic m_imgImage;
    afx_msg void OnBnClickedBtnShowPrintOptions();
    afx_msg void OnBnClickedBtnPrint();
    afx_msg void OnBnClickedBtnShowPrinterMaintenanceDialog();
    afx_msg void OnEnChangeCopyCount();
    afx_msg void OnBnClickedRadioCreateByFile();
    afx_msg void OnBnClickedRadioByDrawing();
    afx_msg void OnBnClickedBtnEditImage();
    CButton m_btnPrintSARPass;
    afx_msg void OnBnClickedBtnPrintSarPass();
	CButton m_dontEject;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedBtnPrint2();
	afx_msg void OnBnClickedBtnPrint3();
	afx_msg void OnBnClickedBtnPrint4();
	afx_msg void OnBnClickedBtnPrint5();
	afx_msg void OnBnClickedButton1();
};
