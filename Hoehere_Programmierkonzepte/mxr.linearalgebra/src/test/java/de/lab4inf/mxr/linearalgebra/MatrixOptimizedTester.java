package de.lab4inf.mxr.linearalgebra;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Fact3D;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;
import de.lab4inf.mxr.linearalgebra.tools.MatrixCreator;

public class MatrixOptimizedTester {
			
	double[][] expected;
	double[][] result;
	static double tolerance = 5E-12;
	Random r = new Random();
	
	
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
    
    //Mops<MathProblem, Fact3D<double[][], double[][], Boolean>, double[][]> optimized; 
    MatrxMultOptimized optimized; 
    MatrxMult naiv; 
    
    
    
   
    @BeforeEach
    void setUp() throws Exception {
    	this.optimized = new MatrxMultOptimized();
    	this.naiv = new MatrxMult(); 
    }
    
    // SIMPLE mutli matrix 1  : Seriell 
    @Test
    void serMultMatrixTest1() {
        expected = new double[][]{
                {5.0, 8.0},
                {8.0, 14.0}
        };
        
        Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(m1, m3, false);
        double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
        MyAssertEquals.assertMatrixEquals(expected, actual,tolerance);
    }
    
    // SIMPLE mutli matrix 1 : Parallel 
    @Test
    void parMultMatrixTest1() {
        expected = new double[][]{
                {5.0, 8.0},
                {8.0, 14.0}
        };
        
        Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(m1, m3, true);
        double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
        MyAssertEquals.assertMatrixEquals(expected, actual,tolerance);
    }

    // SIMPLE mutli matrix 2 : Seriell
    @Test
    void serMultMatrixTest2() {
        expected = new double[][]{
                {23.0/72.0, 17.0/60.0},
                {23.0/72.0, 17.0/60.0}
        };
        
        Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(m5, m6, false);
        double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
        MyAssertEquals.assertMatrixEquals(expected, actual,tolerance);
    }
    
    // SIMPLE mutli matrix 2 : Parallel
    @Test
    void parMultMatrixTest2() {
        expected = new double[][]{
                {23.0/72.0, 17.0/60.0},
                {23.0/72.0, 17.0/60.0}
        };
        
        Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(m5, m6, true);
        double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
        MyAssertEquals.assertMatrixEquals(expected, actual,tolerance);
    }

    //Wrong Dim : matrix OPTMULT (2,3)*(2,2)
    @Test
    void wrongDimMatrixTest() {
        try {
        	Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(m1, m4, true);
            @SuppressWarnings("unused")
			double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"* Operation is impossible. The matrices have different dimensions");
        }
    }
    
    //wrong problem
    @Test
    void wrongProbTest() {
        try {
        	Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(m1, m4, true);
            @SuppressWarnings("unused")
			double[][] actual = optimized.solve(MathProblem.WRONG, facts);
            fail();
        } catch (IllegalArgumentException e) {
            assertEquals(e.getMessage(),"wrong problem");
        }
    }
    
    // hilbert(n)*hilbert(n)^-1 : Parallel	 
    @Test
	void parHilbertMatrixTest() {
		//double delta = 1.0E-5;
		double delta = 1.0E-8;
		for (int n = 1; n <= 7; n++) {
			double[][] a = MatrixCreator.createHilbertMatrix(n);
			double[][] b = MatrixCreator.createInverseHilbertMatrix(n);
			double[][] expected = MatrixCreator.createIdMatrix(n);
        	Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(a, b, true);
			
			double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
			MyAssertEquals.assertMatrixEquals(expected, actual, delta);
		}
	}
    
    // hilbert(n)*hilbert(n)^-1 : Seriell 
    @Test
	void serHilbertMatrixTest() {
		//double delta = 1.0E-5;
		double delta = 1.0E-8;
		for (int n = 1; n <= 7; n++) {
			double[][] a = MatrixCreator.createHilbertMatrix(n);
			double[][] b = MatrixCreator.createInverseHilbertMatrix(n);
			double[][] expected = MatrixCreator.createIdMatrix(n);
        	Fact3D<double[][], double[][], Boolean> facts = Fact3D.fact(a, b, false);
			
			double[][] actual = optimized.solve(MathProblem.OPTMULT, facts);
			MyAssertEquals.assertMatrixEquals(expected, actual, delta);
		}
	}
    
    
    @Test 
    @Disabled
    void zeitMessungenTest() {
    	double delta = 1.0E-12;
        long naivStart, naivEnde, seriellEnde, optimised, parallelized, baseLine;
        double speedUp, seriellSpeedUp, parallelSpeedUp;
        System.out.println(" dim | baseline  |    optimized    |   parallelized   | speedUp | Amdahl ");
        System.out.println("-----+-----------+----------+------+----------+-------+---------+--------");
        System.out.println("  n  |   b[ms]   |   o[ms   |  b/o |   p[ms]  |  b/p  |   o/p   |  pi[%] ");
        System.out.println("-----+-----------+----------+------+----------+-------+---------+--------");

        
        for (int n = 128; n <= 4096; n*=2) {
            double[][] matrixA = MatrixCreator.createRndMatrix(n,n);
            double[][] matrixB = MatrixCreator.createRndMatrix(n,n);
            
            naivStart = System.nanoTime();
            double[][] baseResult = naiv.solve(MathProblem.MULT, Fact2D.fact(matrixA, matrixB));
            naivEnde = System.nanoTime();
            baseLine = naivEnde - naivStart; //b
  
            double[][] seriellResult = optimized.solve(MathProblem.OPTMULT, Fact3D.fact(matrixA, matrixB, false));
            seriellEnde = System.nanoTime();
            optimised = seriellEnde - naivEnde; // o 
            
            double[][] parallelResult = optimized.solve(MathProblem.OPTMULT, Fact3D.fact(matrixA, matrixB, true));
            parallelized = System.nanoTime()- seriellEnde; // p
            
            seriellSpeedUp = (double) baseLine/optimised;  // b/o
            parallelSpeedUp = (double) baseLine/parallelized;  // b/p
            speedUp = parallelSpeedUp/seriellSpeedUp;    // o/p
            
            double pi = 0.0;
            if (speedUp > 1) {
                int processors = Runtime.getRuntime().availableProcessors();
                pi = ((processors* (speedUp-1)) / (speedUp*(processors - 1)))*100;
            }

            System.out.println(String.format("%5d|%11d|%10d|%6.1f|%10d|%7.1f|%9.1f|%.1f", n, baseLine/1000, optimised/1000, seriellSpeedUp, parallelized/1000, (double)parallelSpeedUp, speedUp, pi));

            MyAssertEquals.assertMatrixEquals(baseResult, seriellResult, n*delta);
            MyAssertEquals.assertMatrixEquals(baseResult, parallelResult, n*delta);
        }
    }
    
    
    
}
