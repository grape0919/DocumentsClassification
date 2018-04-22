// DDPDoc.cpp : 구현 파일입니다.
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


// DDPDoc 진단입니다.

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
// DDPDoc serialization입니다.

void DDPDoc::Serialize(CArchive& ar)
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


// DDPDoc 명령입니다.
