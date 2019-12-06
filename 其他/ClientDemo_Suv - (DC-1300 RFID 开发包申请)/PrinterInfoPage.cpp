// PrinterInfoPage.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PrinterInfoPage.h"
#include "afxdialogex.h"

#define WM_QUERY_DONE (WM_USER + 0x0)
bool firstrun = true;
// CPrinterInfoPage 对话框

IMPLEMENT_DYNAMIC(CPrinterInfoPage, CPropertyPage)

CPrinterInfoPage::CPrinterInfoPage()
	: CPropertyPage(CPrinterInfoPage::IDD, IDS_MAINTENANCE_PAGE_1),
    notActivated(TRUE) {}

CPrinterInfoPage::~CPrinterInfoPage()
{
    if (refresher) {
        WaitForSingleObject(refresher->m_hThread, INFINITE);
    }
}

BOOL CPrinterInfoPage::OnSetActive()
{
    BOOL ret = CPropertyPage::OnSetActive();

    if (notActivated) {
        notActivated = FALSE;
        StartRefresh();
    }

    return ret;
}

void CPrinterInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrinterInfoPage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON1, &CPrinterInfoPage::OnBnClickedButton1)
    ON_MESSAGE(WM_QUERY_DONE, &CPrinterInfoPage::OnRefreshDone)
END_MESSAGE_MAP()

// CPrinterInfoPage 消息处理程序
void CPrinterInfoPage::OnBnClickedButton1()
{
	StartRefresh();
}

static uint32_t GetRunningInfo(CStringA &s, int func)
{
    uint32_t ret;
    unsigned char *sbuf;
    int slen;

    sbuf = (unsigned char *)s.GetBuffer(256);
    slen = 256;

    //ret = DASSetNetworkParams(
    //    (char*)(const char*)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    //if (ret != 0)
    //    goto done;

    ret = DASSetPrinterName(
        GetApp().GetPrinter().name,
        GetApp().GetPrinter().model);
    if (ret != 0)
        goto done;

    ret = DASGetRunningInfo(func, sbuf, &slen);

done:
    if (ret != 0) {
        s.ReleaseBuffer(0);
    } else {
        s.ReleaseBuffer(slen);
    }

    return ret;
}

static CString ParseUnsigned(CStringA &s)
{
    CString ret;
    int value = 0;

    for (int i = 0; i < s.GetLength(); ++i)
    {
        value += ((unsigned char)s[i] << (i * 8));
    }

    ret.Format(TEXT("%d"), value);
    return ret;
}

static uint32_t GetCycleRemaining(int *cnt)
{
    uint32_t ret;

    //ret = DASSetNetworkParams(
    //    (char*)(const char*)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    //if (ret != 0)
    //    goto done;

    ret = DASSetPrinterName(
        GetApp().GetPrinter().name,
        GetApp().GetPrinter().model);
    if (ret != 0)
        goto done;

    ret = DASCanPrintTotalPreClean(cnt);

done:
    return ret;
}

static uint32_t GetSensorStatus(unsigned char *status)
{
    uint32_t ret;
    int i = 5;

    //ret = DASSetNetworkParams(
    //    (char*)(const char*)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    //if (ret != 0)
    //    goto done;

    ret = DASSetPrinterName(
        GetApp().GetPrinter().name,
        GetApp().GetPrinter().model);
    if (ret != 0)
        goto done;

    ret = DASGetPrinterCardPos(status, &i);

done:
    return ret;
}

static uint32_t GetFanStatus(uint32_t &fanStatus)
{
    uint32_t ret;
    uint64_t status;

    //ret = DASSetNetworkParams(
    //    (char*)(const char*)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    //if (ret != 0)
    //    goto done;

    ret = DASSetPrinterName(
        GetApp().GetPrinter().name,
        GetApp().GetPrinter().model);
    if (ret != 0)
        goto done;

    ret = DASFetchPrinterStatus(&status);
    if (ret != 0)
        goto done;

    fanStatus = DASGetFanStatus(status);

done:
    return ret;
}

static uint32_t GetHeadTemperature(int &temperature)
{
    uint32_t ret;

    //ret = DASSetNetworkParams(
    //    (char*)(const char*)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    //if (ret != 0)
    //    goto done;

    ret = DASSetPrinterName(
        GetApp().GetPrinter().name,
        GetApp().GetPrinter().model);
    if (ret != 0)
        goto done;

    ret = DASGetPrtHeadTemperature(&temperature);

done:
    return ret;
}

UINT CPrinterInfoPage::RefreshMain(LPVOID param)
{
	DWORD T1 = GetTickCount();
    CPrinterInfoPage *_this = reinterpret_cast<CPrinterInfoPage*>(param);
    PrinterInfo &info = _this->info;
    CStringA s;
    uint32_t ret;

    // 清理上一次的查询结果
    info.model.Empty();
    info.firmwareVersion.Empty();
    info.serial.Empty();
    info.maxCycle.Empty();
    info.cycleCnt.Empty();
    info.currentCycleRemaining.Empty();
    info.totalInCnt.Empty();
    info.headChangeCnt.Empty();
    info.feedPosHasCard.Empty();
    info.printPosHasCard.Empty();
    info.cardBoxNotEmpty.Empty();
    info.fanInUse.Empty();
    info.headAtHome.Empty();
    info.doorOpen.Empty();
    info.headTemperature.Empty();
    info.headSerial.Empty();
    info.headMaxCycle.Empty();
    info.headCycleCnt.Empty();
    info.headTotalInCnt.Empty();
#define NOP ;
    // 执行查询
#define GET_SFIELD(func, f)\
    ret = GetRunningInfo(s, func);\
    if (ret != 0) break;\
    f = s

#define GET_UFIELD(func, f)\
    ret = GetRunningInfo(s, func);\
    if (ret != 0) break;\
    f.Format(ParseUnsigned(s))\

    do {
        GET_SFIELD(1, info.model); // 型号
        GET_SFIELD(2, info.serial); // 序列号
        GET_SFIELD(3, info.firmwareVersion); // 固件版本
        GET_UFIELD(9, info.maxCycle); // 最大清洁周期
        GET_UFIELD(11, info.cycleCnt); // 当前机器清洁次数
        GET_UFIELD(10, info.totalInCnt); // 总进卡次数
        GET_UFIELD(4, info.headChangeCnt); // 打印头更换次数

        {
			NOP;
            int i;
            ret = GetCycleRemaining(&i); // 下次清洁前可进卡次数
            if (ret != 0) break;
            info.currentCycleRemaining.Format(TEXT("%d"), i);
			NOP;
        }

        {
            unsigned char statuss[5];
            ret = GetSensorStatus(statuss);
            if (ret != 0) break;
            info.feedPosHasCard = (statuss[0] & 0x1) ? TEXT("进卡口有卡") : TEXT("进卡口无卡");
            info.doorOpen = (statuss[0] & 0x2) ? TEXT("前盖闭合") : TEXT("前盖打开");
            info.printPosHasCard = (statuss[0] & 0x4) ? TEXT("打印位有卡") : TEXT("打印位无卡");
            info.headAtHome = (statuss[0] & 0x8) ? TEXT("印头未归位") : TEXT("印头已归位");
            info.cardBoxNotEmpty = (statuss[0] & 0x10) ? TEXT("卡盒有卡") : TEXT("卡盒无卡");
			NOP;
        }

        {
            uint32_t statusf;
            ret = GetFanStatus(statusf);
            if (ret != 0) break;
            info.fanInUse = statusf ?
                TEXT("风扇正在运行") : TEXT("风扇静止");
			NOP;
        }

        {
            int temperature;
            ret = GetHeadTemperature(temperature); // 印头温度
            if (ret != 0) break;
            info.headTemperature.Format(TEXT("%d"), temperature);
			NOP;
        }

        GET_SFIELD(5, info.headSerial);
        GET_UFIELD(6, info.headMaxCycle);
        GET_UFIELD(8, info.headCycleCnt);
        GET_UFIELD(7, info.headTotalInCnt);
    } while (0);

#undef GET_SFIELD
#undef GET_UFIELD
// 	do 
// 	{
// 		BYTE flag = 0;
// 		ret = DASGetPrintSpeed(&flag);
// 		if(ret)break;
// 		info.printSpd.Format(L"%d",flag);
// 		ret = DASGetPrintTemperature(&flag);
// 		if(ret)break;
// 		info.printTep.Format(L"%d",flag);
// 		ret = DASGetEraseTemperature(&flag);
// 		if(ret)break;
// 		info.eraseTep.Format(L"%d",flag);
// 	} while (0);

    // 通知更新主界面。
    // 尝试而不保证消息抵达：窗口可能已经销毁
    HWND hwnd = _this->m_hWnd;
    if (hwnd) {
        ::PostMessage(hwnd, WM_QUERY_DONE, ret, 0);
    }
	T1 = GetTickCount() - T1;

    return 0;
}

void CPrinterInfoPage::StartRefresh()
{
    // 禁用“刷新”按钮
    GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
   
    // TODO : 显示一个查询中的GIF

    // 启动工作线程
    refresher.reset(new CWinThread(RefreshMain, this));
    refresher->m_bAutoDelete = FALSE;
    refresher->CreateThread();
}

LRESULT CPrinterInfoPage::OnRefreshDone(WPARAM ret, LPARAM)
{
    CString s;

    // 更新界面信息
    SetDlgItemText(IDC_STA_MODEL, info.model);
    SetDlgItemText(IDC_STA_SERIAL, info.serial);
    SetDlgItemText(IDC_STA_VERSION, info.firmwareVersion);
    SetDlgItemText(IDC_STA_MAX_CYCLE, info.maxCycle);
    SetDlgItemText(IDC_STA_CYCLES, info.cycleCnt);
    SetDlgItemText(IDC_STA_INSERTION, info.totalInCnt);
    SetDlgItemText(IDC_STA_HEAD_INDEX, info.headChangeCnt);
    SetDlgItemText(IDC_STA_CYCLE_REMAINING, info.currentCycleRemaining);
    SetDlgItemText(IDC_STA_SENINPUT, info.feedPosHasCard);
    SetDlgItemText(IDC_STA_SENCONVEYER, info.printPosHasCard);
    SetDlgItemText(IDC_STA_SENCARDBOX, info.cardBoxNotEmpty);
    SetDlgItemText(IDC_STA_SENFAN, info.fanInUse);
    SetDlgItemText(IDC_STA_SENHEAD, info.headAtHome);
    SetDlgItemText(IDC_STA_SENHEADTEMP, info.headTemperature);
    SetDlgItemText(IDC_STA_SENCOVER, info.doorOpen);

    SetDlgItemText(IDC_STA_HEAD_SERIAL, CString(info.headSerial));
    SetDlgItemText(IDC_STA_HEAD_MAX_CYCLE, info.headMaxCycle);
    SetDlgItemText(IDC_STA_HEAD_CYCLES, info.headCycleCnt);
    SetDlgItemText(IDC_STA_HEAD_INSERTION, info.headTotalInCnt);


    // TODO : 停止显示GIF

    // 启用“刷新”按钮
    GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);

    if (ret != 0) {
        MessageBox(TEXT("查询时遇到错误，部分内容未获得"), TEXT("维护打印机"), MB_OK);
    }

    return 0;
}