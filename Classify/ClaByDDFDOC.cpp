// ClaByDDFDOC.cpp : ���� �����Դϴ�.
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


// CClaByDDFDOC �����Դϴ�.

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
// CClaByDDFDOC serialization�Դϴ�.

void CClaByDDFDOC::Serialize(CArchive& ar)
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


// CClaByDDFDOC ����Դϴ�.
