#pragma once


// CEditSWFile ��ȭ �����Դϴ�.

class CEditSWFile : public CDialogEx
{
	DECLARE_DYNAMIC(CEditSWFile)

public:
	CEditSWFile(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEditSWFile();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EditSWdlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
