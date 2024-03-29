// Unbounded Knapsack - 무한 개수 배낭
// Tabulation
// 상태 공간 축소 - DP table 1차원으로 축소
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UnboundedKnapsack(int items, int capacity, vector<int> values, vector<int> weight) {
	vector<int> DP(capacity + 1, 0);

	for (int w = 0; w <= capacity; w++) {
		for (int i = 0; i < items; i++) {
			if (weight[i] <= w) {
				DP[w] = max(DP[w], DP[w - weight[i]] + values[i]);
			}
		}
	}
	return DP[capacity];
}

int main()
{
	int items, capacity; // 전체 물건 개수, 배낭의 제한 용량
	cin >> items >> capacity;

	vector<int> values(items), weight(items); // 각 물건의 가격과 무게

	//이렇게 입력받을 수도 있구나..
	for (auto& v : values) cin >> v;
	for (auto& w : weight) cin >> w;

	int result = UnboundedKnapsack(items, capacity, values, weight);

	cout << "배낭에 채울 수 있는 물건들의 최고 가격: " << result << endl;
}

/*
* TC 1
 5 12
 5 1 6 3 4
 3 2 4 5 2
*/

/*
* TC 2
 30 335
 91 81 86 64 24 61 13 57 60 25 94 54 39 62 5 34 95 12 53 33 53 3 42 75 56 1
 84 38 46 62
 40 13 4 17 16 35 5 33 35 16 25 29 6 28 12 37 26 27 32 27 7 24 5 28 39 15
 38 37 15 40
*/