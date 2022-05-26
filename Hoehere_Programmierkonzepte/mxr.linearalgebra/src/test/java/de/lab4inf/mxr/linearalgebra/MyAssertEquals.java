package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.assertEquals;

//SOURCE: http://www.lab4inf.fh-muenster.de/Lab4Math/testapidocs/de/lab4inf/math/L4MTestCase.html#assertRelEquals(java.lang.String,%20double,%20double,%20double)

public class MyAssertEquals {

	public static void assertRelativEquals(double expected, double returned, double tolerance) {
		if (Math.abs(expected) > 1) {
			tolerance *= Math.abs(expected);
		}
		assertEquals(expected, returned, tolerance);
	}

	public static void assertVectorEquals(double[] expected, double[] returned, double tolerance) {
		assertEquals(expected.length, returned.length, "different dimension");
		for (int i = 0; i < returned.length; i++) {
			assertRelativEquals(expected[i], returned[i], tolerance);
		}
	}

	public static void assertMatrixEquals(double[][] expected, double[][] returned, double tolerance) {
		assertEquals(expected.length, returned.length, "different dimension (matrix row)");
		for (int i = 0; i < returned.length; i++) {
			assertVectorEquals(expected[i], returned[i], tolerance);
		}
	}

}
