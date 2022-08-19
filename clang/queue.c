#include <stdio.h>
#include <stdlib.h>

struct cell {
	int element;
	struct cell* next;
};

struct queue {
	struct cell* front;  // queue の先頭
	struct cell* rear;  // queue の末尾
};

void enqueue(int x, struct queue* Q);
void dequeue(struct queue* Q);

// Manipulation of a linked queue of cells
int main() {
	struct queue Q;
	struct cell *q;
	int i;

	Q.front = Q.rear = NULL;
	for (i = 0; i < 10; i++) {
		enqueue(i+1, &Q);
	}

	printf("Q.front = %p, Q.rear = %p\n", Q.front, Q.rear);
	q = Q.front;

	while (q != NULL) {
		printf("cell = %d, %p\n", q->element, q->next);
		q = q->next;
	}

	for (i = 0; i < 8; i++) {
		dequeue(&Q);
	}

	printf("Q.front = %p, Q.rear = %p\n", Q.front, Q.rear);
	q = Q.front;

	while (q != NULL) {
		printf("cell = %d, %p\n", q->element, q->next);
		q = q->next;
	}

	return 0;
}

void enqueue(int x, struct queue *Q) {
	struct cell* p;

	p = (struct cell*)malloc(sizeof(struct cell));

	if (Q->rear != NULL) {
		Q->rear->next = p;
	}
	Q->rear = p;
	if (Q->front == NULL) {
		Q->front = p;
	}
	Q->rear->element = x;
	Q->rear->next = NULL;

	return;
}

void dequeue(struct queue* Q) {
	struct cell* q;

	if (Q->front == NULL) {
		printf("Error: Queue is empty.\n");
		exit(1);
	} else {
		q = Q->front;
		Q->front = Q->front->next;
		free(q);
	}

	if (Q->front == NULL) {
		Q->rear = NULL;
	}

	return;
}