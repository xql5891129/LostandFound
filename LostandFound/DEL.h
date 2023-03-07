#pragma once


// DEL 对话框

class DEL : public CDialogEx
{
	DECLARE_DYNAMIC(DEL)

public:
	DEL(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DEL();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Delete_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString reason;
	CString de_name;
	CString de_manname;
	CBrush m_rush4;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
