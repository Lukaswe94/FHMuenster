/*
 * Project: mxr.client
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

package de.lab4inf.mxr.client;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact;
import de.lab4inf.mxr.core.Fact4D;
import de.lab4inf.mxr.core.FactFactory;
import de.lab4inf.mxr.core.FactVA;
import de.lab4inf.mxr.core.Mops;

/**
 * A very simple Fact/Mops test for string concatenation with various type
 * combinations.
 * 
 * @author nwulff
 *
 */
class SimpleConcatTest {
	final static String PROBLEM = SimpleConcat.PROBLEM;
	Mops<String,Fact,String> mops;

	/**
	 * Setup for this test case.
	 * @throws java.lang.Exception in case of an error
	 */
	@BeforeEach
	void setUp() throws Exception {
		mops =  new SimpleConcat().concatinator();
	}

	@Test
	void testWrongProblem() {
		String[] strings = { "Aufruf", "mit", "falschem", "Problem" };
		FactVA<String> facts = FactVA.fact(strings);
		assertThrows(IllegalArgumentException.class, () -> mops.solve("uhps", facts));
	}

	@Test
	void testNoProblem() {
		String[] strings = { "Aufruf", "mit", "NullPointer", "Problem" };
		FactVA<String> facts = FactVA.fact(strings);
		assertThrows(NullPointerException.class, () -> mops.solve(null, facts));
	}

	@Test
	void testNoFacts() {
		FactVA<String>  facts = null;
		assertThrows(NullPointerException.class, () -> mops.solve(PROBLEM, facts));
	}

	@Test
	void testString1D() {
		String[] strings = { "Hello" };
		Fact facts = FactVA.fact(strings);
		String expected = strings[0];
		String returned = mops.solve(PROBLEM, facts);
		assertEquals(expected, returned);
	}

	@Test
	void testInteger2D() {
		Integer[] ints = { 47, 11 };
		Fact facts = FactFactory.facts(ints);
		String expected = "4711";
		String returned = mops.solve(PROBLEM, facts);
		assertEquals(expected, returned);
	}

	@Test
	void testIntDouble2D() {
		Fact facts = FactFactory.facts(47, 11.0);
		String expected = "4711.0";
		String returned = mops.solve(PROBLEM, facts);
		assertEquals(expected, returned);
	}

	@Test
	void testString3D() {
		String[] strings = { "Hello", "World", "!" };
		FactVA<String> facts = FactVA.fact(strings);
		String expected = String.join("", strings);
		String returned = mops.solve(PROBLEM, facts);
		assertEquals(expected, returned);
	}

	@Test
	void testMixed4D() {
		Fact4D<String,String,Integer,String> facts = Fact4D.fact("Hello", "World", 2, "!");
		String expected = "HelloWorld2!";
		String returned = mops.solve(PROBLEM, facts);
		assertEquals(expected, returned);
	}

	@Test
	void testMixedVA() {
		Object[] array = { "Hello", "World", "_", 2., " !" };
		// Fact facts = Fact.facts("Hello", "World", "_", 2., " !");
		FactVA<?> facts = FactVA.fact(array);
		String expected = "HelloWorld_2.0 !";
		String returned = mops.solve(PROBLEM, facts);
		assertEquals(expected, returned);
	}

}
