#include <jni.h>
#include "dialogc_PM_Parser.h"
#include "ParameterManager.h"

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseTitle
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_dialogc_PM_1Parser_parseTitle(JNIEnv *env, jobject object, jstring jfilename) {
	ParameterManager *param = NULL;
	FILE *fp = NULL;
	const char *filename;
	char *title = NULL;
	jstring jtitle = NULL;
	jclass exception = (*env)->FindClass(env, "java/lang/Exception");

	#ifdef _DEBUG_
	printf("parseTitle: starting\n");
	#endif

	filename = (*env)->GetStringUTFChars(env, jfilename, 0);

	fp = fopen(filename,"r");

	param = PM_create(1);
	if(param == NULL) {
		#ifdef _DEBUG_
		printf("parseTitle: PM_create failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "PM_create failure");
		return NULL;
	}

	PM_manage(param,"title",STRING_TYPE,1);

	if(!PM_parseFrom(param, fp, '#')) {
		#ifdef _DEBUG_
		printf("parseTitle: PM_parseFrom failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "Parse Error");
		return NULL;
	}

	fclose(fp);
	(*env)->ReleaseStringUTFChars(env, jfilename, filename);

	title = PM_getValue(param,"title").str_val;
	jtitle = (*env)->NewStringUTF(env, title);

	PM_destroy(param);

	#ifdef _DEBUG_
	printf("parseTitle: returning\n");
	#endif
	
	return jtitle;
}

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseFields
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_dialogc_PM_1Parser_parseFields(JNIEnv *env, jobject object, jstring jfilename) {
	ParameterManager *param = NULL;
	FILE *fp = NULL;
	const char *filename;

	int i = 0;
	int list_length = 0;
	char *current = NULL;
	jobjectArray jfields = NULL;
	ParameterList *fields;
	jclass exception = (*env)->FindClass(env, "java/lang/Exception");

	#ifdef _DEBUG_
	printf("parseFields called\n");
	#endif

	filename = (*env)->GetStringUTFChars(env, jfilename, 0);

	fp = fopen(filename,"r");

	param = PM_create(1);
	if(param == NULL) {
		#ifdef _DEBUG_
		printf("parseFields: PM_create failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "PM_create failure");
		return NULL;
	}

	PM_manage(param,"fields",LIST_TYPE,1);

	if(!PM_parseFrom(param, fp, '#')) {
		#ifdef _DEBUG_
		printf("parseFields: PM_parseFrom failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "Parse Error");
		return NULL;
	}

	(*env)->ReleaseStringUTFChars(env, jfilename, filename);

	fields = PM_getValue(param,"fields").list_val;

	list_length = PL_count(fields);

	jfields = (jobjectArray)(*env)->NewObjectArray(env, list_length, (*env)->FindClass(env,"java/lang/String"), (*env)->NewStringUTF(env, ""));

	while(current = PL_next(fields)) {
		(*env)->SetObjectArrayElement(env, jfields, i, (*env)->NewStringUTF(env, current));
		i++;
	}

	PM_destroy(param);
	fclose(fp);

	#ifdef _DEBUG_
	printf("parseFields: returning\n");
	#endif

	return jfields;
}

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseValues
 * Signature: (Ljava/lang/String;[Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_dialogc_PM_1Parser_parseValues(JNIEnv *env, jobject object, jstring jfilename, jobjectArray jfields) {
	ParameterManager *param = NULL;
	FILE *fp = NULL;
	const char *filename;

	int i = 0;
	int list_length = 0;
	char *current = NULL;
	char *value = NULL;
	jstring string;
	jobjectArray jvalues;
	jclass exception = (*env)->FindClass(env, "java/lang/Exception");

	#ifdef _DEBUG_
	printf("parseValues: called\n");
	#endif

	filename = (*env)->GetStringUTFChars(env, jfilename, 0);

	fp = fopen(filename,"r");


	list_length = (*env)->GetArrayLength(env, jfields);
	

	param = PM_create(list_length);
	if(param == NULL) {
		#ifdef _DEBUG_
		printf("parseValues: PM_create failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "PM_create failure");
		return NULL;
	}

	for(i = 0; i < list_length; i++) {
		string = (jstring) (*env)->GetObjectArrayElement(env, jfields, i);
		current = (*env)->GetStringUTFChars(env, string, 0);
		PM_manage(param,current,STRING_TYPE,1);				
		(*env)->ReleaseStringUTFChars(env, string, current);
	}	
	

	if(!PM_parseFrom(param, fp, '#')) {
		#ifdef _DEBUG_
		printf("parseValues: PM_parseFrom failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "Parse Error");
		return NULL;
	}

	fclose(fp);
	(*env)->ReleaseStringUTFChars(env, jfilename, filename);

	jvalues = (jobjectArray)(*env)->NewObjectArray(env, list_length, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env,""));

	for(i = 0; i < list_length; i++) {
		string = (jstring) (*env)->GetObjectArrayElement(env, jfields, i);
		current = (*env)->GetStringUTFChars(env, string, 0);
		
		(*env)->SetObjectArrayElement(env, jvalues, i, (*env)->NewStringUTF(env, value));

		(*env)->ReleaseStringUTFChars(env, string, current);
	}	

	PM_destroy(param);

	#ifdef _DEBUG_
	printf("parseValues: returning\n");
	#endif
	
	return jvalues;
}

/*
 * Class:     dialogc_PM_Parser
 * Method:    parseButtons
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_dialogc_PM_1Parser_parseButtons(JNIEnv *env, jobject object, jstring jfilename) {
	ParameterManager *param = NULL;
	FILE *fp = NULL;
	const char *filename;

	int i = 0;
	int list_length = 0;
	char *current = NULL;
	jobjectArray jbuttons = NULL;
	ParameterList *buttons = NULL;
	jclass exception = (*env)->FindClass(env, "java/lang/Exception");

	#ifdef _DEBUG_
	printf("parseButtons: called\n");
	#endif

	filename = (*env)->GetStringUTFChars(env, jfilename, 0);

	fp = fopen(filename,"r");

	param = PM_create(1);
	if(param == NULL) {
		#ifdef _DEBUG_
		printf("parseButtons: PM_create failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "PM_create failure");
		return NULL;
	}

	PM_manage(param,"buttons",LIST_TYPE,1);

	if(!PM_parseFrom(param, fp, '#')) {
		#ifdef _DEBUG_
		printf("parseButtons: PM_parseFrom failure\n");
		#endif

		(*env)->ThrowNew(env, exception, "Parse Error");
		return NULL;
	}

	(*env)->ReleaseStringUTFChars(env, jfilename, filename);

	buttons = PM_getValue(param,"buttons").list_val;

	list_length = PL_count(buttons);

	jbuttons = (jobjectArray)(*env)->NewObjectArray(env, list_length, (*env)->FindClass(env,"java/lang/String"), (*env)->NewStringUTF(env,""));

	while(current = PL_next(buttons)) {
		(*env)->SetObjectArrayElement(env, jbuttons, i, (*env)->NewStringUTF(env, current));
		i++;
	}

	PM_destroy(param);
	fclose(fp);

	#ifdef _DEBUG_
	printf("parseButtons: returning\n");
	#endif

	return jbuttons;
}



