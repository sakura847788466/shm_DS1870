
// ToolRWLicenseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "ToolRWLicenseDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <memory>

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ds_iomem_suv.lib")
#else
#pragma comment(lib, "..\\Release\\ds_iomem_suv.lib")
#endif
#pragma 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define getSafeBuf(TYPE,SIZE) std::unique_ptr<TYPE>(new TYPE[SIZE])

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


// CToolRWLicenseDlg �Ի���




CToolRWLicenseDlg::CToolRWLicenseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolRWLicenseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolRWLicenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_printlist);
	DDX_Control(pDX, IDC_EDIT2, m_output);
	DDX_Control(pDX, IDC_CHECK1, m_epcid_isstring);
}

BEGIN_MESSAGE_MAP(CToolRWLicenseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CToolRWLicenseDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolRWLicenseDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CToolRWLicenseDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolRWLicenseDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CToolRWLicenseDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CToolRWLicenseDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CToolRWLicenseDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CToolRWLicenseDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CToolRWLicenseDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CToolRWLicenseDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CToolRWLicenseDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CToolRWLicenseDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CToolRWLicenseDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CToolRWLicenseDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON27, &CToolRWLicenseDlg::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CToolRWLicenseDlg::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON15, &CToolRWLicenseDlg::OnBnClickedButton15)
END_MESSAGE_MAP()


// CToolRWLicenseDlg ��Ϣ�������
CString GetFileVer();
BOOL CToolRWLicenseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CString str;
	str.Format(L"1300 RFID ��д "+GetFileVer());
	SetWindowTextW(str);
	MoveWindow(200,200,420,500);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CToolRWLicenseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CToolRWLicenseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD CToolRWLicenseDlg::SetPrinterName()
{
	auto ret = DASSetPrinterName(
		theApp.GetPrinter().name,
		theApp.GetPrinter().model);
	if(ret)
	{
		output(L"����ö��");
	}
	return ret;
	
}

void CToolRWLicenseDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	SetPrinterName();
// 	CString str;
// 	GetDlgItemText(IDC_EDIT1, str);
// 	CStringA strA(str);
// 	if( 0 != DSWriteLicense((byte*)strA.GetBuffer(), strA.GetLength()))
// 	{
// 		output(L"д��ʧ��");
// 		return;
// 	}
// 	output(L"д��ɹ�");
}


void CToolRWLicenseDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	SetPrinterName();
// 	SetDlgItemText(IDC_EDIT1, L"");
// 	std::vector<char> buf(4096);
// 	unsigned int rlen = 0;
// 	if( 0 != DSReadLicense((byte*)&buf[0], &rlen))
// 	{
// 		output(L"��ȡʧ��");
// 		return;
// 	}
// 	CString str(&buf[0]);
// 	SetDlgItemText(IDC_EDIT1, str);
// 	output(str);
// 	output(L"��ȡ�ɹ�");
}

void CToolRWLicenseDlg::output(const CString str)
{
	if(str == L"CLR")
		m_output.SetWindowTextW(L"");
	else
	{
		CString curStr;
		m_output.GetWindowTextW(curStr);
		CString s;
		s+=str;
		s+=L"\r\n";
		s+=curStr;
		if(s.GetLength()>8192) s=s.Mid(0,8192);
		m_output.SetWindowTextW(s);
		// 		m_output.SendMessage(EM_SCROLL, SB_BOTTOM, 0);//����������
		// 		int nLen = m_output.SendMessage(WM_GETTEXTLENGTH);
		// 		m_output.SetSel(nLen, nLen, FALSE);
	}
}

template<typename stringtype>
static int Split2(stringtype &orgstr, stringtype &seprator, std::vector<stringtype> *res)
{
	stringtype tempOrgStr = orgstr;
	int items_num = 0;
	int sepLen = seprator.length();
	while(1)
	{
		if(tempOrgStr.length()==0)
			break;
		items_num++;
		int pos = tempOrgStr.find(seprator);
		if(pos == stringtype::npos)
		{
			if(res)
				res->push_back(tempOrgStr);
			break;
		}
		stringtype item = tempOrgStr.substr(0,pos);
		if(res)
			res->push_back(item);
		if(pos + sepLen > tempOrgStr.length()-1)
			break;
		tempOrgStr = tempOrgStr.substr(pos+sepLen);
	}
	return items_num;
}

void CToolRWLicenseDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_printlist.ResetContent();
	/*
	1:�� USB ��ӡ��
	2:�������ӡ��
	3:���д�ӡ��
	*/
	char buf[1024] = {0};
	int buflen = 1024;
	DWORD RE = DASEnumPrinter(buf,&buflen, 3);
	if(RE != 0)
	{
		output(L"ö��ʧ��");
		return;
	}
	CString printerlist = (CString)buf;
	if(printerlist.GetLength()==0)
	{
		output(L"δ�ҵ�����ӡ��");
		return ;
	}
	
	std::vector<CString> printers;
	std::wstring str = printerlist.GetBuffer();
	std::wstring sp = L"\n";
	std::vector<std::wstring> res;
	Split2<std::wstring>(str, sp, &res);
	for(auto i = res.begin(); i != res.end(); ++i)
	{
		m_printlist.AddString(i->data());
	}
}


void CToolRWLicenseDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	output(L"CLR");
}


void CToolRWLicenseDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	SetPrinterName();
// 	char buf[1024] = {0};
// 	int buflen = 1024;
// 	DWORD RE = DASGetRunningInfo(2, (byte*)buf, &buflen);
// 	if(RE)
// 	{
// 		output(L"��ȡ����ʧ��");
// 		return;
// 	}
// 
// 	output(CString(buf));
}


void CToolRWLicenseDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	auto RE = DAS_RFIDTag_ClrCache();
	if(RE)
	{
		output(L"�������ʧ��");
		return;
	}
	output(L"�������ɹ�");
}


void CToolRWLicenseDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	unsigned int numOfTag = 0;
	auto RE = DAS_RFIDTag_Search(&numOfTag);
	if(RE)
	{
		output(L"������ǩʧ��");
		return;
	}
	CString strNumOfTag;
	strNumOfTag.Format(L"�������ı�ǩ����%d",numOfTag);
	output(strNumOfTag);
}


void CToolRWLicenseDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	byte buffer[34] = {0};
	int buflen = 33;
	SetDlgItemText(IDC_EDIT3,L"");
	auto RE = DAS_RFIDTag_Read_EPCID(buffer, buflen);
	if(RE)
	{
		output(L"�� EPC ID ʧ��");
		return;
	}
	CStringA strEpcId;
	strEpcId.Format("��ȡ��EPC ID��");
	CStringA strEpc;
	if(m_epcid_isstring.GetCheck())
	{
		strEpc += (char*)(&buffer[21]);
	}
	else
	{
		for(int i = 0 ; i<12; ++i)
		{
			CStringA temp;
			temp.Format(" %02X",buffer[21+i]);
			strEpc += temp;
		}

	}

	output(CString(strEpcId+strEpc));
	SetDlgItemText(IDC_EDIT3,CString(strEpc));
}

static DWORD String2Hex(CStringA& str,char* buffer,int bufferLen,int &writen)
{
	if(str.GetLength()==0) return 0;
	str.MakeUpper();
	for(UINT a = 0;a<256;a++)
	{
		if((a>=48 && a<=57) || (a>=65 && a<=70))
			continue;
		else
			str.Remove(a);
	}
	if(str.GetLength()%2!=0) return 0;

	writen = 0;
	char sendBuffer[4096] = {0};
	ZeroMemory(buffer,bufferLen);
	auto datalen = str.GetLength()/2;
	for(int i=0;i< datalen;i++)
	{
		BYTE H,L;
		H = str.GetAt(i*2);
		L = str.GetAt(i*2+1);
		if(H>=48 && H<=57)
			H-=48;
		else if(H>=65 && H<=70)
			H-=55;
		if(L>=48 && L<=57)
			L-=48;
		else if(L>=65 && L<=70)
			L-=55;
		sendBuffer[i] = H*16+ L;
	}
	writen = datalen;
	memcpy(buffer,sendBuffer,datalen);
	return 0;
}
static DWORD Hex2String(CStringA& str,char* buffer,int bufferLen)
{
	if(bufferLen<=0) return 0x000D0001;
	CStringA tempch;str = "";int f = 0;
	for(int i = 0;i<bufferLen;++i)
	{
		BYTE a = buffer[i];
		tempch.Format("%.2x ",a);
		if(f!=0 && f%8==0)
			str+="\r\n";
		str+=tempch;
		f++;
	}
	return 0;
}
void CToolRWLicenseDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	CString EPC_IDW;
	GetDlgItemText(IDC_EDIT3,EPC_IDW);
	CStringA EPC_ID = CStringA(EPC_IDW);
	byte buf[32] = {0};
	if(m_epcid_isstring.GetCheck())
	{
		EPC_ID += "            ";
		memcpy(buf,EPC_ID.GetBuffer(),12);
	}
	else
	{
		int writen = 0;
		String2Hex(EPC_ID, (char*)buf,32, writen);
		if(writen != 12)
		{
			output(L"EPC ID ��ʽ����");
			return;
		}
	}
	
	auto RE = DAS_RFIDTag_Write_EPCID(buf, 12);
	if(RE)
	{
		output(L"д EPC ID ʧ��");
		return;
	}
	CString strNumOfTag;
	strNumOfTag.Format(L"д EPC ID �ɹ�");
	output(strNumOfTag);
}


void CToolRWLicenseDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	SetDlgItemText(IDC_EDIT4,L"");
	USHORT POW = 0;
	auto RE = DAS_RFIDTag_FetchReadPower(&POW);
	if(RE)
	{
		output(L"��ȡ������ʧ��");
		return;
	}
	CString strNumOfTag;
	CString strPowVal;
	strPowVal.Format(L"%.2f",POW/100.0);
	strNumOfTag.Format(L"������Ϊ%s",strPowVal);
	SetDlgItemText(IDC_EDIT4,strPowVal);
	output(strNumOfTag);
}


void CToolRWLicenseDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;

	SetDlgItemText(IDC_EDIT5,L"");
	USHORT POW = 0;
	auto RE = DAS_RFIDTag_FetchWritePower(&POW);
	if(RE)
	{
		output(L"��ȡд����ʧ��");
		return;
	}
	CString strNumOfTag;
	CString strPowVal;
	strPowVal.Format(L"%.2f",POW/100.0);
	strNumOfTag.Format(L"д����Ϊ%s",strPowVal);
	SetDlgItemText(IDC_EDIT5,strPowVal);
	output(strNumOfTag);
}


void CToolRWLicenseDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	CString strPow;
	GetDlgItemText(IDC_EDIT4,strPow);
	float pow = _ttof(strPow);
	USHORT POW = pow * 100;
	auto RE = DAS_RFIDTag_SetReadPower(POW);
	if(RE)
	{
		output(L"���ö�����ʧ��");
		return;
	}

	CString str;
	str.Format(L"���ö����� %.1f �ɹ�",pow);
	output(str);
}


void CToolRWLicenseDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	CString strPow;
	GetDlgItemText(IDC_EDIT5,strPow);
	float pow = _ttof(strPow);
	USHORT POW = pow * 100;
	auto RE = DAS_RFIDTag_SetWritePower(POW);
	if(RE)
	{
		output(L"����д����ʧ��");
		return;
	}

	CString str;
	str.Format(L"����д���� %.1f �ɹ�",pow);
	output(str);
}


void CToolRWLicenseDlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringA temp;
	temp.Format(" %02X",13);

	char *printerFilter[] = {"DASCOMDC-3300", "DASCOMDC-350", "DASCOMDC-3310", "DASCOMDC-3320", "DASCOMDC-3340", "DASCOMDC-3350", 
		"DASCOMDC-340", "DASCOMDC-341", "DASCOMDC-342", "DASCOMDC-348", "DASCOMDC-351", "DASCOMDC-352", "DASCOMDC-358",
		"DASCOMDC-7600", "DASCOMDC-7610", "DASCOMDC-7620", "DASCOMDC-7630", "DASCOMDC-7640", "DASCOMDC-7650", "DASCOMDC-600", 
		"DASCOMDC-610", "DASCOMDC-620", "DASCOMDC-630",
		"AISINODC-3300", "AISINODC-350", "AISINODC-3310", "AISINODC-3320", "AISINODC-3340", "AISINODC-3350", "AISINODC-340", 
		"AISINODC-341", "AISINODC-342", "AISINODC-348", "AISINODC-351", "AISINODC-352", "AISINODC-358",
		"AISINODC-7600", "AISINODC-7610", "AISINODC-7620", "AISINODC-7630", "AISINODC-7640", "AISINODC-7650", "AISINODC-600", 
		"AISINODC-610", "AISINODC-620", "AISINODC-630",
		"DB_END"};

	for(int j = 0; ;j++)
	{
		if(strcmp(printerFilter[j],"DB_END") == 0)
			break;
		CStringA printerName("DASCOMDC-3300@USB001");
		printerName = printerName.MakeUpper();
		printerName = printerName.Left(printerName.Find("@"));
		if(printerName.Compare(printerFilter[j]) == 0)
		{
			break;
		}
	}
}


void CToolRWLicenseDlg::OnBnClickedButton27()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())return;
	auto RE = DAS_RFIDTag_CommFast();
	if(RE == 0)
	{
		output(L"��ʼ�����");
	}
	else
	{
		output(L"��ʼ��ʧ��");
	}
}

BOOL ImageFromIDResource(CImage &m_Image, DWORD nID)
{
	LPCTSTR sTR = _T("PNG");
	//UINT nID = IDB_BITMAP1;
	//LPCTSTR sTR = RT_BITMAP;
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),sTR); // type
	if (!hRsrc)
		return FALSE;
	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;
	// Allocate global memory on which to create stream
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem,lpRsrc,len);
	IStream* pstm;
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);
	// load from stream
	m_Image.Load(pstm);
	// free/release stuff
	GlobalUnlock(m_hMem);
	pstm->Release();
	FreeResource(lpRsrc);
	return TRUE;
}

void CToolRWLicenseDlg::OnBnClickedButton28()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())
		return;

	CString ֤������ = L"֤�����룺 ";
	CString str ;
	
	GetDlgItemText(IDC_EDIT3, str);
	if(str.GetLength() == 0)
	{
		֤������ += L"!nocontent!";
	}
	else
	{
		str.Replace(L" ",L"");
		str = str.Right(8);
		֤������ += str;
	}

	if(SetPrinterName())
		return;

#define chkres(r,f)\
	if(r)\
	{\
	output(L## #f L"ʧ��");\
	return;\
	}

	auto  ret = 0;
	ret = ::DASsetCardSize(54.0, 85.6);
	chkres(ret,DASsetCardSize);
	ret = DASaddNeedEraseRect(0,0,53.5,85.6);
	chkres(ret,DASaddNeedEraseRect);
	CImage img;
// 	ImageFromIDResource(img, IDB_PNG2);
// 	if(((HBITMAP)img) == NULL)
// 	{
// 		output(L"������ԴͼƬʧ��");
// 		return;
// 	}
	char tempPath[4000] = {0};
	DWORD dwSize=4000;
	GetTempPathA(dwSize,tempPath);//��ȡ��ʱ�ļ���·��
	CString strPath(tempPath);
	SYSTEMTIME t ,ft;
	GetSystemTime(&t);
// 	strPath.Format(L"%s%d%d%d%d1%s",strPath,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds,L"temp1.png");
// 	if(FAILED(img.Save(strPath)))
// 	{
// 		output(L"������ԴͼƬʧ��");
// 		return;
// 	}
// 
// 	ret = DASdrawImage(0,0,53.98,85.6,CStringA(strPath).GetBuffer(),1);
// 	DeleteFile(strPath);
// 
// 	img.Destroy();
	ImageFromIDResource(img, IDB_PNG1);
	strPath.Format(L"%s%d%d%d%d2%s",strPath,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds,L"temp2.png");
	if(FAILED(img.Save(strPath)))
	{
		output(L"������ԴͼƬʧ��");
		return;
	}
	ret = DASdrawImage(16,17,21,27,CStringA(strPath).GetBuffer(),1);
	DeleteFile(strPath);
	chkres(ret,DASdrawImage);
	ret = ::DASsetFont("����",20);
	chkres(ret,DASsetFont);
	ret = DASdrawText(12,6,30,10,"�� �� ֤");
	ret = ::DASsetFont("΢���ź�",8);
	ret = DASdrawText(10,45+1,40,10,"�ÿ������� ����");
	ret = DASdrawText(10,50+1,40,10,"������λ�� ��ʵ����");
	ret = DASdrawText(10,55+1,40,10,CStringA(֤������).GetBuffer());
	ret = DASdrawText(10,60+1,40,10,"�������ڣ� 2016 / 09 / 01");
	ret = DASdrawText(10,65+1,40,10,"�� �� �� �� ����");
	ret = DASdrawText(10,70+1,40,10,"���ò��ţ� ������");
	ret = DASdrawText(10,75+1,40,6,"Я����Ʒ�� �ʼǱ�����");

	chkres(ret,DASdrawText);

	if (!(0 == (ret = ::DASBuildGraphicsDataForRotation(true,true,2))&&
		0 == (ret = ::DASPrintCard()))) 
	{
		output(_T("��ӡʧ��"));
	}

	output(L"��ӡ�ɹ�");
}


void CToolRWLicenseDlg::OnBnClickedButton15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(SetPrinterName())
		return;
	DWORD RE = DASSetFeedCardPattern(1);
	if(RE)
	{
		output(L"�����ֶ�����ʧ��");
		return;
	}
	RE = DASSetManualCard();


	if (RE != 0) {
		output(L"����ʧ�ܣ�");
		return;
	}
	output(L"�����ɹ�");
}
