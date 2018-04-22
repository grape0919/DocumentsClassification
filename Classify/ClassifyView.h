
// ClassifyView.h : CClassifyView Ŭ������ �������̽�
//

#pragma once


class CClassifyView : public CView
{
protected: // serialization������ ��������ϴ�.
	CClassifyView();
	DECLARE_DYNCREATE(CClassifyView)

// Ư���Դϴ�.
public:
	CClassifyDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CClassifyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32792();
};

#ifndef _DEBUG  // ClassifyView.cpp�� ����� ����
inline CClassifyDoc* CClassifyView::GetDocument() const
   { return reinterpret_cast<CClassifyDoc*>(m_pDocument); }
#endif

