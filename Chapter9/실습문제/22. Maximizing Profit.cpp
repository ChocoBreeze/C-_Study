// maximize profit
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Product {
	int quantity;
	int price;
	int value;

	Product(int q, int c, int y) :quantity(q), price(c), value(y) {}
};

int main() {
	int N, budget, capacity;
	cin >> N >> budget >> capacity; // 제품 개수, 예산, 구매가능한 제품 최대 수

	vector<Product> products;

	for (int i = 0; i < N; i++) {
		int quantity, cost, value; // 제품 양, 가격 , 판매 시 얻을 수 있는 이익
		cin >> quantity >> cost >> value;

		products.push_back(Product(quantity, cost, value));
	}
	// 제약 사항 = capacity & budget --> 3차원
	vector<vector<vector<int>>> DP(N + 1, vector<vector<int>>(budget + 1, vector<int>(capacity + 1, 0)));

	for (int i = 1; i <= N; i++) {
		Product product = products[i - 1];
		for (int cost = 0; cost <= budget; cost++) {
			for (int count = 0; count <= capacity; count++) {
				if (cost < product.price || count < product.quantity) {// 안 넣고 통과
					DP[i][cost][count] = DP[i - 1][cost][count];
				}
				else { // 넣은 것과 안 넣은 것 중 max 취함.
					DP[i][cost][count] = max(DP[i - 1][cost][count],
						DP[i - 1][cost - product.price][count - product.quantity] + product.value);
				}
			}
		}
	}
	cout << DP[N][budget][capacity] << endl;
	return 0;
}