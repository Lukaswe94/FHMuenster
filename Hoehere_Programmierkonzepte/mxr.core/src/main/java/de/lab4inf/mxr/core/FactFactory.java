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
 * Factory to create generic facts.
 * 
 * @author nwulff
 *
 */
public final class FactFactory {
	/**
	 * No instances of utility class allowed.
	 */
	private FactFactory() {
	}

	/**
	 * Create a fact instance with many arguments of the same type.
	 * 
	 * @param <T> type of the facts
	 * @param va  variable arguments array
	 * @return Fact instance
	 */
	@SuppressWarnings("unchecked")
	@NonNull
	public static <T> FactVA<T> facts(@NonNull T... va) {
		return FactVA.fact(va);
	}

	/**
	 * Create a fact instance from one argument.
	 * 
	 * @param <U> type of the argument
	 * @param u   the argument
	 * @return Fact instance
	 */
	@NonNull
	public static <U> Fact1D<U> facts(@NonNull U u) {
		return Fact1D.fact(u);
	}

	/**
	 * Create a fact instance from two arguments of different type.
	 * 
	 * @param <U> type of the 1.st argument
	 * @param <V> type of the 2.nd argument
	 * @param u   1.st argument
	 * @param v   2.nd argument
	 * @return Fact instance
	 */
	@NonNull
	public static <U, V> Fact2D<U, V> facts(@NonNull U u, @NonNull V v) {
		return Fact2D.fact(u, v);
	}

	/**
	 * Create a fact instance from three arguments of different type.
	 * 
	 * @param <U> type of the 1.st argument
	 * @param <V> type of the 2.nd argument
	 * @param <W> type of the 3.rd argument
	 * @param u   1.st argument
	 * @param v   2.nd argument
	 * @param w   3.rd argument
	 * @return Fact instance
	 */
	@NonNull
	public static <U, V, W> Fact3D<U, V, W> facts(@NonNull U u, @NonNull V v, @NonNull W w) {
		return Fact3D.fact(u, v, w);
	}

	/**
	 * Create a fact instance from four arguments of different type.
	 * 
	 * @param <U> type of the 1.st argument
	 * @param <V> type of the 2.nd argument
	 * @param <W> type of the 3.rd argument
	 * @param <X> type of the 4.th argument
	 * @param u   1.st argument
	 * @param v   2.nd argument
	 * @param w   3.rd argument
	 * @param x   4.th argument
	 * @return Fact instance
	 */
	@NonNull
	public static <U, V, W, X> Fact4D<U, V, W, X> facts(@NonNull U u, @NonNull V v, @NonNull W w, @NonNull X x) {
		return Fact4D.fact(u, v, w, x);
	}
}
