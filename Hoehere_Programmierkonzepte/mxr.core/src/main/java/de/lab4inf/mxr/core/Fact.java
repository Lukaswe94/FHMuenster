/*
 * Project: mxr.core-lib
 *
 * Copyright (c) 2020,  Prof. Dr. Nikolaus Wulff
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

package de.lab4inf.mxr.core;

/**
 * Common fact container interface for all generic MXR facts, providing signature and
 * arguments, implemented by various hidden x-dimensional FactxD classes.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
public interface Fact {
	/**
	 * Arguments of this fact container.
	 * 
	 * @return argument array
	 */
	@NonNull
	Object[] arguments();

	/**
	 * number of arguments of this fact container
	 * 
	 * @return in with dimension
	 */
	default int dimension() {
		return arguments().length;
	}

	/**
	 * Type signature of this fact container.
	 * 
	 * @return Class array with signature of the arguments
	 */
	@NonNull
	Class<?>[] signature();

}
