#include <iostream>
#include <string.h>
#include <stdlib.h>

#define MAX_N 256
#define MAX_WEIGHT 0x7FFFFFFF

using namespace std;


int cost[MAX_N][MAX_N];
int path[MAX_N][MAX_N];


void solve() {
	memset(cost, MAX_WEIGHT, sizeof(cost));
	for( int i = 0; i < MAX_N; i ++ )
		for( int j = 0; j < MAX_N; j ++ )
			cost[i][j] = MAX_WEIGHT;

	int p;
	cin >> p;
	for( int i = 0; i < p; i ++ ) {
		char a, b;
		int w;
		cin >> a >> b >> w;

		if( cost[a][b] > w ) {
			cost[a][b] = cost[b][a] = w;
		}
	}

	int d[MAX_N][MAX_N];
	memcpy(d, cost, sizeof(cost));

	for (int k = 'A'; k <= 'z'; k++) {
		if( ! isalpha(k) ) {
			continue;
		}
		for (int i = 'A'; i <= 'z'; i++) {
			if( ! isalpha(i) || i == 'Z' ) {
				continue;
			}
			for (int j = 'A'; j <= 'z'; j++) {
				if( ! isalpha(j) ) {
					continue;
				}

				if( d[i][k] >= MAX_WEIGHT || d[k][j] >= MAX_WEIGHT ) {
					continue;
				}

				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					path[i][j] = k;
				}
			}
		}
	}

	char c = 'A';
	int min_w = MAX_WEIGHT;
	for( int i = 'A'; i <= 'Y'; i ++ ) {
		int w = d[i]['Z'];
		if( w < min_w ) {
			min_w = w;
			c = i;
		}
	}
	printf("%c %d\n", c, min_w);


int main() {
	solve();
}