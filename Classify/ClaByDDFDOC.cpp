// ClaByDDFDOC.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Classify.h"
#include "ClaByDDFDOC.h"


// CClaByDDFDOC

IMPLEMENT_DYNCREATE(CClaByDDFDOC, CDocument)

CClaByDDFDOC::CClaByDDFDOC()
{
}

BOOL CClaByDDFDOC::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CClaByDDFDOC::~CClaByDDFDOC()
{
}


BEGIN_MESSAGE_MAP(CClaByDDFDOC, CDocument)
END_MESSAGE_MAP()


// CClaByDDFDOC 진단입니다.

#ifdef _DEBUG
void CClaByDDFDOC::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CClaByDDFDOC::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CClaByDDFDOC serialization입니다.

void CClaByDDFDOC::Serialize(CArchive& ar)
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


// CClaByDDFDOC 명령입니다.
