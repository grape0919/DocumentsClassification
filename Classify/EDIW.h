#pragma once


// EDIW dialog

class EDIW : public CDialogEx
{
	DECLARE_DYNAMIC(EDIW)

public:
	EDIW(CWnd* pParent = NULL);   // standard constructor
	virtual ~EDIW();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void WikifileSelect();
	// 문서를 추출할 Wikipedia dataset file
	CStringArray wikiFP;
	afx_msg void SaveFolderSelect();
	CString saveFolder;
	afx_msg void OnBnClickedOk();
	// //불러올 파일 패스// //불러올 파일 패스
	CString lodeFiles;
};
