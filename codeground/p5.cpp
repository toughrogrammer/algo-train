#include <iostream>
#include <math.h>
#include <vector>
#include <deque>
#include <cstdio>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 1010
#define MAX_WEIGHT 0x7FFFFFFF

using namespace std;


int dp[MAX_N][MAX_N];
int via[MAX_N][MAX_N];


void find_path(int q, int r, vector<int>& path) {
	if (via[q][r] != 0) {
		find_path(q, via[q][r], path);
		path.push_back(via[q][r]);
		find_path(via[q][r], r, path);
	}
}

void proc() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < MAX_N; i ++) {
		for (int j = 0; j < MAX_N; j ++) {
			dp[i][j] = MAX_WEIGHT;
			via[i][j] = 0;
		}
	}

	int u, v, w;
	for (int i = 0; i < m; i ++) {
		cin >> u >> v >> w;
		dp[u][v] = w;
		dp[v][u] = w;
	}

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (dp[i][k] == MAX_WEIGHT || dp[k][j] == MAX_WEIGHT) {
					continue;
				} 

				if (dp[i][j] > dp[i][k] + dp[k][j]) {
					dp[i][j] = dp[i][k] + dp[k][j];
					via[i][j] = k;
				}
			}
		}
	}

	int visitCheck[MAX_N] = { 0, };
	for (int i = 1; i < n; i ++) {
		for (int j = i + 1; j <= n; j ++) {
			if (i == j) {
				continue;
			}

			vector<int> path;
			find_path(i, j, path);

			if (path.size() == 0) {
				continue;
			}

			for (int k = 0; k < path.size(); k ++) {
				visitCheck[path[k]] = 1;
			}
		}
	}

	vector<int> printTarget;
	for (int i = 1; i <= n; i ++) {
		if (!visitCheck[i]) {
			printTarget.push_back(i);
		}
	}

	cout << printTarget.size() << " ";
	for (int i = 0; i < printTarget.size(); i ++) {
		cout << printTarget[i] << " ";
	}
	cout << endl;
}

int main() {
	setbuf(stdout, NULL);

	int T;
	cin >> T;

	for (int i = 0; i < T; i ++) {
		cout << "Case #" << i + 1 << endl;
		proc();
	}

	return 0;
}