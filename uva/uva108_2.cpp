#include <iostream>
#include <climits>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MAX_ROW 100
#define MAX_COL 100

using namespace std;

int arr[MAX_ROW][MAX_COL];
int size;

void kadane(int *arr, int n, int& max_sum, int& max_start_index, int& max_end_index) {
	max_sum = INT_MIN;
	max_start_index = 0;
	max_end_index = 0;

	int current_max_sum = 0;
	int current_start_index = 0;
	for( int i = 0; i < n; i ++ ) {
		current_max_sum = current_max_sum + arr[i];
		if( current_max_sum > max_sum ) {
			max_sum = current_max_sum;
			max_start_index = current_start_index;
			max_end_index = i;
		}

		if( current_max_sum < 0 ) {
			current_max_sum = 0;
			current_start_index = i + 1;
		}
	}
}

void solve() {
	int temp[MAX_ROW];
	int max = INT_MIN;
	for( int left = 0; left < size; left ++ ) {
		memset(temp, 0, sizeof(temp));
		for( int right = left; right < size; right ++ ) {
			for( int i = 0; i < size; i ++ ) {
				temp[i] += arr[i][right];
			}

			int max_sum, max_start_index, max_end_index;
			kadane(temp, size, max_sum, max_start_index, max_end_index);
			if(max_sum > max) {
				max = max_sum;
			}
		}
	}

	cout << max << endl;
}

int main(int argc, char const *argv[]) {
	cin >> size;
	for( int i = 0; i < size; i ++ ) {
		for( int j = 0; j < size; j ++ ) {
			cin >> arr[i][j];
		}
	}

	solve();

	return 0;
}