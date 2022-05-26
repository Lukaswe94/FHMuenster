package de.lab4inf.mxr.linearalgebra;

import static java.lang.String.format;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import de.lab4inf.mxr.core.Fact3D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;
import de.lab4inf.mxr.linearalgebra.tools.MatrixCreator;

public class MatParallel_3 implements Mops<MathProblem, Fact3D<double[][], double[][], Boolean>, double[][]> {



	@Override
	public double[][] solve(MathProblem p, Fact3D<double[][], double[][], Boolean> facts) throws NoSolutionException {

		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");
		

		if (!MathProblem.MULT.equals(p) || facts.w != true)
			throw new IllegalArgumentException(format("wrong problem"));
		
		double[][] matrix1 = facts.u; 
		double[][] matrix2 = facts.v; 

		
		if(( matrix1[0].length != matrix2.length)  ) 
			throw new IllegalArgumentException("* Operation is impossible. The matrices have different dimensions");

		double[][] result = new double[matrix1.length][matrix2[0].length];
		double[][] transposeMat = MatrixCreator.transpose(matrix2);

		ExecutorService executor = Executors.newFixedThreadPool(16);
		List<Callable<Object>> tasks = new ArrayList<>();
		for(int i = 0; i<result.length; i++) {
			final int tnum = i;
			tasks.add(Executors.callable(()->{
				for(int j = 0;j<result[0].length; j++) {
					for(int k = 0; k< matrix1[0].length;k++) {
						result[tnum][j] += matrix1[tnum][k] * transposeMat[j][k];
					}
				}
			}));
		}
		try {
			executor.invokeAll(tasks);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		return result;
		
	}
}
