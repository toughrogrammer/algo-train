#include <iostream>
#include <vector>
#define MAX_HOUSE 101

using namespace std;

int adj[MAX_HOUSE][MAX_HOUSE];
int N;

struct Edge {
	int u, v, dist;

	Edge(int u, int v, int dist) {
		this->u = u;
		this->v = v;
		this->dist = dist;
	}
};

int main() {
	cin >> N;
	for( int i = 1; i <= N; i ++ ) {
		for( int j = 1; j <= N; j ++ ) {
			cin >> adj[i][j];
		}
	}

	int nearest[MAX_HOUSE] = { 0, };
	int dist[MAX_HOUSE] = { 0, };
	int i, vnear, min;

	vector<Edge> result;

	for( i = 1; i <= N; i ++ ) {
		nearest[i] = 1;
		dist[i] = adj[1][i];
	}

	for( int k = 0; k < N - 1; k ++ ) {
		min = 0x7FFFFFFF;
		for( i = 2; i <= N; i ++ ) {
			if( 0 < dist[i] && dist[i] <= min ) {
				min = dist[i];
				vnear = i;
			}
		}

		result.push_back( Edge(vnear, nearest[vnear], min) );
		dist[vnear] = -1;
		for( i = 2; i <= N; i ++ ) {
			if( adj[i][vnear] < dist[i] ) {
				dist[i] = adj[i][vnear];
				nearest[i] = vnear;
			}
		}
	}

	int sum = 0;
	for( int i = 0; i < result.size(); i ++ ) {
		// cout << result[i].u << " " << result[i].v << " " << result[i].dist << endl;
		sum += result[i].dist;
	}

	cout << sum << endl;

	return 0;
}