#include "Differentiator.h"
#include "Function.h"
#include <math.h>
#include <stdio.h>
#include<float.h>


double minus_sinus(double x){
	return -sin(x);
}

double id(double x){
	return x;
}

double one_fct(double x){
	return 1;
}

double x_quadrat(double x) {
	return x*x;
}

double zwei_x(double x) {
	return 2*x;
}

double dlog(double x) {
	return 1.0/x;
}

double hyp(double x){
	return 1.0/x;
}

double dhyp(double x){
	return -1.0/(x*x);
}


void testF (FctPointer myf, FctPointer mydf, double von, double bis) {
	double dy, eps=5.E-10,x;

		Function f = Function(myf);
		Function df = Function(mydf);

		for (x = von; x <= bis; x += 0.25) {
				dy = differentiate (f, x, eps);
				printf(" x: %f ",x);
				assert(abs(dy - df(x)) < eps);
			}
		printf("\terfolgreich\n\n");
}


int main(int argc, char *argv[])
{
	printf("sin(x) Test:\n");
	testF(sin, cos , 0, 1);

	printf("cos(x) Test:\n");
	testF(cos, minus_sinus, 0, 1);

	printf("exp(x) Test:\n");
	testF(exp, exp, 0, 2);

	printf("x Test:\n");
	testF(id,one_fct , 0, 1);

	printf("x² Test:\n");
	testF(x_quadrat , zwei_x , 0, 1);

	printf("log(x) Test:\n");
	testF(log , dlog, 0.1, 5);


}


