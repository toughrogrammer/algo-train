#include <iostream>

#define MAX_N 1010

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

using namespace std;


int room[MAX_N][MAX_N];
int visit[MAX_N][MAX_N];


void proc() {
	int n;
	cin >> n;

	char c;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			cin >> c;

			room[i][j] = c - '0';

			visit[i][j] = 0;
		}
		cin >> ws;
	}

	int currX = 0;
	int currY = 1;
	int dirX = 1;
	int dirY = 0;

	int count = 0;

	while(true) {
		currX += dirX;
		currY += dirY;
		if (currX < 1 || currX > n || currY < 1 || currY > n) {
			break;
		}

		int currType = room[currY][currX];
		if (currType == 0) {
		} else if (currType == 1) {
			int newDirX = -dirY;
			int newDirY = -dirX;
			dirX = newDirX;
			dirY = newDirY;

			if (visit[currY][currX] == 0) {
				visit[currY][currX] = 1;
				count ++;
			}
		} else if (currType == 2) {
			int newDirX = dirY;
			int newDirY = dirX;
			dirX = newDirX;
			dirY = newDirY;

			if (visit[currY][currX] == 0) {
				visit[currY][currX] = 1;
				count ++;
			}
		}
	}
	
	cout << count << endl;
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