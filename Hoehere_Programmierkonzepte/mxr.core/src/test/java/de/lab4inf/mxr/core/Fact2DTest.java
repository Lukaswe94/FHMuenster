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
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * Test of the 2D fact instance.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
class Fact2DTest extends AbstractFactTesting {
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#setUp()
     */
	@Override
	@BeforeEach
	void setUp() throws Exception {
		dimension = 2;
		fact1 = new Fact2D<>("one", 1);
		fact2 = Fact2D.fact("two", 2);
		fact3 = new Fact2D<>(1.0, 2.0f);
		fact4 = facts(2.0, 3.0f);
	}
	
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testSignature()
     */
	@Override
	@Test
	void testSignature() {
		assertArrayEquals(new Class<?>[] {String.class,Integer.class}, fact1.signature());
		assertArrayEquals(new Class<?>[] {Double.class, Float.class}, fact3.signature());
	}
	/*
	 * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testHashCode()
	 */
	@Override
	@Test
	void testHashCode() {
		super.testHashCode();
		assertEquals(Fact2D.class.cast(fact1).u.hashCode()*31 + 1, fact1.hashCode());
		assertEquals(Fact2D.class.cast(fact2).u.hashCode()*31 + 2, fact2.hashCode());
		assertNotEquals(fact1.hashCode(), fact2.hashCode());
	}
	/*
	 * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testEqualsObject()
	 */
	@Override
	@Test
	void testEqualsObject() {
		super.testEqualsObject();
		fact2 = new Fact2D<>("one",1);
		assertEquals(fact1, fact2);
		fact2 = new Fact2D<>("one",2);
		assertNotEquals(fact1, fact2);
		fact2 = new Fact2D<>("two",1);
		assertNotEquals(fact1, fact2);
		fact2 = new Fact1D<>("one");
		assertNotEquals(fact1, fact2);
		assertNotEquals(fact2, fact1);
	}
	/*
	 * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testToString()
	 */
	@Override
	@Test
	void testToString() {
		assertEquals("one 1", fact1.toString());
		assertEquals("1.0 2.0", fact3.toString());
	}
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testArguments()
     */
	@Override
	@Test
	void testArguments() {
		Object[] args = fact1.arguments();
		assertEquals("one", args[0]);
		assertEquals(Integer.valueOf(1), args[1]);
	}
    /*
     * @see @see de.lab4inf.mxr.core.AbstractFactTesting#testArgumentsReadOnly()
     */
	@Override
	@Test
	void testArgumentsReadOnly() {
		Object[] args = fact1.arguments();
		args[0] = "anOther";
		args[1] = Integer.valueOf(2);
		args = fact1.arguments();
		assertEquals("one", args[0]);
		assertEquals(Integer.valueOf(1), args[1]);
	}

}
