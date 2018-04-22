#pragma once


// CompareDlg 대화 상자입니다.

class CompareDlg : public CDialog
{
	DECLARE_DYNAMIC(CompareDlg)

public:
	CompareDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CompareDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPAREDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_DocA;
	CString m_DocB;
	CString m_Common;
	CString m_StaticA;
	CString m_StaticB;
};
