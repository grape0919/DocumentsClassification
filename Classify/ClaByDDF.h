#pragma once

#ifdef _WIN32_WCE
#error "Windows CE������ CMDIChildWnd�� �������� �ʽ��ϴ�."
#endif 

// �����ڰ� �ִ� CClaByDDF �������Դϴ�.

class CClaByDDF : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CClaByDDF)
protected:
	CClaByDDF();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CClaByDDF();

	CSplitterWnd m_wndSplitter;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


