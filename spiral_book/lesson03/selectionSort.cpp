#include <iostream>

using namespace std;

int selectionSort(int A[], int N);

int main() {
	int N, i, sw;
	scanf("%d", &N);

	int A[N];

	for (i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	sw = selectionSort(A, N);

	for (i = 0; i < N; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	// print number of swaps;
	printf("%d\n", sw);

	return 0;
}

int selectionSort(int A[], int N) {
	int count = 0;
	
	for (int i = 0; i < N; i++) {
		int minj = i;
		for (int j = i; j < N; j++) {
			if (A[j] < A[minj]) {
				minj = j;
			}
		}
		swap(A[i], A[minj]);
		if (i != minj) {
			count++;
		}
	}

	return count;
}
