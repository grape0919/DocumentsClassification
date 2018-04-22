
// Classify.h : Classify 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
// CClassifyApp:
// 이 클래스의 구현에 대해서는 Classify.cpp을 참조하십시오.
//

class CClassifyApp : public CWinAppEx
{
public:
	CClassifyApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileNew();
	afx_msg void OnNewExtractword();
	afx_msg void OnNewClassifyDOC();
	afx_msg void stopwordManager();

public:
	afx_msg void OnOpendocument();
	afx_msg void WikiDlg();
	afx_msg void OnNewSecondclustering();
	afx_msg void TestMenu();

};

extern CClassifyApp theApp;
