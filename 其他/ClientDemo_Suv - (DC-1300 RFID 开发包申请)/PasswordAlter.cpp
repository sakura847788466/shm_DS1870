// PasswordAlter.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "PasswordAlter.h"
#include "afxdialogex.h"


// CPasswordAlter 对话框

IMPLEMENT_DYNAMIC(CPasswordAlter, CPropertyPage)

CPasswordAlter::CPasswordAlter()
	: CPropertyPage(CPasswordAlter::IDD)
	, m_strPwd1(_T(""))
	, m_strPwd2(_T(""))
	, m_PrinterHeadID_B(_T(""))
	, m_printerHeadNumber_A(_T(""))
{

}

CPasswordAlter::~CPasswordAlter()
{
}

void CPasswordAlter::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strPwd1);
	DDV_MaxChars(pDX, m_strPwd1, 8);
	DDX_Text(pDX, IDC_EDIT3, m_strPwd2);
	DDV_MaxChars(pDX, m_strPwd2, 8);
	DDX_Text(pDX, IDC_EDIT1, m_PrinterHeadID_B);
	DDV_MaxChars(pDX, m_PrinterHeadID_B, 17);
	DDX_Text(pDX, IDC_EDIT11, m_printerHeadNumber_A);
	DDV_MaxChars(pDX, m_printerHeadNumber_A, 17);
}


BEGIN_MESSAGE_MAP(CPasswordAlter, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CPasswordAlter::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON20, &CPasswordAlter::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CPasswordAlter::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON18, &CPasswordAlter::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CPasswordAlter::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON22, &CPasswordAlter::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON24, &CPasswordAlter::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON23, &CPasswordAlter::OnBnClickedButton23)
END_MESSAGE_MAP()


// CPasswordAlter 消息处理程序


void CPasswordAlter::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT1,L"");
	char pterheadsn[128]={0};
	DWORD ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
		(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
	if(ret != 0){
		MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	ret = DASGetPrinterHeadID_B(pterheadsn,128);
	if(ret != 0){
		MessageBox(_T("查询打印机状态失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	SetDlgItemText(IDC_EDIT1,CString(pterheadsn));
}


void CPasswordAlter::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(1);
	SetDlgItemText(IDC_EDIT2,L"");
	CHAR PWD1[32]={0};
	DWORD ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
		(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
	if(ret != 0){
		MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	ret = DASGetKey(0,PWD1,32);
	if(ret != 0){
		MessageBox(_T("获取一级密码失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	SetDlgItemText(IDC_EDIT2,CString(PWD1));
}


std::string Hex2String(const char* buffer,int bufferLen)
{
	std::string str;
	if(bufferLen<=0 ) return std::string("");
	if( buffer==NULL) return std::string("");
	CStringA tempch;str = "";int f = 0;
	for(int i = 0;i<bufferLen;++i)
	{
		BYTE a = buffer[i];
		tempch.Format("%.2x ",a);
		// 		if(f!=0 && f%8==0)
		// 			str+="\r\n";
		str+=tempch;
		f++;
	}
	return str;
}
void CPasswordAlter::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(1);
	char PWD1[12]={0};
	char PWD2[12]={0};
	GetDlgItemTextA(m_hWnd,IDC_EDIT2,PWD1,9);
	GetDlgItemTextA(m_hWnd,IDC_EDIT3,PWD2,9);
	if(strlen(PWD1)<=8 && strlen(PWD2)<=8 && strlen(PWD1)!=0 && strlen(PWD2)!=0)
	{
		DWORD ret = ::DASSetPrinterName(
			(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
			(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if(ret != 0){
			MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
		ret = DASSetKey(0,PWD1,strlen(PWD1),PWD2,strlen(PWD2));
		if(ret != 0){
			MessageBox(_T("设置一级密码失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
	}
	else{
		MessageBox(_T("请输入一级密码和二级密码，且长度必须小于等于8位"));
	}
}


void CPasswordAlter::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT3,L"");
	CHAR PWD2[32]={0};
	DWORD ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
		(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
	if(ret != 0){
		MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	ret = DASGetKey(1,PWD2,32);
	if(ret != 0){
		MessageBox(_T("获取二级密码失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	SetDlgItemText(IDC_EDIT3,CString(PWD2));
}


void CPasswordAlter::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	char PWD2[12]={0};
	GetDlgItemTextA(m_hWnd,IDC_EDIT3,PWD2,8);
	if(strlen(PWD2)<=8 && strlen(PWD2)!=0)
	{
		DWORD ret = ::DASSetPrinterName(
			(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
			(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if(ret != 0){
			MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
		ret = DASSetKey(1,0,0,PWD2,strlen(PWD2));
		if(ret != 0){
			MessageBox(_T("设置二级密码失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
	}
	else
	{
		MessageBox(_T("密码长度必须小于等于8位"));
	}
}


void CPasswordAlter::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	char printerHeadNo[18]={0};
	GetDlgItemTextA(m_hWnd,IDC_EDIT1,printerHeadNo,18);
	if(strlen(printerHeadNo)<=17 && strlen(printerHeadNo)!=0)
	{
		DWORD ret = ::DASSetPrinterName(
			(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
			(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if(ret != 0){
			MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
		ret = ::DASSetPrinterHeadID_B(printerHeadNo,strlen(printerHeadNo));
		if(ret != 0){
			MessageBox(_T("设置打印头编号失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
	}
	else
	{
		MessageBox(_T("编号长度必须小于等于17位"));
	}
}


void CPasswordAlter::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
	char printerHeadNo1[20]={0};
	char printerHeadNo2[20]={0};
	GetDlgItemTextA(m_hWnd,IDC_EDIT11,printerHeadNo1,18);
	GetDlgItemTextA(m_hWnd,IDC_EDIT1,printerHeadNo2,18);
	if(strlen(printerHeadNo1)<=17 && strlen(printerHeadNo2)<=17)
	{
		DWORD ret = ::DASSetPrinterName(
			(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
			(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
		if(ret != 0){
			MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
		ret = DASSetPrinterHeadID_A(printerHeadNo1,17,printerHeadNo2,17);
		if(ret != 0){
			MessageBox(_T("设置打印机编号A失败：") +	GetApp().TranslateErrorCode(ret));
			return;
		}
	}
	else{
		MessageBox(_T("请输入打印机编号A和打印机编号B，且长度必须小于等于17位"));
	}
}


void CPasswordAlter::OnBnClickedButton23()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT11,L"");
	DWORD ret = ::DASSetPrinterName(
		(LPSTR)(LPCSTR)GetApp().GetPrinter().name,
		(LPSTR)(LPCSTR)GetApp().GetPrinter().model);
	if(ret != 0){
		MessageBox(_T("设置打印机名称失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	byte pterheadsn[128]={0};
	int length = 128;
	ret = DASGetPrinterHeadSerialNumber(pterheadsn,&length);
	if(ret != 0){
		MessageBox(_T("查询打印机状态失败：") +	GetApp().TranslateErrorCode(ret));
		return;
	}
	SetDlgItemText(IDC_EDIT11,CString((char*)pterheadsn));
}
