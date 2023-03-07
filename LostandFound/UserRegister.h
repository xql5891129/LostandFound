#pragma once


// UserRegister 对话框

class UserRegister : public CDialogEx
{
	DECLARE_DYNAMIC(UserRegister)

public:
	UserRegister(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserRegister();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Register_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString User_name;
	CString User_password;
	CString User_realname;
	CString User_E_mail;
	CEdit User_phone;
	CString User_telephone;
	CBrush m_rush2;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
