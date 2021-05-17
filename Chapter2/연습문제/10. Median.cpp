//중앙값(median) 구하기
#include<iostream>
#include<queue>
#include<vector>

struct median {
	std::priority_queue<int> maxHeap;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // greater<int> a>b
	//priority queue T, container, Compare

	void insert(int data) { // 새로 들어온 데이터 저장
		// 중앙값보다 작은 새 데이터 -> 최대 힙
		// 중앙값보다 큰 새 데이터 -> 최소 힙
		if (maxHeap.size() == 0) {
			maxHeap.push(data);
			return;
		}
		if (maxHeap.size() == minHeap.size()) {
			if (data <= get()) maxHeap.push(data);
			else minHeap.push(data);

			return;
		}

		if (maxHeap.size() < minHeap.size()) {
			if (data > get()) {
				maxHeap.push(minHeap.top());
				minHeap.pop();
				minHeap.push(data);
			}
			else
				maxHeap.push(data);

			return;
		}

		if (data < get()) { // maxHeap.size() > minHeap.size()
			minHeap.push(maxHeap.top());
			maxHeap.pop();
			maxHeap.push(data);
		}
		else minHeap.push(data);
	}

	double get() { // 저장된 원소로부터 중앙값 반환
		if (maxHeap.size() == minHeap.size()) return (maxHeap.top() + minHeap.top()) / 2.0;
		if (maxHeap.size() < minHeap.size())
			return minHeap.top();

		return maxHeap.top();
	}
};

int main() {
	median med;

	med.insert(1);
	std::cout << "1 삽입 후 중앙값: " << med.get() << std::endl;

	med.insert(5);
	std::cout << "5 삽입 후 중앙값: " << med.get() << std::endl;

	med.insert(2);
	std::cout << "2 삽입 후 중앙값: " << med.get() << std::endl;

	med.insert(10);
	std::cout << "10 삽입 후 중앙값: " << med.get() << std::endl;

	med.insert(40);
	std::cout << "40 삽입 후 중앙값: " << med.get() << std::endl;
	
	return 0;
}
