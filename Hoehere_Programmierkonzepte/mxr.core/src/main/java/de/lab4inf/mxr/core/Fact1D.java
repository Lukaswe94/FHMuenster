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

import static java.lang.String.format;

import java.util.Objects;

/**
 * Fact with one generic argument of type U.
 * 
 * @author nwulff
 * @param <U> the generic type to use.
 */
public class Fact1D<U> implements Fact {
		protected Class<?>[] signature;
		/**
		 * access to the immutable argument of type U.
		 */
		@NonNull
		public final U u;

		/**
		 * Constructor for the one argument to hold.
		 * 
		 * @param uu 1.st argument
		 */
		public Fact1D(@NonNull final U uu) {
			u = Objects.requireNonNull(uu);
		}

		/*
		 * (non-Javadoc)
		 * 
		 * @see java.lang.Object#equals(java.lang.Object)
		 */
		@Override
		public boolean equals(final Object o) {
			if (null == o)
				return false;
			if (this == o)
				return true;
			if (o.getClass() == this.getClass()) {
				@NonNull
				Fact1D<?> that = Fact1D.class.cast(o);
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
			return u.hashCode();
		}

		/*
		 * (non-Javadoc)
		 * 
		 * @see java.lang.Object#toString()
		 */
		@Override
		public String toString() {
			return format("%s", u);
		}

		/**
		 * Internal argument equal check to be chained by child-classes.
		 * 
		 * @param <T>  kind of fact
		 * @param that object to check
		 * @return boolean if arguments are equal
		 */
		protected <T extends Fact1D<?>> boolean argEquals(@NonNull T that) {
			return this.u.equals(that.u);
		}

		/*
		 * (non-Javadoc)
		 * 
		 * @see de.lab4inf.mxr.core.Fact#dimension()
		 */
		@Override
		public int dimension() {
			return 1;
		}

		/**
		 * Factory method for a fact instance.
		 * 
		 * @param <U> first type
		 * @param u   1.st argument
		 * @return one argument fact
		 */
		@NonNull
		public static <U> Fact1D<U> fact(@NonNull final U u) {
			return new Fact1D<>(u);
		}

		/*
		 * (non-Javadoc)
		 * 
		 * @see de.lab4inf.mxr.core.Fact#arguments()
		 */
		@Override
		@NonNull
		public Object[] arguments() {
			return new Object[] { u };
		}

		/*
		 * (non-Javadoc)
		 * 
		 * @see de.lab4inf.mxr.core.Fact#signature()
		 */
		@Override
		@NonNull
		public Class<?>[] signature() {
			if (null == signature) {
				signature = new Class<?>[] { u.getClass() };
			}
			return signature;
		}
}
