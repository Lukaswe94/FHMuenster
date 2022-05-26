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

import java.util.Objects;

/**
 * Fact with two generic arguments of type U,V.
 * 
 * @author nwulff
 * @param <U> the 1.st generic type to use.
 * @param <V> the 2.nd generic type to use.
 */
public class Fact2D<U, V> extends Fact1D<U> {
	/**
	 * access to the immutable argument of type V.
	 */
	@NonNull
	public final V v;

	/**
	 * Constructor for the two arguments to hold.
	 * 
	 * @param uu 1.st argument
	 * @param vv 2.nd argument
	 */
	public Fact2D(@NonNull final U uu, @NonNull final V vv) {
		super(uu);
		v = Objects.requireNonNull(vv);
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
			Fact2D<?, ?> that = Fact2D.class.cast(o);
			return argEquals(that);
		}
		return false;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		return super.hashCode()*31 + v.hashCode();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return format("%s %s", super.toString(), v);
	}

	/**
	 * Internal argument equal check to be chained by child-classes.
	 * 
	 * @param <T>  kind of fact
	 * @param that object to check
	 * @return boolean if arguments are equal
	 */
	protected <T extends Fact2D<?, ?>> boolean argEquals(@NonNull T that) {
		return super.argEquals(that) && this.v.equals(that.v);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#dimension()
	 */
	@Override
	public int dimension() {
		return 2;
	}

	/**
	 * Factory method for a fact instance.
	 * 
	 * @param <U> first type
	 * @param <V> second type
	 * @param u   1.st argument
	 * @param v   2.nd argument
	 * @return two argument fact
	 */
	@NonNull
	public static <U, V> Fact2D<U, V> fact(@NonNull final U u, @NonNull final V v) {
		return new Fact2D<>(u, v);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#arguments()
	 */
	@Override
	@NonNull
	public Object[] arguments() {
		return new Object[] { u, v };
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#signature()
	 */
	@Override
	@NonNull
	public final Class<?>[] signature() {
		if (null == signature) {
			Object[] args = arguments();
			signature = new Class<?>[args.length];
			for (int j = 0; j < args.length; signature[j] = args[j].getClass(), j++)
				;
		}
		return signature;
	}

}
