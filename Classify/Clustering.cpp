// Clustering.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Classify.h"
#include "Clustering.h"


// CClustering

IMPLEMENT_DYNCREATE(CClustering, CMDIChildWndEx)

CClustering::CClustering()
{

}

CClustering::~CClustering()
{
}

BOOL CClustering::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,       // TODO: �� �� ���� ������ �����մϴ�.
		CSize(10, 10),  // TODO: �ּ� â ũ�⸦ �����մϴ�.
		pContext);
}

BEGIN_MESSAGE_MAP(CClustering, CMDIChildWndEx)
END_MESSAGE_MAP()


// CClustering �޽��� ó�����Դϴ�.
