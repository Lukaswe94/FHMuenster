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

import static de.lab4inf.mxr.core.FactFactory.facts;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * Test of the 1D fact instance.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
class Fact1DTest extends AbstractFactTesting {
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#setUp()
     */
	@Override
	@BeforeEach
	void setUp() throws Exception {
		dimension = 1;
		fact1 = new Fact1D<>(1);
		fact2 = Fact1D.fact(2);
		fact3 = new Fact1D<>(1.0);
		fact4 = facts(2.0);
	}


	/**
	 * Test method for signature.
	 */
	@Override
	@Test
	void testSignature() {
		assertArrayEquals(new Class<?>[] {Integer.class}, fact1.signature());
		assertArrayEquals(new Class<?>[] {Double.class}, fact3.signature());
	}
	/**
	 * Test method for equals
	 */
	@Override
	@Test
	void testEqualsObject() {
		super.testEqualsObject();
		assertEquals(fact1, new Fact1D<>(1));
	}

	/**
	 * Test method for hashCode.
	 */
	@Override
	@Test
	void testHashCode() {
		super.testHashCode();
		assertEquals(Fact1D.class.cast(fact1).u.hashCode(), fact1.hashCode());
		assertEquals(Fact1D.class.cast(fact2).u.hashCode(), fact2.hashCode());
	}


	/**
	 * Test method for toString.
	 */
	@Override
	@Test
	void testToString() {
		assertEquals("1", fact1.toString());
		assertEquals("1.0", fact3.toString());
	}
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testArguments()
     */
	@Override
	@Test
	void testArguments() {
		Object[] args = fact1.arguments();
		assertEquals(Integer.valueOf(1), args[0]);
	}
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testArgumentsReadOnly()
     */
  	@Override
	@Test
	void testArgumentsReadOnly() {
		Object[] args = fact1.arguments();
		args[0] = Integer.valueOf(2);
		args = fact1.arguments();
		assertEquals(Integer.valueOf(1), args[0]);
	}

}
