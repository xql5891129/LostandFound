// UserLogin.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "UserLogin.h"
#include "afxdialogex.h"
#include"LostandFoundDlg.h"
#include"USER.h"
#include"UserRegister.h"
// UserLogin 对话框
CADOConnect adc;
IMPLEMENT_DYNAMIC(UserLogin, CDialogEx)

UserLogin::UserLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, Username(_T(""))
	, Userpassword(_T(""))
{

}

UserLogin::~UserLogin()
{
}

void UserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Username);
	DDX_Text(pDX, IDC_EDIT3, Userpassword);
}


BEGIN_MESSAGE_MAP(UserLogin, CDialogEx)
	
	ON_BN_CLICKED(IDC_CHECK1, &UserLogin::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &UserLogin::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &UserLogin::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &UserLogin::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// UserLogin 消息处理程序




void UserLogin::OnBnClickedCheck1()   //显示密码
{
	if (IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT3);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT3, Userpassword);
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT3);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT3, Userpassword);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT3)->SetFocus();// TODO: 在此添加控件通知处理程序代码
}


void UserLogin::OnBnClickedButton2()  //用户登录
{
	static int k = 10;
	CString str;
	UpdateData(true);
	if (Username.IsEmpty())
	{
		MessageBox(_T("用户名不能为空！"), _T("登陆错误"));
		GetDlgItem(IDC_EDIT2)->SetFocus();
		return;
	}
	if (Userpassword.IsEmpty())
	{
		MessageBox(_T("用户密码不能为空！"), _T("登陆错误"));
		GetDlgItem(IDC_EDIT3)->SetFocus();
		return;
	}
	CString sql;
	sql.Format(_T("select* from Users where Username='%s' and Password='%s'"), Username, Userpassword);
	_bstr_t Sql;
	Sql = (_bstr_t)sql;



	_RecordsetPtr m_recordset;
	try
	{
		m_recordset = adc.GetRecordSet(Sql);  //执行查询，获取记录集
		CString str1, str2;
		str1 = (LPCSTR)(_bstr_t)(m_recordset->GetCollect("Username")); //获取管理员账户，密码
		str2 = (LPCSTR)(_bstr_t)(m_recordset->GetCollect("Password"));

		//删除字符串右空格
		str1.TrimRight();
		str2.TrimRight();

		if (str1 == Username || str2 == Userpassword)
		{

			m_recordset->Close();
			UserLogin::OnOK();
			USER user;
			user.DoModal();

		}
		else
		{
			k--;
			str.Format(_T("%d"), k);
			if (k == 0)
			{
				m_recordset->Close();
				MessageBox(_T("已经连续输入十次错误账户或密码！请下次再试"), _T("登录错误"));
				exit(0);
			}
			int m = MessageBox(_T("账号或密码错误，请检查！你还有") + str + _T("次机会，是否重新登录"), _T("登陆错误"), MB_YESNO);
			if (m == IDNO)
			{
				m_recordset->Close();
				UserLogin::OnOK();
			}
			else
			{
				m_recordset->Close();
				GetDlgItem(IDC_EDIT2)->SetFocus();
			}
		}
	}
	catch (...)
	{

		k--;
		str.Format(_T("%d"), k);
		if (k == 0)
		{
			MessageBox(_T("已经连续输入十次错误账户或密码！请下次再试"), _T("登录错误"));
			exit(0);
		}
		int m = MessageBox(_T("账号或密码错误，请检查！你还有") + str + _T("次机会，是否重新登录"), _T("登陆错误"), MB_YESNO);
		if (m == IDNO)
			UserLogin::OnOK();
		else
		{
			m_recordset->Close();
			GetDlgItem(IDC_EDIT2)->SetFocus();
		}


	}

}

	// TODO: 在此添加控件通知处理程序代码



void UserLogin::OnBnClickedCancel()  //退出用户登录页面
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



void UserLogin::OnBnClickedButton1()     //进入用户登录页面
{
	UserRegister reg;
	reg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}





BOOL UserLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rush1.CreateSolidBrush(RGB(219, 238, 249));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH UserLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_rush1;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0, 180, 0));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_rush1;

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_rush1;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
