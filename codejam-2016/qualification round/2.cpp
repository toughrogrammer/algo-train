#include <iostream>
#include <stdlib.h>

using namespace std;


void solve() {
	string line;
	cin >> line;

	int length = line.length();

	if (length == 1) {
		if (line[0] == '-') {
			cout << 1 << endl;
		} else {
			cout << 0 << endl;
		}

		return;
	}

	int count = 0;
	while (1) {
		int side1 = 0;
		int side2 = 0;
		int last_diff = 0;
		bool found = false;
		for (int i = 0; i < length; i ++) {
			if (line[i] == '-') {
				side1 ++;
			} else {
				side2 ++;
			}

			if (!found && line[0] != line[i]) {
				last_diff = i;
				found = true;
			}
		}
		if (!found) {
			last_diff = length;
		}

		if (side1 == length) {
		} else if (side2 == length) {
			break;
		}

		for (int i = 0; i < last_diff; i ++) {
			if (line[i] == '-') {
				line[i] = '+';
			} else {
				line[i] = '-';
			}
		}

		count ++;
	}

	cout << count << endl;
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
