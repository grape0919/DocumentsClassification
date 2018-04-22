
// ClassifyView.cpp : CClassifyView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
///#include "Classify.h"
#endif

///#include "ClassifyDoc.h"
///#include "ClassifyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClassifyView

IMPLEMENT_DYNCREATE(CClassifyView, CView)

BEGIN_MESSAGE_MAP(CClassifyView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CClassifyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CClassifyView ����/�Ҹ�

CClassifyView::CClassifyView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CClassifyView::~CClassifyView()
{
}

BOOL CClassifyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CClassifyView �׸���

void CClassifyView::OnDraw(CDC* /*pDC*/)
{
	CClassifyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CClassifyView �μ�


void CClassifyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CClassifyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CClassifyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CClassifyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CClassifyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CClassifyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CClassifyView ����

#ifdef _DEBUG
void CClassifyView::AssertValid() const
{
	CView::AssertValid();
}

void CClassifyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClassifyDoc* CClassifyView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClassifyDoc)));
	return (CClassifyDoc*)m_pDocument;
}
#endif //_DEBUG


// CClassifyView �޽��� ó����


