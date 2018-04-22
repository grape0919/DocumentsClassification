#include "stdafx.h"
//#include "ClassifyMethod.h"




/*Ŭ���� �����ڷ� �������� Stopword�� ������
��� �ܾ���� �����Ͽ� allWord�� ���� �մϴ�.*/

//������
ClassifyMethod::ClassifyMethod(CString text)
{

	/*
	���¼� �м�

	POSTagger ���

	���� '.' �� �����ؼ� ���
	*/
	//text = ExtractNouns(text);
	//AfxMessageBox(text);
	CMProcess(text);
}
//������
ClassifyMethod::ClassifyMethod() {

}
//�Ҹ���
ClassifyMethod::~ClassifyMethod()
{

}

void ClassifyMethod::CMProcess(CString text) {

	//document = RemoveSW(text);
	document = text;
	//����� ���� �Լ� ExtractWord(CString * )�� �̿��Ͽ�
	//��� �ܾ� ����
	if (!document.IsEmpty()) {
		cout << _T("*********************[") << DOCUMENTNAME << _T("] �м� ����*****************\n") << endl;

		allWord = ExtractWord(document);
		//���ܾ��� ũ�� ����
		wordSize = size;
		//allWord = SortAllWord(allWord, wordSize);
		CompressNum(allWord, wordSize);
		//������ ���� ����� ���� �Լ�
		KeyPhrases(document);

		cout << _T("*********************�м� �� [") << DOCUMENTNAME << _T("]*****************\n") << endl;
	}
}


//*������ ��� �ܾ���� �ܾ�� �������� �ٲ۴�.
void ClassifyMethod::CompressNum(CString * ExtractedWordSorted, UINT arrSize)
{
	CString* buffArr = NULL;
	int num = 1;
	numOfWord = 1;
	//��� �ܾ� ���� ��ŭ ���� ����
	buffArr = new CString[arrSize];
	//����Ǿ� ���ĵ� �ܾ���� ���ۿ� �Է�
	buffArr = ExtractedWordSorted;

	//���� �ܾ���� ������ 0�� �Ǵ� 1�����, 
	//�ܾ���� ������ ������� �ٷ� ����
	if (arrSize == 0 || arrSize == 1) {
		Word = new CString[arrSize];
		Word = buffArr;
		//numOfEachWord �� �ܾ��� �󵵼��� �����ϴ� ����.
		numOfEachWord = new UINT[arrSize];
		numOfEachWord[0] = 1;
	}
	//�ܾ��� ������ 0�Ǵ� 1���� �ƴ϶��,
	else {
		/*���ĵ� �ܾ ������� ���� �ܾ�� ��.
		ex)
		aaa
		aaa
		bbb
		ccc
		ccc
		ccc
		...
		���� �ٸ� ������ �󵵼��� ����
		�ٸ��� �ܾ�� �󵵼��� ����.
		*/

		//�ߺ��Ǵ� �ܾ �����ϰ� �ܾ��� ������ ����.
		//���� �ܾ�� �� �� �ٸ��� �ܾ� ����++.
		for (int i = 0; i < arrSize - 1; i++) {
			if (buffArr[i].Compare(buffArr[i + 1]) != 0) {
				numOfWord++;
			}
		}
		//�ܾ� ���� ��ŭ �޸� �Ҵ�
		Word = new CString[numOfWord];
		numOfEachWord = new UINT[numOfWord];

		//���ο� �ܾ����� �ε���
		int wordArrNum = 0;

		Word[wordArrNum] = buffArr[0];
		numOfEachWord[wordArrNum] = num;

		//�����ܾ�񱳸� ������� ����
		for (int i = 0; i < arrSize - 1; i++) {
			//���� ����ܾ�� ���� �ܾ ���ٸ�,
			//���� �ܾ��� �󵵼�++;
			if (buffArr[i].Compare(buffArr[i + 1]) == 0) {
				num++;
			}
			//����ܾ�� ���� �ܾ �ٸ��ٸ�,
			else {
				//Word - �ߺ��Ǵ� �ܾ���� ������ ���� �ܾ���.
				//���� �ܾ �ܾ��忡 ����.
				Word[wordArrNum] = buffArr[i];
				//���� �ܾ��� �󵵼� ����.
				numOfEachWord[wordArrNum] = num;
				//�ܾ��� �ε��� ++
				wordArrNum++;
				//���� �ܾ��� �󵵼� ����� ����
				//�󵵼��� 1�� �ʱ�ȭ
				num = 1;
			}
		}
		//���� ������ �ܾ�� �� �� �ܾ ���ٸ�,
		//�ܾ��忡 ����
		if (buffArr[arrSize - 2] == buffArr[arrSize - 1]) {
			Word[wordArrNum] = buffArr[arrSize - 1];
			numOfEachWord[wordArrNum] = num;
		}
		//���� �ٸ��ٸ�,
		//������ �ܾ �ܾ��忡 �߰�.
		else {
			Word[wordArrNum] = buffArr[arrSize - 1];
			numOfEachWord[wordArrNum] = 1;
		}

		//�󵵼��� SORT �Ѵ�.
		CString Stemp = _T("");
		int numTemp = 0;
		for (int i = 0; i < numOfWord; i++) {
			for (int j = 0; j < numOfWord; j++) {
				if (numOfEachWord[i] > numOfEachWord[j]) {

					Stemp = Word[i];
					numTemp = numOfEachWord[i];

					Word[i] = Word[j];
					numOfEachWord[i] = numOfEachWord[j];

					Word[j] = Stemp;
					numOfEachWord[j] = numTemp;
				}
			}
		}

	}
}
/*�ܾ���� ������������ �������ش�.*/
CString* ClassifyMethod::SortAllWord(CString * ExtractedWord, UINT arrSize)
{
	CString temp = _T("");
	if (arrSize == 0 || arrSize == 1) {
		return ExtractedWord;
	}
	else {
		for (int i = 0; i < arrSize; i++) {
			for (int j = 0; j < arrSize; j++) {
				if (ExtractedWord[i] < ExtractedWord[j]) {
					temp = ExtractedWord[i];
					ExtractedWord[i] = ExtractedWord[j];
					ExtractedWord[j] = temp;
				}
			}
		}
	}
	return ExtractedWord;
}

/*�Էµ� �ܾ stopword ���� �˻�.
  bool �� ��ȯ.*/
bool ClassifyMethod::isStopWord(CString word)
{
	bool issw = false;

	if (word >= stopword[(numofsw / 2)]) {
		if (word >= stopword[(numofsw / 4) * 3]) {
			for (int i = ((numofsw / 4) * 3); i < numofsw; i++) {
				if (word.Compare(stopword[i]) == 0) {
					issw = true;
					break;
				}
			}
		}
		else {
			for (int i = (numofsw / 2); i < ((numofsw / 4) * 3); i++) {
				if (word.Compare(stopword[i]) == 0) {
					issw = true;
					break;
				}
			}
		}
	}
	else {
		if (word >= stopword[(numofsw / 4)]) {
			for (int i = (numofsw / 4); i < (numofsw / 2); i++) {
				if (word.Compare(stopword[i]) == 0) {
					issw = true;
					break;
				}
			}
		}
		else {
			for (int i = 0; i < (numofsw / 4); i++) {
				if (word.Compare(stopword[i]) == 0) {
					issw = true;
					break;
				}
			}
		}
	}/*
	for (int i = 0; i < numofsw; i++) {
		if (word.Compare(stopword[i]) == 0) {
			issw = true;
			break;
		}
	}
	*/


	return issw;
}

/*Stop word�� ������ ��� �ܾ���� �����Ѵ�.*/
CString * ClassifyMethod::ExtractAllWord(CString text) {
	cout << _T("---------�ܾ� ���� ����-------------") << endl;
	//�ʱ�ȭ
	string buff = text;
	string matbuf;
	regex re(_T("[^\\W\\d]{2,}"));
	smatch match;
	CString * w;
	int count = 0;

	//�ܾ� ���� ����
	//regex_search(������ ����, ����, ���Խ�);
	//�ܾ �������� ����������.
	while (regex_search(buff, match, re)) {
		count++;
		buff = match.suffix().str();
	}
	//�ܾ� ���� ��ŭ �޸� �Ҵ�
	w = new CString[count];
	buff = text;
	//���Խ��� �̿��Ͽ� �ܾ� ����
	for (int i = 0; i < count; i++) {
		//���Խ��� ã�� �Լ�
		//regex_search(������ ����, ����, ���Խ�);
		regex_search(buff, match, re);
		matbuf = match.str();
		transform(matbuf.begin(), matbuf.end(), matbuf.begin(), tolower);
		//ã�� �ܾ� �迭�� ����.
		w[i] = matbuf.c_str();
		buff = match.suffix().str();
	}
	w = SortAllWord(w, count);
	numOfWord = count;
	numofsw = count;
	cout << _T("--�ܾ� ���� : ") << count << endl;
	return w;
}

/*�������� Stop word�� ������ �ܾ���� �����Ͽ�
  �� �迭�� CString �����ͷ� ��ȯ�մϴ�.*/
CString * ClassifyMethod::ExtractWord(CString text) {
	//cout << _T("---------�ܾ� ���� ����-------------") << endl;
	//�ʱ�ȭ
	string buff = text;
	regex re(_T("[^\\W\\d]{2,}"));
	smatch match;
	int count = 0;
	CString sbuff;
	CString * w = 0;
	//�ܾ� ������ ����.
	//regex_search(������ ����, ����, ���Խ�);
	//�ܾ �������� ���� �� ����.
	//count = 0;

	auto begin = sregex_iterator(buff.begin(), buff.end(), re);
	auto end = sregex_iterator();

	count = distance(begin, end);
	//cout << _T("--�ܾ� ���� : ") << count << endl;
	/*

	while (regex_search(buff, match, re)) {
		///sbuff = match.str().c_str();
		///sbuff.MakeLower();
		///if (!isStopWord(sbuff)) {
			count++;
		///}
		buff = match.suffix().str();
	}*/
	//�ܾ� ������ŭ �޸� �Ҵ�
	w = new CString[count];
	//���� �ʱ�ȭ = ����;
	//buff = text;
	//�ܾ ã�� ����
	for (int i = 0; i < count; i++) {
		//���Խ��� �̿��Ͽ� �ܾ� ����
		//regex_search(������ ����, ����, ���Խ�);
		regex_search(buff, match, re);
		sbuff = match.str().c_str();

		///sbuff.MakeLower();
		//stopword�� �ƴϸ� �ܾ� ����
		//if (!isStopWord(sbuff)) {
		w[i] = sbuff;
		//cout << _T("[")<<i<< _T("] : ") << w[i] <<endl;
		//}
		//stopword�� �ܾ�迭[index--]
		//else i--;
		buff = match.suffix().str();

	}
	//����
	w = SortAllWord(w, count);
	size = count;

	return w;
}


/*������ ����
 (CStringArray * ��ȯ���� ��ȯ����)*/
CString ** ClassifyMethod::KeyPhrases(CString text) {
	cout << "---------������ ����---------" << endl;
	//��������
	//�� ������ �ܾ��� ��
	//�ΰ� �̻��� ���
	//�ܾ� ���� ����
	//�ѹ��忡�� ��ġ�ϴ� �ܾ� ��θ� �ѽ����� ��
	//���� ���� �󵵿� ����
	//���� ���� ���� ������ ����.
	//�ܾ� ������ Ŭ�����͸��� ����


	//���峪����//

	string buff = RemoveSW(text);

	//ã�� �ܾ dictionary�� ����ϱ� ���� �迭 ��ġ �������ִ� ����
	//�Ǵ� ������ ��ϵ� �����ĺ� ������ ������.
	UINT dicCount = 0;
	regex re(_T("[\\.]"));
	///regex re("[.!?][\\s\\n\\(\\{\\<\\[]");
	smatch match;
	string sbuff;
	//���尳��
	UINT count = 0;
	CString * sentences = NULL;
	//. + �������� ������ �����Ѵ�.
	//���� ������ ����.
	/*while (regex_search(buff, match, re)) {
		count++;
		buff = match.suffix().str();
	}*/
	auto begin = sregex_iterator(buff.begin(), buff.end(), re);
	auto end = sregex_iterator();

	count = distance(begin, end);
	//cout << _T("���尳�� : ") << count << endl;
	//���尳���� 2�� �̻��̸� ���� ��.
	if (count > 1) {

		//���� ���� ��ŭ �迭 ����
		sentences = new CString[count];
		//buff = document;
		int i = 0;

		//���� ����
		while (regex_search(buff, match, re)) {
			sentences[i] = match.prefix().str().c_str();
			//cout << _T("[") << i << _T("]") << sentences[i] << endl;
			buff = match.suffix().str();
			i++;
		}

		buff = _T("");

		//�ִ� dictionary ���� ����
		if (count % 2 == 0) {
			dicSize = int(count / 2) * (count - 1);
		}
		else dicSize = int(count / 2) * count;
		//����
		dictionary = new CStringArray[dicSize];

		//���忡�� �ܾ� ���� 
		//������ ��
		CString ** buffWordPRE;
		CString * buffTest;

		buffWordPRE = new CString*[count];
		for (int i = 0; i <= count; i++) {
			buffWordPRE[i] = NULL;
		}

		//�� �޹������ �˻� ����
		//5���� ���� A, B, C, D, E �� �ִٰ� ���� ��,
		//1ROUND E - D, C, B, A ��
		//2ROUND D - C, B, A, (�̹� E�ʹ� ����).
		//..
		//4ROUND B - A;


		//���� �� �ݺ����� ���� ���� ���� ��ó��(�ܾ� ����)
		//�ܾ� ����
		UINT * preSize = new UINT[count];

		regex resize(_T("[^\\W\\d]{2,}"));
		//���� ����� ���� ����� ��
		UINT now = 0;
		sbuff = sentences[0];
		///buffWordPRE[0] = ExtractWord(sentences[0]);	//�ܾ� ���� ���� ����. this.size;
		auto begin = sregex_iterator(sbuff.begin(), sbuff.end(), resize);
		auto end = sregex_iterator();

		now = distance(begin, end);
		//cout << "����[0]�� ���� : " << now << endl;

		//int t = buffTest.GetSize();
		buffWordPRE[0] = new CString[now];

		//�� �� ������ �ܾ� ���� 
		preSize[0] = now;
		buffWordPRE[0] = ExtractWord(sentences[0]);

		for (int i = 1; i < count; i++) {
			sbuff = sentences[i];
			auto begin = sregex_iterator(sbuff.begin(), sbuff.end(), resize);
			auto end = sregex_iterator();

			now = distance(begin, end);
			//cout << "����[" << i << "]�� ���� : " << now << endl;
			///ExtractWord(sentences[i]);	//�ܾ� ���� ���� ����. this.size;
			buffWordPRE[i] = new CString[now];
			preSize[i] = now;
			buffWordPRE[i] = ExtractWord(sentences[i]);
			//printf("%d",size);

			//�� ���� ��� ��
			//cout << "++++[" << i << "]���� ���� �������� �ܾ� ã��++++" << endl;

			for (int j = i - 1; j >= 0; j--) {
				CStringArray DicBuff;	//���� ���� �ܾ �ӽ� ������ ����
				//�ܾ�� �� �� �⿬�ϴ� �ܾ� DicBuff�� ����
				//cout << "-[" << i << "]/[" << j << "]-" << endl;
				for (int com = 0; com < preSize[i]; com++) {
					for (int comwith = 0; comwith < preSize[j]; comwith++) {
						bool isExist = false; //ã�� �ܾ ���ۿ� �̹� �����ϴ��� �˻��ϱ� ���� ����

						if (buffWordPRE[i][com].Compare(buffWordPRE[j][comwith]) == 0) {

							//DicBuff�� ã�� �ܾ �����ϴ��� ���� �ܾ �߰��ϱ� ���� ������� Ȯ���Ѵ�.
							//��������� �׳� �ܾ �߰��ϰ� ������� �ʴٸ� ���� �ܾ �����ϴ��� Ȯ���Ѵ�.

							//int log = DicBuff.GetSize();
							if (DicBuff.GetSize() != 0) {
								//���� �ܾ �ִ��� �˻�
								for (int check = 0; check < DicBuff.GetSize(); check++) {
									//���� �ܾ �����Ѵٸ� isExist �� ���� ����Ȯ��
									if (buffWordPRE[i][com].Compare(DicBuff[check]) == 0) {
										isExist = true;
										break;
									}
								}
								//�ܾ ���� ���� �ʴ´ٸ�
								if (isExist == false) {
									//���ۿ� ����
									DicBuff.Add(buffWordPRE[i][com]);
									//cout << buffWordPRE[i][com] << endl;
								}

							}

							//���۰� ����ִٸ� �߰�.
							else	DicBuff.Add(buffWordPRE[i][com]);

							break;
						}
					}
				}
				//ã�� �ܾ���� 2���̻� �����Ѵٸ�,
				//�ܾ� ������ ���
				//2���̻��� �ܾ ���� �Ѵٸ�,
				//
				if (DicBuff.GetSize() >= 2) {
					//������ ���
					dictionary[dicCount].Append(DicBuff);
					//���� �ܾ� ã�⸦ ���� ���ۺ���
					DicBuff.RemoveAll();
					//���� ����� ���� �迭 �̵�.
					dicCount++;
				}
			}
		}
		for (int d = 0; d < dicCount + 1; d++) {
			dictionary[d].FreeExtra();
		}
		dicSize = dicCount;
		Dictionary();

		return buffWordPRE;
	}
	else {
		return nullptr;
	}

}

//���� ����, �����ĺ� ���� ��
void ClassifyMethod::Dictionary() {
	//cout << "���� ����" << endl;
	//���� ũ�⿡ �°� �迭 ����.
	CStringArray* buffDIC = new CStringArray[dicSize];
	//DICNUM = new UINT[dicSize];
	UINT* dicnum = new UINT[dicSize];
	//DICTIONARY = new CStringArray[dicSize];
	//���� �ĺ��� ��ϵǾ����� Ȯ��.
	if (dictionary == NULL) return;
	//�����Ѵٸ�,
	else {
		CStringArray temp;
		//�ʱ�ȭ
		for (int i = 0; i < dicSize; i++) {
			dicnum[i] = 0;
		}
		int dicindex = 0;
		int whereis = 0;
		bool excheck = true;
		//���� ����
		//���� �ܾ ������ ��ϵǾ��ִ��� �˻��ϰ� �� �� �� �÷��ش�.
		//�ܾ� ������ ���� �� �˻��ϰ� ���ٸ� �ܾ ������ �˻�.
		for (int i = 0; i < dicSize; i++) {
			excheck = true;
			//�˻� ��� �ĺ��� ������ ��ϵǾ� �ִ��� �˻�.
			//ù��° ������	
			if (dicindex == 0) {
				buffDIC[0].Append(dictionary[i]);
				dicnum[0]++;
				dicindex++;
			}
			else {
				for (int ex = 0; ex < dicindex; ex++) {
					excheck = true;
					//������ ������ �´��� �˻�.
					//���ٸ� ������ �˻�.
					if (buffDIC[ex].GetSize() == dictionary[i].GetSize()) {
						//������ �˻�.
						for (int exx = 0; exx < dictionary[i].GetSize(); exx++) {
							//���� �ʴٸ�/
							if (buffDIC[ex].GetAt(exx).Compare(dictionary[i].GetAt(exx)) != 0) {
								excheck = false;
								break;
							}
						}
						if (excheck == true)
						{
							whereis = ex;
							break;
						}
					}
					else {
						excheck = false;
					}
				}
				if (excheck == false) {
					buffDIC[dicindex].Append(dictionary[i]);
					dicnum[dicindex]++;
					dicindex++;
				}
				else {
					dicnum[whereis]++;
				}
			}
			//������ ������ �ĺ��� �������� �ʴٸ� ������ ���.


		}
		dicSize = dicindex;

	}
	delete[] dictionary;
	CStringArray temp;
	UINT itemp;
	//sort
	for (int i = 0; i < dicSize - 1; i++) {
		for (int j = i + 1; j < dicSize; j++) {
			if (dicnum[i] < dicnum[j]) {
				itemp = dicnum[i];
				dicnum[i] = dicnum[j];
				dicnum[j] = itemp;

				temp.Append(buffDIC[i]);
				buffDIC[i].RemoveAll();
				buffDIC[i].Append(buffDIC[j]);

				buffDIC[j].RemoveAll();
				buffDIC[j].Append(temp);

				temp.RemoveAll();
			}
		}
	}

	//DICNUM �� 1�����̸� ����
	//k = dicsize/2�� ������

	float k = 0;

	//dicSize = sqrt(dicSize / 2);

	//DICTIONARY.RemoveAll();
	if (dicSize == 0) {
		//����� �ܾ ���ٸ� ������ ��� ��縦 Ű����� ���.
		for (int j = 0; j < allWord->GetLength(); j++) {
			bool ex = false; //���� �ܾ� �����ϴ��� �˻��ϱ� ���� ����.
			for (int m = 0; m < DICTIONARY.GetCount(); m++) {
				//���� ���� �ܾ Ű���� ������ �����Ѵٸ� �߰����� �ʰ� �Ѿ��.
				if (DICTIONARY.ElementAt(m) == allWord[j]) {
					ex = true;
					break;
				}
			}
			//���� Ű���� ������ ���� �ܾ �������� �ʴ� �ٸ� ������ ���.
			if (ex == false) {
				DICTIONARY.Add(allWord[j]);
			}
		}
	}
	//���� ã�� Ű���尡 �����Ѵٸ�.
	else {
		//Ű���尡 ������ ���� �ܾ �ִ��� �˻��ϰ� ���
		for (int i = 0; i < dicSize; i++) {
			//Ű����� �� �̹Ƿ� �� �ܾ ������ ��ϵǾ��ִ��� �˻�.
			for (int j = 0; j < buffDIC[i].GetCount(); j++) {
				bool ex = false; //������ ���� ���θ� Ȯ���ϴ� ����.
				//������ ��ϵǾ��ִ��� �˻�.
				for (int m = 0; m < DICTIONARY.GetCount(); m++) {
					//���� ������ ���� �Ѵٸ�.
					if (DICTIONARY.ElementAt(m) == buffDIC[i].ElementAt(j)) {
						ex = true; //���� ������ true��.
						break;
					}
				}
				//���� �������� �ʴ� �ٸ�,
				if (ex == false) {
					//������ ���.
					DICTIONARY.Add(buffDIC[i].ElementAt(j));
					///try {
					DICNUM.Add(dicnum[i]);
					///}
					///catch (const exception& e) {
					///	AfxMessageBox(_T("����ó��"));
					///}
				}
			}
		}
	}
	//���� �ʴ� �������� nulló��.
	//dicnum = NULL;
	delete dicnum;

	cout << "������ : " << DICTIONARY.GetCount() << "\n";
	//����ġ ó��

	/*--------------���� ���� �ȵ� tf-idf �� ��ü�� ����.------------------------------------
	float weight = DICTIONARY.GetCount();
	DICWEIGHT = new float[weight];
	for (int i = 0; i < weight; i++) {
		for (int j = 0; j < numOfWord; j++) {
			if (DICTIONARY.ElementAt(i).Compare(Word[j]) == 0) {
				DICWEIGHT[i] = (float)numOfEachWord[j] / (float)wordSize;
				break;
			}
		}
	}*/

}

//���Խ� �չ��� ���
string ClassifyMethod::Pref_regex(string buff, CString reg) {
	string pre = _T("");
	CString re = reg;
	regex regex(re);
	smatch match;

	if (regex_search(buff, match, regex)) {
		pre = match.prefix().str();
		return pre;
	}
	else return _T("");
}

//���Խ� �޹��� ���
string ClassifyMethod::Suff_regex(string buff, CString reg) {
	string suf = _T("");
	CString re = reg;
	regex regex(re);
	smatch match;

	if (regex_search(buff, match, regex)) {
		suf = match.suffix().str();
		return suf;
	}
	else return _T("");
}

//���Խİ� �´� ���� ���
string ClassifyMethod::Match_regex(string buff, CString reg) {
	string mat = _T("");
	CString re = reg;
	regex regex(re);
	smatch match;

	if (regex_search(buff, match, regex)) {
		mat = match.str();
		return mat;
	}
	else return _T("");
}

CString ClassifyMethod::RemoveSW(CString text) {
	string buff = text;
	CString document = _T("");
	regex re(_T("([^\\W]{2,})|([.])"));
	smatch match;
	int count = 0;
	CString sbuff;
	//CString * w;

	//regex_search(������ ����, ����, ���Խ�);
	//ã�� �ܾ �������� ���� �� ����.
	//���������� �ҿ�� ����
	while (regex_search(buff, match, re)) {
		sbuff = match.str().c_str();
		sbuff.MakeLower();
		if (!isStopWord(sbuff)) {
			document += sbuff;
			document += _T(" ");
		}
		buff = match.suffix().str();
	}
	return document;
}

/*
CString ClassifyMethod::ExtractNouns(CString document) {
	JNIEnv* env = NULL;
	JavaVM* jvm = NULL;

	env = Create_VM(&jvm);
	if (env == NULL)
		return "JVM ���� ����\n";
	jclass string_class = env->FindClass("java/lang/String");
	jclass task2_class = NULL;
	jmethodID task2_method = NULL;
	jobjectArray task2_param = NULL;

	return "";
}*/
