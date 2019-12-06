#pragma once


// CPrinterInfoPage 对话框

typedef struct PrinterInfoTag {

    // 打印机信息
    CString model; // 机器型号
    CString firmwareVersion; // 固件版本
    CString serial; // 机器序列号
    CString maxCycle; // 最大清洁周期
    CString cycleCnt; // 清洁次数
    CString currentCycleRemaining; // 本清洁周期剩余可进卡次数
    CString totalInCnt; // 总进卡次数
    CString headChangeCnt; // 打印头更换次数

    // 传感器
    CString feedPosHasCard; // 进卡口是否有卡
    CString printPosHasCard; // 打印位置是否有卡
    CString cardBoxNotEmpty; // 卡盒是否有卡
    CString fanInUse; // 风扇是否正在工作
    CString headAtHome; // 打印头是否归位
    CString doorOpen; // 前盖是否打开
    CString headTemperature; // 打印头温度

    // 打印头信息
    CString headSerial;
    CString headMaxCycle;
    CString headCycleCnt;
    CString headTotalInCnt;

// 	// 打印速度、温度，擦除温度
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

// 对话框数据
	enum { IDD = IDD_PRINTERINFOPAGE };

    virtual BOOL OnSetActive();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    // “刷新”按钮支持
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
