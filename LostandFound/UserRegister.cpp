// UserRegister.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "UserRegister.h"
#include "afxdialogex.h"
#include"LostandFoundDlg.h"
#include"stdafx.h"
#include<regex>
// UserRegister 对话框

IMPLEMENT_DYNAMIC(UserRegister, CDialogEx)

UserRegister::UserRegister(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Register_DIALOG, pParent)
	, User_name(_T(""))
	, User_password(_T(""))
	, User_realname(_T(""))
	, User_E_mail(_T(""))
	, User_telephone(_T(""))
{

}

UserRegister::~UserRegister()
{
}

void UserRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, User_name);
	DDX_Text(pDX, IDC_EDIT2, User_password);
	DDX_Text(pDX, IDC_EDIT3, User_realname);
	DDX_Text(pDX, IDC_EDIT4, User_E_mail);
	DDX_Control(pDX, IDC_EDIT6, User_phone);
	DDX_Text(pDX, IDC_EDIT6, User_telephone);
}


BEGIN_MESSAGE_MAP(UserRegister, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &UserRegister::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &UserRegister::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// UserRegister 消息处理程序


void UserRegister::OnBnClickedButton1()
{
	CString sql, str;
	CADOConnect ado;
	_bstr_t Sql,fSql,FSql;
	UpdateData(true);
	if (User_name=="" || User_password=="" || User_realname=="" || User_E_mail=="" || User_telephone=="")
		MessageBox(_T("请输入完整注册信息！"), _T("提示"));
	
	else
	{
		int nlen = User_realname.GetLength();
		int flag = 0;           //设置标志，初始化0
		unsigned char ch1,ch2;
		for(int i=0;i<2*nlen;i+=2)
		{
			ch1 = User_realname[i];   
			ch2 = User_realname[i + 1];//逐个字符检查是否都为汉字
			if (ch1 >= 0xB0 && ch2>=0xA1)
				continue;
			else
			{
				flag = 1;       //存在不为汉字的退出，标志置1
				break;
			}
		}
	
		if (User_name.GetLength() >=6 && User_name.GetLength() <= 10 && User_password.GetLength()>=6 && User_password.GetLength() <=10 && User_telephone.GetLength()==11 && User_telephone.SpanIncluding(_T("0123456789")) && flag == 1)
		{
			CString fsql1,fsql2;
			fsql1.Format(_T("select* from Users where Username='%s'"), User_name);
			fsql2.Format(_T("select* from Users where Phone='%s'"), User_telephone);
			fSql = (_bstr_t)fsql1;
			FSql= (_bstr_t)fsql2;
			if(ado.ExecuteSQL(fSql))
			{
				AfxMessageBox(_T("该用户名账号已存在！请检查！"));
				return;
			}
			if (ado.ExecuteSQL(FSql))
			{
				AfxMessageBox(_T("该联系电话已存在！请检查！"));
				return;
			}
			sql.Format(_T("insert into Users values('%s','%s','%s','%s','%s')"), User_name, User_password, User_realname, User_E_mail, User_telephone);
			Sql = (_bstr_t)sql;
			if (!ado.ExecuteSQL(Sql))
				AfxMessageBox(_T("数据库异常！注册失败"));
			else
			{
				int k = MessageBox(_T("注册成功！是否返回登录"), _T("提示"), MB_YESNO);
				if (k == IDYES)
					CDialogEx::OnCancel();
			}
		}
		else
			MessageBox(_T("注册用户名和密码需在6-10位，电话号码为11位有效数字数字,真实姓名需全为中文字符！请仔细检查！"), _T("提示"));
		
	}
	// TODO: 在此添加控件通知处理程序代码
}


void UserRegister::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL UserRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rush2.CreateSolidBrush(RGB(219, 238, 249));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH UserRegister::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_rush2;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0, 180, 0));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_rush2;

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_rush2;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
