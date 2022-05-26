package de.lab4inf.mxr.linearalgebra.tools;

import java.util.Random;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class MatrixCreator {
	static Random rnd = new Random();

	public static double[] createRndVector(int n) {
		double[] x = new double[n];
		for (int i = 0; i < n; i++) {
			x[i] = rnd.nextDouble();
		}
		return x;
	}

	// create random Matrix (n,m)
	public static double[][] createRndMatrix(int n, int m) {
		double[][] a = new double[n][m];
		for (int i = 0; i < n; i++) {
			a[i] = createRndVector(m);
		}
		return a;
	}

	public static double[][] createHilbertMatrix(int n) {
		double hilbert[][] = new double[n][n];

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				hilbert[i - 1][j - 1] = 1.0 / (i + j - 1.0);
			}
		}
		return hilbert;
	}

	public static double fakult(int n) {
		double fakult = 1.0;
		for (int i = 2; i <= n; i++) {
			fakult *= i;
		}
		return fakult;
	}

	public static double[][] createInverseHilbertMatrix(int n) {
		double hilbInverse[][] = new double[n][n];

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				hilbInverse[i - 1][j - 1] = (Math.pow(-1, i + j) * fakult(i + n - 1) * fakult(j + n - 1))
						/ (Math.pow(fakult(i - 1), 2) * Math.pow(fakult(j - 1), 2) * fakult(n - j) * fakult(n - i)
								* (i + j - 1));
			}
		}
		return hilbInverse;
	}
	

	public static double[][] createIdMatrix(int n) {
		double[][] idMAtrix = new double[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					idMAtrix[i][j] = 1.0;
				} else {
					idMAtrix[i][j] = 0.0;
				}
			}
		}
		return idMAtrix;
	}
	

	public static double[][] transponieren(double[][] a) {
		double[][] transponiert = new double[a[0].length][a.length];
		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < a[0].length; j++) {
				transponiert[j][i] = a[i][j];
			}
		}
		return transponiert;
	}


	public static double[][] transpose(final double[][] matrix) {
	    return IntStream.range(0, matrix[0].length)
	    		.parallel()
	    		.mapToObj(i -> Stream.of(matrix).mapToDouble(row -> row[i])
	    		.toArray()).toArray(double[][]::new);
	}
	
	//
	public static double vectorSkalarProdukt(double[] a, double[] b) {
		double result = 0.0;
		for (int i = 0; i < a.length; i++) {
			result += a[i]*b[i]; 
		}
		return result;

	}
}
