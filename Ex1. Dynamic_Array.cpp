/*동적 크기 배열 구현*/
#define _SCL_SECURE_NO_WARNINGS
#include<string>
#include<algorithm>
#include<iostream>
#include<sstream> // stringstream

using std::string;
// 동적 배열
template <typename T>
class dynamic_array {
private:
	T* data; // 자료형
	size_t n; // 크기

public:
	dynamic_array(int n) {
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other) {
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; ++i) {
			data[i] = other[i];
		}
	}

	T& operator[](int index) {
		return data[index];
	}

	const T& operator[](int index) const {
		return data[index];
	}

	T& at(int index) {
		if (index < n) {
			return data[index];
		}
		throw "Index out of range";
	}

	//size 반환
	size_t size() const {
		return n;
	}

	~dynamic_array() {
		delete[] data;
	}

	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() const { return data + n; }

	// concatenate
	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2) {
		dynamic_array<T> result(arr1.size() + arr2.size());
		std::copy(arr1.begin(), arr1.end(), result.begin());
		std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

		return result;
	}

	// 배열에 저장된 모든 데이터 문자열로 반환
	string to_string(const string& sep = ", ") {
		if (n == 0)
			return "";

		std::ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++) {
			os << sep << data[i];
		}

		return os.str();
	}
};

// 학생 정보를 저장할 구조체
struct student {
	string name;
	int standard; // 학급
};

std::ostream& operator<<(std::ostream& os, const student& s) {
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main() {
	int nStudents;
	std::cout << "1반 학생 수를 입력하세요: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++) {
		string name;
		int standard;
		std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard }; 
		// class1[i].name = name;
		// class1[i].standard = standard;
	}

	// 배열 크기보다 큰 인덱스의 학생에 접근
	/*try {
		//class1[nStudents] = student{ "John", 8 }; // 예상할 수 없는 동작
		//class1.at(nStudents) = student{ "John", 8 };
	} catch (...) {
		std::cout << "예외 발생!" << std::endl;
	}*/

	//깊은 복사
	auto class2 = class1;
	std::cout << "1번을 복사하여 2번 생성: " << class2.to_string() << std::endl;

	//두 학급을 합쳐서 새로운 큰 학급 생성
	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << std::endl;

	return 0;
}

