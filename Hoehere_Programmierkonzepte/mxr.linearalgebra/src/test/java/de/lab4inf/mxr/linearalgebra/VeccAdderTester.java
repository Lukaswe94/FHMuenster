package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class VeccAdderTester {

	Mops<MathProblem, Fact2D<double[], double[]>, double[]> myVecAdder;

    static double tolerance = 5.2E-12;
	
	
	@BeforeEach
	void setUp() throws Exception {
		this.myVecAdder = new VecAdder();
	}


	// ( Double_Array , {0.0} )
	@Test
	void zeroVektorAddTest() {
		Random r = new Random();
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
		double[] actual = myVecAdder.solve(MathProblem.ADD, facts);
		double[] expected = vec1;

		MyAssertEquals.assertVectorEquals(actual, expected,tolerance);
	}

	// ( Double_Array , - Double_Array)
	@Test
	void oppositeVektorAddTest() {
		Random r = new Random();
		int size = r.nextInt(100);

		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		double[] expected = new double[size];

		for (int i = 0; i < size - 1; i++)
			vec1[i] = r.nextDouble();

		for (int i = 0; i < size - 1; i++)
			vec2[i] = -vec1[i];

		for (int i = 0; i < size - 1; i++)
			expected[i] = 0.0;

		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vec1, vec2);
		double[] actual = myVecAdder.solve(MathProblem.ADD, facts);

		MyAssertEquals.assertVectorEquals(actual, expected,tolerance);
	}

	// ( Double_Array , Double_Array)
	@Test
	void sameVektorAddTest() {
		Random r = new Random();
		int size = r.nextInt(100);

		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		double[] expected = new double[size];

		for (int i = 0; i < size - 1; i++) {
			vec1[i] = r.nextDouble();
			vec2[i] = vec1[i];
			expected[i] = 2 * vec1[i];
		}

		Fact2D<double[], double[]> facts = Fact2D.fact(vec1, vec2);
		double[] actual = myVecAdder.solve(MathProblem.ADD, facts);

		MyAssertEquals.assertVectorEquals(actual, expected,tolerance);
	}

	// (Exception: not same size)
	@Test
	void notSameSizeAddTest() {
		Random r = new Random();
		int size1 = r.nextInt(100);
		double[] vec1 = new double[size1];
		double[] vec2 = new double[size1 + 1];

		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vec1, vec2);

		try {
			@SuppressWarnings("unused")
			double[] actual = myVecAdder.solve(MathProblem.ADD, facts);
			fail("Ouuups, Test fails because no exception was thron for wrong dimensions ");
		} catch (IllegalArgumentException e) {
			assertEquals(e.getMessage(), "not the same size of vectors");

		}
	}

	// nicht effizient : (radom Vektor , random Vektor)
	@Test
	void twoRandVecTest() {
		Random r = new Random();
		int size = r.nextInt(100);
		double[] vec1 = new double[size];
		double[] vec2 = new double[size];
		double[] expected = new double[size];

		for (int i = 0; i < size - 1; i++) {
			vec1[i] = r.nextDouble();
			vec2[i] = r.nextDouble();
			expected[i] = vec1[i] + vec2[i];
		}
		
		Fact2D<double[], double[]> facts = Fact2D.fact(vec1, vec2);
		double[] actual = myVecAdder.solve(MathProblem.ADD,  facts);
		MyAssertEquals.assertVectorEquals(actual, expected,tolerance);
	}
	
	//Exception: falsches Problem 
	@Test
	void falseProbTest() {
		Random r = new Random();
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
			double[] actual = myVecAdder.solve(MathProblem.WRONG, facts);
			fail("Oups, no exception has been thrown ");
		}
		catch( Exception e) {
			assertEquals(e.getMessage(), "wrong problem");
		}
	}
}
