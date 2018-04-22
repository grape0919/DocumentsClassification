#pragma once
#include "afxwin.h"


// CSWMDialog ��ȭ �����Դϴ�.

class CSWMDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSWMDialog)

public:
	CSWMDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSWMDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SWMENAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
