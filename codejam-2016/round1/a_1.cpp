#include <iostream>
#include <deque>

using namespace std;


void solve() {
	string input;
	cin >> input;

	deque<char> deq;
	deq.push_back(input[0]);

	for (int i = 1; i < input.size(); i ++) {
		char c = input[i];
		if (deq.front() <= c) {
			deq.push_front(c);
		} else {
			deq.push_back(c);
		}
	}

	for (int i = 0; i < input.size(); i ++) {
		cout << deq[i];
	}

	cout << endl;
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