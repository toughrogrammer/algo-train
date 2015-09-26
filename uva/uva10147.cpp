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
		return w > op.w;
	}

};

// // for std::sort
// inline bool operator<(const Edge& lhs, const Edge& rhs) {
// 	return rhs.w < lhs.w;
// }


class DisjointSet {
public:
	DisjointSet *parent;
	int x;
	int rank;

	DisjointSet() { 
		parent = this;
		x = -1;
		rank = 0;
	}

	DisjointSet(int v) {
		parent = this;
		this->x = v;
		rank = 0;
	}

	static DisjointSet* FindRoot(DisjointSet &set) {
		if( set.parent == &set ) {
			return &set;
		}

		return FindRoot(*set.parent);
	}

	static void Union(DisjointSet &set1, DisjointSet &set2) {
		DisjointSet *root1 = FindRoot(set1);
		DisjointSet *root2 = FindRoot(set2);

		if( root1->rank < root2->rank ) {
			root1->parent = root2;
		}
		else if( root1->rank > root2->rank ) {
			root2->parent = root1;
		}
		else {
			root2->parent = root1;
			root1->rank++;
		}
	}
};

bool comp_edge_beautifying(const Edge& lhs, const Edge& rhs) {
	return lhs.u < rhs.u;
}


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

void kruskal(int n, const vector<Edge> &sortedEdges, vector<Edge> &result) {
	vector<DisjointSet> disjointSets;
	disjointSets.resize( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		disjointSets[i].x = i;
	}

	int i = sortedEdges.size() - 1;
	while( result.size() < n - 1 ) {
		Edge e = sortedEdges[i--];

		int p1 = find_root(e.u);
		int p2 = find_root(e.v);
		if( p1 != p2 ) {
			union_set(e.u, e.v);
			result.push_back( e );
		}

		// DisjointSet& set1 = disjointSets[e.u];
		// DisjointSet& set2 = disjointSets[e.v];
		// if( DisjointSet::FindRoot(set1) != DisjointSet::FindRoot(set2) ) {
		// 	DisjointSet::Union(set1, set2);
		// 	result.push_back( e );
		// }
	}
}

int tick = 0;
void DFS_visit(const int adj[][MAX_CITY], 
	int u, vector<int>& v, vector<int>& f,vector<int>& d, vector<int>& c) {
	c[u] = GREY;
	tick++;
	d[u] = tick;

	v.push_back(u);

	for( int i = 1; i <= f.size() - 1; i ++ ) {
		if( c[i] == WHITE && adj[u][i] ) {
			DFS_visit(adj, i, v, f, d, c);
		}
	}

	c[u] = BLACK;
	tick++;
	f[u] = tick;
}

void solve() {
	memset(parent, -1, sizeof(parent));

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
	vector<Edge> regacy_edges;

	int num_of_regacy_edge;
	cin >> num_of_regacy_edge;
	for( int i = 0; i < num_of_regacy_edge; i ++ ) {
		int a, b;
		cin >> a >> b;

		Edge e = Edge(a, b, 0);
		edges.push_back( e );
		regacy_edges.push_back(e);

		adj_mat[a][b] = 1;
		adj_mat[b][a] = 1;
	}

	// check
	vector<int> color(num_of_city + 1, 0);
	vector<int> d(num_of_city + 1, 0);
	vector<int> f(num_of_city + 1, 0);
	vector<int> visited;
	DFS_visit(adj_mat, 1, visited, f, d, color);
	int count = 0;
	for( int i = 1; i <= num_of_city; i ++ ) {
		if( visited[i] ) {
			count++;
		}
	}
	if( count == num_of_city - 1 ) {
		cout << "No new highways need" << endl;
		return;
	}


	for( int i = 1; i <= num_of_city; i ++ ) {
		for( int j = i + 1; j <= num_of_city; j ++ ) {
			if( adj_mat[i][j] ) {
				continue;
			}

			pair<double, double> city1 = vertices[i], city2 = vertices[j];
			edges.push_back( 
				Edge(i, 
					j, 
					sqrt( pow( city1.first - city2.first, 2 ) + pow( city1.second - city2.second, 2 ) ) ) );
			adj_mat[i][j] = 1;
			adj_mat[j][i] = 1;
		}
	}

	sort(edges.begin(), edges.end());

	vector<Edge> result;
	result.clear();
	kruskal(num_of_city, edges, result);
	// sort(result.begin(), result.end(), comp_edge_beautifying);

	for( int i = 0; i < result.size(); i ++ ) {
		Edge e = result[i];
		bool is_regacy = false;
		for( int j = 0; j < regacy_edges.size(); j ++ ) {
			if( regacy_edges[j].u == e.u && regacy_edges[j].v == e.v ) {
				is_regacy = true;
				break;
			}
			if( regacy_edges[j].v == e.u && regacy_edges[j].u == e.v ) {
				is_regacy = true;
				break;
			}
		}

		if( is_regacy ) {
			continue;
		}
		cout << e.u << " " << e.v << endl;
	}
}

int main() {
	int test_case_num;
	cin >> test_case_num;

	while(test_case_num-- > 0) {
		cin >> ws;
		solve();
		cout << endl;
	}

	return 0;
}