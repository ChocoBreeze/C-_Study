// 0 -1 knapsack
// tabulation
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Knapsack_01(int items, int capacity, vector<int> values, vector<int> weight) {
	// �κ������� �� ������ ������ ����. (���ǰ��� + 1, �賶 �뷮 + 1)
	vector<vector<int>> DP(items + 1, vector<int>(capacity + 1, 0));

	for (int i = 1; i <= items; i++)
	{
		int currentWeight = weight[i - 1]; // ���� ���� ����
		int currentValue = values[i - 1]; // ���� ���� ����

		for (int totalWeight = 1; totalWeight <= capacity; totalWeight++)
		{
			if (totalWeight < currentWeight)
			{
				DP[i][totalWeight] = DP[i - 1][totalWeight];	// ���� x
			}
			else
			{
				DP[i][totalWeight] = max(DP[i - 1][totalWeight], // ���� x
					DP[i - 1][totalWeight - currentWeight] + currentValue); // ���� o
			}
		}
	}

	return DP[items][capacity];
}

int main()
{
	int items, capacity; // ��ü ���� ����, �賶�� ���� �뷮
	cin >> items >> capacity;

	vector<int> values(items), weight(items); // �� ������ ���ݰ� ����

	//�̷��� �Է¹��� ���� �ֱ���..
	for (auto& v : values) cin >> v;
	for (auto& w : weight) cin >> w;

	int result = Knapsack_01(items, capacity, values, weight);

	cout << "�賶�� ä�� �� �ִ� ���ǵ��� �ְ� ����: " << result << endl;
}

/*
	8 66
	20 4 89 12 5 50 8 13
	5 23 9 72 16 14 32 4
	returns 180.
*/