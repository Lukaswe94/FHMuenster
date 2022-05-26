package de.lab4inf.mxr.core;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class MXRTest {
	boolean initialized = false;
	/** Mock for a Plugin during test. */
    class PluginMock implements MXR.Plugin {
		@Override
		public void init(MXR container) {
			initialized = true;
		}
    }
    /** Mock for a MXR Engine during test. */
    class MXRMock implements MXR {

		static final String MOCK_WITHOUT_IMPLEMENTATION = "Mock without implementation";

		@Override
		public <Problem, Facts extends Fact, Solution> Solution solve(Problem p, Facts facts)
				throws NoSolutionException {
			throw new IllegalStateException(MOCK_WITHOUT_IMPLEMENTATION);
		}

		@Override
		public <Problem, Facts extends Fact, Solution> Mops<Problem, Facts, Solution> findSolver(Problem p, Facts facts)
				throws NoSolverException {
			throw new IllegalStateException(MOCK_WITHOUT_IMPLEMENTATION);
		}

		@Override
		public <Problem, Facts extends Fact, Solution> void register(Problem p, Fact facts,
				Mops<Problem, Facts, Solution> solver) {
			throw new IllegalStateException(MOCK_WITHOUT_IMPLEMENTATION);
		}
    	
    }
    /**
     * Test that no MXR engine is accidently deployed in the core project.
     */
	@Test
	void testGetEngine() {
		assertThrows( IllegalStateException.class, MXR::getEngine);
	}
    /**
     * Test that the default plugin registration behaves ok.
     */
	@Test
	void testRegisterPlugin() {
		MXR engine = new MXRMock();
		MXR.Plugin plugin = new PluginMock();
		engine.register(plugin);
		assertTrue(initialized,"plugin not initialized");
	}

}
