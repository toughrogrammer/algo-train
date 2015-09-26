#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>

#define INFINITE 9999999
#define MAX_CITY 800
#define WHITE 0
#define GREY 1
#define BLACK 2


using namespace std;


class Edge {
public:
	int u, v;
	double w;

	Edge(int u, int v, double w) { 
		this->u = u, this->v = v, this->w = w;
	}
	
	const bool operator<( const Edge &op ) const {
		return w < op.w;
	}

};

int parent[MAX_CITY];
int find_root(int p) {
	if( parent[p] < 0 ) 
		return p;
	return parent[p] = find_root(parent[p]);
}
void union_set(int p, int q) {
	p = find_root(p);
	q = find_root(q);
 
	if( p != q )
		parent[p] = q;
}

void solve() {
	memset(parent, -1, sizeof(parent));
	vector<Edge> result;

	int num_of_city;
	cin >> num_of_city;

	vector< pair<double, double> > vertices;
	vertices.push_back( pair<double, double>(0, 0) );
	for( int i = 0; i < num_of_city; i ++ ) {
		double x, y;
		cin >> x >> y;
		vertices.push_back( pair<double, double>(x, y) );
	}

	int adj_mat[MAX_CITY][MAX_CITY];
	memset(adj_mat, 0, sizeof(adj_mat));

	vector<Edge> edges;
	int num_of_regacy_edge;
	cin >> num_of_regacy_edge;
	for( int i = 0; i < num_of_regacy_edge; i ++ ) {
		int a, b;
		cin >> a >> b;
		adj_mat[a][b] = 1;
		adj_mat[b][a] = 1;

		Edge e = Edge(a, b, 0);
		edges.push_back( e );
		if( find_root(e.u) != find_root(e.v) ) {
			union_set(e.u, e.v);
			result.push_back( e );
		}
	}

	if( result.size() == num_of_city - 1) {
		cout << "No new highways need" << endl;
		return;
	}

	for( int i = 1; i <= num_of_city; i ++ ) {
		for( int j = i + 1; j <= num_of_city; j ++ ) {
			pair<double, double> city1 = vertices[i], city2 = vertices[j];
			edges.push_back( 
				Edge(i, 
					j, 
					pow( city1.first - city2.first, 2 ) + pow( city1.second - city2.second, 2 ) ) );
			adj_mat[i][j] = 1;
			adj_mat[j][i] = 1;
		}
	}

	sort(edges.begin(), edges.end());

	int i = 0;
	int last = result.size();
	while( result.size() < num_of_city - 1 ) {
		Edge e = edges[i++];
		if( find_root(e.u) != find_root(e.v) ) {
			union_set(e.u, e.v);
			result.push_back( e );
		}
	}

	for( int i = last; i < result.size(); i ++ ) {
		cout << result[i].u << " " << result[i].v << endl;
	}
}

int main() {
	int test_case_num;
	cin >> test_case_num;

	while(1) {
		cin >> ws;
		solve();
		if( --test_case_num == 0 ) {
			break;
		}

		cout << endl;
	}

	return 0;
}