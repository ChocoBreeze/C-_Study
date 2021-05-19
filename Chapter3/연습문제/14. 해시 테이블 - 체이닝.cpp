// 해시 테이블 구현 + 체이닝을 이용한 충돌 처리
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using uint = unsigned int;

using std::vector;
using std::list;
class hash_map {
	vector<list<int>> data;

public:
	hash_map(size_t n) { // 인자 = 해시 맵 또는 데이터 크기
		data.resize(n);
	}

	void insert(uint value) { // value 값을 항상 추가
		int n = data.size();
		data[value%n].push_back(value);
		std::cout << value << "을(를) 삽입했습니다." << std::endl;
	}

	bool find(uint value) {
		int n = data.size();
		auto& entries = data[value%n];
		return std::find(entries.begin(), entries.end(), value) != entries.end(); // 찾아진 경우 TRUE
	}

	void erase(uint value) { // 하나만 제거
		int n = data.size();
		auto& entries = data[value%n]; // 같은 해시 값 가지는 list 가져 옴
		auto iter = std::find(entries.begin(), entries.end(), value);

		if (iter != entries.end()) {
			entries.erase(iter);
			std::cout << value << "을(를) 삭제했습니다." << std::endl;
		}
	}
};

int main() {
	hash_map map(7);

	auto print = [&](int value) {
		if (map.find(value))
			std::cout << "해시 맵에서 " << value << "을(를) 찾았습니다.";
		else
			std::cout << "해시 맵에서 " << value << "을(를) 찾지 못했습니다.";
		std::cout << std::endl;
	};

	map.insert(2);
	map.insert(25);
	map.insert(10);

	map.insert(100);
	map.insert(55);

	print(100);
	print(2);

	map.erase(2);
}