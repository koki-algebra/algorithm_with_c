#include <stdio.h>
#include <stdlib.h>

enum yn {yes, no};
enum LR {LEFT, RIGHT};

struct node {
	int element;
	struct node *left;
	struct node *right;
};

enum yn member(int x, struct node *init);
struct node* insert(int x, struct node *init);
int min(struct node *init);
struct node* delete(int x, struct node *init);
struct node* off(struct node *p);
void printpre(struct node *p);
void inorder(struct node *p);

int main() {
	struct node *init;
	int i, x;
	enum yn a;

	init = NULL;
	for (i = 0; i < 10; i++) {
		init = insert((8-3*i)*(2-i/2), init);
	}

	init = insert(30, init);
	init = insert(25, init);
	init = insert(31, init);
	init = insert(37, init);

	printf("init = %p\n", init);

	printf("inorder\n");
	if (init != NULL) {
		inorder(init);
	}

	printf("preorder\n");
	if (init != NULL) {
		printpre(init);
	}

	x = 31;
	a = member(x, init);
	if (a == yes) {
		printf("Yes: x = %d\n", x);
	} else {
		printf("No: x = %d\n", x);
	}

	x = -2;
	a = member(x, init);
	if (a == yes) {
		printf("Yes: x = %d\n", x);
	} else {
		printf("No: x = %d\n", x);
	}

	x = 16;
	init = delete(x, init);
	printf("delete x = %d\n", x);
	printf("init = %p\n", init);
	if (init != NULL) {
		printpre(init);
	}

	x = 32;
	init = delete(x, init);
	printf("delete x = %d\n", x);
	printf("init = %p\n", init);
	if (init != NULL) {
		printpre(init);
	}

	x = 37;
	init = delete(x, init);
	printf("delete x = %d\n", x);
	printf("init = %p\n", init);
	if (init != NULL) {
		printpre(init);
	}

	return 0;
}

enum yn member(int x, struct node *init) {
	struct node *q;

	q = init;  // root (init) から探索開始

	while (q != NULL) {
		if (q->element == x) {
			return yes;
		}
		if (q->element < x) {
			q = q->right;
		} else {
			q = q->left;
		}
	}

	return no;
}

struct node* insert(int x, struct node *init) {
	struct node *p, *q, *r;

	p = (struct node*)malloc(sizeof(struct node));

	q = init;  // root (init) から探索開始
	if (init == NULL) {
		init = p;
	}

	while (q != NULL) {
		if (q->element == x) {  // x は既に存在
			free(p);
			return init;
		}
		r = q;
		if (q->element < x) {
			q = q->right;
			if (q == NULL) {
				r->right = p;
			}
		} else {
			q = q->left;
			if (q == NULL) {
				r->left = p;
			}
		}
	}

	p->element = x;
	p->left = p->right = NULL;

	return init;
}

int min(struct node *init) {
	struct node *q, *r;

	q = init;
	if (q == NULL) {
		printf("Error: Tree is empty.\n");
		exit(1);
	}

	while (q != NULL) {
		r = q;
		q = q->left;
	}

	return r->element;
}

struct node* delete(int x, struct node *init) {
	struct node *q, *r, *p;  // q は探索中のポインタ, r はその親
	int side;  // side == 1: r の右の子が q, 0: 左の子が q

	q = init;  // root (init) から探索開始
	while (q != NULL) {
		if (q->element == x) {
			p = off(q);  // x のセル q を除去し, q の部分木を更新
			if (p == NULL) {
				if (q == init) {
					init = NULL;
				} else {
					if (side == 1) {
						r->right = NULL;
					} else {
						r->left = NULL;
					}
				}
			}

			return init;
		}

		r = q;  // 探索を続ける
		if (r->element < x) {
			q = r->right;
			side = 1;
		} else {
			q = r->left;
			side = 0;
		}
	}

	return init;
}

struct node* off(struct node *p) {
	struct node *q, *r, *s;  // q は探索中のポインタ, r はその親, s は r の親
	int side;

	if (p->left == NULL && p->right == NULL) {  // p の子が共に空
		return NULL;
	}
	if (p->left == NULL || p->right == NULL) {  // p の子の一方が空
		if (p->left == NULL) {
			q = p->right;
		} else {
			q = p->left;
		}

		p->element = q->element;
		p->left = q->left;
		p->right = q->right;

		return p;
	}

	// p の子が共に存在
	s = p;
	side = 1;

	// p の右の部分木の最小要素を探索
	r = s->right;
	q = r->left;
	while (q != NULL) {
		s = r;
		side = 0;
		r = q;
		q = r->left;
	}

	p->element = r->element;
	r = off(r);

	if (r == NULL) {
		if (side == 1) {
			s->right = NULL;
		} else {
			s->left = NULL;
		}
	}

	return p;
}

void printpre(struct node *p) {
	printf("p = %p, element = %d, left = %p, right = %p\n", p, p->element, p->left, p->right);
	if (p->left != NULL) {
		printpre(p->left);
	}
	if (p->right != NULL) {
		printpre(p->right);
	}

	return;
}

void inorder(struct node *p) {
	if (p->left != NULL) {
		inorder(p->left);
	}
	printf("p = %p, element = %d, left = %p, right = %p\n", p, p->element, p->left, p->right);

	if (p->right != NULL) {
		inorder(p->right);
	}

	return;
}