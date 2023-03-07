// Administrators_Manual.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "Administrators_Manual.h"
#include "afxdialogex.h"

CFont m_edit1;
// Administrators_Manual 对话框

IMPLEMENT_DYNAMIC(Administrators_Manual, CDialogEx)

Administrators_Manual::Administrators_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Administrator_DIALOG2, pParent)
{

}

Administrators_Manual::~Administrators_Manual()
{
}

void Administrators_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_static2);
}


BEGIN_MESSAGE_MAP(Administrators_Manual, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Administrators_Manual::OnBnClickedCancel)
END_MESSAGE_MAP()


// Administrators_Manual 消息处理程序


BOOL Administrators_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_edit1.CreatePointFont(200, _T("楷体"), NULL);
	m_static2.SetFont(&m_edit1, true);
	m_static2.SetWindowText(_T("本系统可提供给管理员添加、修改、删除拾取物品的相关信息。管理员需在首页点击管理员入口进入用户登录界面，进行登录，再进入管理员专区界面—>就可进行相关操作。"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Administrators_Manual::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
