#pragma once


// CompareDlg ��ȭ �����Դϴ�.

class CompareDlg : public CDialog
{
	DECLARE_DYNAMIC(CompareDlg)

public:
	CompareDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CompareDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPAREDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_DocA;
	CString m_DocB;
	CString m_Common;
	CString m_StaticA;
	CString m_StaticB;
};
