#pragma once


// CNewSWFile 대화 상자입니다.

class CNewSWFile : public CDialogEx
{
	DECLARE_DYNAMIC(CNewSWFile)

public:
	CNewSWFile(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNewSWFile();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWSTOPWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_filename;
};
