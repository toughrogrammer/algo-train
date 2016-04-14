#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>

#define MAX_LENGTH 100

using namespace std;


int radix_conversion(int n, int radix, char* dest) {
	char str[MAX_LENGTH] = { 0, };

	int i = 0;
	while(n) {
		str[i++] = (n % radix) + '0';
		n /= radix;
	}

	int length = i;
	for (i = 0; i < length; i ++) {
		dest[length - i - 1] = str[i];
	}

	return length;
}

unsigned long long interpret_from_two(const char* str, int radix) {
	int length = strlen(str);
	int i = length - 1;
	unsigned long long n = 1, result = 0;

	while(i >= 0) {
		result += (str[i] - '0') * n;
		i--;
		n *= radix;
	}

	return result;
}

int is_not_prime(unsigned long long n) {
	int last = (int)sqrt(n);
	for (int i = 2; i <= last; i ++) {
		if (n % (unsigned long long)i == 0) {
			return i;
		}
	}

	return 0;
}

bool proc(int n) {
	char two_radix[MAX_LENGTH];
	char radixed[11][MAX_LENGTH];
	int divisors[11];

	memset(two_radix, 0, sizeof(two_radix));
	memset(radixed, 0, sizeof(radixed));
	memset(divisors, 0, sizeof(divisors));

	int length = radix_conversion(n, 2, two_radix);
	if (two_radix[length - 1] == '0') {
		return false;
	}

	vector<unsigned long long> results;
	for (int i = 2; i <= 10; i ++) {
		unsigned long long result = interpret_from_two(two_radix, i);
		results.push_back(result);

		int divisor = is_not_prime(result);
		if (divisor) {
			divisors[i] = divisor;
		} else {
			return false;
		}
	}

	cout << two_radix;
	for (int i = 2; i <= 10; i ++) {
		cout << " " << divisors[i];
	}
	cout << endl;

	return true;
}

int main() {
	int t;
	cin >> t;

	int n, j;
	cin >> n >> j;

	int start = pow(2, n - 1) + 1;
	int end = ((start - 1) * 2) - 1;

	cout << "Case #1:" << endl;
	for (int i = start; i <= end; i ++) {
		if (proc(i)) {
			j --;
		}
	}

	return 0;
}