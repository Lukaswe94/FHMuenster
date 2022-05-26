package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;
import de.lab4inf.mxr.linearalgebra.tools.MatrixCreator;

public class MatrxVecMultTester {
	Mops<MathProblem, Fact2D<double[][], double[]>, double[]> myMatVecMult;
	Random r = new Random();
    static double tolerance = 1E-12;
    
    double[] expected;
	double[] result;
	
	final double[][] m1 = {
            {0.0, 1.0, 2.0},
            {1.0, 2.0, 3.0}
    };
	
	final double[] v1 = { 0.0, 1.0, 2.0};
	final double[] v2 = { 2.0, 1.0};

	
	@BeforeEach
    void setUp() throws Exception {
    	this.myMatVecMult = new MatrxVecMult();
    }
	
	
	//  mutli matrix*VEC{0.0} 
    @Test
    void multMatrixNullVecTest() {
    	
    	
		int n = r.nextInt(100);
		int m = r.nextInt(100);
		
		expected = new double[n];

		double[] vec = new double[m];
		for (int i = 0; i < m - 1; i++) {
			vec[i] = 0.0;
		}

		for (int i = 0; i < n - 1; i++) {
			expected[i] = 0.0;
		}
    	double[][] a= MatrixCreator.createRndMatrix(n, m);
    	
        Fact2D<double[][], double[]> facts = Fact2D.fact(a, vec);
        double[] actual = myMatVecMult.solve(MathProblem.MULT, facts);
        MyAssertEquals.assertVectorEquals(expected, actual,tolerance);
    }
	
	// SIMPLE mutli matrix*vec 
    @Test
    void multMatrixTest1() {
        expected = new double[] {5.0, 8.0};
        
        Fact2D<double[][], double[]> facts = Fact2D.fact(m1, v1);
        double[] actual = myMatVecMult.solve(MathProblem.MULT, facts);
        MyAssertEquals.assertVectorEquals(expected, actual,tolerance);
    }

    //wrong dimensions : matrix*vec (2,3)*(2,1)
    @Test
    void wrongDimMatrixTest() {
        try {
        	Fact2D<double[][], double[]> facts = Fact2D.fact(m1, v2);
            @SuppressWarnings("unused")
			double[] actual = myMatVecMult.solve(MathProblem.MULT, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"Multiplication is because of the dimensions not possible");
        }
    }
    
    //wrong problem
    @Test
    void wrongProbTest() {
        try {
        	Fact2D<double[][], double[]> facts = Fact2D.fact(m1, v1);
            @SuppressWarnings("unused")
			double[] actual = myMatVecMult.solve(MathProblem.WRONG, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"wrong problem");
        }
    }
    
}
