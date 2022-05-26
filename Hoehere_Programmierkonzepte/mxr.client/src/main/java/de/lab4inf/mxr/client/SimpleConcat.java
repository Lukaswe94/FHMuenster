/*
 * Project: mxr.client
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

package de.lab4inf.mxr.client;

import static java.lang.String.format;

import java.util.Objects;

import de.lab4inf.mxr.core.Fact;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NonNull;

/**
 * A very simple Concatinator for various type combinations.
 * 
 * 
 * @author nwulff
 * @since 11.10.2021
 */
public class SimpleConcat {
	final static String PROBLEM = "CONCAT";

	/**
	 * Factory method to construct a concatinator from facts.
	 * 
	 * @return a concatinator
	 */
	@NonNull
	public Mops<String,Fact, String> concatinator() {
		return (p, f) -> {
			@NonNull
			String s = "";
			Objects.requireNonNull(p, "no problem given");
			Objects.requireNonNull(f, "no fact(s) given");
			if (!PROBLEM.equals(p))
				throw new IllegalArgumentException(format("wrong problem %s != %s",p, PROBLEM));
			for (Object o : f.arguments())
				s = String.format("%s%s", s, o);
			return s;
		};

	}

}
