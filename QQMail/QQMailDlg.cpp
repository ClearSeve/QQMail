// QQMailDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQMail.h"
#include "QQMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
int m_nData1;
int m_nData2;

CProgressCtrl m_wndProgress;
BOOL g_Bdata;
CButton m_wndStatr;
CButton m_wndEnd;
int data1;
int data2;
HANDLE Main;//�߳̾��
DWORD nThreadID;//�߳�ID
FILE* File;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CQQMailDlg �Ի���




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


// CQQMailDlg ��Ϣ�������

BOOL CQQMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_wndEnd.EnableWindow(FALSE);
    CString str1,str2;
    int nData1 = 10001;
    int nData2 = 1000000000;
    
    str1.Format(_T("%d"),nData1);
    str2.Format(_T("%d"),nData2);
    m_wndEdit2.SetWindowText(str2);
    m_wndEdit1.SetWindowText(str1);
    m_wndBehind.SetCheck(TRUE);
    
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQQMailDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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

      //��ʼ�߳�
      Main = CreateThread(NULL,0,::ThreadProc,NULL,0,&nThreadID);//����һ������ִ�е��߳�

}

void CQQMailDlg::OnBnClickedEnd()
{
    //m_bData=FALSE;
    m_wndStatr.EnableWindow(TRUE);
    m_wndEnd.EnableWindow(FALSE);
    m_wndBehind.EnableWindow(TRUE);
    m_wndEdit1.EnableWindow(TRUE);
    m_wndEdit2.EnableWindow(TRUE);
    //�����߳�
    TerminateThread(Main,0);
    fclose(File);//�ر��ļ���    
}

void CQQMailDlg::OnEnChangeEdit2()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CDialog::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int data = data2;
    UpdateData();
    if (data1>data2)
    {
        AfxMessageBox(_T("����������ȿ�ʼ��С������!"));
        CString str;
        str.Format(_T("%d"),data);
        m_wndEdit2.SetWindowText(str);
        
    }
    //if(m_nData1==m_nData2)
    //{
    //    AfxMessageBox(_T("���������뿪ʼ�������ȵ�����!"));
    //    CString str;
    //    str.Format(_T("%d"),data);
    //    m_wndEdit2.SetWindowText(str);
    //}
}

void CQQMailDlg::OnEnChangeEdit1()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CDialog::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int data = data1;
    UpdateData();
    if (data2<data1)
    {
        AfxMessageBox(_T("����������Ƚ������������!"));
        CString str;
        str.Format(_T("%d"),data);
        m_wndEdit1.SetWindowText(str);
    }

    //if(m_nData1==m_nData2)
    //{
    //    AfxMessageBox(_T("���������뿪ʼ�������ȵ�����"));
    //    CString str;
    //    str.Format(_T("%d"),data);
    //    m_wndEdit1.SetWindowText(str);

    //}
}

void CQQMailDlg::OnEnUpdateEdit1()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
    // ���͸�֪ͨ��������д CDialog::OnInitDialog()
    // �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
    // ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{

    int data = data1;
    m_wndProgress.SetRange(data1,data2);
    CString str;
    
    WCHAR szCurrent[MAX_PATH] = {0};//��ȡ·������
    ::GetCurrentDirectory( MAX_PATH, szCurrent );//��ȡ·��
    CString strPath;//ȫ·���ַ���
    strPath.Format(_T("%s\\QQData.txt"),szCurrent);

    WCHAR path[MAX_PATH] = {0};
    wsprintf(path, _T("%s\\QQData.txt"), szCurrent);
    File = _wfopen(path,_T("w+"));//���ļ�
    if (File == NULL)
    {
        AfxMessageBox(_T("���ļ�ʧ��"));
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
    AfxMessageBox(_T("���!"));
    fclose(File);
    return 0;
}