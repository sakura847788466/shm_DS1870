// PrintEEPEntryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PrintEEPEntryDlg.h"
#include "afxdialogex.h"

template <typename T, size_t N>
size_t CountOf(T (&)[N]) { return N; }

namespace EEP {

    static const TCHAR *entryTypeStrings[] = {
        _T("探亲（T），有效期3个月，往返一次"),
        _T("探亲（T），有效期3个月，往返多次"),
        _T("探亲（T），有效期1年，往返多次"),
        _T("商务（S），有效期3个月，往返一次"),
        _T("商务（S），有效期3个月，往返多次"),
        _T("商务（S），有效期1年，往返多次"),
        _T("团队旅游（L），有效期3个月，往返一次"),
        _T("团队旅游（L），有效期3个月，往返两次"),
        _T("团队旅游（L），有效期1年，往返一次"),
        _T("团队旅游（L），有效期1年，往返两次"),
        _T("个人旅游（G），有效期3个月，往返一次"),
        _T("个人旅游（G），有效期3个月，往返两次"),
        _T("个人旅游（G），有效期1年，往返一次"),
        _T("个人旅游（G），有效期1年，往返两次"),
        _T("个人旅游（G），有效期1年，往返多次"),
        _T("逗留（D）"),
        _T("其它（Q），有效期3个月，往返一次"),
        _T("其它（Q），有效期3个月，往返两次"),
        _T("其它（Q），有效期3个月，往返多次")
    };

    static const char *entryTypeStringsForPrinting[] = {
        "探亲（T）        壹次往返有效",
        "探亲（T）        多次往返有效",
        "探亲（T）        多次往返有效",
        "商务（S）        壹次往返有效",
        "商务（S）        多次往返有效",
        "商务（S）        多次往返有效",
        "团队旅游（L）    壹次往返有效",
        "团队旅游（L）    贰次往返有效",
        "团队旅游（L）    壹次往返有效",
        "团队旅游（L）    贰次往返有效",
        "个人旅游（G）    壹次往返有效",
        "个人旅游（G）    贰次往返有效",
        "个人旅游（G）    壹次往返有效",
        "个人旅游（G）    贰次往返有效",
        "个人旅游（G）    多次往返有效",
        "逗留（D）",
        "其它（Q）        壹次往返有效",
        "其它（Q）        贰次往返有效",
        "其它（Q）        多次往返有效"
    };

    static const TCHAR *durationOfStayStrings[] = {
        _T("3天"),
        _T("7天"),
        _T("14天"),
        _T("自首次进入之日起90天"),
        _T("90天"),
        _T("无限制")
    };

    static const char *durationOfStayStringsForPrinting[] = {
        "3天",
        "7天",
        "14天",
        "自首次进入之日起90天",
        "90天",
        "无限制"
    };

    struct Combination
    {
        EntryType entryType;
        DurationOfStay durationOfStay;
    };

    Combination validCombinationsForHK[] = {
        { TQuarterlyOnce, FourteenDay },
        { TQuarterlyMultiple, NinetyDayOnFirstEnter },
        { TYearlyMultiple, NinetyDay },

        { SQuarterlyOnce, SevenDay },
        { SQuarterlyMultiple, SevenDay },
        { SYearlyMultiple, SevenDay },

        { LQuarterlyOnce, ThreeDay },
        { LQuarterlyOnce, SevenDay },
        { LQuarterlyTwice, SevenDay },
        { LYearlyOnce, SevenDay },
        { LYearlyTwice, SevenDay },

        { GQuarterlyOnce, SevenDay },
        { GQuarterlyTwice, SevenDay },
        { GYearlyOnce, SevenDay },
        { GYearlyTwice, SevenDay },
        { GYearlyMultiple, SevenDay },

        { D, Unlimited },
    
        { QQuarterlyOnce, FourteenDay },
        { QQuarterlyTwice, FourteenDay },
        { QQuarterlyMultiple, FourteenDay }
    };

    Combination validCombinationsForMO[] = {
        { TQuarterlyOnce, FourteenDay },
        { TQuarterlyMultiple, NinetyDayOnFirstEnter },
        { TYearlyMultiple, NinetyDay },

        { SQuarterlyOnce, SevenDay },
        { SQuarterlyMultiple, SevenDay },
        { SYearlyMultiple, SevenDay },

        { LQuarterlyOnce, ThreeDay },
        { LQuarterlyOnce, SevenDay },
        { LYearlyOnce, SevenDay },

        { GQuarterlyOnce, SevenDay },
        { GYearlyOnce, SevenDay },

        { D, Unlimited },
    
        { QQuarterlyOnce, FourteenDay },
        { QQuarterlyTwice, FourteenDay },
        { QQuarterlyMultiple, FourteenDay }
    };

    SYSTEMTIME GetExpireDate(EntryType type, const SYSTEMTIME &effectDate)
    {
        SYSTEMTIME expireDate;
        memset(&expireDate, 0, sizeof(expireDate));
        expireDate.wYear = effectDate.wYear;
        expireDate.wMonth = effectDate.wMonth;
        expireDate.wDay = effectDate.wDay;

        ASSERT(type != D);
        
        switch (type) {
        case TQuarterlyOnce:
        case TQuarterlyMultiple:
        case SQuarterlyOnce:
        case SQuarterlyMultiple:
        case LQuarterlyOnce:
        case LQuarterlyTwice:
        case GQuarterlyOnce:
        case GQuarterlyTwice:
        case QQuarterlyOnce:
        case QQuarterlyTwice:
        case QQuarterlyMultiple:
            {
                // 当前日期加三个月
                expireDate.wMonth = ((effectDate.wMonth - 1) + 3) % 12 + 1;
                expireDate.wYear += (expireDate.wMonth < effectDate.wMonth ? 1 : 0);
                if (expireDate.wDay == 1) {
                    expireDate.wDay = 31;
                    if (expireDate.wMonth == 1) {
                        expireDate.wMonth = 12;
                        --expireDate.wYear;
                    } else {
                        --expireDate.wMonth;
                    }
                } else {
                    --expireDate.wDay;
                }
                
                // 如果日期无效，必然是因为这年二月没有29日、30日、31日等
                // 此时就从该日起逐日检查直到成功
                FILETIME notUsed;
                while (!SystemTimeToFileTime(&expireDate, &notUsed))
                    --expireDate.wDay;
            }
            break;
        case TYearlyMultiple:
        case SYearlyMultiple:
        case LYearlyOnce:
        case LYearlyTwice:
        case GYearlyOnce:
        case GYearlyTwice:
        case GYearlyMultiple:
            {
                // 当前日期加一年
                ++expireDate.wYear;
                if (expireDate.wDay == 1) {
                    expireDate.wDay = 31;
                    if (expireDate.wMonth == 1) {
                        expireDate.wMonth = 12;
                        --expireDate.wYear;
                    } else {
                        --expireDate.wMonth;
                    }
                } else {
                    --expireDate.wDay;
                }

                // 同上方
                FILETIME notUsed;
                while (!SystemTimeToFileTime(&expireDate, &notUsed))
                    --expireDate.wDay;
            }
            break;
        case D:
            break;
        }

        return expireDate;
    }

    CStringA GetEntryTypeText(EntryType type)
    {
        return entryTypeStringsForPrinting[type];
    }

    CStringA GetValidPeriod(SYSTEMTIME effectDate, SYSTEMTIME expireDate)
    {
        CStringA result;
        result.Format("%04d.%02d.%02d - %04d.%02d.%02d",
            effectDate.wYear, effectDate.wMonth, effectDate.wDay,
            expireDate.wYear, expireDate.wMonth, expireDate.wDay);
        return result;
    }

    typedef std::pair<CStringA, CStringA> CommentLines;

    CommentLines GetCommentLines(EntryType type, DurationOfStay duration, EntryRegion region)
    {
        CommentLines result;
        result.first = "持证人";
        CStringA regionString = (region == HongKong ? "香港" : "澳门");
        
        switch (type) {
        case TQuarterlyOnce:
        case SQuarterlyOnce:
        case GQuarterlyOnce:
        case QQuarterlyOnce:
        case GYearlyOnce:
            result.first += "在" + regionString + "逗留不超过" +
                durationOfStayStringsForPrinting[(size_t)duration];
            break;
        case LYearlyOnce:
        case LQuarterlyOnce:
            result.first += "在" + regionString + "逗留不超过" +
                durationOfStayStringsForPrinting[(size_t)duration] + "，";
            result.second = "须随团出入境";
            break;
        case GQuarterlyTwice:
        case QQuarterlyTwice:
        case GYearlyTwice:
        case TQuarterlyMultiple:
			result.first += "在" + regionString + "逗留不超过";
			result.second = durationOfStayStringsForPrinting[(size_t)duration];
			break;
		case SQuarterlyMultiple:
        case QQuarterlyMultiple:
        case TYearlyMultiple:
        case SYearlyMultiple:
        case GYearlyMultiple:
            result.first += "每次在" + regionString + "逗留不超过" +
                durationOfStayStringsForPrinting[(size_t)duration];
            break;
        case LQuarterlyTwice:
        case LYearlyTwice:
            result.first += "每次在" + regionString + "逗留不超过" +
                durationOfStayStringsForPrinting[(size_t)duration] + "，";
            result.second = "须随团出入境";
            break;
        case D:
            result.first += "须按照";
            result.first += regionString;
            result.first += "进入许可的规定";
            result.second = "入出" + regionString;
            break;
        }

        return result;
    }

    CStringA GetQrData(CStringA eepno, EntryType, DurationOfStay, SYSTEMTIME)
    {
        CStringA result(eepno);
        result + "M003A1L 180521WHJPbQePReRP";
        return result;
    }
}

using namespace EEP;

IMPLEMENT_DYNAMIC(CPrintEEPEntryDlg, CDialog)

CPrintEEPEntryDlg::CPrintEEPEntryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintEEPEntryDlg::IDD, pParent)
    , m_bHKChecked(FALSE)
    , m_bMOChecked(FALSE)
    , m_sEEPNO(_T(""))
{
}

CPrintEEPEntryDlg::~CPrintEEPEntryDlg()
{
}

BOOL CPrintEEPEntryDlg::GetHKEntryType(EntryType &out)
{
    int sel = m_cmbHKEntryType.GetCurSel();
    if (sel == CB_ERR)
        return FALSE;
    
    out = (EntryType)m_cmbHKEntryType.GetItemData(sel);
    return TRUE;
}

BOOL CPrintEEPEntryDlg::GetMOEntryType(EntryType &out)
{
    int sel = m_cmbMOEntryType.GetCurSel();
    if (sel == CB_ERR)
        return FALSE;
    
    out = (EntryType)m_cmbMOEntryType.GetItemData(sel);
    return TRUE;
}

BOOL CPrintEEPEntryDlg::GetHKDurationOfStay(DurationOfStay &out)
{
    int sel = m_cmbHKDurationOfStay.GetCurSel();
    if (sel == CB_ERR)
        return FALSE;

    out = (DurationOfStay)m_cmbHKDurationOfStay.GetItemData(sel);
    return TRUE;
}

BOOL CPrintEEPEntryDlg::GetMODurationOfStay(DurationOfStay &out)
{
    int sel = m_cmbMODurationOfStay.GetCurSel();
    if (sel == CB_ERR)
        return FALSE;

    out = (DurationOfStay)m_cmbMODurationOfStay.GetItemData(sel);
    return TRUE;
}

void CPrintEEPEntryDlg::InitHKEntryTypes()
{
    std::set<size_t> entryIndices;
    for (size_t i = 0; i < CountOf(validCombinationsForHK); ++i) {
        entryIndices.insert(
            (size_t)validCombinationsForHK[i].entryType
            );
    }

    for (auto i = entryIndices.begin(); i != entryIndices.end(); ++i) {
        auto itemIndex = m_cmbHKEntryType.AddString(entryTypeStrings[*i]);
        m_cmbHKEntryType.SetItemData(itemIndex, *i);
    }

    // 10 -> 个人旅游，三个月1次
    m_cmbHKEntryType.SetCurSel(10);
}

void CPrintEEPEntryDlg::InitMOEntryTypes()
{
    std::set<size_t> entryIndices;
    for (size_t i = 0; i < CountOf(validCombinationsForMO); ++i) {
        entryIndices.insert(
            (size_t)validCombinationsForMO[i].entryType
            );
    }

    for (auto i = entryIndices.begin(); i != entryIndices.end(); ++i) {
        auto itemIndex = m_cmbMOEntryType.AddString(entryTypeStrings[*i]);
        m_cmbMOEntryType.SetItemData(itemIndex, *i);
    }

    // 8 -> 个人旅游，三个月1次
    m_cmbMOEntryType.SetCurSel(8);
}

void CPrintEEPEntryDlg::UpdateHKDurationEntries()
{
    BOOL hasEntryType;
    EntryType entryType;
    hasEntryType = GetHKEntryType(entryType);
    ASSERT(hasEntryType);

    BOOL hasOldDuration;
    DurationOfStay oldDuration;
    int newSelection = 0;
    hasOldDuration = GetHKDurationOfStay(oldDuration);

    std::set<DurationOfStay> newEntries;
    for (size_t i = 0; i < CountOf(validCombinationsForHK); ++i) {
        auto & combination = validCombinationsForHK[i];
        if (combination.entryType == entryType) {
            newEntries.insert(combination.durationOfStay);
        }
    }

    m_cmbHKDurationOfStay.ResetContent();
    for (auto i = newEntries.begin(); i != newEntries.end(); ++i) {
        auto index = m_cmbHKDurationOfStay.AddString(
            durationOfStayStrings[*i]
            );
        if (hasOldDuration && *i == oldDuration) {
            newSelection = index;
        }
        m_cmbHKDurationOfStay.SetItemData(index, *i);
    }

    m_cmbHKDurationOfStay.SetCurSel(newSelection);
}

void CPrintEEPEntryDlg::UpdateMODurationEntries()
{
    BOOL hasEntryType;
    EntryType entryType;
    hasEntryType = GetMOEntryType(entryType);
    ASSERT(hasEntryType);

    BOOL hasOldDuration;
    DurationOfStay oldDuration;
    int newSelection = 0;
    hasOldDuration = GetMODurationOfStay(oldDuration);

    std::set<DurationOfStay> newEntries;
    for (size_t i = 0; i < CountOf(validCombinationsForHK); ++i) {
        auto & combination = validCombinationsForHK[i];
        if (combination.entryType == entryType) {
            newEntries.insert(combination.durationOfStay);
        }
    }

    m_cmbMODurationOfStay.ResetContent();
    for (auto i = newEntries.begin(); i != newEntries.end(); ++i) {
        auto index = m_cmbMODurationOfStay.AddString(
            durationOfStayStrings[*i]
            );
        if (hasOldDuration && *i == oldDuration) {
            newSelection = index;
        }
        m_cmbMODurationOfStay.SetItemData(index, *i);
    }

    m_cmbMODurationOfStay.SetCurSel(newSelection);
}

BOOL CPrintEEPEntryDlg::DoDrawing()
{
    ::DASsetCardSize(85.6, 54.0);

    const char *fontName = "黑体";
    const char *numFontName = "Sans Serif";
    const char *ocrFontName = "黑体";

    ::DASsetTextColor(0, 0, 0);
	::DASsetBarCodeColor(0, 0, 0);
	::DASsetTextDirection(true, false, true);
	::DASsetSpacing(2.5, 0);
	::DASsetTextDecorate(false, false, false);

    // HK
    if (m_bHKChecked) {
        // 擦除整个区块
        ::DASaddNeedEraseRect(8, 5, 74, 21);

        // 打印表头
        ::DASsetFont(fontName, 8);
        ::DASsetTextDecorate(true, false, false);
        ::DASdrawText(9, 6, 11, 4, "种　类");
        ::DASdrawText(9, 11, 11, 4, "有效期");
        ::DASdrawText(9, 16, 11, 4, "备　注");

        // 打印内容
        ::DASsetTextDecorate(false, false, false);
        EntryType type;
        DurationOfStay duration;

        GetHKEntryType(type);
        GetHKDurationOfStay(duration);

        SYSTEMTIME effectDate, expireDate;
        m_dtHKEffectDate.GetTime(&effectDate);
        m_dtHKExpireDate.GetTime(&expireDate);

        ::DASdrawText(21, 6, 46, 4, GetEntryTypeText(type)); // 种类
        ::DASsetFont(numFontName, 8);
        ::DASdrawText(21, 11, 46, 4, GetValidPeriod(effectDate, expireDate)); // 有效期
        ::DASsetFont(fontName, 8);

        auto comments(GetCommentLines(type, duration, HongKong));
        ::DASdrawText(21, 16, 46, 4, comments.first);
        if (!comments.second.IsEmpty()) {
            ::DASdrawText(21, 21, 46, 4, comments.second); // 备注第二行
        }

        CStringA qrData = GetQrData(CStringA(m_sEEPNO), type, duration, expireDate);
        ::DASdrawQR(68, 6, 12, 12, "C12962154M003A1L 180521WHJPbQePReRP", 2, true); // QR码
        ::DASsetFont(ocrFontName, 6);
        ::DASdrawText(68, 21, 13, 3, "4302-H001"); // QR码可读文字

    }

    // MO
    if (m_bMOChecked) {
        // 整个擦除澳门部分
        ::DASaddNeedEraseRect(8, 27, 74, 21);

        // 打印表头
        ::DASsetFont(fontName, 8);
        ::DASsetTextDecorate(true, false, false);
        ::DASdrawText(9, 28, 11, 4, "种　类");
        ::DASdrawText(9, 33, 11, 4, "有效期");
        ::DASdrawText(9, 38, 11, 4, "备　注");

        // 打印内容
        ::DASsetTextDecorate(false, false, false);
        EntryType type;
        DurationOfStay duration;

        GetMOEntryType(type);
        GetMODurationOfStay(duration);

        SYSTEMTIME effectDate, expireDate;
        m_dtMOEffectDate.GetTime(&effectDate);
        m_dtMOExpireDate.GetTime(&expireDate);

        ::DASdrawText(21, 28, 46, 4, GetEntryTypeText(type)); // 种类
        ::DASsetFont(numFontName, 8);
        ::DASdrawText(21, 33, 46, 4, GetValidPeriod(effectDate, expireDate)); // 有效期
        ::DASsetFont(fontName, 8);

        auto comments(GetCommentLines(type, duration, Macau));
        ::DASdrawText(21, 38, 46, 4, comments.first);
        if (!comments.second.IsEmpty()) {
            ::DASdrawText(21, 43, 46, 4, comments.second); // 备注第二行
        }

        CStringA qrData = GetQrData(CStringA(m_sEEPNO), type, duration, expireDate);
        ::DASdrawQR(68, 28, 12, 12, "C12962154M003A1L 180521WHJPbQePReRP", 2, true); // QR码
        ::DASsetFont(ocrFontName, 6);
        ::DASdrawText(68, 43, 13, 3, "4302-M001"); // QR码可读文字
    }

    // 指纹信息
    ::DASsetFont(fontName, 8);
    ::DASsetTextDecorate(false, false, false);
    ::DASdrawText(16, 48, 58, 4, "预存指纹信息(R1L1VHM)，可按规定自助通关");

    return 0 == ::DASBuildGraphicsData(true, true);
	return 0 == ::DASBuildGraphicsDataForRotation(true, true,2);
}

BOOL CPrintEEPEntryDlg::DoPrint()
{
    JobInfo info;
    uint32_t ret;
    CString line;

    auto &printer = GetApp().GetPrinter();
    info.printer = printer.name;
    info.printerModel = printer.model;

    auto &job = GetApp().GetCurrentJob();
    if (job.copyCount <= 0 || job.copyCount > 65535) {
        MessageBox(_T("打印份数超出允许的范围（0 ~ 65535）"));
        return FALSE;
    }

    ret = ::DASSetCopies(job.copyCount);
    info.copyCount = job.copyCount;
    info.printedCopyCount = 0;

    ////ret = ::DASSetPrintLevel(job.priority);
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
    //char uuid[33];
    //int  uuidLen = sizeof(uuid) / sizeof(char);
    info.submitDate = time(nullptr);

	BOOL DontEjectCard  = ((CButton*)(GetDlgItem(IDC_CHECK1)))->GetCheck();;
	if(DontEjectCard)
	{
		if (0 == (ret = ::DASPrintCard ())) {
			//// 将任务添加到列表中
			//info.index = JobInfo::currentIndex++; // 只在成功添加的情况下递增序号
			//info.jobStatus = 1; // JOB的初始状态是等待状态
			//info.uuid.SetString(uuid, 32);
			//GetApp().AddToJobList(info);
			// MessageBox(_T("打印成功。"));
			return TRUE;
		} else {
			line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
			MessageBox(line);
			return FALSE;
		}
	}
	else
	{
		if (0 == (ret = ::DASPrintCard())) {
			//// 将任务添加到列表中
			//info.index = JobInfo::currentIndex++; // 只在成功添加的情况下递增序号
			//info.jobStatus = 1; // JOB的初始状态是等待状态
			//info.uuid.SetString(uuid, 32);
			//GetApp().AddToJobList(info);
		   // MessageBox(_T("打印成功。"));
			return TRUE;
		} else {
			line.Append(_T("失败：") + GetApp().TranslateErrorCode(ret));
			MessageBox(line);
			return FALSE;
		}
	}
}

void CPrintEEPEntryDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHK_HK, m_bHKChecked);
    DDX_Check(pDX, IDC_CHK_MO, m_bMOChecked);
    DDX_Control(pDX, IDC_CMB_HK_ENTRY_TYPE, m_cmbHKEntryType);
    DDX_Control(pDX, IDC_DT_HK_EFFECT_DATE, m_dtHKEffectDate);
    DDX_Control(pDX, IDC_DT_HK_EXPIRE_DATE, m_dtHKExpireDate);
    DDX_Control(pDX, IDC_CMB_HK_DURATION_OF_STAY, m_cmbHKDurationOfStay);
    DDX_Control(pDX, IDC_CMB_MO_ENTRY_TYPE, m_cmbMOEntryType);
    DDX_Control(pDX, IDC_DT_MO_EFFECT_DATE, m_dtMOEffectDate);
    DDX_Control(pDX, IDC_DT_MO_EXPIRE_DATE, m_dtMOExpireDate);
    DDX_Control(pDX, IDC_CMB_MO_DURATION_OF_STAY, m_cmbMODurationOfStay);
 /*   DDX_Text(pDX, IDC_TXT_EEPNO, m_sEEPNO);
	DDV_MaxChars(pDX, m_sEEPNO, 8);*/
}

BOOL CPrintEEPEntryDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    InitHKEntryTypes();
    OnCbnSelchangeCmbHkEntryType();
    m_cmbHKEntryType.EnableWindow(FALSE);
    m_dtHKEffectDate.EnableWindow(FALSE);
    m_dtHKExpireDate.EnableWindow(FALSE);
    m_cmbHKDurationOfStay.EnableWindow(FALSE);

    InitMOEntryTypes();
    OnCbnSelchangeCmbMoEntryType();
    m_cmbMOEntryType.EnableWindow(FALSE);
    m_dtMOEffectDate.EnableWindow(FALSE);
    m_dtMOExpireDate.EnableWindow(FALSE);
    m_cmbMODurationOfStay.EnableWindow(FALSE);

	//::ShowWindow(GetDlgItem(IDOK3)->GetSafeHwnd(),SW_HIDE);
// 	BYTE flag = 0;
// 	auto re = DASGetEjectMode(&flag);
// 	CheckDlgButton(IDC_CHECK1,flag);
	//GetDlgItem(IDOK3)->ShowWindow(flag);
    return TRUE;
}

BEGIN_MESSAGE_MAP(CPrintEEPEntryDlg, CDialog)
    ON_BN_CLICKED(IDC_CHK_HK, &CPrintEEPEntryDlg::OnBnClickedChkHk)
    ON_BN_CLICKED(IDC_CHK_MO, &CPrintEEPEntryDlg::OnBnClickedChkMo)
    ON_BN_CLICKED(IDOK, &CPrintEEPEntryDlg::OnBnClickedOk)
    ON_CBN_SELCHANGE(IDC_CMB_HK_ENTRY_TYPE, &CPrintEEPEntryDlg::OnCbnSelchangeCmbHkEntryType)
    ON_CBN_SELCHANGE(IDC_CMB_MO_ENTRY_TYPE, &CPrintEEPEntryDlg::OnCbnSelchangeCmbMoEntryType)
    ON_EN_CHANGE(IDC_TXT_EEPNO, &CPrintEEPEntryDlg::OnEnChangeTxtEepno)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DT_HK_EFFECT_DATE, &CPrintEEPEntryDlg::OnDtnDatetimechangeDtHkEffectDate)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DT_MO_EFFECT_DATE, &CPrintEEPEntryDlg::OnDtnDatetimechangeDtMoEffectDate)
	ON_BN_CLICKED(IDOK2, &CPrintEEPEntryDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_CHECK1, &CPrintEEPEntryDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDOK3, &CPrintEEPEntryDlg::OnBnClickedOk3)
END_MESSAGE_MAP()

void CPrintEEPEntryDlg::OnBnClickedChkHk()
{
    UpdateData();
    if (m_bHKChecked) {
        m_cmbHKEntryType.EnableWindow(TRUE);
        m_dtHKEffectDate.EnableWindow(TRUE);
        m_cmbHKDurationOfStay.EnableWindow(TRUE);
        OnCbnSelchangeCmbHkEntryType();
    } else {
        m_cmbHKEntryType.EnableWindow(FALSE);
        m_dtHKEffectDate.EnableWindow(FALSE);
        m_dtHKExpireDate.EnableWindow(FALSE);
        m_cmbHKDurationOfStay.EnableWindow(FALSE);
    }
}

void CPrintEEPEntryDlg::OnBnClickedChkMo()
{
    UpdateData();
    if (m_bMOChecked) {
        m_cmbMOEntryType.EnableWindow(TRUE);
        m_dtMOEffectDate.EnableWindow(TRUE);
        m_cmbMODurationOfStay.EnableWindow(TRUE);
        OnCbnSelchangeCmbMoEntryType();
    } else {
        m_cmbMOEntryType.EnableWindow(FALSE);
        m_dtMOEffectDate.EnableWindow(FALSE);
        m_dtMOExpireDate.EnableWindow(FALSE);
        m_cmbMODurationOfStay.EnableWindow(FALSE);
    }
}

void CPrintEEPEntryDlg::OnBnClickedOk()
{
    //if (m_sEEPNO.GetLength() != 8) {
    //    MessageBox(_T("请将通行证编号填写完整"));
    //    ::SetFocus(GetDlgItem(IDC_TXT_EEPNO)->m_hWnd);
    //    return;
    //}

    if (!m_bHKChecked && !m_bMOChecked) {
        MessageBox(_T("请至少选择香港签注与澳门签注中的一个"));
        return;
    }

    //::DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    uint32_t ret = ::DASSetPrinterName(
        (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
        (LPSTR)(LPCSTR)GetApp().GetPrinter().model);

	if  ( ret > 0 ){
		MessageBox(_T("打印失败。") + GetApp().TranslateErrorCode(ret));
		return;
	}

    if (!DoDrawing() || !DoPrint()) {
        return;
    }

    CDialog::OnOK();
}

void CPrintEEPEntryDlg::OnCbnSelchangeCmbHkEntryType()
{
    UpdateHKDurationEntries();

    EntryType type;
    GetHKEntryType(type);

    if (type != D) {
        SYSTEMTIME effectDate;
        SYSTEMTIME expireDate;
        m_dtHKEffectDate.GetTime(&effectDate);
        expireDate = GetExpireDate(type, effectDate);
        m_dtHKExpireDate.SetTime(&expireDate);
        m_dtHKExpireDate.EnableWindow(FALSE);
    } else {
        m_dtHKExpireDate.EnableWindow(TRUE);
    }
}

void CPrintEEPEntryDlg::OnCbnSelchangeCmbMoEntryType()
{
    UpdateMODurationEntries();

    EntryType type;
    GetMOEntryType(type);

    if (type != D) {
        SYSTEMTIME effectDate;
        SYSTEMTIME expireDate;
        m_dtMOEffectDate.GetTime(&effectDate);
        expireDate = GetExpireDate(type, effectDate);
        m_dtMOExpireDate.SetTime(&expireDate);
        m_dtMOExpireDate.EnableWindow(FALSE);
    } else {
        m_dtMOExpireDate.EnableWindow(TRUE);
    }
}

void CPrintEEPEntryDlg::OnEnChangeTxtEepno()
{
    UpdateData();
}

void CPrintEEPEntryDlg::OnDtnDatetimechangeDtHkEffectDate(NMHDR *, LRESULT *pResult)
{
    EntryType type;
    GetHKEntryType(type);

    if (type != D) {
        SYSTEMTIME effectDate;
        SYSTEMTIME expireDate;
        m_dtHKEffectDate.GetTime(&effectDate);
        expireDate = GetExpireDate(type, effectDate);
        m_dtHKExpireDate.SetTime(&expireDate);
    }

    *pResult = 0;
}

void CPrintEEPEntryDlg::OnDtnDatetimechangeDtMoEffectDate(NMHDR *, LRESULT *pResult)
{
    EntryType type;
    GetMOEntryType(type);

    if (type != D) {
        SYSTEMTIME effectDate;
        SYSTEMTIME expireDate;
        m_dtMOEffectDate.GetTime(&effectDate);
        expireDate = GetExpireDate(type, effectDate);
        m_dtMOExpireDate.SetTime(&expireDate);
        m_dtMOExpireDate.EnableWindow(FALSE);
    }

    *pResult = 0;
}


void CPrintEEPEntryDlg::OnBnClickedOk2()
{
	for(auto i = 0; i< 20 ;++i)
	{
		// TODO: 在此添加控件通知处理程序代码
		if (!m_bHKChecked && !m_bMOChecked) {
			MessageBox(_T("请至少选择香港签注与澳门签注中的一个"));
			return;
		}

		//::DASSetNetworkParams(
		//    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
		//    GetApp().GetServer().GetPort());
		uint32_t ret = ::DASSetPrinterName(
			(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
			(LPSTR)(LPCSTR)GetApp().GetPrinter().model);

		if  ( ret > 0 ){
			MessageBox(_T("打印失败。") + GetApp().TranslateErrorCode(ret));
			return;
		}
		if (!DoDrawing() || !DoPrint()) {
			return;
		}
		Sleep(12000);
	}

	CDialog::OnOK();

}


void CPrintEEPEntryDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	int flag = ((CButton*)(GetDlgItem(IDC_CHECK1)))->GetCheck();
	auto re = ::DASSetEjectMode(flag);
	if(re)
	{
		if(flag)
			MessageBox(CString(L"设置 手动排卡模式 为有效失败！"));
		else
			MessageBox(CString(L"设置 手动排卡模式 为无效失败！"));
		((CButton*)(GetDlgItem(IDC_CHECK1)))->SetCheck(!flag);
		return;
	}
	//::ShowWindow(GetDlgItem(IDOK3)->GetSafeHwnd(),flag?SW_SHOW:SW_HIDE);
}


void CPrintEEPEntryDlg::OnBnClickedOk3()
{
	// TODO: 在此添加控件通知处理程序代码
// 	BYTE flag = 0;
// 	auto re = DASGetEjectMode(&flag);
// 	if(flag)
// 	{
		auto re = DASEject();
		if(re != DS_CPSDK_OK)
		{
			MessageBox(L"退卡失败");
		}
// 	}
// 	else
// 	{
// 		MessageBox(L"手动排卡模式无效！");
// 	}
}
