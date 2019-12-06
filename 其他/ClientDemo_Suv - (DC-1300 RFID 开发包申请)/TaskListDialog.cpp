// TaskListDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "TaskListDialog.h"
#include "afxdialogex.h"

#define REFRESH_TIMER_ID       1
#define REFRESH_TIMER_INTERVAL 5000

// CTaskListDialog 对话框

IMPLEMENT_DYNAMIC(CTaskListDialog, CDialog)

CTaskListDialog::CTaskListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskListDialog::IDD, pParent)
    , m_newPriority(0)
{
}

CTaskListDialog::~CTaskListDialog()
{
}

BOOL CTaskListDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    DWORD exStyle = m_listTasks.GetExtendedStyle();
    exStyle |= LVS_EX_AUTOSIZECOLUMNS;
    exStyle |= LVS_EX_FULLROWSELECT;
    m_listTasks.SetExtendedStyle(exStyle);
    m_listTasks.InsertColumn(0, _T("编号"), LVCFMT_RIGHT, 40);
    m_listTasks.InsertColumn(1, _T("创建时间"), LVCFMT_RIGHT, 100, 1);
    m_listTasks.InsertColumn(2, _T("打印机"), LVCFMT_LEFT, 100, 3);
    m_listTasks.InsertColumn(3, _T("状态"), LVCFMT_CENTER, 80, 4);
    m_listTasks.InsertColumn(4, _T("打印份数"), LVCFMT_RIGHT, 60, 5);
    m_listTasks.InsertColumn(5, _T("已打印份数"), LVCFMT_RIGHT, 60, 6);
    m_listTasks.InsertColumn(6, _T("任务优先级"), LVCFMT_RIGHT, 80, 7);
    m_listTasks.InsertColumn(7, _T("打印机状态"), LVCFMT_CENTER, 100, 8);
    DisableTaskOperations();
    RefreshTasks();
    SetTimer(REFRESH_TIMER_ID, REFRESH_TIMER_INTERVAL, nullptr);
    return TRUE;
}

int  CTaskListDialog::AddTaskToListCtrl(JobInfo &info)
{
    CString jobIndex;
    jobIndex.Format(_T("%d"), info.index);
    int itemIndex = m_listTasks.InsertItem(m_listTasks.GetItemCount(), jobIndex);

    CString submitDate =  GetApp().FormatTime(info.submitDate);
    m_listTasks.SetItemText(itemIndex, 1, submitDate);

    CString printer(info.printer);
    m_listTasks.SetItemText(itemIndex, 2, printer);

    CString statusName(info.GetStatusName());
    m_listTasks.SetItemText(itemIndex, 3, statusName);

    CString copyCount;
    copyCount.Format(_T("%d"), info.copyCount);
    m_listTasks.SetItemText(itemIndex, 4, copyCount);

    CString printedCopyCount;
    printedCopyCount.Format(_T("%d"), info.printedCopyCount);
    m_listTasks.SetItemText(itemIndex, 5, printedCopyCount);

    CString priority;
    priority.Format(_T("%d"), info.priority);
    m_listTasks.SetItemText(itemIndex, 6, priority);

    m_listTasks.SetItemText(itemIndex, 7, CString(info.printerStatus));

    return itemIndex;
}

void CTaskListDialog::RefreshTasks()
{
    int selectedTaskIndex = -1;
    int selectedItemIndex = m_listTasks.GetSelectionMark();
    if (!(selectedItemIndex < 0)) {
        selectedTaskIndex = ::_wtoi(m_listTasks.GetItemText(selectedItemIndex, 0));
    }

    selectedItemIndex = -1;
    auto &app = GetApp();
    auto list = app.GetJobListCopy();

    // 更新原有条目，标记选中的条目，标记要删除的条目
    std::vector<int> itemsToRemove;
    int itemCount = m_listTasks.GetItemCount();
    for (int i = 0; i < itemCount; ++i) {
        int taskIndex = ::_wtoi(m_listTasks.GetItemText(i, 0));
        auto iter = list.find(taskIndex);
        if (iter != list.end()) {
            if (taskIndex == selectedTaskIndex) {
                selectedItemIndex = i;
            }
            auto &task = iter->second;
            CString tmp;
            m_listTasks.SetItemText(i, 3, task.GetStatusName());
            tmp.Format(_T("%d"), task.printedCopyCount);
            m_listTasks.SetItemText(i, 5, tmp);
            tmp.Format(_T("%d"), task.priority);
            m_listTasks.SetItemText(i, 6, tmp);
            m_listTasks.SetItemText(i, 7, CString(task.printerStatus));
            list.erase(iter);
        } else {
            itemsToRemove.push_back(i);
        }
    }

    // 添加新条目
    std::for_each(list.begin(), list.end(), [this](ConstJobListItem &li) {
        AddTaskToListCtrl(li.second);
    });

    // 删除旧条目，调整选中条目的位置
    int removed = 0;
    auto fn = [this, &removed, &selectedItemIndex](const int &itemIndex) {
        if (itemIndex < selectedItemIndex) {
            --selectedItemIndex;
        }
        m_listTasks.DeleteItem(itemIndex - removed);
        ++removed;
    };
    std::for_each(itemsToRemove.begin(), itemsToRemove.end(), fn);

    if (!(selectedItemIndex < 0)) {
        SelectTask(selectedItemIndex);
        EnableTaskOperations();
    } else {
        DisableTaskOperations();
    }
}

void CTaskListDialog::SelectTask(int index)
{
    m_listTasks.SetItemState(index, (UINT)(-1), LVIS_FOCUSED | LVIS_SELECTED);
}

void CTaskListDialog::EnableTaskOperations()
{
    int index = m_listTasks.GetSelectionMark();

    CString jobStatusName = m_listTasks.GetItemText(index, 3);
    CString printCountStr = m_listTasks.GetItemText(index, 4);
    CString printedCountStr = m_listTasks.GetItemText(index, 5);
    int printCount = ::atoi(CStringA(printCountStr));
    int printedCount = ::atoi(CStringA(printedCountStr));

    BOOL canSuspend = FALSE;
    BOOL canResume = FALSE;
    BOOL canTerminate = FALSE;
    BOOL canReprioritize = FALSE;
    
    if (jobStatusName == _T("已完成")) {
        ;
    } else if (jobStatusName == _T("正在排队")) {
        canSuspend = canTerminate = canReprioritize = TRUE;
    } else if (jobStatusName == _T("已暂停")) {
        canResume = canTerminate = canReprioritize = TRUE;
    } else if (jobStatusName == _T("出错")) {
        canResume = canTerminate = TRUE;
    } else if (jobStatusName == _T("已终止")) {
        ;
    } else if (jobStatusName == _T("正在打印")) {
        if (printCount - printedCount > 1) {
            canSuspend = canTerminate = TRUE;
        }
    }

    m_btnSuspendJob.EnableWindow(canSuspend);
    m_btnResumeJob.EnableWindow(canResume);
    m_btnTerminateJob.EnableWindow(canTerminate);
    m_chkTerminateNoWait.EnableWindow(canTerminate);
    m_btnAdjustPriority.EnableWindow(canReprioritize);
    GetDlgItem(IDC_TXT_NEW_PRIORITY)->EnableWindow(canReprioritize);
}

void CTaskListDialog::DisableTaskOperations()
{
    m_btnSuspendJob.EnableWindow(FALSE);
    m_btnResumeJob.EnableWindow(FALSE);
    m_btnTerminateJob.EnableWindow(FALSE);
    m_chkTerminateNoWait.EnableWindow(FALSE);
    m_btnAdjustPriority.EnableWindow(FALSE);
    GetDlgItem(IDC_TXT_NEW_PRIORITY)->EnableWindow(FALSE);
}

JobInfo *CTaskListDialog::GetSelectedTask()
{
    int itemIndex = m_listTasks.GetSelectionMark();
    if (itemIndex < 0) {
        return nullptr;
    } else {
        int jobIndex = ::_wtoi(m_listTasks.GetItemText(itemIndex, 0));
        return GetApp().FindJobInfoByIndex(jobIndex);
    }
}

void CTaskListDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_TASKS, m_listTasks);
    DDX_Control(pDX, IDC_BTN_SUSPEND_JOB, m_btnSuspendJob);
    DDX_Control(pDX, IDC_BTN_RESUME_JOB, m_btnResumeJob);
    DDX_Control(pDX, IDC_BTN_TERMINATE_JOB, m_btnTerminateJob);
    DDX_Control(pDX, IDC_BTN_ADJUST_PRIORITY, m_btnAdjustPriority);
    DDX_Text(pDX, IDC_TXT_NEW_PRIORITY, m_newPriority);
    DDX_Control(pDX, IDC_CHK_TERMINATE_NO_WAIT, m_chkTerminateNoWait);
}

BEGIN_MESSAGE_MAP(CTaskListDialog, CDialog)
    ON_BN_CLICKED(IDC_BTN_REFRESH, &CTaskListDialog::OnBnClickedBtnRefresh)
    ON_NOTIFY(NM_CLICK, IDC_LIST_TASKS, &CTaskListDialog::OnNMClickListTasks)
    ON_BN_CLICKED(IDC_BTN_SUSPEND_JOB, &CTaskListDialog::OnBnClickedBtnSuspendJob)
    ON_BN_CLICKED(IDC_BTN_RESUME_JOB, &CTaskListDialog::OnBnClickedBtnResumeJob)
    ON_BN_CLICKED(IDC_BTN_TERMINATE_JOB, &CTaskListDialog::OnBnClickedBtnTerminateJob)
    ON_BN_CLICKED(IDC_BTN_ADJUST_PRIORITY, &CTaskListDialog::OnBnClickedBtnAdjustPriority)
    ON_WM_TIMER()
    ON_EN_CHANGE(IDC_TXT_NEW_PRIORITY, &CTaskListDialog::OnEnChangeTxtNewPriority)
    ON_BN_CLICKED(IDC_BTN_REMOVE_FINISHED_JOBS, &CTaskListDialog::OnBnClickedBtnRemoveFinishedJobs)
    ON_BN_CLICKED(IDC_BTN_REMOVE_ALL_JOBS, &CTaskListDialog::OnBnClickedBtnRemoveAllJobs)
END_MESSAGE_MAP()

void CTaskListDialog::OnBnClickedBtnRefresh()
{
    RefreshTasks();
}

void CTaskListDialog::OnNMClickListTasks(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE activationInfo = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (activationInfo->iItem < 0) {
        DisableTaskOperations();
    } else {
        EnableTaskOperations();
    }
    *pResult = 0;
}

void CTaskListDialog::OnBnClickedBtnSuspendJob()
{
    //JobInfo *info = GetSelectedTask();
    //bool success = false;
    //while (info) {
    //    if (0 != ::DASSetNetworkParams(
    //        (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //        GetApp().GetServer().GetPort()))
    //        break;

    //    if (0 == ::DASSuspendJob((LPSTR)(LPCSTR)info->uuid))
    //        success = true;

    //    break;
    //}

    //if (success) {
    //    info->jobStatus = JS_SUSPENDED;
    //    MessageBox(_T("暂停任务成功。"));
    //} else {
    //    MessageBox(_T("暂停任务失败！"));
    //}

    //RefreshTasks();
}

void CTaskListDialog::OnBnClickedBtnResumeJob()
{
    //JobInfo *info = GetSelectedTask();
    //bool success = false;
    //while (info) {
    //    if (0 != ::DASSetNetworkParams(
    //        (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //        GetApp().GetServer().GetPort()))
    //        break;

    //    if (0 == ::DASResumeJob((LPSTR)(LPCSTR)info->uuid))
    //        success = true;

    //    break;
    //}

    //if (success) {
    //    info->jobStatus = JS_WAITING;
    //    MessageBox(_T("恢复任务成功。"));
    //} else {
    //    MessageBox(_T("恢复任务失败！"));
    //}

    //RefreshTasks();
}

void CTaskListDialog::OnBnClickedBtnTerminateJob()
{
    //JobInfo *info = GetSelectedTask();
    //bool success = false;
    //while (info) {
    //    if (0 != ::DASSetNetworkParams(
    //        (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //        GetApp().GetServer().GetPort()))
    //        break;

    //    int noWait = (m_chkTerminateNoWait.GetCheck() == BST_CHECKED ? 1 : 0);

    //    if (0 == ::DASCancelJob((LPSTR)(LPCSTR)info->uuid, noWait))
    //        success = true;

    //    break;
    //}

    //if (success) {
    //    info->jobStatus = JS_TERMINATED;
    //    MessageBox(_T("终止任务成功。"));
    //} else {
    //    MessageBox(_T("终止任务失败！"));
    //}

    //RefreshTasks();
}

void CTaskListDialog::OnBnClickedBtnAdjustPriority()
{
    //if (m_newPriority > 10) {
    //    MessageBox(_T("优先级应在 0 到 10 之间"));
    //    HWND txtWnd;
    //    GetDlgItem(IDC_TXT_NEW_PRIORITY, &txtWnd);
    //    ::SetFocus(txtWnd);
    //    return;
    //}

    //JobInfo *info = GetSelectedTask();
    //bool success = false;
    //while (info) {
    //    if (0 != ::DASSetNetworkParams(
    //        (LPSTR)(LPCSTR)GetApp().GetServer().GetIp(),
    //        GetApp().GetServer().GetPort()))
    //        break;

    //    if (0 == ::DASUpdateJob(
    //        (LPSTR)(LPCSTR)info->uuid, m_newPriority))
    //        success = true;

    //    break;
    //}

    //if (success) {
    //    info->priority = m_newPriority;
    //    MessageBox(_T("更新任务优先级成功。"));
    //} else {
    //    MessageBox(_T("更新任务优先级失败！"));
    //}

    //RefreshTasks();
}

void CTaskListDialog::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == REFRESH_TIMER_ID) {
        RefreshTasks();
    } else {
        CDialog::OnTimer(nIDEvent);
    }
}


void CTaskListDialog::OnEnChangeTxtNewPriority()
{
    UpdateData(TRUE);
}

void CTaskListDialog::OnBnClickedBtnRemoveFinishedJobs()
{
    GetApp().RemoveFinishedJobs();
    RefreshTasks();
}


void CTaskListDialog::OnBnClickedBtnRemoveAllJobs()
{
    GetApp().RemoveAllJobs();
    RefreshTasks();
}
