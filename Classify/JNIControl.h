#pragma once

class JNIControl
{
public:
	JNIControl();
	~JNIControl();

	const char* extractNoun(string doc);

	JavaVMOption options;
	JavaVMInitArgs vm_args;
	JNIEnv * env;
	JavaVM * jvm;
	jclass cls;
	jmethodID cls_constructor;
	jobject obj;
	jmethodID tagString;
};

