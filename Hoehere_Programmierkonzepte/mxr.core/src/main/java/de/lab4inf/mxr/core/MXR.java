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

import java.util.*;

/**
 * MXR
 * 
 * The Mops eXtendable Runtime container. Several Mops solver instances register
 * within this container to provide solutions to given problems.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
public interface MXR {
	/** const string for facts nullpointer. */
	String FACTS_ARE_A_NULL_POINTER = "facts are a NullPointer!";
	/** const string for problem nullpointer. */
	String PROBLEM_IS_A_NULL_POINTER = "problem is a NullPointer!";
	/** const string for solution nullpointer. */
	String SOLUTION_IS_A_NULL_POINTER = "solution is a NullPointer!";
	/** const string for unknown problem. */
	String NO_MOPS_FOR_PROBLEM_FOUND = "no solver for problem: %s found";
	/** const string for no MXR instance found. */
	String NO_MXR_FOUND = "no valid MSR implementation found";

	/**
	 * Utility method using the reflection API to look-up an MXR implementation via
	 * the ServiceLoder mechanism. <br>
	 * Note: This static method uses a JDK1.8 feature: a static implementation
	 * within an interface and uses the Reflection API with a JDK1.6 ServiceLoader
	 * implementation - more in the lectures.
	 * 
	 * @return MXR instance found by reflection
	 */
	@NonNull
	static MXR getEngine() {
		ServiceLoader<MXR> loader = ServiceLoader.load(MXR.class);
		Optional<MXR> maybe = loader.findFirst();
		if (maybe.isPresent()) {
			MXR engine = Objects.requireNonNull(maybe.get(),NO_MXR_FOUND);
			return engine;
		}
		throw new IllegalStateException(NO_MXR_FOUND);

		// all this can be coded in one (more or less readable) line - I don't like this
		// style of programming...
		// return ServiceLoader.load(MXR.class).findFirst().orElseThrow(()->new
		// IllegalStateException(NO_MXR_FOUND));
	}

	/**
	 * Solve a problem for the given fact with the help of a suitable solver.
	 * Note: The solver has to be registered beforehand e.g. via the plugin mechanism in order to be found.
	 * 
	 * @param p    problem to solve
	 * @param fact to use
	 * @return solution to the problem
	 * @param <F>        type of the fact
	 * @param <Problem>  type of the problem
	 * @param <Solution> type of the solution
	 * @throws NoSolutionException if not solvable
	 */
	@NonNull
	<Problem, Facts extends Fact, Solution> Solution solve(@NonNull Problem p, @NonNull Facts facts) throws NoSolutionException; 

	/**
	 * Find the solver for the given problem and fact.
	 * 
	 * @param p     problem of the query
	 * @param facts fact of the query
	 * @return solver for the query
	 * @param <Problem>  type of the problem
	 * @param <Solution> type of the solution
	 * @throws NoSolverException if no solver exits
	 */
	@NonNull
	<Problem, Facts extends Fact, Solution> Mops<Problem, Facts, Solution> findSolver(@NonNull Problem p, @NonNull Facts facts)
			throws NoSolverException;

	/**
	 * Register a solver for a problem and facts.
	 * 
	 * @param p          problem to register
	 * @param facts      facts to register
	 * @param solver     to use for the problem,facts tuple
	 * @param <Problem>  type of the problem
	 * @param <Solution> type of the solution
	 */
	<Problem,Facts extends Fact, Solution> void register(@NonNull Problem p, @NonNull Fact facts, @NonNull Mops<Problem, Facts, Solution> solver);

	/**
	 * Simple plugin interface for components interacting with this container.
	 * A plugin can during the init phase register its solver instances.
	 */
	interface Plugin {
		void init(@NonNull MXR container);
	}

	/**
	 * Default registration of a plugin within the MXR container. The plugin should
	 * register its mops to provide within its init method.
	 * 
	 * @param plugin to register
	 */
	default void register(@NonNull Plugin plugin) {
		Objects.requireNonNull(plugin,"plugin to register is a NullPointer");
		plugin.init(this);
	}
}
