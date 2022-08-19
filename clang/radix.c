#include <stdio.h>
#include <stdlib.h>
#define N 100  // 配列Aの最大サイズ
#define m 10  // 値の範囲は [0,1,..., m-1]
#define K 3  // 語長

struct word {
	int letter[K];
};

struct cell {
	int index;
	struct cell *next;
};

void radixsort(struct word *A, int *idx, int n);
void bucketsort(struct word *A, int *idx, int n, int k);
void insert(struct word *A, int idx, struct cell **B, int k);

int main() {
	struct word A[N];
	int idx[N];
	int i, h, n;

	// データの生成
	n = 15;
	for (i = 0; i < n; i++) {
		idx[i] = i;
		for (h = 0; h < K; h++) {
			A[i].letter[h] = (765-i*i+3*h*i) % 10;
		}
	}

	printf("n = %d\n", n);

	for (i = 0; i < n; i++) {
		for (h = 0; h < K; h++) {
			printf("%d", A[idx[i]].letter[h]);
		}
		printf(" ");
	}
	printf("\n");

	radixsort(A, idx, n);

	for (i = 0; i < n; i++) {
		for (h = 0; h < K; h++) {
			printf("%d", A[idx[i]].letter[h]);
		}
		printf(" ");
	}
	printf("\n");

	return 0;
}

void radixsort(struct word *A, int *idx, int n) {
	int k;
	for (k = K-1; k >= 0; k--) {
		bucketsort(A, idx, n, k);
	}

	return;
}

void bucketsort(struct word *A, int *idx, int n, int k) {
	struct cell *B[m];  // バケット 0,...,m-1
	struct cell *p, *q;
	int i, j;

	// バケットの初期化
	for (j = 0; j < m; j++) {
		B[j] = NULL;
	}

	// idx[i] をバケットへ
	for (i = 0; i < n; i++) {
		insert(A, idx[i], B, k);
	}

	i = n - 1;
	for (j = m-1; j >= 0; j--) {
		p = B[j];
		while (p != NULL) {
			idx[i] = p->index;
			i = i - 1;
			q = p->next;
			free(p);
			p = q;
		}
	}

	return;
}


// insert ix を k桁目の値 A[ix].letter[k] のバケットBに挿入
void insert(struct word *A, int ix, struct cell **B, int k) {
	struct cell *p;

	p = (struct cell*)malloc(sizeof(struct cell));

	p->index = ix;
	p->next = B[A[ix].letter[k]];
	B[A[ix].letter[k]] = p;

	return;
}
