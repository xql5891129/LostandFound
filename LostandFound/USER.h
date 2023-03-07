#pragma once


// USER 对话框

class USER : public CDialogEx
{
	DECLARE_DYNAMIC(USER)

public:
	USER(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~USER();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_User_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CBrush m_bbrush;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	void list_dispaly();
	CString mc;
	CString mname;
	CString sj;
	CString dd;
	CString mc1;
	CListCtrl m_list;
	CStatic m_image;
	afx_msg void OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	CEdit lp;
	CString ld;
	CString lm;
	afx_msg void OnBnClickedButton4();
};
