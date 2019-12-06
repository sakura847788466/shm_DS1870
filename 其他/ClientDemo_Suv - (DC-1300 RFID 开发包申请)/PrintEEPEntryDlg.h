#pragma once
#include "afxwin.h"
#include "afxdtctl.h"

enum EntryRegion
{
    HongKong, Macau
};

enum EntryType {

    // 探亲(T)签
    TQuarterlyOnce = 0,
    TQuarterlyMultiple,
    TYearlyMultiple,

    // 商务(S)签
    SQuarterlyOnce,
    SQuarterlyMultiple,
    SYearlyMultiple,

    // 团队旅游(L)签
    LQuarterlyOnce,
    LQuarterlyTwice,
    LYearlyOnce,
    LYearlyTwice,

    // 个人旅游(G)签
    GQuarterlyOnce,
    GQuarterlyTwice,
    GYearlyOnce,
    GYearlyTwice,
    GYearlyMultiple,

    // 逗留(D)签
    D,

    // 其它(Q)签
    QQuarterlyOnce,
    QQuarterlyTwice,
    QQuarterlyMultiple
};

enum DurationOfStay {
    ThreeDay = 0,
    SevenDay,
    FourteenDay,
    NinetyDayOnFirstEnter,
    NinetyDay,
    Unlimited // 仅逗留(D)签注
};

// 打印港澳通行证签注
class CPrintEEPEntryDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrintEEPEntryDlg)

public:
	CPrintEEPEntryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrintEEPEntryDlg();

    // 对话框数据
	enum { IDD = IDD_PRINTEEPENTRYDLG };

private:
    BOOL GetHKEntryType(EntryType &);
    BOOL GetMOEntryType(EntryType &);
    BOOL GetHKDurationOfStay(DurationOfStay &);
    BOOL GetMODurationOfStay(DurationOfStay &);

    void InitHKEntryTypes();
    void InitMOEntryTypes();
    void UpdateHKDurationEntries();
    void UpdateMODurationEntries();

    BOOL DoDrawing();
    BOOL DoPrint();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bHKChecked;
    BOOL m_bMOChecked;
    afx_msg void OnBnClickedChkHk();
    afx_msg void OnBnClickedChkMo();
    afx_msg void OnBnClickedOk();
    CComboBox m_cmbHKEntryType;
    CDateTimeCtrl m_dtHKEffectDate;
    CDateTimeCtrl m_dtHKExpireDate;
    CComboBox m_cmbHKDurationOfStay;
    CComboBox m_cmbMOEntryType;
    CDateTimeCtrl m_dtMOEffectDate;
    CDateTimeCtrl m_dtMOExpireDate;
    CComboBox m_cmbMODurationOfStay;
    afx_msg void OnCbnSelchangeCmbHkEntryType();
    afx_msg void OnCbnSelchangeCmbMoEntryType();
    CString m_sEEPNO;
    afx_msg void OnEnChangeTxtEepno();
    afx_msg void OnDtnDatetimechangeDtHkEffectDate(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDtnDatetimechangeDtMoEffectDate(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedOk3();
};
