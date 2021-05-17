//Áß¾Ó°ª(median) ±¸ÇÏ±â
#include<iostream>
#include<queue>
#include<vector>

struct median {
	std::priority_queue<int> maxHeap;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // greater<int> a>b
	//priority queue T, container, Compare

	void insert(int data) { // »õ·Î µé¾î¿Â µ¥ÀÌÅÍ ÀúÀå
		// Áß¾Ó°ªº¸´Ù ÀÛÀº »õ µ¥ÀÌÅÍ -> ÃÖ´ë Èü
		// Áß¾Ó°ªº¸´Ù Å« »õ µ¥ÀÌÅÍ -> ÃÖ¼Ò Èü
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

	double get() { // ÀúÀåµÈ ¿ø¼Ò·ÎºÎÅÍ Áß¾Ó°ª ¹ÝÈ¯
		if (maxHeap.size() == minHeap.size()) return (maxHeap.top() + minHeap.top()) / 2.0;
		if (maxHeap.size() < minHeap.size())
			return minHeap.top();

		return maxHeap.top();
	}
};

int main() {
	median med;

	med.insert(1);
	std::cout << "1 »ðÀÔ ÈÄ Áß¾Ó°ª: " << med.get() << std::endl;

	med.insert(5);
	std::cout << "5 »ðÀÔ ÈÄ Áß¾Ó°ª: " << med.get() << std::endl;

	med.insert(2);
	std::cout << "2 »ðÀÔ ÈÄ Áß¾Ó°ª: " << med.get() << std::endl;

	med.insert(10);
	std::cout << "10 »ðÀÔ ÈÄ Áß¾Ó°ª: " << med.get() << std::endl;

	med.insert(40);
	std::cout << "40 »ðÀÔ ÈÄ Áß¾Ó°ª: " << med.get() << std::endl;
	
	return 0;
}