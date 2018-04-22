
// Classify.h : Classify ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
// CClassifyApp:
// �� Ŭ������ ������ ���ؼ��� Classify.cpp�� �����Ͻʽÿ�.
//

class CClassifyApp : public CWinAppEx
{
public:
	CClassifyApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
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
