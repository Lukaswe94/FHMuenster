package de.lab4inf.mxr.math;

import static java.lang.Math.abs;
import static java.lang.Math.max;
import static java.lang.String.format;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Objects;

import org.junit.jupiter.api.Test;

class PraktikumIVTest {
	double eps = 2 * Differentiator.EPS;
	MXRFunction sinFct = (x) -> Math.sin(x);
	MXRFunction cosFct = (x) -> Math.cos(x);
	MXRFunction expFct = (x) -> Math.exp(x);
	MXRFunction logFct = (x) -> Math.log(x);
	MXRFunction hypFct = (x) -> 1.0/x;
	MXRFunction idFct  = (x) -> x;
	MXRFunction oneFct = (x) -> 1;
	@SuppressWarnings("null")
	MXRFunction f, dF;
    int calls,maxCalls=16;
    int supCalls= 0; 
    
	class CountingFunction implements MXRFunction {
		MXRFunction kernel;

		@SuppressWarnings("null")
		CountingFunction(MXRFunction kern) {
			kernel = Objects.requireNonNull(kern);
		}
		@Override
		public double eval(double x) {
			calls++;
			return kernel.eval(x);
		}
	}
	
	
	
	@Test
	void testDifferentiateX() {
		double x, expected, returned;
		maxCalls = 4;
		f = new CountingFunction(idFct);
		dF = oneFct;
		for (x = -2; x < 5; x += 0.25) {
			calls = 0;
			expected = dF.eval(x);
			returned = Differentiator.differentiate(f, x, eps);
			assertEquals(expected, returned, eps);
			assertTrue(calls<=maxCalls,format("iterations: %d>%d",calls,maxCalls));
		}
	}


	@Test
	void testDifferentiateSine() {
		f = new CountingFunction(sinFct);
		dF = cosFct;
		double x, expected, returned;
		for (x = -2; x < 5; x += 0.25) {
			calls = 0;
			expected = dF.eval(x);
			returned = Differentiator.differentiate(f, x, eps);
			assertEquals(expected, returned, eps);
			assertTrue(calls<=maxCalls,format("iterations: %d>%d",calls,maxCalls));
		}
	}

	@Test
	void testDifferentiateExp() {
		f = new CountingFunction(expFct);
		dF = expFct;
		double x, expected, returned, delta;
		for (x = -5; x < 5; x += 0.25) {
			calls = 0;
			expected = dF.eval(x);
			returned = Differentiator.differentiate(f, x, eps);
			delta = eps*max(1,abs(expected));
			assertEquals(expected, returned, delta);
			assertTrue(calls<=maxCalls,format("iterations: %d>%d",calls,maxCalls));
		}
	}

	@Test
	void testDifferentiateLog() {
		f = new CountingFunction(logFct);
		dF = hypFct;
		maxCalls = 32;
		double x, expected, returned, delta;
		for (x = 0.01; x < 5; x += 0.25) {
			System.out.println("x= "+ x);
			calls = 0;
			expected = dF.eval(x);
			returned = Differentiator.differentiate(f, x, eps);
			delta = eps*max(1,abs(expected));
			if(calls > supCalls)
				supCalls= calls;
			System.out.println("supCalls- ist "+ supCalls);
			assertEquals(expected, returned, delta);
			assertTrue(calls<=maxCalls,format("iterations: %d>%d",calls,maxCalls));
		}
	}

	@Test
	void testDifferentiateHyperbola() {
		f = new CountingFunction(hypFct);
		dF = (x)-> -(hypFct.eval(x)*hypFct.eval(x));
		maxCalls = 32;
		double x, expected, returned, delta;
		for (x = 0.01; x < 5; x += 0.25) {
			calls = 0;
			expected = dF.eval(x);
			returned = Differentiator.differentiate(f, x, eps);
			delta = eps*max(1,abs(expected));
			assertEquals(expected, returned, delta);
			assertTrue(calls<=maxCalls,format("iterations: %d>%d",calls,maxCalls));
		}
	}

	@Test
	void testDifferentialX() {
		double x, expected, returned;
		f = idFct;
		dF = oneFct;
		MXRFunction dy = Differentiator.differential(f);
		for (x = -2; x < 5; x += 0.25) {
			expected = dF.eval(x);
			returned = dy.eval(x);
			assertEquals(expected, returned, eps);
		}
	}

	@Test
	void testDifferentialSine() {
		double x, expected, returned;
		f = sinFct;
		dF = cosFct;
		MXRFunction dy = Differentiator.differential(f);
		for (x = -2; x < 5; x += 0.25) {
			expected = dF.eval(x);
			returned = dy.eval(x);
			assertEquals(expected, returned, eps);
		}
	}

	@Test
	void testDifferentialExp() {
		double x, delta,expected, returned;
		f = expFct;
		dF = expFct;
		MXRFunction dy = Differentiator.differential(f);
		for (x = -2; x < 5; x += 0.25) {
			expected = dF.eval(x);
			returned = dy.eval(x);
			delta = eps*max(1,abs(expected));
			assertEquals(expected, returned, delta);
		}
	}
	@Test
	void testDifferentialLog() {
		double x, delta,expected, returned;
		f = logFct;
		dF = hypFct;
		MXRFunction dy = Differentiator.differential(f);
		for (x = 0.5; x < 5; x += 0.25) {
			expected = dF.eval(x);
			returned = dy.eval(x);
			delta = eps*max(1,abs(expected));
			assertEquals(expected, returned, delta);
		}
	}
}
