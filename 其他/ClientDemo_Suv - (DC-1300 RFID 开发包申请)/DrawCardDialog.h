#pragma once
#include "afxwin.h"
#include "afxfontcombobox.h"
#include "afxcolorbutton.h"


// CDrawCardDialog 对话框

class CDrawCardDialog : public CDialog
{
	DECLARE_DYNAMIC(CDrawCardDialog)

public:
	CDrawCardDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawCardDialog();

// 对话框数据
	enum { IDD = IDD_DRAWCARDDIALOG };

    virtual BOOL OnInitDialog();
	
private:
    BOOL m_bHasContent;

    BOOL UpdateDataToView();
    BOOL UpdateViewToData();
    void SetCardSize();
    void DisableAddProtectionRect();
    void log(const CString &line);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    bool   m_sizeSet;
    double m_coordX;
    double m_coordY;
    double m_width;
    double m_height;
    CString m_txtData;
    float m_fontSize;
    BOOL m_bold;
    BOOL m_italic;
    BOOL m_underline;
    int m_printDirection;
	int m_printRotation;
    BOOL m_qrAutoFill;
    int m_qrReliability;
    int m_barcodeType;
    BOOL m_barcodeReadableLabel;
    BOOL m_barcodeLabelAsHeader;
    CString m_txtInfo;
    CEdit m_txtInfoCtrl;
    CMFCFontComboBox m_cmbFontName;
    CMFCColorButton m_btnTextColor;
    CMFCColorButton m_btnBarcodeColor;
    BOOL m_verticalText;
    BOOL m_reversedTextOrder;
	
    afx_msg void OnEnChangeEdit2();
    afx_msg void OnEnChangeEdit3();
    afx_msg void OnEnChangeEdit5();
    afx_msg void OnEnChangeEdit6();
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnEnChangeEdit4();
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck4();
    afx_msg void OnBnClickedCheck5();
    afx_msg void OnCbnSelchangeCombo2();
    afx_msg void OnCbnSelchangeCombo3();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedButton6();
    afx_msg void OnBnClickedCheck6();
    afx_msg void OnBnClickedCheck7();
    afx_msg void OnBnClickedCheck8();
    BOOL m_layDown;
    afx_msg void OnBnClickedCheck9();
    int m_barcodeScale;
    afx_msg void OnCbnSelchangeCmbScale();
	BOOL m_FeedLine;
	double m_LineSpacing;
	double m_charSpacing;
    CString m_imagePath;
    afx_msg void OnBnClickedButton5();
    BOOL m_whiteAsTransparent;
    afx_msg void OnBnClickedButton7();
    afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedMfccolorbutton1();
	BOOL m_whiteAsTransparentBase64;
	afx_msg void OnBnClickedButton25();
	CString m_imageBase64;
	CString m_ImgBase64Suffix;
	int m_printRotationBase64;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedCheck12();
};
