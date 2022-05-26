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
 * Test of the 3D fact instance.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
class Fact3DTest {
	Fact3D<String, Integer, Integer> si1, si2;
	Fact3D<Double, Float, Double> df1, df2;

	/**
	 * @throws java.lang.Exception
	 */
	@BeforeEach
	void setUp() throws Exception {
		si1 = new Fact3D<>("one", 1, 2);
		si2 = Fact3D.fact("two", 2, 3);
		df1 = new Fact3D<>(1.0, 2.0f, 3.0);
		df2 = facts(2.0, 3.0f, 4.0);
	}
	
	/**
	 * Test method for dimension.
	 */
	@Test
	void testDimension() {
		assertEquals(3,si1.dimension());
	}

	/**
	 * Test method for signature.
	 */
	@Test
	void testSignature() {
		assertArrayEquals(new Class<?>[] {String.class,Integer.class, Integer.class}, si1.signature());
		assertArrayEquals(new Class<?>[] {Double.class, Float.class,Double.class}, df1.signature());
	}

	/**
	 * Test method for hashCode.
	 */
	@Test
	void testHashCode() {
		assertEquals((si1.u.hashCode()*31 + 1)*31 + 2, si1.hashCode());
		assertEquals((si2.u.hashCode()*31 + 2)*31 + 3, si2.hashCode());
		assertNotEquals(si1.hashCode(), si2.hashCode());
	}

	/**
	 * Test method for equals.
	 */
	@Test
	void testEqualsObject() {
		assertEquals(si1, si1);
		assertEquals(si1, new Fact3D<>("one", 1, 2));
		assertNotEquals(si1, new Fact2D<>("one", 1));
		assertNotEquals(new Fact2D<>("one", 1), si1);
		assertNotEquals(si1, si2);
		assertNotEquals(df1, si1);
		assertNotEquals(si1, df1);
		assertNotEquals(si1, "aString");
		assertNotEquals(si1, null);
	}

	/**
	 * Test method for toString
	 */
	@Test
	void testToString() {
		assertEquals("one 1 2", si1.toString());
		assertEquals("1.0 2.0 3.0", df1.toString());
	}

	@Test
	void testArguments() {
		Object[] args = si1.arguments();
		assertEquals("one", args[0]);
		assertEquals(Integer.valueOf(1), args[1]);
		assertEquals(Integer.valueOf(2), args[2]);
	}

	@Test
	void testArgumentsReadOnly() {
		Object[] args = si1.arguments();
		args[0] = "anOther";
		args[1] = Integer.valueOf(2);
		args[2] = Integer.valueOf(3);
		args = si1.arguments();
		assertEquals("one", args[0]);
		assertEquals(Integer.valueOf(1), args[1]);
		assertEquals(Integer.valueOf(2), args[2]);
	}

}
