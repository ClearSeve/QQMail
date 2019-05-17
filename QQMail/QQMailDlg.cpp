// QQMailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQMail.h"
#include "QQMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int m_nData1;
int m_nData2;

CProgressCtrl m_wndProgress;
BOOL g_Bdata;
CButton m_wndStatr;
CButton m_wndEnd;
int data1;
int data2;
HANDLE Main;//线程句柄
DWORD nThreadID;//线程ID
FILE* File;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
   
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CQQMailDlg 对话框




CQQMailDlg::CQQMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQQMailDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
}

void CQQMailDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_wndEdit1);
    DDX_Control(pDX, IDC_EDIT2, m_wndEdit2);
    DDX_Control(pDX, IDC_BEHIND, m_wndBehind);
    DDX_Control(pDX, IDC_PROGRESS1, m_wndProgress);
    DDX_Control(pDX, IDC_START, m_wndStatr);
    DDX_Control(pDX, IDC_END, m_wndEnd);
    DDX_Text(pDX, IDC_EDIT1, data1);
    DDX_Text(pDX, IDC_EDIT2, data2);
}

BEGIN_MESSAGE_MAP(CQQMailDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_START, &CQQMailDlg::OnBnClickedStart)
    ON_BN_CLICKED(IDC_END, &CQQMailDlg::OnBnClickedEnd)
    ON_EN_CHANGE(IDC_EDIT2, &CQQMailDlg::OnEnChangeEdit2)
    ON_EN_CHANGE(IDC_EDIT1, &CQQMailDlg::OnEnChangeEdit1)
    ON_EN_UPDATE(IDC_EDIT1, &CQQMailDlg::OnEnUpdateEdit1)
END_MESSAGE_MAP()


// CQQMailDlg 消息处理程序

BOOL CQQMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    m_wndEnd.EnableWindow(FALSE);
    CString str1,str2;
    int nData1 = 10001;
    int nData2 = 1000000000;
    
    str1.Format(_T("%d"),nData1);
    str2.Format(_T("%d"),nData2);
    m_wndEdit2.SetWindowText(str2);
    m_wndEdit1.SetWindowText(str1);
    m_wndBehind.SetCheck(TRUE);
    
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQMailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CQQMailDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQQMailDlg::OnBnClickedStart()
{
      //m_bData=FALSE;
      m_wndEnd.EnableWindow(TRUE);
      m_wndStatr.EnableWindow(FALSE);
      m_wndBehind.EnableWindow(FALSE);
      m_wndEdit1.EnableWindow(FALSE);
      m_wndEdit2.EnableWindow(FALSE);

      UpdateWindow();

	  g_Bdata = m_wndBehind.GetCheck();

      //开始线程
      Main = CreateThread(NULL,0,::ThreadProc,NULL,0,&nThreadID);//创建一个立刻执行的线程

}

void CQQMailDlg::OnBnClickedEnd()
{
    //m_bData=FALSE;
    m_wndStatr.EnableWindow(TRUE);
    m_wndEnd.EnableWindow(FALSE);
    m_wndBehind.EnableWindow(TRUE);
    m_wndEdit1.EnableWindow(TRUE);
    m_wndEdit2.EnableWindow(TRUE);
    //结束线程
    TerminateThread(Main,0);
    fclose(File);//关闭文件是    
}

void CQQMailDlg::OnEnChangeEdit2()
{
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CDialog::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。
    // TODO:  在此添加控件通知处理程序代码
    int data = data2;
    UpdateData();
    if (data1>data2)
    {
        AfxMessageBox(_T("您不能输入比开始还小的数字!"));
        CString str;
        str.Format(_T("%d"),data);
        m_wndEdit2.SetWindowText(str);
        
    }
    //if(m_nData1==m_nData2)
    //{
    //    AfxMessageBox(_T("您不能输入开始与结束相等的数字!"));
    //    CString str;
    //    str.Format(_T("%d"),data);
    //    m_wndEdit2.SetWindowText(str);
    //}
}

void CQQMailDlg::OnEnChangeEdit1()
{
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CDialog::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
    int data = data1;
    UpdateData();
    if (data2<data1)
    {
        AfxMessageBox(_T("您不能输入比结束还大的数字!"));
        CString str;
        str.Format(_T("%d"),data);
        m_wndEdit1.SetWindowText(str);
    }

    //if(m_nData1==m_nData2)
    //{
    //    AfxMessageBox(_T("您不等输入开始与结束相等的数字"));
    //    CString str;
    //    str.Format(_T("%d"),data);
    //    m_wndEdit1.SetWindowText(str);

    //}
}

void CQQMailDlg::OnEnUpdateEdit1()
{
    // TODO:  如果该控件是 RICHEDIT 控件，则它将不会
    // 发送该通知，除非重写 CDialog::OnInitDialog()
    // 函数，将 EM_SETEVENTMASK 消息发送到控件，
    // 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

    // TODO:  在此添加控件通知处理程序代码
}
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{

    int data = data1;
    m_wndProgress.SetRange(data1,data2);
    CString str;
    
    WCHAR szCurrent[MAX_PATH] = {0};//获取路径变量
    ::GetCurrentDirectory( MAX_PATH, szCurrent );//获取路径
    CString strPath;//全路径字符串
    strPath.Format(_T("%s\\QQData.txt"),szCurrent);

    WCHAR path[MAX_PATH] = {0};
    wsprintf(path, _T("%s\\QQData.txt"), szCurrent);
    File = _wfopen(path,_T("w+"));//打开文件
    if (File == NULL)
    {
        AfxMessageBox(_T("打开文件失败"));
        return -1;
    }
    if (g_Bdata==TRUE)
    {
        while (data!=data2)
        {
			CStringA strTmp;
			strTmp.Format("%d@qq.com\n", data);
            m_wndProgress.SetStep(1);
			fprintf(File, strTmp.GetBuffer());
            data++;
        }
    }else
    {
        while (data!=data2)
        {
			CStringA strTmp;
			strTmp.Format("%d\n", data);
            m_wndProgress.SetStep(1);
			fprintf(File, strTmp.GetBuffer());
            data++;
        }
    }
    m_wndEnd.EnableWindow(FALSE);
    m_wndStatr.EnableWindow(TRUE);
    AfxMessageBox(_T("完成!"));
    fclose(File);
    return 0;
}