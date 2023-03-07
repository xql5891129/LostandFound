// LOGIN.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "LOGIN.h"
#include "afxdialogex.h"
#include"ADMIN.h"
#include"stdafx.h"
#include"LostandFoundDlg.h"

// LOGIN 对话框
CADOConnect ad;
IMPLEMENT_DYNAMIC(LOGIN, CDialogEx)

LOGIN::LOGIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Login_DIALOG, pParent)
	, passwords(_T(""))
	, userName(_T(""))
{

}

LOGIN::~LOGIN()
{
}

void LOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, userName);
	DDX_Text(pDX, IDC_EDIT2, passwords);
}


BEGIN_MESSAGE_MAP(LOGIN, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &LOGIN::OnBnClickedCheck1)
	ON_BN_CLICKED(IDOK, &LOGIN::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &LOGIN::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// LOGIN 消息处理程序


void LOGIN::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_CHECK1) == BST_CHECKED)
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
		pEdit->SetPasswordChar(0);
		SetDlgItemText(IDC_EDIT2, passwords);
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		CEdit* pEdit = (CEdit*)(this)->GetDlgItem(IDC_EDIT2);
		pEdit->SetPasswordChar('*');
		SetDlgItemText(IDC_EDIT2, passwords);
		UpdateData(false);
	}
	GetDlgItem(IDC_EDIT2)->SetFocus();
}


void LOGIN::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	static int k = 6;
	CString str;
	UpdateData(true);
	if (userName.IsEmpty())
	{
		MessageBox(_T("用户名不能为空！"), _T("登陆错误"));
		GetDlgItem(IDC_EDIT1)->SetFocus();
		return;
	}
	if (passwords.IsEmpty())
	{
		MessageBox(_T("用户密码不能为空！"), _T("登陆错误"));
		GetDlgItem(IDC_EDIT2)->SetFocus();
		return;
	}
	CString sql;
	sql.Format(_T("select* from Administrator where Adnumber='%s' and Adpassword='%s'"),userName,passwords);
	_bstr_t Sql;
	Sql = (_bstr_t)sql;
	
	
	
		_RecordsetPtr m_recordset;
		try
		{
			m_recordset = ad.GetRecordSet(Sql);  //执行查询，获取记录集
			CString str1, str2;
			str1 = (LPCSTR)(_bstr_t)(m_recordset->GetCollect("Adnumber")); //获取管理员账户，密码
			str2 = (LPCSTR)(_bstr_t)(m_recordset->GetCollect("Adpassword"));

			//删除字符串右空格
			str1.TrimRight();
			str2.TrimRight();
			
			if (str1 == userName && str2 == passwords)
			{
				
					m_recordset->Close();
					LOGIN::OnOK();
					ADMIN admin;
					admin.DoModal();
				
			}
			else
			{
				k--;
				str.Format(_T("%d"), k);
				if (k == 0)
				{
					m_recordset->Close();
					MessageBox(_T("已经连续输入六次错误账户或密码！请下次再试"), _T("登录错误"));
					exit(0);
				}
				int m = MessageBox(_T("账号或密码错误，请检查！你还有") + str + _T("次机会，是否重新登录"), _T("登陆错误"), MB_YESNO);
				if (m == IDNO)
				{
					m_recordset->Close();
					LOGIN::OnOK();
				}
				else
				{
					m_recordset->Close();
					GetDlgItem(IDC_EDIT1)->SetFocus();
				}
			}
		}
		catch(...)
		{
			
			k--;
			str.Format(_T("%d"), k);
			if (k == 0)
			{
				MessageBox(_T("已经连续输入三次错误账户或密码！请下次再试"), _T("登录错误"));
				exit(0);
			}
			int m=MessageBox(_T("账号或密码错误，请检查！你还有") + str + _T("次机会，是否重新登录"), _T("登陆错误"),MB_YESNO);
				if (m == IDNO)
					LOGIN::OnOK();
				else
				{
					m_recordset->Close();
					GetDlgItem(IDC_EDIT1)->SetFocus();
				}
					
			
		}
		
}


void LOGIN::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	LOGIN::OnOK();
}


BOOL LOGIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_brush1.CreateSolidBrush(RGB(219, 238, 249));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH LOGIN::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_brush1;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0, 180, 0));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_brush1;

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_brush1;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
