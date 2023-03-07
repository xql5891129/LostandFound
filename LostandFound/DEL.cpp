// DEL.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "DEL.h"
#include "afxdialogex.h"
#include"LostandFoundDlg.h"
#include"ADMIN.h"


// DEL 对话框

IMPLEMENT_DYNAMIC(DEL, CDialogEx)

DEL::DEL(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Delete_DIALOG, pParent)
	, reason(_T(""))
	, de_name(_T(""))
	, de_manname(_T(""))
{

}

DEL::~DEL()
{
}

void DEL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, reason);
	DDX_Text(pDX, IDC_EDIT1, de_name);
	DDX_Text(pDX, IDC_EDIT2, de_manname);
}


BEGIN_MESSAGE_MAP(DEL, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &DEL::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &DEL::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// DEL 消息处理程序


void DEL::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	DEL::OnOK();
}


void DEL::OnBnClickedOk()
{
	CADOConnect aq;
	CString sql1,sql2;
	_bstr_t Sql1,Sql2;
	UpdateData(true);
	if (de_manname == "" || de_name == "" || reason == "")
	{
		MessageBox(_T("所有内容不能为空！请检查！"), _T("错误"));
		return;
	}
	sql1.Format(_T("delete from Pick where Pick_name='%s' and Pname='%s'"), de_name, de_manname);
	Sql1 = (_bstr_t)sql1;
	if (aq.ExecuteSQL(Sql1))
	{
		sql2.Format(_T("insert into ADelete(Delete_name,Delete_manname,Delete_reason) values('%s','%s','%s')"), de_name, de_manname, reason);
		Sql2 = (_bstr_t)sql2;
		if(aq.ExecuteSQL(Sql2))
		MessageBox(_T("删除成功！"), _T("提示"));
	}
	else
		MessageBox(_T("删除失败！"), _T("提示"));
	// TODO: 在此添加控件通知处理程序代码
	
}


BOOL DEL::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rush4.CreateSolidBrush(RGB(213, 251, 201));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH DEL::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_rush4;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 251, 201));//设置背景颜色
		hbr = (HBRUSH)m_rush4;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
