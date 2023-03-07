// ADMIN.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "ADMIN.h"
#include "afxdialogex.h"
#include"ADD.h"
#include"DEL.h"
#include"LostandFoundDlg.h"



// ADMIN 对话框
CADOConnect adp;
IMPLEMENT_DYNAMIC(ADMIN, CDialogEx)
CADOConnect adz;
struct DATA
{
	int subitem;//存放点击的列
	CListCtrl* plist;
};
int sort_column;//记录点击的列
static bool method = false;;//记录比较方法
ADMIN::ADMIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Admin_DIALOG, pParent)
	, m_pickname(_T(""))
	, m_pname(_T(""))
	, m_picktime(_T(""))
	, m_pickplace(_T(""))
{

}

ADMIN::~ADMIN()
{
}

void ADMIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_pickname);
	DDX_Text(pDX, IDC_EDIT4, m_pname);
	DDX_Text(pDX, IDC_EDIT2, m_picktime);
	DDX_Text(pDX, IDC_EDIT3, m_pickplace);
	DDX_Control(pDX, IDC_LIST2, m_list1);
	DDX_Control(pDX, IDC_P1_STATIC, m_image2);
}


BEGIN_MESSAGE_MAP(ADMIN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ADMIN::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ADMIN::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ADMIN::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ADMIN::OnBnClickedButton4)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &ADMIN::OnNMClickList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, &ADMIN::OnLvnColumnclickList2)
	ON_BN_CLICKED(IDC_BUTTON5, &ADMIN::OnBnClickedButton5)
END_MESSAGE_MAP()
BOOL ADMIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_rush.CreateSolidBrush(RGB(219, 238, 249));
	// TODO:  在此添加额外的初始化
	LONG lStyle;
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST2);
	lStyle = GetWindowLong(list->m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(list->m_hWnd, GWL_STYLE, lStyle);
	DWORD dwStyle = list->GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	list->SetExtendedStyle(dwStyle);
	list->InsertColumn(1, _T("名称"), LVCFMT_CENTER, 100);
	list->InsertColumn(2, _T("时间"), LVCFMT_CENTER, 160);
	list->InsertColumn(3, _T("地点"), LVCFMT_CENTER, 180);
	list->InsertColumn(4, _T("拾取人名"), LVCFMT_CENTER, 100);
	list_dispaly1();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


// ADMIN 消息处理程序
void ADMIN::list_dispaly1()
{
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST2);
	plist->SetRedraw(FALSE);
	plist->DeleteAllItems();
	_RecordsetPtr  m_pRecordSet;
	try {
		int i = 0;
		CString sql;
		//m_pRecordSet.CreateInstance(__uuidof(Recordset));
		_bstr_t Sql;
		sql.Format(_T("select Pick_name,Pick_time,Pick_place,Pname from Pick "));
		Sql = (_bstr_t)sql;
		//m_pRecordSet->Open((_bstr_t)sql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockPessimistic, adCmdText);
		m_pRecordSet = adp.GetRecordSet(Sql);
		while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF)//遍历返回的每一条记录
		{
			CString str1, str2, str3, str4;
			str1 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_name"));
			str2 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_time"));
			str3 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_place"));
			str4 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pname"));
			str1.TrimRight();
			str2.TrimRight();
			str3.TrimRight();
			str4.TrimRight();
			//删除字符串右边的空格
			plist->InsertItem(i, str1);
			plist->SetItemText(i, 1, str2);
			plist->SetItemText(i, 2, str3);
			plist->SetItemText(i, 3, str4);
			i++;
			m_pRecordSet->MoveNext();
		}
		m_pRecordSet->Close();
	}
	catch (_com_error e)	// 捕捉异常
	{
		m_pRecordSet->Close();
	}

	plist->SetRedraw(TRUE);
	plist->Invalidate();
	plist->UpdateWindow();
}

static int CALLBACK MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	DATA* pListCtrl = (DATA*)lParamSort;
	int col = pListCtrl->subitem; //点击的列项传递给col，用来判断点击了第几列
	CString strItem1 = (pListCtrl->plist)->GetItemText(lParam1, col);
	CString strItem2 = (pListCtrl->plist)->GetItemText(lParam2, col);
	int tmp = strItem1.CompareNoCase(strItem2); //如果两个对象完全一致则返回0，如果小于，则返回-1。
	if (method) // true--升序
	{
		if (tmp <= 0)
			return -1;
		else
			return 1;
	}
	else
	{
		if (tmp >= 0)
			return -1;
		else
			return 1;
	}
}

void ADMIN::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ADD add;
	add.DoModal();
}


void ADMIN::OnBnClickedButton2()   //删除物品信息
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_pname == "" || m_pickplace == "" || m_picktime=="")
	{
		MessageBox(_T("所有内容不能为空！请检查！"), _T("错误"));
		return;
	}
	CString str = m_pickname;
	int k= MessageBox(_T("是否要删除物品") + str + _T("？确认删除后需输入删除原因"), _T("提示"), MB_YESNO);
	if (k == IDYES)
	{
		DEL del;
		del.DoModal();
	}
}


void ADMIN::OnBnClickedButton3()   
{
	// TODO: 在此添加控件通知处理程序代码
	ADMIN::OnOK();
}


void ADMIN::OnBnClickedButton4()   //修改物品信息
{
	UpdateData(true);
	if (m_pickname == "" || m_pname == "" || m_pickplace == "" || m_picktime=="")
	{
		MessageBox(_T("所有内容不能为空！请检查！"), _T("错误"));
		return;
	}
	int k = MessageBox(_T("物品名称将不会进行修改！是否继续"), _T("提示"), MB_YESNO);
	if (IDYES)
	{
		CString sql;
		_bstr_t Sql;
		sql.Format(_T("update Pick set Pname='%s',Pick_time='%s',Pick_place='%s' where Pick_name='%s' "), m_pname, m_picktime, m_pickplace, m_pickname);
		Sql = (_bstr_t)sql;
		if (adz.ExecuteSQL(Sql))
			MessageBox(_T("修改成功！"), _T("提示"));
		else
			AfxMessageBox(_T("修改失败！"));
	}
	else
		return;
	
	// TODO: 在此添加控件通知处理程序代码
}


BOOL ADMIN::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT1)->m_hWnd)
			{
				return  TRUE;
			}
		}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH ADMIN::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_rush;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0, 180, 0));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_rush;

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_rush;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}




void ADMIN::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	CListCtrl* list = (CListCtrl*)GetDlgItem(IDC_LIST2);
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	CString str;
	USES_CONVERSION;
	if (-1 != pNMListView->iItem)
	{
		str = list->GetItemText(pNMListView->iItem, 0);
		m_pickname = str;
		str = list->GetItemText(pNMListView->iItem, 1);
		m_picktime = str;
		str = list->GetItemText(pNMListView->iItem, 2);
		m_pickplace = str;
		str = list->GetItemText(pNMListView->iItem, 3);
		m_pname = str;
		UpdateData(false);
	}
	CBitmap bitmap;  // CBitmap对象，用于加载位图   
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄 
	if (strcmp("手机", T2A(m_pickname)) == 0)
		bitmap.LoadBitmap(IDB_phone_image);  // 将位图加载到bitmap   
	else if (strcmp("饭卡", T2A(m_pickname)) == 0)
		bitmap.LoadBitmap(IDB_card_image);
	else if (strcmp("钥匙", T2A(m_pickname)) == 0)
		bitmap.LoadBitmap(IDB_key_image);
	else
		MessageBox(_T("没有此物品对应的图片"));
	hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
	m_image2.SetBitmap(hBmp);    // 设置图片控件m_iamge的位图图片

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void ADMIN::OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	CListCtrl* m_ListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST2);
	sort_column = pNMLV->iSubItem;//点击的列

	int count = m_ListCtrl->GetItemCount();
	for (int i = 0; i < count; i++)
		m_ListCtrl->SetItemData(i, i);

	DATA data;
	data.subitem = sort_column;
	data.plist = m_ListCtrl;

	method = !method;
	m_ListCtrl->SortItems(MyCompareProc1, (LPARAM)&data);
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}


void ADMIN::OnBnClickedButton5()
{
	list_dispaly1();
	// TODO: 在此添加控件通知处理程序代码
}
