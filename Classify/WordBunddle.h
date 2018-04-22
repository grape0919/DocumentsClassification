#pragma once
class WordBunddle
{
public:
	typedef struct wordBunddle {
		CString word;
		UINT numOfWord;
	}wordBunddle;
	
	wordBunddle WB;

	WordBunddle();
	WordBunddle(CString word, UINT num);
	~WordBunddle();

	void SetBunddle(CString word, UINT num);
	void SetWord(CString word);
	void SetNum(UINT num);

	CString GetWord();
	UINT GetNum();
	void Numpp();
	void Remove();
	UINT GetWordSize();
};

