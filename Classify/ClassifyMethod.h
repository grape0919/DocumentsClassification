#pragma once
#include "stdafx.h"
#include <string>
#include <regex>

class ClassifyMethod
{
public:
	

	CString * ExtractWord(CString text);
	CString * allWord = 0; //모든단어
	UINT wordSize = 0;	//모든 단어 개수

	CStringArray * dictionary = NULL; //모든 주제어 후보가 들어있음
	

	CStringArray DICTIONARY; //중복 주제어 제거 빈도수 체크
	CUIntArray DICNUM;
	float * DICWEIGHT = NULL;
	UINT dicSize = 0;//사전 사이즈

	UINT size = 0; //크기를 저장하는 버퍼

	CString DOCUMENTNAME = _T("");

	void CompressNum(CString * ExtractedWordSorted, UINT arrSize);

	CString *Word = NULL;//추출된 단어들 중복없이 저장
	UINT *numOfEachWord = NULL;	//각 단어들의 빈도수

	UINT numOfWord = 0; //중복없는 단어의 개수
	
	CString* SortAllWord(CString * ExtractedWord, UINT arrSize);
	
	bool isStopWord(CString word);

	CString * ExtractAllWord(CString text);
	CString ** KeyPhrases(CString text);
	void Dictionary();

	string Pref_regex(string buff, CString reg);

	string Suff_regex(string buff, CString reg);

	string Match_regex(string buff, CString reg);

	CString RemoveSW(CString text);

public:

	ClassifyMethod(CString text);
	ClassifyMethod();
	~ClassifyMethod();

	void CMProcess(CString text);

protected:
	CString document = _T("");

	
};

