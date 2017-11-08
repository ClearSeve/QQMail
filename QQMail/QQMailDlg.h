// QQMailDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CQQMailDlg �Ի���
class CQQMailDlg : public CDialog
{
// ����
public:
	CQQMailDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQMAIL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
    

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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