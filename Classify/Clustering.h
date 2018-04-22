#pragma once

#ifdef _WIN32_WCE
#error "Windows CE에서는 CMDIChildWnd가 지원되지 않습니다."
#endif 

// 분할자가 있는 CClustering 프레임입니다.

class CClustering : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CClustering)
protected:
	CClustering();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CClustering();

	CSplitterWnd m_wndSplitter;

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
};


