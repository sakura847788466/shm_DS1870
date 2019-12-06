// PrinterMaintenanceDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PrinterMaintenanceDialog.h"
#include "afxdialogex.h"


// CPrinterMaintenanceDialog 对话框

IMPLEMENT_DYNAMIC(CPrinterMaintenanceDialog, CDialog)

CPrinterMaintenanceDialog::CPrinterMaintenanceDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrinterMaintenanceDialog::IDD, pParent)
    , m_printerStatus(_T(""))
    , m_xOffset(0)
    , m_yOffset(0)
    , m_chroma(0)
{

}

CPrinterMaintenanceDialog::~CPrinterMaintenanceDialog()
{
}

void CPrinterMaintenanceDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TXT_PRINTER_STATUS, m_printerStatus);
    DDX_Text(pDX, IDC_EDIT1, m_xOffset);
    DDX_Text(pDX, IDC_EDIT2, m_yOffset);
    DDX_Text(pDX, IDC_EDIT3, m_chroma);
}


BEGIN_MESSAGE_MAP(CPrinterMaintenanceDialog, CDialog)
    ON_BN_CLICKED(IDC_BTN_CLEAN_PRINTER, &CPrinterMaintenanceDialog::OnBnClickedBtnCleanPrinter)
    ON_BN_CLICKED(IDC_BTN_PRINT_TEST_CARD, &CPrinterMaintenanceDialog::OnBnClickedBtnPrintTestCard)
    ON_BN_CLICKED(IDC_BTN_ERASE_CARD, &CPrinterMaintenanceDialog::OnBnClickedBtnEraseCard)
    ON_BN_CLICKED(IDC_BTN_GET_PRINTER_STATUS, &CPrinterMaintenanceDialog::OnBnClickedBtnGetPrinterStatus)
    ON_BN_CLICKED(IDC_BUTTON1, &CPrinterMaintenanceDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CPrinterMaintenanceDialog::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CPrinterMaintenanceDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPrinterMaintenanceDialog 消息处理程序

void CPrinterMaintenanceDialog::OnBnClickedBtnCleanPrinter()
{
    if (IDOK == MessageBox(
        _T("请将清洁卡放入打印机，并按下OK按钮开始清洁打印机。"),
        nullptr,
        MB_OKCANCEL)) {
        uint32_t ret;
        //ret = ::DASSetNetworkParams(
        //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
        //    GetApp().GetServer().GetPort());
        ret = ::DASSetPrinterName(
            (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
            (LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if  ( ret == DS_CPSDK_OK ){
			ret = ::DASCleanPrinter();
			if (0 == ret) {
				MessageBox(_T("清洁命令已发送。"));
			} else {
				MessageBox(_T("清洁命令发送失败：") +
					GetApp().TranslateErrorCode(ret));
			}
		}else{
			MessageBox(_T("X轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
		}
    }
}

void CPrinterMaintenanceDialog::OnBnClickedBtnPrintTestCard()
{
    uint32_t ret;
    //ret = ::DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    ret = ::DASSetPrinterName(
        (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
        (LPSTR)(LPCSTR)GetApp().GetPrinter().model);
	if ( ret == DS_CPSDK_OK ){
		ret = ::DASPrintTestCard();
		if (0 == ret) {
			MessageBox(_T("打印测试卡命令已发送。"));
		} else {
			MessageBox(_T("打印测试卡命令发送失败：") +
				GetApp().TranslateErrorCode(ret));
		}
	}else{
		MessageBox(_T("X轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
	}
}

static bool IsAllXDigit(const CStringA &s)
{
    for (int i = 0; i < s.GetLength(); ++i) {
        if (!::isxdigit(s[i]))
            return false;
    }

    return true;
}

static bool hex2raw(const CStringA &hex, CStringA &raw)
{
    if (hex.GetLength() % 2)
        return false;

    raw.GetBufferSetLength(hex.GetLength() / 2);

    for (int i = 0; i < hex.GetLength(); i += 2) {
        unsigned char high = (unsigned char)toupper(hex[i]);
        unsigned char low  = (unsigned char)toupper(hex[i + 1]);
        if (!isxdigit(high) || !isxdigit(low))
            return false;
        high = ((high <= '9') ? (high - '0') : (high - 'A' + 0xA));
        low  = ((low  <= '9') ? (low  - '0') : (low  - 'A' + 0xA));
        raw.SetAt(i / 2, (high << 4) | low);
    }

    return true;
}



void CPrinterMaintenanceDialog::OnBnClickedBtnEraseCard()
{
    uint32_t ret;
    //ret = ::DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    ret = ::DASSetPrinterName(
        (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
        (LPSTR)(LPCSTR)GetApp().GetPrinter().model);
	if ( ret == DS_CPSDK_OK ){
		ret = ::DASEraseCard();
		if (0 == ret) {
			MessageBox(_T("擦除卡片命令已发送。"));
		} else {
			MessageBox(_T("擦除卡片命令发送失败：") +
				GetApp().TranslateErrorCode(ret));
		}
	}else{
		MessageBox(_T("X轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
	}
}

void CPrinterMaintenanceDialog::OnBnClickedBtnGetPrinterStatus()
{
    uint32_t ret;
    //ret = DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    ret = ::DASSetPrinterName(
        (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
        (LPSTR)(LPCSTR)GetApp().GetPrinter().model);

	if  ( ret == DS_CPSDK_OK){
		uint64_t status;
		ret = ::DASFetchPrinterStatus(&status);
		if (0 == ret) {
			uint32_t err = DASGetPrinterStatus_ErrorNo(status);
			uint32_t fcm = DASGetFeedCardMode(status);
			uint32_t cln = DASGetCleaningStatus(status);
			uint32_t fan = DASGetFanStatus(status);
			uint32_t cbs = DASGetPrinterStatus_CardBoxStatus(status);
			uint32_t fcs = DASGetPrinterStatus_FrontCoverStatus(status);
			uint32_t buffs  = DASGetRecvBufferStatus(status);
			uint32_t busy =	DASGetBusyStatus(status);

			m_printerStatus.Format(_T("错误码 0x%02X，"), err);
			m_printerStatus +=
				((fcm == 0) ? _T("卡盒送卡") :
				 (fcm == 1) ? _T("手动装卡") :
				 (fcm == 2) ? _T("自动装卡") : _T("未知"));
			m_printerStatus += _T("，");
			m_printerStatus +=
				((cln == 0) ? _T("无需清洁") :
				 (cln == 1) ? _T("建议清洁") :
				 (cln == 2) ? _T("必须清洁") : _T("未知"));
			m_printerStatus += _T("，");
			m_printerStatus +=
				((fan == 0) ? _T("风扇关闭") :
				 (fan == 1) ? _T("风扇开启") : _T("未知"));
			m_printerStatus += _T("，");
			m_printerStatus +=
				((cbs == 0) ? _T("卡盒有卡") :
				 (cbs == 1) ? _T("卡盒无卡") : _T("未知"));
			m_printerStatus += _T("，");
			m_printerStatus +=
				((buffs == 0) ? _T("接收缓存不满") :
				 (buffs == 2) ? _T("接收缓存满") : _T("接收缓存空"));
			m_printerStatus += _T("，");
			m_printerStatus +=
				((busy == 0) ? _T("打印机空闲") :
				 (busy == 1) ? _T("打印机忙") : _T("未知"));
			m_printerStatus += _T("，");
			m_printerStatus +=        
				((fcs == 0) ? _T("前盖闭合") :
				 (fcs == 1) ? _T("前盖打开") : _T("未知"));
			UpdateData(FALSE);
		} else {
			MessageBox(_T("查询打印机状态失败：") +
				GetApp().TranslateErrorCode(ret));
		}
	}else{
		MessageBox(_T("查询打印机状态失败：") +	GetApp().TranslateErrorCode(ret));
	}
}

void CPrinterMaintenanceDialog::OnBnClickedButton1()
{
    if (UpdateData()) {
        uint32_t ret;
        //ret = ::DASSetNetworkParams(
        //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
        //    GetApp().GetServer().GetPort());
        ret = ::DASSetPrinterName(
            (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
            (LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if ( ret == DS_CPSDK_OK ){
			ret = ::DASsetXoffset(m_xOffset);
			if (0 == ret) {
				MessageBox(_T("X轴偏移调整命令已发送。"));
			} else {
				MessageBox(_T("X轴偏移调整命令发送失败：") +
					GetApp().TranslateErrorCode(ret));
			}
		}else{
			MessageBox(_T("X轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
    }
  }
}


void CPrinterMaintenanceDialog::OnBnClickedButton2()
{
    if (UpdateData()) {
        uint32_t ret;
        //ret = ::DASSetNetworkParams(
        //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
        //    GetApp().GetServer().GetPort());
        ret = ::DASSetPrinterName(
            (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
            (LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if  (ret == DS_CPSDK_OK)
		{
			ret = ::DASsetYoffset(m_yOffset);
			if (0 == ret) {
				MessageBox(_T("Y轴偏移调整命令已发送。"));
			} else {
				MessageBox(_T("Y轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
			}
		}else{
			MessageBox(_T("X轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
		}
    }
}

void CPrinterMaintenanceDialog::OnBnClickedButton3()
{
    if (UpdateData()) {
        uint32_t ret;

        ret = ::DASSetPrinterName(
            (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
            (LPSTR)(LPCSTR)GetApp().GetPrinter().model);

		if  (ret == DS_CPSDK_OK){
			ret = ::DASsetPrintChroma(m_chroma);
			if (0 == ret) {
				MessageBox(_T("打印浓度调整命令已发送。"));
			} else {
				MessageBox(_T("打印浓度调整命令发送失败：") +
					GetApp().TranslateErrorCode(ret));
			}
		}else{
			MessageBox(_T("X轴偏移调整命令发送失败：") +	GetApp().TranslateErrorCode(ret));
		}
    }
}
