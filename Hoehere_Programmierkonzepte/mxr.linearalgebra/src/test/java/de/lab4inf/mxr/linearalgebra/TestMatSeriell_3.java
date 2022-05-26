package de.lab4inf.mxr.linearalgebra;

import java.util.Random;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Fact3D;
import de.lab4inf.mxr.core.FactFactory;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

class TestMatSeriell_3 {

	
	double[][] expected;
	double[][] result;
	static double tolerance = 5E-12;
	Random r = new Random();


	Mops<MathProblem, Fact3D<double[][], double[][], Boolean>, double[][]> matSeriellmult;
	Mops<MathProblem, Fact2D<double[][], double[][]>, double[][]> resultmult;
	
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
		matSeriellmult = new MatSeriell_3();
		resultmult = new MatrxMult();
	}

	@Test
	void multtest() {
		Fact3D<double[][], double[][], Boolean> facts3d = FactFactory.facts(m1, m3, false);
		Fact2D<double[][], double[][]> facts2d = FactFactory.facts(m1, m3);
		expected = resultmult.solve(MathProblem.MULT, facts2d);
		result = matSeriellmult.solve(MathProblem.MULT, facts3d);
		MyAssertEquals.assertMatrixEquals(expected, result, tolerance);
	}

}
