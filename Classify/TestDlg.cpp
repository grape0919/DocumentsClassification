// TestDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Classify.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "JNIControl.h"
#include <thread>

// CTestDlg ��ȭ �����Դϴ�.

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


// CTestDlg �޽��� ó�����Դϴ�.


void CTestDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	cout << "JNI Test" << endl;
	string result = "";
	JNIControl *jni = new JNIControl();
	
	result = jni->extractNoun("F:\\Windows\\HONGKYO\\Project\\Classify\\StudyData\\Text_Sample\\Computer.txt");
	cout << result << endl;
}

