#include <iostream>
#include <math.h>
#include <vector>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

using namespace std;


bool check(int n, int b) {
	if (b == 1) {
		return false;
	}

	int m = n % b;
	int m2;
	while(n > 0) {
		m2 = n % b;
		n /= b;
		if (m != m2) {
			return false;
		}
	}

	return true;
}

void proc() {
	int n;
	cin >> n;

	if (n < 3) {
		cout << n + 1 << endl;
		return;
	}

	int root = (int)sqrt(n);

	vector<int> divisors;
	divisors.push_back(1);

	for (int i = 2; i <= root; i ++){
		if (n % i == 0) {
			divisors.push_back(i);
			continue;
		}

		if (check(n, i)) {
			cout << i << endl;
			return;
		}
	}

	for (int i = divisors.size() - 1; i >= 0; i --) {
		int divisor = divisors[i];
		int tmp = n / divisor;
		if (check(n, tmp - 1)) {
			cout << tmp - 1 << endl;
			return;
		}
	}
}

int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; i ++) {
		cout << "Case #" << i + 1 << endl;
		proc();
	}

	return 0;
}