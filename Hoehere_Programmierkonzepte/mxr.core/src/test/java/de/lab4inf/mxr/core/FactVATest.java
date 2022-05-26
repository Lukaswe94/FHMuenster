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

import static de.lab4inf.mxr.core.FactFactory.*;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * Test of the varargs fact instance.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
class FactVATest {
	FactVA<String> si1, si2;
	FactVA<Double> df1, df2;

	/**
	 * @throws java.lang.Exception
	 */
	@BeforeEach
	void setUp() throws Exception {
		si1 = new FactVA<>("one", "two", "three");
		si2 = FactVA.fact("one", "two");
		df1 = new FactVA<>(1.0, 2.0, 3.0, 4.0);
		df2 = FactVA.fact(2.0, 3.0, 4.0);
	}
	
	/**
	 * Test method for dimension.
	 */
	@Test
	void testDimension() {
		assertEquals(3,si1.dimension());
		assertEquals(4,df1.dimension());
	}

	/**
	 * Test method for signature.
	 */
	@Test
	void testSignature() {
		assertArrayEquals(new Class<?>[] {String.class,String.class, String.class}, si1.signature());
		assertArrayEquals(new Class<?>[] {Double.class, Double.class,Double.class}, df2.signature());
	}

	/**
	 * Test method for hashCode.
	 */
	@Test
	void testHashCode() {
		assertNotEquals(si1.hashCode(), si2.hashCode());
		assertNotEquals(df1.hashCode(), df2.hashCode());
	}

	/**
	 * Test method for equals.
	 */
	@Test
	void testEqualsObject() {
		assertEquals(si1, si1);
		assertNotEquals(si1, new FactVA<>(1, 2, 3));
		assertNotEquals(si1, Fact3D.fact("one", 1, 2));
		assertNotEquals(df1, facts(1.0f, 2.0f, 3.0f, 4.0f));
		assertEquals(df1, FactVA.fact(1.0, 2.0, 3.0, 4.0));
		assertNotEquals(df1, Fact3D.fact("one", 1, 2));
		assertNotEquals(new Fact3D<>("one", 1, 2), si1);
		assertNotEquals(si1, si2);
		assertNotEquals(df1, si1);
		assertNotEquals(si1, df1);
		assertNotEquals(df1, df2);
		assertNotEquals(si1, "aString");
		assertNotEquals(si1, null);
	}

	/**
	 * Test method for toString.
	 */
	@Test
	void testToString() {
		assertEquals("one two three", si1.toString());
		assertEquals("1.0 2.0 3.0 4.0", df1.toString());
	}

	@Test
	void testArguments() {
		Object[] args = si1.arguments();
		assertEquals("one", args[0]);
		assertEquals("two", args[1]);
		assertEquals("three", args[2]);
	}

	@Test
	void testArgumentsReadOnly() {
		Object[] args = si1.arguments();
		args[0] = "anOther";
		args[1] = "dummy";
		args[2] = "string";
		args = si1.arguments();
		assertEquals("one", args[0]);
		assertEquals("two", args[1]);
		assertEquals("three", args[2]);
	}

}
