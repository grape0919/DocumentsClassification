// ClusteringDoc.cpp : 구현 파일입니다.
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


// CClusteringDoc 진단입니다.

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
// CClusteringDoc serialization입니다.

void CClusteringDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}
#endif


// CClusteringDoc 명령입니다.
