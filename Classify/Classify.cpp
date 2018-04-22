
// Classify.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "EDIW.h"
#include "TestDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClassifyApp

BEGIN_MESSAGE_MAP(CClassifyApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CClassifyApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_NEW_EXTRACT, &CClassifyApp::OnNewExtractword)
	ON_COMMAND(ID_NEW_CLASSIFY, &CClassifyApp::OnNewClassifyDOC)
	ON_COMMAND(ID_32786, &CClassifyApp::stopwordManager)
	ON_COMMAND(ID_NEW_OPENDOCUMENT, &CClassifyApp::OnOpendocument)
	ON_COMMAND(ID_32789, &CClassifyApp::WikiDlg)
	ON_COMMAND(ID_NEW_SECONDCLUSTERING, &CClassifyApp::OnNewSecondclustering)
	ON_COMMAND(ID_32792, &CClassifyApp::TestMenu)
END_MESSAGE_MAP()


// CClassifyApp ����

CClassifyApp::CClassifyApp()
{
	m_bHiColorIcons = TRUE;

	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���α׷��� ���� ��� ��Ÿ�� ������ ����Ͽ� ������ ���(/clr):
	//     1) �� �߰� ������ �ٽ� ���� ������ ������ ����� �۵��ϴ� �� �ʿ��մϴ�.
	//     2) ������Ʈ���� �����Ϸ��� System.Windows.Forms�� ���� ������ �߰��ؾ� �մϴ�.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Classify.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.

}

// ������ CClassifyApp ��ü�Դϴ�.

CClassifyApp theApp;


// CClassifyApp �ʱ�ȭ

BOOL CClassifyApp::InitInstance()
{
	{
		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDR_CLABYDDFVIEW_TMPL,
			RUNTIME_CLASS(CClaByDDFDOC),
			RUNTIME_CLASS(CClaByDDF),
			RUNTIME_CLASS(CClaByDDFView));
		AddDocTemplate(pNewDocTemplate);
	}
	{
		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDR_DDPVIEW_TMPL,
			RUNTIME_CLASS(DDPDoc),
			RUNTIME_CLASS(DDP),
			RUNTIME_CLASS(DDPView));
		AddDocTemplate(pNewDocTemplate);
	}
	{
		CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
			IDD_CLUSTERINGVIEW,
			RUNTIME_CLASS(CClusteringDoc),
			RUNTIME_CLASS(CClustering),
			RUNTIME_CLASS(CClusteringView));
		AddDocTemplate(pNewDocTemplate);
	}

	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ClassifyTYPE,
		RUNTIME_CLASS(CClassifyDoc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CClassifyView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	// ��� ���⿡ ���� ���⸦ Ȱ��ȭ�մϴ�.
	m_pMainWnd->DragAcceptFiles();

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// DDE Execute ���⸦ Ȱ��ȭ�մϴ�.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;
	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	
	return TRUE;
}

int CClassifyApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);


	return CWinAppEx::ExitInstance();
}

// CClassifyApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CClassifyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CClassifyApp ����� ���� �ε�/���� �޼���

void CClassifyApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);


	CUtilFunction util;
	util.StopWordUpdate();
	util.LoadSWPfile();

	
}

void CClassifyApp::LoadCustomState()
{
}

void CClassifyApp::SaveCustomState()
{
}

// CClassifyApp �޽��� ó����



int m_poscntDocTemp = 0;

void CClassifyApp::OnFileNew()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CDocTemplate* pDocTemplate = nullptr;

	POSITION pos = GetFirstDocTemplatePosition(); //��ũ�帮��Ʈ�� ù��° ��ġ ���

	for (int i = 0; i < m_poscntDocTemp; i++) //������ ��ũ�帮��Ʈ�� ��ϵ� ���� ��ŭ �̵�ó������.
		pDocTemplate = GetNextDocTemplate(pos);	//��ũ�帮��Ʈ�� ���� ����������.

	pDocTemplate->OpenDocumentFile(NULL);

	
}

void CClassifyApp::OnNewExtractword()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_poscntDocTemp = 2;
	CClassifyApp::OnFileNew();
	m_poscntDocTemp = 0;
}

void CClassifyApp::OnNewClassifyDOC()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_poscntDocTemp = 1;
	CClassifyApp::OnFileNew();
	m_poscntDocTemp = 0;
}

void CClassifyApp::stopwordManager()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	CSWMDialog swmanager;
	swmanager.DoModal();
}

void CClassifyApp::OnOpendocument()
{
	CString str = "Document File(*.txt)|*.txt|";
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE, "*.txt", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, str);
	if (dlg.DoModal() == IDOK) {
	}
}


void CClassifyApp::WikiDlg()
{
	// TODO: Add your command handler code here
	EDIW wiki;
	wiki.DoModal();
}


void CClassifyApp::OnNewSecondclustering()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_poscntDocTemp = 3;
	CClassifyApp::OnFileNew();
	m_poscntDocTemp = 0;
}


void CClassifyApp::TestMenu()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CTestDlg dlg;
	dlg.DoModal();

}
