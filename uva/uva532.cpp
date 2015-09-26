#include <iostream>
#include <deque>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define MAX_MAP_SIZE 35

using namespace std;

int dungeon[MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE];
bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE];
int l, r, c;
bool finished;
int last_step;


class Point {
public:
	int l, x, y, step;
	Point() {
		l = x = y = step = 0;
	}
	Point(int l, int x, int y, int step) {
		this->l = l;
		this->x = x;
		this->y = y;
		this->step = step;
	}
};


bool accessable(int l, int x, int y) {
	return l >= 0 && l < MAX_MAP_SIZE 
		&& x >= 0 && x < MAX_MAP_SIZE 
		&& y >= 0 && y < MAX_MAP_SIZE 
		&& (dungeon[l][y][x] == '.' || dungeon[l][y][x] == 'E')
		&& visited[l][y][x] == false;
}

bool accessable(Point p) {
	return accessable(p.l, p.x, p.y);
}

void solve() {
	Point start;
	for( int i = 0; i < l; i ++ ) {
		for( int j = 0; j < r; j ++ ) {
			for( int k = 0; k < c; k ++ ) {
				if( dungeon[i][j][k] == 'S' ) {
					start.l = i;
					start.y = j;
					start.x = k;
					start.step = 0;
				}
			}
		}
	}

	deque<Point> dq;
	dq.push_back(start);
	while( dq.size() > 0 ) {
		Point curr = dq.front();
		// cout << curr.l << " " << curr.y << " " << curr.x << " " << curr.step << endl;
		if( dungeon[curr.l][curr.y][curr.x] == 'E' ) {
			finished = true;
			last_step = curr.step;
			break;
		}

		if( accessable(curr.l - 1, curr.x, curr.y) ) {
			dq.push_back( Point(curr.l - 1, curr.x, curr.y, curr.step + 1) );
			visited[curr.l - 1][curr.y][curr.x] = true;
		}
		if( accessable(curr.l + 1, curr.x, curr.y) ) {
			dq.push_back( Point(curr.l + 1, curr.x, curr.y, curr.step + 1) );
			visited[curr.l + 1][curr.y][curr.x] = true;
		}
		if( accessable(curr.l, curr.x - 1, curr.y) ) {
			dq.push_back( Point(curr.l, curr.x - 1, curr.y, curr.step + 1) );
			visited[curr.l][curr.y][curr.x - 1] = true;
		}
		if( accessable(curr.l, curr.x + 1, curr.y) ) {
			dq.push_back( Point(curr.l, curr.x + 1, curr.y, curr.step + 1) );
			visited[curr.l][curr.y][curr.x + 1] = true;
		}
		if( accessable(curr.l, curr.x, curr.y - 1) ) {
			dq.push_back( Point(curr.l, curr.x, curr.y - 1, curr.step + 1) );
			visited[curr.l][curr.y - 1][curr.x] = true;
		}
		if( accessable(curr.l, curr.x, curr.y + 1) ) {
			dq.push_back( Point(curr.l, curr.x, curr.y + 1, curr.step + 1) );
			visited[curr.l][curr.y + 1][curr.x] = true;
		}

		dq.pop_front();
	}
}

int main() {
	while(1) {
		cin >> l >> r >> c;
		if( l == 0 ) {
			break;
		}

		memset(dungeon, 0, sizeof(dungeon));
		memset(visited, false, sizeof(visited));
		finished = false;
		last_step = 0;

		for( int i = 0; i < l; i ++ ) {
			for( int j = 0; j < r; j ++ ) {
				for( int k = 0; k < c; k ++ ) {
					char c;
					cin >> c;
					dungeon[i][j][k] = c;
				}
			}
			cin >> ws;
		}

		solve();

		if( finished ) {
			printf("Escaped in %d minute(s).\n", last_step);
		} else {
			printf("Trapped!\n");
		}
	}
}