#include <stdio.h>
#include <stdlib.h>

struct cell {
	int element;
	struct cell *next;
};

struct cell *insert(int x, struct cell *p, struct cell *init);
struct cell *delete(struct cell *p, struct cell *init);

int main() {
	struct cell *init;
	struct cell *p, *q;
	int i;

	init = NULL;
	p = NULL;

	for (i = 0; i < 10; i++) {
		init = insert(i+1, p, init);
		p = NULL;
	}

	printf("init = %p\n", init);

	q = init;
	while (q != NULL) {
		printf("cell = %d, %p\n", q->element, q->next);
		q = q->next;
	}

	p = init->next->next;
	for (i = 0; i < 6; i++) {
		init = delete(p, init);
	}

	printf("init = %p\n", init);

	q = init;
	while (q != NULL) {
		printf("cell = %d, %p\n", q->element, q->next);
		q = q->next;
	}

	return 0;
}

// insert ポインタ p が指すセルの次に x のセルを挿入. p == NULL なら先頭へ挿入
struct cell* insert(int x, struct cell *p, struct cell *init) {
	struct cell *q, *r;

	// 新しいポインタの生成
	r = (struct cell *)malloc(sizeof(struct cell));

	if (p == NULL) { // 先頭への挿入
		q = init;
		init = r;
	} else { // 途中への挿入
		q = p->next;
		p->next = r;
	}

	r->element = x;
	r->next = q;

	return init;
}

// delete init からの連結リストにおいてポインタ p が指すセルの次のセルを除去
struct cell* delete(struct cell *p, struct cell *init) {
	struct cell *q;

	if (init == NULL) {
		printf("Error: List is empty.\n");
		exit(1);
	}

	if (p == NULL) {  // 先頭のセルを除去
		q = init;
		init = init->next;
		free(q);
	} else {
		if (p->next == NULL) {  // 次のセルが存在しない
			printf("Error: No element to remove.\n");
		} else {  // 次のセルを削除
			q = p->next;
			p->next = q->next;
			free(q);
		}
	}

	return init;
}