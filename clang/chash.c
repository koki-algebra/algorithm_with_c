#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 5
#define W 6

enum yn {yes, no};
enum oed {occupied, empty, deleted};

struct word {
	char name[W+1];
	enum oed state;
};

void insert(char *x, struct word *A);
void delete(char *x, struct word *A);
enum yn member(char *x, struct word *A);
int h(char *x);

int main() {
	struct word A[B];
	int i;
	enum yn t;

	for (i = 0; i < B; i++) {
		A[i].state = empty;
	}
	A[B-1].state = deleted;

	insert("xy", A);
	insert("xyz", A);
	insert("xyzabc", A);
	insert("xywwwww", A);
	insert("xyz", A);
	delete("xyzabc", A);
	insert("xxxxx", A);

	t = member("xyz", A);
	if (t == yes) {
		printf("member = yes\n");
	} else {
		printf("member = no\n");
	}

	t = member("yyz", A);
	if (t == yes) {
		printf("member = yes\n");
	} else {
		printf("member = no\n");
	}

	t = member("xywwww", A);
	if (t == yes) {
		printf("member = yes\n");
	} else {
		printf("member = no\n");
	}

	t = member("xy", A);
	if (t == yes) {
		printf("member = yes\n");
	} else {
		printf("member = no\n");
	}

	delete("abcd", A);
	printf("deleted\n");
	printf("-------------\n");

	for (i = 0; i < B; i++) {
		if (A[i].state == empty) {
			printf("empty");
		} else {
			if (A[i].state == deleted) {
				printf("deleted");
			} else {
				printf("%s", A[i].name);
			}
		}
		printf("\n");
	}

	for (i = 0; i < B; i++) {
		switch (A[i].state) {
		case empty:
			printf("empty\n");
			break;
		case deleted:
			printf("deleted\n");
			break;
		case occupied:
			printf("occupied\n");
			break;
		default:
			printf("unknown\n");
			break;
		}
	}

	return 0;
}

void insert(char *x, struct word *A) {
	int i, k, found = -1;
	enum oed cstate;

	// x のハッシュ値
	k = i = h(x);
	do {
		cstate = A[k].state;
		if (cstate == empty || cstate == deleted) {
			if (found < 0) {
				found = k;
			}
		} else {
			if (strcmp(x, A[k].name) == 0) {
				return;
			}
		}
		// 次のセルへ
		k = (k+1) % B;
	} while (cstate != empty && k != i);

	if (found < 0) {
		printf("Error: Dictionary is full.\n");
		exit(1);
	}

	// A[found] への x の挿入
	strcpy(A[found].name, x);
	A[found].state = occupied;

	return;
}

void delete(char *x, struct word *A) {
	int i, k;
	enum oed cstate;

	// x のハッシュ値
	k = i = h(x);
	// x の探索
	do {
		cstate = A[k].state;
		if (cstate == occupied) {
			if (strcmp(x, A[k].name) == 0) {
				A[k].state = deleted;
				return;
			}
		}
		// 次のセルへ
		k = (k+1) % B;
	} while (cstate != empty && k != i);

	return;
}

enum yn member(char *x, struct word *A) {
	int i, k;
	enum oed cstate;

	// x のハッシュ値
	k = i = h(x);
	// x の探索
	do {
		cstate = A[k].state;
		if (cstate == occupied) {
			if (strcmp(x, A[k].name) == 0) {  // x の発見
				return yes;
			}
		}
		// 次のセルへ
		k = (k+1) % B;
	} while (cstate != empty && k != i);

	return no;
}

int h(char *x) {
	int i, hash;

	hash = i = 0;
	while (x[i] != 0 && i < W) {
		hash = hash + (int)x[i];
		i = i + 1;
	}
	hash = hash % B;

	return hash;
}
