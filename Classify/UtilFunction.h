
#pragma once
#include <direct.h>
#include <regex>
#include <string>
#include "stdafx.h"

using namespace std;

class CUtilFunction
{
public:
	CUtilFunction();
	~CUtilFunction();

public:
	void LoadSWPfile();
	void UpdateFile(CString filePath, CString text);
	void StopWordUpdate();
	void StdSWInit(CFile & stopwordfile);
	bool SaveFileDialog(CString text, CString extension, CString filter);
	CString OpenFileDialog(CString extension, CString filter);
	//CStringArray OpenMultiFileDialog(CString extenstion, CString filter);
};

