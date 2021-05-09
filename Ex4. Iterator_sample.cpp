// �پ��� �ݺ��ڿ��� �̵��ϱ�
#include<iostream>
#include<forward_list>
#include<vector>
#include<string> // �ڵ忡 �߰���

int main()
{
	std::vector<std::string> vec = {
		"Lewis Hamilton", "Newis Hamilton", "Nico Roseberg",
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Seabstian Vettel", "Fernando Alonso"
	};
	auto it = vec.begin();
	std::cout << "���� �ֱ� �����: " << *it << std::endl;

	it += 8; // ��� �ð�
	std::cout << "8�� �� �����: " << *it << std::endl;

	advance(it, -3); // ��� �ð�
	std::cout << "�� �� 3�� �� �����: " << *it << std::endl;

	std::forward_list<std::string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	std::cout << "���� �ֱ� �����: " << *it1 << std::endl;

	advance(it1, 5);
	std::cout << "5�� �� �����: " << *it1 << std::endl;
	// advance(iterator, �Ÿ�) �ݺ��ڸ� �Ÿ���ŭ ����
	// advance(it1, -2); ������ �̵� �Ұ� -> ����
	// it1 += 2;�� ���������� ���� ���� �Ұ���
	return 0;
}