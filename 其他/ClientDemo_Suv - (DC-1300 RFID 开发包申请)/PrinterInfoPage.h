#pragma once


// CPrinterInfoPage �Ի���

typedef struct PrinterInfoTag {

    // ��ӡ����Ϣ
    CString model; // �����ͺ�
    CString firmwareVersion; // �̼��汾
    CString serial; // �������к�
    CString maxCycle; // ����������
    CString cycleCnt; // ������
    CString currentCycleRemaining; // ���������ʣ��ɽ�������
    CString totalInCnt; // �ܽ�������
    CString headChangeCnt; // ��ӡͷ��������

    // ������
    CString feedPosHasCard; // �������Ƿ��п�
    CString printPosHasCard; // ��ӡλ���Ƿ��п�
    CString cardBoxNotEmpty; // �����Ƿ��п�
    CString fanInUse; // �����Ƿ����ڹ���
    CString headAtHome; // ��ӡͷ�Ƿ��λ
    CString doorOpen; // ǰ���Ƿ��
    CString headTemperature; // ��ӡͷ�¶�

    // ��ӡͷ��Ϣ
    CString headSerial;
    CString headMaxCycle;
    CString headCycleCnt;
    CString headTotalInCnt;

// 	// ��ӡ�ٶȡ��¶ȣ������¶�
// 	CString printSpd;
// 	CString printTep;
// 	CString eraseTep;

} PrinterInfo;

class CPrinterInfoPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPrinterInfoPage)

public:
	CPrinterInfoPage();
	virtual ~CPrinterInfoPage();

// �Ի�������
	enum { IDD = IDD_PRINTERINFOPAGE };

    virtual BOOL OnSetActive();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

    // ��ˢ�¡���ť֧��
private:
    PrinterInfo info;
    std::unique_ptr<CWinThread> refresher;
    static UINT RefreshMain(LPVOID);
    void StartRefresh();

private:
    BOOL notActivated;

public:
    afx_msg void OnBnClickedButton1();
    afx_msg LRESULT OnRefreshDone(WPARAM, LPARAM);
    
};
