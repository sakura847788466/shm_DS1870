#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPrintOptionDialog 对话框

class CPrintOptionDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrintOptionDialog)

public:
	CPrintOptionDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrintOptionDialog();

// 对话框数据
	enum { IDD = IDD_PRINTOPTIONDIALOG };

private:
    Job options;
    void ReloadOptions();
    void ApplyOptions();

    
public:
    // 用于处理滑动条的自定义窗口消息函数
    LRESULT OnSliderScroll(WPARAM wParam, LPARAM lParam);
    void OnSldPrintSpeedScroll();
    void OnSldPrintContrastScroll();
    void OnSldPrintTemperatureScroll();
    void OnSldEraseTemperatureScroll();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    CEdit m_txtJobPriority;
    afx_msg void OnEnChangeTxtJobPriority();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnBnClickedRadioPrintDirectionHorizontal();
    afx_msg void OnBnClickedRadioPrintDirectionVertical();
    afx_msg void OnBnClickedRadioHalftoneMethodThreshold();
    afx_msg void OnBnClickedRadioHalftoneMethodErrorDiffusion();
    CEdit m_txtHalftoneThreshold;
    afx_msg void OnEnChangeTxtHalftoneThreshold();
    afx_msg void OnBnClickedRadioEraseSettingEraseAll();
    afx_msg void OnBnClickedRadioEraseSettingNoErase();
    afx_msg void OnBnClickedRadioEraseSettingUseMask();
    CButton m_btnBrowseEraseMask;
    CEdit m_txtEraseMaskPath;
    afx_msg void OnBnClickedBtnBrowseEraseMask();
    CSliderCtrl m_sldPrintSpeed;
    CEdit m_txtPrintSpeed;
    CSpinButtonCtrl m_spinPrintSpeed;
    CSliderCtrl m_sldPrintContrast;
    CEdit m_txtPrintContrast;
    CSpinButtonCtrl m_spinPrintContrast;
    CSliderCtrl m_sldPrintTemperature;
    CEdit m_txtPrintTemperature;
    CSpinButtonCtrl m_spinPrintTemperature;
    CSliderCtrl m_sldEraseTemperature;
    CEdit m_txtEraseTemperature;
    CSpinButtonCtrl m_spinEraseTemperature;
    afx_msg void OnDeltaposSpinPrintSpeed(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposSpinPrintContrast(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposSpinPrintTemperature(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposSpinEraseTemperature(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnKillfocusTxtPrintSpeed();
    afx_msg void OnEnKillfocusTxtPrintContrast();
    afx_msg void OnEnKillfocusTxtPrintTemperature();
    afx_msg void OnEnKillfocusTxtEraseTemperature();
    afx_msg void OnBnClickedRadioCardTypeBlack();
    afx_msg void OnBnClickedRadioCardTypeBlue();
    afx_msg void OnBnClickedRadioCardTypeThin();
    afx_msg void OnBnClickedRadioEjectMethodManual();
    afx_msg void OnBnClickedRadioEjectMethodAuto();
    afx_msg void OnBnClickedRadioFeedMethodManual();
    afx_msg void OnBnClickedRadioFeedMethodFeedBox();
    afx_msg void OnBnClickedRadioFeedMethodAuto();
    afx_msg void OnBnClickedBtnResetOptions();
	afx_msg void OnBnClickedRadioFeedMethodManual2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
};
