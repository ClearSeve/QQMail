// QQMailDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CQQMailDlg 对话框
class CQQMailDlg : public CDialog
{
// 构造
public:
	CQQMailDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQMAIL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
    

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CEdit m_wndEdit1;
public:
    CEdit m_wndEdit2;
public:
    CButton m_wndBehind;
public:
    
public:

   
public:
    afx_msg void OnBnClickedStart();
public:
    afx_msg void OnBnClickedEnd();
public:

public:
    afx_msg void OnEnChangeEdit2();
public:
    afx_msg void OnEnChangeEdit1();
public:
    afx_msg void OnEnUpdateEdit1();
};
DWORD WINAPI ThreadProc(LPVOID lpParameter);