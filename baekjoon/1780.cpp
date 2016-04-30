#include <iostream>

#define MAX_N 2200

using namespace std;


int n;
int picture[MAX_N][MAX_N];
int count1 = 0, count2 = 0, count3 = 0;


void search(int left, int top, int right, int bottom) {
	int curr = picture[top][left];
	bool equip = true;
	for (int i = top; i <= bottom && equip; i ++) {
		for (int j = left; j <= right && equip; j ++) {
			if (curr != picture[i][j]) {
				equip = false;
			}
		}
	}

	if (equip) {
		if (curr == -1) {
			count1++;
		} else if (curr == 0) {
			count2++;
		} else {
			count3++;
		}
	} else {
		int gap = (right - left + 1) / 3;

		int mid1 = left + gap;
		int mid2 = left + gap * 2;
		int mid3 = top + gap;
		int mid4 = top + gap * 2;


		// (1) (2) (3)
		search(left, top, mid1 - 1, mid3 - 1);
		search(mid1, top, mid2 - 1, mid3 - 1);
		search(mid2, top, right, mid3 - 1);

		// (4) (5) (6)
		search(left, mid3, mid1 - 1, mid4 - 1);
		search(mid1, mid3, mid2 - 1, mid4 - 1);
		search(mid2, mid3, right, mid4 - 1);

		// (7) (8) (9)
		search(left, mid4, mid1 - 1, bottom);
		search(mid1, mid4, mid2 - 1, bottom);
		search(mid2, mid4, right, bottom);
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

	cout << count1 << endl << count2 << endl << count3 << endl;
}