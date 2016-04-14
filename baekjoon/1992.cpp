#include <iostream>

#define MAX_N 65

using namespace std;


int n;
char picture[MAX_N][MAX_N];


void search(int left, int top, int right, int bottom) {
	char curr = picture[top][left];
	bool equip = true;
	for (int i = top; i <= bottom && equip; i ++) {
		for (int j = left; j <= right && equip; j ++) {
			if (curr != picture[i][j]) {
				equip = false;
			}
		}
	}

	if (equip) {
		cout << curr;
	} else {
		int mid1 = (left + right) / 2;
		int mid2 = (top + bottom) / 2;

		cout << '(';

		// 1사분면
		search(left, top, mid1, mid2);

		// 2사분면
		search(mid1 + 1, top, right, mid2);

		// 4사분면
		search(left, mid2 + 1, mid1, bottom);

		// 3사분면
		search(mid1 + 1, mid2 + 1, right, bottom);

		cout << ')';
	}
}

int main() {
	cin >> n;

	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			cin >> picture[i][j];
		}
	}

	search(0, 0, n - 1, n - 1);

	cout << endl;
}