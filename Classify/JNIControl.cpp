#include "stdafx.h"
#include "JNIControl.h"

JNIControl::JNIControl()
{
	
	//JVM ����
	//options.optionString = "-Djava.class.path=./stanford-postagger.jar";
	options.optionString = "-Djava.class.path=./preprocessor.jar";
	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 1;
	vm_args.options = &options;
	vm_args.ignoreUnrecognized = 0;

	long status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	if (status !=  0) {
		AfxMessageBox("Unable to Launch JVM");
	}
	else {
		cout << ("Create VM") << endl;
		//Ŭ���� ã��
		cls = env->FindClass("com/cd/preprocess/TaggerForCD");
		if (cls == 0) {
			AfxMessageBox("Failed finding class");
		}
		else
		{
			cout << "Maxent Tagger Load : " << cls << endl;
		}
		
		//������ ã��
		cls_constructor = env->GetMethodID(cls, "<init>", "()V");
		if (cls_constructor == NULL) {
			AfxMessageBox("Failed finding constructor");
			return;
		}
		else {
			cout << "Constructor ID : " << cls_constructor << endl;
		}
		//��ü ����
		obj = env->NewObject(cls, cls_constructor, "()V");
		cout << "Create object : " << obj << endl;
		
		//Method ã��
		tagString = env->GetMethodID(cls, "extractNoun", "(Ljava/lang/String;)Ljava/lang/String;");
		if (tagString == NULL) {
			AfxMessageBox("Failed finding method");
		}
		else {
			cout << "test ID : " << tagString << endl;
		}
	}
}


JNIControl::~JNIControl()
{
}

const char* JNIControl::extractNoun(string docpath) {

	//tagString�� parameter�� �Էµ� arg ����
	jstring arg1 = env->NewStringUTF(docpath.c_str());
	//cout << "arg1 : " << arg1 << endl;

	//�޼ҵ� ȣ��
	//CallObjectMethod(��ü, �޼ҵ�, �μ�1);
	jstring ar = (jstring)env->CallObjectMethod(obj, tagString, arg1);

	//jobject ���¸� jstring���� ��ȯ.
	const char * r = env->GetStringUTFChars(ar, 0);
	//cout << "r:" << r << endl;
	cout << "Extracting Noun in " << docpath << endl;
	//env->ReleaseStringUTFChars(ar, r);
	return r;
}