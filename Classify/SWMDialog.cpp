// SWMDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
///#include "Classify.h"
///#include "SWMDialog.h"
#include "afxdialogex.h"

///#include "UtilFunction.h"
///#include "DDPView.h"
#include "EditSWFile.h"
// CSWMDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSWMDialog, CDialogEx)

CSWMDialog::CSWMDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SWMENAGE, pParent)
	, m_preView(_T(""))
{
	
}

CSWMDialog::~CSWMDialog()
{
}

void CSWMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_swList);
	DDX_Text(pDX, IDC_EDIT1, m_preView);

	
}


BEGIN_MESSAGE_MAP(CSWMDialog, CDialogEx)
ON_LBN_SELCHANGE(IDC_LIST1, &CSWMDialog::OnLbnSelchangeList1)
ON_BN_CLICKED(IDC_BUTTON1, &CSWMDialog::addStopWord)
ON_BN_CLICKED(IDC_BUTTON2, &CSWMDialog::DeleteStopword)
ON_BN_CLICKED(IDOK, &CSWMDialog::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON5, &CSWMDialog::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON4, &CSWMDialog::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON3, &CSWMDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSWMDialog �޽��� ó�����Դϴ�.




void CSWMDialog::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index;
	char* buff = nullptr;
	index = m_swList.GetCurSel();
	if (index != LB_ERR) {
		CString swfile;
		m_swList.GetText(index, swfile);

		swfile = "stopword\\sw\\" + swfile;

		CFile file;
		CFileException e;
		if (!file.Open(swfile, CFile::modeRead, &e)) {
			AfxMessageBox("stopword\\sw\\ �Ʒ� �ش� ������ �����ϴ�.");
		}
		else {
			buff = new char[file.GetLength() + 1];
			buff[file.GetLength()] = '\0';
			file.Read(buff, file.GetLength());

			swfile.Format("%s", buff);

			m_preView = swfile;
		}
	}
	UpdateData(false);
}


BOOL CSWMDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	listUpdate();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CSWMDialog::addStopWord()
{
	CFile stopwordfile;
	CFileException e;

	CFile copyfile;
	CString newfilename;
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!stopwordfile.Open("stopword\\stopword.swp", CFile::modeWrite, &e)) {
		AfxMessageBox("�⺻���� ���� \"stopword.swp\" �� �������� �ʽ��ϴ�.");
	}
	else {
		CString str = "Stop Word File(*.sw)|*.sw|";
		CFileDialog dlg(TRUE, "*.sw", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, str, this);
		/*CFileDialog dlg(TRUE = ����|FALSE = ����, �⺻Ȯ����(*.cpp ��), ��ȭ���� ��½� "�����̸�" Edit ��Ʈ�ѿ� ��µ� ���ϸ�, �ɼ�, �ҷ��� Ȯ����, ��ȭ������ �θ�������);
		//�ɼ�
		OFN_EXPLOPER			������ Ž���� ��Ÿ�Ϸ� ���
		OFN_ARROWMULTISELECT	������ �ѹ��� ������ ���� ����
		OFN_CREATEPROMPT		�������� �ʴ� ���ϸ��� �Է����� ��� ���� �����ϰڳĴ� �޽��� �ڽ� ���
		OFN_FILEMUSTEXIST		�������� �ʴ� ���ϸ��� �Է��� �� ������ ��
		OFN_HIDEREADONLY		�б����� ������ ������� ����
		OFN_LONGNAMES			�� ���� �̸� ���� ����
		OFN_OVERWRITEPROMPT		�����ϴ� ���ϸ��� �Է����� ��� ����ڳĴ� �޽��� �ڽ� ���
		OFN_PATHMUSTEXIST		�̹� �����ϴ� ���͸����� �Է�
		*/

		if (IDOK == dlg.DoModal()) {

			newfilename = dlg.GetFileName();
			newfilename += "\n";

			stopwordfile.SeekToEnd();
			stopwordfile.Write(newfilename, newfilename.GetLength());
			stopwordfile.Close();
			
			char * buff;

			copyfile.Open(dlg.GetPathName(), CFile::modeRead);

			CFileFind find;

			if (find.FindFile("stopword\\sw\\"+copyfile.GetFileName())) {
				AfxMessageBox("������ stopword ���� �� ���� �̸��� ������ �����մϴ�.");
			}
			else {
				stopwordfile.Open("stopword\\sw\\" + dlg.GetFileName(), CFile::modeCreate | CFile::modeWrite);

				buff = new char[copyfile.GetLength() + 1];
				buff[copyfile.GetLength()] = '\0';
				copyfile.Read(buff, copyfile.GetLength());

				stopwordfile.Write(buff, copyfile.GetLength());

				copyfile.Close();
				stopwordfile.Close();

				CUtilFunction util;
				util.StopWordUpdate();

				listUpdate();
			}
		}
	}
}

/* sw���� �����մϴ�.*/
void CSWMDialog::DeleteStopword()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = -1;
	CString buff= nullptr;
	index = m_swList.GetCurSel();
	int delArray = 0;

	//���õ� ����Ʈ �˻�
	//����Ʈ�� ���õ��� �ʾҴٸ� index�� -1 �̴�.
	if (index != -1) {
		CString delname;
		m_swList.GetText(index, delname);

		CFileFind find;
		
		if (find.FindFile("stopword\\sw\\" + delname)) {
			DeleteFile("stopword\\sw\\" + delname);
		}
		CString * newswfilename = new CString[numoffile - 1];
		int sizeofarr = 0;
		
		for (int i = 0; i < numoffile; i++) {
			if (strcmp(swfilename[i],delname)==0) {
				continue;
			}
			else {
				newswfilename[sizeofarr] = swfilename[i];
				sizeofarr++;
			}
		}

		swfilename = nullptr;
		swfilename = new CString[sizeofarr];

		for (int i = 0; i < sizeofarr; i++) {
			swfilename[i] = newswfilename[i];
		}
		numoffile = sizeofarr;

		//swp ���� ���ΰ�ħ
		CFile swp;
		DeleteFile("stopword\\stopword.swp");
		if (!swp.Open("stopword\\stopword.swp", CFile::modeCreate | CFile::modeReadWrite)){
			AfxMessageBox("swp���� ���ΰ�ħ ����");
		}
		else {
			for (int i = 0; i < numoffile; i++) {
				buff = swfilename[i] + "\n";
				swp.Write(buff, buff.GetLength());
			}
			swp.Close();
			listUpdate();
		}
	}
	else {
		AfxMessageBox("������ ������ �������ּ���.");
	}
}


void CSWMDialog::listUpdate() {
	m_swList.ResetContent();
	for (int i = 0; i < numoffile; i++)
	{
		m_swList.AddString(swfilename[i]);
	}
}

void CSWMDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CUtilFunction util;
	util.LoadSWPfile();
	CDialogEx::OnOK();
}


void CSWMDialog::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CUtilFunction util;
	util.LoadSWPfile();
	
}


void CSWMDialog::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = -1;
	index = m_swList.GetCurSel();
	CString editFile;
	CString sbuff;
	char * buff;

	CFile file;
	
	if (index != -1) {
		m_swList.GetText(index, editFile);

		if(!file.Open("stopword\\sw\\"+editFile, CFile::modeReadWrite)) {
			AfxMessageBox("sw ���� �ҷ����� ����");
		}
		else {
			buff = new char[file.GetLength() + 1];
			buff[file.GetLength()] = '\0';

			file.Read(buff, file.GetLength());
			file.Close();
			sbuff.Format("%s", buff);
			CEditSWFile dlg;
			dlg.DoModal(sbuff, editFile);
			OnLbnSelchangeList1();
		}
	}
	else {
		AfxMessageBox("������ ������ �������ּ���.");
	}
}



void CSWMDialog::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CEditSWFile newSWFile;
	newSWFile.DoModal();
	listUpdate();
}
