#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "stdafx.h"
#include "DocMat.h"
#include "WordStorage.h"

// CClusteringView 폼 뷰입니다.

class CClusteringView : public CFormView
{
	DECLARE_DYNCREATE(CClusteringView)

public:
	CClusteringDoc* GetDocument() const;
	
protected:
	CClusteringView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CClusteringView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLUSTERINGVIEW };
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
	CTreeCtrl m_ctlTree;
	WordStorage l;
	afx_msg void OnFileOpen();
	CListBox m_fileList;
	vector<CString> files;
	CString m_WorldDictionary;

	CString m_KeyWord;
	CString m_locDic;
	UINT m_k;

	float Sim(DocMat a, DocMat b);
	void Savefile(CString text);
	bool Kcompare(CUIntArray& a, CUIntArray& b);
	WordStorage worldWS;
	WordStorage* DOC = nullptr;
	DocMat* DocMatrix = nullptr;
	afx_msg void OnSelchangeList1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	UINT * SeedInit(UINT numDoc);
	UINT * SeedInit_FarDist(UINT numDoc, DocMat * Doc_Matrix);
	BOOL m_InitSeedSel;
	enum class Flag {
		same = true,
		notsame
	};
};

#ifndef _DEBUG //non-디버그 버전
inline CClusteringDoc* CClusteringView::GetDocument() const
{
	return reinterpret_cast<CClusteringDoc*>(m_pDocument);
}
#endif 
