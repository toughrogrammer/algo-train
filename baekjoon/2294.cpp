#include <iostream>
#include <climits>
#define MAX_N 101
#define MAX_K 10010

using namespace std;


int dp[MAX_N][MAX_K];
int coin[MAX_N];
int n, k;


int main() {
	cin >> n >> k;

	for (int i = 0; i <= n; i ++)
		for (int j = 0; j <= k; j ++)
			dp[i][j] = INT_MAX;

	for (int i = 1; i <= n; i ++) {
		cin >> coin[i];

		if (coin[i] <= MAX_K) {
			dp[i][coin[i]] = 1;
		}
	}

	for (int i = 1; i <= n; i ++) {
		int curr_coin = coin[i];
		for (int j = 1; j <= k; j ++) {
			int v1 = -1, v2 = -1;

			if (j - curr_coin >= 1 && dp[i][j - curr_coin] != INT_MAX) {
				v1 = dp[i][j - curr_coin] + 1;
			}

			v2 = dp[i - 1][j];

			int& curr = dp[i][j];
			curr = v1 != -1 && v1 < curr ? v1 : curr;
			curr = v2 < curr ? v2 : curr;
		}
	}

	int result = dp[n][k] == INT_MAX ? -1 : dp[n][k];
	cout << result << endl;

	return 0;
}