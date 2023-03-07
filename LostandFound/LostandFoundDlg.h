
// LostandFoundDlg.h: 头文件
//

#pragma once
#include"stdafx.h"

// CLostandFoundDlg 对话框
class CLostandFoundDlg : public CDialogEx
{
// 构造
public:
	CLostandFoundDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOSTANDFOUND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg LRESULT OnNcHitTest(CPoint point);
	CButton m_static;
	CStatic m_Static;
	CBrush m_Brush;
	CButton m_button2;
	afx_msg void OnView();
	afx_msg void OnView2();
	afx_msg void Onuser();
	afx_msg void Onadminitrators();
};
class CADOConnect
{
public:
	CADOConnect()
	{}
	virtual~CADOConnect()
	{}

	_ConnectionPtr m_pConnection;		// 对象智能指针连接操作数据库 
	_RecordsetPtr m_pRecordPtr;			// 对象指针(记录集)

	// 初始化连接数据库，执行查询，执行SQL语句，断开连接
	// 初始化连接数据库，执行查询，执行SQL语句，断开连接
	void OnInitDBConnect()
	{// 创建connection对象
		try {
			m_pConnection.CreateInstance("ADODB.Connection");
			// 设置字符串
			_bstr_t strConnect = "Provider=SQLNCLI11.1;Persist Security Info=False;User ID=sa;Initial Catalog=swzl;Data Source=DESKTOP-1VPFSGK;Initial File Name="";Server SPN=""";// Catalog数据库名称，Data数据库 .表示本地数据库

			// 连接数据库   双引号里写对应连接数据库的账号和密码
			m_pConnection->Open(strConnect, "sa", "123456", adModeUnknown);
			
		}
		catch(_com_error e)
		{
			AfxMessageBox(e.Description());
		}
	}
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL)
	{
		try
		{
			if (m_pConnection == NULL)		// 连接对象不存在
				OnInitDBConnect();
			m_pRecordPtr.CreateInstance(__uuidof(Recordset));		// 创建记录集对象
			// 执行查询，等待记录集
			m_pRecordPtr->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		}
		catch (_com_error e)	// 捕捉异常
		{
			
			AfxMessageBox(e.Description());
			
		}

		return m_pRecordPtr;		// 返回记录集
	}
	BOOL ExecuteSQL(_bstr_t bstrSQL)   //_bstr_t也是一个类，可以保存字符串和字符串指针
	{
		try
		{
			if (m_pConnection == NULL)
			{
				OnInitDBConnect();
			}
			_variant_t RecordSAffected;    //_variant_t是一个类可以封装任意类型的数据（如字符型，时间，数值型等）
			m_pConnection->Execute(bstrSQL, NULL, adCmdText);
			return true;
			
		}
		catch (_com_error e)
		{
			AfxMessageBox(e.Description());
			
			return false;
		}
		
	}
	void ExitConnect()
	{
		if (m_pConnection != NULL)
		{
			m_pRecordPtr->Close();	// 关闭记录
			m_pConnection->Close();	// 关闭连接
		}

		// 清除缓存
		::CoUninitialize();
	}

};


