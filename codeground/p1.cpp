#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

#define MAX_N 1000010
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

using namespace std;


int arr[MAX_N];
int dp[MAX_N];


void proc() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		dp[i] = -1;
	}

	int k;
	cin >> k;

	int start = 0;
	for (int i = 0; 
		i < k && arr[i] <= k; 
		i ++, start ++) {
		dp[i] = 1;
	}

	int min_of_range = 1;
	int min_index = start - 1;

	for (int i = start; i < n; i ++) {
		// impossible case
		if (arr[i] - arr[i-1] > k) {
			cout << -1 << endl;
			return;
		}

		if (arr[i] - arr[min_index] > k) {
			while (arr[i] - arr[min_index] > k) {
				min_index++;
			}

			min_of_range = dp[min_index];
		}

		dp[i] = min_of_range + 1;
	}

	cout << dp[n - 1] << endl;
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