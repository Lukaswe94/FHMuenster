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

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * Abstract basic Test for various derived Fact classes.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
abstract class AbstractFactTesting {
	/** placeholder for various facts with different dimensions
	 *  and generic types. To be initialized during the setUp.
	 */
	Fact fact1, fact2,fact3, fact4;
    int dimension;
    /**
     * Initialization of the test case, providing four fact instances.
     * @throws Exception in case of any error
     */
    @BeforeEach
    abstract void setUp() throws Exception;
	/**
	 * Test method for dimension.
	 */
	@Test
	void testDimension() {
		assertEquals(dimension, fact1.dimension());
	}

	/**
	 * Test method for signature.
	 */
	@Test
	abstract void testSignature();

	/**
	 * Test method for hashCode.
	 */
	@Test
	void testHashCode() {
		assertEquals(fact1.hashCode(), fact1.hashCode());
		assertNotEquals(fact1.hashCode(), fact2.hashCode());
	}

	/**
	 * Test method for equals
	 */
	@Test
	void testEqualsObject() {
		assertNotEquals(fact1, null);
		assertEquals(fact1, fact1);
		assertNotEquals(fact1, fact2);
		assertNotEquals(fact3, fact1);
		assertNotEquals(fact1, fact3);
		assertNotEquals(fact1, "aString");
	}

	/**
	 * Test method for toString.
	 */
	@Test
	abstract void testToString();

	@Test
	void testArguments() {
		// assuming that all fact1 instances start with Integer 1...
		Object[] args = fact1.arguments();
		assertEquals(Integer.valueOf(1), args[0]);
	}

	@Test
	void testArgumentsReadOnly() {
		Object[] args = fact1.arguments();
		args[0] = Integer.valueOf(2);
		args = fact1.arguments();
		assertEquals(Integer.valueOf(1), args[0]);
	}

}
