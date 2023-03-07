#pragma once


// LOGIN 对话框

class LOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(LOGIN)

public:
	LOGIN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LOGIN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Login_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedOk();
	CString userName;
	CString passwords;
	CBrush m_brush1;
	afx_msg void OnBnClickedCancel();
	
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
