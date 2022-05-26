package de.lab4inf.mxr.linearalgebra;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Fact3D;

import de.lab4inf.mxr.core.MXR;
import de.lab4inf.mxr.linearalgebra.tools.MathProblem;

public class LinearAlgebraPlugin implements MXR.Plugin {

	@Override
	public void init(MXR container) {
		
		double[] vector = new double[0];
		double[][] matrix = new double[0][0];
		
		container.register(MathProblem.ADD, Fact2D.fact(vector, vector), new VecAdder());
		container.register(MathProblem.MULT, Fact2D.fact(vector, vector), new VecMult());
		container.register(MathProblem.ADD, Fact2D.fact(matrix, matrix), new MatrxAdder());
		container.register(MathProblem.MULT, Fact2D.fact(matrix, matrix), new MatrxMult());
		container.register(MathProblem.MULT, Fact2D.fact(matrix, vector), new MatrxVecMult());		
		container.register(MathProblem.OPTMULT, Fact3D.fact(matrix, matrix, false), new MatrxMultOptimized());
	}

}