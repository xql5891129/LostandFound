// ADD.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "ADD.h"
#include "afxdialogex.h"
#include"LostandFoundDlg.h"


// ADD 对话框
DLinklist h, p, s;
IMPLEMENT_DYNAMIC(ADD, CDialogEx)

ADD::ADD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Add_DIALOG, pParent)
	, Pick_manname(_T(""))
	, Pick_phone(_T(""))
	, Pick_name(_T(""))
	, Pick_place(_T(""))
	, Pick_tiame(_T(""))
{

}
BOOL ADD::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rush3.CreateSolidBrush(RGB(213, 251, 201));
	h = init(h);
	p = h;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

ADD::~ADD()
{
}

void ADD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, Pick_manname);
	DDX_Text(pDX, IDC_EDIT5, Pick_phone);
	DDX_Text(pDX, IDC_EDIT1, Pick_name);
	DDX_Text(pDX, IDC_EDIT2, Pick_place);
	DDX_Text(pDX, IDC_EDIT3, Pick_tiame);
}


BEGIN_MESSAGE_MAP(ADD, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &ADD::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &ADD::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ADD 消息处理程序


void ADD::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	ADD::OnOK();
}

void ADD::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	USES_CONVERSION;
	LPSTR str;
	UpdateData(true);
	s = (Node*)malloc(sizeof(Node));
	str = T2A(Pick_name);
	strcpy_s(s->pick_name, str);
	str = T2A(Pick_place);
	strcpy_s(s->pick_place, str);
	str = T2A(Pick_tiame);
	strcpy_s(s->pick_time, str);
	str = T2A(Pick_manname);
	strcpy_s(s->pick_manname, str);
	str = T2A(Pick_phone);
	strcpy_s(s->pick_phone, str);
	/*p->next = s;
	s->prior = p;
	p = s;
	p->next = NULL;*/

	
	
		CString sql;
		CADOConnect adq;
			sql.Format(_T("insert into Pick(Pick_name,Pick_time,Pick_place,Pname,Pphone) values('%s','%s','%s','%s','%s')"), Pick_name, Pick_tiame, Pick_place, Pick_manname, Pick_phone);
			_bstr_t Sql;
			Sql = (_bstr_t)sql;
			if(!adq.ExecuteSQL(Sql))
			AfxMessageBox(_T("入库失败"));
			else
				AfxMessageBox(_T("入库成功"));
		
		free(s);


}




HBRUSH ADD::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_rush3;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 251, 201));//设置背景颜色
		hbr = (HBRUSH)m_rush3;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
