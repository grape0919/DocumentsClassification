#pragma once
class WordStorage : public WordBunddle
{
public:
	WordStorage();
	~WordStorage();

private:
	wordBunddle* storage;

public:
	UINT WBsize;
	void Add(CString word);
	void Add(CString word, UINT num);
	void Insert(CString word, UINT index);
	void SetBunddle(UINT index, CString Word, UINT num);
	int GetIndex(CString word);
	CString* GetPtr(CString word);

	CString GetAtW(UINT index);
	UINT GetAtN(UINT index);

	UINT GetCount();

	void Numpp(UINT index);

	void Numpp(UINT index, UINT num);

	int Storage(CString word);
	int Storage(CString word, UINT num);
	/*-1 = Fail, 0 = Insert Or Add, 1 = Npp */
	UINT GetNumofWholeWord();
};

