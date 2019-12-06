// MaintenanceSheets.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "MaintenanceSheets.h"


// CMaintenanceSheets

IMPLEMENT_DYNAMIC(CMaintenanceSheets, CPropertySheet)

CMaintenanceSheets::CMaintenanceSheets(CWnd *pParentWnd)
: CPropertySheet(IDS_MAINTENANCE_SHEETS_TITLE, pParentWnd)
{
    AddPage((CPropertyPage*)&infoPage);
	AddPage((CPropertyPage*)&operationPage);
	AddPage((CPropertyPage*)&PasswordAlter);
}

CMaintenanceSheets::~CMaintenanceSheets()
{
	RemovePage((CPropertyPage*)&infoPage);
	RemovePage((CPropertyPage*)&operationPage);
	RemovePage((CPropertyPage*)&PasswordAlter);
}


BEGIN_MESSAGE_MAP(CMaintenanceSheets, CPropertySheet)
END_MESSAGE_MAP()


// CMaintenanceSheets 消息处理程序
