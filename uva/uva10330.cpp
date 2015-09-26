#include <iostream>
#include <vector>
#define MAX_N 110
#define INF 99999999

using namespace std;

class Edge {
public:
	int v, c;

	Edge() {

	}

	Edge(int v, int c) {
		this->v = v;
		this->c = c;
	}
};

int N, M, B, D;
int src, dest;
vector<Edge> graph[MAX_N * 2 + 2];


bool arrive = false;
void find_path(int start, int end, int u, vector<int>& path, vector<int>& visited) {
	if( arrive ) {
		return;
	}

	if( u == end ) {
		arrive = true;
		return;
	}

	for( int i = 0; i < graph[u].size(); i ++ ) {
		Edge& edge = graph[u][i];
		if( edge.c > 0 && ! visited[edge.v] && ! arrive ) {
			visited[edge.v] = 1;
			path.push_back(edge.v);

			find_path(start, end, edge.v, path, visited);

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

		for( int j = 0; j < graph[u].size(); j ++ ) {
			if( graph[u][j].v == v ) {
				if( min > graph[u][j].c ) {
					min = graph[u][j].c;
				}
				break;
			}
		}

		u = v;
	}

	return min;
}

void increase_capacity(int u, int v, int incr) {
	for( int i = 0; i < graph[u].size(); i ++ ) {
		if( graph[u][i].v == v ) {
			graph[u][i].c += incr;
			break;
		}
	}
}

int vertex_interpolating(int u) {
	return u + N;
}

void print_graph() {
	for( int i = 0; i <= dest; i ++ ) {
		vector<Edge>& edges = graph[i];
		for( int j = 0; j < edges.size(); j ++ ) {
			cout << i << " " << edges[j].v << " " << edges[j].c << endl;
		}
	}
}

void inputting() {
	for( int i = 0; i < MAX_N * 2 + 2; i ++ ) {
		graph[i].clear();
	}

	int u, v, c;

	cin >> N;
	for( int i = 1; i <= N; i ++ ) {
		cin >> c;
		graph[i].push_back( Edge(vertex_interpolating(i), c) );
		graph[vertex_interpolating(i)].push_back( Edge(i, 0) );
	}
	dest = vertex_interpolating(N) + 1;

	cin >> M;
	for( int i = 0; i < M; i ++ ) {
		cin >> u >> v >> c;
		graph[vertex_interpolating(u)].push_back( Edge(v, c) );
		graph[v].push_back( Edge(vertex_interpolating(u), 0) );
	}

	cin >> B >> D;
	for( int i = 0; i < B; i ++ ) {
		cin >> u;
		graph[0].push_back( Edge(u, INF) );
	}
	for( int i = 0; i < D; i ++ ) {
		cin >> u;
		graph[vertex_interpolating(u)].push_back( Edge(dest, INF) );
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

			// cout << "path : ";

			int u, v;
			u = path[0];
			// cout << u << " ";

			for( int i = 1; i < path.size(); i ++ ) {
				v = path[i];
				// cout << v << " ";

				increase_capacity(u, v, -path_flow);
				increase_capacity(v, u, path_flow);

				u = v;
			}

			// cout << ", " << path_flow << endl;

			// print_graph();
			// cout << endl;
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