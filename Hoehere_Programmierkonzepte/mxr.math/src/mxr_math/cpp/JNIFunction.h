/*
 * JNIFunction.h
 *
 *  Created on: 30.11.2021
 *      Author: nwulff
 */

#ifndef SRC_MXR_MATH_CPP_JNIFUNCTION_H_
#define SRC_MXR_MATH_CPP_JNIFUNCTION_H_
#include <jni.h>
#include "Function.h"

class JNIFunction: public Function {
private:
	JNIEnv   *env;
	jobject   mxrFunction;
	jmethodID eval;
public:
	/**
	 * Constructor to wrap a Java Function implementation.
	 * @param envir the JNI java virtual machine handle
	 * @param mxrFct the java MXRFunction reference
	 */
	JNIFunction(JNIEnv* envir,jobject mxrFct);
	virtual ~JNIFunction();
	// overload operator for java functions implementations.
	virtual double operator()(double x) const;
};


#endif /* SRC_MXR_MATH_CPP_JNIFUNCTION_H_ */
