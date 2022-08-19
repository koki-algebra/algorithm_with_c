#include <stdio.h>
#define N 100

void merge(int *A, int nA, int *B, int nB, int i, int *C);

int main() {
	int A[N], B[N], C[2*N];
	int nA, nB, nC;
	int i;

	// データの生成
	nA = 10;
	nB = 15;
	nC = nA + nB;
	for (i = 0; i < nA; i++) {
		A[i] = 5 + 2*i;
	}
	for (i = 0; i < nB; i++) {
		B[i] = 3*i;
	}

	printf("A = ");
	for (i = 0; i < nA; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	printf("B = ");
	for (i = 0; i < nB; i++) {
		printf("%d ", B[i]);
	}
	printf("\n");

	merge(A, nA, B, nB, 0, C);

	printf("C = ");
	for (i = 0; i < nC; i++) {
		printf("%d ", C[i]);
	}
	printf("\n");

	return 0;
}

// merge 整列配列 A[0],...,A[nA-1] と B[0],...,B[nB-1] を併合し, 整列配列 C[i],...,C[i+nA+nB-1] に入れる
void merge(int *A, int nA, int *B, int nB, int i, int *C) {
	int iA, iB, iC;

	iA = iB = iC = 0;
	while (iC <= nA+nB-1) {
		if (iA >= nA) {  // A は既に空
			C[i+iC] = B[iB];
			iB = iB + 1;
		} else {
			if (iB >= nB) {  // B は既に空
				C[i+iC] = A[iA];
				iA = iA + 1;
			} else {  // A[iA] と B[iB] の小さい方を C へ
				if (A[iA] <= B[iB]) {
					C[i+iC] = A[iA];
					iA = iA + 1;
				} else {
					C[i+iC] = B[iB];
					iB = iB + 1;
				}
			}
		}
		iC = iC + 1;
	}

	return;
}