#include <iostream>
#include <stdio.h>
#include <vector>

#define MAX_SINGER 1100

using namespace std;


int num_of_singer;
int num_of_input;
int arr[MAX_SINGER][110];
int deleted_nodes[MAX_SINGER];

vector< pair<int, int> > edges;

bool is_completed() {
	for( int i = 1; i <= num_of_singer; i ++ ) {
		if( deleted_nodes[i] == 0 ) {
			return false;
		}
	}

	return true;
}

int get_tail_vertex() {
	int exist[MAX_SINGER] = { 0, };
	int num_of_edge = edges.size();
	for( int i = 0; i < num_of_edge; i ++ ) {
		exist[ edges[i].second ] = 1;
	}

	int tail_vertex = 0;
	for( int i = 1; i <= MAX_SINGER; i ++ ) {
		if( deleted_nodes[i] == 0 && exist[i] == 0 && i <= num_of_singer ) {
			tail_vertex = i;
			break;
		}
	}

	return tail_vertex;
}

void delete_edges_outbound(int v) {
	vector<int> delete_list;
	for( int i = 0; i < edges.size(); i ++ ) {
		if( edges[i].first == v ) {
			delete_list.push_back(i);
		}
	}

	for( int i = 0; i < delete_list.size(); i ++ ) {
		int pos = delete_list[i];
		edges.erase( edges.begin() + (pos - i) );
	}
}

void solve() {
	vector<int> nodes;

	while( !is_completed() ) {
		int tail_vertex = get_tail_vertex();
		if( tail_vertex == 0 ) {
			break;
		}

		deleted_nodes[tail_vertex] = 1;
		nodes.push_back(tail_vertex);

		delete_edges_outbound(tail_vertex);
	}

	if( nodes.size() != num_of_singer ) {
		cout << 0 << endl;
	} else {
		for( int i = 0; i < nodes.size(); i ++ ) {
			cout << nodes[i] << endl;
		}
	}
}

int main() {
	cin >> num_of_singer;
	cin >> num_of_input;
	for( int i = 0; i < num_of_input; i ++ ) {
		cin >> arr[i][0];
		for( int j = 1; j <= arr[i][0]; j ++ ) {
			cin >> arr[i][j];
			if( j > 1 ) {
				edges.push_back( pair<int, int>( arr[i][j-1], arr[i][j] ) );
			}
		}
	}

	solve();

	return 0;
}