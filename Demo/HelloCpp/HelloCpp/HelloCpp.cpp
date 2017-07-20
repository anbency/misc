#include <stdio.h>
#include <iostream>
#include <jni.h>
#include <stdlib.h>
#include <assert.h>
#include <Windows.h> 
/*
jstring stoJstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("java/lang/String");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}


char* jstringTostring(JNIEnv* env, jstring jstr)
{
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}
*/
int main()
{
	//����һ������ָ�룬��������ָ��JVM�е�JNI_CreateJavaVM����  
	typedef jint(WINAPI *PFunCreateJavaVM)(JavaVM **, void **, void *);

	JavaVMOption options[2];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;
	long status;
	jclass cls;
	jmethodID mid;
	jint square;
	jboolean jnot;
	jobject jobj;

	options[0].optionString = "-Djava.compiler=NONE";
	options[1].optionString = "-Djava.class.path=.;d:/test/Demo";
	//options[2].optionString = "-verbose:jni"; //���ڸ�������ʱ����Ϣ
	vm_args.version = JNI_VERSION_1_8; // JDK�汾��
	vm_args.nOptions = 2;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = JNI_TRUE;

	//����JVM.DLL��̬��  
	HINSTANCE hInstance = ::LoadLibrary(L"C:\\Program Files (x86)\\Java\\jdk1.8.0_111\\jre\\bin\\client\\jvm.dll");
	if (hInstance == NULL)
	{
		printf("LoadLibrary jvm.dll failed\n");
		return false;
	}
	else
	{
		printf("LoadLibrary jvm.dll success\n");
	}

	//ȡ�������JNI_CreateJavaVM����ָ��  
	PFunCreateJavaVM funCreateJavaVM = (PFunCreateJavaVM)::GetProcAddress(hInstance, "JNI_CreateJavaVM");
	//����JNI_CreateJavaVM���������  
	status = (*funCreateJavaVM)(&jvm, (void**)&env, &vm_args);


	//status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

	if (status != JNI_ERR) {
		printf("cool create java jvm success\n");
		cls = env->FindClass("CppInvokingJava");  // ���������ava��
		if (cls != 0) {
			printf("find java class success, haha\n");
			// ���캯��
			mid = env->GetMethodID(cls, "<init>", "()V");
			if (mid != 0) {
				jobj = env->NewObject(cls, mid);
				std::cout << "init ok" << std::endl;
			}

			// ����add����
			mid = env->GetStaticMethodID(cls, "add", "(II)I");
			if (mid != 0) {
				square = env->CallStaticIntMethod(cls, mid, 5, 5);
				std::cout << square << std::endl;
			}


			// ����judge����
			mid = env->GetMethodID(cls, "judge", "(Z)Z");
			if (mid != 0) {
				jnot = env->CallBooleanMethod(jobj, mid, 1);
				if (!jnot) std::cout << "Boolean ok" << std::endl;
			}
		}
		else {
			fprintf(stderr, "FindClass failed\n");
		}

		jvm->DestroyJavaVM();
		fprintf(stdout, "Java VM destory.\n");
		return 0;
	}
	else {
		printf("create java jvm fail\n");
		return -1;
	}
}
