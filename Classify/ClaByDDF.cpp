// ClaByDDF.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Classify.h"
#include "ClaByDDF.h"


// CClaByDDF

IMPLEMENT_DYNCREATE(CClaByDDF, CMDIChildWndEx)

CClaByDDF::CClaByDDF()
{
}

CClaByDDF::~CClaByDDF()
{
}

BOOL CClaByDDF::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,       // TODO: �� �� ���� ������ �����մϴ�.
		CSize(10, 10),  // TODO: �ּ� â ũ�⸦ �����մϴ�.
		pContext);
}

BEGIN_MESSAGE_MAP(CClaByDDF, CMDIChildWndEx)
END_MESSAGE_MAP()


// CClaByDDF �޽��� ó�����Դϴ�.
