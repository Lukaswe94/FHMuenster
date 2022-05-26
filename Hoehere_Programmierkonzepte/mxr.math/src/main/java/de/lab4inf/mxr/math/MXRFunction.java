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

package de.lab4inf.mxr.math;

import java.util.Objects;
import java.util.function.Function;

import de.lab4inf.mxr.core.Nullable;

/**
 * MXR function interface.
 *
 * @author nwulff
 * @since  28.11.2021
 */
@FunctionalInterface
public interface MXRFunction extends Function<Double,Double>{
	/*
	 * @see @see java.util.function.Function#apply(java.lang.Object)
	 */
	@Override
	default Double apply(@Nullable Double x) {
		return eval(Objects.requireNonNull(x));
	}
	/**
	 * Functional interface method for a mathematical function calculating f(x).
	 * @param x argument
	 * @return f(x)
	 */
	double eval(double x);
}
