#pragma once


// CPrinterOperationPage �Ի���

class CPrinterOperationPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPrinterOperationPage)

public:
	CPrinterOperationPage();
	virtual ~CPrinterOperationPage();

// �Ի�������
	enum { IDD = IDD_PRINTEROPERATIONPAGE };

private:
    uint32_t RefreshPrintParams();
    uint32_t RefreshFeedAndExitParams();

    CString  FilterAsHexString(const CString &in);
    CStringA HexStringToBytes(const CString &in);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton11();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton8();
    // X��ƫ��
    int m_printParamXOffset;
    // Y��ƫ��
    int m_printParamYOffset;
    // ��ӡŨ��
    int m_printParamChroma;
    afx_msg void OnBnClickedButton9();
    afx_msg void OnBnClickedButton10();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton12();
    afx_msg void OnBnClickedButton13();
    afx_msg void OnBnClickedButton14();
    afx_msg void OnBnClickedButton15();
    afx_msg void OnBnClickedButton17();
    afx_msg void OnBnClickedButton6();
    afx_msg void OnEnKillfocusEditUserData();
    afx_msg void OnBnClickedButton7();

	afx_msg void OnBnClickedButton16();
};
