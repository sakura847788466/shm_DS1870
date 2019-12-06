
// clientDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "ClientDemoDlg.h"
#include "PrinterPickerDialog.h"
#include "PrintOptionDialog.h"
#include "PrinterMaintenanceDialog.h"
#include "TaskListDialog.h"
#include "DrawCardDialog.h"
#include "PrintEEPEntryDlg.h"
#include "afxdialogex.h"
#include "MaintenanceSheets.h"
#include "ToolRWLicenseDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDemoDlg 对话框




CClientDemoDlg::CClientDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDemoDlg::IDD, pParent), printByDrawing(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PRINTER_NAME, m_txtPrinterName);
	DDX_Control(pDX, IDC_BTN_SHOW_PRINTER_MAINTENANCE_DIALOG, m_btnShowPrinterMaintenanceDlg);
	DDX_Control(pDX, IDC_BTN_SELECT_IMAGE, m_btnSelectImage);
	DDX_Control(pDX, IDC_TXT_IMAGE_PATH, m_txtImagePath);
	DDX_Control(pDX, IDC_BTN_EDIT_IMAGE, m_btnEditImage);
	DDX_Control(pDX, IDC_COPY_COUNT, m_txtCopyCount);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
	DDX_Control(pDX, IDC_BTN_SHOW_PRINT_OPTIONS, m_btnShowPrintOptionDlg);
	DDX_Control(pDX, IDC_BTN_SHOW_PRINTER_PICKER, m_btnShowPrinterPicker);
	DDX_Control(pDX, IDC_IMG_IMAGE, m_imgImage);

	if (pDX->m_bSaveAndValidate) {
		CString copyCountStr;
		m_txtCopyCount.GetWindowText(copyCountStr);
		int copyCount = _tcstol(copyCountStr, nullptr, 10);
		DDV_MinMaxInt(pDX, copyCount, 1, 65535);
	}
	DDX_Control(pDX, IDC_BTN_PRINT_SAR_PASS, m_btnPrintSARPass);
	DDX_Control(pDX, IDC_CHECK1, m_dontEject);
}



void CClientDemoDlg::InitPrinterControls()
{
    m_btnShowPrinterMaintenanceDlg.EnableWindow(FALSE);
}

void CClientDemoDlg::InitJobControls()
{
    CheckDlgButton(IDC_RADIO_CREATE_BY_FILE, BST_CHECKED);
    m_btnSelectImage.EnableWindow(FALSE);
    m_btnEditImage.EnableWindow(FALSE);
    m_btnPrintSARPass.EnableWindow(FALSE);
    m_txtCopyCount.SetLimitText(5);
    m_txtCopyCount.SetWindowText(_T("1"));
    m_txtCopyCount.EnableWindow(FALSE);
    m_btnPrint.EnableWindow(FALSE);
}



void CClientDemoDlg::DisplayImage()
{
    CString path;
    m_txtImagePath.GetWindowText(path);
    if (path.IsEmpty())   return;

	image.Destroy();
    image.Load(path);

    RECT rc;
    int dstWidth, dstHeight;
    m_imgImage.GetClientRect(&rc);
    dstWidth = rc.right - rc.left;
    dstHeight = rc.bottom - rc.top;
	
    bool rotationNeeded = (GetApp().GetCurrentJob().printDirection == CD_PD_VERTICAL);
    if (rotationNeeded) { // counter-clock wise 90 degree rotation needed
        RotateImage();
    }
    StretchImage(dstWidth, dstHeight);

	const auto & job = GetApp().GetCurrentJob();
	if ( ! job.erasePath.IsEmpty() ){

		CImage maskImage;
		maskImage.Load( CString(job.erasePath) );
		
		CImage resizedMaskImage;
		resizedMaskImage.Create(image.GetWidth(), image.GetHeight(), 32);
		BOOL res = maskImage.StretchBlt(resizedMaskImage.GetDC(),
			0,
			0,
			image.GetWidth(), 
			image.GetHeight(),
			0,
			0,
			maskImage.GetWidth(),maskImage.GetHeight());

		maskImage.Destroy();//by liu
		if ( res ) {
			for (int x=0;x<resizedMaskImage.GetWidth();x++) {
				for (int y=0;y<resizedMaskImage.GetHeight();y++) {
					COLORREF  color = resizedMaskImage.GetPixel(x,y);
					if ( GetRValue(color) == 255 &&  GetGValue(color) == 255 && GetBValue(color) == 255 )
						image.SetPixel(x,y,RGB(255,255,255));
				}
			}
			resizedMaskImage.ReleaseDC(); //by liu
		}
	}

    m_imgImage.SetBitmap(image);

}

void CClientDemoDlg::RotateImage()
{
    // 创建新图像
    CImage newImage;
    int srcWidth = image.GetWidth();
    int srcHeight = image.GetHeight();
    newImage.Create(srcHeight, srcWidth, 32);
    // 执行旋转
    POINT coords[3];
    coords[0].x = 0;
    coords[0].y = srcWidth;
    coords[1].x = 0;
    coords[1].y = 0;
    coords[2].x = srcHeight;
    coords[2].y = srcWidth;
    image.PlgBlt(newImage.GetDC(), coords);
    newImage.ReleaseDC();
    // 交换新旧图像
    HBITMAP newImageHandle = newImage.Detach();
    HBITMAP oldImageHandle = image.Detach();
    newImage.Attach(oldImageHandle); // 这样oldImageHandle就随newImage一同销毁
    image.Attach(newImageHandle);
}

RECT CClientDemoDlg::CalcStretchedRect(int outputWidth, int outputHeight)
{
    RECT dstRect;
    int srcWidth = image.GetWidth();
    int srcHeight = image.GetHeight();
    double xRatio = outputWidth / static_cast<double>(srcWidth);
    double yRatio = outputHeight / static_cast<double>(srcHeight);
    if (xRatio < yRatio) {
        int dstWidth = outputWidth;
        int dstHeight = static_cast<int>(srcHeight * xRatio);
        dstRect.left = 0;
        dstRect.right = dstWidth - 1;
        dstRect.top = (outputHeight - dstHeight) / 2;
        dstRect.bottom = dstRect.top + dstHeight - 1;
    } else {
        int dstWidth = static_cast<int>(srcWidth * yRatio);
        int dstHeight = outputHeight;
        dstRect.left = (outputWidth - dstWidth) / 2;
        dstRect.right = dstRect.left + dstWidth - 1;
        dstRect.top = 0;
        dstRect.bottom = dstHeight - 1;
    }
    return dstRect;
}

void CClientDemoDlg::StretchImage(int outputWidth, int outputHeight)
{
    // 计算拉伸坐标
    RECT srcRect = { 0, 0, image.GetWidth() - 1, image.GetHeight() - 1 };
    RECT dstRect = CalcStretchedRect(outputWidth, outputHeight);

    // 创建新图像
    CImage newImage;
    newImage.Create(outputWidth, outputHeight, 32);
	
    // 执行拉伸
    HDC dc = newImage.GetDC();
    ::SelectObject(dc, GetStockObject(WHITE_PEN));
    ::SelectObject(dc, GetStockObject(WHITE_BRUSH));
    ::Rectangle(dc, 0, 0, outputWidth, outputHeight);
    int oldMode = ::SetStretchBltMode(dc, HALFTONE);
    ::SetBrushOrgEx(dc, 0, 0, nullptr);
    image.StretchBlt(dc, dstRect, srcRect);
    ::SetStretchBltMode(dc, oldMode);
    newImage.ReleaseDC();

    // 交换新旧图像
    HBITMAP newImageHandle = newImage.Detach();
    HBITMAP oldImageHandle = image.Detach();
    newImage.Attach(oldImageHandle); // 这样oldImageHandle就随newImage一同销毁
    image.Attach(newImageHandle);
}

void CClientDemoDlg::TryEnablePrint()
{
    if (m_txtPrinterName.GetWindowTextLength()) {
        if (printByDrawing) {
            m_btnEditImage.EnableWindow(TRUE);
            m_btnPrintSARPass.EnableWindow(TRUE);
            m_btnSelectImage.EnableWindow(FALSE);
            m_btnPrint.EnableWindow(FALSE);
        } else {
            m_btnEditImage.EnableWindow(FALSE);
            m_btnPrintSARPass.EnableWindow(FALSE);
            m_btnSelectImage.EnableWindow(TRUE);
            if (m_txtImagePath.GetWindowTextLength())
                m_btnPrint.EnableWindow(TRUE);
        }
    } else {
        m_btnEditImage.EnableWindow(FALSE);
        m_btnPrintSARPass.EnableWindow(FALSE);
        m_btnPrint.EnableWindow(FALSE);
        m_btnSelectImage.EnableWindow(FALSE);
    }
}

BEGIN_MESSAGE_MAP(CClientDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_SHOW_PRINTER_PICKER, &CClientDemoDlg::OnBnClickedBtnShowPrinterPicker)
    ON_BN_CLICKED(IDC_BTN_SELECT_IMAGE, &CClientDemoDlg::OnBnClickedBtnSelectImage)
    ON_BN_CLICKED(IDC_BTN_SHOW_PRINT_OPTIONS, &CClientDemoDlg::OnBnClickedBtnShowPrintOptions)
    ON_BN_CLICKED(IDC_BTN_PRINT, &CClientDemoDlg::OnBnClickedBtnPrint)
    ON_BN_CLICKED(IDC_BTN_SHOW_PRINTER_MAINTENANCE_DIALOG, &CClientDemoDlg::OnBnClickedBtnShowPrinterMaintenanceDialog)
    ON_EN_CHANGE(IDC_COPY_COUNT, &CClientDemoDlg::OnEnChangeCopyCount)
    ON_BN_CLICKED(IDC_RADIO_CREATE_BY_FILE, &CClientDemoDlg::OnBnClickedRadioCreateByFile)
    ON_BN_CLICKED(IDC_RADIO_BY_DRAWING, &CClientDemoDlg::OnBnClickedRadioByDrawing)
    ON_BN_CLICKED(IDC_BTN_EDIT_IMAGE, &CClientDemoDlg::OnBnClickedBtnEditImage)
    ON_BN_CLICKED(IDC_BTN_PRINT_SAR_PASS, &CClientDemoDlg::OnBnClickedBtnPrintSarPass)
	ON_BN_CLICKED(IDC_CHECK1, &CClientDemoDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BTN_PRINT2, &CClientDemoDlg::OnBnClickedBtnPrint2)
	ON_BN_CLICKED(IDC_BTN_PRINT3, &CClientDemoDlg::OnBnClickedBtnPrint3)
	ON_BN_CLICKED(IDC_BTN_PRINT4, &CClientDemoDlg::OnBnClickedBtnPrint4)
	ON_BN_CLICKED(IDC_BTN_PRINT5, &CClientDemoDlg::OnBnClickedBtnPrint5)
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CClientDemoDlg 消息处理程序
CString GetFileVer()
{
	char cPath[200],szVersionBuffer[200];
	DWORD dwHandle,InfoSize;
	CString strVersion;
	::GetModuleFileNameA(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度
	InfoSize = GetFileVersionInfoSizeA(cPath,&dwHandle); //将版本信息资源读入缓冲区
	if(InfoSize==0) return _T("None VerSion Supprot");
	char *InfoBuf = new char[InfoSize];
	GetFileVersionInfoA(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
	unsigned int  cbTranslate = 0;
	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;
	VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
	// Read the file description for each language and code page.
	for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
	{
		char  SubBlock[200];
		sprintf( SubBlock,
			"\\StringFileInfo\\%04x%04x\\FileVersion",
			lpTranslate[i].wLanguage,
			lpTranslate[i].wCodePage);
		void *lpBuffer=NULL;
		unsigned int dwBytes=0;
		VerQueryValueA(InfoBuf,
			SubBlock,
			&lpBuffer,
			&dwBytes);
		CString strTemp((char *)lpBuffer);
		strVersion+=strTemp;

	}
	return strVersion;
}
BOOL CClientDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    CString title;
    GetWindowText(title);
    SetWindowText(title + _T(" - ") + GetApp().GetVersion());

	// 初始化控件
	CString FileVer = L"CG_" + GetFileVer();//常规版本 CG
	SetWindowText(FileVer);
    InitPrinterControls();
    InitJobControls();

	//GetDlgItem(IDC_BTN_PRINT2)->ShowWindow(SW_HIDE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDemoDlg::OnBnClickedBtnShowPrinterPicker()
{
    CPrinterPickerDialog dialog;
    CString printerName;
    if (IDOK == dialog.DoModal()) {
        printerName = GetApp().GetPrinter().name;
        m_txtPrinterName.SetWindowText(printerName);
        m_btnSelectImage.EnableWindow(TRUE);
        m_txtCopyCount.EnableWindow(TRUE);
        m_btnShowPrinterMaintenanceDlg.EnableWindow(TRUE);
        TryEnablePrint();


		auto &printer = GetApp().GetPrinter();

		//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
		//    server.GetPort());
		auto ret = ::DASSetPrinterName(
			(LPSTR)(LPCSTR)printer.name,
			(LPSTR)(LPCSTR)printer.model);
		BYTE flag = 0;
		//auto re = DASGetEjectMode(&flag);
		CheckDlgButton(IDC_CHECK1,flag);

		GetDlgItem(IDC_BTN_PRINT2)->ShowWindow(flag);
    }
}

void CClientDemoDlg::OnBnClickedBtnSelectImage()
{
	//CString szFilters = _T("所有文件(*.*)|*.*||");
	//CFileDialog fileDlg(true, NULL, NULL, OFN_NOCHANGEDIR, szFilters, this);
	//if(fileDlg.DoModal()!=IDOK)
	//{
	//	// 操作完成
	//	return;
	//}
    // 显示加载图片的按钮
    CFileDialog fileDialog(
        TRUE,
        NULL, 
		NULL,
        OFN_PATHMUSTEXIST | OFN_ENABLESIZING | OFN_EXPLORER | OFN_HIDEREADONLY,
        _T("图像文件(*.jpeg;*.jpg;*.bmp;*.png;*.tif;*.gif)|*.jpeg;*.jpg;*.bmp;*.png;*.tif;*.gif|"),
        this);
	
    if (fileDialog.DoModal() == IDOK) {
        auto &job = GetApp().GetCurrentJob();
        job.imagePath = (CStringA)fileDialog.GetPathName();
        m_txtImagePath.SetWindowText(fileDialog.GetPathName());
        DisplayImage();
        m_btnPrint.EnableWindow(TRUE);
    }
}

void CClientDemoDlg::OnBnClickedBtnShowPrintOptions()
{
    CPrintOptionDialog dialog;
    if (dialog.DoModal() == IDOK) {
        DisplayImage();
    }
}
CStringA ReErr;
int FeedType(int FeederFlag, int OutCardDir)//进卡类型
{
	int Pattern;
	char pcs[256][256] = { 0 };
	int connstrlen = 256;
	int printtype = 1;
	UINT32 print_flag = DASEnumPrinter(pcs[0], &connstrlen, printtype);
	if (print_flag != 0x00000000)
	{
		//cdr.log(0, "%s\r\n", "签注机离线！");
		ReErr.Format("%s", "$#$签注机离线!");
		///DASExit();
		return 1;
	}
	//DASInit();
	print_flag = DASSetPrinterName(pcs[0], "D300RW");
	if (print_flag != 0x00000000)
	{
		//cdr.log(0, "%s\r\n", "链接签注机错误！");
		ReErr.Format("%s", "$#$链接签注机错误!");
		//DASExit();
		return 1;
	}
	print_flag = DASSetCardBoxEjectCard(FeederFlag, OutCardDir);
	if (print_flag != 0x00000000)
	{
		//cdr.log(0, "%s\r\n", "设置打印机进卡方式失败！");
		ReErr.Format("%s%d%d", "$#$设置打印机进卡方式失败!", FeederFlag, OutCardDir);
		//DASExit();
		return 1;
	}

	print_flag = DASGetFeedCardPattern(&Pattern);
	if (print_flag != 0x00000000)
	{
		//cdr.log(0, "%s\r\n", "获取打印机装卡模式失败！");
		ReErr.Format("%s", "$#$获取打印机装卡模式失败!");
		//DASExit();
		return 1;
	}

	if (Pattern != FeederFlag)
	{
		print_flag = DASSetFeedCardPattern(FeederFlag);
		if (print_flag != 0x00000000)
		{
			//cdr.log(0, "%s\r\n", "设置打印机装卡模式为手动模式失败！");
			ReErr.Format("%s", "$#$设置打印机装卡模式为手动模式失败!");
			return 1;
		}
	}
	//DASExit();
	return 0;
}
int CardIn() {//进卡
	//	return 0;
	int Pattern;
	UINT64 status;
	if (FeedType(1,0) != 0)
	{
		return 1;
	}
	char pcs[256][256] = { 0 };
	int connstrlen = 256;
	int printtype = 1;
	UINT32 print_flag = DASEnumPrinter(pcs[0], &connstrlen, printtype);
	if (print_flag != 0x00000000)
	{
		//cdr.log(0, "%s\r\n", "ǩע�����ߣ�");
		ReErr.Format("%s", "$#$ǩע������!");
		///DASExit();
		return 1;
	}
	//DASInit();
	print_flag = DASSetPrinterName(pcs[0], "D300RW");
	if (print_flag != 0x00000000)
	{
		//cdr.log(0, "%s\r\n", "����ǩע������");
		ReErr.Format("%s", "$#$����ǩע������!");
		//DASExit();
		return 1;
	}
//  	print_flag = DASSetManualCard();
//  	if (print_flag != 0x00000000)
//  	{
//  		ReErr.Format("%s", "$#$��ӡ��װ��ʧ��!");
//  		return 1;
//  	}
	for (int i = 0; i < 50; i++)
	{
		print_flag = DASFetchPrinterStatus(&status);
		if (print_flag != 0x00000000)
		{
			//cdr.log(0, "%s\r\n", "��ӡ��״̬��ȡʧ�ܣ�");
			ReErr.Format("%s", "$#$��ӡ��״̬��ȡʧ��!");
			return 1;
		}

		print_flag = DASGetPrinterStatus_ErrorNo(status);
		if (print_flag != 0x00000000)
		{
			Sleep(100);
			continue;
		}
		else
		{
			break;
		}
	}
	if (print_flag != 0x00000000)
	{
		switch (print_flag)
		{
		case 0x00000001:
			//cdr.log(0, "%s\r\n", "��ӡ��ȱ�����");
			ReErr.Format("%s", "$#$��ӡ��ȱ����!");
			break;
		case 0x00000002:
			//cdr.log(0, "%s\r\n", "��ӡ���������");
			ReErr.Format("%s", "$#$��ӡ��������!");
			break;
		case 0x00000003:
			//cdr.log(0, "%s\r\n", "��ӡ����λ���");
			ReErr.Format("%s", "$#$��ӡ����λ��!");
			break;
		case 0x00000004:
			//	cdr.log(0, "%s\r\n", "��ӡ��������");
			ReErr.Format("%s", "$#$��ӡ�������!");
			break;
		case 0x00000005:
			//cdr.log(0, "%s\r\n", "��ӡ����Ƭ��ʱ��");
			ReErr.Format("%s", "$#$��ӡ����Ƭ��ʱ!");
			break;
		case 0x00000006:
			//cdr.log(0, "%s\r\n", "��ӡ��ǰ�Ǵ򿪴��");
			ReErr.Format("%s", "$#$��ӡ��ǰ�Ǵ򿪴�!");
			break;
		case 0x00000007:
			//cdr.log(0, "%s\r\n", "��ӡ���������");
			ReErr.Format("%s", "$#$��ӡ��������!");
			break;
		case 0x00000008:
			//cdr.log(0, "%s\r\n", "��ӡ��ӡͷ���´��");
			ReErr.Format("%s", "$#$��ӡ��ӡͷ���´�!");
			break;
		case 0x00000009:
			//cdr.log(0, "%s\r\n", "��ӡ��ӡͷ���´��");
			ReErr.Format("%s", "$#$��ӡ��ӡͷ���´�!");
			break;
		case 0x0000000a:
			//cdr.log(0, "%s\r\n", "��ӡ��ӡͷ���������");
			ReErr.Format("%s", "$#$��ӡ��ӡͷ��������!");
			break;
		case 0x0000000b:
			//cdr.log(0, "%s\r\n", "��ӡ�����������");
			ReErr.Format("%s", "$#$��ӡ����������!");
			break;
		case 0x0000000c:
			//	cdr.log(0, "%s\r\n", "��ӡ��Flash ���");
			ReErr.Format("%s", "$#$��ӡ��Flash ��!");
			break;
		default:
			//cdr.log(0, "%s\r\n", "��ӡ��λ�ô���");
			ReErr.Format("%s", "$#$��ӡ��λ�ô���!");
			break;
		}
		return 1;
	}
	//DASExit();
	return 0;
}


void CClientDemoDlg::OnBnClickedBtnPrint()
{
	//CardIn();
	//FeedType(0,0);
    uint32_t ret;
    JobInfo info;

    auto &job = GetApp().GetCurrentJob();

    if (job.copyCount < 1 || job.copyCount >65535) {
        MessageBox(_T("打印份数超出允许范围(1 - 65535)"));
        m_txtCopyCount.SetSel(0, -1);
        m_txtCopyCount.SetFocus();
        return;
    }

    //auto &server = GetApp().GetServer();
    auto &printer = GetApp().GetPrinter();

    //ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
    //    server.GetPort());
    ret = ::DASSetPrinterName(
        (LPSTR)(LPCSTR)printer.name,
        (LPSTR)(LPCSTR)printer.model);

	if  ( ret > 0 ){
		MessageBox(_T("打印失败。") + GetApp().TranslateErrorCode(ret));
		return;
	}

    info.printer = printer.name;
    info.printerModel = printer.model;
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

    ret = ::DASSetGraphicDataByFile(0, (LPSTR)(LPCSTR)job.imagePath);

	if  ( ret == DS_CPSDK_OK ){
		BOOL DontEjectCard = ((CButton*)(GetDlgItem(IDC_CHECK1)))->GetCheck();
		info.submitDate = time(nullptr);
		if(!DontEjectCard)
		{

			if (0 ==  ::DASPrintCard()) {
				MessageBox(_T("打印成功。"));
			} else {
				MessageBox(_T("打印失败。") + GetApp().TranslateErrorCode(ret));
			}
		}
		else
		{
			if (0 ==  ::DASPrintCard ()) {
				MessageBox(_T("打印成功。"));
			} else {
				MessageBox(_T("打印失败。") + GetApp().TranslateErrorCode(ret));
			}
		}
	}else{
		MessageBox(_T("打印失败。") + GetApp().TranslateErrorCode(ret));
	}


}

void CClientDemoDlg::OnBnClickedBtnShowPrinterMaintenanceDialog()
{
    CMaintenanceSheets dialog;
    dialog.DoModal();


// 	BYTE flag = 0;
// 	auto re = DASGetEjectMode(&flag);
// 	CheckDlgButton(IDC_CHECK1,flag);
// 
// 	GetDlgItem(IDC_BTN_PRINT2)->ShowWindow(flag);
}



void CClientDemoDlg::OnEnChangeCopyCount()
{
    CString text;
    m_txtCopyCount.GetWindowText(text);
    int copyCount = _tcstol(text, nullptr, 10);
    GetApp().GetCurrentJob().copyCount = copyCount;
}

void CClientDemoDlg::OnBnClickedRadioCreateByFile()
{
    printByDrawing = false;
    TryEnablePrint();
}

void CClientDemoDlg::OnBnClickedRadioByDrawing()
{
    printByDrawing = true;
    TryEnablePrint();
}

void CClientDemoDlg::OnBnClickedBtnEditImage()
{
    CDrawCardDialog dialog;
    dialog.DoModal();
}

void CClientDemoDlg::OnBnClickedBtnPrintSarPass()
{
    CPrintEEPEntryDlg dialog;
    dialog.DoModal();
}


void CClientDemoDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	auto &printer = GetApp().GetPrinter();
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);

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

	//::ShowWindow(GetDlgItem(IDC_BTN_PRINT2)->GetSafeHwnd(),flag?SW_SHOW:SW_HIDE);
}


void CClientDemoDlg::OnBnClickedBtnPrint2()
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


void CClientDemoDlg::OnBnClickedBtnPrint3()
{
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton*)GetDlgItem( IDC_CHECK3))->GetCheck())
	{
		SetDlgItemText(IDC_EDIT2,L"");
		byte a = 0 ;
		auto re = DASGetEraseTemperature(&a);
		SetDlgItemInt(IDC_EDIT2,a);

	}
	else
	{
		int a = GetDlgItemInt(IDC_EDIT2);
		auto re = DASSetEraseTemperature_NoReset(a);
	}
}


void CClientDemoDlg::OnBnClickedBtnPrint4()
{
	// TODO: 在此添加控件通知处理程序代码
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton*)GetDlgItem( IDC_CHECK2))->GetCheck())
	{
		SetDlgItemText(IDC_EDIT3,L"");
		byte a = 0 ;
		auto re = DASGetPrintTemperature(&a);
		SetDlgItemInt(IDC_EDIT3,a);

	}
	else
	{
		int a = GetDlgItemInt(IDC_EDIT3);
		auto re = DASSetPrintTemperature_NoReset(a);

	}
}


void CClientDemoDlg::OnBnClickedBtnPrint5()
{
	// TODO: 在此添加控件通知处理程序代码
	auto &printer = GetApp().GetPrinter();

	//ret = ::DASSetNetworkParams((LPSTR)(LPCSTR)server.GetIp(),
	//    server.GetPort());
	auto ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)printer.name,
		(LPSTR)(LPCSTR)printer.model);
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton*)GetDlgItem( IDC_CHECK14))->GetCheck())
	{
		SetDlgItemText(IDC_EDIT13,L"");
		byte a = 0 ;
		auto re = DASGetPrintSpeed(&a);
		SetDlgItemInt(IDC_EDIT13,a);

	}
	else
	{
		int a = GetDlgItemInt(IDC_EDIT13);
		auto re = DASSetPrintSpeed_NoReset(a);
	}
}


void CClientDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CToolRWLicenseDlg abc(this);
	abc.DoModal();
}
