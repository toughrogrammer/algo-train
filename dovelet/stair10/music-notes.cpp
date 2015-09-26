#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int note_length[50001];
int n, q;

int main(int argc, char const *argv[]) {
	cin >> n >> q;

	for( int i = 0; i < n; i ++ ) {
		int l;
		cin >> l;
		note_length[i] = l;
		if( i > 0 ) {
			note_length[i] += note_length[i-1];
		}
	}

	for( int i = 0; i < q; i ++ ) {
		int tmp;
		cin >> tmp;
		
		int *last = upper_bound(note_length, note_length + n, tmp);
		cout << last - note_length + 1 << endl;
	}

	return 0;
}