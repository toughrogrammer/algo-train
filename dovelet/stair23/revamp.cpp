#include <iostream>
#include <queue>

#define MAX_AREA 10001
#define MAX_EDGE 50001
#define MAX_K 25
#define MAX 0x0FFFFFFF

using namespace std;

struct Edge {
	int u, v, dist;
	
	Edge(int u, int v, int dist){
		this->u = u;
		this->v = v;
		this->dist = dist;
	}
};

struct Node {
	int u, k, dist;
	
	Node() {}
	Node(int u, int k, int dist) {
		this->u = u;
		this->k = k;
		this->dist = dist;
	}
	
	bool operator< (const Node& rhs) const {
		return this->dist > rhs.dist;
	}
};


int main(){
	int N, M, K;
	cin >> N >> M >> K;

	vector< vector<Edge> > edge_list(N + 1);
	for(int i = 1; i <= N; i ++){
		edge_list[i].push_back( Edge(i, i, 0) );
	}
	
	for(int i = 0; i < M; i ++){
		int u, v, dist;
		cin >> u >> v >> dist;

		edge_list[u].push_back( Edge(u, v, dist) );
		edge_list[v].push_back( Edge(v, u, dist) );
	}
;
	bool visited[MAX_K][MAX_AREA] = { false, };
	int dist[MAX_K][MAX_AREA];
	for( int i = 0; i <= K; i ++ ) {
		for( int j = 0; j <= N; j ++ ) {
			dist[i][j] = MAX;
		}
	}
	
	
	priority_queue<Node> pq;
	pq.push( Node(1, 0, 0) );
	
	Node node;
	while(! pq.empty()) {
		node = pq.top();
		pq.pop();
		
		if( node.u == N && node.k == K ) {
			break;
		}
		
		if( visited[node.k][node.u] ) {
			continue;
		}
		visited[node.k][node.u] = true;
		
		const vector<Edge>& edges = edge_list[node.u];
		for( int i = 0; i < edges.size(); i ++ ) {
			const Edge& edge = edges[i];
			int new_dist = node.dist + edge.dist;
			if( !visited[node.k][edge.v] 
				&& dist[node.k][edge.v] > new_dist ) {
				dist[node.k][edge.v] = new_dist;
				pq.push( Node(edge.v, node.k, new_dist) );
			}
			
			if( node.k < K && !visited[node.k + 1][edge.v]
				&& dist[node.k + 1][edge.v] > node.dist ) {
				dist[node.k + 1][edge.v] = node.dist;
				pq.push( Node(edge.v, node.k + 1, node.dist) );
			}
		}
	}

	cout << node.dist << endl;

	return 0;
}