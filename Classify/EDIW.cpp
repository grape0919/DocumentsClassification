// EDIW.cpp : implementation file
//

#include "stdafx.h"
///#include "Classify.h"
#include "EDIW.h"
#include "afxdialogex.h"
///#include "UtilFunction.h"
///#include "ClassifyMethod.h"

// EDIW dialog

IMPLEMENT_DYNAMIC(EDIW, CDialogEx)

EDIW::EDIW(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EDIW, pParent)
	, saveFolder(_T(""))
	, lodeFiles(_T(""))
{

}

EDIW::~EDIW()
{
}

void EDIW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, saveFolder);
	DDX_Text(pDX, IDC_EDIT1, lodeFiles);
}


BEGIN_MESSAGE_MAP(EDIW, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &EDIW::WikifileSelect)
	ON_BN_CLICKED(IDC_BUTTON2, &EDIW::SaveFolderSelect)
	ON_BN_CLICKED(IDOK, &EDIW::OnBnClickedOk)
END_MESSAGE_MAP()


// EDIW message handlers


void EDIW::WikifileSelect()
{
	// TODO: Add your control notification handler code here
	CString file = "";
	CString extension = ".txt|";
	CString filter = "Text File(*.txt)|*.txt|";
	CString Path = "";
	CString strFileList;
	CFileDialog dlg(TRUE, extension, NULL, OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT, filter);

	const int c_cMaxFiles = 1000;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (dlg.DoModal() == IDOK) {
		AfxGetApp()->DoWaitCursor(1);//마우스 커서 대기중으로 변경
		POSITION pos = dlg.GetStartPosition();
		while (pos) {
			file = dlg.GetNextPathName(pos);
			wikiFP.Add(file);

			lodeFiles += file + ";";
		}
		AfxGetApp()->DoWaitCursor(-1);//마우스 커서 대기중에서 일반으로 변경
		UpdateData(false);
	}
}


void EDIW::SaveFolderSelect()
{
	// TODO: Add your control notification handler code here
	ITEMIDLIST        *pidlBrowse;
	char    pszPathname[MAX_PATH];
	BROWSEINFO BrInfo;
	BrInfo.hwndOwner = NULL; //GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = "저장할 디렉토리를 선택하세요.";
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;


	// 다이얼로그를 띄우기
	pidlBrowse = SHBrowseForFolder(&BrInfo);
	CString path = "";

	if (pidlBrowse != NULL)
	{
		// 패스를 얻어옴
		SHGetPathFromIDList(pidlBrowse, pszPathname);
		path = pszPathname;
		saveFolder = path;
		UpdateData(false);
	}
}


void EDIW::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	CFile file;
	char * read;
	string buff;
	string document;
	string filename;
	CString nameBuff;
	ClassifyMethod cm;
	if (!saveFolder.IsEmpty() && !wikiFP.IsEmpty()) {
		for (int i = 0; i < wikiFP.GetCount(); i++) {
			file.Open(wikiFP.GetAt(i), CFile::modeRead, NULL);
			UINT length;
			length = file.GetLength();
			read = new char[length + 1];
			read[length] = '\0';
			file.Read(read, length);
			buff = read;
			delete[] read;
			file.Close();


			while (buff != "") {
				buff = cm.Suff_regex(buff, "(\\[\\[)");
				document = cm.Pref_regex(buff, "(==Refer|== Refer)");
				if (cm.Match_regex(document, "(\\[\\[)") == "") {
					filename = cm.Pref_regex(document, "(\\]\\])");
					nameBuff = filename.c_str();
					nameBuff.Replace("\"", "_");
					nameBuff.Replace("\'", "_");
					nameBuff.Replace("\-", "_");
					nameBuff.Replace("\`", "_");
					if (!file.Open(saveFolder + "\\" + nameBuff + ".txt", CFile::modeCreate | CFile::modeWrite, NULL)) {
						//CString m(filename.c_str());
						//m = m +" 열기 실패";
						//AfxMessageBox(m);
	//					file.Close();
					}
					else {
						//file.Open(saveFolder + "\\" + filename.c_str() + ".txt", CFile::modeCreate | CFile::modeWrite, NULL);
						file.Write(document.c_str(), document.length());
						file.Close();
						buff = cm.Suff_regex(buff, "(==Refer|== Refer)");
						//					delete[] &document;
					}
				}
				else {
					buff = cm.Suff_regex(buff, "(==Refer|== Refer)");
				}
			}
		}
	}
}
