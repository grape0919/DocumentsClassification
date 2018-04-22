// ClusteringView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Classify.h"
#include "ClusteringView.h"
#include "JNIControl.h"
// CClusteringView

IMPLEMENT_DYNCREATE(CClusteringView, CFormView)

CClusteringView::CClusteringView()
	: CFormView(IDD_CLUSTERINGVIEW)
	, m_WorldDictionary(_T(""))
	, m_KeyWord(_T(""))
	, m_locDic(_T(""))
	, m_k(0)
	, m_InitSeedSel(FALSE)
{
}

CClusteringView::~CClusteringView()
{
}

void CClusteringView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctlTree);
	HTREEITEM  hRoot;

	DDX_Control(pDX, IDC_LIST1, m_fileList);
	DDX_Text(pDX, IDC_EDIT2, m_WorldDictionary);
	DDX_Text(pDX, IDC_EDIT1, m_KeyWord);
	DDX_Text(pDX, IDC_EDIT3, m_locDic);
	DDX_Text(pDX, IDC_EDIT4, m_k);
	DDX_Check(pDX, IDC_CHECK1, m_InitSeedSel);
}

BEGIN_MESSAGE_MAP(CClusteringView, CFormView)
	ON_COMMAND(ID_FILE_OPEN, &CClusteringView::OnFileOpen)
	ON_BN_CLICKED(IDC_BUTTON1, &CClusteringView::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CClusteringView::OnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClusteringView::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClusteringView 진단입니다.

#ifdef _DEBUG
void CClusteringView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClusteringView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
CClusteringDoc* CClusteringView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClusteringDoc)));
	return (CClusteringDoc*)m_pDocument;
}
#endif //_DEBUG


// CClusteringView 메시지 처리기입니다.


void CClusteringView::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString extension = "*.txt|*.*|";
	CString filter = "Text File(*.txt)|*.txt|All File(*.*)|*.*|";

	//파일 열기
	//CFile openFile;

	CString strFileList;
	CString sbuff;
	char * buff;

	POSITION pos;
	CFileDialog dlg(TRUE, extension, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, filter);
	//멀티 선택 개수제한 없애기
	const int c_cMaxFiles = 10000;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;

	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (dlg.DoModal() == IDOK) {

		string sfile;
		int count = 0;
		AfxGetApp()->DoWaitCursor(1);//마우스 커서 대기중으로 변경

		//문서 개수 세기
		pos = dlg.GetStartPosition();
		while (pos) {
			sfile = dlg.GetNextPathName(pos);
			CFileException e;
			CFile * filebuff = new CFile(sfile.c_str(), CFile::modeRead);
			files.push_back(filebuff->GetFileTitle());
			filebuff->Close();
			m_fileList.AddString(sfile.c_str());
		}
		//문서 개수 만큼 단어 저장소객체 생성;
		count = m_fileList.GetCount();
		DOC = new WordStorage[count];
		DocMatrix = new DocMat[count];
		count = 0;
		pos = dlg.GetStartPosition();

		JNIControl * jni = new JNIControl();
		//월드 사전 생성 및 문서 사전 생성.
		while (pos) { //문서가 없을때까지 반복.
			CString* text;

			sfile = dlg.GetNextPathName(pos);
			sbuff = jni->extractNoun(sfile);

			if (sbuff == "") {
				AfxMessageBox("해당 파일 읽기 실패");
			}
			else {

				ClassifyMethod cm;
				cm.KeyPhrases(sbuff);//주제어 추출
				int index = cm.DICTIONARY.GetCount();//주제어 개수
				m_fileList.GetText(count, sbuff);
				cout << sbuff << "\nMaking document for classifing...\n";
				for (int i = 0; i < index; i++) {
					DOC[count].Storage(cm.DICTIONARY.GetAt(i), cm.DICNUM.GetAt(i));
					worldWS.Storage(cm.DICTIONARY.GetAt(i), cm.DICNUM.GetAt(i));
				}
			}
			count++;
		}
	}

	for (int i = 0; i < worldWS.GetCount(); i++) {
		sbuff.Format("%s : %d", worldWS.GetAtW(i), worldWS.GetAtN(i));
		m_WorldDictionary += sbuff + "\r\n";
	}

	sbuff.Format("%d", worldWS.GetCount());
	m_WorldDictionary += sbuff + "\r\n";

	UpdateData(false);
}


float CClusteringView::Sim(DocMat a, DocMat b) {
	float ABcount = 0;
	float BAcount = 0;
	float sim = 0;

	for (int i = 0; i < a.GetMatSize(); i++) {
		if (a.GetAt(i) + b.GetAt(i) != 0) {
			ABcount++;
		}
	}
	if (ABcount == 0) {
		sim = 0;
	}
	else {
		sim = ABcount / (float)(b.GetMatSize());
	}
	return sim;
}


//분류 버튼 클릭
void CClusteringView::OnBnClickedButton1()
{
	CString logForCheck = "";
	CString logBuff = "";

	int index = m_fileList.GetCount();

	UpdateData(true);
	m_ctlTree.DeleteAllItems();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxGetApp()->DoWaitCursor(-1);//마우스 커서 대기중에서 일반으로 변경
	CString sbuff = "";
	if (m_k == 0) {
		AfxMessageBox("군집 개수를 입력하세요");
		return;
	}

	//빈도수 확인을 위한 Log 처리
	for (int i = 0; i < m_fileList.GetCount(); i++) {
		DocMatrix[i].SetMatrix(worldWS, DOC[i]);
		logBuff.Format("%d", i);
		logForCheck += "Doc[" + logBuff + "] : ";
		m_fileList.GetText(i, logBuff);
		logForCheck += logBuff + "\r\n";
	}
	
////*****************Create Docmat for idf**********//////////
	UINT *idf = new UINT[worldWS.GetCount()];
	memset(idf,0,sizeof(int)*worldWS.GetCount());
	for(int i = 0; i < worldWS.GetCount(); i++){
		for(int j = 0; j < m_fileList.GetCount(); j++){
			if(DocMatrix[j].GetAt(i)>0) idf[i]++;
		}
	}

//////////////////////////
	logForCheck += "\r\n***********************************************************데이터(tf)***********************************************************\r\n";
	logForCheck += "\t\t\t";
	for (int i = 0; i < index; i++) {
		logBuff.Format("%d", i);
		logForCheck += "doc[" + logBuff + "]\t";
	}
	logForCheck += "idf\t";
	logForCheck += "TF";
	logForCheck += "\r\n";
	for (int i = 0; i < worldWS.GetCount(); i++) {
		logForCheck += worldWS.GetAtW(i);
		for (int tap = 0; tap < 3 - (worldWS.GetAtW(i).GetLength() / 8); tap++) {
			logForCheck += "\t";
		}

		for (int j = 0; j < index; j++) {
			if (DocMatrix[j].GetAt(i) == 0) {
				logBuff = "\t";
			}
			else {
				logBuff.Format("%.5f\t", DocMatrix[j].GetAt(i));
			}
			logForCheck += logBuff;
		}
		logBuff.Format("%d", idf[i]);
		logForCheck += logBuff + "\t";
		logBuff.Format("%d", worldWS.GetAtN(i));
		logForCheck += logBuff+"\r\n";
	}

	//tf*idf 가중치로 변환
	for (int i = 0; i < m_fileList.GetCount(); i++){
		DocMatrix[i].Changetotfidf(worldWS, m_fileList.GetCount(), idf);
	}

	logForCheck += "\r\n***********************************************************데이터(tf*idf)***********************************************************\r\n";
	logForCheck += "\t\t\t";
	for (int i = 0; i < index; i++) {
		logBuff.Format("%d", i);
		logForCheck += "doc[" + logBuff + "]\t";
	}
	//log

	logForCheck += "\r\n";
	for (int i = 0; i < worldWS.GetCount(); i++) {
		logForCheck += worldWS.GetAtW(i);
		for (int tap = 0; tap < 3 - (worldWS.GetAtW(i).GetLength() / 8); tap++) {
			logForCheck += "\t";
		}

		for (int j = 0; j < index; j++) {
			if (DocMatrix[j].GetAt(i) == 0) {
				logBuff = "\t";
			}
			else {
				logBuff.Format("%.5f\t", DocMatrix[j].GetAt(i));
			}
			logForCheck += logBuff;
		}

		logForCheck += "\r\n";
	}


	float test = 0;

	//k-meas군집화//////////////////////////////////
	int numOfK = m_k;//군집 개수
	float evaluateK = 0.0f;
	bool stop = true;

	DocMat* preK = nullptr; // 이전 군집화
	DocMat* sufK = nullptr; // 현재 군집화

	CUIntArray* preKgroup = nullptr;
	CUIntArray* sufKgroup = nullptr;


	do {
		//cout << "\n****************************K:" << numOfK << "***********************\n";
		preK = new DocMat[numOfK]; // 이전 군집
		sufK = new DocMat[numOfK]; // 현재 군집

		preKgroup = new CUIntArray[numOfK];
		sufKgroup = new CUIntArray[numOfK];

		//초기화
		for (int i = 0; i < numOfK; i++) {
			sufK[i].SetMatSize(worldWS.GetCount());
			preK[i].SetMatSize(worldWS.GetCount());
		}

		//랜덤 기준 설정..
		
		UINT* indforRandom = new UINT[numOfK];
		if (m_InitSeedSel == 0) indforRandom = SeedInit(index);
		else indforRandom = SeedInit_FarDist(index, DocMatrix);
		for (int i = 0; i < numOfK; i++) {
			preK[i].Append(DocMatrix[indforRandom[i]]);
		}
		//랜덤 기준점 완료//
		delete[] indforRandom;
		
		

		//처음 랜덤 기준점
		logForCheck += "\r\n***********************************************************처음 기준점(문서 중 랜덤)***********************************************************\r\n\t\t\t";
		for (int i = 0; i < numOfK; i++) {
			logBuff.Format("%d", i);
			logForCheck += "k[" + logBuff + "]\t";
		}
		logForCheck += "\r\n";
		for (int i = 0; i < worldWS.GetCount(); i++) {
			logForCheck += worldWS.GetAtW(i);
			for (int tap = 0; tap < 3 - (worldWS.GetAtW(i).GetLength() / 8); tap++) {
				logForCheck += "\t";
			}
			for (int j = 0; j < numOfK; j++) {
				if (preK[j].GetAt(i) == 0) logBuff = "\t";
				else logBuff.Format("%.5f\t", preK[j].GetAt(i));
				logForCheck += logBuff;
			}
			logForCheck += "\r\n";
		}

		//가까운 기준에 할당.
		bool Kstop = true;
		int round = 1;
		//라운드 넘어올떄 기준점 불안정
		do {
			float dist = 0.0f;
			float buffdist = 0.0f;
			UINT g_index = 0;

			//거리 검사 각 기준에
			for (int i = 0; i < index; i++) {
				dist = 0;
				dist = DocMatrix[i].Cosin(preK[0]);

				m_fileList.GetText(i, sbuff);
				g_index = 0;
				for (int j = 1; j < numOfK; j++) {
					buffdist = DocMatrix[i].Cosin(preK[j]);
					if (buffdist > dist) {
						dist = buffdist;
						buffdist = 0;
						//그룹에 현재문서 할당
						g_index = j;
					}
				}
				//그룹에 할당;
				sufKgroup[g_index].Add(i);

				buffdist = 0.0f;
				dist = 0.0f;
			}

			for (int i = 0; i < numOfK; i++) {
				cout << "*********group[" << i << "]***********\n";
				for (int j = 0; j < sufKgroup[i].GetCount(); j++) {
					m_fileList.GetText(sufKgroup[i].GetAt(j), sbuff);
					cout << sbuff << "\n";
				}
			}

			//기준점 재설정
			float hap = 0.0f;
			float buff = 0.0f;
			for (int i = 0; i < numOfK; i++) {
				//군집 개수 만큼 반복
				for (int w = 0; w < worldWS.GetCount(); w++) { //월드 단어 수 만큼 반복
					for (int j = 0; j < sufKgroup[i].GetCount(); j++) { //그룹 원소 수 만큼 반복 //각 단어의 평균 재설정
						hap += DocMatrix[sufKgroup[i].GetAt(j)].GetAt(w);
					}
					buff = hap / sufKgroup[i].GetCount();

					sufK[i].SetAt(w, buff);
					hap = 0;
					buff = 0.0f;
				}
			}

			//log
			logBuff.Format("%d", round);
			logForCheck += "\r\n***********************************************************[Round "+logBuff+"]기준점 재설정***********************************************************\r\n";
			for (int j = 0; j < numOfK; j++) {
				logForCheck += "\t\t\t";
				logBuff.Format("%d", j);
				logForCheck += "k[" + logBuff + "]\t";
				for (int k = 0; k < sufKgroup[j].GetCount(); k++) {
					logBuff.Format("%d", sufKgroup[j].GetAt(k));
					logForCheck += "Doc[" + logBuff + "]\t";
				}
				logForCheck += "\r\n";
				for (int i = 0; i < worldWS.GetCount(); i++) {
					if (sufK[j].GetAt(i) != 0) {
						logForCheck += worldWS.GetAtW(i);
						for (int tap = 0; tap < 3 - (worldWS.GetAtW(i).GetLength() / 8); tap++) {
							logForCheck += "\t";
							
						}
						logBuff.Format("%.5f", sufK[j].GetAt(i));
						logForCheck += logBuff + "\t";
						

						for (int k = 0; k < sufKgroup[j].GetCount(); k++) {
							if (DocMatrix[sufKgroup[j].GetAt(k)].GetAt(i) == 0) logBuff = "\t";
							else logBuff.Format("%.5f\t", DocMatrix[sufKgroup[j].GetAt(k)].GetAt(i));
							logForCheck += logBuff;
							
						}
						logForCheck += "\r\n";
					}
				}
				logForCheck += "***********************************************************\r\n\r\n";
			}
			
			Kstop = true;
			for (int i = 0; i < numOfK; i++) {
				if (Kcompare(preKgroup[i], sufKgroup[i]) == false) {
					Kstop = false;
					round++;
					for (int j = 0; j < numOfK; j++) {
						preK[j].Append(sufK[j]);
						preKgroup[j].RemoveAll();
						preKgroup[j].Append(sufKgroup[j]);
						sufKgroup[j].RemoveAll();
					}
					break;
				}
			}

		} while (Kstop==false);

		Savefile(logForCheck);
		/*
		//군집 평가  Dunn index = 가장 가까운 클러스터 거리/가장 먼 클러스터 내 데이터 거리
		float evaluateBuff1 = 0.0f;
		float minKDist = 0.0f;
		float maxDataDist = 0.0f;
		float evaluate = 0.0f;

		//가장 가까운 클러스터 거리 찾기;
		minKDist = sufK[0].Cosin(sufK[1]);
		for (int i = 0; i < numOfK; i++) {
			for (int j = 0; j < numOfK; j++) {
				if (i != j) {
					float minBuff = sufK[i].Cosin(sufK[j]);
					if (minKDist > minBuff) {
						minKDist = minBuff;
					}
				}
			}
		}
		//cout << "minKDist : " << minKDist << "\t";
		//클러스터내 데이터간 가장 먼 거리 찾기;
		maxDataDist = 0.0f;
		for (int i = 0; i < numOfK; i++) {
			for (int j = 0; j < sufKgroup[i].GetCount(); j++) {
				for (int l = 0; l < sufKgroup[i].GetCount(); l++) {
					if (j != l) {
						float maxBuff = DocMatrix[sufKgroup[i].GetAt(j)].Cosin(DocMatrix[sufKgroup[i].GetAt(l)]);
						if (maxDataDist < maxBuff) {
							maxDataDist = maxBuff;
						}
					}
				}
			}
		}
		//cout << "maxDataDist : " << maxDataDist << "\n";

		//각 군집의 디스턴스 평균 구하여 군집평가.
		float evaluateBuff2 = 0.0f;
		for (int i = 0; i < numOfK; i++) {
			for (int j = 0; j < sufKgroup[i].GetCount(); j++) {
				for (int l = 0; l < sufKgroup[i].GetCount(); l++) {
					if (l == j) continue;
					else {
						evaluateBuff2 += DocMatrix[sufKgroup[i].GetAt(j)].Cosin(DocMatrix[sufKgroup[i].GetAt(l)]);
					}
				}
			}
		}


		evaluateBuff1 = minKDist / maxDataDist;
		evaluateBuff2 = evaluateBuff2 / index;

		evaluate = evaluateBuff1;// / evaluateBuff2;
		//cout << "evaluateBuff1 : " << evaluateBuff1 << "\n";
		//cout << "evaluateBuff2 : " << evaluateBuff2 << "\n";
		//cout << "evaluatePRE : " << evaluateK << "\tevaluateSUF : " << evaluate << "\n";

		stop = true;
		if (numOfK == 2) {
			evaluateK = evaluate;
			delete[] preKgroup;
			preKgroup = new CUIntArray[numOfK];
			for (int j = 0; j < numOfK; j++) {
				preKgroup[j].Append(sufKgroup[j]);
			}
			numOfK++;
		}
		else {
			if (evaluateK >= evaluate) {
				stop = false;
			}
			else {
				if (numOfK == index) stop = false;
				else {
					evaluateK = evaluate;
					delete[] preKgroup;
					preKgroup = new CUIntArray[numOfK];
					for (int j = 0; j < numOfK; j++) {
						preKgroup[j].Append(sufKgroup[j]);
					}
					numOfK++;
					stop = true;
				}
			}
		}*/
	} while (false);//stop);
	
	HTREEITEM* hRoot = new HTREEITEM[numOfK];

	for (int i = 0; i < numOfK; i++) {
		sbuff.Format("%d", i);
		CString rootname = "k" + sbuff;
		hRoot[i] = m_ctlTree.InsertItem(rootname, 0/* nImage */, 1/* nSelectedImage */, TVI_ROOT, TVI_LAST);
		cout << "*********group[" << i << "]***********\n";
		for (int j = 0; j < sufKgroup[i].GetSize(); j++) {
			CString filename = "";
			m_fileList.GetText(sufKgroup[i].GetAt(j), filename);
			m_ctlTree.InsertItem(filename, 0, 0, hRoot[i], TVI_SORT);

			cout << sufKgroup[i].GetAt(j) << "\n";
		}
	}
	UpdateData(false);
}


void CClusteringView::OnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	m_KeyWord = "";
	char* buff;
	CString sbuff;
	int cur = m_fileList.GetCurSel();
	CString sfile;
	m_fileList.GetText(cur, sfile);

	CFile file;
	CFileException e;
	if (!file.Open(sfile, CFile::modeRead, &e)) {
		AfxMessageBox("해당 파일을 읽을 수 없습니다.");
	}
	else {
		buff = new char[file.GetLength() + 1];
		buff[file.GetLength()] = '\0';
		file.Read(buff, file.GetLength());
		file.Close();
		sbuff.Format("%s", buff);

		ClassifyMethod cm;

		cm.KeyPhrases(sbuff);
		int index = cm.DICTIONARY.GetCount();

		for (int i = 0; i < index; i++) {
			sbuff.Format("%d", cm.DICNUM.GetAt(i));
			m_KeyWord += cm.DICTIONARY.GetAt(i) + " : " + sbuff + "\r\n";
		}
	}
	UpdateData(false);
}

void CClusteringView::Savefile(CString text) {
	CUtilFunction util;
	CString extension = "*.txt|";
	CString filter = "Text File(*.txt)|*.txt|";

	util.SaveFileDialog(text, extension, filter);
}

bool CClusteringView::Kcompare(CUIntArray& a, CUIntArray& b) {
	bool comp = true;
	if (a.GetSize() == b.GetSize()) {
for (int i = 0; i < a.GetSize(); i++) {
	//cout << a.GetAt(i) << " : " << b.GetAt(i) << endl;
	if (a.GetAt(i) != b.GetAt(i)) {
		comp = false;
		break;
	}
}
	}
	else comp = false;
	return comp;
}

void CClusteringView::OnBnClickedButton2()
{
	//making *.cvs
	//.cvs 파일은 ,로 구분되는 dataset 이다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString buff = "";
	CString sbuff = "";
	UINT fileNum = m_fileList.GetCount();
	UINT wordNum = worldWS.GetCount();
	if (DocMatrix == NULL) {
		AfxMessageBox("문서를 입력하세요");
	}
	else {
		buff += "words\\documents";
		for (int i = 0; i < fileNum; i++) {
			buff += "," + files[i];
		}
		buff += "\n";
		for (int j = 0; j < wordNum; j++) {
			buff += worldWS.GetAtW(j);
			for (int i = 0; i < fileNum; i++) {
				sbuff.Format("%f", DocMatrix[i].GetAt(j));
				buff += "," + sbuff;
			}
			buff += "\r\n";
		}

		CUtilFunction util;
		util.SaveFileDialog(buff, "*.cvs|*.*|", "*.cvs|*.*|");
	}
}


UINT * CClusteringView::SeedInit(UINT numDoc) {
	UpdateData(true);

	UINT * seed = new UINT[m_k];
	UINT index = 0;
	auto sameK = Flag::notsame;

	while (index != m_k) {
		seed[index] = rand() & numDoc - 1;
		cout << "Seed[" << index << "]" << seed[index] << endl;
		sameK = Flag::notsame;
		for (int i = 0; i < index; i++) {
			if (index == i);
			if (seed[index] == seed[i]) {
				sameK = Flag::same;
				break;
			}
		}
		if (sameK == Flag::notsame) {
			index++;
		}
	}
	return seed;
}

UINT * CClusteringView::SeedInit_FarDist(UINT numDoc, DocMat * Doc_Matrix) {
	/*// 처음 기준점 설정
	// 첫 기준은 입력된 데이터중 랜덤으로 설정;
	// 두번째 기준부터는 현재 설정된 기준들에서 가장 먼 데이터를 기준으로 설정;
	// 거리는 코사인 유사도를 사용
	// 마지막 k 개의 기준이 결정되면
	// 다시 첫 기준점을 마지막에 설정된 기준에서 가장 먼 데이터를 기준으로 설정.
	*/
	UINT * seed = new UINT[m_k];
	srand((unsigned int)time(NULL));
	seed[0] = rand() & numDoc - 1;
	float distforstart = 2.0f * (float)numDoc;
	float fbuff = 0.0f;
	UINT indforstart = 0;
	//
	vector<UINT> vseed;
	vector<UINT> docindex(numDoc);
	for (int i = 0; i < docindex.size(); i++) {
		docindex[i] = i;
	}

	//첫 seed 랜덤 설정
	vseed.push_back(rand() & numDoc - 1);
	vector<UINT>::iterator it = docindex.begin();
	for (it; it != docindex.end(); it++) {
		if (*it == vseed.at(0)) {
			docindex.erase(it);
		}
	}

	for (int i = 1; i < m_k; i++) {
		vector<UINT>::iterator itbuff;
		UINT seedBuff = 0;
		//시그마(모든 기준점과 거리)
		//모든 기준점과의 거리가 가장 먼 문서를 초기 시드로 설정
		//(현재 있는 기준점들과 가장 다른 문서를 채택)
		for (it = docindex.begin(); it != docindex.end(); it++) {
			fbuff = 0.0f;
			for (int si = 0; si < i; si++) {
				fbuff += Doc_Matrix[*it].Cosin(Doc_Matrix[seed[si]]);
			}
			if (fbuff < distforstart) {
				distforstart = fbuff;
				seedBuff = *it;
				itbuff = it;
			}
		}
		vseed.push_back(seedBuff);
		docindex.erase(itbuff);
		cout << "seed[" << i << "]" << vseed[i] << endl;
	}

	//첫번째 랜덤으로 선택된 시드를 제외한 모든 시드로
	//다시 첫번째 시드를 찾는다.


	for (int i = 1; i < m_k; i++) {
		for (int j = 0; j < numDoc; j++) {
			fbuff = 0.0f;
			for (int si = 0; si < i; si++) {
				fbuff += Doc_Matrix[j].Cosin(Doc_Matrix[seed[si]]);
			}
			if (fbuff < distforstart) {
				distforstart = fbuff;
				indforstart = j;
			}
		}
		seed[i] = indforstart;

		cout << "seed[" << i << "]" << seed[i] << endl;
	}
	distforstart = 2.0f * (float)numDoc;
	fbuff = 0.0f;
	for (int i = 0; i < numDoc; i++) {
		for (int j = 1; j < m_k; j++) {
			fbuff += Doc_Matrix[i].Cosin(Doc_Matrix[seed[j]]);
		}
		if (fbuff < distforstart) {
			distforstart = fbuff;
			seed[0] = i;
		}
	}
	seed[0] = indforstart;
	cout << "seed[0] : " << seed[0] << endl;

	return seed;
}