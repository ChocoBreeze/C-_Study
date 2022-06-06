#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UnboundedKnapsack(int items, int capacity, vector<int> values, vector<int> weight) {
	auto max = [](int a, int b, int c) {return std::max(a, std::max(b, c)); };
	vector<vector<int>> DP(items+1, vector<int> (capacity + 1, 0));

	for (int i = 1; i <= items; ++i) {
		int current_weight = weight[i - 1];
		int value = values[i - 1];

		for (int total_weight = 0; total_weight <= capacity; ++total_weight) {
			if (total_weight < current_weight) {
				DP[i][total_weight] = DP[i - 1][total_weight];
			}
			else {
				DP[i][total_weight] = max(DP[i - 1][total_weight], DP[i-1][total_weight - current_weight] + value, DP[i-1][total_weight - current_weight] + value);
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

	int result = UnboundedKnapsack(items, capacity, values, weight);

	cout << "배낭에 채울 수 있는 물건들의 최고 가격: " << result << endl;
}
