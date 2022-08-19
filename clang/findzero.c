#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float epsilon = 0.0001;
float delta = 0.0001;

float findzero(float a, float b);
float f(float x);

int main() {
	float a, b, x;

	a = 0.0;
	b = 10.0;
	x = findzero(a, b);

	printf("a = %f, b = %f, epsilon = %f, delta = %f\n", a, b, epsilon, delta);
	printf("zero x* = %f, f(x*) = %f\n", x, f(x));

	return 0;
}

float findzero(float a, float b) {
	float xL, xR, xM, fx;

	xL = a;
	xR = b;
	if (f(a) > delta || f(b) < -delta) {
		printf("There is no zero f(x) = 0\n");
		exit(1);
	}

	while (xR - xL > epsilon) {
		xM = (xL + xR) / 2.0;
		fx = f(xM);

		if (fabs(fx) <= delta) {
			return xM;
		}
		if (fx <= 0.0) {
			xL = xM;
		} else {
			xR = xM;
		}
	}

	return xL;
}

float f(float x) {
	float fx;

	fx = x*x*x - 10.0;

	return fx;
}
