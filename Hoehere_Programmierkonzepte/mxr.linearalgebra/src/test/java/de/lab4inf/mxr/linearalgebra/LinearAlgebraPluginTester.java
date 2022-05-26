package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Fact3D;

import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.engine.MXREngine;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class LinearAlgebraPluginTester {

	final double[] vectorA = { 1.0, 2.0 };
	final double[] vectorB = { 4.0, 5.0 };
	
	final double[][] matrixA = { { 1.0, 2.0 },
								 { 4.0, 3.0 } };
	final double[][] matrixB = { { 2.0, 2.0 }, 
								 { 0.0, 1.0 } };
	final double[][] matrixC = { { 1.0 , 2.0 , 3.0 }, 
								 { 4.0 , 5.0 , 6.0 } };
	
	static double delta = 1.0E-08;

	MXREngine engine;

	@BeforeEach
	void setUp() throws Exception {
		engine = new MXREngine();
		engine.register(new LinearAlgebraPlugin());
	}

	@AfterEach
	void clean() {
		engine.getMap().clear();
	}

	@Test
	void testWrongProblem() {
		assertThrows(NoSolutionException.class, () -> engine.solve(MathProblem.WRONG , Fact2D.fact(matrixA, matrixB)));
	}

	@Test
	void testNoProblem() {
		assertThrows(NullPointerException.class, () -> engine.solve(null, Fact2D.fact(matrixA, matrixB)));
	}

	@Test
	void testNoFacts() {
		assertThrows(NullPointerException.class, () -> engine.solve(MathProblem.MULT, null));
	}

	@Test
	void testWrongDimension() {
		assertThrows(IllegalArgumentException.class, () -> {
			engine.solve(MathProblem.MULT, Fact2D.fact(matrixC, matrixA));
		});
	}

	@Test
	void testMatrixPlus() {
		double[][] expected = { { 3.0, 4.0 },
								{ 4.0, 4.0 } };
		double[][] result = engine.solve(MathProblem.ADD, Fact2D.fact(matrixA, matrixB));
		MyAssertEquals.assertMatrixEquals(expected, result, delta);
	}

	@Test
	void testMatrixMult() {
		double[][] expected = { { 2.0, 4.0 },
								{ 8.0, 11.0 } };
		double[][] result = engine.solve(MathProblem.MULT, Fact2D.fact(matrixA, matrixB));
		MyAssertEquals.assertMatrixEquals(expected, result, delta);
	}

	@Test
	void testVectorPlus() {
		double[] expected = { 5.0, 7.0 };
		double[] result = engine.solve(MathProblem.ADD, Fact2D.fact(vectorA, vectorB));
		MyAssertEquals.assertVectorEquals(expected, result, delta);
	}

	@Test
	void testVectorMult() {
		double expected = 14.0;
		double result = engine.solve(MathProblem.MULT, Fact2D.fact(vectorA, vectorB));
		MyAssertEquals.assertRelativEquals(expected, result, delta);
	}
	
	
	@Test
	void testVectorMatrxMult() {
		double[] expected = { 18.0, 5.0 };
		double[] result = engine.solve(MathProblem.MULT, Fact2D.fact(matrixB, vectorB));
		MyAssertEquals.assertVectorEquals(expected, result, delta);
	}
	
	// Test parallel Matrix Multiplication
	@Test
	void testParMatrixMult() {
		double[][] expected = { { 2.0, 4.0 },
								{ 8.0, 11.0 } };
		double[][] result = engine.solve(MathProblem.OPTMULT, Fact3D.fact(matrixA, matrixB, true));
		MyAssertEquals.assertMatrixEquals(expected, result, delta);
	}
	
	// Test seriell Matrix Multiplication
		@Test
		void testSerMatrixMult() {
			double[][] expected = { { 2.0, 4.0 },
									{ 8.0, 11.0 } };
			double[][] result = engine.solve(MathProblem.OPTMULT, Fact3D.fact(matrixA, matrixB, false));
			MyAssertEquals.assertMatrixEquals(expected, result, delta);
		}
	
	
}