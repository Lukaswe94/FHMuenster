package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class VecMultTester {
	Mops<MathProblem, Fact2D<double[], double[]>, Double> myVecMult;
	Random r = new Random();
    static double tolerance = 1E-12;
	
	
	@BeforeEach
	void setUp() throws Exception {
		this.myVecMult = new VecMult();
	}

	// ( Double_Array , {0.0} )
	@Test
	void zeroVektorMultTest() {
		int size = r.nextInt(100);

		double[] vec1 = new double[size];
		double[] vec2 = new double[size];

		for (int i = 0; i < size - 1; i++) {
			vec1[i] = r.nextDouble();
		}

		for (int i = 0; i < size - 1; i++) {
			vec2[i] = 0.0;
		}

		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vec1, vec2);
		double actual = myVecMult.solve(MathProblem.MULT, facts);
		double expected = 0.0;

		assertEquals(expected, actual, tolerance);
	}

	// ( Double_Array , - Double_Array)
	@Test
	void oppositeVektorMultTest() {
		int size = r.nextInt(100);

		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		Double expected = 0.0;

		for (int i = 0; i < size - 1; i++)
			vec1[i] = r.nextDouble();

		for (int i = 0; i < size - 1; i++)
			vec2[i] = -vec1[i];

		for (int i = 0; i < size - 1; i++)
			expected += -Math.pow(vec1[i], 2);

		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vec1, vec2);
		double actual = myVecMult.solve(MathProblem.MULT, facts);

		assertEquals(expected, actual, tolerance);
	}

	// ( Double_Array , Double_Array)
	@Test
	void sameVektorMultTest() {
		int size = r.nextInt(100);

		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		Double expected = 0.0;

		for (int i = 0; i < size - 1; i++) {
			vec1[i] = r.nextDouble();
			vec2[i] = vec1[i];
			expected += Math.pow(vec1[i], 2);
		}

		Fact2D<double[], double[]> facts = Fact2D.fact(vec1, vec2);
		Double actual = myVecMult.solve(MathProblem.MULT, facts);

		assertEquals(expected, actual, tolerance);
	}

	// (Exception: not same size)
	@Test
	void notSameSizeMultTest() {
		int size1 = r.nextInt(100);
		double[] vec1 = new double[size1];
		double[] vec2 = new double[size1 + 1];

		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vec1, vec2);

		try {
			@SuppressWarnings("unused")
			double actual = myVecMult.solve(MathProblem.MULT, facts);
			fail("Ouuups, Test fails because no exception was thron for wrong dimensions ");
		} catch (IllegalArgumentException e) {
			assertEquals(e.getMessage(), "not the same size of vectors");

		}
	}

	// nicht effizient : (radom Vektor , random Vektor)
	@Test
	void twoRandVecMultTest() {
		int size = r.nextInt(100);
		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		double expected = 0.0;

		for (int i = 0; i < size - 1; i++) {
			vec1[i] = r.nextDouble();
			vec2[i] = r.nextDouble();
			expected += vec1[i] * vec2[i];
		}
		
		Fact2D<double[], double[]> facts = Fact2D.fact(vec1, vec2);
		double actual = myVecMult.solve(MathProblem.MULT,  facts);
		assertEquals(expected, actual, tolerance);
	}
	
	//Exception: falsches Problem 
	@Test
	void falseProbTest() {
		
		int size = 10;
		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		
		for (int i = 0; i < size - 1; i++) 
			vec1[i] = r.nextDouble();
		

		for (int i = 0; i < size - 1; i++) 
			vec2[i] = r.nextDouble();
		


		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vec1, vec2);
		try {
			@SuppressWarnings("unused")
			double actual = myVecMult.solve(MathProblem.WRONG, facts);
			fail("Oups, no exception has been thrown ");
		}
		catch( Exception e) {
			assertEquals(e.getMessage(), "wrong problem");
		}
	}
	
	
}
