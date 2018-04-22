// TestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Classify.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "JNIControl.h"
#include <thread>

// CTestDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TESTDLG, pParent)
	, Log(_T(""))
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Log);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestDlg 메시지 처리기입니다.


void CTestDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cout << "JNI Test" << endl;
	string result = "";
	JNIControl *jni = new JNIControl();
	
	result = jni->extractNoun("F:\\Windows\\HONGKYO\\Project\\Classify\\StudyData\\Text_Sample\\Computer.txt");
	cout << result << endl;
}

