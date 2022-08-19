#include <stdio.h>
#include <stdlib.h>

void insertSort(int *A, int k, int l, int N);
void printArray(int *A, int k, int l, int N);

int main() {
	int N;
	int i;

	// input array size N
	scanf("%d", &N);

	int A[N];
	// input array
	for (i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	// run insert sort
	insertSort(A, 0, N-1, N);

	return 0;
}

// insertSort merge sort A[k] ~ A[l]
void insertSort(int *A, int k, int l, int N) {
	if (k < 0 || l >= N) {
		printf("invalid index k or l\n");
		exit(1);
	}

	int i, j;

	for (i = k; i <= l; i++) {
		int v = A[i];

		for (j = i - 1; j >= 0 && A[j] > v; j--) {
			A[j+1] = A[j];
		}
		A[j+1] = v;

		printArray(A, k, l, N);
	}
}

// printArray print A[k] ~ A[l]
void printArray(int *A, int k, int l, int N) {
	if (k < 0 || l >= N) {
		printf("invalid index k or l\n");
		exit(1);
	}

	int i;
	for (i = k; i <= l; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
}
