// DDPDoc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"


// DDPDoc

IMPLEMENT_DYNCREATE(DDPDoc, CDocument)

DDPDoc::DDPDoc()
{
}

BOOL DDPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

DDPDoc::~DDPDoc()
{
}


BEGIN_MESSAGE_MAP(DDPDoc, CDocument)
END_MESSAGE_MAP()


// DDPDoc �����Դϴ�.

#ifdef _DEBUG
void DDPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void DDPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// DDPDoc serialization�Դϴ�.

void DDPDoc::Serialize(CArchive& ar)
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


// DDPDoc ����Դϴ�.
