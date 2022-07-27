#include <stdio.h>
#include <stdlib.h>
#define N 100

struct cell {
	int node;
	struct cell* next;
};

void preorder(int k, struct cell **S);

// Traverse a tree S in preorder
int main() {
	struct cell *S[N], *p, *q;
	int n, j, parent, child, root;
	FILE *file;

	file = fopen("treedata.txt", "r");
	fscanf(file, "%d", &n);
	if (n > N) {
		printf("ILLegal array size n = %d for N = %d\n", n, N);
		exit(1);
	}

	printf("n = %d\n", n);
	for (j = 0; j < n; j++) {
		S[j] = NULL;
	}

	// create a tree
	fscanf(file, "%d", &parent);
	while (parent >= 0) {
		fscanf(file, "%d", &child);
		if (child >= 0) {
			p = (struct cell*)malloc(sizeof(struct cell));
			S[parent] = q = p;
		}

		while (child >= 0) {
			q->node = child;
			q->next = NULL;
			fscanf(file, "%d", &child);
			if (child >= 0) {
				p = (struct cell*)malloc(sizeof(struct cell));
				q->next = p;
				q = p;
			}
		}

		fscanf(file, "%d", &parent);
	}

	// output the tree
	for (j = 0; j < n; j++) {
		printf("S[%d] = %p, ", j, S[j]);
		q = S[j];
		while (q != NULL) {
			printf("node = %d, next = %p, ", q->node, q->next);
			q = q->next;
		}

		printf("\n");
	}

	// traverse the tree S in preorder
	root = 0;
	printf("preorder =");
	preorder(root, S);
	printf("\n");

	return 0;
}

void preorder(int k, struct cell **S) {
	struct cell *q;

	printf(" %d", k);

	q = S[k];
	while (q != NULL) {
		preorder(q->node, S);
		q = q->next;
	}

	return;
}
