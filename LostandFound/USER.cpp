// USER.cpp: 实现文件
//

#include "pch.h"
#include "LostandFound.h"
#include "USER.h"
#include "afxdialogex.h"
#include"LostandFoundDlg.h"

// USER 对话框

IMPLEMENT_DYNAMIC(USER, CDialogEx)
//_ConnectionPtr  m_pConnection;		//连接对象
//_RecordsetPtr  m_pRecordSet;		//记录集对象
CADOConnect ado;
struct DATA1
{
	int subitem1;//存放点击的列
	CListCtrl* plist1;
};
int sort_column1;//记录点击的列
static bool method1 = false;;//记录比较方法

USER::USER(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_User_DIALOG, pParent)
	, mc(_T(""))
	, mname(_T(""))
	, sj(_T(""))
	, dd(_T(""))
	, mc1(_T(""))
	, ld(_T(""))
	, lm(_T(""))
{

}

USER::~USER()
{
}

void USER::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mc);
	DDX_Text(pDX, IDC_EDIT6, mname);
	DDX_Text(pDX, IDC_EDIT2, sj);
	DDX_Text(pDX, IDC_EDIT3, dd);
	DDX_Text(pDX, IDC_EDIT4, mc1);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_P_STATIC, m_image);
	DDX_Control(pDX, IDC_EDIT5, lp);
	DDX_Text(pDX, IDC_EDIT5, ld);
	DDX_Text(pDX, IDC_EDIT7, lm);
}


BEGIN_MESSAGE_MAP(USER, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &USER::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, &USER::OnLvnColumnclickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &USER::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON1, &USER::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &USER::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &USER::OnBnClickedButton4)
END_MESSAGE_MAP()


// USER 消息处理程序


void USER::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	USER::OnOK();
}


HBRUSH USER::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)// 选择对话框    
	{


		return m_bbrush;

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明    
	}
	if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0, 180, 0));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_bbrush;

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		//pDC->SetTextColor(RGB(22, 167, 212));//设置字体颜色
		pDC->SetBkColor(RGB(213, 241, 251));//设置背景颜色
		hbr = (HBRUSH)m_bbrush;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL USER::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_bbrush.CreateSolidBrush(RGB(219, 238, 249));
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
	list_dispaly();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void USER::list_dispaly()
{
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST2);
	plist->SetRedraw(FALSE);
	plist->DeleteAllItems();
	_RecordsetPtr  m_pRecordSet;
	::CoInitialize(NULL);
	/*try {
		m_pConnection.CreateInstance("ADODB.Connection");
		_bstr_t strConnect = "Provider=SQLNCLI11.1;Persist Security Info=False;User ID=sa;Initial Catalog=swzl;Data Source=DESKTOP-1VPFSGK;Initial File Name="";Server SPN=""";// Catalog数据库名称，Data数据库 .表示本地数据库
		m_pConnection->Open(strConnect, "sa", "123456", adModeUnknown);
		AfxMessageBox(_T("连接数据库成功！"));
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}*/
	//ado.OnInitDBConnect();
	try {
		int i = 0;
		CString sql;
		//m_pRecordSet.CreateInstance(__uuidof(Recordset));
		_bstr_t Sql;
		sql.Format(_T("select Pick_name,Pick_time,Pick_place,Pname from Pick "));
		Sql = (_bstr_t)sql;
		//m_pRecordSet->Open((_bstr_t)sql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockPessimistic, adCmdText);
		m_pRecordSet = ado.GetRecordSet(Sql);
		while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF)//遍历返回的每一条记录
		{
			CString str1, str2, str3,str4;
			str1 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_name"));
			str2 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_time"));
			str3 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_place"));
			str4= (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pname"));
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
	DATA1* pListCtrl = (DATA1*)lParamSort;
	int col = pListCtrl->subitem1; //点击的列项传递给col，用来判断点击了第几列
	CString strItem1 = (pListCtrl->plist1)->GetItemText(lParam1, col);
	CString strItem2 = (pListCtrl->plist1)->GetItemText(lParam2, col);
	int tmp = strItem1.CompareNoCase(strItem2); //如果两个对象完全一致则返回0，如果小于，则返回-1。
	if (method1) // true--升序
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

void USER::OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	CListCtrl* m_ListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST2);
	sort_column1 = pNMLV->iSubItem;//点击的列

	int count = m_ListCtrl->GetItemCount();
	for (int i = 0; i < count; i++)
		m_ListCtrl->SetItemData(i, i);

	DATA1 data;
	data.subitem1 = sort_column1;
	data.plist1 = m_ListCtrl;

	method1 = !method1;
	m_ListCtrl->SortItems(MyCompareProc1, (LPARAM)&data);
	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void USER::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
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
		mc = str;
		str = list->GetItemText(pNMListView->iItem, 1);
		sj = str;
		str = list->GetItemText(pNMListView->iItem, 2);
		dd = str;
		str = list->GetItemText(pNMListView->iItem, 3);
		mname = str;
		UpdateData(false);
	}
	CBitmap bitmap;  // CBitmap对象，用于加载位图   
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄 
	if (strcmp("手机", T2A(mc)) == 0)
		bitmap.LoadBitmap(IDB_phone_image);  // 将位图加载到bitmap   
	else if (strcmp("饭卡", T2A(mc)) == 0)
		bitmap.LoadBitmap(IDB_card_image);
	else if (strcmp("钥匙", T2A(mc)) == 0)
		bitmap.LoadBitmap(IDB_key_image);
	else
		MessageBox(_T("没有此物品对应的图片"));
	hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
	m_image.SetBitmap(hBmp);    // 设置图片控件m_iamge的位图图片

	// TODO: 在此添加控件通知处理程序代码
	
}


void USER::OnBnClickedButton1()
{
	int  flag = 0;
	USES_CONVERSION;
	_RecordsetPtr  m_pRecordSet;
	UpdateData(true);
	if (mc1 == "")
	{
		MessageBox(_T("请输入要查询的物品名称"));
	}
	else
	{
		try {
			CString sql;
			//m_pRecordSet.CreateInstance(__uuidof(Recordset));
			sql.Format(_T("select Pick_name,Pick_time,Pick_place,Pname from Pick where Pick_name='%s'"), mc1);
			_bstr_t Sql;
			Sql = (_bstr_t)sql;
			//m_pRecordSet->Open((_bstr_t)sql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockPessimistic, adCmdText);
			m_pRecordSet = ado.GetRecordSet(Sql);
			while (!m_pRecordSet->adoEOF || !m_pRecordSet->BOF)//遍历返回的每一条记录
			{
				CString str1, str2, str3,str4;
				str1 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_name"));
				str2 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_time"));
				str3 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pick_place"));
				str4 = (LPCSTR)(_bstr_t)(m_pRecordSet->GetCollect("Pname"));
				str1.TrimRight();
				str2.TrimRight();
				str3.TrimRight();
				str3.TrimRight();//删除字符串右边的空格
				mc = mc1;
				sj = str2;
				dd = str3;
				mname = str4;
				flag = 1;
				UpdateData(false);
				CBitmap bitmap;  // CBitmap对象，用于加载位图   
				HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄 
				if (strcmp("手机", T2A(mc1)) == 0)
					bitmap.LoadBitmap(IDB_phone_image);  // 将位图加载到bitmap   
				else if (strcmp("饭卡", T2A(mc1)) == 0)
					bitmap.LoadBitmap(IDB_card_image);
				else if (strcmp("钥匙", T2A(mc1)) == 0)
					bitmap.LoadBitmap(IDB_key_image);
				else
					MessageBox(_T("没有此物品对应的图片"));
				hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
				m_image.SetBitmap(hBmp);    // 设置图片控件m_iamge的位图图片
				m_pRecordSet->MoveNext();
			}
			m_pRecordSet->Close();
		}
		catch (_com_error e)	// 捕捉异常
		{
			m_pRecordSet->Close();
		}
		if (!flag)
		{
			MessageBox(_T("查无此物品！"), _T("查询失败"));
		}
	}// TODO: 在此添加控件通知处理程序代码
}


void USER::OnBnClickedButton3()
{
	UpdateData(true);
	if ( mc== "" || dd == "" || sj == "" || mname=="")
	{
		MessageBox(_T("所有物品信息内容不能为空！请检查！"), _T("错误"));
		return;
	}
	if (lm == "" || ld == "" )
	{
		MessageBox(_T("必须输入领取人姓名与电话！请检查！"), _T("错误"));
		return;
	}
	int k = MessageBox(_T("是否确认领取该物品？"), _T("提示！"), MB_YESNO);
	if (k == IDYES)
	{
		CString sql, sql1;
		_bstr_t Sql, Sql1;
		sql1.Format(_T("insert into Receive(Receiveman_name,Receiveman_phone,Receive_name) values('%s','%s','%s')"), lm, ld, mc);
		Sql1 = (_bstr_t)sql1;
		ado.ExecuteSQL(Sql1);
		sql.Format(_T("delete from Pick where Pick_name='%s' and Pname='%s' and Pick_time='%s' and Pick_place='%s'"), mc, mname, sj, dd);
		Sql = (_bstr_t)sql;
		if (ado.ExecuteSQL(Sql))
			MessageBox(_T("领取成功！"), _T("提示"));
		else
			MessageBox(_T("领取失败！请检查！"), _T("提示"));
	}
	else
		return;
	// TODO: 在此添加控件通知处理程序代码
}


void USER::OnBnClickedButton4()
{
	list_dispaly();
	// TODO: 在此添加控件通知处理程序代码
}
