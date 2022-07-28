#include <stdio.h>
#include <stdlib.h>
#define N 500

void mergesort(int i, int j, int *A);
void merge(int *A, int nA, int *B, int nB, int i, int *C);

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

	mergesort(0, n-1, A);

	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}

// mergesort 配列 A[i],...,A[j] をマージソート
void mergesort(int i, int j, int *A) {
	int k, n, n1, n2, mid;
	int A1[N], A2[N];

	n = j - i + 1;  // 配列のサイズ
	if (n > 1) {
		mid = i + (n - 1) / 2;  // 中央値により前後の部分配列へ分割
		mergesort(i, mid, A);  // 前半の整列
		mergesort(mid + 1, j, A);  // 後半の整列

		n1 = mid - i + 1;
		// A1 は前半の部分配列
		for (k = i; k <= mid; k++) {
			A1[k-i] = A[k];
		}

		n2 = j - mid;
		// A2 は後半の部分配列
		for (k = mid + 1; k <= j; k++) {
			A2[k - mid - 1] = A[k];
		}

		// A1 と A2 の併合
		merge(A1, n1, A2, n2, i, A);
	}

	return;
}

// merge 整列配列 A[0],...,A[nA-1] と B[0],...,B[nB-1] を併合し整列配列 C[i],...,C[i+nA+nB-1] に入れる
void merge(int *A, int nA, int *B, int nB, int i, int *C) {
	int iA, iB, iC;

	iA = iB = iC = 0;
	while (iC <= nA + nB -1) {
		if (iA >= nA) {  // A は既に空
			C[i + iC] = B[iB];
			iB = iB + 1;
		} else {
			if (iB >= nB) {  // B は既に空
				C[i + iC] = A[iA];
				iA = iA + 1;
			} else {  // A[iA] と B[iB] の小さい方を C へ移す
				if (A[iA] <= B[iB]) {
					C[i + iC] = A[iA];
					iA = iA + 1;
				} else {
					C[i + iC] = B[iB];
					iB = iB + 1;
				}
			}
		}
		iC = iC + 1;
	}

	return;
}