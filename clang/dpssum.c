#include <stdio.h>
#include <stdlib.h>
#define N 100
#define B 10000

enum yn {yes, no};

enum yn dpssum(int *a, int b, int n);

// SUBSET-SUM 問題を解く動的計画法のテストプログラム
int main() {
	int a[N], b;
	int n, j;
	FILE *file;

	file = fopen("ssumdata.txt", "r");
	fscanf(file, "%d", &n);
	if (n > N) {
		printf("Illegal array size n = %d for N = %d\n", n, N);
		exit(1);
	}
	printf("n = %d\na = ", n);

	for (j = 0; j < n; j++) {
		fscanf(file, "%d", &a[j]);
	}
	for (j = 0; j < n; j++) {
		printf("%d ", a[j]);
	}
	printf("\n");

	fscanf(file, "%d", &b);
	if (b >= B) {
		printf("Illegal size b = %d for B = %d\n", b, B);
		exit(1);
	}
	printf("b = %d\n", b);

	if (dpssum(a, b, n) == yes) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}

	return 0;
}

enum yn dpssum(int *a, int b, int n) {
	int y[N][B];  // 動的計画法の計算表
	int k, p;

	// 初期設定
	for (k = 0; k < n; k++) {
		for (p = 0; p <= b; p++) {
			y[k][p] = 0;
		}
	}

	// k = 0
	y[0][0] = 1;  // p = 0
	if (a[0] <= b) {
		y[0][a[0]] = 1;  // p = a[0]
	}

	// 動的計画法の反復
	for (k = 1; k < n; k++) {
		for (p = 0; p <= b; p++) {
			if (y[k-1][p] == 1) {
				y[k][p] = 1;
			} else if (p - a[k] >= 0 && y[k-1][p - a[k]] == 1) {
				y[k][p] = 1;
			}
		}
	}

	// 結果
	if (y[n-1][b] == 1) {
		return yes;
	} else {
		return no;
	}
}
