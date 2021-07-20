#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// 실행시켜보고 이해하기
// 첫 번째 DFS --> 탐색을 통해 순서 파악
// 두 번째 DFS(Transpose Grapph) --> 강한 연결 요소 파악

//DFS 구현 --> 최종 결과 = 873465210
void FillStack(int node, vector<bool>& visited, 
	vector<vector<int>>& adj, stack<int>& stack) {
	// node = 현재 정점 인덱스, visited = 방문한 정점 기록, adj = 그래프를 의미하는 인접 리스트
	// 정수형 스택 stack = 방문 순서에 따른 정점 인덱스 기록.
	visited[node] = true;

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}

	stack.push(node);
}

//Transpose된 Graph에 DFS 구현
void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component) {
	// component = 각각의 강한 연결 요소에 속하는 정점 인덱스가 저장됨.
	visited[node] = true;
	component.push_back(node);

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			CollectConnectedComponents(next, visited, adj, component);
		}
	}
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj) {
	// Transpose(전치)된 그래프 반환
	vector<vector<int>> transpose(V);

	for (int i = 0; i < V; i++)
	{
		for (auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}

	return transpose;
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj) // V = 정점 개수 / adj = 그래프 표현 인접 리스트.
{
	vector<bool> visited(V, false);
	stack<int> stack;
	// 아직 방문되지 않은 정점에 대해 DFS
	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	// 두 번째 DFS 전에 Transpose
	vector<vector<int>> transpose = Transpose(V, adj);

	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponents; // 강한 연결 요소를 담은 정수형 벡터의 벡터

	while (!stack.empty())
	{
		int node = stack.top();
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;

			CollectConnectedComponents(node, visited, transpose, component);
			connectedComponents.push_back(component);
		}
	}

	return connectedComponents;
}

int main()
{
	int V = 9;

	vector<vector<int>> adj =
	{
		{ 1, 3 },
		{ 2, 4 },
		{ 3, 5 },
		{ 7 },
		{ 2 },
		{ 4, 6 },
		{ 7, 2 },
		{ 8 },
		{ 3 }
	};

	vector<vector<int>> connectedComponents = Kosaraju(V, adj);

	cout << "강한 연결 요소 개수: " << connectedComponents.size() << endl;

	for (int i = 0; i < connectedComponents.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponents[i])
			cout << node << " ";

		cout << endl;
	}
}