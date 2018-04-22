// SWMDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
///#include "Classify.h"
///#include "SWMDialog.h"
#include "afxdialogex.h"

///#include "UtilFunction.h"
///#include "DDPView.h"
#include "EditSWFile.h"
// CSWMDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSWMDialog, CDialogEx)

CSWMDialog::CSWMDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SWMENAGE, pParent)
	, m_preView(_T(""))
{
	
}

CSWMDialog::~CSWMDialog()
{
}

void CSWMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_swList);
	DDX_Text(pDX, IDC_EDIT1, m_preView);

	
}


BEGIN_MESSAGE_MAP(CSWMDialog, CDialogEx)
ON_LBN_SELCHANGE(IDC_LIST1, &CSWMDialog::OnLbnSelchangeList1)
ON_BN_CLICKED(IDC_BUTTON1, &CSWMDialog::addStopWord)
ON_BN_CLICKED(IDC_BUTTON2, &CSWMDialog::DeleteStopword)
ON_BN_CLICKED(IDOK, &CSWMDialog::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON5, &CSWMDialog::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON4, &CSWMDialog::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON3, &CSWMDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSWMDialog 메시지 처리기입니다.




void CSWMDialog::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index;
	char* buff = nullptr;
	index = m_swList.GetCurSel();
	if (index != LB_ERR) {
		CString swfile;
		m_swList.GetText(index, swfile);

		swfile = "stopword\\sw\\" + swfile;

		CFile file;
		CFileException e;
		if (!file.Open(swfile, CFile::modeRead, &e)) {
			AfxMessageBox("stopword\\sw\\ 아래 해당 파일이 없습니다.");
		}
		else {
			buff = new char[file.GetLength() + 1];
			buff[file.GetLength()] = '\0';
			file.Read(buff, file.GetLength());

			swfile.Format("%s", buff);

			m_preView = swfile;
		}
	}
	UpdateData(false);
}


BOOL CSWMDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	listUpdate();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSWMDialog::addStopWord()
{
	CFile stopwordfile;
	CFileException e;

	CFile copyfile;
	CString newfilename;
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!stopwordfile.Open("stopword\\stopword.swp", CFile::modeWrite, &e)) {
		AfxMessageBox("기본생성 파일 \"stopword.swp\" 이 존재하지 않습니다.");
	}
	else {
		CString str = "Stop Word File(*.sw)|*.sw|";
		CFileDialog dlg(TRUE, "*.sw", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, str, this);
		/*CFileDialog dlg(TRUE = 열기|FALSE = 저장, 기본확장자(*.cpp 등), 대화상자 출력시 "파일이름" Edit 컴트롤에 출력될 파일명, 옵션, 불러올 확장자, 대화상자의 부모윈도우);
		//옵션
		OFN_EXPLOPER			윈도우 탐색기 스타일로 출력
		OFN_ARROWMULTISELECT	파일을 한번에 여러개 선택 가능
		OFN_CREATEPROMPT		존재하지 않는 파일명을 입력했을 경우 새로 생성하겠냐는 메시지 박스 출력
		OFN_FILEMUSTEXIST		존재하지 않는 파일명을 입력할 수 없도록 함
		OFN_HIDEREADONLY		읽기전용 파일은 출력하지 않음
		OFN_LONGNAMES			긴 파일 이름 포맷 지원
		OFN_OVERWRITEPROMPT		존재하는 파일명을 입력했을 경우 덮어쓰겠냐는 메시지 박스 출력
		OFN_PATHMUSTEXIST		이미 존재하는 디렉터리명만을 입력
		*/

		if (IDOK == dlg.DoModal()) {

			newfilename = dlg.GetFileName();
			newfilename += "\n";

			stopwordfile.SeekToEnd();
			stopwordfile.Write(newfilename, newfilename.GetLength());
			stopwordfile.Close();
			
			char * buff;

			copyfile.Open(dlg.GetPathName(), CFile::modeRead);

			CFileFind find;

			if (find.FindFile("stopword\\sw\\"+copyfile.GetFileName())) {
				AfxMessageBox("참조된 stopword 파일 중 같은 이름의 파일이 존재합니다.");
			}
			else {
				stopwordfile.Open("stopword\\sw\\" + dlg.GetFileName(), CFile::modeCreate | CFile::modeWrite);

				buff = new char[copyfile.GetLength() + 1];
				buff[copyfile.GetLength()] = '\0';
				copyfile.Read(buff, copyfile.GetLength());

				stopwordfile.Write(buff, copyfile.GetLength());

				copyfile.Close();
				stopwordfile.Close();

				CUtilFunction util;
				util.StopWordUpdate();

				listUpdate();
			}
		}
	}
}

/* sw파일 삭제합니다.*/
void CSWMDialog::DeleteStopword()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = -1;
	CString buff= nullptr;
	index = m_swList.GetCurSel();
	int delArray = 0;

	//선택된 리스트 검사
	//리스트가 선택되지 않았다면 index는 -1 이다.
	if (index != -1) {
		CString delname;
		m_swList.GetText(index, delname);

		CFileFind find;
		
		if (find.FindFile("stopword\\sw\\" + delname)) {
			DeleteFile("stopword\\sw\\" + delname);
		}
		CString * newswfilename = new CString[numoffile - 1];
		int sizeofarr = 0;
		
		for (int i = 0; i < numoffile; i++) {
			if (strcmp(swfilename[i],delname)==0) {
				continue;
			}
			else {
				newswfilename[sizeofarr] = swfilename[i];
				sizeofarr++;
			}
		}

		swfilename = nullptr;
		swfilename = new CString[sizeofarr];

		for (int i = 0; i < sizeofarr; i++) {
			swfilename[i] = newswfilename[i];
		}
		numoffile = sizeofarr;

		//swp 파일 새로고침
		CFile swp;
		DeleteFile("stopword\\stopword.swp");
		if (!swp.Open("stopword\\stopword.swp", CFile::modeCreate | CFile::modeReadWrite)){
			AfxMessageBox("swp파일 새로고침 실패");
		}
		else {
			for (int i = 0; i < numoffile; i++) {
				buff = swfilename[i] + "\n";
				swp.Write(buff, buff.GetLength());
			}
			swp.Close();
			listUpdate();
		}
	}
	else {
		AfxMessageBox("삭제할 파일을 선택해주세요.");
	}
}


void CSWMDialog::listUpdate() {
	m_swList.ResetContent();
	for (int i = 0; i < numoffile; i++)
	{
		m_swList.AddString(swfilename[i]);
	}
}

void CSWMDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUtilFunction util;
	util.LoadSWPfile();
	CDialogEx::OnOK();
}


void CSWMDialog::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CUtilFunction util;
	util.LoadSWPfile();
	
}


void CSWMDialog::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = -1;
	index = m_swList.GetCurSel();
	CString editFile;
	CString sbuff;
	char * buff;

	CFile file;
	
	if (index != -1) {
		m_swList.GetText(index, editFile);

		if(!file.Open("stopword\\sw\\"+editFile, CFile::modeReadWrite)) {
			AfxMessageBox("sw 파일 불러오기 실패");
		}
		else {
			buff = new char[file.GetLength() + 1];
			buff[file.GetLength()] = '\0';

			file.Read(buff, file.GetLength());
			file.Close();
			sbuff.Format("%s", buff);
			CEditSWFile dlg;
			dlg.DoModal(sbuff, editFile);
			OnLbnSelchangeList1();
		}
	}
	else {
		AfxMessageBox("편집할 파일을 선택해주세요.");
	}
}



void CSWMDialog::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEditSWFile newSWFile;
	newSWFile.DoModal();
	listUpdate();
}
