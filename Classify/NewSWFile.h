#pragma once


// CNewSWFile ��ȭ �����Դϴ�.

class CNewSWFile : public CDialogEx
{
	DECLARE_DYNAMIC(CNewSWFile)

public:
	CNewSWFile(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNewSWFile();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWSTOPWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_filename;
};
