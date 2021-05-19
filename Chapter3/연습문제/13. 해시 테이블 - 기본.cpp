// 정수 값을 저장하는 간단한 사전
// 부호 없는 정수를 사용하는 기본적인 해시 맵
#include<iostream>
#include<vector>

using uint = unsigned int;

using std::vector;
class hash_map {
	vector<int> data;

public:
	hash_map(size_t n) {
		data = vector<int>(n, -1); // n개 -1로 할당 -> 원소 없음을 의미
	}

	void insert(uint value) {
		int n = data.size();
		data[value%n] = value;
		std::cout << value << "을(를) 삽입했습니다. " << std::endl; 
		//기존 값 존재 확인 없이 중복이라면 그냥 덮어 씀
	}

	bool find(uint value) {
		int n = data.size();
		return (data[value%n] == value);
	}

	void erase(uint value) {
		int n = data.size();
		if (data[value%n] == value) {
			data[value%n] == -1;
			std::cout << value << "을(를) 삭제했습니다." << std::endl;
		}
	}
};

int main() {
	hash_map map(7);

	auto print = [&](int value) {
		if (map.find(value)) std::cout << "해시 맵에서 " << value << "을(를) 찾았습니다.";
		else std::cout << "해시 맵에서 " << value << "을(를) 찾지 못했습니다.";
		std::cout << std::endl;
	};

	map.insert(2);
	map.insert(25);
	map.insert(10);
	print(25);

	map.insert(100);
	print(100);
	print(2);

	map.erase(25);
	return 0;

	//충돌 문제 해결 못 함 --> 키와 값을 함께 저장하는 방식을 이용해야 한다.
}