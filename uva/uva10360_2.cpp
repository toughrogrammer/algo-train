#include <iostream>
#include <stdlib.h>
#include <math.h>

#define MAX_ROW 20000

using namespace std;


int row_x[MAX_ROW];
int row_y[MAX_ROW];
int row_population[MAX_ROW];

void init() {
	for( int i = 0; i < MAX_ROW; i++ ) {
		row_x[i] = 0;
		row_y[i] = 0;
		row_population[i] = 0;
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

bool valid(int bx, int by, int d, int cx, int cy) {
	return max( abs(bx - cx), abs(by - cy) ) <= d;
}

void solve() {
	int d, n;
	cin >> d;
	cin >> n;
	for(int i = 0; i < n; i++ ) {
		int x, y, p;
		cin >> x >> y >> p;
		row_x[i] = x;
		row_y[i] = y;
		row_population[i] = p;
	}

	int max = -99999;
	int max_x, max_y;
	for( int i = 0; i <= 1024; i ++ ) {
		for( int j = 0; j <= 1024; j ++ ) {
			int count = 0;
			for( int k = 0; k < n; k ++ ) {
				if( valid(j, i, d, row_x[k], row_y[k] ) ) {
					count += row_population[k];
				}
			}

			if( count > max ) {
				max = count;
				max_x = j;
				max_y = i;
			}
		}
	}

	cout << max_x << " " << max_y << " " << max << endl;
}

int main() {
	int n;
	cin >> n;

	for( int i = 0; i < n; i ++ ) {
		init();
		solve();
	}

	return 0;
}