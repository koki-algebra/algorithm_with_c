#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 4  // バケット数
#define W 6  // 語長

enum yn {yes, no};

struct cell {
	char name[W+1];
	struct cell *next;
};

void insert(char *x, struct cell **A);
void delete(char *x, struct cell **A);
enum yn member(char *x, struct cell **A);
int h(char *x);

int main() {
	struct cell *A[B], *q;
	int j;
	enum yn t;

	for (j = 0; j < B; j++) {
		A[j] = NULL;
	}

	insert("abcdef", A);
	insert("abcdefg", A);
	insert("abc", A);
	insert("cd", A);
	insert("def", A);
	insert("abcdef", A);
	insert("azc", A);
	insert("azd", A);
	insert("bzd", A);

	for (j = 0; j < B; j++) {
		printf("A[%d] = %p, ", j, A[j]);
		q = A[j];

		while (q != NULL) {
			printf("%s, next = %p, ", q->name, q->next);
			q = q->next;
		}

		printf("\n");
	}

	t = member("azd", A);
	if (t == yes) {
		printf("member = yes\n");
	} else {
		printf("member = no\n");
	}

	t = member("vwx", A);
	if (t == yes) {
		printf("member = yes\n");
	} else {
		printf("member = no\n");
	}

	delete("azd", A);
	delete("cccc", A);
	delete("cd", A);
	delete("abcdefg", A);

	for (j = 0; j < B; j++) {
		printf("A[%d] = %p, ", j, A[j]);
		q = A[j];
		while (q != NULL) {
			printf("%s, next = %p, ", q->name, q->next);
			q = q->next;
		}
		printf("\n");
	}

	return 0;
}

// insert ハッシュ表 A への文字列 x の挿入
void insert(char *x, struct cell **A) {
	int k;
	struct cell *p, *q, *r;

	k = h(x);  // x の入るバケット番号
	q = A[k];  // バケット k 内の探索

	p = (struct cell*)malloc(sizeof(struct cell));

	if (q == NULL) {
		A[k] = p;
	} else {
		while (q != NULL) {  // x の存在チェック
			if (strcmp(q->name, x) == 0) {
				free(p);
				return;
			} else {
				r = q;
				q = q->next;
			}
		}
		r->next = p;
	}

	strcpy(p->name, x);  // x の挿入
	p->next = NULL;

	return;
}

// delete ハッシュ表 A から文字列 x の除去
void delete(char *x, struct cell **A) {
	int k;
	struct cell *q, *r;

	k = h(x);  // x のハッシュ値
	q = A[k];  // バケット k 内で x の探索
	r = NULL;

	while (q != NULL) {
		if (strcmp(q->name, x) == 0) {
			if (r == NULL) {
				A[k] = q->next;
			} else {
				r->next = q->next;
			}

			free(q);
			return;
		}

		r = q;
		q = q->next;
	}

	return;
}

// member ハッシュ表 A に文字列 x の存在判定
enum yn member(char *x, struct cell **A) {
	struct cell *q, *r;

	q = A[h(x)];  // バケット h(x) 内で x の探索
	while (q != NULL) {
		if (strcmp(q->name, x) == 0) {
			return yes;
		}
		q = q->next;
	}

	return no;
}

// h ハッシュ関数
int h(char *x) {
	int i, hash;
	hash = i = 0;

	while (i < W && x[i] != 0) {
		hash = hash + (int)x[i];
		i = i + 1;
	}

	hash = hash % B;

	return hash;
}
