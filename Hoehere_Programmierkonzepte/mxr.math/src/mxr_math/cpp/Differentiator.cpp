#include <stdio.h>
#include <math.h>
#include<float.h>
#include "Differentiator.h"

double differentiate(Function &f, double x, double eps)
{
	/*
	double h = 0.00001;
	return (f(x+h)-f(x-h))/(2*h);
	 */


	int n;
	double actualAblt, lastAblt, oldDelta, delta;

	double h = 1e-5;
	//double h= pow(DBL_EPSILON*2.0, (1.0/3.0));

	actualAblt = (f(x+h)-f(x-h))/(2.0*h);
	delta = 25000;


	do {
		oldDelta = delta;
		lastAblt=actualAblt;
		h = h/2.0;
		actualAblt = (f(x+h)-f(x-h))/(2.0*h);
		delta=abs(lastAblt-actualAblt);
 	//} while(delta>eps && delta<oldDelta && h>1e-9);
	} while(delta>eps && delta<oldDelta);

	//} while(delta>eps);
		return actualAblt;
}



