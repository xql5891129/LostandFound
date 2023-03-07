#pragma once


// ADMIN 对话框

class ADMIN : public CDialogEx
{
	DECLARE_DYNAMIC(ADMIN)

public:
	ADMIN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ADMIN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Admin_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString m_pickname;
	CString m_pname;
	CString m_picktime;
	CString m_pickplace;
	CBrush m_rush;
	afx_msg void OnBnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	void list_dispaly1();
//	CStatic m_image1;
	CListCtrl m_list1;
	CStatic m_image2;
	afx_msg void OnBnClickedButton5();
};
