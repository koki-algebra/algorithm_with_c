#include <stdio.h>
#include <stdlib.h>
#define N 500

void insert(int x, int *A, int *n);
int deletemin(int *A, int *n);
void upmin(int i, int *A, int n);
void downmin(int i, int *A, int n);
void swap(int i, int j, int *A);

int main() {
	int A[N];
	int n, i, k, min;

	n = 0;
	for (k = 0; k < 10; k++) {
		insert(100 - (5-i) * (5-i), A, &n);
		printf("n = %d\nA = ", n);
		for (i = 0; i < n; i++) {
			printf("%d ", A[i]);
		}
		printf("\n");
	}

	for (k = 0; k < 10; k++) {
		min = deletemin(A, &n);
		printf("n = %d, min = %d\nA = ", n, min);
		for (i = 0; i < n; i++) {
			printf("%d ", A[i]);
		}
		printf("\n");
	}

	return 0;
}

void insert(int x, int *A, int *n) {
	int n1;
	 n1 = *n;
	 if (n1 >= N) {
		printf("Error: Heap A is full.\n");
		exit(1);
	 }

	 A[n1] = x;  // 末尾へ x を置く
	 upmin(n1, A, n1+1);
	 *n = n1 + 1;

	 return;
}

int deletemin(int *A, int *n) {
	int min, n1;

	n1 = *n;
	if (n1 < 1) {
		printf("Error: Heap is empty.\n");
		exit(1);
	}

	min = A[0];
	A[0] = A[n1 - 1];

	if (n1 > 1) {
		downmin(0, A, n1 - 1);
	}

	*n = n1 - 1;

	return min;
}

void upmin(int i, int *A, int n) {
	int j;

	if (i < 0 || i >= n) {
		printf("Illegal element i = %d for n = %d\n", i, n);
		exit(1);
	}

	if (i == 0) {  // root に到達すれば終了
		return;
	}
	j = (i - 1) / 2;  // i の親

	if (A[j] > A[i]) {
		swap(i, j, A);
		upmin(j, A, n);
	}

	return;
}

// downmin A[i] から下方へ, ヒープ条件回復のための swap 操作を適用
void downmin(int i, int *A, int n) {
	int j;

	if (i < 0 || i >= n) {
		printf("Illegal element i = %d for n = %d\n", i, n);
		exit(1);
	}

	j = 2 * i + 1;  // i の左の子
	if (j >= n) {
		return;
	}

	if (j + 1 < n && A[j] > A[j+1]) {
		j = j + 1;
	}

	if (A[j] < A[i]) {
		swap(i, j, A);
		downmin(j, A, n);
	}

	return;
}

void swap(int i, int j, int *A) {
	int tmp;
	tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;

	return;
}
