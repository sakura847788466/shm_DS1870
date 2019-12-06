// DrawCardDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DrawCardDialog.h"
#include "afxdialogex.h"



// CDrawCardDialog 对话框

IMPLEMENT_DYNAMIC(CDrawCardDialog, CDialog)

CDrawCardDialog::CDrawCardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawCardDialog::IDD, pParent)
    , m_sizeSet(false)
    , m_coordX(0)
    , m_coordY(0)
    , m_width(0)
    , m_height(0)
    , m_txtData(_T(""))
    , m_fontSize(0)
    , m_bold(0)
    , m_italic(0)
    , m_underline(0)
    , m_qrAutoFill(0)
    , m_qrReliability(0)
    , m_barcodeType(0)
    , m_barcodeReadableLabel(FALSE)
    , m_bHasContent(FALSE)
    , m_printDirection(0)
	, m_printRotation(0)
    , m_barcodeLabelAsHeader(FALSE)
    , m_verticalText(FALSE)
    , m_reversedTextOrder(FALSE)
    , m_layDown(FALSE)
    , m_barcodeScale(0)
	, m_FeedLine(FALSE)
	, m_LineSpacing(0)
	, m_charSpacing(0)
    , m_imagePath(_T(""))
    , m_whiteAsTransparent(FALSE)
	, m_whiteAsTransparentBase64(FALSE)
	, m_imageBase64(_T(""))
	, m_ImgBase64Suffix(_T(""))
	, m_printRotationBase64(0)
{

}

CDrawCardDialog::~CDrawCardDialog()
{
}

BOOL CDrawCardDialog::OnInitDialog()
{
    //::DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
     uint32_t  ret=::DASSetPrinterName(
        (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
        (LPSTR)(LPCSTR)GetApp().GetPrinter().model);
    // ::DASsetCardSize(85.6, 54.0);

	 CDialog::OnInitDialog();
	 m_cmbFontName.SelectString(0, _T("宋体"));
	 UpdateDataToView();

	GetDlgItem(IDC_EDIT11)->SetWindowText(L"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");
	GetDlgItem(IDC_EDIT12)->SetWindowText(L".gif");

	if  ( ret == DS_CPSDK_OK ){
		::EnableWindow(GetDlgItem(IDC_CHECK6)->m_hWnd, FALSE);
		return TRUE;
	}else{
		return FALSE;
	}
	//::ShowWindow(GetDlgItem(IDOK3)->GetSafeHwnd(),SW_HIDE);
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
//	BYTE flag = 0;
// 	auto re = DASGetEjectMode(&flag);
// 	CheckDlgButton(IDC_CHECK1,flag);
/*	GetDlgItem(IDOK3)->ShowWindow(flag);*/
}

BOOL CDrawCardDialog::UpdateDataToView()
{
    return UpdateData(FALSE);
}

BOOL CDrawCardDialog::UpdateViewToData()
{
    return UpdateData(TRUE);
}

void CDrawCardDialog::SetCardSize()
{
	UpdateViewToData();

	if (!m_sizeSet) {
		m_sizeSet = true;
		if (m_printDirection == 0) {
			::DASsetCardSize(85.6, 54.0);
		} else {
			::DASsetCardSize(54.0, 85.6);
		}
		::EnableWindow(GetDlgItem(IDC_COMBO1)->m_hWnd, FALSE);
	}
}

void CDrawCardDialog::DisableAddProtectionRect()
{
    ::EnableWindow(GetDlgItem(IDC_BUTTON4)->m_hWnd, FALSE);
}

void CDrawCardDialog::log(const CString &line)
{
    m_txtInfo += line;
    m_txtInfo += _T("\r\n");
    m_txtInfoCtrl.SetWindowText(m_txtInfo);
    m_txtInfoCtrl.LineScroll(m_txtInfoCtrl.GetLineCount());
}

void CDrawCardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_coordX);
	DDX_Text(pDX, IDC_EDIT3, m_coordY);
	DDX_Text(pDX, IDC_EDIT5, m_width);
	DDX_Text(pDX, IDC_EDIT6, m_height);
	DDX_Text(pDX, IDC_EDIT1, m_txtData);
	DDX_Text(pDX, IDC_EDIT4, m_fontSize);
	//DDX_Text(pDX, IDC_EDIT7, m_txtInfo);
	DDX_Control(pDX, IDC_EDIT7, m_txtInfoCtrl);
	DDX_Check(pDX, IDC_CHECK1, m_bold);
	DDX_Check(pDX, IDC_CHECK2, m_italic);
	DDX_Check(pDX, IDC_CHECK3, m_underline);
	DDX_Check(pDX, IDC_CHECK4, m_qrAutoFill);
	DDX_CBIndex(pDX, IDC_COMBO2, m_qrReliability);
	DDX_CBIndex(pDX, IDC_COMBO3, m_barcodeType);
	DDX_Check(pDX, IDC_CHECK5, m_barcodeReadableLabel);
	DDX_Check(pDX, IDC_CHECK6, m_barcodeLabelAsHeader);
	DDX_Control(pDX, IDC_MFCFONTCOMBO1, m_cmbFontName);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_btnTextColor);
	DDV_MinMaxDouble(pDX, m_coordX, 0.0, DBL_MAX);
	DDV_MinMaxDouble(pDX, m_coordY, 0.0, DBL_MAX);
	DDV_MinMaxDouble(pDX, m_width, 0.0, DBL_MAX);
	DDV_MinMaxDouble(pDX, m_height, 0.0, DBL_MAX);
	//    DDV_MinMaxInt(pDX, m_fontSize, 0, 255);
	DDX_CBIndex(pDX, IDC_COMBO1, m_printDirection);
	DDX_CBIndex(pDX, IDC_COMBO5, m_printRotation);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_btnBarcodeColor);
	DDX_Check(pDX, IDC_CHECK7, m_verticalText);
	DDX_Check(pDX, IDC_CHECK8, m_reversedTextOrder);
	DDX_Check(pDX, IDC_CHECK9, m_layDown);
	DDX_CBIndex(pDX, IDC_CMB_SCALE, m_barcodeScale);
	DDX_Check(pDX, IDC_CHECK10, m_FeedLine);
	DDX_Text(pDX, IDC_EDIT8, m_LineSpacing);
	DDX_Text(pDX, IDC_EDIT9, m_charSpacing);
	DDX_Text(pDX, IDC_EDIT10, m_imagePath);
	DDX_Check(pDX, IDC_CHECK11, m_whiteAsTransparent);
	DDX_Check(pDX, IDC_CHECK13, m_whiteAsTransparentBase64);
	DDX_Text(pDX, IDC_EDIT11, m_imageBase64);
	DDX_Text(pDX, IDC_EDIT12, m_ImgBase64Suffix);
	DDX_CBIndex(pDX, IDC_COMBO6, m_printRotationBase64);
}

BEGIN_MESSAGE_MAP(CDrawCardDialog, CDialog)
    ON_EN_CHANGE(IDC_EDIT2, &CDrawCardDialog::OnEnChangeEdit2)
    ON_EN_CHANGE(IDC_EDIT3, &CDrawCardDialog::OnEnChangeEdit3)
    ON_EN_CHANGE(IDC_EDIT5, &CDrawCardDialog::OnEnChangeEdit5)
    ON_EN_CHANGE(IDC_EDIT6, &CDrawCardDialog::OnEnChangeEdit6)
    ON_EN_CHANGE(IDC_EDIT1, &CDrawCardDialog::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT4, &CDrawCardDialog::OnEnChangeEdit4)
    ON_BN_CLICKED(IDC_CHECK1, &CDrawCardDialog::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &CDrawCardDialog::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK3, &CDrawCardDialog::OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &CDrawCardDialog::OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &CDrawCardDialog::OnBnClickedCheck5)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CDrawCardDialog::OnCbnSelchangeCombo2)
    ON_CBN_SELCHANGE(IDC_COMBO3, &CDrawCardDialog::OnCbnSelchangeCombo3)
    ON_BN_CLICKED(IDOK, &CDrawCardDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDC_CHECK6, &CDrawCardDialog::OnBnClickedCheck6)
    ON_BN_CLICKED(IDC_CHECK7, &CDrawCardDialog::OnBnClickedCheck7)
    ON_BN_CLICKED(IDC_CHECK8, &CDrawCardDialog::OnBnClickedCheck8)
    ON_BN_CLICKED(IDC_CHECK9, &CDrawCardDialog::OnBnClickedCheck9)
    ON_CBN_SELCHANGE(IDC_CMB_SCALE, &CDrawCardDialog::OnCbnSelchangeCmbScale)
	ON_BN_CLICKED(IDOK, &CDrawCardDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDrawCardDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDrawCardDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDrawCardDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDrawCardDialog::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CDrawCardDialog::OnBnClickedButton5)
	ON_BN_CLICKED(IDCANCEL, &CDrawCardDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON6, &CDrawCardDialog::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CDrawCardDialog::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &CDrawCardDialog::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CDrawCardDialog::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_BUTTON25, &CDrawCardDialog::OnBnClickedButton25)
	ON_BN_CLICKED(IDOK2, &CDrawCardDialog::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &CDrawCardDialog::OnBnClickedOk3)
	ON_BN_CLICKED(IDC_CHECK12, &CDrawCardDialog::OnBnClickedCheck12)
END_MESSAGE_MAP()

void CDrawCardDialog::OnEnChangeEdit2()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnEnChangeEdit3()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnEnChangeEdit5()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnEnChangeEdit6()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnEnChangeEdit1()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnEnChangeEdit4()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck1()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck2()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck3()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck4()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck5()
{
    UpdateViewToData();
    if (m_barcodeReadableLabel) {
        ::EnableWindow(GetDlgItem(IDC_CHECK6)->m_hWnd, TRUE);
    } else {
        ::EnableWindow(GetDlgItem(IDC_CHECK6)->m_hWnd, FALSE);
    }
}

void CDrawCardDialog::OnCbnSelchangeCombo2()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnCbnSelchangeCombo3()
{
    UpdateViewToData();
}

#include <sstream> 
#include <iostream>
template<class out_T,class in_T>
out_T _C(in_T data)
{
	std::stringstream iostrm;
	iostrm<<data;
	out_T o;
	iostrm>>o;
	return o;
}
void CDrawCardDialog::OnBnClickedButton1()
{
	UpdateViewToData();
    uint32_t ret;
    CString line;

    SetCardSize();

    CString fontNameT;
    m_cmbFontName.GetLBText(m_cmbFontName.GetCurSel(), fontNameT);
    if (m_layDown) {
        fontNameT = _T("@") + fontNameT;
    }
	CString a;
	((CEdit*)(GetDlgItem(IDC_EDIT4)))->GetWindowText(a);

	float fontsize_ = _ttof(a.GetBuffer());
    line.Format(_T("设置字体（名称 = %s，大小 = %f）"),
        (LPCTSTR)fontNameT, fontsize_);
    CStringA fontName(fontNameT);
    if (0 == (ret = ::DASsetFont((LPCSTR)fontName, fontsize_))) {
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }


    COLORREF color = m_btnTextColor.GetColor();
    line.AppendFormat(_T("设置字体颜色为RGB(%d, %d, %d)"),
        GetRValue(color), GetGValue(color), GetBValue(color));
    ret = ::DASsetTextColor(
        GetRValue(color),
        GetGValue(color),
        GetBValue(color));
    if (0 == ret) {
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    CString delim;
    CString attributes;
    if (m_bold) {
        attributes = _T("粗体");
        delim = _T("，");
    }
    if (m_italic) {
        attributes += delim;
        attributes += _T("斜体");
        delim = _T("，");
    }
    if (m_underline) {
        attributes += delim;
        attributes += _T("下划线");
    }
    if (!attributes.GetLength()) {
        attributes = _T("正常");
    }
    line.AppendFormat(_T("设置字体修饰（%s）"), (LPCTSTR)attributes);
    ret = ::DASsetTextDecorate(!!m_bold, !!m_italic, !!m_underline);
    if (0 == ret) {
        line.Append(_T("成功\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    line.AppendFormat(_T("设置打印方向为%s%s%s"),
        (m_verticalText ? _T("竖排、") : _T("横排、")),
		(m_reversedTextOrder ? _T("倒序、") : _T("顺序、")),
        (m_FeedLine==TRUE ? _T("换行") : _T("截断")));
    ret = ::DASsetTextDirection(!m_verticalText, !!m_reversedTextOrder,m_FeedLine==TRUE?true:false);
    if (0 == ret) {
        line.Append(_T("成功\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

	line.AppendFormat(_T("设置行间距为%f字间距为%f"),	m_LineSpacing,m_charSpacing);

	ret = ::DASsetSpacing(m_LineSpacing,m_charSpacing);
	if (0 == ret) {
		line.Append(_T("成功\r\n"));
	} else {
		line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
		log(line);
		return;
	}

    CStringA text(m_txtData);
    line.AppendFormat(_T("添加文本到（X = %g，Y = %g，宽 = %g，高 = %g）"),
        m_coordX, m_coordY, m_width, m_height);
    if (0 == (ret = ::DASdrawText(m_coordX, m_coordY, m_width, m_height,(LPCSTR)text))) {
        line.Append(_T("成功"));
        m_bHasContent = TRUE;
        DisableAddProtectionRect();
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
    }
    log(line);
}

void CDrawCardDialog::OnBnClickedButton2()
{
    uint32_t ret;
    CString line;

    SetCardSize();

    COLORREF color = m_btnBarcodeColor.GetColor();
    line.AppendFormat(_T("设置条码/二维码颜色为RGB(%d, %d, %d)"),
        GetRValue(color), GetGValue(color), GetBValue(color));
    ret = ::DASsetBarCodeColor(GetRValue(color), GetGValue(color), GetBValue(color));
    if (0 == ret) {
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    CStringA data(m_txtData);
    line.AppendFormat(_T("添加QR码到（X = %g，Y = %g，宽 = %g，高 = %g）"),
        m_coordX, m_coordY, m_width, m_height);
    ret = ::DASdrawQR(m_coordX, m_coordY, m_width, m_height,
        (LPCSTR)data,
        m_qrReliability,
        true);
    if (0 == ret) {
        line.Append(_T("成功"));
        m_bHasContent = TRUE;
        DisableAddProtectionRect();
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
    }
    log(line);
}

void CDrawCardDialog::OnBnClickedButton3()
{
    uint32_t ret;
    CString line;

    SetCardSize();

    CString fontNameT;
    m_cmbFontName.GetLBText(m_cmbFontName.GetCurSel(), fontNameT);
    if (m_layDown) {
        fontNameT = _T("@") + fontNameT;
    }

    line.Format(_T("设置字体（名称 = %s，大小 = %d）"),
        (LPCTSTR)fontNameT, m_fontSize);
    CStringA fontName(fontNameT);
    if (0 == (ret = ::DASsetFont((LPCSTR)fontName, (unsigned char)m_fontSize))) {
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    COLORREF color = m_btnTextColor.GetColor();
    line.AppendFormat(_T("设置字体颜色为RGB(%d, %d, %d)"),
        GetRValue(color), GetGValue(color), GetBValue(color));
    ret = ::DASsetTextColor(GetRValue(color), GetGValue(color), GetBValue(color));
    if (0 == ret) {
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    CString delim;
    CString attributes;
    if (m_bold) {
        attributes = _T("粗体");
        delim = _T("，");
    }
    if (m_italic) {
        attributes += delim;
        attributes += _T("斜体");
        delim = _T("，");
    }
    if (m_underline) {
        attributes += delim;
        attributes += _T("下划线");
    }
    if (!attributes.GetLength()) {
        attributes = _T("正常");
    }
    line.AppendFormat(_T("设置字体修饰（%s）"), (LPCTSTR)attributes);
    ret = ::DASsetTextDecorate(!!m_bold, !!m_italic, !!m_underline);
    if (0 == ret) {
        line.Append(_T("成功\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    color = m_btnBarcodeColor.GetColor();
    line.AppendFormat(_T("设置条码/二维码颜色为RGB(%d, %d, %d)"),
        GetRValue(color), GetGValue(color), GetBValue(color));
    ret = ::DASsetBarCodeColor(GetRValue(color), GetGValue(color), GetBValue(color));
    if (0 == ret) {
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
        log(line);
        return;
    }

    CStringA data(m_txtData);
    line.AppendFormat(_T("添加条形码到（X = %g，Y = %g，宽 = %g，高 = %g）"),
        m_coordX, m_coordY, m_width, m_height);
    ret = ::DASdrawBarCode(m_coordX, m_coordY, m_width, m_height,
        m_barcodeType, (LPCSTR)data, !!m_barcodeReadableLabel,
        !m_barcodeLabelAsHeader, m_barcodeScale + 2);
    if (0 == ret) {
        line.Append(_T("成功"));
        m_bHasContent = TRUE;
        DisableAddProtectionRect();
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
    }
    log(line);
}

void CDrawCardDialog::OnBnClickedButton4()
{
    uint32_t ret;
    CString line;

    SetCardSize();
	line.Format(_T("添加保护区（X = %g，Y = %g，宽 = %g，高 = %g）"),
		m_coordX, m_coordY, m_width, m_height);
	if (0 == (ret = ::DASaddProtectedRect(m_coordX, m_coordY, m_width, m_height))) {
		DisableAddProtectionRect();
		line.Append(_T("成功。\r\n"));
	} else {
		line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
	}
	log(line);

}

void CDrawCardDialog::OnBnClickedOk()
{
    CString line;
    uint32_t ret;
    JobInfo  info;

    if (!m_bHasContent) {
        MessageBox(_T("没有绘制任何内容，请先绘制内容。"));
        return;
    }

    auto &printer = GetApp().GetPrinter();
    info.printer = printer.name;
    info.printerModel = printer.model;


    auto &job = GetApp().GetCurrentJob();
    if (job.copyCount <= 0 || job.copyCount > 65535) {
        MessageBox(_T("打印份数超出允许的范围（0 ~ 65535）"));
        return;
    }

    ret = ::DASSetCopies(job.copyCount);
    info.copyCount = job.copyCount;
    info.printedCopyCount = 0;

    //ret = ::DASSetPrintLevel(job.priority);
    info.priority = job.priority;

    ret = ::DASSetPrintDirection(job.printDirection);
    ret = ::DASSetBlackPrintMethod(job.halftoneMethod);
    ret = ::DASSetNthreshold(job.halftoneThreshold);
    if (job.eraseMethod != CD_EM_ERASE_ALL) {
        ret = ::DASSetEraseDataByFile(
            (LPSTR)(LPCSTR)job.erasePath,
            (job.eraseMethod == CD_EM_USE_MASK ? 0 : 1));
    }
    ret = ::DASSetPrintSpeed(job.printSpeed);
    ret = ::DASSetCardContrast(job.printContrast);
    ret = ::DASSetPrintTemperature(job.printTemperature);
    ret = ::DASSetEraseTemperature(job.eraseTemperature);
    ret = ::DAS_CardSet(
        job.cardType,
        0,
        0,
        job.ejectMode,
        0,
        job.feedMode,
        0);

	info.submitDate = time(nullptr);

	UpdateViewToData();
	BOOL DontEjectCard = ((CButton*)(GetDlgItem(IDC_CHECK12)))->GetCheck();
	if(DontEjectCard)
	{
		if (0 == (ret = ::DASBuildGraphicsData(true,true)) &&
			0 == (ret = ::DASPrintCard ())) {
				line.Append(_T("成功"));
				MessageBox(line);
		} else {
			line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
			MessageBox(line);
		}
	}
	else
	{
		if (0 == (ret = ::DASBuildGraphicsData(true,true))&&
			0 == (ret = ::DASPrintCard())) {
				line.Append(_T("成功"));
				MessageBox(line);
		} else {
			line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
			MessageBox(line);
		}
	}

	m_sizeSet = false;
	m_bHasContent = false;
	::EnableWindow(GetDlgItem(IDC_BUTTON4)->m_hWnd, TRUE);
	::EnableWindow(GetDlgItem(IDC_COMBO1)->m_hWnd, TRUE);

	ret= ::DASSetPrinterName(
		(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
		(LPSTR)(LPCSTR)GetApp().GetPrinter().model);

	if  ( ret > 0 ){
		MessageBox(_T("设置打印机失败。") + GetApp().TranslateErrorCode(ret));
		return;
	}
}

void CDrawCardDialog::OnBnClickedCancel()
{
    // 清理数据
    ::DASBuildGraphicsData(true, true);
    CDialog::OnCancel();


}

void CDrawCardDialog::OnBnClickedButton6()
{
    m_txtInfo = _T("");
    m_txtInfoCtrl.SetWindowText(m_txtInfo);
}

void CDrawCardDialog::OnBnClickedCheck6()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck7()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck8()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedCheck9()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnCbnSelchangeCmbScale()
{
    UpdateViewToData();
}

void CDrawCardDialog::OnBnClickedButton5()
{
	UpdateViewToData();
    CFileDialog fileDialog(
        TRUE,
        _T("jpg"),
        nullptr,
        OFN_PATHMUSTEXIST | OFN_ENABLESIZING | OFN_EXPLORER | OFN_HIDEREADONLY,
        _T("图像文件(*.jpeg;*.jpg;*.bmp;*.png;*.tif;*.gif)|*.jpeg;*.jpg;*.bmp;*.png;*.tif;*.gif|"),
        this);
    if (fileDialog.DoModal() == IDOK) {
		OutputDebugStringA("CDrawCardDialog IDOK");
        m_imagePath = fileDialog.GetPathName();
        UpdateDataToView();
    }else{
		OutputDebugStringA("CDrawCardDialog IDOK Failure");
		MessageBox(TEXT("选取图片失败"));
	}
}

void CDrawCardDialog::OnBnClickedButton7()
{
    UpdateViewToData();

    uint32_t ret;
    CString line;

    if (m_imagePath.IsEmpty()) {
        MessageBox(TEXT("请先选好要添加的图片"));
        return;
    }

    SetCardSize();

    line.Format(_T("添加图片（X = %g，Y = %g，宽 = %g，高 = %g）"),
        m_coordX, m_coordY, m_width, m_height);
    if (0 == (ret = ::DASdrawImageForRotation(m_coordX, m_coordY, m_width, m_height,
        (CStringA)m_imagePath, (m_whiteAsTransparent ? false : true),((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel()))) {
        DisableAddProtectionRect();
        m_bHasContent = TRUE;
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
    }
    log(line);
}

void CDrawCardDialog::OnBnClickedButton8()
{
    uint32_t ret;
    CString line;

    SetCardSize();

    line.Format(_T("添加擦除区（X = %g，Y = %g，宽 = %g，高 = %g）"),
        m_coordX, m_coordY, m_width, m_height);
    if (0 == (ret = ::DASaddNeedEraseRect(m_coordX, m_coordY, m_width, m_height))) {
        m_bHasContent = TRUE;
        DisableAddProtectionRect();
        line.Append(_T("成功。\r\n"));
    } else {
        line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
    }
    log(line);
}


void CDrawCardDialog::OnBnClickedMfccolorbutton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDrawCardDialog::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateViewToData();

	uint32_t ret;
	CString line;

	SetCardSize();

	line.Format(_T("添加Base64图片（X = %g，Y = %g，宽 = %g，高 = %g）"),
		m_coordX, m_coordY, m_width, m_height);
	if (0 == (ret = ::DASdrawBase64ImageForRotation(m_coordX, m_coordY, m_width, m_height,
		(CStringA)m_imageBase64, (CStringA)m_ImgBase64Suffix,(m_whiteAsTransparent ? false : true),m_printRotationBase64))) {
			DisableAddProtectionRect();
			m_bHasContent = TRUE;
			line.Append(_T("成功。\r\n"));
	} else {
		line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
	}
	log(line);
}




struct data{
	double X;
	double Y;
	double Width;
	double Height;
	int TextColorR;
	int TextColorB;
	int TextColorG;
	double TextSize;
	char* TextType;
	bool IsUnderLine;
	bool IsStronger;
	double LineSpacing;
	double CharSpacing;
	char* TextString;
};

void CDrawCardDialog::OnBnClickedOk2()
{

	uint64_t status;
	unsigned int num = DASFetchPrinterStatus(&status);
	if (num != 0u)
	{
		MessageBox(L"获取打印机状态失败，" +(num));
		return;
	}
// 	num = DASGetPrinterStatus_CardBoxStatus(status);
// 
// 	if (num != 0u)
// 	{
// 		MessageBox(L"卡盒未装上卡片！请确认卡片位置！");
// 		return;
// 	}
// 	num = DASGetPrinterStatus_FrontCoverStatus(status);
// 
// 	if (num != 0u)
// 	{
// 		MessageBox(L"打印机前盖打开！请确认是否安装好！");
// 		return;
// 	}
// 
// 	num = DASGetCleaningStatus(status);
// 
// 	if (num == 1)
// 	{
// 		MessageBox(L"建议清洁打印机！");
// 	}
// 	if (num == 2)
// 	{
// 		MessageBox(L"打印机必须清洁！");
// 		return;
// 	}
// 
// 	num = DASGetBusyStatus(status);
// 
// 	if (num != 0u)
// 	{
// 		MessageBox(L"打印机正忙！请稍等！");
// 		return;
// 	}
	/*
	string str = File.ReadAllText(Application.StartupPath + "\\label\\模板.txt", System.Text.Encoding.Default);
	string[] strs = str.ToString().Split('|');

	List<PrintData> listprintdata = new List<PrintData>();
	//因为 strs数组会最后会多一个 空的值，所以少循环一次
	for (int i = 0; i < strs.Length - 1; i++)
	{
		listprintdata.Add((JsonHelper.DeserializeJsonToObject<PrintData>(strs[i])));
	}
	listprintdata[1].TextString = dgvMain.SelectedRows[0].Cells["danhao"].Value.ToString().Trim();
	listprintdata[3].TextString = dgvMain.SelectedRows[0].Cells["bomhao"].Value.ToString();
	listprintdata[5].TextString = dgvMain.SelectedRows[0].Cells["colorname"].Value.ToString();
	listprintdata[7].TextString = dgvMain.SelectedRows[0].Cells["wpsize"].Value.ToString();
	listprintdata[9].TextString = dgvMain.SelectedRows[0].Cells["zhahao"].Value.ToString();
	listprintdata[11].TextString = dgvMain.SelectedRows[0].Cells["shuliang"].Value.ToString();
	string strerr = Printer_DASCOMDC.PrintDatas(listprintdata, cbbPrinter.Text);
	*/
	//constrct print data list
	std::vector<data> dataList;
	data printdata;
	printdata.X = 5.0;printdata.Y = 10.0;
	printdata.Width = 20.0;printdata.Height = 4.0;
	printdata.TextColorR = 0;printdata.TextColorB = 0;
	printdata.TextColorG = 0;printdata.TextSize = 9.0;
	printdata.TextType = "微软雅黑";printdata.IsUnderLine = false;
	printdata.IsStronger = false;printdata.LineSpacing = 1.0;
	printdata.CharSpacing = 0.5;printdata.TextString = "实裁单号:";
	dataList.push_back(printdata);
	data pd2;
	pd2.X=22.0;pd2.Y=10.0;pd2.Width=20.0;
	pd2.Height=4.0;pd2.TextColorR=0;pd2.TextColorB=0;
	pd2.TextColorG=0;pd2.TextSize=8.0;pd2.TextType="微软雅黑";
	pd2.IsUnderLine=false;pd2.IsStronger=false;
	pd2.LineSpacing=1.0;pd2.CharSpacing=0.5;pd2.TextString="实裁单号值";
	dataList.push_back(pd2);
	data pd3,pd4,pd5,pd6,pd7,pd8,pd9,pd10,pd11,pd12;
	pd3.X=5.0;pd3.Y=15.0;pd3.Width=20.0;pd3.Height=4.0;pd3.TextColorR=0;pd3.TextColorB=0;pd3.TextColorG=0;pd3.TextSize=8.0;pd3.TextType="微软雅黑";pd3.IsUnderLine=false;pd3.IsStronger=false;pd3.LineSpacing=1.0;pd3.CharSpacing=0.5;pd3.TextString="制令单号：";
	dataList.push_back(pd3);
	pd4.X=22.0;pd4.Y=15.0;pd4.Width=20.0;pd4.Height=4.0;pd4.TextColorR=0;pd4.TextColorB=0;pd4.TextColorG=0;pd4.TextSize=8.0;pd4.TextType="微软雅黑";pd4.IsUnderLine=false;pd4.IsStronger=false;pd4.LineSpacing=1.0;pd4.CharSpacing=0.5;pd4.TextString="制令单号值";
	pd5.X=5.0;pd5.Y=25.0;pd5.Width=20.0;pd5.Height=4.0;pd5.TextColorR=0;pd5.TextColorB=0;pd5.TextColorG=0;pd5.TextSize=8.0;pd5.TextType="微软雅黑";pd5.IsUnderLine=false;pd5.IsStronger=false;pd5.LineSpacing=1.0;pd5.CharSpacing=0.5;pd5.TextString="颜色：";
	pd6.X=15.0;pd6.Y=25.0;pd6.Width=20.0;pd6.Height=4.0;pd6.TextColorR=0;pd6.TextColorB=0;pd6.TextColorG=0;pd6.TextSize=9.0;pd6.TextType="微软雅黑";pd6.IsUnderLine=false;pd6.IsStronger=false;pd6.LineSpacing=1.0;pd6.CharSpacing=0.5;pd6.TextString="颜色值";
	pd7.X=5.0;pd7.Y=30.0;pd7.Width=20.0;pd7.Height=4.0;pd7.TextColorR=0;pd7.TextColorB=0;pd7.TextColorG=0;pd7.TextSize=9.0;pd7.TextType="微软雅黑";pd7.IsUnderLine=false;pd7.IsStronger=false;pd7.LineSpacing=1.0;pd7.CharSpacing=0.5;pd7.TextString="尺码：";
	pd8.X=15.0;pd8.Y=30.0;pd8.Width=20.0;pd8.Height=4.0;pd8.TextColorR=0;pd8.TextColorB=0;pd8.TextColorG=0;pd8.TextSize=9.0;pd8.TextType="微软雅黑";pd8.IsUnderLine=false;pd8.IsStronger=false;pd8.LineSpacing=1.0;pd8.CharSpacing=0.5;pd8.TextString="尺码值";
	pd9.X=5.0;pd9.Y=20.0;pd9.Width=20.0;pd9.Height=5.0;pd9.TextColorR=0;pd9.TextColorB=0;pd9.TextColorG=0;pd9.TextSize=11.0;pd9.TextType="微软雅黑";pd9.IsUnderLine=false;pd9.IsStronger=false;pd9.LineSpacing=1.0;pd9.CharSpacing=0.5;pd9.TextString="扎号：";
	pd10.X=22.0;pd10.Y=20.0;pd10.Width=20.0;pd10.Height=5.0;pd10.TextColorR=0;pd10.TextColorB=0;pd10.TextColorG=0;pd10.TextSize=11.0;pd10.TextType="微软雅黑";pd10.IsUnderLine=true;pd10.IsStronger=false;pd10.LineSpacing=1.0;pd10.CharSpacing=0.5;pd10.TextString="扎号值";
	pd11.X=23.0;pd11.Y=30.0;pd11.Width=20.0;pd11.Height=4.0;pd11.TextColorR=0;pd11.TextColorB=0;pd11.TextColorG=0;pd11.TextSize=8.0;pd11.TextType="微软雅黑";pd11.IsUnderLine=false;pd11.IsStronger=false;pd11.LineSpacing=1.0;pd11.CharSpacing=0.5;pd11.TextString="件数：";
	pd12.X=31.0;pd12.Y=30.0;pd12.Width=20.0;pd12.Height=4.0;pd12.TextColorR=0;pd12.TextColorB=0;pd12.TextColorG=0;pd12.TextSize=8.0;pd12.TextType="微软雅黑";pd12.IsUnderLine=false;pd12.IsStronger=false;pd12.LineSpacing=1.0;pd12.CharSpacing=0.5;pd12.TextString="件数值";
	dataList.push_back(pd4);
	dataList.push_back(pd5);
	dataList.push_back(pd6);
	dataList.push_back(pd7);
	dataList.push_back(pd8);
	dataList.push_back(pd9);
	dataList.push_back(pd10);
	dataList.push_back(pd11);
	dataList.push_back(pd12);
	unsigned int num2;
	
	//usb://\\?\usb#vid_0471&pid_7003&mi_00#7&118002cc&0&0000#{28d78fad-5a12-11d1-ae5b-0000f803a8c2}
	
	int ss = 0;
	for(int k = 0;k<5;k++)
	{
		k?Sleep(10500):0;

		num = DASSetPrinterName((LPSTR)(LPCSTR)GetApp().GetPrinter().name, "DC-1300");
		if (DASsetCardSize(53.98, 85.6) != 0u)
		{
			MessageBox(L"Fail DASsetCardSize");
		}
		//设置打印方向
		if (DASSetPrintDirection(0) != 0u)
		{
			MessageBox(L"fail DASSetPrintDirection");
		}
		if (DASaddProtectedRect(0, 60, 53.98, 25.6) != 0u)
		{
			MessageBox(L"fail  DASaddProtectedRect");
		}
		for (int i = 0; i < dataList.size(); i++)
		{

			if (DASsetTextColor(dataList[i].TextColorR, dataList[i].TextColorB, dataList[i].TextColorG) != 0u)
			{
				MessageBox(L"Fail DASsetTextColor");
			}
			if (DASsetFont(dataList[i].TextType, dataList[i].TextSize) != 0u)
			{
				MessageBox(L"Fail DASsetFont");
			}
			if (DASsetTextDirection(true, false, false) != 0u)
			{
				MessageBox(L"Fail DASsetTextDirection");
			}
			if (DASsetSpacing(dataList[i].LineSpacing, dataList[i].CharSpacing) != 0u)
			{
				MessageBox(L"Fail DASsetSpacing");
			}
			if (DASsetTextDecorate(dataList[i].IsStronger, false, dataList[i].IsUnderLine) != 0u)
			{
				MessageBox(L"Fail DASsetTextDecorate");
			}

			if (DASdrawText(dataList[i].X, dataList[i].Y, dataList[i].Width, dataList[i].Height, (std::to_string((LONGLONG)k) + dataList[i].TextString).data()) != 0u)//添加需要打印的文本
			{
				MessageBox(L"Fail DASdrawText  " + CString(dataList[i].TextString));
			}
		}
		//num = DASBuildGraphicsData(true, true);
		num = DASBuildGraphicsData(true, true);
		if (num != 0u)
		{
			CString tmp;
			tmp.Format(L"第%d次：%u",k,num);
			MessageBox(tmp);
		}

		num2 = DASPrintCard();

		if (num2 == 0u)
		{
			CString tmp;
			tmp.Format(L"第%d次打印执行成功!",k);
			//MessageBox(tmp);
		}
	}
}



void CDrawCardDialog::OnBnClickedOk3()
{
	// TODO: 在此添加控件通知处理程序代码
// 	BYTE flag = 0;
// 	auto re = DASGetEjectMode(&flag);
// 	if(flag)
// 	{
		auto re = DASEject();
		if(re != DS_CPSDK_OK)
		{
			log(L"退卡失败");
		}
// 		else
// 		{
// 			log(L"退卡成功");
// 		}
// 	}
// 	else
// 	{
// 		log(L"手动排卡模式无效！");
// 	}
}


void CDrawCardDialog::OnBnClickedCheck12()
{
	// TODO: 在此添加控件通知处理程序代码
	int flag = ((CButton*)(GetDlgItem(IDC_CHECK12)))->GetCheck();
	auto re = ::DASSetEjectMode(flag);
	if(re != DS_CPSDK_OK)
	{
		if(flag)
			log(L"设置 手动排卡模式 为有效失败！");
		else
			log(L"设置 手动排卡模式 为无效失败！");
		((CButton*)(GetDlgItem(IDC_CHECK12)))->SetCheck(!flag);
		return;
	}
	//::ShowWindow(GetDlgItem(IDOK3)->GetSafeHwnd(),flag?SW_SHOW:SW_HIDE);
}
