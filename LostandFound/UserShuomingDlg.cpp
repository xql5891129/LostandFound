// UserShuomingDlg.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "UserShuomingDlg.h"
#include "afxdialogex.h"

CFont m_edit;
// UserShuomingDlg 对话框

IMPLEMENT_DYNAMIC(UserShuomingDlg, CDialogEx)

UserShuomingDlg::UserShuomingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_usershuoming_DIALOG2, pParent)
{

}

UserShuomingDlg::~UserShuomingDlg()
{
}

void UserShuomingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_static1);
}


BEGIN_MESSAGE_MAP(UserShuomingDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &UserShuomingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// UserShuomingDlg 消息处理程序


BOOL UserShuomingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_edit.CreatePointFont(200, _T("楷体"), NULL);
	m_static1.SetFont(&m_edit, true);
	m_static1.SetWindowText(_T("本系统可提供给用户查询浏览系统上传的拾取物品的相关信息，以及领取属于自己打的丢失物品。用户需在首页点击用户入口进入用户登录界面，登录或者注册后登录，再进入用户专区界面—>可进行查询、浏览以及领取相关物品。"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void UserShuomingDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
