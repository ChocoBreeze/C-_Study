// Floyd-Warshall
// 모든 정점 간에 최단 거리
#include <vector>
#include <iostream>

using namespace std;

const int UNKNOWN = 1e9;

vector<vector<int>> FloydWarshall(int V, vector<vector<int>> weight) { // 
	vector<vector<int>> distance(V, vector<int>(V, UNKNOWN));

	//초기 최단 거리 값 지정
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			distance[i][j] = weight[i][j];
		}
		distance[i][i] = 0;
	}

	for (int mid = 0; mid < V; mid++) // 중간 정점
	{
		for (int start = 0; start < V; start++) // 시작 정점
		{
			for (int end = 0; end < V; end++) // 목표 정점
			{
				if (distance[start][mid] + distance[mid][end] < distance[start][end])
				{
					distance[start][end] = distance[start][mid] + distance[mid][end];
				}
			}
		}
	}

	for (int i = 0; i < V; i++)
	{
		// 자기 자신으로의 거리가 0보다 작으면 음수 가중치 사이클이 있는 것으로 판단
		if (distance[i][i] < 0)
			return {};
	}

	return distance; // 최단 거리가 저장된 2차원 벡터
}

int main()
{
	int V, E; // 정점 수, 간선 수
	cin >> V >> E;

	vector<vector<int>> weight(V, vector<int>(V, UNKNOWN));

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w; // u -> v, weight = w

		weight[u][v] = w;
	}

	vector<vector<int>> distance = FloydWarshall(V, weight);

	if (distance.empty())
	{
		cout << "음수 가중치 사이클이 있습니다." << endl;
		return 0;
	}

	for (int i = 0; i < V; i++) {
		cout << i << endl;
		for (int j = 0; j < V; j++) {
			cout << "\t" << j << ": ";
			(distance[i][j] == UNKNOWN) ? cout << "_" << endl : cout << distance[i][j] << endl;
		}
	}
	return 0;
}

/*
* TC 1
7 9
0 1 3
1 2 5
1 3 10
1 5 -4
2 4 2
3 2 -7
4 1 -3
5 6 -8
6 0 12
*/

/*
* TC 2
6 8
0 1 3
1 3 -8
2 1 3
2 4 2
2 5 5
3 2 3
4 5 -1
5 1 8
*/