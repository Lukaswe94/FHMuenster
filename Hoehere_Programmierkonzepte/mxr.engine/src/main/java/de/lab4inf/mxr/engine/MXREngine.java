/**
 * 
 */
package de.lab4inf.mxr.engine;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import de.lab4inf.mxr.core.Fact;
import de.lab4inf.mxr.core.MXR;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;
import de.lab4inf.mxr.core.NoSolverException;


/**
 * @author lukas
 *
 */
public class MXREngine implements MXR{
	
	private Map<Key<?, ?>, Mops<?,?,?>> MXRContainer; 
	/*
	 * Pojo Constructor
	 * 
	 */
	public MXREngine() {
		this.MXRContainer = new HashMap<Key<?, ?>, Mops<?, ?, ?>>();
	}
	@Override
	public <Problem, Facts extends Fact, Solution> Solution solve(Problem p, Facts facts) throws NoSolutionException {
		Solution solution;
		try {
		Mops<Problem,Facts,Solution> solver = this.findSolver(p, facts);
		solution = solver.solve(p, facts);
		}catch(NoSolverException e) {
			throw new NoSolutionException(e);
		}
		return solution;
	}

	@SuppressWarnings("unchecked")
	@Override
	public <Problem, Facts extends Fact, Solution> Mops<Problem, Facts, Solution> findSolver(Problem p, Facts facts)
			throws NoSolverException {
			Key<Problem, Facts> solverKey = new Key<>(p, facts);
			if(this.MXRContainer.containsKey(solverKey)){
				return (Mops<Problem, Facts, Solution>)this.MXRContainer.get(solverKey);
			}
			else throw new NoSolverException("No Solver found");
	}
	
	@Override
	public <Problem, Facts extends Fact, Solution> void register(Problem p, Fact facts,
			Mops<Problem, Facts, Solution> solver) {
		p = Objects.requireNonNull(p);
		facts = Objects.requireNonNull(facts);
		Key<Problem, Fact> key = new Key<>(p, facts);
		this.MXRContainer.put(key, solver);	
	}
	public Map<?, ?> getMap(){
		return this.MXRContainer;
	}
}