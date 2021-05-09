// 다양한 반복자에서 이동하기
#include<iostream>
#include<forward_list>
#include<vector>
#include<string> // 코드에 추가함

int main()
{
	std::vector<std::string> vec = {
		"Lewis Hamilton", "Newis Hamilton", "Nico Roseberg",
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Seabstian Vettel", "Fernando Alonso"
	};
	auto it = vec.begin();
	std::cout << "가장 최근 우승자: " << *it << std::endl;

	it += 8; // 상수 시간
	std::cout << "8년 전 우승자: " << *it << std::endl;

	advance(it, -3); // 상수 시간
	std::cout << "그 후 3년 뒤 우승자: " << *it << std::endl;

	std::forward_list<std::string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	std::cout << "가장 최근 우승자: " << *it1 << std::endl;

	advance(it1, 5);
	std::cout << "5년 전 우승자: " << *it1 << std::endl;
	// advance(iterator, 거리) 반복자를 거리만큼 증가
	// advance(it1, -2); 역방향 이동 불가 -> 에러
	// it1 += 2;도 마찬가지로 에러 덧셈 불가능
	return 0;
}