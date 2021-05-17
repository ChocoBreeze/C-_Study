// 힙 -> 데이터 리스트 병합
#include<iostream>
#include<algorithm> // push_heap, pop_heap -- maxheap 유지 --> vector
#include<vector>

struct node {
	int data;
	int listPosition;
	int dataPosition;
};

using std::vector;
vector<int> merge(const vector<vector<int>>& input) {
	auto comparator = [](const node& left, const node& right) { // lambda
		if (left.data == right.data)
			return left.listPosition > right.listPosition;
		return left.data > right.data;
	};

	vector<node> heap;
	for (int i = 0; i < input.size(); i++) {
		heap.push_back({ input[i][0],i,0 }); // 값, listposition, dataposition
		std::push_heap(heap.begin(), heap.end(), comparator); // left > right -- greater -> min_heap
	}

	vector<int> result;
	while (!heap.empty()) {
		std::pop_heap(heap.begin(), heap.end(), comparator); // minheap의 root 꼬리로 이동
		auto min = heap.back(); // 꼬리 값 가져옴
		heap.pop_back(); // 꼬리 제거

		result.push_back(min.data);
		int nextIndex = min.dataPosition + 1;
		if (nextIndex < input[min.listPosition].size()) { // 뺀 배열의 다음 값 가져옴(이미 정렬된 배열)
			heap.push_back({ input[min.listPosition][nextIndex], min.listPosition, nextIndex });
			std::push_heap(heap.begin(), heap.end(), comparator); // heap 만족하도록 정리
		}
	}
	return result;
}

int main() {
	std::vector<int> v1 = { 1, 3, 8, 15, 105 };
	std::vector<int> v2 = { 2, 3, 10, 11, 16, 20, 25 };
	std::vector<int> v3 = { -2, 100, 1000 };
	std::vector<int> v4 = { -1, 0, 14, 18 };

	auto result = merge({ v1, v2, v3, v4 });

	for (auto i : result)
		std::cout << i << ' ';
	std::cout << std::endl;

	return 0;
}