// ClusteringDoc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Classify.h"
#include "ClusteringDoc.h"


// CClusteringDoc

IMPLEMENT_DYNCREATE(CClusteringDoc, CDocument)

CClusteringDoc::CClusteringDoc()
{
}

BOOL CClusteringDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CClusteringDoc::~CClusteringDoc()
{
}


BEGIN_MESSAGE_MAP(CClusteringDoc, CDocument)
END_MESSAGE_MAP()


// CClusteringDoc �����Դϴ�.

#ifdef _DEBUG
void CClusteringDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CClusteringDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CClusteringDoc serialization�Դϴ�.

void CClusteringDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}
#endif


// CClusteringDoc ����Դϴ�.
