// NewSWFile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
///#include "Classify.h"
#include "NewSWFile.h"
#include "afxdialogex.h"


// CNewSWFile 대화 상자입니다.

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


// CNewSWFile 메시지 처리기입니다.
