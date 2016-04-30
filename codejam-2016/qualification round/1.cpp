#include <iostream>
#include <stdlib.h>

using namespace std;


int digits[10];
int rest_digits;

void set_digits(int n) {
	while(n) {
		int digit = n % 10;
		if (digits[digit] == 0) {
			rest_digits--;
			digits[digit] = 1;
		}

		n /= 10;
	}
}

void solve() {
	int n;
	cin >> n;

	if (n == 0) {
		cout << "INSOMNIA" << endl;
		return;
	}

	memset(digits, 0, sizeof(digits));
	rest_digits = 10;

	for (int i = 0; ; i ++) {
		int n2 = i * n;
		set_digits(n2);
		if (rest_digits == 0) {
			cout << n2 << endl;
			return;
		}
	}
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i ++) {
		cout << "Case #" << i + 1 << ": ";
		solve();
	}

	return 0;
}