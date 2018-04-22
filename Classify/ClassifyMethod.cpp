#include "stdafx.h"
//#include "ClassifyMethod.h"




/*클래스 생성자로 문서내의 Stopword를 제외한
모든 단어들을 추출하여 allWord에 저장 합니다.*/

//생성자
ClassifyMethod::ClassifyMethod(CString text)
{

	/*
	형태소 분석

	POSTagger 사용

	명사와 '.' 만 추출해서 사용
	*/
	//text = ExtractNouns(text);
	//AfxMessageBox(text);
	CMProcess(text);
}
//생성자
ClassifyMethod::ClassifyMethod() {

}
//소멸자
ClassifyMethod::~ClassifyMethod()
{

}

void ClassifyMethod::CMProcess(CString text) {

	//document = RemoveSW(text);
	document = text;
	//사용자 정의 함수 ExtractWord(CString * )을 이용하여
	//모든 단어 추출
	if (!document.IsEmpty()) {
		cout << _T("*********************[") << DOCUMENTNAME << _T("] 분석 시작*****************\n") << endl;

		allWord = ExtractWord(document);
		//모든단어의 크기 저장
		wordSize = size;
		//allWord = SortAllWord(allWord, wordSize);
		CompressNum(allWord, wordSize);
		//주제어 추출 사용자 정의 함수
		KeyPhrases(document);

		cout << _T("*********************분석 끝 [") << DOCUMENTNAME << _T("]*****************\n") << endl;
	}
}


//*추출한 모든 단어들을 단어와 누적수로 바꾼다.
void ClassifyMethod::CompressNum(CString * ExtractedWordSorted, UINT arrSize)
{
	CString* buffArr = NULL;
	int num = 1;
	numOfWord = 1;
	//모든 단어 개수 만큼 버퍼 생성
	buffArr = new CString[arrSize];
	//추출되어 정렬된 단어들을 버퍼에 입력
	buffArr = ExtractedWordSorted;

	//만약 단어들의 개수가 0개 또는 1개라면, 
	//단어들을 별도의 연산없이 바로 저장
	if (arrSize == 0 || arrSize == 1) {
		Word = new CString[arrSize];
		Word = buffArr;
		//numOfEachWord 각 단어의 빈도수를 저장하는 변수.
		numOfEachWord = new UINT[arrSize];
		numOfEachWord[0] = 1;
	}
	//단어의 개수가 0또는 1개가 아니라면,
	else {
		/*정렬된 단어를 순서대로 다음 단어와 비교.
		ex)
		aaa
		aaa
		bbb
		ccc
		ccc
		ccc
		...
		비교후 다를 때까지 빈도수를 세고
		다르면 단어와 빈도수를 저장.
		*/

		//중복되는 단어를 제외하고 단어의 개수를 센다.
		//다음 단어와 비교 후 다르면 단어 개수++.
		for (int i = 0; i < arrSize - 1; i++) {
			if (buffArr[i].Compare(buffArr[i + 1]) != 0) {
				numOfWord++;
			}
		}
		//단어 개수 만큼 메모리 할당
		Word = new CString[numOfWord];
		numOfEachWord = new UINT[numOfWord];

		//새로운 단어장의 인덱스
		int wordArrNum = 0;

		Word[wordArrNum] = buffArr[0];
		numOfEachWord[wordArrNum] = num;

		//다음단어비교를 순서대로 진행
		for (int i = 0; i < arrSize - 1; i++) {
			//만약 현재단어와 다음 단어가 같다면,
			//현재 단어의 빈도수++;
			if (buffArr[i].Compare(buffArr[i + 1]) == 0) {
				num++;
			}
			//현재단어와 다음 단어가 다르다면,
			else {
				//Word - 중복되는 단어들을 제외한 순수 단어장.
				//현재 단어를 단어장에 저장.
				Word[wordArrNum] = buffArr[i];
				//현재 단어의 빈도수 저장.
				numOfEachWord[wordArrNum] = num;
				//단어장 인덱스 ++
				wordArrNum++;
				//다음 단어의 빈도수 계산을 위해
				//빈도수를 1로 초기화
				num = 1;
			}
		}
		//만약 마지막 단어와 그 전 단어가 같다면,
		//단어장에 저장
		if (buffArr[arrSize - 2] == buffArr[arrSize - 1]) {
			Word[wordArrNum] = buffArr[arrSize - 1];
			numOfEachWord[wordArrNum] = num;
		}
		//만약 다르다면,
		//마지막 단어를 단어장에 추가.
		else {
			Word[wordArrNum] = buffArr[arrSize - 1];
			numOfEachWord[wordArrNum] = 1;
		}

		//빈도수로 SORT 한다.
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
/*단어들을 오름차순으로 정렬해준다.*/
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

/*입력된 단어가 stopword 인지 검사.
  bool 값 반환.*/
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

/*Stop word를 포함한 모든 단어들을 추출한다.*/
CString * ClassifyMethod::ExtractAllWord(CString text) {
	cout << _T("---------단어 추출 시작-------------") << endl;
	//초기화
	string buff = text;
	string matbuf;
	regex re(_T("[^\\W\\d]{2,}"));
	smatch match;
	CString * w;
	int count = 0;

	//단어 개수 세기
	//regex_search(저장할 변수, 버퍼, 정규식);
	//단어가 존재하지 않을때까지.
	while (regex_search(buff, match, re)) {
		count++;
		buff = match.suffix().str();
	}
	//단어 개수 만큼 메모리 할당
	w = new CString[count];
	buff = text;
	//정규식을 이용하여 단어 추출
	for (int i = 0; i < count; i++) {
		//정규식을 찾는 함수
		//regex_search(저장할 변수, 버퍼, 정규식);
		regex_search(buff, match, re);
		matbuf = match.str();
		transform(matbuf.begin(), matbuf.end(), matbuf.begin(), tolower);
		//찾은 단어 배열에 저장.
		w[i] = matbuf.c_str();
		buff = match.suffix().str();
	}
	w = SortAllWord(w, count);
	numOfWord = count;
	numofsw = count;
	cout << _T("--단어 개수 : ") << count << endl;
	return w;
}

/*문서에서 Stop word를 제외한 단어들을 추출하여
  그 배열을 CString 포인터로 반환합니다.*/
CString * ClassifyMethod::ExtractWord(CString text) {
	//cout << _T("---------단어 추출 시작-------------") << endl;
	//초기화
	string buff = text;
	regex re(_T("[^\\W\\d]{2,}"));
	smatch match;
	int count = 0;
	CString sbuff;
	CString * w = 0;
	//단어 개수를 센다.
	//regex_search(저장할 변수, 버퍼, 정규식);
	//단어가 존재하지 않을 때 까지.
	//count = 0;

	auto begin = sregex_iterator(buff.begin(), buff.end(), re);
	auto end = sregex_iterator();

	count = distance(begin, end);
	//cout << _T("--단어 개수 : ") << count << endl;
	/*

	while (regex_search(buff, match, re)) {
		///sbuff = match.str().c_str();
		///sbuff.MakeLower();
		///if (!isStopWord(sbuff)) {
			count++;
		///}
		buff = match.suffix().str();
	}*/
	//단어 개수만큼 메모리 할당
	w = new CString[count];
	//버퍼 초기화 = 문서;
	//buff = text;
	//단어를 찾아 저장
	for (int i = 0; i < count; i++) {
		//정규식을 이용하여 단어 추출
		//regex_search(저장할 변수, 버퍼, 정규식);
		regex_search(buff, match, re);
		sbuff = match.str().c_str();

		///sbuff.MakeLower();
		//stopword가 아니면 단어 저장
		//if (!isStopWord(sbuff)) {
		w[i] = sbuff;
		//cout << _T("[")<<i<< _T("] : ") << w[i] <<endl;
		//}
		//stopword면 단어배열[index--]
		//else i--;
		buff = match.suffix().str();

	}
	//정렬
	w = SortAllWord(w, count);
	size = count;

	return w;
}


/*주제어 추출
 (CStringArray * 반환으로 변환예정)*/
CString ** ClassifyMethod::KeyPhrases(CString text) {
	cout << "---------주제어 추출---------" << endl;
	//문장추출
	//전 문장의 단어들과 비교
	//두개 이상일 경우
	//단어 사전 구축
	//한문장에서 일치하는 단어 모두를 한쌍으로 봄
	//동시 출현 빈도에 따라
	//제일 높음 쌍을 주제어 집합.
	//단어 사전은 클러스터링에 사용됨


	//문장나누기//

	string buff = RemoveSW(text);

	//찾은 단어를 dictionary에 등록하기 위해 배열 위치 지정해주는 변수
	//또는 사전에 등록된 주제후보 개수를 세어줌.
	UINT dicCount = 0;
	regex re(_T("[\\.]"));
	///regex re("[.!?][\\s\\n\\(\\{\\<\\[]");
	smatch match;
	string sbuff;
	//문장개수
	UINT count = 0;
	CString * sentences = NULL;
	//. + 공백으로 문장을 구분한다.
	//문장 개수를 센다.
	/*while (regex_search(buff, match, re)) {
		count++;
		buff = match.suffix().str();
	}*/
	auto begin = sregex_iterator(buff.begin(), buff.end(), re);
	auto end = sregex_iterator();

	count = distance(begin, end);
	//cout << _T("문장개수 : ") << count << endl;
	//문장개수가 2개 이상이면 문장 비교.
	if (count > 1) {

		//문장 개수 만큼 배열 생성
		sentences = new CString[count];
		//buff = document;
		int i = 0;

		//문장 추출
		while (regex_search(buff, match, re)) {
			sentences[i] = match.prefix().str().c_str();
			//cout << _T("[") << i << _T("]") << sentences[i] << endl;
			buff = match.suffix().str();
			i++;
		}

		buff = _T("");

		//최대 dictionary 개수 설정
		if (count % 2 == 0) {
			dicSize = int(count / 2) * (count - 1);
		}
		else dicSize = int(count / 2) * count;
		//사전
		dictionary = new CStringArray[dicSize];

		//문장에서 단어 추출 
		//문장들과 비교
		CString ** buffWordPRE;
		CString * buffTest;

		buffWordPRE = new CString*[count];
		for (int i = 0; i <= count; i++) {
			buffWordPRE[i] = NULL;
		}

		//맨 뒷문장부터 검색 시작
		//5개의 문장 A, B, C, D, E 가 있다고 했을 때,
		//1ROUND E - D, C, B, A 비교
		//2ROUND D - C, B, A, (이미 E와는 비교함).
		//..
		//4ROUND B - A;


		//문장 비교 반복문을 위해 시작 문장 전처리(단어 추출)
		//단어 개수
		UINT * preSize = new UINT[count];

		regex resize(_T("[^\\W\\d]{2,}"));
		//현재 문장과 이전 문장들 비교
		UINT now = 0;
		sbuff = sentences[0];
		///buffWordPRE[0] = ExtractWord(sentences[0]);	//단어 개숫 세기 위함. this.size;
		auto begin = sregex_iterator(sbuff.begin(), sbuff.end(), resize);
		auto end = sregex_iterator();

		now = distance(begin, end);
		//cout << "문장[0]의 길이 : " << now << endl;

		//int t = buffTest.GetSize();
		buffWordPRE[0] = new CString[now];

		//이 전 문장의 단어 개수 
		preSize[0] = now;
		buffWordPRE[0] = ExtractWord(sentences[0]);

		for (int i = 1; i < count; i++) {
			sbuff = sentences[i];
			auto begin = sregex_iterator(sbuff.begin(), sbuff.end(), resize);
			auto end = sregex_iterator();

			now = distance(begin, end);
			//cout << "문장[" << i << "]의 길이 : " << now << endl;
			///ExtractWord(sentences[i]);	//단어 개숫 세기 위함. this.size;
			buffWordPRE[i] = new CString[now];
			preSize[i] = now;
			buffWordPRE[i] = ExtractWord(sentences[i]);
			//printf("%d",size);

			//전 문장 들과 비교
			//cout << "++++[" << i << "]문장 기준 동시출현 단어 찾기++++" << endl;

			for (int j = i - 1; j >= 0; j--) {
				CStringArray DicBuff;	//동시 출현 단어를 임시 저장할 변수
				//단어들 비교 후 출연하는 단어 DicBuff에 저장
				//cout << "-[" << i << "]/[" << j << "]-" << endl;
				for (int com = 0; com < preSize[i]; com++) {
					for (int comwith = 0; comwith < preSize[j]; comwith++) {
						bool isExist = false; //찾은 단어가 버퍼에 이미 존재하는지 검사하기 위한 변수

						if (buffWordPRE[i][com].Compare(buffWordPRE[j][comwith]) == 0) {

							//DicBuff에 찾은 단어가 존재하는지 보고 단어를 추가하기 위해 비었는지 확인한다.
							//비어있으면 그냥 단어를 추가하고 비어있지 않다면 같은 단어가 존재하는지 확인한다.

							//int log = DicBuff.GetSize();
							if (DicBuff.GetSize() != 0) {
								//같은 단어가 있는지 검사
								for (int check = 0; check < DicBuff.GetSize(); check++) {
									//같은 단어가 존재한다면 isExist 를 통해 존재확인
									if (buffWordPRE[i][com].Compare(DicBuff[check]) == 0) {
										isExist = true;
										break;
									}
								}
								//단어가 존재 하지 않는다면
								if (isExist == false) {
									//버퍼에 저장
									DicBuff.Add(buffWordPRE[i][com]);
									//cout << buffWordPRE[i][com] << endl;
								}

							}

							//버퍼가 비어있다면 추가.
							else	DicBuff.Add(buffWordPRE[i][com]);

							break;
						}
					}
				}
				//찾은 단어들이 2개이상 존재한다면,
				//단어 사전에 등록
				//2개이상의 단어가 존재 한다면,
				//
				if (DicBuff.GetSize() >= 2) {
					//사전에 등록
					dictionary[dicCount].Append(DicBuff);
					//다음 단어 찾기를 위해 버퍼비우기
					DicBuff.RemoveAll();
					//다음 등록을 위해 배열 이동.
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

//사전 구성, 주제후보 출현 수
void ClassifyMethod::Dictionary() {
	//cout << "사전 정리" << endl;
	//사전 크기에 맞게 배열 생성.
	CStringArray* buffDIC = new CStringArray[dicSize];
	//DICNUM = new UINT[dicSize];
	UINT* dicnum = new UINT[dicSize];
	//DICTIONARY = new CStringArray[dicSize];
	//주제 후보가 등록되었는지 확인.
	if (dictionary == NULL) return;
	//존재한다면,
	else {
		CStringArray temp;
		//초기화
		for (int i = 0; i < dicSize; i++) {
			dicnum[i] = 0;
		}
		int dicindex = 0;
		int whereis = 0;
		bool excheck = true;
		//사전 구성
		//현재 단어가 사전에 등록되어있는지 검사하고 그 수 를 늘려준다.
		//단어 갯수가 같은 지 검사하고 같다면 단어가 같은지 검사.
		for (int i = 0; i < dicSize; i++) {
			excheck = true;
			//검색 대상 후보가 사전에 등록되어 있는지 검사.
			//첫번째 주제어	
			if (dicindex == 0) {
				buffDIC[0].Append(dictionary[i]);
				dicnum[0]++;
				dicindex++;
			}
			else {
				for (int ex = 0; ex < dicindex; ex++) {
					excheck = true;
					//주제어 개수가 맞는지 검사.
					//같다면 주제어 검사.
					if (buffDIC[ex].GetSize() == dictionary[i].GetSize()) {
						//주제어 검사.
						for (int exx = 0; exx < dictionary[i].GetSize(); exx++) {
							//같지 않다면/
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
			//사전에 주제어 후보가 존재하지 않다면 사전에 등록.


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

	//DICNUM 이 1이하이면 삭제
	//k = dicsize/2의 제곱근

	float k = 0;

	//dicSize = sqrt(dicSize / 2);

	//DICTIONARY.RemoveAll();
	if (dicSize == 0) {
		//추출된 단어가 없다면 문서의 모든 명사를 키워드로 사용.
		for (int j = 0; j < allWord->GetLength(); j++) {
			bool ex = false; //같은 단어 존재하는지 검사하기 위한 조건.
			for (int m = 0; m < DICTIONARY.GetCount(); m++) {
				//만약 같은 단어가 키워드 사전에 존재한다면 추가하지 않고 넘어가기.
				if (DICTIONARY.ElementAt(m) == allWord[j]) {
					ex = true;
					break;
				}
			}
			//만약 키워드 사전에 같은 단어가 존재하지 않는 다면 사전에 등록.
			if (ex == false) {
				DICTIONARY.Add(allWord[j]);
			}
		}
	}
	//만약 찾은 키워드가 존재한다면.
	else {
		//키워드가 사전에 같은 단어가 있는지 검사하고 등록
		for (int i = 0; i < dicSize; i++) {
			//키워드는 구 이므로 각 단어를 사전에 등록되어있는지 검사.
			for (int j = 0; j < buffDIC[i].GetCount(); j++) {
				bool ex = false; //사전에 존재 여부를 확인하는 조건.
				//사전에 등록되어있는지 검사.
				for (int m = 0; m < DICTIONARY.GetCount(); m++) {
					//만약 사전에 존재 한다면.
					if (DICTIONARY.ElementAt(m) == buffDIC[i].ElementAt(j)) {
						ex = true; //조건 변수를 true로.
						break;
					}
				}
				//만약 존재하지 않는 다면,
				if (ex == false) {
					//사전에 등록.
					DICTIONARY.Add(buffDIC[i].ElementAt(j));
					///try {
					DICNUM.Add(dicnum[i]);
					///}
					///catch (const exception& e) {
					///	AfxMessageBox(_T("예외처리"));
					///}
				}
			}
		}
	}
	//쓰지 않는 전역변수 null처리.
	//dicnum = NULL;
	delete dicnum;

	cout << "주제어 : " << DICTIONARY.GetCount() << "\n";
	//가중치 처리

	/*--------------아직 구현 안된 tf-idf 로 대체할 예정.------------------------------------
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

//정규식 앞문장 얻기
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

//정규식 뒷문장 얻기
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

//정규식과 맞는 문장 얻기
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

	//regex_search(저장할 변수, 버퍼, 정규식);
	//찾는 단어가 존재하지 않을 때 까지.
	//문서에서의 불용어 제거
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
		return "JVM 생성 실패\n";
	jclass string_class = env->FindClass("java/lang/String");
	jclass task2_class = NULL;
	jmethodID task2_method = NULL;
	jobjectArray task2_param = NULL;

	return "";
}*/
