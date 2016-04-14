#include <stdio.h>
#include <math.h>

#define POW_2_20 1048576


void hanoi(int n, int p, int q, int r) {
	if (n == 1) {
		printf("%d %d\n", p, q);
	} else {
		hanoi(n - 1, p, r, q);
		hanoi(1, p, q, r);
		hanoi(n - 1, r, q, p);
	}
}

int main() {
	int n;
	scanf("%d", &n);

	printf("%d\n", (int)(pow(2, n) - 1));
	hanoi(n, 1, 3, 2);

	return 0;
}