// ���� ���� �����ϴ� ������ ����
// ��ȣ ���� ������ ����ϴ� �⺻���� �ؽ� ��
#include<iostream>
#include<vector>

using uint = unsigned int;

using std::vector;
class hash_map {
	vector<int> data;

public:
	hash_map(size_t n) {
		data = vector<int>(n, -1); // n�� -1�� �Ҵ� -> ���� ������ �ǹ�
	}

	void insert(uint value) {
		int n = data.size();
		data[value%n] = value;
		std::cout << value << "��(��) �����߽��ϴ�. " << std::endl; 
		//���� �� ���� Ȯ�� ���� �ߺ��̶�� �׳� ���� ��
	}

	bool find(uint value) {
		int n = data.size();
		return (data[value%n] == value);
	}

	void erase(uint value) {
		int n = data.size();
		if (data[value%n] == value) {
			data[value%n] == -1;
			std::cout << value << "��(��) �����߽��ϴ�." << std::endl;
		}
	}
};

int main() {
	hash_map map(7);

	auto print = [&](int value) {
		if (map.find(value)) std::cout << "�ؽ� �ʿ��� " << value << "��(��) ã�ҽ��ϴ�.";
		else std::cout << "�ؽ� �ʿ��� " << value << "��(��) ã�� ���߽��ϴ�.";
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

	//�浹 ���� �ذ� �� �� --> Ű�� ���� �Բ� �����ϴ� ����� �̿��ؾ� �Ѵ�.
}