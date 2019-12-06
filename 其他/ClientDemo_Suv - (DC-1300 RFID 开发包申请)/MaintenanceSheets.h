#pragma once

#include "PrinterInfoPage.h"
#include "PrinterOperationPage.h"
#include "PasswordAlter.h"

// CMaintenanceSheets

class CMaintenanceSheets : public CPropertySheet
{
	DECLARE_DYNAMIC(CMaintenanceSheets)

public:
    CMaintenanceSheets(CWnd* pParentWnd = NULL);
	virtual ~CMaintenanceSheets();

protected:
	DECLARE_MESSAGE_MAP()

private:
    CPrinterInfoPage infoPage;
    CPrinterOperationPage operationPage;
	CPasswordAlter PasswordAlter ;
};


