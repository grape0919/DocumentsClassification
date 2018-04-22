#pragma once
#include "afxwin.h"
#include "ClassifyMethod.h"
class DDPDoc;

// DDPView 폼 뷰입니다.

class DDPView : public CFormView
{
	DECLARE_DYNCREATE(DDPView)

public:
	DDPDoc* GetDocument() const;

	BOOL PreTranslateMessage(MSG * pMsg);

public:
	DDPView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~DDPView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DDPVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_text;
//	CString m_DDF;
	CEdit m_edit;

	CString m_title = _T("");
	CString m_publish = _T("");
	CString m_writer = _T("");

	CString DOCUMENTNAME = _T("");

	CStringArray DICTIONARY;
	UINT DICSIZE;
	float* DICWEIGHT;
	CString * ExtractedWord;
	UINT WordSize;

	CString * Word;
	UINT * numOfeachWord;
	UINT numOfWord;
	afx_msg void OnEnChangeEdit1();

public:
	void DDFProcess(CString text);
	CString m_KEYWORD;
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG //non-디버그 버전
inline DDPDoc* DDPView::GetDocument() const
{
	return reinterpret_cast<DDPDoc*>(m_pDocument);
}
#endif 


