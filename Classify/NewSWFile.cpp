// NewSWFile.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
///#include "Classify.h"
#include "NewSWFile.h"
#include "afxdialogex.h"


// CNewSWFile ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNewSWFile, CDialogEx)

CNewSWFile::CNewSWFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWSTOPWORD, pParent)
	, m_filename(_T(""))
{

}

CNewSWFile::~CNewSWFile()
{
}

void CNewSWFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_filename);
}


BEGIN_MESSAGE_MAP(CNewSWFile, CDialogEx)
END_MESSAGE_MAP()


// CNewSWFile �޽��� ó�����Դϴ�.
