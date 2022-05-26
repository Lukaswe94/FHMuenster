/*
 * Project: mxr.math
 *
 * Copyright (c) 2021,  Prof. Dr. Nikolaus Wulff
 * University of Applied Sciences, Muenster, Germany
 * Lab for computer sciences (Lab4Inf).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/**
 * Function.h
 *
 *  Created on: 29.11.2021
 *      Author: nwulff
 */

#ifndef SRC_MXR_MATH_CPP_FUNCTION_H_
#define SRC_MXR_MATH_CPP_FUNCTION_H_
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef double (*FctPointer)(double);
#ifdef __cplusplus
}
#endif
class Function {
private:
	FctPointer fp;
protected:
	Function() : fp(0) {};
public:
	Function(FctPointer ptr) : fp(ptr) {assert(fp!=0);}
	virtual ~Function() {};
	virtual double operator()(const double x) const {assert(fp!=0); return fp(x);}

};

#endif /* SRC_MXR_MATH_CPP_FUNCTION_H_ */
