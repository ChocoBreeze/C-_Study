//quick sort -- 오름차순
//std::sort()

#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<algorithm>


template<typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) { // 정렬 수행
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true) { 
		// pivot보다 큰 원소 찾기
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;
		// pivot보다 작은 원소 찾기(역순)
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		// 만약 left_iter와 right_iter가 같다면 교환할 원소가 없음을 의미합니다.
		// 그렇지 않으면 left_iter와 right_iter가 가리키는 원소를 서로 교환합니다.
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}
	
	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter; // 오른쪽 부분 배열 시작 원소 가리키는 곳 반환
}

template <typename T>
void partial_quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last,
	size_t k)
{
	// 벡터에 하나 이상의 원소가 남아 있는 경우
	if (std::distance(begin, last) >= 1)
	{
		// 분할 연산을 수행
		auto partition_iter = partition<T>(begin, last);

		// 분할 연산에 의해 생성된 두 벡터를 재귀적으로 정렬
		partial_quick_sort<T>(begin, partition_iter - 1, k);

		// 만약 마지막 피벗 위치가 k보다 작으면 오른쪽 부분 벡터도 정렬
		if (std::distance(begin, partition_iter) < k)
			partial_quick_sort<T>(partition_iter, last, k);
	}
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last) {
	// 만약 벡터에 하나 이상의 원소가 있다면
	if (std::distance(begin, last) >= 1)
	{
		// 분할 작업을 수행
		auto partition_iter = partition<T>(begin, last);

		// 분할 작업에 의해 생성된 벡터를 재귀적으로 정렬
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

template <typename T>
void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";

	std::cout << std::endl;
}

template<typename T>
auto generate_random_vector(T size) {
	std::vector<T> V;
	V.reserve(size);

	std::random_device rd;
	std::mt19937 rand(rd());

	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	for (T i = 0; i < size; i++) {
		V.push_back(uniform_dist(rand));
	}
	return std::move(V);
}

template <typename T>
void test_partial_quicksort(size_t size, size_t k)
{
	// 임의의 벡터를 생성하고, 복사본을 만들어 두 알고리즘에 각각 테스트 진행.
	auto random_vec = generate_random_vector<T>(size);
	auto random_vec_copy(random_vec);

	std::cout << "입력 벡터: " << std::endl;
	print_vector<T>(random_vec);

	// 부분 퀵 정렬 알고리즘 수행 시간 측정
	auto begin1 = std::chrono::steady_clock::now();
	partial_quick_sort<T>(random_vec.begin(), random_vec.end() - 1, k);
	auto end1 = std::chrono::steady_clock::now();
	auto diff1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);

	std::cout << std::endl;
	std::cout << "부분 퀵 정렬 수행 시간: " << diff1.count() << "us" << std::endl;

	std::cout << "(처음 " << k << "개 원소만) 부분 정렬된 벡터: ";
	print_vector<T>(random_vec);

	// 전체 퀵 정렬 알고리즘 수행 시간 측정
	auto begin2 = std::chrono::steady_clock::now();
	quick_sort<T>(random_vec_copy.begin(), random_vec_copy.end() - 1);
	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);

	std::cout << std::endl;
	std::cout << "전체 퀵 정렬 수행 시간: " << diff2.count() << "us" << std::endl;

	std::cout << "전체 정렬된 벡터: ";
	print_vector<T>(random_vec_copy);
}

void run_quick_sort_test()
{
	std::vector<int>    S1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
	std::vector<float>  S2{ 45.6f, 1.0f, 3.8f, 1.01f, 2.2f, 3.9f, 45.3f, 5.5f, 1.0f, 2.0f, 44.0f, 5.0f, 7.0f };
	std::vector<double> S3{ 45.6, 1.0, 3.8 , 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
	std::vector<char>   C{ 'b', 'z', 'a', 'e', 'f', 't', 'q', 'u', 'y' };

	std::cout << "정렬되지 않은 입력 벡터:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);
	std::cout << std::endl;

	// arr.end()는 맨 마지막 원소 다음을 가리키므로 arr.end() - 1 형태로 호출합니다.
	quick_sort<int>(S1.begin(), S1.end() - 1);
	quick_sort<float>(S2.begin(), S2.end() - 1);
	quick_sort<double>(S3.begin(), S3.end() - 1);
	quick_sort<char>(C.begin(), C.end() - 1);

	std::cout << "퀵 정렬 수행 후의 벡터:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);
	std::cout << std::endl;
}

int main()
{
	test_partial_quicksort<unsigned>(100, 10);
	return 0;
}