package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;
import de.lab4inf.mxr.linearalgebra.tools.MatrixCreator;

public class MatrxMultTester {

	
	double[][] expected;
	double[][] result;
	static double tolerance = 5E-12;
	Random r = new Random();


	Mops<MathProblem, Fact2D<double[][], double[][]>, double[][]> myMtrxMulti;
	
	final double[][] m1 = {
            {0.0, 1.0, 2.0},
            {1.0, 2.0, 3.0}
    };

    final double[][] m2 = {
            {0.0, 1.0, 2.0},
            {1.0, 2.0, 3.0}
    };

    final double[][] m3 = {
            {0.0, 1.0},
            {1.0, 2.0},
            {2.0, 3.0}
    };
    final double[][] m4 = {
            {0.0, 1.0},
            {1.0, 2.0}
    };

    final double[][] m5 = {
            {1.0/2.0, 1.0/3.0, 1.0/6.0},
            {1.0/2.0, 1.0/3.0, 1.0/6.0}
    };

    final double[][] m6 = {
            {1.0/4.0, 1.0/3.0},
            {1.0/3.0, 1.0/4.0},
            {1.0/2.0, 1.0/5.0},

    };
   

 
    @BeforeEach
    void setUp() throws Exception {
    	this.myMtrxMulti = new MatrxMult();
    }
    
    // SIMPLE mutli matrix 1 
    @Test
    void multMatrixTest1() {
        expected = new double[][]{
                {5.0, 8.0},
                {8.0, 14.0}
        };
        
        Fact2D<double[][], double[][]> facts = Fact2D.fact(m1, m3);
        double[][] actual = myMtrxMulti.solve(MathProblem.MULT, facts);
        MyAssertEquals.assertMatrixEquals(expected, actual,tolerance);
    }

    // SIMPLE mutli matrix 2
    @Test
    void multMatrixTest2() {
        expected = new double[][]{
                {23.0/72.0, 17.0/60.0},
                {23.0/72.0, 17.0/60.0}
        };
        
        Fact2D<double[][], double[][]> facts = Fact2D.fact(m5, m6);
        double[][] actual = myMtrxMulti.solve(MathProblem.MULT, facts);
        MyAssertEquals.assertMatrixEquals(expected, actual,tolerance);
    }

    //Wrong Dim : matrix mult (2,3)*(2,2)
    @Test
    void wrongDimMatrixTest() {
        try {
        	Fact2D<double[][], double[][]> facts = Fact2D.fact(m1, m4);
            @SuppressWarnings("unused")
			double[][] actual = myMtrxMulti.solve(MathProblem.MULT, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"* Operation is impossible. The matrices have different dimensions");
        }
    }
    
    //wrong problem
    @Test
    void wrongProbTest() {
        try {
        	Fact2D<double[][], double[][]> facts = Fact2D.fact(m1, m4);
            @SuppressWarnings("unused")
			double[][] actual = myMtrxMulti.solve(MathProblem.WRONG, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"wrong problem");
        }
    }
    
    // hilbert(n)*hilbert(n)^-1
    @Test
	void hilbertMatrixTest() {
		//double delta = 1.0E-5;
		double delta = 1.0E-8;
		for (int n = 1; n <= 7; n++) {
			double[][] a = MatrixCreator.createHilbertMatrix(n);
			double[][] b = MatrixCreator.createInverseHilbertMatrix(n);
			double[][] expected = MatrixCreator.createIdMatrix(n);
        	Fact2D<double[][], double[][]> facts = Fact2D.fact(a, b);
			
			double[][] actual = myMtrxMulti.solve(MathProblem.MULT, facts);
			MyAssertEquals.assertMatrixEquals(expected, actual, delta);
		}
	}
    
    /*
	//Tr( A.B) = Tt(B).Tr(A)
	@Test
	void multTranspTest() {
		double delta = 1.0E-8;

		int n = r.nextInt(100); 
		int m = r.nextInt(100);
		int l = r.nextInt(100);
		
		double[][] a= MatrixCreator.createRndMatrix(n, m);
		double[][] b = MatrixCreator.createRndMatrix(m, l);
    	Fact2D<double[][], double[][]> facts = Fact2D.fact(a, b);
		
		double[][] ab = myMtrxMulti.solve(MathProblem.MULT, facts);
		double[][] trAB = MatrixCreator.transponieren(ab); 
		
		double[][] trA = MatrixCreator.transponieren(a); 
		double[][] trB = MatrixCreator.transponieren(b); 
		
    	Fact2D<double[][], double[][]> facts1 = Fact2D.fact(trB, trA);
		double[][] trB_trA = myMtrxMulti.solve(MathProblem.MULT, facts1);
		
		MyAssertEquals.assertMatrixEquals(trAB, trB_trA, delta);
	}
	*/
	
}
