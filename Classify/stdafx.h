
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.

#include <fstream>	//���� ������� ���� �������


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


#include <afxsock.h>            // MFC ���� Ȯ��


using namespace std;




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//��ó�� include
#include "ClassifyMethod.h"
#include "UtilFunction.h"
#include "WordBunddle.h"
#include "DDP.h"
#include "DDPDoc.h"
#include "DDPView.h"
#include "ClaByDDF.h"
#include "ClaByDDFDOC.h"
#include "ClaByDDFView.h"
#include "Classify.h"
#include "ClassifyDoc.h"
#include "ClassifyView.h"
#include "SWMDialog.h"
#include "Clustering.h"
#include "ClusteringDoc.h"
#include "ClusteringView.h"
#include "jni.h"
#include "jni_md.h"
#include <list>
#include <regex>
#include <iostream>
//���� ���� ����
//stopword ���� �ý���
extern CString * swfilename;
extern UINT numoffile;
extern CString * stopword;
extern UINT numofsw;
extern CStringArray worldDictionary;
extern CArray<UINT> worldDicNum;

/*extern JavaVMOption options;
extern JavaVMInitArgs vm_args;
extern JNIEnv * env;
extern JavaVM * jvm;
extern jclass cls;
extern jmethodID cls_constructor;
extern jobject obj;
extern jmethodID tagString;*/
//stopword ���ϵ��� �����Ű�� ���� ����


