#include <iostream>
#include <stdio.h>
using namespace std;

int map_row, map_col;
int start_x;
int map[20][20] = { 0, };
int step_map[20][20];
bool isEnd = false;

int offset_x[] = { 0, 0, 1, -1 };
int offset_y[] = { -1, 1, 0, 0 };

void recurse(int x, int y, int step) {
	if( (x < 0 || x >= map_col || y < 0 || y >= map_row) && !isEnd ){
		isEnd = true;
		cout << step << " step(s) to exit" << endl;
	}

	if( step_map[y][x] >= 0 && !isEnd ) {
		isEnd = true;
		cout << step_map[y][x] << " step(s) before a loop of " << step - step_map[y][x] << " step(s)" << endl;
	}

	if( isEnd ) {
		return;
	}

	// printf("step_map[%d][%d] = %d\n", y, x, step_map[y][x]);
	step_map[y][x] = step;
	recurse(x + offset_x[map[y][x]], y + offset_y[map[y][x]], step + 1);
}

int main(int argc, char const *argv[])
{
	cin >> map_row >> map_col >> start_x;
	for( int i = 0; i < map_row; i ++ ) {
		for( int j = 0; j < map_col; j ++ ) {
			char c;
			cin >> c;
			if( c == 'N' ) {
				map[i][j] = 0;
			} else if( c == 'S' ) {
				map[i][j] = 1;
			} else if( c == 'E' ) {
				map[i][j] = 2;
			} else if( c == 'W' ) {
				map[i][j] = 3;
			}
		}
	}

	for( int i = 0; i < map_row; i ++ ) {
		for( int j = 0; j < map_col; j ++ ) {
			step_map[i][j] = -1;
		}
	}

	recurse(start_x - 1, 0, 0);

	return 0;
}