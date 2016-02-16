/* filename:   dialogc_PM_Parser.h
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*2750
 * assignment: 3
 * 
 * This file contains JNI function declarations for interfacing between Java and libpm
 */

#include <jni.h>


#ifndef _Included_dialogc_PM_Parser
#define _Included_dialogc_PM_Parser
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseTitle
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_dialogc_PM_1Parser_parseTitle
  (JNIEnv *, jobject, jstring);

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseFieldNames
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_dialogc_PM_1Parser_parseFields
  (JNIEnv *, jobject, jstring);

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseButtonNames
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_dialogc_PM_1Parser_parseButtons
  (JNIEnv *, jobject, jstring);

 /*
 * Class:     dialogc_PM_Parser
 * Method:    parseFieldValues
 * Signature: (Ljava/lang/String;[Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_dialogc_PM_1Parser_parseValues
  (JNIEnv *, jobject, jstring, jobjectArray);

 

#ifdef __cplusplus
}
#endif
#endif
