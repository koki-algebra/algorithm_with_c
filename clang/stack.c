#include <stdio.h>
#include <stdlib.h>

struct cell {
	int element;
	struct cell *next;
};

struct cell* push(int x, struct cell* init);
struct cell *pop(struct cell *init);

int main() {
	struct cell *init;
	struct cell *q;
	int i;

	init = NULL;
	for (i = 0; i < 10; i++) {
		init = push(i+1, init);
	}

	printf("init = %p\n", init);

	q = init;
	while (q != NULL) {
		printf("cell = %d, %p\n", q->element, q->next);
		q = q->next;
	}

	for (i = 0; i < 7; i++) {
		init = pop(init);
	}

	printf("init = %p\n", init);

	q = init;
	while (q != NULL) {
		printf("cell = %d, %p\n", q->element, q->next);
		q = q->next;
	}

	return 0;
}

struct cell* push(int x, struct cell* init) {
	struct cell *q, *r;

	r = (struct cell*)malloc(sizeof(struct cell));

	q = init;
	init = r;
	r->element = x;
	r->next = q;

	return init;
}

struct cell* pop(struct cell* init) {
	struct cell* q;

	if (init != NULL) {
		q = init;
		init = init->next;
		free(q);

		return init;
	} else {
		printf("Error: Stack is empty.\n");
		exit(1);
	}
}