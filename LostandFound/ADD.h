#pragma once


// ADD 对话框

class ADD : public CDialogEx
{
	DECLARE_DYNAMIC(ADD)

public:
	ADD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ADD();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Add_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void Onuser();
	afx_msg void OnBnClickedOk();
	CString Pick_manname;
	CString Pick_phone;
	CString Pick_name;
	CString Pick_place;
	CString Pick_tiame;
	CBrush m_rush3;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
typedef struct node
{
	char pick_name[20];
	char pick_place[20];
	char pick_time[20];
	char pick_manname[15];
	char pick_phone[15];
	struct node* prior, * next;
}Node, * DLinklist;

inline DLinklist init(DLinklist h)
{
	h = (Node*)malloc(sizeof(Node));
	h->prior = NULL;
	h->next = NULL;
	return h;
}

