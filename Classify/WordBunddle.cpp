#include "stdafx.h"
//#include "WordBunddle.h"

//�ܾ�� �ܾ� ������ ���� Ŭ����
WordBunddle::WordBunddle()
{
	//��ü ������ �ʱ�ȭ.
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

//������ �ϳ� �÷��ش�.
void WordBunddle::Numpp()
{
	WB.numOfWord++;
}

void WordBunddle::Remove() {
	WB.word = "";
	WB.numOfWord = NULL;
	delete this;
}

//�ܾ� ���� ��´�.
UINT WordBunddle::GetWordSize() {
	return WB.word.GetLength();
}



