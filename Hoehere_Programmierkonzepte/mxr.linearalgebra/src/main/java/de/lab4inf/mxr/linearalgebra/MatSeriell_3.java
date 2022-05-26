package de.lab4inf.mxr.linearalgebra;

import static java.lang.String.format;
import java.util.Objects;

import de.lab4inf.mxr.core.*;
import de.lab4inf.mxr.linearalgebra.tools.*;

public class MatSeriell_3 implements Mops<MathProblem, Fact3D<double[][], double[][], Boolean>, double[][]> {

	@Override
	public double[][] solve(MathProblem p, Fact3D<double[][], double[][], Boolean> facts) throws NoSolutionException {

		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");
		

		if (!MathProblem.MULT.equals(p) || facts.w != false)
			throw new IllegalArgumentException(format("wrong problem"));
		
		double[][] matrix1 = facts.u; 
		double[][] matrix2 = facts.v; 
		double[][] transposeMat;
		
		if(( matrix1[0].length != matrix2.length)  ) 
			throw new IllegalArgumentException("* Operation is impossible. The matrices have different dimensions");

		@NonNull
		double[][] result = new double[matrix1.length][matrix2[0].length];
		
		transposeMat = MatrixCreator.transponieren(matrix2);
		
		for(int i = 0; i< result.length; i++) {
			for(int j = 0; j<result[0].length; j++) {
				for(int k = 0; k<matrix1[0].length; k++) {
					result[i][j] += matrix1[i][k] * transposeMat[j][k];
				}
			}
		}
		return result;
	}

}
