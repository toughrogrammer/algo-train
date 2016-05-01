#include <iostream>
#define MAX_N 101
#define MAX_K 10010

using namespace std;


unsigned long dp[MAX_K];
int coin[MAX_N];
int n, k;


int main() {
	cin >> n >> k;

	for (int j = 0; j <= k; j ++)
		dp[j] = 0;

	for (int i = 1; i <= n; i ++) {
		cin >> coin[i];
	}

	for (int i = 1; i <= n; i ++) {
		int curr_coin = coin[i];
		for (int j = 1; j <= k; j ++) {
			int v1 = 0, v2 = 0;

			v1 = dp[j];

			if (j - curr_coin >= 0) {
				v2 = dp[j - curr_coin];
			}

			if (j == curr_coin) {
				v2++;
			}

			dp[j] = v1 + v2;
		}
	}

	for (int j = 1; j <= k; j ++) {
		printf("%10d", dp[j]);
	}
	printf("\n");

	cout << dp[k] << endl;

	return 0;
}