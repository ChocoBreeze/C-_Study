// 다양한 타입의 데이터 -> 공통 타입 변환
#include<array> // 전체 원소 빠른 순회를 위해
#include<iostream>
#include<type_traits>

using std::array;
/*
auto가 값에 상응하는 타입을 추론시켜주는 키워드라면,
decaltype은 값으로부터 타입을 추출해 낼 수 있는 키워드라고 생각하면 된다.
trailing return type(후행 반환 형식) auto 반환형에서 주로 이용
*/
// 컨테이너 생성 함수 - 가변 템플릿(임의 개수의 매개변수 허용)
// common_type : Determines the common type among all types T..., that is the type all T... can be implicitly converted to.
// auto & decltype(declared type)
// std::forward 참조와 관련. 보편 참조.
template<typename ... Args>
auto build_array(Args&&... args) -> array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main() 
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);
	// auto data2 = build_array(1, "Packt", 2.0); error. 다 커버되는 자료형이 없음

	for (auto i : data) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
