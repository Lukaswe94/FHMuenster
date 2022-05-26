package de.lab4inf.mxr.engine;

import static org.junit.jupiter.api.Assertions.*;



import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import de.lab4inf.mxr.core.Fact;
import de.lab4inf.mxr.core.Fact2D;
import de.lab4inf.mxr.core.FactFactory;
import de.lab4inf.mxr.core.FactVA;
import de.lab4inf.mxr.core.MXR;
import de.lab4inf.mxr.core.Mops;
import de.lab4inf.mxr.core.NoSolutionException;

class MXREngineTester {
	
	final static String PROBLEM = "ADD_NUM";
	final static String VAR_PROBLEM = "ADD_VARNUM";
	
	Mops<String, Fact2D<Double, Double>, Double> myAdder;
	Mops<String, FactVA<Double>, Double> myVarDoubleAdder;
	FactVA<Double> va;
	Fact dummy1D;
	Fact dummy2D;
	Fact dummy3D;
	MXREngine engine;
	
	@BeforeEach
	void setUp() throws Exception {
		myAdder = new Adder();
		myVarDoubleAdder = new VarAdder<>();
		engine = new MXREngine();
		dummy2D = FactFactory.facts(1.0, 2.0);
		dummy3D = FactFactory.facts(1.0, 2.0, 3.0);
		engine.register(MXREngineTester.PROBLEM, dummy2D, myAdder);
		va = new FactVA<>(1.0, 5.0, 7.0, 13.5);
	}
	@Test
	void testRegister() {
		engine.register(MXREngineTester.PROBLEM, dummy2D, myAdder);
		assertFalse(engine.getMap().isEmpty());
	}
	@Test 
	void testRegisterException() {
		assertThrows(NullPointerException.class,()-> engine.register(null, dummy1D, myAdder));
	}
	@Test
	void testFindSolver() {
		Mops<String, Fact2D<Double, Double>, Double> add1 = new Adder();
		Mops<String, FactVA<Double>, Double> varAdd1 = new VarAdder<Double>();
		engine.register(MXREngineTester.PROBLEM, dummy2D, add1);
		engine.register(MXREngineTester.VAR_PROBLEM, va, varAdd1);
		assertNotNull(engine.findSolver("ADD_VARNUM", va));
		
	}
	
	@Test 
	@Disabled
	void testSolve(){
		engine.register(MXREngineTester.PROBLEM, dummy2D, myAdder);
		engine.register(MXREngineTester.VAR_PROBLEM, va, myVarDoubleAdder);
		Double retVal = engine.solve("ADD_NUM", dummy2D);
		assertEquals(3.0, retVal);
		retVal = engine.solve("ADD_VARNUM", va);
		assertEquals(26.5, retVal);
	}
	@Test 
	void testNoSolution(){
		assertThrows(NoSolutionException.class, ()-> engine.solve("ADD_VARNUM", va));
	}
	
	@Test 
	void testSolveWithGetEngine(){
		MXR myEngine = MXR.getEngine(); 		
		assert(engine.getClass() == myEngine.getClass()); 	
		
		myEngine.register(MXREngineTester.PROBLEM, dummy2D, myAdder);
		Double retVal = myEngine.solve(MXREngineTester.PROBLEM, dummy2D);
		assertEquals(3.0, retVal);
	}
	
	
	
}