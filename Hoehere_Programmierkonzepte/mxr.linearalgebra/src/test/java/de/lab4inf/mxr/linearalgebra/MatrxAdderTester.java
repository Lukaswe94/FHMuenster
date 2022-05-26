package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Random;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;
import de.lab4inf.mxr.linearalgebra.tools.MatrixCreator;

public class MatrxAdderTester {
	double[][] expected;
	double[][] result;
	static double tolerance = 1.0E-8;
	Random r = new Random();
	
	Mops<MathProblem, Fact2D<double[][], double[][]>, double[][]> myMtrxAdder;
	

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
    	this.myMtrxAdder = new MatrxAdder();
    }
    
    // SIMPLE add test
    @Test
    void testAddMatrix() {
        expected = new double[][]{
                {0.0, 2.0, 4.0},
                {2.0, 4.0, 6.0}
        };
        
        Fact2D<double[][], double[][]> facts = Fact2D.fact(m1, m2);
		double[][] actual = myMtrxAdder.solve(MathProblem.ADD, facts);
		MyAssertEquals.assertMatrixEquals(expected, actual, tolerance);
	}
    
    //wrong dimensions
    @Test
    void wrongDimMatrixTest() {
        try {
        	Fact2D<double[][], double[][]> facts = Fact2D.fact(m1, m4);
            @SuppressWarnings("unused")
			double[][] actual = myMtrxAdder.solve(MathProblem.ADD, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"+ Operation is impossible. The matrices have different dimensions");
        }
    }
    
    // wrong problem
    @Test
    void wrongProbTest() {
        try {
        	Fact2D<double[][], double[][]> facts = Fact2D.fact(m1, m2);
            @SuppressWarnings("unused")
			double[][] actual = myMtrxAdder.solve(MathProblem.WRONG, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"wrong problem");
        }
    }
    
  //Tr( A+B) = Tt(B) + Tr(A)
  	@Test
  	void addTranspTest() {
  		double delta = 1.0E-8;

  		int n = r.nextInt(100); 
  		int m = r.nextInt(100);
  		
  		double[][] a= MatrixCreator.createRndMatrix(n, m);
  		double[][] b = MatrixCreator.createRndMatrix(n, m);
      	Fact2D<double[][], double[][]> facts = Fact2D.fact(a, b);
  		
  		double[][] aPlusb = myMtrxAdder.solve(MathProblem.ADD, facts);
  		double[][] tr_aPlusb = MatrixCreator.transponieren(aPlusb); 
  		
  		double[][] trA = MatrixCreator.transponieren(a); 
  		double[][] trB = MatrixCreator.transponieren(b); 
  		
      	Fact2D<double[][], double[][]> facts1 = Fact2D.fact(trB, trA);
  		double[][] trB_plus_trA = myMtrxAdder.solve(MathProblem.ADD, facts1);
  		
  		MyAssertEquals.assertMatrixEquals(tr_aPlusb, trB_plus_trA, delta);

  		
  	}

}
