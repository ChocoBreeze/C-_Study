/*���� ũ�� �迭 ����*/
#define _SCL_SECURE_NO_WARNINGS
#include<string>
#include<algorithm>
#include<iostream>
#include<sstream> // stringstream

using std::string;
// ���� �迭
template <typename T>
class dynamic_array {
private:
	T* data; // �ڷ���
	size_t n; // ũ��

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

	//size ��ȯ
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

	// �迭�� ����� ��� ������ ���ڿ��� ��ȯ
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

// �л� ������ ������ ����ü
struct student {
	string name;
	int standard; // �б�
};

std::ostream& operator<<(std::ostream& os, const student& s) {
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main() {
	int nStudents;
	std::cout << "1�� �л� ���� �Է��ϼ���: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++) {
		string name;
		int standard;
		std::cout << i + 1 << "��° �л� �̸��� ���̸� �Է��ϼ���: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard }; 
		// class1[i].name = name;
		// class1[i].standard = standard;
	}

	// �迭 ũ�⺸�� ū �ε����� �л��� ����
	/*try {
		//class1[nStudents] = student{ "John", 8 }; // ������ �� ���� ����
		//class1.at(nStudents) = student{ "John", 8 };
	} catch (...) {
		std::cout << "���� �߻�!" << std::endl;
	}*/

	//���� ����
	auto class2 = class1;
	std::cout << "1���� �����Ͽ� 2�� ����: " << class2.to_string() << std::endl;

	//�� �б��� ���ļ� ���ο� ū �б� ����
	auto class3 = class1 + class2;
	std::cout << "1�ݰ� 2���� ���� 3�� ����: " << class3.to_string() << std::endl;

	return 0;
}

