#include <stdio.h>
#define N 100

enum yn {yes, no};

enum yn bsearch(int x, int *A, int n);

int main() {
	int A[N];
	int i, x, nA;
	enum yn ans;

	nA = 15;
	for (i = 0; i < nA; i++) {
		A[i] = 5+2*i;
	}
	printf("A = ");
	for (i = 0; i < nA; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	x = 7;
	printf("x = %d\n", x);
	ans = bsearch(x, A, nA);

	if (ans == yes) {
		printf("Answer = yes\n");
	} else {
		printf("Answer = no\n");
	}

	return 0;
}

// bsearch 整列配列 A[0],...,A[n-1] 上で x の二分探索; yes あるいは no を出力
enum yn bsearch(int x, int *A, int n) {
	int iL, iR, iM;  // iL は左, iR は右, iM は中央のインデックス
	
	iL = 0;
	iR = n - 1;

	// 初期条件でのチェック
	if (A[iL] == x || A[iR] == x) {
		return yes;
	}
	if (x < A[iL] || x > A[iR]) {
		return no;
	}

	// 二分探索
	while (iR - iL > 1) {
		iM = (iL + iR) / 2;  // 中央値
		if (A[iM] == x) {
			return yes;
		}

		// 新しいインデックスの設定
		if (A[iM] < x) {
			iL = iM;
		} else {
			iR = iM;
		}
	}

	return no;
}
