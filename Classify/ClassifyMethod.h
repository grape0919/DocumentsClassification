#pragma once
#include "stdafx.h"
#include <string>
#include <regex>

class ClassifyMethod
{
public:
	

	CString * ExtractWord(CString text);
	CString * allWord = 0; //���ܾ�
	UINT wordSize = 0;	//��� �ܾ� ����

	CStringArray * dictionary = NULL; //��� ������ �ĺ��� �������
	

	CStringArray DICTIONARY; //�ߺ� ������ ���� �󵵼� üũ
	CUIntArray DICNUM;
	float * DICWEIGHT = NULL;
	UINT dicSize = 0;//���� ������

	UINT size = 0; //ũ�⸦ �����ϴ� ����

	CString DOCUMENTNAME = _T("");

	void CompressNum(CString * ExtractedWordSorted, UINT arrSize);

	CString *Word = NULL;//����� �ܾ�� �ߺ����� ����
	UINT *numOfEachWord = NULL;	//�� �ܾ���� �󵵼�

	UINT numOfWord = 0; //�ߺ����� �ܾ��� ����
	
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

