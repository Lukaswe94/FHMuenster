package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class KreuzProdTester {
	Mops<MathProblem, Fact2D<double[], double[]>, double[]> myKreuzMult;
	Random r = new Random();
    static double tolerance = 1E-12;

	
	@BeforeEach
	void setUp() throws Exception {
		this.myKreuzMult = new KreuzProdukt();
	}
	
	
	@Test 
	void kpTest() {
		double[] vectorA=  { 1.0, 2.0, 3.0}; 
		double[] vectorB=  { -7.0, 8.0, 9.0}; 
		
		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vectorA, vectorB);
		double[] actual = myKreuzMult.solve(MathProblem.KRMULT, facts);
		
		
		double[] expected = { -6.0, -30.0 , 22.0};
		
		MyAssertEquals.assertVectorEquals(expected, actual, tolerance);
		
	}
	
	
	
	
	
	

	@Test 
	void wrongDimensionTest() {
		double[] vectorA=  { 1.0, 2.0, 3.0}; 
		double[] vectorB=  { -7.0, 8.0, 9.0, 10.0}; 
		
		Fact2D<double[], double[]> facts = new Fact2D<double[], double[]>(vectorA, vectorB);

		assertThrows(IllegalArgumentException.class, () ->myKreuzMult.solve(MathProblem.KRMULT, facts));
	}
	
}
