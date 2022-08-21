#include <cstdio>

int main() {
	int n, q, i, j;
	int count = 0;

	// create array S
	scanf("%d", &n);
	int S[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &S[i]);
	}

	// create array T
	scanf("%d", &q);
	int T[q];
	for (i = 0; i < q; i++) {
		scanf("%d", &T[i]);
	}

	// linear search
	for (i = 0; i < n; i++) {
		for (j = 0; j < q; j++) {
			if (S[i] == T[j]) {
				count++;
			}
		}
	}

	// print result
	printf("%d\n", count);

	return 0;
}
