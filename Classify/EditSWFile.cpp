// EditSWFile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
//#include "Classify.h"
#include "EditSWFile.h"
#include "afxdialogex.h"
//#include "UtilFunction.h"
#include "NewSWFile.h"

using namespace std;
// CEditSWFile 대화 상자입니다.

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


// CEditSWFile 메시지 처리기입니다.


BOOL CEditSWFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

INT_PTR CEditSWFile::DoModal(CString text, CString filename)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
				AfxMessageBox("파일 이름에는 \' \\ / : * ? \" < > |] \'\n이 포함될 수 없습니다.");
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
					AfxMessageBox("같은 이름의 파일이 존재합니다.");
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
