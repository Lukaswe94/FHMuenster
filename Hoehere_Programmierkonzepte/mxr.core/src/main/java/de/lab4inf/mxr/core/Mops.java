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
 * MOPS: a multiple object-oriented problem solver.
 * 
 * @author nwulff
 * @since 10.10.2021
 * @param <Problem>  generic problem type to use
 * @param <Facts>    generic facts to parameterize the solver
 * @param <Solution> generic solution type to return
 */
@FunctionalInterface
public interface Mops<Problem, Facts extends Fact, Solution>  {
	/**
	 * Generic functional interface method to calculate a solution for a given
	 * problem and some facts. The facts are provided be several n-dimensional fact
	 * implementations.
	 * 
	 * @param p     problem to solve
	 * @param facts to use
	 * @return solution for the problem and facts
	 * @throws NoSolutionException if the problem is not solvable by this mops
	 */
	@NonNull
	Solution solve(@NonNull Problem p, @NonNull Facts facts) throws NoSolutionException;
}
