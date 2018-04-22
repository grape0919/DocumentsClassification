// CompareDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Classify.h"
#include "CompareDlg.h"
#include "afxdialogex.h"


// CompareDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CompareDlg, CDialog)

CompareDlg::CompareDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_COMPAREDLG, pParent)
	, m_DocA(_T(""))
	, m_DocB(_T(""))
	, m_Common(_T(""))
	, m_StaticA(_T(""))
	, m_StaticB(_T(""))
{

}

CompareDlg::~CompareDlg()
{
}

void CompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DocA);
	DDX_Text(pDX, IDC_EDIT2, m_DocB);
	DDX_Text(pDX, IDC_EDIT3, m_Common);
	DDX_Text(pDX, IDC_STATIC1, m_StaticA);
	DDX_Text(pDX, IDC_STATIC2, m_StaticB);
}


BEGIN_MESSAGE_MAP(CompareDlg, CDialog)
END_MESSAGE_MAP()


// CompareDlg 메시지 처리기입니다.
