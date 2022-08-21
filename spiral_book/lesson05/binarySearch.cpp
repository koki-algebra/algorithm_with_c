#include <cstdio>
#include <cstdlib>
#define N 10000

bool binarySearch(int A[], int n, int key);

int main() {
	int n, q, i, j;
	int count = 0;

	// create array S
	scanf("%d", &n);
	int S[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &S[i]);
	}

	// create array T
	scanf("%d", &q);
	int key;
	for (i = 0; i < q; i++) {
		scanf("%d", &key);
		if (binarySearch(S, n, key)) {
			count++;
		}
	}

	// print result
	printf("%d\n", count);

	return 0;
}

bool binarySearch(int A[], int n, int key) {
	int left = 0, right = n - 1, m;

	if (A[left] == key || A[right] == key) {
		return true;
	}

	if (key < A[left] || A[right] < key) {
		return false;
	}

	// binary search
	while (right - left > 1) {
		// median
		m = (left + right) / 2;
		if (A[m] == key) {
			return true;
		}

		// update index
		if (A[m] < key) {
			left = m;
		} else {
			right = m;
		}
	}

	return false;
}
