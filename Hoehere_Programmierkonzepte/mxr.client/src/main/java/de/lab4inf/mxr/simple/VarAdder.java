package de.lab4inf.mxr.simple;

import static java.lang.String.format;

import java.util.Objects;

import de.lab4inf.mxr.core.FactVA;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.core.NonNull;

public class VarAdder <T extends Number> implements Mops<String,FactVA<T>, Double> {
	
	
	final static String PROBLEM = "ADD_VARNUM";

	@Override
	public Double solve(String p, FactVA<T> facts) throws NoSolutionException {
		
		@NonNull
		double result=0.0; 
		//T resultat; 
		
		Objects.requireNonNull(p, "no problem given");
		Objects.requireNonNull(facts, "no fact(s) given");
		
		if (!PROBLEM.equals(p))
			throw new IllegalArgumentException(format("wrong problem %s != %s",p, PROBLEM));
		
		
		//TODO : überprüfen dass die übergebenen Fact Parameter Doubles sind fehlt (Version : implement <String, Fact, Double>  )
		// Jetzt brauchen wir das nicht mehr zu machen .. (Version : implement Mops<String, FactVA<Double>, Double> 
		// Jetzt gar kein Cast nötig: wir wissen dass die zurückgebeenen Values bom Typ Double sind
		
		//Number zahl1= 1;
		//Number zahl2 = 3;
		//Number res = zahl1 + zahl2;
		
		
		for (T i : facts.values()) {	
			
			
			result += i.doubleValue();
		}
		
		return result; 
	}

}			
