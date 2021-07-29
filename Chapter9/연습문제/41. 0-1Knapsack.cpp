// 0 -1 knapsack
// tabulation
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Knapsack_01(int items, int capacity, vector<int> values, vector<int> weight) {
	// 부분집합의 합 문제와 유사한 구조. (물건개수 + 1, 배낭 용량 + 1)
	vector<vector<int>> DP(items + 1, vector<int>(capacity + 1, 0));

	for (int i = 1; i <= items; i++)
	{
		int currentWeight = weight[i - 1]; // 현재 물건 무게
		int currentValue = values[i - 1]; // 현재 물건 가격

		for (int totalWeight = 1; totalWeight <= capacity; totalWeight++)
		{
			if (totalWeight < currentWeight)
			{
				DP[i][totalWeight] = DP[i - 1][totalWeight];	// 선택 x
			}
			else
			{
				DP[i][totalWeight] = max(DP[i - 1][totalWeight], // 선택 x
					DP[i - 1][totalWeight - currentWeight] + currentValue); // 선택 o
			}
		}
	}

	return DP[items][capacity];
}

int main()
{
	int items, capacity; // 전체 물건 개수, 배낭의 제한 용량
	cin >> items >> capacity;

	vector<int> values(items), weight(items); // 각 물건의 가격과 무게

	//이렇게 입력받을 수도 있구나..
	for (auto& v : values) cin >> v;
	for (auto& w : weight) cin >> w;

	int result = Knapsack_01(items, capacity, values, weight);

	cout << "배낭에 채울 수 있는 물건들의 최고 가격: " << result << endl;
}

/*
	8 66
	20 4 89 12 5 50 8 13
	5 23 9 72 16 14 32 4
	returns 180.
*/