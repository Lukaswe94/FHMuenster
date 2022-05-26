#include "de_lab4inf_mxr_math_Differentiator.h"
#include "JNIFunction.h"
#include "Differentiator.h"

JNIEXPORT jdouble JNICALL Java_de_lab4inf_mxr_math_Differentiator_diff(JNIEnv *env, jclass c, jobject obj, jdouble x, jdouble eps)
{
	JNIFunction f = JNIFunction(env, obj);
	return differentiate(f, x, eps);
}
