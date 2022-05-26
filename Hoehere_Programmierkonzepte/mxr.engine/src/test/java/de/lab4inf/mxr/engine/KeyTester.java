package de.lab4inf.mxr.engine;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import de.lab4inf.mxr.core.Fact1D;
import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Fact3D;
import de.lab4inf.mxr.core.FactFactory;

public class KeyTester {
	Key<String, Fact1D<Double>> key1;
	Key<String, Fact1D<Double>> key2;
	Key<String, Fact2D<Double, Double>> key3;
	Key<String, Fact3D<Double, Double, Double>> key4;
	String problem1;
	String problem2;
	String problem3; 

	@BeforeEach
	void setUp() throws Exception {
		problem1 = new String("problem1");
		problem2 = new String("problem2");
		problem3 = new String("problem3");
		key1 = new Key<>(problem1, FactFactory.facts(1.0));
		key2 = new Key<>(problem1, FactFactory.facts(1.0));
		key3 = new Key<>(problem2, FactFactory.facts(1.0, 1.0));
		
	}
	@Test
	void EqualsTest() {
		assertTrue(key1.equals(key2));
	}
	@Test
	void NotEqualsTest() {
		assertFalse(key1.equals(key3));
	}
	@Test
	void HashCodeTest() {
		assertEquals(key1.hashCode(), key2.hashCode());
	}
	
}
