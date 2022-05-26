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

import static java.lang.String.format;

import java.util.Arrays;
import java.util.Objects;

/**
 * Fact with many generic arguments of the same type T.
 * 
 * @author nwulff
 * @param <T> the tpye of alle elements to use.
 */
public class FactVA<T> implements Fact {
	/**
	 * no access to the immutable values to hold.
	 */
	@NonNull
	private final T[] args;
	@NonNull
	private final Class<T>[] signature;
	private String asString;

	/**
	 * Constructor with variable number of arguments of type T.
	 * 
	 * @param values of type T to hold
	 */
	@SuppressWarnings("unchecked")
	@SafeVarargs
	public FactVA(@Nullable T... values) {
		args = Objects.requireNonNull(values);
		if (values.length == 0)
			throw new IllegalArgumentException("no values");
		Class<T> type = (Class<T>) values[0].getClass();
		signature = (Class<T>[]) new Class<?>[dimension()];
		for (int j = 0; j < values.length; signature[j] = type, j++)
			;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		return Arrays.hashCode(args);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		if (null == asString) {
			String s = null;
			for (T a : args)
				s = null == s ? a.toString() : format("%s %s", s, a);
			asString = s;
		}
		return asString;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(@Nullable final Object o) {
		if (null == o)
			return false;
		if (this == o)
			return true;
		if (o.getClass() == this.getClass()) {
			@NonNull
			FactVA<?> that = FactVA.class.cast(o);
			return argEquals(that);
		}
		return false;
	}

	/**
	 * Internal argument equal check to be chained by child-classes.
	 * 
	 * @param that object to check
	 * @return boolean if arguments are equal
	 */
	protected boolean argEquals(final FactVA<?> that) {
		return Arrays.deepEquals(this.args, that.args);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#dimension()
	 */
	@Override
	public int dimension() {
		return args.length;
	}

	/**
	 * Factory method for a fact instance.
	 * 
	 * @param <T> arguments type
	 * @param x   arguments
	 * @return VarArgs fact
	 */
	@SafeVarargs
	@NonNull
	public static <T> FactVA<T> fact(@Nullable final T... x) {
		return new FactVA<>(x);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#arguments()
	 */
	@Override
	@NonNull
	public Object[] arguments() {
		// we only return a copy!
		return args.clone();
	}

	/**
	 * The type-safe arguments of type T
	 * 
	 * @return T array
	 */
	public T[] values() {
		return args.clone();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#signature()
	 */
	@Override
	@NonNull
	public Class<T>[] signature() {
		return signature;
	}
}
