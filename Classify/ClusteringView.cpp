// ClusteringView.cpp : ���� �����Դϴ�.
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


// CClusteringView �����Դϴ�.

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


// CClusteringView �޽��� ó�����Դϴ�.


void CClusteringView::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString extension = "*.txt|*.*|";
	CString filter = "Text File(*.txt)|*.txt|All File(*.*)|*.*|";

	//���� ����
	//CFile openFile;

	CString strFileList;
	CString sbuff;
	char * buff;

	POSITION pos;
	CFileDialog dlg(TRUE, extension, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, filter);
	//��Ƽ ���� �������� ���ֱ�
	const int c_cMaxFiles = 10000;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;

	dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);
	dlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (dlg.DoModal() == IDOK) {

		string sfile;
		int count = 0;
		AfxGetApp()->DoWaitCursor(1);//���콺 Ŀ�� ��������� ����

		//���� ���� ����
		pos = dlg.GetStartPosition();
		while (pos) {
			sfile = dlg.GetNextPathName(pos);
			CFileException e;
			CFile * filebuff = new CFile(sfile.c_str(), CFile::modeRead);
			files.push_back(filebuff->GetFileTitle());
			filebuff->Close();
			m_fileList.AddString(sfile.c_str());
		}
		//���� ���� ��ŭ �ܾ� ����Ұ�ü ����;
		count = m_fileList.GetCount();
		DOC = new WordStorage[count];
		DocMatrix = new DocMat[count];
		count = 0;
		pos = dlg.GetStartPosition();

		JNIControl * jni = new JNIControl();
		//���� ���� ���� �� ���� ���� ����.
		while (pos) { //������ ���������� �ݺ�.
			CString* text;

			sfile = dlg.GetNextPathName(pos);
			sbuff = jni->extractNoun(sfile);

			if (sbuff == "") {
				AfxMessageBox("�ش� ���� �б� ����");
			}
			else {

				ClassifyMethod cm;
				cm.KeyPhrases(sbuff);//������ ����
				int index = cm.DICTIONARY.GetCount();//������ ����
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


//�з� ��ư Ŭ��
void CClusteringView::OnBnClickedButton1()
{
	CString logForCheck = "";
	CString logBuff = "";

	int index = m_fileList.GetCount();

	UpdateData(true);
	m_ctlTree.DeleteAllItems();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//AfxGetApp()->DoWaitCursor(-1);//���콺 Ŀ�� ����߿��� �Ϲ����� ����
	CString sbuff = "";
	if (m_k == 0) {
		AfxMessageBox("���� ������ �Է��ϼ���");
		return;
	}

	//�󵵼� Ȯ���� ���� Log ó��
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
	logForCheck += "\r\n***********************************************************������(tf)***********************************************************\r\n";
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

	//tf*idf ����ġ�� ��ȯ
	for (int i = 0; i < m_fileList.GetCount(); i++){
		DocMatrix[i].Changetotfidf(worldWS, m_fileList.GetCount(), idf);
	}

	logForCheck += "\r\n***********************************************************������(tf*idf)***********************************************************\r\n";
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

	//k-meas����ȭ//////////////////////////////////
	int numOfK = m_k;//���� ����
	float evaluateK = 0.0f;
	bool stop = true;

	DocMat* preK = nullptr; // ���� ����ȭ
	DocMat* sufK = nullptr; // ���� ����ȭ

	CUIntArray* preKgroup = nullptr;
	CUIntArray* sufKgroup = nullptr;


	do {
		//cout << "\n****************************K:" << numOfK << "***********************\n";
		preK = new DocMat[numOfK]; // ���� ����
		sufK = new DocMat[numOfK]; // ���� ����

		preKgroup = new CUIntArray[numOfK];
		sufKgroup = new CUIntArray[numOfK];

		//�ʱ�ȭ
		for (int i = 0; i < numOfK; i++) {
			sufK[i].SetMatSize(worldWS.GetCount());
			preK[i].SetMatSize(worldWS.GetCount());
		}

		//���� ���� ����..
		
		UINT* indforRandom = new UINT[numOfK];
		if (m_InitSeedSel == 0) indforRandom = SeedInit(index);
		else indforRandom = SeedInit_FarDist(index, DocMatrix);
		for (int i = 0; i < numOfK; i++) {
			preK[i].Append(DocMatrix[indforRandom[i]]);
		}
		//���� ������ �Ϸ�//
		delete[] indforRandom;
		
		

		//ó�� ���� ������
		logForCheck += "\r\n***********************************************************ó�� ������(���� �� ����)***********************************************************\r\n\t\t\t";
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

		//����� ���ؿ� �Ҵ�.
		bool Kstop = true;
		int round = 1;
		//���� �Ѿ�Ë� ������ �Ҿ���
		do {
			float dist = 0.0f;
			float buffdist = 0.0f;
			UINT g_index = 0;

			//�Ÿ� �˻� �� ���ؿ�
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
						//�׷쿡 ���繮�� �Ҵ�
						g_index = j;
					}
				}
				//�׷쿡 �Ҵ�;
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

			//������ �缳��
			float hap = 0.0f;
			float buff = 0.0f;
			for (int i = 0; i < numOfK; i++) {
				//���� ���� ��ŭ �ݺ�
				for (int w = 0; w < worldWS.GetCount(); w++) { //���� �ܾ� �� ��ŭ �ݺ�
					for (int j = 0; j < sufKgroup[i].GetCount(); j++) { //�׷� ���� �� ��ŭ �ݺ� //�� �ܾ��� ��� �缳��
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
			logForCheck += "\r\n***********************************************************[Round "+logBuff+"]������ �缳��***********************************************************\r\n";
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
		//���� ��  Dunn index = ���� ����� Ŭ������ �Ÿ�/���� �� Ŭ������ �� ������ �Ÿ�
		float evaluateBuff1 = 0.0f;
		float minKDist = 0.0f;
		float maxDataDist = 0.0f;
		float evaluate = 0.0f;

		//���� ����� Ŭ������ �Ÿ� ã��;
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
		//Ŭ�����ͳ� �����Ͱ� ���� �� �Ÿ� ã��;
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

		//�� ������ ���Ͻ� ��� ���Ͽ� ������.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		AfxMessageBox("�ش� ������ ���� �� �����ϴ�.");
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
	//.cvs ������ ,�� ���еǴ� dataset �̴�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString buff = "";
	CString sbuff = "";
	UINT fileNum = m_fileList.GetCount();
	UINT wordNum = worldWS.GetCount();
	if (DocMatrix == NULL) {
		AfxMessageBox("������ �Է��ϼ���");
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
	/*// ó�� ������ ����
	// ù ������ �Էµ� �������� �������� ����;
	// �ι�° ���غ��ʹ� ���� ������ ���ص鿡�� ���� �� �����͸� �������� ����;
	// �Ÿ��� �ڻ��� ���絵�� ���
	// ������ k ���� ������ �����Ǹ�
	// �ٽ� ù �������� �������� ������ ���ؿ��� ���� �� �����͸� �������� ����.
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

	//ù seed ���� ����
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
		//�ñ׸�(��� �������� �Ÿ�)
		//��� ���������� �Ÿ��� ���� �� ������ �ʱ� �õ�� ����
		//(���� �ִ� ��������� ���� �ٸ� ������ ä��)
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

	//ù��° �������� ���õ� �õ带 ������ ��� �õ��
	//�ٽ� ù��° �õ带 ã�´�.


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