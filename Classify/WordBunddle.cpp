#include "stdafx.h"
//#include "WordBunddle.h"

//단어와 단어 갯수를 갖는 클래스
WordBunddle::WordBunddle()
{
	//객체 생성시 초기화.
	SetNum(NULL);
	SetWord(NULL);
}

WordBunddle::WordBunddle(CString word, UINT num) 
{
///	WB.word = new CString(word);
	SetWord(word);
	SetNum(num);
}

WordBunddle::~WordBunddle()
{
}

void WordBunddle::SetBunddle(CString word, UINT num)
{
	SetWord(word);
	SetNum(num);
}

void WordBunddle::SetWord(CString word)
{
	///WB.word = new CString(word);
	WB.word = word;
}

void WordBunddle::SetNum(UINT num)
{
	WB.numOfWord = num;
}

CString WordBunddle::GetWord()
{
	return WB.word;
}

UINT WordBunddle::GetNum()
{
	return WB.numOfWord;
}

//개수를 하나 늘려준다.
void WordBunddle::Numpp()
{
	WB.numOfWord++;
}

void WordBunddle::Remove() {
	WB.word = "";
	WB.numOfWord = NULL;
	delete this;
}

//단어 길이 얻는다.
UINT WordBunddle::GetWordSize() {
	return WB.word.GetLength();
}



