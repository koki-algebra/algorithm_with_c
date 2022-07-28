#include <stdio.h>
#include <stdlib.h>
#define N 500

void heapsort(int *A, int n);
void heapify(int *A, int n);
void downmax(int i, int *A, int n);
int deletemax(int *A, int n);
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
	printf("\nA = ");

	heapsort(A, n);

	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}

void heapsort(int *A, int n) {
	int i;

	// 配列 A をヒープ化. ただし root は最大要素
	heapify(A, n);

	// 最大要素を末尾へ
	for (i = n - 1; i > 0; i--) {
		A[i] = deletemax(A, i+1);
	}
}

// hearpify A[0],...,A[n-1] をヒープ化
void heapify(int *A, int n) {
	int i;
	for (i = n/2-1; i >= 0; i--) {
		downmax(i, A, n);
	}
}

// downmax A[i] から下方へ,ヒープの性質を回復するための swap 操作を適用
void downmax(int i, int *A, int n) {
	int j;

	j = 2*i + 1;  // i の左の子
	if (j >= n) {
		return;
	}

	if (j + 1 < n && A[j] < A[j+1]) {
		j = j + 1;
	}
	if (A[j] > A[i]) {
		swap(i, j, A);
		downmax(j, A, n);
	}

	return;
}


// deletemax ヒープ A[0],...,A[n-1] から最大要素 A[0] の出力と除去
int deletemax(int *A, int n) {
	int max;

	max = A[0];
	A[0] = A[n-1];

	downmax(0, A, n-1);

	return max;
}

void swap(int i, int j, int *A) {
	int tmp;

	tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;

	return;
}