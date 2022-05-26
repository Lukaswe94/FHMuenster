package de.lab4inf.mxr.linearalgebra;

import static java.lang.String.format;

import java.util.Objects;
import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.core.NonNull;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class MatrxMult implements Mops<MathProblem, Fact2D<double[][], double[][]>, double[][]>{

	@Override
	public double[][] solve(MathProblem p, Fact2D<double[][], double[][]> facts) throws NoSolutionException {
		
		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");
		

		if (!MathProblem.MULT.equals(p))
			throw new IllegalArgumentException(format("wrong problem"));
		
		double[][] matrix1 = facts.u; 
		double[][] matrix2 = facts.v; 
		
		int spaltenZahl1 = matrix1[0].length;
		int zeilenZahl1 = matrix1.length; 
	
		int spaltenZahl2 = matrix2[0].length;
		int zeilenZahl2 = matrix2.length; 
		
		if( (spaltenZahl1 != zeilenZahl2) ) 
			throw new IllegalArgumentException("* Operation is impossible. The matrices have different dimensions");

		@NonNull
		double[][] result = new double[zeilenZahl1][spaltenZahl2];
		
	
		for(int i=0; i< result.length; i++ )
			for( int j=0; j < result[0].length; j++)
				for( int k=0 ; k< spaltenZahl1; k++)
					result[i][j] += matrix1[i][k]* matrix2[k][j];			
		
		return result; 
	}

	
	
}
