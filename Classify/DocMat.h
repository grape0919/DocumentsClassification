#pragma once
#include "WordStorage.h"
class DocMat
{
private:
	float* docmatrix;
public:
	DocMat();
	~DocMat();
	UINT MatSize = 0;
	UINT NumOfWholeWord = 0;
	float GetAt(UINT);
	UINT GetMatSize();

	void SetMatSize(UINT size);

	void SetAt(UINT, float);
	void SetMatrix(WordStorage world, WordStorage doc);

	float Dist(DocMat);
	float Cosin(DocMat a);
	void Append(DocMat);

	void ChangetoProb();

	void Changetotfidf(WordStorage Docs, short DocNum, UINT * idf);
	
};

