#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#define MAX_SCHOOL_NUM 110

#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

int num_of_school;
int network[MAX_SCHOOL_NUM][MAX_SCHOOL_NUM];
int reversed_network[MAX_SCHOOL_NUM][MAX_SCHOOL_NUM];
int scc_num[MAX_SCHOOL_NUM];

int tick;


bool comp_finished_time(const pair<int, int>& lhs, const pair<int, int>& rhs) {
	return lhs.second > rhs.second;
}

void DFS_visit(const int adj[][MAX_SCHOOL_NUM], 
	int u, vector<int>& v, vector<int>& f,vector<int>& d, vector<int>& c) {
	c[u] = GREY;
	tick++;
	d[u] = tick;

	v.push_back(u);

	for( int i = 1; i <= num_of_school; i ++ ) {
		if( c[i] == WHITE && adj[u][i] ) {
			DFS_visit(adj, i, v, f, d, c);
		}
	}

	c[u] = BLACK;
	tick++;
	f[u] = tick;
}

void solve() {
	vector<int> color(num_of_school + 1, 0);
	vector<int> d(num_of_school + 1, 0);
	vector<int> f(num_of_school + 1, 0);
	vector<int> visited;
	for( int i = 1; i <= num_of_school; i ++ ) {
		if( color[i] == WHITE ) {
			DFS_visit(network, i, visited, f, d, color);
		}
	}

	vector< pair<int, int> > sorted_by_finished_time;
	for( int i = 1; i <= num_of_school; i ++ ) {
		sorted_by_finished_time.push_back( pair<int, int>(i, f[i]) );
	}
	sort(sorted_by_finished_time.begin(), sorted_by_finished_time.end(), comp_finished_time);

	for( int i = 0; i < sorted_by_finished_time.size(); i ++ ) {
		cout << sorted_by_finished_time[i].second << " ";
	}
	cout << endl;


	color.clear();
	color.resize(num_of_school + 1, WHITE);
	int answer1 = 0;
	for( int i = 0; i < sorted_by_finished_time.size(); i ++ ) {
		int u = sorted_by_finished_time[i].first;
		if( color[u] == WHITE ) {
			visited.clear();
			DFS_visit(network, u, visited, f, d, color);
			answer1 ++;
		}
	}

	cout << answer1 << endl;

	color.clear();
	color.resize(num_of_school + 1, WHITE);

	vector< vector<int> > scc_list;
	for( int i = 0; i < sorted_by_finished_time.size(); i ++ ) {
		int u = sorted_by_finished_time[i].first;
		if( color[u] == WHITE ) {
			visited.clear();
			DFS_visit(reversed_network, u, visited, f, d, color);

			// 한번에 전부다 strongly connected component이면 추가 edge 없이 바로 끝낸다.
			if( visited.size() == num_of_school ) {
				cout << 0 << endl;
				return;
			}

			for( int j = 0; j < visited.size(); j ++ ) {
				scc_num[ visited[j] ] = scc_list.size();
			}
			scc_list.push_back( visited );
		}
	}

	vector<int> indegree(scc_list.size(), 0);
	vector<int> outdegree(scc_list.size(), 0);
	for( int i = 1; i <= num_of_school; i ++ ) {
		for( int j = 1; j <= num_of_school; j ++ ) {
			if( network[i][j] && scc_num[i] != scc_num[j]) {
				indegree[scc_num[i]]++;
				outdegree[scc_num[j]]++;
			}
		}
	}

	int zc1 = 0;
	int zc2 = 0;
	for( int i = 0; i < scc_list.size(); i ++ ) {
		if( indegree[i] == 0 ) {
			zc1++;
		}
		if( outdegree[i] == 0 ) {
			zc2++;
		}
	}

	int answer2 = zc1 > zc2 ? zc1 : zc2;
	cout << answer2 << endl;
}

int main() {
	cin >> num_of_school;
	for( int i = 1; i  <= num_of_school; i ++ ) {
		int n;
		while( (cin >> n) && n != 0 ) {
			network[i][n] = 1;
			reversed_network[n][i] = 1;
		}
	}
	
	solve();
}