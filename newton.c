#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float zero = 0.001;  // 微分係数 > 0 の許容範囲
float delta = 0.0001;  // |f(x)| の許容範囲

float f(float x);
float df(float x);
float newton(float xinit);

int main() {
	float xinit, x;

	xinit = 5.0;
	x = newton(xinit);

	printf("xinit = %f, delta = %f\n", xinit, delta);
	printf("zero x* = %f, f(x*) = %f\n", x, f(x));

	return 0;
}

float newton(float xinit) {
	float x, y, dy;

	x = xinit;
	y = f(x);

	// Newton 法の反復
	while (fabs(y) > delta) {
		dy = df(x);

		// 微分係数 = 0 のチェック
		if (fabs(dy) < zero) {
			printf("Error: derivative at x = %f is zero\n", x);
			exit(1);
		}

		// 次の反復解
		x = x - y / dy;
		y = f(x);
	}

	return x;
}

float f(float x) {
	float fx;

	fx = x*x*x - 10.0;

	return fx;
}

float df(float x) {
	float d;

	d = 3*x*x;

	return d;
}
