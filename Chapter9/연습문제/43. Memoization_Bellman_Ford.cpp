// 단일 시작 최단 경로
// Memoization
// 하향식 동적 계획법.
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>

using namespace std;

const int UNKNOWN = 1e9;

int V, E; // 정점 개수, Edge 개수
vector<vector<int>> weight; // Weight
vector<vector<int>> adj; // 인접 리스트

map<pair<int, int>, int> memo; // Memoization용 table - 키의 존재 여부 + 키가 UNKNOWN인지 확인

int ShortestPath_Memoization(int depth, int node,
vector<vector<int>>& adj, vector<vector<int>>& weight) {
	// 반복횟수(depth), node = 정점..
	// DFS 수행.
	// 맵에 키가 있는지를 확인
	if (memo.find({ node, depth }) != memo.end())
	{
		return memo[{node, depth}];
	}

	memo[{node, depth}] = UNKNOWN;

	// 인접한 에지에 대해 반복
	for (auto next : adj[node])
	{
		int w = weight[node][next]; // 인접 vertex에 대한 weight
		int dist = ShortestPath_Memoization(depth - 1, next, adj, weight) + w;

		memo[{node, depth}] = min(memo[{node, depth}], dist);
	}

	return memo[{node, depth}];
}

vector<int> SingleSourceShortestPaths(int source) { // source = 시작 정점.
	// 접근 : 다른 모든 정점에서 시작 정점까지의 weight 합 계산 할 것 --> 전치된 그래프 필요.
	vector<vector<int>> adj_t(V);
	vector<vector<int>> weight_t(V, vector<int>(V, UNKNOWN));

	memo.clear();

	for (int i = 0; i < V; i++)
	{
		// 전치 그래프 생성
		for (auto j : adj[i])
		{
			adj_t[j].push_back(i);
			weight_t[j][i] = weight[i][j];
		}

		// 기저 조건 - 시작 정점에서 자기 자신까지의 최단 거리는 항상 0
		//memo[{node, depth{], 즉 모든 depth(반복수)에 대해서 자기 자신까지의 최단 거리 = 0
		memo[{source, i}] = 0;

		if (i != source) {
			// V-1 반복 후 소스 이외의 노드에 도달한 경우, depth = 0
			// 경로가 존재하지 않음
			memo[{i, 0}] = UNKNOWN;
		}
	}

	vector<int> distance(V);

	for (int i = 0; i < V; i++)
	{
		// 전치된 그래프에서 시작 정점 i
		distance[i] = ShortestPath_Memoization(V - 1, i, adj_t, weight_t);
	}

	return distance; // 각각의 정점에서 시작 정점까지 가는 최단 거리.
}

int main()
{
	cin >> V >> E;

	weight.resize(V, vector<int>(V, UNKNOWN));
	adj.resize(V);

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w; // u -> v, weight = w

		adj[u].push_back(v);
		weight[u][v] = w;
	}

	vector<vector<int>> paths(V); // 실질적인 경로 저장.

	for (int i = 0; i < V; i++)
	{
		paths[i] = SingleSourceShortestPaths(i);
	}

	cout << "각 정점 사이의 최단 거리:" << endl;

	for (int i = 0; i < V; i++)
	{
		cout << i << ": ";

		for (int j = 0; j < V; j++)
		{
			(paths[i][j] == UNKNOWN) ? cout << "- "
				: cout << paths[i][j] << " ";
		}
		cout << endl;
	}
}
/*
* TC 1
8 20
0 1 387
0 3 38
0 5 471
1 0 183
1 4 796
2 5 715
3 0 902
3 1 712
3 2 154
3 6 425
4 3 834
4 6 214
5 0 537
5 3 926
5 4 125
5 6 297
6 1 863
6 7 248
7 0 73
7 3 874
*/