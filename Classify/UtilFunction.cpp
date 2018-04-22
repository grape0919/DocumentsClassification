#include "stdafx.h"
//#include "UtilFunction.h"
//#include "ClassifyMethod.h"

CUtilFunction::CUtilFunction()
{
}


CUtilFunction::~CUtilFunction()
{
}

void CUtilFunction::StopWordUpdate() {

	CFileException e;
	CFileFind find;
	bool isfind = false;

	CString paths;
	char * buff = nullptr;
	CFile stopwordfile;

	numoffile = 0;

	if (!stopwordfile.Open(_T("stopword\\stopword.swp"), CFile::modeRead, &e)) {
		isfind = find.FindFile(_T("stopword"));
		if (!isfind) {
			_mkdir("stopword");
			_mkdir("stopword\\sw");
		}
		if (!stopwordfile.Open(_T("stopword\\stopword.swp"), CFile::modeCreate | CFile::modeReadWrite, &e)) {
			AfxMessageBox(_T("File open fail:") + e.m_cause);
		}
		else {

			CUtilFunction util;
			util.StdSWInit(stopwordfile);

			stopwordfile.Open("stopword\\stopword.swp", CFile::modeRead);

			buff = new char[stopwordfile.GetLength() + 1];
			buff[stopwordfile.GetLength()] = '\0';
			stopwordfile.Read(buff, stopwordfile.GetLength());
			paths.Format("%s", buff);
			stopwordfile.Close();
			delete[] buff;
		}
	}
	else {
		buff = new char[stopwordfile.GetLength() + 1];
		buff[stopwordfile.GetLength()] = '\0';
		stopwordfile.Read(buff, stopwordfile.GetLength());
		paths.Format("%s", buff);
		stopwordfile.Close();
		delete[] buff;
	}

	string sbuff = paths;
	regex re("[a-zA-Z0-9]{1,}\.(sw)");
	smatch match;
	CString buf;

	while (regex_search(sbuff, match, re)) {
		numoffile++;
		sbuff = match.suffix().str();
	}

	swfilename = new CString[numoffile];
	sbuff = paths;
	for (int i = 0; i < numoffile; i++) {
		regex_search(sbuff, match, re);
		swfilename[i] = match.str().c_str();
		sbuff = match.suffix().str();
	}

}

/*기본 stopword 파일을 생성해줍니다.*/
void CUtilFunction::StdSWInit(CFile & stopwordfile) {

	CString stdsw;
	stdsw.Insert(stdsw.GetLength(), "stdstopword.sw\n");

	stopwordfile.Write(stdsw, stdsw.GetLength());

	CFile write;
	write.Open("stopword\\sw\\stdstopword.sw", CFile::modeCreate | CFile::modeWrite);

	stdsw = "a about above after again against all am an and ";
	stdsw += "any are aren't as at be because been before being ";
	stdsw += "below between both but by can't cannot could couldn't did ";
	stdsw += "didn't do does doesn't doing don't down during ";
	stdsw += "each few for from further had hadn't has hasn't have ";
	stdsw += "haven't having he he'd he'll he's her here here's ";
	stdsw += "hers herself him himself his how how's i i'd i'll ";
	stdsw += "i'm i've if in into is isn't it it's its itself ";
	stdsw += "let's me more most mustn't my myself no nor not of ";
	stdsw += "off on once only or other ought our ours ourselves ";
	stdsw += "out over own same shan't she she'd she'll she's ";
	stdsw += "should shouldn't so some such than that that's the ";
	stdsw += "their theirs them themselves then there there's ";
	stdsw += "these they they'd they'll they're they've ";
	stdsw += "this those through to too under until up very ";
	stdsw += "was wasn't we we'd we'll we're we've were weren't ";
	stdsw += "what what's when when's where where's which while ";
	stdsw += "who who's whom why why's with won't would wouldn't ";
	stdsw += "you you'd you'll you're you've your yours yourself yourselves ";

	write.Write(stdsw, stdsw.GetLength());
	stopwordfile.Close();
	write.Close();
}

/*swp 파일 확인후
  stopword를 사용하기위한 stopword 배열 초기화로
  각 sw파일을 불러와 stopword 배열을 생성한다.*/
void CUtilFunction::LoadSWPfile() {

	CFile file;
	//각 파일의 stopword 개수를 총합한다.
	CString swbuf = "";
	CString sbuff;
	char * buff = nullptr;

	int numofsw = 0;
	for (int i = 0; i < numoffile; i++) {
		file.Open("stopword\\sw\\" + swfilename[i], CFile::modeRead);
		buff = new char[file.GetLength() + 1];
		buff[file.GetLength()] = '\0';
		file.Read(buff, file.GetLength());
		sbuff.Format("%s", buff);

		swbuf += sbuff;
		file.Close();
		delete[] buff;
	}

	ClassifyMethod pro;
	stopword = pro.ExtractAllWord(swbuf);
}

/*파일의 내용을 업데이트 해주는 함수.*/
void CUtilFunction::UpdateFile(CString filePath, CString text) {
	CFile swp;
	CFileFind find;
	bool isfind = false;
	isfind = find.FindFile(filePath);

	if (isfind) {
		DeleteFile(filePath);
	}
	if (!swp.Open(filePath, CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox("파일 새로고침 실패");
	}
	else {
		swp.Write(text, text.GetLength());
		swp.Close();
	}
}
/*Save*/
bool CUtilFunction::SaveFileDialog(CString text, CString extension, CString filter) {
	CFile openFile;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg(FALSE, extension, NULL, OFN_OVERWRITEPROMPT, filter);
	
	if (dlg.DoModal() == IDOK) {
		if (!openFile.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite)) {
			AfxMessageBox("파일 저장 실패");
			return false;
		}
		else {
			openFile.Write(text, text.GetLength());
			openFile.Close();
			return true;
		}
	}
}

CString CUtilFunction::OpenFileDialog(CString extenstion, CString filter) {

	CFile openFile;
	CStdioFile file;
	char * buff;
	CString strBuff;
	CString result;
	CFileDialog dlg(TRUE, extenstion, NULL, OFN_FILEMUSTEXIST, filter);
	
	if (dlg.DoModal() == IDOK) {
		//file.Open(dlg.GetPathName(), CFile::modeRead);
		if (!openFile.Open(dlg.GetPathName(), CFile::modeRead,NULL)) {
			AfxMessageBox("파일 불러오기 실패");
			return "파일 불러오기 실패";
		}
		else {
			UINT l;
			l = openFile.GetLength();
			byte w;
			buff = new char[l+1];
			buff[l] = '\0';
			w = openFile.Read(buff, l);
			strBuff = buff;
			delete[] buff;
			openFile.Close();
			return strBuff;
		}
	}
	else {
		return "";
	}
}


