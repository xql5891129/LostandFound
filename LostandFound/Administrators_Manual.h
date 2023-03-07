#pragma once


// Administrators_Manual 对话框

class Administrators_Manual : public CDialogEx
{
	DECLARE_DYNAMIC(Administrators_Manual)

public:
	Administrators_Manual(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Administrators_Manual();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Administrator_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_static2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
