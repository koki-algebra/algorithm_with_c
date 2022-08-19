#include <stdio.h>
#include <stdlib.h>

void bubleSort(int *A, int k, int l, int N);
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

	bubleSort(A, 0, N-1, N);

	return 0;
}

void bubleSort(int *A, int k, int l, int N) {
	int count = 0;
	bool flag = true;
	int i;

	while (flag) {
		flag = false;
		for (i = l; i > 0; i--) {
			if (A[i] < A[i-1]) {
				// swap A[i] and A[i-1]
				int tmp = A[i];
				A[i] = A[i-1];
				A[i-1] = tmp;

				// count up
				count++;
				flag = true;
			}
		}
	}

	// print sorted array
	printArray(A, k, l, N);
	// print number of swaps
	printf("%d\n", count);
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
