// Clustering.cpp : 구현 파일입니다.
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
		2, 2,       // TODO: 행 및 열의 개수를 조정합니다.
		CSize(10, 10),  // TODO: 최소 창 크기를 조정합니다.
		pContext);
}

BEGIN_MESSAGE_MAP(CClustering, CMDIChildWndEx)
END_MESSAGE_MAP()


// CClustering 메시지 처리기입니다.
