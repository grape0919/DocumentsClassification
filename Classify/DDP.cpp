// DDP.cpp : 구현 파일입니다.
//

#include "stdafx.h"

// DDP

IMPLEMENT_DYNCREATE(DDP, CMDIChildWndEx)

DDP::DDP()
{

}

DDP::~DDP()
{
}

BOOL DDP::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,       // TODO: 행 및 열의 개수를 조정합니다.
		CSize(10, 10),  // TODO: 최소 창 크기를 조정합니다.
		pContext);
}

BEGIN_MESSAGE_MAP(DDP, CMDIChildWndEx)
END_MESSAGE_MAP()


// DDP 메시지 처리기입니다.
