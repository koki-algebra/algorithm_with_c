#include <stdio.h>
#include <stdlib.h>
#define N 500

void bubblesort(int h, int k, int *A);
void swap(int i, int j, int *A);

int main() {
	int A[N];
	int n, i;
	FILE *file;

	file = fopen("sortdata.txt", "r");
	fscanf(file, "%d", &n);
	if (n > N) {
		printf("Illegal array size n = %d for N = %d\n", n, N);
		exit(1);
	}

	printf("n = %d\nA = ", n);
	for (i = 0; i < n; i++) {
		fscanf(file, "%d", &A[i]);
	}
	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	// A[0] ~ A[n-1] をソート
	bubblesort(0, n-1, A);
	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}

// bubblesort A[k], ..., A[h] をバブルソート
void bubblesort(int h, int k, int *A) {
	int i, j;
	int test;  // tet == 1; 既にソート済み

	for (i = h; i < k; i++) {
		test = 1;
		for (j = k; j >= i+1; j--) {
			if (A[j] < A[j-1]) {
				swap(j, j-1, A);
				test = 0;
			}
		}

		if (test == 1) {
			return;
		}
	}

	return;
}

// swap A[i] and A[j]
void swap(int i, int j, int *A) {
	int tmp;
	tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;

	return;
}