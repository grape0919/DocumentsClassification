#pragma once

#ifdef _WIN32_WCE
#error "Windows CE������ CMDIChildWnd�� �������� �ʽ��ϴ�."
#endif 

// �����ڰ� �ִ� DDP �������Դϴ�.

class DDP : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(DDP)
protected:
	DDP();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~DDP();

	CSplitterWnd m_wndSplitter;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


