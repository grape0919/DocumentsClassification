#pragma once


// CEditSWFile 대화 상자입니다.

class CEditSWFile : public CDialogEx
{
	DECLARE_DYNAMIC(CEditSWFile)

public:
	CEditSWFile(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEditSWFile();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EditSWdlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit;
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal(CString text, CString filename);
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
	CString m_filename;
	int request;
	CString staBuff = "";
};
