#include <iostream>
#define MAX_N 50

using namespace std;


int f[MAX_N] = { 0, 1, 1, };

int main() {
	int n;
	cin >> n;

	if (n <= 2) {
		cout << 1 << endl;
	} else {
		for (int i = 3; i <= n; i ++) {
			f[i] = f[i - 2] + f[i - 1];
		}

		cout << f[n] << endl;
	}
}