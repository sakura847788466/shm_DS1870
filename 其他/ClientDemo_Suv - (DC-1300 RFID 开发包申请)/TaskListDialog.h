#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTaskListDialog 对话框

class CTaskListDialog : public CDialog
{
	DECLARE_DYNAMIC(CTaskListDialog)

public:
	CTaskListDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskListDialog();

// 对话框数据
	enum { IDD = IDD_TASKLISTDIALOG };

    virtual BOOL OnInitDialog();

private:
    int  AddTaskToListCtrl(JobInfo &);
    void RefreshTasks();
    void SelectTask(int index);
    void EnableTaskOperations();
    void DisableTaskOperations();
    JobInfo *GetSelectedTask();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_newPriority;
    CListCtrl m_listTasks;
    CButton m_btnSuspendJob;
    CButton m_btnResumeJob;
    CButton m_btnTerminateJob;
    CButton m_btnAdjustPriority;
    afx_msg void OnBnClickedBtnRefresh();
    afx_msg void OnNMClickListTasks(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnSuspendJob();
    afx_msg void OnBnClickedBtnResumeJob();
    afx_msg void OnBnClickedBtnTerminateJob();
    afx_msg void OnBnClickedBtnAdjustPriority();
    CButton m_chkTerminateNoWait;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnEnChangeTxtNewPriority();
    afx_msg void OnBnClickedBtnRemoveFinishedJobs();
    afx_msg void OnBnClickedBtnRemoveAllJobs();
};
