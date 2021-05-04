// �پ��� Ÿ���� ������ -> ���� Ÿ�� ��ȯ
#include<array> // ��ü ���� ���� ��ȸ�� ����
#include<iostream>
#include<type_traits>

using std::array;
/*
auto�� ���� �����ϴ� Ÿ���� �߷н����ִ� Ű������,
decaltype�� �����κ��� Ÿ���� ������ �� �� �ִ� Ű������ �����ϸ� �ȴ�.
trailing return type(���� ��ȯ ����) auto ��ȯ������ �ַ� �̿�
*/
// �����̳� ���� �Լ� - ���� ���ø�(���� ������ �Ű����� ���)
// common_type : Determines the common type among all types T..., that is the type all T... can be implicitly converted to.
// auto & decltype(declared type)
// std::forward ������ ����. ���� ����.
template<typename ... Args>
auto build_array(Args&&... args) -> array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main() 
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);
	// auto data2 = build_array(1, "Packt", 2.0); error. �� Ŀ���Ǵ� �ڷ����� ����

	for (auto i : data) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
