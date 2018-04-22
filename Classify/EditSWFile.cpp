// EditSWFile.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
//#include "Classify.h"
#include "EditSWFile.h"
#include "afxdialogex.h"
//#include "UtilFunction.h"
#include "NewSWFile.h"

using namespace std;
// CEditSWFile ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEditSWFile, CDialogEx)

CEditSWFile::CEditSWFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EditSWdlg, pParent)
	, m_edit(_T(""))
	, m_filename(_T(""))
	, request(0)
	, staBuff(_T(""))
{

}

CEditSWFile::~CEditSWFile()
{
}

void CEditSWFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CEditSWFile, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEditSWFile::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditSWFile �޽��� ó�����Դϴ�.


BOOL CEditSWFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

INT_PTR CEditSWFile::DoModal(CString text, CString filename)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_edit = text;
	m_filename = filename;
	request = 0;
	return CDialogEx::DoModal();
}

INT_PTR CEditSWFile::DoModal()
{
	request = 1;
	return CDialogEx::DoModal();
}


void CEditSWFile::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (request == 0) {
		UpdateData(true);
		m_filename = "stopword\\sw\\" + m_filename;
		CUtilFunction util;
		util.UpdateFile(m_filename, m_edit);
	}
	else if (request == 1) {

		UpdateData(true);
		CNewSWFile newfile;
		CString path;
		bool isExist = false;

		smatch match;
		regex re("[\\/:*?\"<> | ]");

		newfile.m_filename = staBuff;
		UpdateData(false);
		
		if (newfile.DoModal() == IDOK) {
			CString buff;
			string str;
			str = newfile.m_filename;
			
			if (regex_search(str, match, re)) {
				AfxMessageBox("���� �̸����� \' \\ / : * ? \" < > |] \'\n�� ���Ե� �� �����ϴ�.");
				staBuff = str.c_str();
				OnBnClickedOk();
			}else{
				path = "stopword\\sw\\" + newfile.m_filename;

				for (int i = 0; i < numoffile; i++) {
					if (swfilename[i].Compare(path) == 0) {
						isExist = true;
						break;
					}
				}
				if (isExist) {
					AfxMessageBox("���� �̸��� ������ �����մϴ�.");
				}
				else {
					CFile newSWFile;
					newSWFile.Open(path + ".sw", CFile::modeWrite | CFile::modeCreate);

					buff = m_edit;

					newSWFile.Write(buff, buff.GetLength());
					newSWFile.Close();

					path = "stopword\\stopword.swp";

					newSWFile.Open(path, CFile::modeRead);
					char * cbuff = new char[newSWFile.GetLength() + 1];
					cbuff[newSWFile.GetLength()] = '\0';
					newSWFile.Read(cbuff, newSWFile.GetLength());
					newSWFile.Close();
					buff.Format("%s", cbuff);
					delete cbuff;

					buff += newfile.m_filename;
					buff += +".sw";
					buff += "\r\n";
					CUtilFunction util;
					util.UpdateFile(path, buff);
					util.StopWordUpdate();
				}
			}
		}
	}
	CDialogEx::OnOK();
}
