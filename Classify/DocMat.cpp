#include "stdafx.h"


DocMat::DocMat()
{
}

DocMat::~DocMat()
{
}

float DocMat::GetAt(UINT index)
{
	return docmatrix[index];
}

void DocMat::SetMatrix(WordStorage world, WordStorage doc) {
	UINT count = world.GetCount();
	MatSize = count;
	docmatrix = new float[count];

	for (int i = 0; i < count; i++) {
		docmatrix[i] = 0;
	}

	count = doc.GetCount();

	for (int i = 0; i < count; i++) {
		int index = world.GetIndex(doc.GetAtW(i));
		docmatrix[index] = doc.GetAtN(i);
	}

	NumOfWholeWord = doc.GetNumofWholeWord();
	//Changetotf(world);
}

//두 문서간 유사도 측정.
//유클리드 거리 사용.
//tf*idf 가중치 사용
float DocMat::Dist(DocMat a)
{
	float dist = 0.0f;
	float doc_a = 0.0f;
	float doc_this = 0.0f;
	float buff = 0.0f;
	for (int i = 0; i < GetMatSize(); i++) {
		doc_a = a.GetAt(i);
		doc_this = GetAt(i);
		buff = doc_a - doc_this;
		dist += fabs(buff);//fabs(data); 절대값!
	}
	dist = dist / GetMatSize();
	return dist;
}

float DocMat::Cosin(DocMat doc) {
	UINT size = GetMatSize();
	float vectora = 0;
	float vectorb = 0;
	float innerab = 0;
	for (int i = 0; i < GetMatSize(); i++) {
		float a = GetAt(i);
		float b = doc.GetAt(i);

		vectora += a * a;
		vectorb += b * b;
		innerab += a * b;
	}
	//cout << "vector A : " << vectora << endl;
	//cout << "vector B : " << vectorb << endl;
	//cout << "inner AB : " << innerab << endl;
	float result = 0;
	result = innerab / (sqrt(vectora)*sqrt(vectorb));
	//cout << "inner AB / rute(vA)*rute(vB) = "<< result << endl;
	if (result == NAN) result = 0;
	return result;
}

UINT DocMat::GetMatSize()
{
	return MatSize;
}

//reset and set matrix size;
void DocMat::SetMatSize(UINT size)
{
	MatSize = size;
	docmatrix = new float[MatSize];
	for (int i = 0; i < GetMatSize(); i++) {
		docmatrix[i] = 0.0f;
	}
}

void DocMat::SetAt(UINT index, float num) {
	docmatrix[index] = num;
}

void DocMat::Append(DocMat doc) {
	if (GetMatSize() == doc.GetMatSize()) {
		for (int i = 0; i < doc.GetMatSize(); i++) {
			SetAt(i, doc.GetAt(i));
		}
	}
	else {
		SetMatSize(doc.GetMatSize());
		docmatrix = new float[doc.GetMatSize()];

		for (int i = 0; i < doc.GetMatSize(); i++) {
			SetAt(i, doc.GetAt(i));
		}
	}
}

void DocMat::ChangetoProb() {
	UINT hap = 0;
	float prob = 0.0f;
	//float test = 0.0f;
	for (int i = 0; i < GetMatSize(); i++) {
		hap += docmatrix[i];
	}
	for (int i = 0; i < GetMatSize(); i++) {
		float buff = (docmatrix[i] / hap);
		SetAt(i, buff);
		//test += buff;
	}
}

void DocMat::Changetotfidf(WordStorage Docs, short DocNum, UINT* df) {
	UINT wordNum = 0;
	UINT maxNum = 0;
	//문서내에서 가장 큰 빈도수 찾기
	for (int i = 0; i < this->GetMatSize(); i++) {
		UINT wa = GetAt(i);
		//wordNum+=wa;
		if (maxNum < wa) maxNum = wa;
	}
	//maxNum = maxNum / wordNum;
	for (int i = 0; i < GetMatSize(); i++) {
		float idf = 0.0f;
		float tf = GetAt(i);//문서내 단어 개수 
		float tfidf = 0.0f;
		short exist = 0;

		if (tf != 0) {
			tf = 0.5 + 0.5*tf/(float)maxNum;
			//tf = tf / (float)wordNum;
			idf = log10f((float)DocNum / (float)df[i])+1;
			tfidf = tf * idf + 1;
			SetAt(i, tfidf);
		}
	}
}
