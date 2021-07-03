//vaccine
#include<iostream>
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>

class Student {
private:
	std::pair<int, int>name;	//
	bool vaccinated;			//백신 접종여부

public:
	Student(std::pair<int, int>n, bool v) : name(n), vaccinated(v) {}
	
	auto get_name() { return name; }
	auto is_vaccinated() { return vaccinated; }

	bool operator==(const Student& p) const {
		return this->name == p.name;
	}
	bool operator< (const Student& p) const
	{
		return this->name < p.name;
	}
	bool operator> (const Student& p) const
	{
		return this->name > p.name;
	}

};

//1부터 max 사이의 ID를 갖는 임의의 학생 정보 생성
auto generate_random_Student(int max) {
	std::random_device rd;
	std::mt19937 rand(rd());

	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, max);
	std::bernoulli_distribution bernoulli_dist(0.5f); // 내가 추가 해봄

	auto random_name = std::make_pair(uniform_dist(rand), uniform_dist(rand));
	// bool is_vaccinated = uniform_dist(rand) % 2 ? true : false; // 기존 코드
	bool is_vaccinated = bernoulli_dist(rand);

	return Student(random_name, is_vaccinated);
}

bool needs_vaccination(Student P, std::vector<Student>& people) {
	auto first = people.begin();
	auto last = people.end();

	while (true) {
		auto range_length = std::distance(first, last);
		auto mid_element_index = std::floor(range_length / 2);
		auto mid_element = *(first + mid_element_index);

		// 목록에 해당 학생이 있고, 예방 접종을 받지 않았다면 true를 반환
		if (mid_element == P && mid_element.is_vaccinated() == false)
			return true;
		// 목록에 해당 학생이 있는데 이미 예방 접종을 받았다면 false를 반환
		else if (mid_element == P && mid_element.is_vaccinated() == true)
			return false;
		else if (mid_element > P)
			std::advance(last, -mid_element_index);
		//advance : iterator 이동 시키는 함수 (1st element = iterator, 2nd element = 이동시킬 offset 수)
		if (mid_element < P)
			std::advance(first, mid_element_index);

		// 목록에 해당 학생이 없다면 true를 반환
		if (range_length == 1)
			return true;
	}
}

void search_test(int size, Student p) {
	std::vector<Student> people;

	for (auto i = 0; i < size; i++)
		people.push_back(generate_random_Student(size));

	std::sort(people.begin(), people.end());

	auto begin = std::chrono::steady_clock::now();
	bool search_result = needs_vaccination(p, people);
	auto end = std::chrono::steady_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	std::cout << "이진 검색 소요 시간: " << diff.count() << "us" << std::endl; // count - 시간 간격의 클록 틱 수 반환

	if (search_result)
		std::cout << "(" << p.get_name().first << " " << p.get_name().second << ") "
		<< "학생은 예방 접종이 필요합니다." << std::endl;
	else
		std::cout << "(" << p.get_name().first << " " << p.get_name().second << ") "
		<< "학생은 예방 접종이 필요하지 않습니다." << std::endl;
}

int main() {
	// 임의의 학생 정보 생성
	auto p = generate_random_Student(1000);

	search_test(1000, p);
	search_test(10000, p);
	search_test(100000, p);

	return 0;
}