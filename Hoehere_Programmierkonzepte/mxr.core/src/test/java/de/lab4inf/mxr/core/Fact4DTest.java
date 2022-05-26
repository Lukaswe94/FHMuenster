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
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 * Test of the 4D fact instance.
 * 
 * @author nwulff
 * @since 10.10.2021
 */
class Fact4DTest {
	Fact4D<String, Integer, Integer, Integer> si1 , si2;
	Fact4D<Double, Float, Double, Float> df1, df2;

	/**
	 * @throws java.lang.Exception
	 */
	@BeforeEach
	void setUp() throws Exception {
		si1 = new Fact4D<>("one", 1, 2, 3);
		si2 = Fact4D.fact("two", 2, 3, 4);
		df1 = new Fact4D<>(1.0, 2.0f, 3.0, 4.0f);
		df2 = facts(2.0, 3.0f, 4.0, 5.0f);
	}
	/**
	 * Test method for dimension.
	 */
	@Test
	void testDimension() {
		assertEquals(4,si1.dimension());
	}

	/**
	 * Test method for {@link de.lab4inf.axela.facts.Fact4D#hashCode()}.
	 */
	@Test
	void testHashCode() {
		assertEquals(((si1.u.hashCode()*31+1)*31+2)*31 + 3, si1.hashCode());
		assertEquals(((si2.u.hashCode()*31+2)*31+3)*31 + 4, si2.hashCode());
		assertNotEquals(si1.hashCode(), si2.hashCode());
	}

	/**
	 * Test method for
	 * {@link de.lab4inf.axela.facts.Fact4D#equals(java.lang.Object)}.
	 */
	@Test
	void testEqualsObject() {
		assertEquals(si1, si1);
		assertEquals(si1, new Fact4D<>("one", 1, 2, 3));
		assertNotEquals(si1, new Fact3D<>("one", 1, 2));
		assertNotEquals(new Fact3D<>("one", 1, 2), si1);
		assertNotEquals(si1, si2);
		assertNotEquals(df1, si1);
		assertNotEquals(si1, df1);
		assertNotEquals(si1, "aString");
		assertNotEquals(si1, null);
	}

	/**
	 * Test method for {@link de.lab4inf.axela.facts.Fact4D#toString()}.
	 */
	@Test
	void testToString() {
		assertEquals("one 1 2 3", si1.toString());
		assertEquals("1.0 2.0 3.0 4.0", df1.toString());
	}

	@Test
	void testArguments() {
		Object[] args = si1.arguments();
		assertEquals("one", args[0]);
		assertEquals(Integer.valueOf(1), args[1]);
		assertEquals(Integer.valueOf(2), args[2]);
		assertEquals(Integer.valueOf(3), args[3]);
	}

	@Test
	void testArgumentsReadOnly() {
		Object[] args = si1.arguments();
		args[0] = "anOther";
		args[1] = Integer.valueOf(2);
		args[2] = Integer.valueOf(3);
		args[3] = Integer.valueOf(3);
		args = si1.arguments();
		assertEquals("one", args[0]);
		assertEquals(Integer.valueOf(1), args[1]);
		assertEquals(Integer.valueOf(2), args[2]);
		assertEquals(Integer.valueOf(3), args[3]);
	}

}
