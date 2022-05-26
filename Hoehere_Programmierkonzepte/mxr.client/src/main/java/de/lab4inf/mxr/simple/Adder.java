package de.lab4inf.mxr.simple;

import static java.lang.String.format;

import java.util.Objects;

import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.core.NonNull;

public class Adder implements Mops<String, Fact2D<Double, Double>, Double> {
	final static String PROBLEM = "ADD_NUM";

	@Override
	@NonNull
	public Double solve(String p, Fact2D<Double, Double> facts) throws NoSolutionException {

		Double result = 0.0;

		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");

		if (!PROBLEM.equals(p))
			throw new IllegalArgumentException(format("wrong problem %s != %s", p, PROBLEM));

		// Cast était faux !! PK ?
		// Erst zur Laufzeit
		// Double[] myDoubleArray = (Double[]) facts.arguments();

		result = Double.sum(facts.u, facts.v);

		return result;
	}

}
