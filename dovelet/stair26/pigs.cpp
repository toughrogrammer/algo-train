#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_HOUSE 1010
#define INF 99999999

using namespace std;


int N, M;
int house[MAX_HOUSE];
int graph[MAX_HOUSE][MAX_HOUSE];
vector<int> customers[101];

int src;
int dest;


int instersection(const vector<int>& v1, const vector<int>& v2) {
	vector<int> v3;
	set_intersection(v1.begin(),
		v1.end(),
		v2.begin(),
		v2.end(),
		back_inserter(v3));

	return v3.size();
}

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

int main() {
	cin >> N >> M;

	src = 0;
	dest = M + 1;

	for( int i = 1; i <= N; i ++ ) {
		cin >> house[i];
	}

	for( int i = 1; i <= M; i ++ ) {
		int k;
		cin >> k;

		for( int j = 0; j < k; j ++ ) {
			int key;
			cin >> key;
			customers[i].push_back(key);
		}

		sort(customers[i].begin(), customers[i].end());

		int need;
		cin >> need;
		graph[0][i] = need;
	}

	for( int i = 2; i <= M; i ++ ) {
		const vector<int>& curr = customers[i];
		for( int j = i - 1; j >= 1; j -- ) {
			const vector<int>& prev = customers[j];
			if( instersection(curr, prev) > 0 ) {
				graph[i][j] = INF;
			}
		}
	}

	for( int i = 1; i <= M; i ++ ) {
		int count = 0;
		for( int j = 0; j < customers[i].size(); j ++ ) {
			int key = customers[i][j];
			count += house[key];
			house[key] = 0;
		}

		graph[i][dest] = count;
	}

	int max_flow = 0;
	while(1) {
		vector<int> path, visited(dest + 1, 0);
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
			for( int i = 1; i < path.size(); i ++ ) {
				v = path[i];

				graph[u][v] -= path_flow;
				graph[v][u] += path_flow;

				u = v;
			}
		}
	}

	cout << max_flow << endl;

	return 0;
}