#include <stdio.h>
#define N 7
#define M 4

struct set {
	int size[M];
	int root[M];
	int parent[N];
};

void treemerge(int i, int k, struct set *S);
int treefind(int j, struct set *S);

int main() {
	struct set S;
	int i, j, k;
	FILE *file;

	// ファイル読み込み
	file = fopen("mtreedata.txt", "r");
	for (i = 0; i < M; i++) {
		fscanf(file, "%d", &S.size[i]);
		fscanf(file, "%d", &S.root[i]);
	}
	for (j = 0; j < N; j++) {
		fscanf(file, "%d", &S.parent[j]);
	}

	// 出力 (マージ前)
	printf("initial S\n");
	for (i = 0; i < M; i++) {
		printf("%d, %d, %d\n", i, S.size[i], S.root[i]);
	}
	printf("initial parents\n");
	for (j = 0; j < N; j++) {
		printf("%d, %d\n", j, S.parent[j]);
	}

	// マージ
	treemerge(1, 3, &S);

	// 出力 (マージ後)
	printf("updated S\n");
	for (i = 0; i < M; i++) {
		printf("%d, %d, %d\n", i, S.size[i], S.root[i]);
	}
	printf("updated parents\n");
	for (j = 0; j < N; j++) {
		printf("%d, %d\n", j, S.parent[j]);
	}

	j = 4;
	k = treefind(j, &S);

	printf("element = %d, set = %d\n", j, k);
	printf("updated S\n");
	for (i = 0; i < M; i++) {
		printf("%d, %d, %d\n", i, S.size[i], S.root[i]);
	}

	printf("updated parents\n");
	for (j = 0; j < N; j++) {
		printf("%d, %d\n", j, S.parent[j]);
	}

	return 0;
}

// treemerge 集合 i と k の2つの木の併合
void treemerge(int i, int k, struct set *S) {
	int j, large, small;

	if (S->size[i] <= S->size[k]) {
		small = i;
		large = k;
	} else {
		small = k;
		large = i;
	}

	// 大きい方へ併合
	j = S->root[small];
	if (S->size[small] == 0) {
		return;
	}
	S->parent[j] = S->root[large];
	S->size[large] = S->size[large] + S->size[small];
	S->size[small] = 0;
	S->root[small] = -1;

	return;
}

// treefind j を要素とする集合 i の出力と path の圧縮
int treefind(int j, struct set *S) {
	int i, k, tmp;

	// 集合 i の発見
	k = j;
	while (k >= 0) {
		k = S->parent[k];
	}
	i = -k - 1;

	// path の圧縮
	k = j;
	while (k >= 0) {
		tmp = S->parent[k];
		if (tmp >= 0) {
			S->parent[k] = S->root[i];
		}
		k = tmp;
	}

	return i;
}
