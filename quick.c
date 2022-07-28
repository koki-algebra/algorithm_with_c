#include <stdio.h>
#include <stdlib.h>
#define N 500

void quicksort(int i, int j, int *A);
int partition(int i, int j, int a, int *A);
int pivot(int i, int j, int *A);
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

	quicksort(0, n-1, A);

	for (i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}

// quicksort 配列 A[i],...,A[j] をクイックソート
void quicksort(int i, int j, int *A) {
	int a, pv, k;

	pv = pivot(i, j, A);
	if (pv != -1) {
		a = A[pv];  // 軸要素
		k = partition(i, j, a, A);

		quicksort(i, k-1, A);  // 前半のソート
		quicksort(k, j, A);  // 後半の整列
	}

	return;
}


// partition A[i],...,A[j] を軸要素 a によって分割
// 前半は A[i],...,A[k-1] < a, 後半は A[k],...,A[j] >= a を満たす
int partition(int i, int j, int a, int *A) {
	int l, r, k;

	l = i;
	r = j;
	while (1) {
		while (A[l] < a) {
			l = l + 1;
		}
		while (A[r] >= a) {
			r = r - 1;
		}

		if (l <= r) {
			swap(l, r, A);
			l = l + 1;
			r = r - 1;
		} else {
			break;
		}
	}

	k = l;

	return k;
}

// pivot A[i],...,A[j] から軸要素 A[pv] を選び pv を出力
// A[pv] は A[i] と最初に異なる A[k] の大きい方; 全て同じなら pv = -1
int pivot(int i, int j, int *A) {
	int pv, k;

	k = i + 1;
	while (k <= j && A[i] == A[k]) {
		k = k + 1;
	}

	if (k > j) {
		pv = -1;
	} else if (A[i] >= A[k]) {
		pv = i;
	} else {
		pv = k;
	}

	return pv;
}

void swap(int i, int j, int *A) {
	int tmp;
	tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;

	return;
}