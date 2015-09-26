#include <iostream>
#include <stdio.h>
#include <climits>

#define MAX_LENGTH 1024

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

int arr[MAX_LENGTH];
int n;

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

	printf("%d %d %d\n", max_sum, max_start_index, max_end_index);
}

int main(int argc, char const *argv[]) {
	cin >> n;
	for( int i = 0; i < n; i ++ ) {
		cin >> arr[i];
	}

	int max_sum, max_start_index, max_end_index;
	kadane(arr, n, max_sum, max_start_index, max_end_index);
	
	return 0;
}