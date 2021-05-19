// �ؽ� ���̺� ���� + ü�̴��� �̿��� �浹 ó��
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
	hash_map(size_t n) { // ���� = �ؽ� �� �Ǵ� ������ ũ��
		data.resize(n);
	}

	void insert(uint value) { // value ���� �׻� �߰�
		int n = data.size();
		data[value%n].push_back(value);
		std::cout << value << "��(��) �����߽��ϴ�." << std::endl;
	}

	bool find(uint value) {
		int n = data.size();
		auto& entries = data[value%n];
		return std::find(entries.begin(), entries.end(), value) != entries.end(); // ã���� ��� TRUE
	}

	void erase(uint value) { // �ϳ��� ����
		int n = data.size();
		auto& entries = data[value%n]; // ���� �ؽ� �� ������ list ���� ��
		auto iter = std::find(entries.begin(), entries.end(), value);

		if (iter != entries.end()) {
			entries.erase(iter);
			std::cout << value << "��(��) �����߽��ϴ�." << std::endl;
		}
	}
};

int main() {
	hash_map map(7);

	auto print = [&](int value) {
		if (map.find(value))
			std::cout << "�ؽ� �ʿ��� " << value << "��(��) ã�ҽ��ϴ�.";
		else
			std::cout << "�ؽ� �ʿ��� " << value << "��(��) ã�� ���߽��ϴ�.";
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