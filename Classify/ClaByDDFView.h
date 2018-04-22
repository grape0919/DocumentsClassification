#pragma once
#include "UtilFunction.h"
#include "afxwin.h"
#include "afxcmn.h"
class CClaByDDFDOC;

// CClaByDDFView �� ���Դϴ�.

class CClaByDDFView : public CFormView
{

	DECLARE_DYNCREATE(CClaByDDFView)

public:
	CClaByDDFDOC* GetDocument() const;
	ClassifyMethod * cm;
protected:
	CClaByDDFView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CClaByDDFView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLABYDDFVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileOpen();
	CListBox m_FileList;
	afx_msg void OnLbnSelchangeList1();
	CString m_text;
	CProgressCtrl progressCtrl;
	afx_msg void OnBnClickedButton1();
	float Sim(ClassifyMethod &a, ClassifyMethod &b);

	LRESULT OnUpdateData(WPARAM wParma, LPARAM lParam);

	static UINT ThreadUP(LPVOID param);

	void OnUpdateWindow();

	void FindWindowAndUpdate(HWND parm_h_window);
	
	afx_msg void OnBnClickedAnalysis();
	afx_msg void OnBnClickedCompare();
	afx_msg void OnFileSave();
};

#ifndef _DEBUG //non-����� ����
inline CClaByDDFDOC* CClaByDDFView::GetDocument() const
{
	return reinterpret_cast<CClaByDDFDOC*>(m_pDocument);
}
#endif 


