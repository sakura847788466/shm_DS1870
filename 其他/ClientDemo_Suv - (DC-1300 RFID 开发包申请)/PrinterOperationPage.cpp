// PrinterOperationPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PrinterOperationPage.h"
#include "afxdialogex.h"

// �ַ�������

static const LPCTSTR FeedPatternAuto = TEXT("�Զ�");
static const LPCTSTR FeedPatternManual = TEXT("�ֶ�");

static const LPCTSTR FeedPatternButtonAuto = TEXT("�л����ֶ�");
static const LPCTSTR FeedPatternButtonManual = TEXT("�л����Զ�");

static const LPCTSTR FeedSourceAuto = TEXT("�Զ�");
static const LPCTSTR FeedSourceCardBox = TEXT("����");
static const LPCTSTR FeedSourceEntrance = TEXT("������");

static const LPCTSTR ExitDirectionNormal = TEXT("����");
static const LPCTSTR ExitDirectionBackward = TEXT("�󷽳���");

static const LPCTSTR ExitDirectionButtonNormal = TEXT("�л���ǰ�����");
static const LPCTSTR ExitDirectionButtonBackward = TEXT("�л�������");

// CPrinterOperationPage �Ի���

IMPLEMENT_DYNAMIC(CPrinterOperationPage, CPropertyPage)

CPrinterOperationPage::CPrinterOperationPage()
	: CPropertyPage(CPrinterOperationPage::IDD)
    , m_printParamXOffset(0)
    , m_printParamYOffset(0)
    , m_printParamChroma(0)
{

}

CPrinterOperationPage::~CPrinterOperationPage()
{
}

void CPrinterOperationPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT2, m_printParamXOffset);
    DDV_MinMaxInt(pDX, m_printParamXOffset, -20, 20);
    DDX_Text(pDX, IDC_EDIT3, m_printParamYOffset);
    DDV_MinMaxInt(pDX, m_printParamYOffset, -8, 8);
    DDX_Text(pDX, IDC_EDIT4, m_printParamChroma);
	DDV_MinMaxInt(pDX, m_printParamChroma, -20, 20);
}


BEGIN_MESSAGE_MAP(CPrinterOperationPage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON11, &CPrinterOperationPage::OnBnClickedButton11)
    ON_BN_CLICKED(IDC_BUTTON5, &CPrinterOperationPage::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON8, &CPrinterOperationPage::OnBnClickedButton8)
    ON_BN_CLICKED(IDC_BUTTON9, &CPrinterOperationPage::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON10, &CPrinterOperationPage::OnBnClickedButton10)
    ON_BN_CLICKED(IDC_BUTTON4, &CPrinterOperationPage::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON1, &CPrinterOperationPage::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CPrinterOperationPage::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CPrinterOperationPage::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON12, &CPrinterOperationPage::OnBnClickedButton12)
    ON_BN_CLICKED(IDC_BUTTON13, &CPrinterOperationPage::OnBnClickedButton13)
    ON_BN_CLICKED(IDC_BUTTON14, &CPrinterOperationPage::OnBnClickedButton14)
    ON_BN_CLICKED(IDC_BUTTON15, &CPrinterOperationPage::OnBnClickedButton15)
    ON_BN_CLICKED(IDC_BUTTON17, &CPrinterOperationPage::OnBnClickedButton17)
    ON_BN_CLICKED(IDC_BUTTON6, &CPrinterOperationPage::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CPrinterOperationPage::OnBnClickedButton7)
    ON_EN_KILLFOCUS(IDC_EDIT_USER_DATA, &CPrinterOperationPage::OnEnKillfocusEditUserData)
	ON_BN_CLICKED(IDC_BUTTON16, &CPrinterOperationPage::OnBnClickedButton16)
END_MESSAGE_MAP()


// CPrinterOperationPage ��Ϣ�������

uint32_t CPrinterOperationPage::RefreshPrintParams()
{
    uint32_t ret;
    CString  s;
    CString  xOffset;
    CString  yOffset;
    CString  chroma;

    GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON10)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);


    xOffset = TEXT("0");
    yOffset = TEXT("0");
    chroma = TEXT("0");

    ret = DASSetPrinterName(
        GetApp().GetPrinter().name,
        GetApp().GetPrinter().model);
    if (ret != 0)
        goto done;

        
	int nXoffset=0,nYoffset=0,nChrome=0;

	ret =  DASGetXoffset(&nXoffset);
	if (ret != 0)
		goto done;
	ret =   DASGetYoffset(&nYoffset);
	if (ret != 0)
		goto done;
	ret =  DASGetPrintChroma(&nChrome);
	if (ret != 0)
		goto done;

    xOffset.Format(TEXT("%d"), nXoffset);
    yOffset.Format(TEXT("%d"), nYoffset);
    chroma.Format(TEXT("%d"), nChrome);

// 	BYTE flag = 0;
// 	ret = DASGetEjectMode(&flag);
// 	if( ret != 0)
// 		goto done;
// 	((CComboBox*)(GetDlgItem(IDC_COMBO1)))->SetCurSel(flag) ;
done:
    GetDlgItem(IDC_EDIT2)->SetWindowText(xOffset);
    GetDlgItem(IDC_EDIT3)->SetWindowText(yOffset);
    GetDlgItem(IDC_EDIT4)->SetWindowText(chroma);
    GetDlgItem(IDC_BUTTON8)->EnableWindow();
    GetDlgItem(IDC_BUTTON9)->EnableWindow();
    GetDlgItem(IDC_BUTTON10)->EnableWindow();
	GetDlgItem(IDC_BUTTON11)->EnableWindow();
    return ret;
}

uint32_t CPrinterOperationPage::RefreshFeedAndExitParams()
{
    uint32_t ret;
    uint64_t status;
    CString  feedPattern;
    CString  feedSource;
    CString  exitDirection;
    CString  feedPatternButtonText;
    CString  exitDirectionButtonText;

    GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
    feedPattern = FeedPatternAuto;
    feedPatternButtonText = FeedPatternButtonAuto;
    feedSource = FeedSourceAuto;

    // Ŀǰû�п��Զ��������������/ָ��
    GetDlgItem(IDC_STA_FEED_N_EXIT_DIRECTION)->GetWindowText(exitDirection);
    GetDlgItem(IDC_BUTTON3)->GetWindowText(exitDirectionButtonText);

    // ��������ʽ
    {
        int manualFlag;

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

        ret = DASGetFeedCardPattern(&manualFlag);
        if (ret != 0)
            goto done;

        if (manualFlag) {
            feedPattern = FeedPatternManual;
            feedPatternButtonText = FeedPatternButtonManual;
        } else {
            feedPattern = FeedPatternAuto;
            feedPatternButtonText = FeedPatternButtonAuto;
        }
    }

    // ��������Դ
    {
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

        switch (DASGetFeedCardMode(status)) {
        case 0:
            feedSource = FeedSourceCardBox;
            break;
        case 1:
            feedSource = FeedSourceEntrance;
            break;
        default:
            feedSource = FeedSourceAuto;
            break;
        }
    }

    // TODO: ����������
    {
        if (exitDirection.GetLength() == 0) {
            exitDirection = ExitDirectionNormal;
            exitDirectionButtonText = ExitDirectionButtonNormal;
        }
    }

done:
	if (ret == 0)
	{
		GetDlgItem(IDC_STA_FEED_N_EXIT_MODE)->SetWindowText(feedPattern);
		GetDlgItem(IDC_STA_FEED_N_EXIT_DIRECTION)->SetWindowText(exitDirection);
		GetDlgItem(IDC_BUTTON4)->SetWindowText(feedPatternButtonText);
		GetDlgItem(IDC_BUTTON3)->SetWindowText(exitDirectionButtonText);
	}else{
		MessageBox(
		TEXT("��ȡ���������ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
		TEXT("����"),
		MB_OK | MB_ICONERROR);
	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow();
	GetDlgItem(IDC_BUTTON2)->EnableWindow();
	GetDlgItem(IDC_BUTTON3)->EnableWindow();
	GetDlgItem(IDC_BUTTON4)->EnableWindow();
	GetDlgItem(IDC_BUTTON5)->EnableWindow();
    return ret;
}

void CPrinterOperationPage::OnBnClickedButton11()
{
    RefreshPrintParams();
}

void CPrinterOperationPage::OnBnClickedButton5()
{
    RefreshFeedAndExitParams();
}

void CPrinterOperationPage::OnBnClickedButton8()
{
    uint32_t ret = 0;

    if (!UpdateData())
        goto done;

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

    ret = DASsetXoffset(m_printParamXOffset);
    if (ret != 0)
        goto done;

done:
    if (ret != 0) {
        MessageBox(
            TEXT("����X��ƫ��ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
        RefreshPrintParams();
    }
}

void CPrinterOperationPage::OnBnClickedButton9()
{
    uint32_t ret = 0;

    if (!UpdateData())
        goto done;

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

    ret = DASsetYoffset(m_printParamYOffset);
    if (ret != 0)
        goto done;

done:
    if (ret != 0) {
        MessageBox(
            TEXT("����Y��ƫ��ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
        RefreshPrintParams();
    }
}

void CPrinterOperationPage::OnBnClickedButton10()
{
    uint32_t ret = 0;

    if (!UpdateData())
        goto done;

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

    ret = DASsetPrintChroma(m_printParamChroma);
    if (ret != 0)
        goto done;

done:
    if (ret != 0) {
        MessageBox(
            TEXT("���ô�ӡŨ��ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
        RefreshPrintParams();
    }
}

void CPrinterOperationPage::OnBnClickedButton4()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    uint32_t ret;
    CString labelText;
    CString buttonText;

    GetDlgItem(IDC_STA_FEED_N_EXIT_MODE)->GetWindowText(labelText);
    GetDlgItem(IDC_BUTTON4)->GetWindowText(buttonText);

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

    if (buttonText == FeedPatternButtonAuto) {
        // �Զ����� -> �ֶ�����
        ret = DASSetFeedCardPattern(1);
        if (ret == 0) {
            labelText = FeedPatternManual;
            buttonText = FeedPatternButtonManual;
        }
    } else {
        // �ֶ����� -> �Զ�����
        ret = DASSetFeedCardPattern(0);
        if (ret == 0) {
            labelText = FeedPatternAuto;
            buttonText = FeedPatternButtonAuto;
        }
    }

done:
    GetDlgItem(IDC_STA_FEED_N_EXIT_MODE)->SetWindowText(labelText);
    GetDlgItem(IDC_BUTTON4)->SetWindowText(buttonText);
    if (ret != 0) {
        MessageBox(
            TEXT("�л�������ʽʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
    }
}

void CPrinterOperationPage::OnBnClickedButton1()
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

    ret = DASSetManualCard();

done:
    if (ret != 0) {
        MessageBox(
            TEXT("����ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
    }
}

void CPrinterOperationPage::OnBnClickedButton2()
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

    ret = DASRejectCard();

done:
    if (ret != 0) {
        MessageBox(
            TEXT("����ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
    }
}

void CPrinterOperationPage::OnBnClickedButton3()
{
    uint32_t ret;
    CString labelText;
    CString buttonText;
    
    GetDlgItem(IDC_STA_FEED_N_EXIT_DIRECTION)->GetWindowText(labelText);
    GetDlgItem(IDC_BUTTON3)->GetWindowText(buttonText);

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

    if (labelText == ExitDirectionNormal) {
        // �Ƴ����С������
        ret = DASSetCardBoxEjectCard(0, 1);
        if (ret == 0) {
            labelText = ExitDirectionBackward;
            buttonText = ExitDirectionButtonBackward;
        }
    } else {
        // װ�俨�С�ǰ����
        ret = DASSetCardBoxEjectCard(1, 0);
        if (ret == 0) {
            labelText = ExitDirectionNormal;
            buttonText = ExitDirectionButtonNormal;
        }
    }

done:
    GetDlgItem(IDC_STA_FEED_N_EXIT_DIRECTION)->SetWindowText(labelText);
    GetDlgItem(IDC_BUTTON3)->SetWindowText(buttonText);
    if (ret != 0) {
        MessageBox(
            TEXT("�л���������ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
            TEXT("����"),
            MB_OK | MB_ICONERROR);
    }
}

void CPrinterOperationPage::OnBnClickedButton12()
{
    uint32_t ret = 0;
    BOOL     cancelled = FALSE;

    if (IDOK != MessageBox(
        TEXT("�����Ҫʹ��ר����࿨�����ڽ���࿨����󵥻���ȷ������ť"),
        TEXT("����ӡ��"),
        MB_OKCANCEL)) {
        cancelled = TRUE;
        goto done;
    }

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

    ret = DASCleanPrinter();

done:
    if (!cancelled) {
        if (ret == 0) {
            MessageBox(TEXT("��������ѳɹ����͡�"), TEXT("����ӡ��"));
        } else {
            MessageBox(TEXT("�����������ʱ��������") +
                GetApp().TranslateErrorCode(ret), TEXT("����ӡ��"),
                MB_OK | MB_ICONERROR);
        }
    }
}

void CPrinterOperationPage::OnBnClickedButton13()
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

    ret = DASPrintTestCard();

done:
    if (ret == 0) {
        MessageBox(TEXT("��ӡ�����ѳɹ����͡�"), TEXT("��ӡ���Կ�"));
    } else {
        MessageBox(TEXT("���ʹ�ӡ����ʱ��������") +
            GetApp().TranslateErrorCode(ret), TEXT("��ӡ���Կ�"),
            MB_OK | MB_ICONERROR);
    }
}

void CPrinterOperationPage::OnBnClickedButton14()
{
    uint32_t ret = 0;
    BOOL     cancelled = FALSE;

    if (IDOK != MessageBox(
        TEXT("�뽫Ҫ�����Ŀ�Ƭ�����ӡ���󵥻���ȷ������ť"),
        TEXT("����"),
        MB_OKCANCEL)) {
        cancelled = TRUE;
        goto done;
    }

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

    ret = DASEraseCard();

done:
    if (!cancelled) {
        if (ret == 0) {
            MessageBox(TEXT("���������ѳɹ����͡�"), TEXT("����"));
        } else {
            MessageBox(TEXT("���Ͳ�������ʱ��������") +
                GetApp().TranslateErrorCode(ret), TEXT("����"),
                MB_OK | MB_ICONERROR);
        }
    }
}

void CPrinterOperationPage::OnBnClickedButton15()
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

    ret = DASRebootPrinter();

done:
    if (ret == 0) {
        MessageBox(TEXT("���������ѳɹ����͡�"), TEXT("������ӡ��"));
    } else {
        MessageBox(TEXT("������������ʱ��������") +
            GetApp().TranslateErrorCode(ret), TEXT("������ӡ��"),
            MB_OK | MB_ICONERROR);
    }
}

void CPrinterOperationPage::OnBnClickedButton17()
{
    uint32_t ret;
    CString  printerStatus;
    //ret = DASSetNetworkParams(
    //    (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //    GetApp().GetServer().GetPort());
    ret = DASSetPrinterName(
        (LPSTR)(LPCSTR)GetApp().GetPrinter().name,
        (LPSTR)(LPCSTR)GetApp().GetPrinter().model);

    uint64_t status;
    ret = DASFetchPrinterStatus(&status);
    if (0 == ret) {
        uint32_t err = DASGetPrinterStatus_ErrorNo(status);
        uint32_t fcm = DASGetFeedCardMode(status);
        uint32_t cln = DASGetCleaningStatus(status);
        uint32_t fan = DASGetFanStatus(status);
        uint32_t cbs = DASGetPrinterStatus_CardBoxStatus(status);
        uint32_t fcs = DASGetPrinterStatus_FrontCoverStatus(status);
		uint32_t buffs  = DASGetRecvBufferStatus(status);
		uint32_t busy =	DASGetBusyStatus(status);

        printerStatus.Format(_T("������ 0x%02X��"), err);
        printerStatus +=
            ((fcm == 0) ? _T("�����Ϳ�") :
             (fcm == 1) ? _T("�ֶ�װ��") :
             (fcm == 2) ? _T("�Զ�װ��") : _T("δ֪"));
        printerStatus += _T("��");
        printerStatus +=
            ((cln == 0) ? _T("�������") :
             (cln == 1) ? _T("�������") :
             (cln == 2) ? _T("�������") : _T("δ֪"));
        printerStatus += _T("��");
        printerStatus +=
            ((fan == 0) ? _T("���ȹر�") :
             (fan == 1) ? _T("���ȿ���") : _T("δ֪"));
        printerStatus += _T("��");
        printerStatus +=
            ((cbs == 0) ? _T("�����п�") :
             (cbs == 1) ? _T("�����޿�") : _T("δ֪"));
        printerStatus += _T("��");
        printerStatus +=
            ((buffs == 0) ? _T("���ջ��治��") :
             (buffs == 2) ? _T("���ջ�����") : _T("���ջ����"));
        printerStatus += _T("��");
        printerStatus +=
            ((busy == 0) ? _T("��ӡ������") :
			 (busy == 1) ? _T("��ӡ��æ") : _T("δ֪"));
        printerStatus += _T("��");
        printerStatus +=        
            ((fcs == 0) ? _T("ǰ�Ǳպ�") :
             (fcs == 1) ? _T("ǰ�Ǵ�") : _T("δ֪"));
        GetDlgItem(IDC_EDIT_STATUS)->SetWindowText(printerStatus);
    } else {
        GetDlgItem(IDC_EDIT_STATUS)->SetWindowText(TEXT(""));
        MessageBox(_T("��ѯʧ�ܣ�") +
            GetApp().TranslateErrorCode(ret),
            _T("��ѯ��ӡ��״̬"), MB_ICONERROR);
    }

}

void CPrinterOperationPage::OnBnClickedButton6()
{
    uint32_t ret;
    unsigned char userData[4096];
    int len = sizeof(userData);

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

    ret = DASGetPrinterUserData(userData, &len);

done:
    if (ret == 0) {
        CString dataInHex;
        dataInHex.Preallocate(3 * len);
        LPCTSTR separator = TEXT("");
        for (int i = 0; i < len; ++i) {
            dataInHex.AppendFormat(TEXT("%s%02X"), separator, userData[i]);
            separator = TEXT(" ");
        }
        GetDlgItem(IDC_EDIT_USER_DATA)->SetWindowText(dataInHex);
    } else {
        GetDlgItem(IDC_EDIT_USER_DATA)->SetWindowText(TEXT(""));
        MessageBox(_T("��ȡʧ�ܣ�") +
            GetApp().TranslateErrorCode(ret),
            _T("���û�����"), MB_ICONERROR);
    }

}

void CPrinterOperationPage::OnBnClickedButton7()
{
    uint32_t ret;
    CStringA userDataA;
    int      len;

    {
        CString userData;
        GetDlgItem(IDC_EDIT_USER_DATA)->GetWindowText(userData);

        CStringA tmp = HexStringToBytes(userData);
        userDataA = tmp;
        len = userDataA.GetLength();
    }

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

    ret = DASSetUserData((LPBYTE)(const char *)userDataA, len);

done:
    if (ret == 0) {
        MessageBox(TEXT("�ѳɹ�д�롣"), TEXT("д���û�����"));
    } else {
        MessageBox(TEXT("д��ʱ��������") +
            GetApp().TranslateErrorCode(ret), TEXT("д���û�����"),
            MB_OK | MB_ICONERROR);
    }
}



void CPrinterOperationPage::OnEnKillfocusEditUserData()
{
    // ȷ���رմ���ʱ����ִ���κβ���
    if (this->GetParent()->IsWindowVisible()) {
        // ����ʮ�������ַ��������û����롣
        CString text;
        CWnd   *edit = GetDlgItem(IDC_EDIT_USER_DATA);
        edit->GetWindowText(text);
        edit->SetWindowText(FilterAsHexString(text));
    }
}



CString CPrinterOperationPage::FilterAsHexString(const CString &in)
{
    CString out;
    TCHAR   t = TEXT('\0');
    LPCTSTR separator = TEXT("");
    BOOL    isEven = FALSE;

    out.Preallocate(in.GetLength() / 2 * 3);

    for (int i = 0; i < in.GetLength(); ++i) {
        if (_istxdigit(in[i])) {
            if (isEven) {
                out.Append(separator);
                out.AppendChar(t);
                out.AppendChar(_totupper(in[i]));
                separator = TEXT(" ");
            } else {
                t = _totupper(in[i]);
            }
            isEven = !isEven;
        }
    }

    return out;
}

static int HexCharToInt(TCHAR t)
{
    TCHAR ut = _totupper(t);
    if (ut > TEXT('9')) {
        return ut - TEXT('A') + 10;
    } else {
        return ut - TEXT('0');
    }
}

CStringA CPrinterOperationPage::HexStringToBytes(const CString &in)
{
    CStringA out;
    TCHAR    t = TEXT('\0');
    BOOL isEven = FALSE;

    out.Preallocate(in.GetLength() / 2 + 1);

    for (int i = 0; i < in.GetLength(); ++i) {
        if (_istxdigit(in[i])) {
            if (isEven) {
                int h = HexCharToInt(t);
                int l = HexCharToInt(in[i]);
                BYTE b = ((h << 4) | l) & 0xFF;
                out.AppendChar((char)b);
            } else {
                t = in[i];
            }
            isEven = !isEven;
        }
    }

    return out;
}

void CPrinterOperationPage::OnBnClickedButton16()
{
	uint32_t ret;

	ret = DASSetPrinterName(
		GetApp().GetPrinter().name,
		GetApp().GetPrinter().model);
	if (ret != 0)
		goto done;

	ret = DASPrintTechnicalTestCard();

done:
	if (ret == 0) {
		MessageBox(TEXT("��ӡ�����ѳɹ����͡�"), TEXT("��ӡ���Կ�"));
	} else {
		MessageBox(TEXT("���ʹ�ӡ����ʱ��������") +
			GetApp().TranslateErrorCode(ret), TEXT("��ӡ���Կ�"),
			MB_OK | MB_ICONERROR);
	}
}


// void CPrinterOperationPage::OnBnClickedButton26()
// {
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	int flag = ((CComboBox*)(GetDlgItem(IDC_COMBO1)))->GetCurSel();
// 	if(flag != -1)
// 	{
// 		auto ret = DASSetPrinterName(
// 			GetApp().GetPrinter().name,
// 			GetApp().GetPrinter().model);
// 		if (ret != 0)
// 			goto done;
// 
// 		ret = DASSetEjectMode(flag);
// 		if (ret != 0)
// 			goto done;
// 
// done:
// 		if (ret != 0) {
// 			MessageBox(
// 				TEXT("�����ֶ��ſ�ʧ�ܣ�") + GetApp().TranslateErrorCode(ret),
// 				TEXT("����"),
// 				MB_OK | MB_ICONERROR);
// 			RefreshPrintParams();
// 		}
// 	}
// }
