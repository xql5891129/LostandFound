#pragma once


// UserShuomingDlg 对话框

class UserShuomingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserShuomingDlg)

public:
	UserShuomingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UserShuomingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_usershuoming_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_static1;
	afx_msg void OnBnClickedCancel();
};
