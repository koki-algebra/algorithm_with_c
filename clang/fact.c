#include <stdio.h>
#include <stdlib.h>

int fact(int n);

int main() {
	int n;

	n = 5;
	printf("factorial of n = %d is %d\n", n, fact(n));
}

int fact(int n) {
	if (n < 0) {
		printf("Illegal input n = %d\n", n);
		exit(1);
	} else {
		if (n == 0) {
			return 1;
		} else {
			return n * fact(n - 1);
		}
	}
}