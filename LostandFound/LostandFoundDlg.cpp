
// LostandFoundDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LostandFound.h"
#include "LostandFoundDlg.h"
#include "afxdialogex.h"
#include"LOGIN.h"
#include"USER.h"
#include"stdafx.h"
#include"UserLogin.h"
#include"Administrators_Manual.h"
#include"UserShuomingDlg.h"
//#include "ADOConnect.h"

CFont m_editFont,m_buttonFont1, m_buttonFont2;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CADOConnect adoConn;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLostandFoundDlg 对话框



CLostandFoundDlg::CLostandFoundDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOSTANDFOUND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLostandFoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_static);
	DDX_Control(pDX, IDC_BUTTON3, m_Static);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
}

BEGIN_MESSAGE_MAP(CLostandFoundDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CLostandFoundDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CLostandFoundDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CLostandFoundDlg::OnBnClickedButton3)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	
	ON_COMMAND(ID_user, &CLostandFoundDlg::Onuser)
	ON_COMMAND(ID_adminitrators, &CLostandFoundDlg::Onadminitrators)
END_MESSAGE_MAP()


// CLostandFoundDlg 消息处理程序
/*HBRUSH CLostandFoundDlg::OnCtlColor(CDC*pDC,CWnd*pWnd,UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd==this)
	{
		return m_bkBrush;
	}
	return hbr;
}*/

BOOL CLostandFoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		 //设置静态文本字体大小
	m_editFont.CreatePointFont(230, _T("楷体"),NULL);
	m_Static.SetFont(&m_editFont,true);
	m_Static.SetWindowText(_T("失物招领系统"));
	m_buttonFont1.CreatePointFont(50, _T("楷体"), NULL);
	m_static.SetFont(&m_editFont, true);
	m_buttonFont2.CreatePointFont(50, _T("楷体"), NULL);
	m_button2.SetFont(&m_editFont, true);
	//m_static.SetFaceColor(RGB(213, 241, 251), true);
	//m_button2.SetFaceColor(RGB(200, 120, 251), true);
	m_Brush.CreateSolidBrush(RGB(219, 238, 249));

	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	SetMenu(&menu);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLostandFoundDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLostandFoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CLostandFoundDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	LOGIN login;
	login.DoModal();
}


void CLostandFoundDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UserLogin User;
	User.DoModal();
}


void CLostandFoundDlg::OnBnClickedButton3()
{
	CString sql;
	sql = "INSERT INTO Administrator VALUES('202107','777777')";
	adoConn.OnInitDBConnect();  //连接数据库
	_bstr_t Sql;
	Sql = (_bstr_t)sql;
	if (!adoConn.ExecuteSQL(Sql))
		AfxMessageBox(_T("添加失败！"));
	else
		AfxMessageBox(_T("添加成功！"));
	
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CLostandFoundDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor==CTLCOLOR_DLG)// 选择对话框    
	{
		return m_Brush; 
	}
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr= (HBRUSH)m_Brush;
	}
	if(pWnd->GetDlgCtrlID()== IDC_BUTTON1)
	{
		pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_Brush;
	}
	return hbr;
}









void CLostandFoundDlg::Onuser()
{
	UserShuomingDlg ud;
	ud.DoModal();
	// TODO: 在此添加命令处理程序代码
}


void CLostandFoundDlg::Onadminitrators()
{
	Administrators_Manual Ad;
	Ad.DoModal();
	// TODO: 在此添加命令处理程序代码
}
