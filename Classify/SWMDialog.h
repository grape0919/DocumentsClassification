#pragma once
#include "afxwin.h"


// CSWMDialog 대화 상자입니다.

class CSWMDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSWMDialog)

public:
	CSWMDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSWMDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SWMENAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CListBox m_swList;
public:
	CString m_preView;
	afx_msg void OnLbnSelchangeList1();
//	virtual INT_PTR DoModal();
	virtual BOOL OnInitDialog();
	afx_msg void addStopWord();
	void listUpdate();
	afx_msg void DeleteStopword();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
