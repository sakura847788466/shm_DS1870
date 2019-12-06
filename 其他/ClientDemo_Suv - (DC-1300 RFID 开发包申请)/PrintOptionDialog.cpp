// PrintOptionDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PrintOptionDialog.h"
#include "afxdialogex.h"


// CPrintOptionDialog 对话框

#define CheckRes(res) if(res !=0){CString str;str.Format(L"设置失败：%x",res);MessageBox(str);}
IMPLEMENT_DYNAMIC(CPrintOptionDialog, CDialog)

CPrintOptionDialog::CPrintOptionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintOptionDialog::IDD, pParent)
{
}

CPrintOptionDialog::~CPrintOptionDialog()
{
}

void CPrintOptionDialog::ReloadOptions()
{
    options = GetApp().GetCurrentJob();

    // 优先级
    CString priorityStr;
    priorityStr.Format(_T("%d"), options.priority);
    m_txtJobPriority.SetWindowText(priorityStr);

    // 打印方向
    CheckDlgButton(IDC_RADIO_PRINT_DIRECTION_HORIZONTAL, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_PRINT_DIRECTION_VERTICAL, BST_UNCHECKED);
    if (options.printDirection == CD_PD_HORIZONTAL) {
        CheckDlgButton(IDC_RADIO_PRINT_DIRECTION_HORIZONTAL, BST_CHECKED);
    } else {
        CheckDlgButton(IDC_RADIO_PRINT_DIRECTION_VERTICAL, BST_CHECKED);
    }

    // 半色调算法
    CheckDlgButton(IDC_RADIO_HALFTONE_METHOD_ERROR_DIFFUSION, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_HALFTONE_METHOD_THRESHOLD, BST_UNCHECKED);

    if (options.halftoneMethod == CD_HM_ERROR_DIFFUSION) {
        CheckDlgButton(IDC_RADIO_HALFTONE_METHOD_ERROR_DIFFUSION, BST_CHECKED);
    } else {
        CheckDlgButton(IDC_RADIO_HALFTONE_METHOD_THRESHOLD, BST_CHECKED);
    }

    // 半色调阈值
    CString thresholdStr;
    thresholdStr.Format(_T("%d"), options.halftoneThreshold);
    m_txtHalftoneThreshold.SetWindowText(thresholdStr);

    // 擦除方式和擦除图像
    CheckDlgButton(IDC_RADIO_ERASE_SETTING_ERASE_ALL, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_ERASE_SETTING_NO_ERASE, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_ERASE_SETTING_USE_MASK, BST_UNCHECKED);
    if (options.eraseMethod == CD_EM_ERASE_ALL) {
        CheckDlgButton(IDC_RADIO_ERASE_SETTING_ERASE_ALL, BST_CHECKED);
        m_btnBrowseEraseMask.EnableWindow(FALSE);
        m_txtEraseMaskPath.EnableWindow(FALSE);
    } else if (options.eraseMethod == CD_EM_NO_ERASE) {
        CheckDlgButton(IDC_RADIO_ERASE_SETTING_NO_ERASE, BST_CHECKED);
        m_btnBrowseEraseMask.EnableWindow(FALSE);
        m_txtEraseMaskPath.EnableWindow(FALSE);
    } else {
        CheckDlgButton(IDC_RADIO_ERASE_SETTING_USE_MASK, BST_CHECKED);
        m_btnBrowseEraseMask.EnableWindow(TRUE);
        m_txtEraseMaskPath.EnableWindow(TRUE);
    }
    m_txtEraseMaskPath.SetWindowText(CString(options.erasePath));

    // 打印速度、打印对比度、打印温度、擦除温度
    m_sldPrintSpeed.SetPos(options.printSpeed);
    m_spinPrintSpeed.SetPos(options.printSpeed);
    m_sldPrintContrast.SetPos(options.printContrast);
    m_spinPrintContrast.SetPos(options.printContrast);
    m_sldPrintTemperature.SetPos(options.printTemperature);
    m_spinPrintTemperature.SetPos(options.printTemperature);
    m_sldEraseTemperature.SetPos(options.eraseTemperature);
    m_spinEraseTemperature.SetPos(options.eraseTemperature);

    // 薄卡
    CheckDlgButton(IDC_RADIO_CARD_TYPE_BLACK, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_CARD_TYPE_BLUE, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_CARD_TYPE_THIN, BST_UNCHECKED);
    if (options.cardType == CD_CT_MITSUBISHI_BLACK) {
        CheckDlgButton(IDC_RADIO_CARD_TYPE_BLACK, BST_CHECKED);
    } else if (options.cardType == CD_CT_MITSUBISHI_BLUE) {
        CheckDlgButton(IDC_RADIO_CARD_TYPE_BLUE, BST_CHECKED);
    } else {
        CheckDlgButton(IDC_RADIO_CARD_TYPE_THIN, BST_CHECKED);
    }

    // 出卡方式
    CheckDlgButton(IDC_RADIO_EJECT_METHOD_MANUAL, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_EJECT_METHOD_AUTO, BST_UNCHECKED);
    if (options.ejectMode == CD_EJM_MANUAL) {
        CheckDlgButton(IDC_RADIO_EJECT_METHOD_MANUAL, BST_CHECKED);
    } else {
        CheckDlgButton(IDC_RADIO_EJECT_METHOD_AUTO, BST_CHECKED);
    }

    // 进卡方式
    CheckDlgButton(IDC_RADIO_FEED_METHOD_MANUAL, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_FEED_METHOD_FEED_BOX, BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_FEED_METHOD_AUTO, BST_UNCHECKED);
    if (options.feedMode == CD_FM_MANUAL) {
        CheckDlgButton(IDC_RADIO_FEED_METHOD_MANUAL, BST_CHECKED);
    } else if (options.feedMode == CD_FM_FEED_BOX) {
        CheckDlgButton(IDC_RADIO_FEED_METHOD_FEED_BOX, BST_CHECKED);
    } else {
        CheckDlgButton(IDC_RADIO_FEED_METHOD_AUTO, BST_CHECKED);
    }
}

void CPrintOptionDialog::ApplyOptions()
{
    auto &job = GetApp().GetCurrentJob();
    options.imagePath = job.imagePath;
    options.copyCount = job.copyCount;
    job = options;
}

LRESULT CPrintOptionDialog::OnSliderScroll(WPARAM, LPARAM lParam)
{
    HWND sliderHwnd = (HWND)(lParam);
    if (sliderHwnd == m_sldPrintSpeed.GetSafeHwnd()) {
        OnSldPrintSpeedScroll();
    } else if (sliderHwnd == m_sldPrintContrast.GetSafeHwnd()) {
        OnSldPrintContrastScroll();
    } else if (sliderHwnd == m_sldPrintTemperature.GetSafeHwnd()) {
        OnSldPrintTemperatureScroll();
    } else if (sliderHwnd == m_sldEraseTemperature.GetSafeHwnd()) {
        OnSldEraseTemperatureScroll();
    }
    return 0;
}

void CPrintOptionDialog::OnSldPrintSpeedScroll()
{
    options.printSpeed = m_sldPrintSpeed.GetPos();
    m_spinPrintSpeed.SetPos(options.printSpeed);
}

void CPrintOptionDialog::OnSldPrintContrastScroll()
{
    options.printContrast = m_sldPrintContrast.GetPos();
    m_spinPrintContrast.SetPos(options.printContrast);
}

void CPrintOptionDialog::OnSldPrintTemperatureScroll()
{
    options.printTemperature = m_sldPrintTemperature.GetPos();
    m_spinPrintTemperature.SetPos(options.printTemperature);
}

void CPrintOptionDialog::OnSldEraseTemperatureScroll()
{
    options.eraseTemperature = m_sldEraseTemperature.GetPos();
    m_spinEraseTemperature.SetPos(options.eraseTemperature);
}

void CPrintOptionDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TXT_JOB_PRIORITY, m_txtJobPriority);
    DDX_Control(pDX, IDC_TXT_HALFTONE_THRESHOLD, m_txtHalftoneThreshold);
    DDX_Control(pDX, IDC_BTN_BROWSE_ERASE_MASK, m_btnBrowseEraseMask);
    DDX_Control(pDX, IDC_TXT_ERASE_MASK_PATH, m_txtEraseMaskPath);
    DDX_Control(pDX, IDC_SLD_PRINT_SPEED, m_sldPrintSpeed);
    DDX_Control(pDX, IDC_TXT_PRINT_SPEED, m_txtPrintSpeed);
    DDX_Control(pDX, IDC_SPIN_PRINT_SPEED, m_spinPrintSpeed);
    DDX_Control(pDX, IDC_SLD_PRINT_CONTRAST, m_sldPrintContrast);
    DDX_Control(pDX, IDC_TXT_PRINT_CONTRAST, m_txtPrintContrast);
    DDX_Control(pDX, IDC_SPIN_PRINT_CONTRAST, m_spinPrintContrast);
    DDX_Control(pDX, IDC_SLD_PRINT_TEMPERATURE, m_sldPrintTemperature);
    DDX_Control(pDX, IDC_TXT_PRINT_TEMPERATURE, m_txtPrintTemperature);
    DDX_Control(pDX, IDC_SPIN_PRINT_TEMPERATURE, m_spinPrintTemperature);
    DDX_Control(pDX, IDC_SLD_ERASE_TEMPERATURE, m_sldEraseTemperature);
    DDX_Control(pDX, IDC_TXT_ERASE_TEMPERATURE, m_txtEraseTemperature);
    DDX_Control(pDX, IDC_SPIN_ERASE_TEMPERATURE, m_spinEraseTemperature);
}

BOOL CPrintOptionDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_txtJobPriority.SetLimitText(2);
    
    m_txtHalftoneThreshold.SetLimitText(5);

    m_sldPrintSpeed.SetRange(0, 20);
    m_txtPrintSpeed.SetLimitText(2);
    m_spinPrintSpeed.SetRange(0, 20);
    
    m_sldPrintContrast.SetRange(0, 20);
    m_txtPrintContrast.SetLimitText(2);
    m_spinPrintContrast.SetRange(0, 20);
    
    m_sldPrintTemperature.SetRange(0, 20);
    m_txtPrintTemperature.SetLimitText(2);
    m_spinPrintTemperature.SetRange(0, 20);
    
    m_sldEraseTemperature.SetRange(0, 20);
    m_txtEraseTemperature.SetLimitText(2);
    m_spinEraseTemperature.SetRange(0, 20);

    ReloadOptions();
// 	OnBnClickedButton21();
// 	OnBnClickedButton22();
// 	OnBnClickedButton23();
// 	OnBnClickedButton24();
    return TRUE;
}

BEGIN_MESSAGE_MAP(CPrintOptionDialog, CDialog)
    ON_BN_CLICKED(IDOK, &CPrintOptionDialog::OnBnClickedOk)
    ON_EN_CHANGE(IDC_TXT_JOB_PRIORITY, &CPrintOptionDialog::OnEnChangeTxtJobPriority)
    ON_BN_CLICKED(IDC_RADIO_PRINT_DIRECTION_HORIZONTAL, &CPrintOptionDialog::OnBnClickedRadioPrintDirectionHorizontal)
    ON_BN_CLICKED(IDC_RADIO_PRINT_DIRECTION_VERTICAL, &CPrintOptionDialog::OnBnClickedRadioPrintDirectionVertical)
    ON_BN_CLICKED(IDC_RADIO_HALFTONE_METHOD_THRESHOLD, &CPrintOptionDialog::OnBnClickedRadioHalftoneMethodThreshold)
    ON_BN_CLICKED(IDC_RADIO_HALFTONE_METHOD_ERROR_DIFFUSION, &CPrintOptionDialog::OnBnClickedRadioHalftoneMethodErrorDiffusion)
    ON_EN_CHANGE(IDC_TXT_HALFTONE_THRESHOLD, &CPrintOptionDialog::OnEnChangeTxtHalftoneThreshold)
    ON_BN_CLICKED(IDC_RADIO_ERASE_SETTING_ERASE_ALL, &CPrintOptionDialog::OnBnClickedRadioEraseSettingEraseAll)
    ON_BN_CLICKED(IDC_RADIO_ERASE_SETTING_NO_ERASE, &CPrintOptionDialog::OnBnClickedRadioEraseSettingNoErase)
    ON_BN_CLICKED(IDC_RADIO_ERASE_SETTING_USE_MASK, &CPrintOptionDialog::OnBnClickedRadioEraseSettingUseMask)
    ON_BN_CLICKED(IDC_BTN_BROWSE_ERASE_MASK, &CPrintOptionDialog::OnBnClickedBtnBrowseEraseMask)
    ON_MESSAGE(WM_HSCROLL, &CPrintOptionDialog::OnSliderScroll)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRINT_SPEED, &CPrintOptionDialog::OnDeltaposSpinPrintSpeed)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRINT_CONTRAST, &CPrintOptionDialog::OnDeltaposSpinPrintContrast)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRINT_TEMPERATURE, &CPrintOptionDialog::OnDeltaposSpinPrintTemperature)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ERASE_TEMPERATURE, &CPrintOptionDialog::OnDeltaposSpinEraseTemperature)
    ON_EN_KILLFOCUS(IDC_TXT_PRINT_SPEED, &CPrintOptionDialog::OnEnKillfocusTxtPrintSpeed)
    ON_EN_KILLFOCUS(IDC_TXT_PRINT_CONTRAST, &CPrintOptionDialog::OnEnKillfocusTxtPrintContrast)
    ON_EN_KILLFOCUS(IDC_TXT_PRINT_TEMPERATURE, &CPrintOptionDialog::OnEnKillfocusTxtPrintTemperature)
    ON_EN_KILLFOCUS(IDC_TXT_ERASE_TEMPERATURE, &CPrintOptionDialog::OnEnKillfocusTxtEraseTemperature)
    ON_BN_CLICKED(IDC_RADIO_CARD_TYPE_BLACK, &CPrintOptionDialog::OnBnClickedRadioCardTypeBlack)
    ON_BN_CLICKED(IDC_RADIO_CARD_TYPE_BLUE, &CPrintOptionDialog::OnBnClickedRadioCardTypeBlue)
    ON_BN_CLICKED(IDC_RADIO_CARD_TYPE_THIN, &CPrintOptionDialog::OnBnClickedRadioCardTypeThin)
    ON_BN_CLICKED(IDC_RADIO_EJECT_METHOD_MANUAL, &CPrintOptionDialog::OnBnClickedRadioEjectMethodManual)
    ON_BN_CLICKED(IDC_RADIO_EJECT_METHOD_AUTO, &CPrintOptionDialog::OnBnClickedRadioEjectMethodAuto)
    ON_BN_CLICKED(IDC_RADIO_FEED_METHOD_MANUAL, &CPrintOptionDialog::OnBnClickedRadioFeedMethodManual)
    ON_BN_CLICKED(IDC_RADIO_FEED_METHOD_CARD_BOX, &CPrintOptionDialog::OnBnClickedRadioFeedMethodFeedBox)
    ON_BN_CLICKED(IDC_RADIO_FEED_METHOD_AUTO, &CPrintOptionDialog::OnBnClickedRadioFeedMethodAuto)
    ON_BN_CLICKED(IDC_BTN_RESET_OPTIONS, &CPrintOptionDialog::OnBnClickedBtnResetOptions)
	ON_BN_CLICKED(IDC_RADIO_FEED_METHOD_MANUAL2, &CPrintOptionDialog::OnBnClickedRadioFeedMethodManual2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPrintOptionDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON18, &CPrintOptionDialog::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CPrintOptionDialog::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CPrintOptionDialog::OnBnClickedButton20)

END_MESSAGE_MAP()

// CPrintOptionDialog 消息处理程序

void CPrintOptionDialog::OnBnClickedOk()
{
    if (options.priority > 10) {
        MessageBox(_T("任务优先级应介于 0 到 10 之间。"));
        m_txtJobPriority.SetSel(0, -1);
        m_txtJobPriority.SetFocus();
        return;
    }

    if (options.halftoneThreshold < 0 ||
        options.halftoneThreshold > 255) {
        MessageBox(_T("半色调阈值应介于 0 到 255 之间。"));
        m_txtHalftoneThreshold.SetSel(0, -1);
        m_txtHalftoneThreshold.SetFocus();
        return;
    }

    if (options.eraseMethod == CD_EM_USE_MASK &&
        options.erasePath.GetLength() == 0) {
        MessageBox(_T("请选择要使用的擦除掩码位图。"));
        m_txtEraseMaskPath.SetFocus();
        return;
    }

    ApplyOptions();
    CDialog::OnOK();
}

void CPrintOptionDialog::OnEnChangeTxtJobPriority()
{
    CString priority;
    bool valid = true;
    bool found;

    m_txtJobPriority.GetWindowText(priority);
    
    // 删除每个非数字字符
    do {
        found = false;
        for (int i = 0; i < priority.GetLength(); ++i) {
            if (!::_istdigit(priority[i])) {
                found = true;
                valid = false;
                priority.Delete(i);
                break;
            }
        }
    } while (found);

    // 如果输入无效，重设输入框内容
    if (!valid) {
        if (priority.GetLength() == 0) {
            priority = _T("0");
        }
        m_txtJobPriority.SetWindowText(priority);
    }
    
    // 更新选项的值
    options.priority = ::_tcstol(priority, nullptr, 10);
}

void CPrintOptionDialog::OnBnClickedRadioPrintDirectionHorizontal()
{
    options.printDirection = CD_PD_HORIZONTAL;
}

void CPrintOptionDialog::OnBnClickedRadioPrintDirectionVertical()
{
    options.printDirection = CD_PD_VERTICAL;
}

void CPrintOptionDialog::OnBnClickedRadioHalftoneMethodThreshold()
{
    options.halftoneMethod = CD_HM_THRESHOLDING;
}

void CPrintOptionDialog::OnBnClickedRadioHalftoneMethodErrorDiffusion()
{
    options.halftoneMethod = CD_HM_ERROR_DIFFUSION;
}

void CPrintOptionDialog::OnEnChangeTxtHalftoneThreshold()
{
    CString threshold;
    bool valid = true;
    bool found;

    m_txtHalftoneThreshold.GetWindowText(threshold);
    
    // 删除每个非数字字符
    do {
        found = false;
        for (int i = 0; i < threshold.GetLength(); ++i) {
            if (!::_istdigit(threshold[i])) {
                found = true;
                valid = false;
                threshold.Delete(i);
                break;
            }
        }
    } while (found);

    // 如果输入无效，重设输入框内容
    if (!valid) {
        if (threshold.GetLength() == 0) {
            threshold = _T("128");
        }
        m_txtHalftoneThreshold.SetWindowText(threshold);
    }
    
    // 更新选项的值
    options.halftoneThreshold = ::_tcstol(threshold, nullptr, 10);
}

void CPrintOptionDialog::OnBnClickedRadioEraseSettingEraseAll()
{
    options.eraseMethod = CD_EM_ERASE_ALL;
    options.erasePath = "";
    m_btnBrowseEraseMask.EnableWindow(FALSE);
    m_txtEraseMaskPath.EnableWindow(FALSE);
}

void CPrintOptionDialog::OnBnClickedRadioEraseSettingNoErase()
{
    options.eraseMethod = CD_EM_NO_ERASE;
    options.erasePath = "";
    m_btnBrowseEraseMask.EnableWindow(FALSE);
    m_txtEraseMaskPath.EnableWindow(FALSE);
}

void CPrintOptionDialog::OnBnClickedRadioEraseSettingUseMask()
{
    options.eraseMethod = CD_EM_USE_MASK;
    CString erasePathT;
    m_btnBrowseEraseMask.EnableWindow(TRUE);
    m_txtEraseMaskPath.EnableWindow(TRUE);
    m_txtEraseMaskPath.GetWindowText(erasePathT);
    options.erasePath = erasePathT;
}

void CPrintOptionDialog::OnBnClickedBtnBrowseEraseMask()
{
    CFileDialog dialog(
        TRUE,
        _T("jpg"),
        nullptr,
        OFN_PATHMUSTEXIST | OFN_ENABLESIZING | OFN_EXPLORER | OFN_HIDEREADONLY,
        _T("位图文件(*.bmp)|*.bmp||"),
        this);

    if (dialog.DoModal() == IDOK) {
        CImage image;
        image.Load(dialog.GetPathName());
        if (image.GetWidth() != 1016 || image.GetHeight() != 648 ||
            image.GetBPP() != 1) {
            MessageBox(_T("掩码文件必须是宽度为1016像素，高度为648像素的黑白位图！"));
            return;
        }
		
        m_txtEraseMaskPath.SetWindowText(dialog.GetPathName());
        options.erasePath = dialog.GetPathName();
    }
}

void CPrintOptionDialog::OnDeltaposSpinPrintSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    options.printSpeed = pNMUpDown->iDelta + pNMUpDown->iPos;
    m_sldPrintSpeed.SetPos(options.printSpeed);
    *pResult = 0;
}

void CPrintOptionDialog::OnDeltaposSpinPrintContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    options.printContrast = pNMUpDown->iDelta + pNMUpDown->iPos;
    m_sldPrintContrast.SetPos(options.printContrast);
    *pResult = 0;
}

void CPrintOptionDialog::OnDeltaposSpinPrintTemperature(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    options.printTemperature = pNMUpDown->iDelta + pNMUpDown->iPos;
    m_sldPrintTemperature.SetPos(options.printTemperature);
    *pResult = 0;
}

void CPrintOptionDialog::OnDeltaposSpinEraseTemperature(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    options.printSpeed = pNMUpDown->iDelta + pNMUpDown->iPos;
    m_sldEraseTemperature.SetPos(options.printSpeed);
    *pResult = 0;
}

void CPrintOptionDialog::OnEnKillfocusTxtPrintSpeed()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
    CString text;
    m_txtPrintSpeed.GetWindowText(text);
    options.printSpeed = ::wcstol(text, nullptr, 10);
    m_sldPrintSpeed.SetPos(options.printSpeed);
}

void CPrintOptionDialog::OnEnKillfocusTxtPrintContrast()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
    CString text;
    m_txtPrintContrast.GetWindowText(text);
    options.printContrast = ::wcstol(text, nullptr, 10);
    m_sldPrintContrast.SetPos(options.printContrast);
}

void CPrintOptionDialog::OnEnKillfocusTxtPrintTemperature()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
    CString text;
    m_txtPrintTemperature.GetWindowText(text);
    options.printTemperature = ::wcstol(text, nullptr, 10);
    m_sldPrintTemperature.SetPos(options.printTemperature);
}

void CPrintOptionDialog::OnEnKillfocusTxtEraseTemperature()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
    CString text;
    m_txtEraseTemperature.GetWindowText(text);
    options.eraseTemperature = ::wcstol(text, nullptr, 10);
    m_sldEraseTemperature.SetPos(options.eraseTemperature);
}

void CPrintOptionDialog::OnBnClickedRadioCardTypeBlack()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.cardType = CD_CT_MITSUBISHI_BLACK;return;
    auto res = DASSetCardType(options.cardType = CD_CT_MITSUBISHI_BLACK);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioCardTypeBlue()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.cardType = CD_CT_MITSUBISHI_BLUE;return;
    auto res = DASSetCardType(options.cardType = CD_CT_MITSUBISHI_BLUE);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioCardTypeThin()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.cardType = CD_CT_EXTRA_THIN;return;
    auto res = DASSetCardType(options.cardType = CD_CT_EXTRA_THIN);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioEjectMethodManual()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.ejectMode = CD_EJM_MANUAL;return;
    auto res = DASSetCardExitPositon(options.ejectMode = CD_EJM_MANUAL);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioEjectMethodAuto()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.ejectMode = CD_EJM_AUTO;return;
    auto res = DASSetCardExitPositon(options.ejectMode = CD_EJM_AUTO);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioFeedMethodManual()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.feedMode = CD_FM_MANUAL;return;
    auto res = DASSetCardInjectPositon(options.feedMode = CD_FM_MANUAL);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioFeedMethodFeedBox()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.feedMode = CD_FM_FEED_BOX;return;
    auto res = DASSetCardInjectPositon(options.feedMode = CD_FM_FEED_BOX);CheckRes(res)
}

void CPrintOptionDialog::OnBnClickedRadioFeedMethodAuto()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	options.feedMode = CD_FM_AUTO;return;
    auto res = DASSetCardInjectPositon(options.feedMode = CD_FM_AUTO);CheckRes(res)
}


void CPrintOptionDialog::OnBnClickedBtnResetOptions()
{
    auto &job = GetApp().GetCurrentJob();
    job.Reset();
    ReloadOptions();
}


void CPrintOptionDialog::OnBnClickedRadioFeedMethodManual2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPrintOptionDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPrintOptionDialog::OnBnClickedButton1()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_PRINT_SPEED);
	auto m_int=pSlidCtrl->GetPos();//取得当前位置值  

	auto res = DASSetPrintSpeed(m_int);CheckRes(res)
}


void CPrintOptionDialog::OnBnClickedButton18()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_PRINT_CONTRAST);
	auto m_int=pSlidCtrl->GetPos();//取得当前位置值  

	auto res = DASSetCardContrast(m_int);CheckRes(res)
}


void CPrintOptionDialog::OnBnClickedButton19()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_PRINT_TEMPERATURE);
	auto m_int=pSlidCtrl->GetPos();//取得当前位置值  

	auto res = DASSetPrintTemperature(m_int);CheckRes(res)
}


void CPrintOptionDialog::OnBnClickedButton20()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_ERASE_TEMPERATURE);
	auto m_int=pSlidCtrl->GetPos();//取得当前位置值  

	auto res = DASSetEraseTemperature(m_int);CheckRes(res)
}


