#include <iostream>
#include <stdlib.h>
#include <math.h>

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024

using namespace std;


int total_problem;
int population_map[2000][2000];

void init() {
	for( int i = 0; i < 2000; i ++ ) {
		for( int j = 0; j < 2000; j ++ ) {
			population_map[i][j] = 0;
		}
	}
}

void increase(int sx, int sy, int ex, int ey, int v) {
	for( int i = sy; i <= ey; i ++ ) {
		if( i < 0 || i > 1024 ) {
			continue;
		}
		for( int j = sx; j <= ex; j ++ ) {
			if( j < 0 || j > 1024 ) {
				continue;
			}
			population_map[i][j] += v;
		}
	}
}

void solve() {
	int d, n;
	cin >> d;
	cin >> n;
	for(int i = 0; i < n; i++ ) {
		int x, y, p;
		cin >> x >> y >> p;

		increase(x - d, y - d, x + d, y + d, p);
	}

	int max = -99999;
	int answer_x = 0, answer_y = 0;
	for( int x = 0; x <= 1024; x ++ ) {
		for( int y = 0; y <= 1024; y ++ ) {
			if( max < population_map[y][x] ) {
				max = population_map[y][x];
				answer_x = x;
				answer_y = y;
			}
		}
	}

	cout << answer_x << " " << answer_y << " " << max << endl;
}

int main() {
	cin >> total_problem;
	while(total_problem--) {
		init();
		solve();
	}
	
	return 0;
}