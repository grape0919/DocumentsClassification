// ClaByDDFView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Classify.h"
#include "ClaByDDFView.h"
#include "ClaByDDFDOC.h"
#include "CompareDlg.h"

#define UM_UPDATE WM_USER+1

// CClaByDDFView

IMPLEMENT_DYNCREATE(CClaByDDFView, CFormView)

CClaByDDFView::CClaByDDFView()
	: CFormView(IDD_CLABYDDFVIEW)
	, m_text(_T(""))
{

}

CClaByDDFView::~CClaByDDFView()
{
}

void CClaByDDFView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_FileList);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Control(pDX, IDC_PROGRESS3, progressCtrl);
	//JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
}

BEGIN_MESSAGE_MAP(CClaByDDFView, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CClaByDDFView::OnFileOpen)
	ON_LBN_SELCHANGE(IDC_LIST1, &CClaByDDFView::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CClaByDDFView::OnBnClickedButton1)
	ON_MESSAGE(UM_UPDATE, &CClaByDDFView::OnUpdateData)
	ON_BN_CLICKED(IDC_BUTTON2, &CClaByDDFView::OnBnClickedAnalysis)
	ON_BN_CLICKED(IDC_BUTTON3, &CClaByDDFView::OnBnClickedCompare)
	ON_COMMAND(ID_FILE_SAVE, &CClaByDDFView::OnFileSave)
END_MESSAGE_MAP()


// CClaByDDFView �����Դϴ�.

#ifdef _DEBUG
void CClaByDDFView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClaByDDFView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

CClaByDDFDOC* CClaByDDFView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClaByDDFDOC)));
	return (CClaByDDFDOC*)m_pDocument;
}
#endif //_DEBUG


// CClaByDDFView �޽��� ó�����Դϴ�.


void CClaByDDFView::OnFileOpen()
{
	// TODO: Add your command handler code here
	//CUtilFunction util;
	CString extension = "*.txt|*.ddf|*.*|";
	CString filter = "Text File(*.txt)|*.txt|Document Data(*.ddf)|*.ddf|All File(*.*)|*.*|";
	
	//���� ����
	//CFile openFile;
	CString sfile;
	CString strFileList;
	CString sbuff;
	char * buff;
	//CString strBuff;
	POSITION pos;
	CFileDialog dlg(TRUE, extension, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, filter);
	//��Ƽ ���� �������� ���ֱ�
	const int c_cMaxFiles = 10000;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;

	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;
	//
	if (dlg.DoModal() == IDOK) {
		//AfxGetApp()->DoWaitCursor(1);//���콺 Ŀ�� ��������� ����
		pos = dlg.GetStartPosition();
		while (pos) {
			sfile = dlg.GetNextPathName(pos);
			m_FileList.AddString(sfile);
		}
		//AfxGetApp()->DoWaitCursor(-1);//���콺 Ŀ�� ����߿��� �Ϲ����� ����
	}


	UINT index = m_FileList.GetCount();
	
	cm = new ClassifyMethod[index];

	index = 0;
		//���� ����Ʈ�� �ҷ��ͼ� 
	//�������� �ܾ��� ����� ����;
	
	while (index != m_FileList.GetCount()) {
		CString filePath;
		m_FileList.GetText(index, filePath);


		CFile file;
		CFileException e;
		if (!file.Open(filePath, CFile::modeRead, &e)) {
			AfxMessageBox("�ش� ������ �����ϴ�.");
		}

		else {
			buff = new char[file.GetLength() + 1];
			buff[file.GetLength()] = '\0';
			file.Read(buff, file.GetLength());

			sbuff.Format("%s", buff);

			cm[index].DOCUMENTNAME = file.GetFileName();
			cm[index].CMProcess(sbuff);
			file.Close();
		}
		index++;
	}
	//AfxGetApp()->DoWaitCursor(-1);
}


void CClaByDDFView::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	/** ����Ʈ Ŭ���� ���� ��� **/
/*	int index;
	char* buff;
	CString sbuff;
	index = m_FileList.GetCurSel();
	if (index != LB_ERR) {
		CString filePath;
		m_FileList.GetText(index, filePath);

		CFile file;
		CFileException e;
		if (!file.Open(filePath, CFile::modeRead, &e)) {
			AfxMessageBox("�ش� ������ �����ϴ�.");
		}
		else {
			buff = new char[file.GetLength() + 1];
			buff[file.GetLength()] = '\0';
			file.Read(buff, file.GetLength());

			sbuff.Format("%s", buff);

			m_text = sbuff;
		}
	}
	UpdateData(false);*/
	m_text = "";
	int index = m_FileList.GetCurSel();
	CString * buff = nullptr;
	if (index != LB_ERR) {
		for (int i = 0; i < cm[index].DICTIONARY.GetCount(); i++) {
			m_text += cm[index].DICTIONARY[i] + " ";
		}
	}
	UpdateData(false);
}

//�з�
void CClaByDDFView::OnBnClickedButton1()
{
	
	// TODO: Add your control notification handler code here
	int index = 0;
//	char* buff;
	CString sbuff = "";
	m_text = "";
	/*
	AfxGetApp()->DoWaitCursor(1);
	static BOOL bContinue = TRUE;
	CWinThread *pThread = ::AfxBeginThread(ThreadUP, &bContinue);
	*/
	sbuff = "";
	//Ŭ�����͸�

	index = m_FileList.GetCount();
	UINT* cml = new UINT[index];
	float avgWeight = 0;
	float avgWeight2 = 0;
	UINT numofk = 1;
	UINT* k1;
	UINT* k2;
	UINT** gp;
	UINT** gp2;
	UINT* numofgp;
	UINT* numofgp2;

	byte round = 0;
	bool inf;

	UINT** preresult;
	UINT* numofgpresult;

	preresult = new UINT*[numofk];
	numofgpresult = new UINT[numofk];

	do {
		inf = false;
		round++;
		avgWeight2 = avgWeight;
		avgWeight = 0;
		
		//numofk++;
		++numofk;
	//Ŭ������ ���� 
		/*
		sbuff.Format("%d", round);
		m_text += "round : " + sbuff;
		m_text += "\r\n";
		sbuff.Format("%d", numofk);
		m_text += "0Number of K : " + sbuff;
		m_text += "\r\n";*/
	

		//���ع��� ���� ����;
		k1 = new UINT[numofk];
		k2 = new UINT[numofk];
		gp = new UINT*[numofk];
		gp2 = new UINT*[numofk];
		numofgp = new UINT[numofk];
		numofgp2 = new UINT[numofk];

		int count = 0;

		fill_n(numofgp, numofk, 0);
		fill_n(numofgp2, numofk, 0);
		fill_n(cml, index, 0);
		srand((unsigned int)time(NULL));

		float sim = 0;
		float buffsim = 0;

		bool exiSame = false;
		do {
			exiSame = false;
			for (int i = 0; i < numofk; i++) {
				k1[i] = rand() % index;
			}
			for (int i = 0; i < numofk; i++) {
				for (int j = i + 1; j < numofk; j++) {
					if (k1[i] == k1[j]) exiSame = true;
				}
			}
		} while (exiSame == true);
		
		///////////////////////////////////
		/*
		for (int j = 0; j < index; j++) {
			for (int m = 0; m < index; m++) {
				if (j != m) {
					buffsim += Sim(cm[j], cm[m]);
				}
			}
			if (buffsim > sim) {
				sim = buffsim;
				k1[0] = index;
			}
		}
		
		for (int i = 1; i < numofk; i++) {
			for (int j = 0; j < i; j++) {
				cm[k1[j]];
			}
		}
		*/
		//�ʱ���ذ� ���------------------------------------------//
		//m_text += "Reference Doc : ";
		//m_text += "\r\n";

		//for (int i = 0; i < numofk; i++) {
		//	sbuff.Format("%d", i);
		//	m_text += "k[" + sbuff + "] = " + cm[k1[i]].DOCUMENTNAME + "\r\n";
		//}
		//m_text += "-----------------------------\r\n";
		//m_text = m_text;
		//--------------------------------------------------------

		//���絵 ���� �� �Ҵ�
		//������ �ƴ� ������ ���ذ� ���絵 ����
	
		bool nonstop = false;

		m_text += "\r\nProcess--------------------------\r\n";
		UpdateData(false);
		do {
			buffsim = 0;
			sim = 0;

			//round++;
			/*
			sbuff.Format("%d", round);
			m_text += "- round " + sbuff;
			m_text += " -\r\n";
			*/
			//���ع����� �ٸ��������� ���絵 ������
			//���絵�� ���� ���ع����� �׷��Ҵ�
			for (int i = 0; i < index; i++) {
				bool isRefDoc = false;
				//�ε����� ���� �������� Ȯ��
				for (int j = 0; j < numofk; j++) {
					if (k1[j] == i) {
						isRefDoc = true;
						cml[i] = k1[j];
						break;
					}
				}
				if (!isRefDoc) {
					for (int j = 0; j < numofk; j++) {
						buffsim = Sim(cm[k1[j]], cm[i]);
						
						sbuff.Format("%f", buffsim);
						m_text += "[ " + cm[i].DOCUMENTNAME + ", " + cm[k1[j]].DOCUMENTNAME + "] = " + sbuff + "\r\n";

						if (buffsim >= sim) {
							sim = buffsim;
							//�׷쿡 ���繮�� �Ҵ�
							cml[i] = k1[j];
						}
					}
				}
				buffsim = 0;
				sim = 0;
				m_text +=  " * " + cm[i].DOCUMENTNAME + " --> " + cm[cml[i]].DOCUMENTNAME + "\r\n";
			}
			m_text += "---------------------------------\r\n";

			//�������� �׷쿡�� �ٽ� ������ ã��
			m_text += "\r\n-------Reset reference docuement-------\r\n";

			for (int i = 0; i < numofk; i++) {
				m_text = CString(m_text) + "\r\n***k[" + cm[k1[i]].DOCUMENTNAME + "]***\r\n";
				count = 0;

				//���� �׷��� ������ ã��
				for (int j = 0; j < index; j++) {
					if (k1[i] == cml[j]) {
						count++;
					}
				}

				//�׷����� ����
				gp[i] = new UINT[count];
				numofgp[i] = count;
				UINT ind = 0;
				for (int j = 0; j < index; j++) {
					if (k1[i] == cml[j]) {
						gp[i][ind] = j;
						ind++;
						m_text = CString(m_text) + cm[j].DOCUMENTNAME + "\r\n";
					}
				}
				//�׷� ��������
				//�� ������ ���� ��
				//
				m_text += "\r\n-weight for reset-\r\n";

				//�׷쳻���� �� �����鰣�� ���絵�� ��� ����.
				sim = 0;
				for (int j = 0; j < numofgp[i]; j++) {
					buffsim = 0;
					if (numofgp[i] <= 1) {
						buffsim += Sim(cm[gp[i][j]], cm[gp[i][j]]);
					}
					else {
						//�ٸ� �������� ���絵�� ��� ����
						for (int m = 0; m < numofgp[i]; m++) {
							if (gp[i][m] != gp[i][j]) {
								buffsim += Sim(cm[gp[i][j]], cm[gp[i][m]]);
							}
						}
						buffsim = buffsim / (numofgp[i] - 1);
					}
					
					
					sbuff.Format("%f", buffsim);
					m_text = CString(m_text) + "--" + cm[gp[i][j]].DOCUMENTNAME + " = " + sbuff + "\r\n";

					avgWeight += buffsim;
					//������ ��ü
					//���絵�� ������ ���������� ��ü

					if (buffsim >= sim) {
						sim = buffsim;
						k2[i] = gp[i][j];
					}
				}
			}
			//���� �������� ��
			//������ �ݺ� �׸�.
			nonstop = false;
			for (int i = 0; i < numofk; i++) {
				//�������� �ٸ��ٸ� �ٽ� �ݺ�
				if (k1[i] != k2[i]) {
					nonstop = true;
					break;
				}
				//�������� ���ٸ�
				else {
					//�� �׷��� ������ ���� ������ ������ �˻�
					bool samegp = true;
					for (int same = 0; same < numofk; same++) {
						if (numofgp[same] != numofgp2[same]) {
							samegp = false;
							nonstop = true;
							break;
						}
					}
					if (i == (numofk - 1) && samegp) {
						for (int check = 0; check < i; check++) {
							for (int gpp = 0; gpp < numofgp[check]; gpp++) {
								if (gp[check][gpp] != gp2[check][gpp]) {
									nonstop = true;
									break;
								}
							}
							if (nonstop) break;
						}
					}
				}
			}
			if (nonstop) {
				for (int j = 0; j < numofk; j++) {
					k1[j] = k2[j];
					gp2[j] = new UINT[numofgp[j]];
					for (int gpp = 0; gpp < numofgp[j]; gpp++) {
						gp2[j][gpp] = gp[j][gpp];
					}
					numofgp2[j] = numofgp[j];
					avgWeight = 0;
				}
			}

			//m_text += "\r\nReference DOC :\r\n";
			
			//for (int i = 0; i < numofk; i++) {
			//	m_text += cm[k1[i]].DOCUMENTNAME + "\r\n";
			//}
			//m_text += "------------------------\r\n\r\n";
			
		} while (nonstop);
		float fbuff = avgWeight;
		avgWeight = fbuff / (float)index;
	
	
		for (int i = 0; i < numofk; i++) {
			m_text += " ************Completed to classify DOCUMENT************* \r\n" + cm[k2[i]].DOCUMENTNAME +"\r\n\r\n";
			//m_text = m_text;
			for (int j = 0; j < index; j++) {
				if (cml[j] == k2[i]) {
					m_text += cm[j].DOCUMENTNAME + "\r\n";
					//m_text = m_text;
				}
			}
			m_text += "\r\n";

		}
		sbuff.Format("%f", avgWeight);
		m_text += "avgWeight : " + sbuff + "\r\n";

		if (!_finite(avgWeight)||_isnan(avgWeight)) {
			numofk--;
			avgWeight = avgWeight2;
			inf = true;
		}
		if (avgWeight >= avgWeight2) {
			preresult = new UINT*[numofk];
			numofgpresult = new UINT[numofk];

			for (int i = 0; i < numofk; i++) {
				numofgpresult[i] = numofgp[i];
				preresult[i] = new UINT[numofgp[i]];
				for (int j = 0; j < numofgp[i]; j++) {
					preresult[i][j] = gp[i][j];
				}
			}
		}
	}while (avgWeight >= avgWeight2 || inf || numofk == index-1);
	
	m_text += "---------------RESURT---------------\r\n";
	for (int i = 0; i < numofk-1; i++) {
		m_text += "---------------------\r\n";
		//m_text += cm[k1[i]].DOCUMENTNAME;
		//m_text += "\r\n";
		for (int j = 0; j < numofgpresult[i]; j++) {
			m_text += cm[preresult[i][j]].DOCUMENTNAME;
			m_text += "\r\n";
		}
		m_text += "---------------------\r\n";
	}
	
	//m_text = m_text;
	UpdateData(false);
	AfxGetApp()->DoWaitCursor(-1);
	//bContinue = FALSE;
	/*TEST*/
	/*
	CString m_text= "";
	
	for (int i = 0; i < m_FileList.GetCount(); i++) {
		m_FileList.GetText(i, sbuff);
		m_text += sbuff;
		m_text += "\r\n";
		for (int j = 0; j < cm[i].DICTIONARY.GetCount(); j++) {
			m_text += cm[i].DICTIONARY.ElementAt(j);
			m_text += "\r\n";
		}
		m_text += "--DOCUMENT--\r\n";

		for (int j = 0; j < cm[i].wordSize; j++) {
			m_text += cm[i].allWord[j];
			m_text += "\r\n";
		}
		m_text += "\r\n";
	}
	m_text = m_text;
	UpdateData(false);
	*/
	//delete[] cm;
}

//
float CClaByDDFView::Sim(ClassifyMethod &a, ClassifyMethod &b) {
	float ABcount = 0;
	float BAcount = 0;
	float sim = 0;
	/*
	for (int i = 0; i < a.DICTIONARY.GetCount(); i++) {
		for (int j = 0; j < b.DICTIONARY.GetCount(); j++) {
			if (a.DICTIONARY.ElementAt(i).Compare(b.DICTIONARY.ElementAt(j)) == 0) {
				ABcount += a.DICWEIGHT[i];
				break;
			}
		}
	}
	
	for (int i = 0; i < b.DICTIONARY.GetCount(); i++) {
		for (int j = 0; j < a.DICTIONARY.GetCount(); j++) {
			if (b.DICTIONARY.ElementAt(i).Compare(a.DICTIONARY.ElementAt(j)) == 0) {
				BAcount += b.DICWEIGHT[i];
				break;
			}
		}
	}
	*/
	for (int i = 0; i < a.DICTIONARY.GetCount(); i++) {
		for (int j = 0; j < b.DICTIONARY.GetCount(); j++) {
			if (a.DICTIONARY.ElementAt(i).Compare(b.DICTIONARY.ElementAt(j))==0) {
				ABcount ++;// *a.DICWEIGHT[i];
				break;
			}
		}
	}
	/*
	for (int i = 0; i < b.DICTIONARY.GetCount(); i++) {
		for (int j = 0; j < a.DICTIONARY.GetCount(); j++) {
			if (b.DICTIONARY.ElementAt(i).Compare(a.DICTIONARY.ElementAt(j))==0) {
				BAcount ++;// *b.DICWEIGHT[i];
				break;
			}
		}
	}*/
	
	//sim = ((ABcount / ((float)b.wordSize) + (BAcount / (float)a.wordSize)))/2;
	if (ABcount == 0) {
		sim = 0;
	}
	else {
		sim = ((ABcount / (float)(b.DICTIONARY.GetCount())) + (ABcount / (float)(a.DICTIONARY.GetCount())))/2 ;
	}
	//sim = ((ABcount / (float)a.dicSize) + (BAcount / (float)b.dicSize)) / 2;
	return sim;
}



LRESULT CClaByDDFView::OnUpdateData(WPARAM wParma, LPARAM lParam) {
	UpdateData(false);
	OnUpdateWindow();
	return 0;
}
UINT CClaByDDFView::ThreadUP(LPVOID param) {
	BOOL *pbContinue = (BOOL *)param;
	CClaByDDFView* pView = (CClaByDDFView *)AfxGetApp()->m_pMainWnd;
	while (*pbContinue) {
		pView->PostMessageA(UM_UPDATE);
	}
	return 0;
}
void CClaByDDFView::OnUpdateWindow()
{
	// �θ�������� ����ũž�� ����ϸ� ����ũž�� ���ϵ� �����쿡�� �˻��ϸ� 
	// ù��° ���ϵ� ������ �ڵ���� �˻��� �����Ѵ�.
	HWND h_wnd = (HWND)FindWindowEx(NULL, NULL, NULL, NULL);
	while (h_wnd != NULL) {
		// IsWindow()�Լ��� ������ �ڵ��� ��ȿ���� üũ�Ѵ�.g5gt
		// IsWindowVisible()�Լ��� �����찡 WS_VISIBLE�� ������ �ִ����� �����ϱ� ������ 
		// �����찡 �ٸ� �����쿡 ������ �ִ��� nonzero�� �����Ѵ�.
		if (IsWindow(h_wnd) && ::IsWindowVisible(h_wnd)) FindWindowAndUpdate(h_wnd);

		// Z-Order�� ���� ��������� �˻��� �Ѵ�.
		h_wnd = (HWND)FindWindowEx(NULL, h_wnd, NULL, NULL);
		::InvalidateRect(h_wnd, NULL, TRUE);
	}
}
void CClaByDDFView::FindWindowAndUpdate(HWND parm_h_window)
{
	// parm_h_window �� ���� ���ϵ� �����츦 �˻��Ѵ�.
	HWND h_find_wnd = (HWND)FindWindowEx(parm_h_window, NULL, NULL, NULL);
	while (h_find_wnd != NULL) {
		if (IsWindow(h_find_wnd) && ::IsWindowVisible(h_find_wnd)) {
			FindWindowAndUpdate(h_find_wnd);
			::InvalidateRect(h_find_wnd, NULL, TRUE);
		}
		h_find_wnd = (HWND)FindWindowEx(parm_h_window, h_find_wnd, NULL, NULL);
	}
}

//�м�...
void CClaByDDFView::OnBnClickedAnalysis()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CUtilFunction util;
	CString buff = _T("");
	CString subBuff = "";

	
	for (int i = 0; i < m_FileList.GetCount(); i++) {
		buff += "*******************"+cm[i].DOCUMENTNAME + "**************************\r\n";
		for (int j = 0; j < cm[i].DICTIONARY.GetCount(); j++) {
			buff += cm[i].DICTIONARY.GetAt(j) + " ";
			if (j%10 == 9) buff += "\r\n";
		}
		subBuff.Format("%d", cm[i].DICTIONARY.GetCount());
		buff += "\r\n : " + subBuff + "\r\n----------------------------------------------------------\r\n\r\n";
	}

	buff += "********************Processing********************\r\n";
	buff += m_text + "\r\n";
	buff += "***************End Processing ****************\r\n";

	util.SaveFileDialog(buff,"*.txt","Text File(*.txt)|*.txt|");

}

//�� ���� ��.
void CClaByDDFView::OnBnClickedCompare()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString extension = "*.txt|";
	CString filter = "Text File(*.txt)|*.txt|";

	//���� ����
	//CFile openFile;
	CString filePath;
	CString strFileList;
	CString sbuff;
	char * buff;
	//CString strBuff;
	POSITION pos;
	CFileDialog dlg(TRUE, extension, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, filter);
	//��Ƽ ���� �������� ���ֱ�
	const int c_cMaxFiles = 2;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;

	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;
	//
	ClassifyMethod classMethod[2];
	if (dlg.DoModal() == IDOK) {
		//AfxGetApp()->DoWaitCursor(1);//���콺 Ŀ�� ��������� ����
		pos = dlg.GetStartPosition();
		int index = 0;
		while (pos) {
			filePath = dlg.GetNextPathName(pos);

			//m_FileList.GetText(index, filePath);


			CFile file;
			CFileException e;
			if (!file.Open(filePath, CFile::modeRead, &e)) {
				AfxMessageBox("�ش� ������ �����ϴ�.");
			}

			else {
				buff = new char[file.GetLength() + 1];
				buff[file.GetLength()] = '\0';
				file.Read(buff, file.GetLength());

				sbuff.Format("%s", buff);

				classMethod[index].CMProcess(sbuff);
				classMethod[index].DOCUMENTNAME = file.GetFileName();
				file.Close();
				index++;
			}
		}
		//AfxGetApp()->DoWaitCursor(-1);//���콺 Ŀ�� ����߿��� �Ϲ����� ����
		
		CompareDlg CD;
		int count = 0;
		CD.m_StaticA = classMethod[0].DOCUMENTNAME;
		CD.m_StaticB = classMethod[1].DOCUMENTNAME;
		CD.m_DocA = "";

		for (int i = 0; i < classMethod[0].DICTIONARY.GetCount(); i++) {
			CD.m_DocA += classMethod[0].DICTIONARY.GetAt(i) + "\r\n";
		}
		sbuff.Format("%d", classMethod[0].DICTIONARY.GetCount());
		CD.m_DocA += " : " + sbuff + "\r\n";
		for (int i = 0; i < classMethod[1].DICTIONARY.GetCount(); i++) {
			CD.m_DocB += classMethod[1].DICTIONARY.GetAt(i) + "\r\n";
		}
		sbuff.Format("%d", classMethod[1].DICTIONARY.GetCount());
		CD.m_DocB += " : " + sbuff + "\r\n";

		for (int i = 0; i < classMethod[0].DICTIONARY.GetCount(); i++) {
			for (int j = 0; j < classMethod[1].DICTIONARY.GetCount(); j++) {
				if (classMethod[0].DICTIONARY.GetAt(i).Compare(classMethod[1].DICTIONARY.GetAt(j)) == 0) {
					CD.m_Common += classMethod[0].DICTIONARY.GetAt(i) + "\r\n";
					count++;
				}
			}
		}
		sbuff.Format("%d", count);
		CD.m_Common += " : " + sbuff + "\r\n";
		float sim = Sim(classMethod[0], classMethod[1]);
		sbuff.Format("%f", sim);
		CD.m_Common += "sim : " + sbuff;

		UpdateData(false);

		CD.DoModal();
	}
}


void CClaByDDFView::OnFileSave()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CUtilFunction util;
	CString extension = "*.txt|";
	CString filter = "Text File(*.txt)|*.txt|";

	util.SaveFileDialog(m_text, extension, filter);
}
