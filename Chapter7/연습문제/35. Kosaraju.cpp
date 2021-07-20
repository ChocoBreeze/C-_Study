#include <vector>
#include <stack>
#include <iostream>

using namespace std;

// ������Ѻ��� �����ϱ�
// ù ��° DFS --> Ž���� ���� ���� �ľ�
// �� ��° DFS(Transpose Grapph) --> ���� ���� ��� �ľ�

//DFS ���� --> ���� ��� = 873465210
void FillStack(int node, vector<bool>& visited, 
	vector<vector<int>>& adj, stack<int>& stack) {
	// node = ���� ���� �ε���, visited = �湮�� ���� ���, adj = �׷����� �ǹ��ϴ� ���� ����Ʈ
	// ������ ���� stack = �湮 ������ ���� ���� �ε��� ���.
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

//Transpose�� Graph�� DFS ����
void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component) {
	// component = ������ ���� ���� ��ҿ� ���ϴ� ���� �ε����� �����.
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
	// Transpose(��ġ)�� �׷��� ��ȯ
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

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj) // V = ���� ���� / adj = �׷��� ǥ�� ���� ����Ʈ.
{
	vector<bool> visited(V, false);
	stack<int> stack;
	// ���� �湮���� ���� ������ ���� DFS
	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	// �� ��° DFS ���� Transpose
	vector<vector<int>> transpose = Transpose(V, adj);

	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponents; // ���� ���� ��Ҹ� ���� ������ ������ ����

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

	cout << "���� ���� ��� ����: " << connectedComponents.size() << endl;

	for (int i = 0; i < connectedComponents.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponents[i])
			cout << node << " ";

		cout << endl;
	}
}