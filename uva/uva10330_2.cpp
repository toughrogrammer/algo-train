#include <iostream>
#include <vector>
#define MAX_N 110
#define INF 99999999

using namespace std;

int N, M, B, D;
int src, dest;
int graph[MAX_N * 3][MAX_N * 3];

bool arrive = false;
void find_path(int start, int end, int u, vector<int>& path, vector<int>& visited) {
	if( arrive ) {
		return;
	}

	if( u == end ) {
		arrive = true;
		return;
	}

	for( int i = start + 1; i <= end; i ++ ) {
		if( graph[u][i] > 0 && ! visited[i] && ! arrive ) {
			visited[i] = 1;
			path.push_back(i);
			find_path(start, end, i, path, visited);

			if( ! arrive ) {
				path.pop_back();
			}
		}
	}
}

int calc_min_flow(const vector<int>& path) {
	int u, v;
	u = path[0];

	int min = INF;
	int min_u, min_v;
	for( int i = 1; i < path.size(); i ++ ) {
		v = path[i];

		if( min > graph[u][v] ) {
			min = graph[u][v];
		}

		u = v;
	}

	return min;
}

int vertex_interpolating(int u) {
	return u + N;
}

void inputting() {
	for( int i = 0; i < MAX_N * 2; i ++ ) {
		for( int j = 0; j < MAX_N * 2; j ++ ) {
			graph[i][j] = 0;
		}
	}

	int from_sources[MAX_N] = { 0, };
	int entry_points[MAX_N] = { 0, };
	int last_points[MAX_N] = { 0, };
	int u, v, c;

	cin >> N;
	for( int i = 1; i <= N; i ++ ) {
		cin >> c;
		graph[i][vertex_interpolating(i)] = c;
	}
	dest = vertex_interpolating(N) + 1;

	cin >> M;
	for( int i = 0; i < M; i ++ ) {
		cin >> u >> v >> c;

		graph[vertex_interpolating(u)][v] = c;
	}

	cin >> B >> D;
	for( int i = 0; i < B; i ++ ) {
		int u;
		cin >> u;

		graph[0][u] = INF;
	}
	for( int i = 0; i < D; i ++ ) {
		int u;
		cin >> u;

		graph[vertex_interpolating(u)][dest] = INF;
	}
}

void solve() {
	int max_flow = 0;
	while(1) {
		vector<int> path, visited(dest + 1, 0);
		path.reserve(100);
		path.push_back(src);
		arrive = false;
		find_path(src, dest, src, path, visited);
		if( path.size() == 1 ) {
			break;
		} else {
			int path_flow = calc_min_flow(path);
			max_flow += path_flow;

			int u, v;
			u = path[0];
			cout << u << " ";

			for( int i = 1; i < path.size(); i ++ ) {
				v = path[i];
				cout << v << " ";

				graph[u][v] -= path_flow;
				graph[v][u] += path_flow;

				u = v;
			}

			cout << ", " << path_flow << endl;
		}
	}

	cout << max_flow << endl;
}

int main() {
	while(1) {
		inputting();
		solve();
		cin >> ws;
		if( cin.eof() ) {
			break;
		}
	}

	return 0;
}