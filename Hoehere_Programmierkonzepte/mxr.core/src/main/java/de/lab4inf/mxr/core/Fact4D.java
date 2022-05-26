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
 * Fact with four generic arguments of type U,V,W,X.
 * 
 * @author nwulff
 * @param <U> the 1.st generic type to use.
 * @param <V> the 2.nd generic type to use.
 * @param <W> the 3.nd generic type to use.
 * @param <X> the 4.th generic type to use.
 */
public class Fact4D<U, V, W, X> extends Fact3D<U, V, W> {
	/**
	 * access to the immutable argument of type X.
	 */
	@NonNull
	public final X x;

	/**
	 * Constructor for the four arguments to hold.
	 * 
	 * @param uu 1.st argument
	 * @param vv 2.nd argument
	 * @param ww 3.rd argument
	 * @param xx 4.th argument
	 */
	public Fact4D(@NonNull final U uu, @NonNull final V vv, @NonNull final W ww, @NonNull final X xx) {
		super(uu, vv, ww);
		x = Objects.requireNonNull(xx);
	}
	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#dimension()
	 */
	@Override
	public int dimension() {
		return 4;
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
			Fact4D<?, ?, ?, ?> that = Fact4D.class.cast(o);
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
		return super.hashCode()*31 + x.hashCode();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return format("%s %s", super.toString(), x);
	}

	/**
	 * Internal argument equal check to be chained by child-classes.
	 * 
	 * @param <T>  kind of fact
	 * @param that object to check
	 * @return boolean if arguments are equal
	 */
	protected <T extends Fact4D<?, ?, ?, ?>> boolean argEquals(@NonNull T that) {
		return super.argEquals(that) && this.x.equals(that.x);
	}

	/**
	 * Factory method for a fact instance.
	 * 
	 * @param <U> first type
	 * @param <V> second type
	 * @param <W> third type
	 * @param <X> third type
	 * @param u   1.st argument
	 * @param v   2.nd argument
	 * @param w   3.rd argument
	 * @param x   4.th argument
	 * @return three argument fact
	 */
	@NonNull
	public static <U, V, W, X> Fact4D<U, V, W, X> fact(@NonNull final U u, @NonNull final V v, @NonNull final W w,
			@NonNull final X x) {
		return new Fact4D<>(u, v, w, x);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see de.lab4inf.mxr.core.Fact#arguments()
	 */
	@Override
	@NonNull
	public Object[] arguments() {
		return new Object[] { u, v, w, x };
	}
}
