#pragma once

#ifdef _WIN32_WCE
#error "Windows CE������ CMDIChildWnd�� �������� �ʽ��ϴ�."
#endif 

// �����ڰ� �ִ� CClustering �������Դϴ�.

class CClustering : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CClustering)
protected:
	CClustering();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CClustering();

	CSplitterWnd m_wndSplitter;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


