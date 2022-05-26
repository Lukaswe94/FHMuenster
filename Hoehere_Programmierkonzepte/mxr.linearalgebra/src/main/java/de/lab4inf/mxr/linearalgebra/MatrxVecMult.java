package de.lab4inf.mxr.linearalgebra;

import static java.lang.String.format;

import java.util.Objects;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class MatrxVecMult implements Mops<MathProblem, Fact2D<double[][], double[]>, double[]> {

	@Override
	public double[] solve(MathProblem p, Fact2D<double[][], double[]> facts) throws NoSolutionException {
		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");

		if (!p.equals(MathProblem.MULT))
			throw new IllegalArgumentException(format("wrong problem"));

		double[][] matrix = facts.u;
		double[] vector = facts.v;

		if (matrix[0].length != vector.length)
			throw new IllegalArgumentException("Multiplication is because of the dimensions not possible");

		double[] result = new double[matrix.length]; 
		
		for (int i =0; i< result.length; i++)
			for (int j=0; j<matrix[0].length; j++)
				result[i] += matrix[i][j]*vector[j]; 
		return result;
	}
}
