// DDP.cpp : ���� �����Դϴ�.
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
		2, 2,       // TODO: �� �� ���� ������ �����մϴ�.
		CSize(10, 10),  // TODO: �ּ� â ũ�⸦ �����մϴ�.
		pContext);
}

BEGIN_MESSAGE_MAP(DDP, CMDIChildWndEx)
END_MESSAGE_MAP()


// DDP �޽��� ó�����Դϴ�.
