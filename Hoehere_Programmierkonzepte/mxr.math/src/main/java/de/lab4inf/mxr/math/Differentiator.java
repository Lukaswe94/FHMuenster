/*
 * Project: mxr.math
 *
 * Copyright (c) 2021,  Prof. Dr. Nikolaus Wulff
 * University of Applied Sciences, Muenster, Germany
 * Lab for computer sciences (Lab4Inf).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

package de.lab4inf.mxr.math;

/**
 * Numerical differentiation of functions, using a C library via JNI.
 *
 * @author nwulff
 * @since 28.11.2021
 */
public class Differentiator {
	/** the default precision for derivatives. */
	public final static double EPS = 5.E-10;
	/** static loading of the the JNI library. */
	static {
		try {
			//System.load("/home/souhail/Desktop/gite/pg6_g5-mxr/mxr.math/build/libs/mxr_math/shared/libmxr_math.so");
			System.loadLibrary("mxr_math");
			
		} catch(Throwable error) {
			System.err.println(error);
		}	
	}

	/**
	 * hidden constructor for a utility class.
	 */
	Differentiator() {
	}

	/**
	 * Return the differential function f' for a given function f.
	 * 
	 * @param f function to use
	 * @return f' the differential function
	 */
	public static MXRFunction differential(MXRFunction f) {
		return (x) -> differentiate(f, x, EPS);
	}
	/**
	 * Calculate the result f'(x) with default precision.
	 * 
	 * @param f function to differentiate.
	 * @param x argument to use
	 * @return f'(x) the value of the differentiation
	 */
	public static double differentiate(MXRFunction f, double x) {
		return diff(f,x,EPS);
	}
	/**
	 * Calculate the result f'(x) for given precision.
	 * 
	 * @param f function to differentiate.
	 * @param x argument to use
	 * @param eps precision to reach
	 * @return f'(x) the value of the differentiation
	 */
	public static double differentiate(MXRFunction f, double x, double eps) {
		return diff(f,x,eps);
	}
    /**
     * Native call to the C/C++ implementation to calculate f'(x).
     * @param f function to differentiate
     * @param x argument for the function
     * @param eps precision to reach
     * @return f'(x)
     */
	public static native double diff(MXRFunction f, double x, double eps);

}