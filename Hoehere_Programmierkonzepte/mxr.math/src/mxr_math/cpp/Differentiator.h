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
 * Differentiator.h
 *
 *  Created on: 29.11.2021
 *      Author: nwulff
 */

#ifndef SRC_MXR_MATH_CPP_DIFFERENTIATOR_H_
#define SRC_MXR_MATH_CPP_DIFFERENTIATOR_H_
#include "Function.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * Differentiate the given function within eps precision at point x.
 */
double differentiate(Function &f, double x, double eps);

#ifdef __cplusplus
}
#endif

#endif /* SRC_MXR_MATH_CPP_DIFFERENTIATOR_H_ */
