#pragma once
#include "afxwin.h"
#include "afxdtctl.h"

enum EntryRegion
{
    HongKong, Macau
};

enum EntryType {

    // ̽��(T)ǩ
    TQuarterlyOnce = 0,
    TQuarterlyMultiple,
    TYearlyMultiple,

    // ����(S)ǩ
    SQuarterlyOnce,
    SQuarterlyMultiple,
    SYearlyMultiple,

    // �Ŷ�����(L)ǩ
    LQuarterlyOnce,
    LQuarterlyTwice,
    LYearlyOnce,
    LYearlyTwice,

    // ��������(G)ǩ
    GQuarterlyOnce,
    GQuarterlyTwice,
    GYearlyOnce,
    GYearlyTwice,
    GYearlyMultiple,

    // ����(D)ǩ
    D,

    // ����(Q)ǩ
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
    Unlimited // ������(D)ǩע
};

// ��ӡ�۰�ͨ��֤ǩע
class CPrintEEPEntryDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrintEEPEntryDlg)

public:
	CPrintEEPEntryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrintEEPEntryDlg();

    // �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
