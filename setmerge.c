#include <stdio.h>
#define N 7  // 最大要素数
#define M 4  // 最大集合数

struct set {
	int size[M];  // size[i]: 集合の要素数 |S[i]|
	int first[M];  // first[i]: S[i] の最初の要素へのポインタの役割
};

struct element {
	int set[N];  // set[j]: 要素 j を含む S[i] の添字 i
	int next[N];  // next[j]: S[i] の要素 j の次の要素へのポインタの役割
};

void setmerge(int i, int k, struct set *S, struct element *E);

int main() {
	struct set S;
	struct element E;
	int i, j;
	FILE *file;

	// 初期化
	for (i = 0; i < M; i++) {
		S.size[i] = 0;
		S.first[i] = -1;
	}
	for (j = 0; j < N; j++) {
		E.set[j] = -1;
		E.next[j] = -1;
	}

	// ファイル読み込み
	file = fopen("mergedata.txt", "r");
	fscanf(file, "%d", &i);
	while (i >= 0) {
		fscanf(file, "%d", &S.size[i]);
		fscanf(file, "%d", &S.first[i]);
		fscanf(file, "%d", &i);
	}
	fscanf(file, "%d", &j);
	while (j >= 0) {
		fscanf(file, "%d", &E.set[j]);
		fscanf(file, "%d", &E.next[j]);
		fscanf(file, "%d", &j);
	}

	printf("initial S\n");
	for (i = 0; i < M; i++) {
		printf("%d, %d, %d\n", i, S.size[i], S.first[i]);
	}
	printf("initial E\n");
	for (j = 0; j < N; j++) {
		printf("%d, %d, %d\n", j, E.set[j], E.next[j]);
	}

	setmerge(0, 3, &S, &E);
	setmerge(0, 1, &S, &E);

	printf("updated S\n");
	for (i = 0; i < M; i++) {
		printf("%d, %d, %d\n", i, S.size[i], S.first[i]);
	}
	printf("updated E\n");
	for (j = 0; j < N; j++) {
		printf("%d, %d, %d\n", j, E.set[j], E.next[j]);
	}

	return 0;
}

// setmerge 配列 S と E で定義された集合属の集合 S[i] と S[k] の併合
void setmerge(int i, int k, struct set *S, struct element *E) {
	int j, h, large, small;

	if (S->size[i] <= S->size[k]) {
		small = i;
		large = k;
	} else {
		small = k;
		large = i;
	}

	// 小さい方の集合の先頭の添字
	j = S->first[small];

	while (j >= 0) {
		// 大きい方へ併合
		E->set[j] = large;
		h = j;
		// 次の要素へ
		j = E->next[j];
	}

	// 集合の配列 S の更新
	E->next[h] = S->first[large];
	S->first[large] = S->first[small];
	S->first[small] = -1;
	S->size[large] = S->size[large] + S->size[small];
	S->size[small] = 0;

	return;
}
