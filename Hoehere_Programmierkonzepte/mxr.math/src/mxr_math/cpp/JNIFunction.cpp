#include "JNIFunction.h"

JNIFunction::~JNIFunction(){}

JNIFunction::JNIFunction(JNIEnv* envir,jobject mxrFct)
{
	env = envir;
	mxrFunction = mxrFct;
	jclass clazz = env->GetObjectClass(mxrFunction);
	eval = env-> GetMethodID(clazz, "eval", "(D)D");
}

double JNIFunction::operator()(double x) const
{
	return env->CallDoubleMethod(mxrFunction, eval, x);
}
