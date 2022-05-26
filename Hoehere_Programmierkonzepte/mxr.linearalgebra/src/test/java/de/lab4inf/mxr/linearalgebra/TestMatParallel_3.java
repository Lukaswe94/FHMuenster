package de.lab4inf.mxr.linearalgebra;


import static org.junit.jupiter.api.Assertions.*;
import java.util.Random;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Fact3D;
import de.lab4inf.mxr.core.FactFactory;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;
import de.lab4inf.mxr.linearalgebra.tools.MatrixCreator;

class TestMatParallel_3 {
	
	
	double[][] expected;
	double[][] result;
	static double tolerance = 5E-12;
	Random r = new Random();

	Mops<MathProblem, Fact3D<double[][], double[][], Boolean>, double[][]> parallelmult;
	Mops<MathProblem, Fact3D<double[][], double[][], Boolean>, double[][]> seriellmult;
	Mops<MathProblem, Fact2D<double[][], double[][]>, double[][]> myMtrxMulti;
	
double[][] m1,m2,m3;
	@BeforeEach
	void setUp() throws Exception {
		parallelmult = new MatParallel_3();
		myMtrxMulti = new MatrxMult();
		seriellmult = new MatSeriell_3();
		m1 = MatrixCreator.createRndMatrix(512, 512);
		m2 = MatrixCreator.createRndMatrix(12, 12);
		m3 = MatrixCreator.createRndMatrix(512, 512);
	}

	@Test
	void testRndMult() {
		Fact3D<double[][], double[][], Boolean> facts3d = FactFactory.facts(m1, m3, true);
		Fact2D<double[][], double[][]> facts2d = FactFactory.facts(m1, m3);
		result = parallelmult.solve(MathProblem.MULT, facts3d);
		expected = myMtrxMulti.solve(MathProblem.MULT, facts2d);
		MyAssertEquals.assertMatrixEquals(expected, result, tolerance);
	}
	
	@Test
	void testWrongDim() {
		Fact3D<double[][], double[][], Boolean> facts3d = FactFactory.facts(m1, m2, true);
		assertThrows(IllegalArgumentException.class, () -> parallelmult.solve(MathProblem.MULT, facts3d));
	}
	@Test
	void testWrongFact() {
		Fact3D<double[][], double[][], Boolean> facts3d = FactFactory.facts(m1, m3, false);
		assertThrows(IllegalArgumentException.class, () -> parallelmult.solve(MathProblem.MULT, facts3d));	
	}
	@Test
	void testWrongProblem() {
		Fact3D<double[][], double[][], Boolean> facts3d = FactFactory.facts(m1, m3, true);
		assertThrows(IllegalArgumentException.class, () -> parallelmult.solve(MathProblem.WRONG, facts3d));		
	}
	
    /*
    @Test 
    void zeitMessungenTest() {
    	double delta = 1.0E-12;
        long naivStart, naivEnde, seriellEnde, optimised, parallelized, baseLine;
        double speedUp, seriellSpeedUp, parallelSpeedUp;
        System.out.println(" dim | baseline  |    optimized    |   parallelized   | speedUp | Amdahl ");
        System.out.println("-----+-----------+----------+------+----------+-------+---------+--------");
        System.out.println("  n  |   b[ms]   |   o[ms   |  b/o |   p[ms]  |  b/p  |   o/p   |  pi[%] ");
        System.out.println("-----+-----------+----------+------+----------+-------+---------+--------");

        
        for (int n = 128; n <= 2048; n*=2) {
            double[][] matrixA = MatrixCreator.createRndMatrix(n,n);
            double[][] matrixB = MatrixCreator.createRndMatrix(n,n);
            
            naivStart = System.nanoTime();
            double[][] baseResult = myMtrxMulti.solve(MathProblem.MULT, Fact2D.fact(matrixA, matrixB));
            naivEnde = System.nanoTime();
            baseLine = naivEnde - naivStart; //b
  
            double[][] seriellResult = seriellmult.solve(MathProblem.MULT, Fact3D.fact(matrixA, matrixB, false));
            seriellEnde = System.nanoTime();
            optimised = seriellEnde - naivEnde; // o 
            
            double[][] parallelResult = parallelmult.solve(MathProblem.MULT, Fact3D.fact(matrixA, matrixB, true));
            parallelized = System.nanoTime()- seriellEnde; // p
            
            seriellSpeedUp = (double) baseLine/optimised;  // b/o
            parallelSpeedUp = (double) baseLine/parallelized;  // b/p
            speedUp = parallelSpeedUp/seriellSpeedUp;    // o/p
            
            double pi = 0.0;
            if (speedUp > 1) {
                int processors = Runtime.getRuntime().availableProcessors();
                double sigma = (processors - speedUp) / (speedUp * (processors - 1));
                pi =  (1 - sigma)*100;
            }

            System.out.println(String.format("%5d|%11d|%10d|%6.1f|%10d|%7.1f|%9.1f|%.1f", n, baseLine/1000, optimised/1000, seriellSpeedUp, parallelized/1000, (double)parallelSpeedUp, speedUp, pi));

            MyAssertEquals.assertMatrixEquals(baseResult, seriellResult, n*delta);
            MyAssertEquals.assertMatrixEquals(baseResult, parallelResult, n*delta);
        }
    }
    */
}
