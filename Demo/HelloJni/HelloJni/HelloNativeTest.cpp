/*
@version 1.10 2016-10-25
@author pxhero
*/

#include "HelloNativeTest.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_HelloNativeTest_greeting(JNIEnv *env, jobject obj)
{
	printf("Hello Native World!\n");
}