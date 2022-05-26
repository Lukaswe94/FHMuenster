package de.lab4inf.mxr.linearalgebra;

import static java.lang.String.format;

import java.util.Objects;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class KreuzProdukt implements Mops<MathProblem, Fact2D<double[], double[]> , double[]> {

	@Override
	public double[] solve(MathProblem p, Fact2D<double[], double[]> facts) throws NoSolutionException {
	
		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");

		if (!MathProblem.KRMULT.equals(p))
			throw new IllegalArgumentException(format("wrong problem"));
		
		int size1= facts.u.length; 
		int size2 = facts.v.length;
		
		if( size1 != size2 || size1!=3)
			throw new IllegalArgumentException("not the same size of vectors");

		double[] result = new double[3];
		
		result[0]= facts.u[1]*facts.v[2]- facts.u[2]*facts.v[1];
		result[1]= facts.u[2]*facts.v[0]- facts.u[0]*facts.v[2];
		result[2]= facts.u[0]*facts.v[1]- facts.u[1]*facts.v[0];

		return result;
		
	}

}
