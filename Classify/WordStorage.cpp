#include "stdafx.h"


WordStorage::WordStorage() :WBsize(0)
{
}

WordStorage::~WordStorage()
{
}

//wordBunbble 추가 (단어) 개수는 자동으로 1로 초기화됨.
void WordStorage::Add(CString word)
{
	if (GetCount() == 0) {
		storage = new wordBunddle[1];
		SetBunddle(0, word, 1);
		++WBsize;
	}
	else {
		wordBunddle* temp = new wordBunddle[GetCount()];
		for (int i = 0; i < GetCount(); i++) {
			temp[i].word = GetAtW(i);
			temp[i].numOfWord = GetAtN(i);
		}
		delete[] storage;

		WBsize++;
		storage = new wordBunddle[GetCount()];

		for (int i = 0; i < GetCount() - 1; i++) {
			SetBunddle(i, temp[i].word, temp[i].numOfWord);
		}
		SetBunddle(GetCount() - 1, word, 1);

		delete[] temp;
	}
	/*cout << "----------------add-----------------" << "\n";
	for (int i = 0; i < WBsize; i++) {
		cout << GetAtW(i) << " : " << GetAtN(i) << "\t";
		if (i % 10 == 9) {
			cout << "\n";
		}
	}
	cout << "\n";*/
}
void WordStorage::Add(CString word, UINT num)
{
	if (GetCount() == 0) {
		storage = new wordBunddle[1];
		SetBunddle(0, word, num);
		++WBsize;
	}
	else {
		wordBunddle* temp = new wordBunddle[GetCount()];
		for (int i = 0; i < GetCount(); i++) {
			temp[i].word = GetAtW(i);
			temp[i].numOfWord = GetAtN(i);
		}
		delete[] storage;

		WBsize++;
		storage = new wordBunddle[GetCount()];

		for (int i = 0; i < GetCount() - 1; i++) {
			SetBunddle(i, temp[i].word, temp[i].numOfWord);
		}
		SetBunddle(GetCount() - 1, word, num);

		delete[] temp;
	}
}
//중간에 데이터 넣기 (단어, 인덱스)
void WordStorage::Insert(CString word, UINT index)
{
	//int count = GetCount();
	wordBunddle* temp = new wordBunddle[GetCount()];
	for (int i = 0; i < WBsize; i++) {
		temp[i].word = GetAtW(i);
		temp[i].numOfWord = GetAtN(i);
	}

	delete[] storage;

	++WBsize;

	storage = new wordBunddle[GetCount()];

	for (int i = 0; i < index; i++) {
		SetBunddle(i, temp[i].word, temp[i].numOfWord);
	}
	SetBunddle(index, word, 1);

	for (int i = index + 1; i < WBsize; i++) {
		SetBunddle(i, temp[i - 1].word, temp[i - 1].numOfWord);
	}

	delete[] temp;

	/*cout << "----------------insert-----------------" << "\n";
	for (int i = 0; i < WBsize; i++) {
		cout << GetAtW(i) << " : " << GetAtN(i) << "\t";
		if (i % 10 == 9) {
			cout << "\n";
		}
	}
	cout << "\n";*/
}

//2진 탐색
int WordStorage::GetIndex(CString word) {
	UINT front = 0;
	UINT back = GetCount() - 1;
	UINT center = 0;

	if (back == -1) { //저장소에 단어가 없을때
		return -1;
	}
	else if (back == 0) { // 저장소에 단어가 하나 있을때.
		if (word.Compare(GetAtW(0)) == 0) return 0;
		else return -1;
	}
	else if (back > 0) {
		while (1) {
			if ((back - front) == 1) {
				if (word.Compare(GetAtW(back)) == 0) return back;
				else if (word.Compare(GetAtW(front)) == 0) return front;
				else return -1;
			}
			else {
				center = (UINT)((back - front) / 2) + front;
				if (word.Compare(GetAtW(center)) == 0) return center;
				else if (word.Compare(GetAtW(center)) > 0) {
					front = center;
				}
				else back = center;
			}
		}
	}
}

CString* WordStorage::GetPtr(CString word) {
	int index = GetIndex(word);
	if (index != -1) {
		return &(storage[index].word);
	}
	else return nullptr;
}

//인덱스의 단어를 반환한다.
CString WordStorage::GetAtW(UINT index) {
	return storage[index].word;
}
//인덱스의 단어개수를 반환한다.
UINT WordStorage::GetAtN(UINT index) {
	return storage[index].numOfWord;
}
void WordStorage::SetBunddle(UINT index, CString Word, UINT num) {
	storage[index].word = Word;
	storage[index].numOfWord = num;
}
UINT WordStorage::GetCount() {
	return WBsize;
}

//인덱스에 단어수를 +1한다.
void WordStorage::Numpp(UINT index) {
	storage[index].numOfWord++;
}

void WordStorage::Numpp(UINT index, UINT num) {
	storage[index].numOfWord += num;
}

/*-1 = Fail, 0 = Insert Or Add, 1 = Npp */
int WordStorage::Storage(CString word)
{
	//cout << text[j] << "************\n";
	UINT dicSize = GetCount();
	//만약 단어저장소에 단어가 하나도 없다면 그냥 단어추가.
	if (dicSize == 0) {
		Add(word);
		return 0;
	}
	//저장소에서 같은단어 찾기(있으면 개수 추가, 없으면 저장소에 추가)
	else {
		int indexS = GetIndex(word);
		if (indexS != -1) {
			//cout << indexS << "\n";
			Numpp(indexS);
			return 1;
		}
		else {
			for (int i = 0; i < dicSize; i++) {
				string wordindoc = GetAtW(i);
				int compare = wordindoc.compare(word);
				//삽입정렬 방식으로 단어추가.
				//단어 사전에서 큰단어부터 검사
				//만약 단어 사전의 단어가 검색단어보다 작아질때까지검사.
				//만약 작다면 이전 자리에 삽입.

				if (compare > 0) {
					Insert(word, i);
					return 0;
				}
				if (i == dicSize - 1) {
					Add(word);
					return 0;
				}

			}
		}
	}
	return -1;
}

int WordStorage::Storage(CString word, UINT num)
{
	//cout << text[j] << "************\n";
	UINT dicSize = GetCount();
	//만약 단어저장소에 단어가 하나도 없다면 그냥 단어추가.
	if (dicSize == 0) {
		Add(word, num);
		return 0;
	}
	//저장소에서 같은단어 찾기(있으면 개수 추가, 없으면 저장소에 추가)
	else {
		int indexS = GetIndex(word);
		if (indexS != -1) {
			//cout << indexS << "\n";
			Numpp(indexS, num);
			return 1;
		}
		else {
			for (int i = 0; i < dicSize; i++) {
				string wordindoc = GetAtW(i);
				int compare = wordindoc.compare(word);
				//삽입정렬 방식으로 단어추가.
				//단어 사전에서 큰단어부터 검사
				//만약 단어 사전의 단어가 검색단어보다 작아질때까지검사.
				//만약 작다면 이전 자리에 삽입.

				if (compare > 0) {
					Insert(word, i);
					Numpp(i, num - 1);
					return 0;
				}
				if (i == dicSize - 1) {
					Add(word, num);
					return 0;
				}

			}
		}
	}
	return -1;
}

UINT WordStorage::GetNumofWholeWord(){
	UINT num = 0;
	if(WBsize ==0) return 0;
	else {
		for(int i = 0; i < WBsize; i++){
			num += GetAtN(i);
		}
		return num;
	}
}