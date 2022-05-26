/*
 * Project: mxr.core
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
 * Exception to be thrown by Mops instances and MXR containers when no solution or solver exists.
 * @author nwulff
 * @since 10.10.2021
 */
public class NoSolutionException extends RuntimeException {
	private static final long serialVersionUID = -7993181211221162197L;

	/**
	 * constructor with a message for the reason.
	 * @param message reason of exception
	 */
	public NoSolutionException(@NonNull String message) {
		super(message);
	}

	/**
	 * constructor with a cause for this exception
	 * @param cause underlying reason of exception
	 */
	public NoSolutionException(@NonNull Throwable cause) {
		super(cause);
	}

	/**
	 * constructor with a message and cause for this exception
	 * @param message reason of exception
	 * @param cause underlying reason of exception
	 */
	public NoSolutionException(@NonNull String message, @NonNull Throwable cause) {
		super(message, cause);
	}
}
