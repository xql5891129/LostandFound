#pragma once


// UserLogin 对话框

class UserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(UserLogin)

public:
	UserLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString Username;
	CString Userpassword;
	
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
	CBrush m_rush1;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
