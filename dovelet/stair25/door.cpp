#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


class CheckNode {
public:
	int count, o1, o2;
	CheckNode(int count, int o1, int o2) {
		this->count = count;
		this->o1 = o1;
		this->o2 = o2;
	}

	bool operator< (const CheckNode& rhs) const {
		return this->count < rhs.count;
	}
};


int min_end = INT_MAX;
int N;
int pass_time;
int checks[25];


void backtracking(int count, int open1, int open2, int curr) {
	if( open1 < 1 || open1 > N ) {
		return;
	}
	if( open2 < 1 || open2 > N ) {
		return;
	}
	if( open1 == open2 ) {
		return;
	}


	int nextCheck = curr;
	while(nextCheck < pass_time) {
		if( checks[nextCheck] == open1 || checks[nextCheck] == open2 ) {
			nextCheck++;
		} else {
			break;
		}
	}
	if( nextCheck == pass_time && min_end > count ) {
		min_end = count;
		return;
	}

	if( min_end >= count + pass_time - nextCheck ) {
		int diff1 = checks[nextCheck] - open1;
		int diff2 = checks[nextCheck] - open2;
		backtracking(count + abs(diff1), open1 + diff1, open2, nextCheck);
		backtracking(count + abs(diff2), open1, open2 + diff2, nextCheck);
	}
}

int main() {
	int o1, o2;
	cin >> N;
	cin >> o1 >> o2;
	cin >> pass_time;
	for( int i = 0; i < pass_time; i ++ ) {
		cin >> checks[i];
	}

	backtracking(0, o1, o2, 0);
	cout << min_end << endl;
}