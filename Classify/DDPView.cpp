// DDPView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
///#include "Classify.h"
///#include "DDPView.h"
///#include "DDPDoc.h"
//#include <regex>
//#include "ClassifyMethod.h"
//#include "UtilFunction.h"

using namespace std;
// DDPView

IMPLEMENT_DYNCREATE(DDPView, CFormView)

DDPView::DDPView()
	: CFormView(IDD_DDPVIEW)
	, m_text(_T(""))
	//, m_DDF(_T(""))
	, m_KEYWORD(_T(""))
{
}

DDPView::~DDPView()
{
}

void DDPView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
//	DDX_Text(pDX, IDC_EDIT2, m_DDF);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT3, m_KEYWORD);
}

BEGIN_MESSAGE_MAP(DDPView, CFormView)
	ON_EN_CHANGE(IDC_EDIT1, &DDPView::OnEnChangeEdit1)
	ON_COMMAND(ID_FILE_SAVE, &DDPView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &DDPView::OnFileOpen)
END_MESSAGE_MAP()


// DDPView 진단입니다.

#ifdef _DEBUG
void DDPView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DDPView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

DDPDoc* DDPView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(DDPDoc)));
	return (DDPDoc*)m_pDocument;
}
#endif //_DEBUG

// DDPView 메시지 처리기입니다.

BOOL DDPView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->hwnd == (HWND)m_edit)            // 에디트 박스에서의 키 이벤트
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if ((::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == 86))    // Ctrl + V 면 
				pMsg->message = WM_PASTE;                                               // 메시지에 해당 발생 메시지를
																						// 넣어주고 전송시킵니다.
			else if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == 67)  // Ctrl + C
				pMsg->message = WM_COPY;

			else if (::GetKeyState(VK_CONTROL) < 0 && pMsg->wParam == 65)
				pMsg->message = ID_EDIT_SELECT_ALL;

			// else if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_SPACE) {
				
			//}
		}
	}
	
	return CView::PreTranslateMessage(pMsg);
}



void DDPView::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);
	CString buff;
	CString * buffp;
//	ClassifyMethod cm;
	DDFProcess(m_text);
	
	//m_text.
	//MAKE DIC 
//	buffp = cm.MakeDictionary(m_text);

//	for (int i = 0; i < sizeof(buffp); i++) {
//		m_KEYWORD += buffp[i];
//	}

	//UpdateData(false);
	
}

/*입력된 텍스트에서 단어를 추출하여 출력될 문구를 만듭니다.
출력 문구는 DDF 파일로 활용될 수 있습니다.*/
void DDPView::DDFProcess(CString text) {
	UpdateData(true);

	CString buff;
	CString buff2;
	//UINT* numOfWord;

	//단어 추출
	ClassifyMethod cm(text);
	DICTIONARY.Append(cm.DICTIONARY);
	DICSIZE = cm.dicSize;
	DICWEIGHT = cm.DICWEIGHT;

	ExtractedWord = cm.allWord;
	WordSize = cm.wordSize;

	Word = cm.Word;
	numOfeachWord = cm.numOfEachWord;
	numOfWord = cm.numOfWord;

	//키워드 추출
	buff = "";
	
	for (int i = 0; i < numOfWord; i++) {
		buff += Word[i];
		//buff += DICTIONARY.ElementAt(i);
		//buff += " : ";
		//buff2.Format("%d", cm.DICNUM.ElementAt(i));
		//buff += buff2;
		buff +="\r\n";
	}
	buff += "=============================\r\n";
	//buff2.Format("%d", cm.DICTIONARY.GetCount());
	buff2.Format("%d", numOfWord);
	buff += buff2;
	//모든 단어 추출
	/*
	for (int i = 0; i < cm.numOfWord; i++) {
		buff += cm.Word[i];
		buff += "\r\n";
		
	}
	*/
	m_KEYWORD = buff;
	UpdateData(false);
}

void DDPView::OnFileSave()
{
	UpdateData(true);

	CUtilFunction util;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString extenstion = "*.ddf";
	CString filter = "Document Data File(*.ddf)|*.ddf|";
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString saveDDFbuff;
	CString buff = "";
	CString secbuff = "";
	/*
	<DDF>
		<INFORMATION 
				title = "제목"
				writer = "저자"
				publisher = "출판사"
		/>
		<KEYWORD>
			abc dda
			aaa fa
			ddd fa
			dddda eef
			...
		</KEYWORD>
		<DOCUMENT>
			
		</DOCUMENT>
	</DDF>
	*/
	
	buff = CString("<DDF>") + "\r\n"
		+ "<INFORMATION" + "\r\n"
		+ "title = \" " + m_title + "\"\r\n"
		+ "writer = \" " + m_writer + "\"\r\n"
		+ "publish = \" " + m_publish + "\"\r\n"
		+ "/>" + "\r\n"
		+ "<KEYWORD>" + "\r\n";

	buff = CString(buff) + m_KEYWORD + "\r\n";

	buff = CString(buff)
		+ "</KEYWORD>" + "\r\n"
		+ "<DOCUMENT>" + "\r\n";

	for (int i = 0; i < numOfWord; i++) {
		buff += ExtractedWord[i] + " = ";
		secbuff.Format("%d", numOfeachWord[i]);
		buff += secbuff;
		if (i % 10 == 0) {
			buff += "\r\n";
		}
	}

	buff = CString(buff)
		+ _T("</DOCUMENT>") + "\r\n"
		+ "</DDF>" + "\r\n"
		;


	util.SaveFileDialog(buff, extenstion, filter);
}


void DDPView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//UpdateData(true);

	CUtilFunction util;
	CString extension = _T("*.txt");
	CString filter = _T("Text File(*.txt)|*.txt|");
	m_text = util.OpenFileDialog(extension, filter);
	UpdateData(false);


	DDFProcess(m_text);
}

