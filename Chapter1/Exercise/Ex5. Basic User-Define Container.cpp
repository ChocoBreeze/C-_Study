// 사용자 정의 컨테이너 만들기
#include<iostream>
#include<algorithm>

struct singly_ll_node {
	int data;
	singly_ll_node* next;
};

class singly_ll {
public:
	using node = singly_ll_node;
	using node_ptr = node * ;
	//using -> alis 별칭 
	//참고 : https://unikys.tistory.com/381

private:
	node_ptr head;


public:
	//std::forward_list의 push_front pop_front 구현
	void push_front(int val)
	{
		auto new_node = new node{ val, NULL };
		if (head != NULL) 
			new_node->next = head;
		head = new_node;
	}

	void pop_front() {
		auto first = head;
		if (head) {
			head = head->next;
			delete first;
		}
	}
	// 기본 반복자 구현
	struct singly_ll_iterator {
	private:
		node_ptr ptr;

	public:
		singly_ll_iterator(node_ptr p) : ptr(p) {}

		int& operator*() { return ptr->data; }

		node_ptr get() { return ptr; }

		singly_ll_iterator& operator++() { // 선행 증가
			ptr = ptr->next;
			return *this;
		}
		singly_ll_iterator& operator++(int) {// 후행 증가
			singly_ll_iterator result = *this;
			++(*this);
			return result;
		}

		// 두 반복자가 같은지 판단
		friend bool operator==(const singly_ll_iterator& left, const singly_ll_iterator& right) {
			return left.ptr == right.ptr;
		}
		friend bool operator!=(const singly_ll_iterator& left, const singly_ll_iterator& right) {
			return left.ptr != right.ptr;
		}
	};
	//함수 선언 뒤(body 직전)에 "const" 키워드를 삽입하면, 해당 함수가 속한 객체의 멤버를 변경할 수 없습니다.
	singly_ll_iterator begin() { return singly_ll_iterator(head); }
	singly_ll_iterator end() { return singly_ll_iterator(NULL); }
	singly_ll_iterator begin() const { return singly_ll_iterator(head); }
	singly_ll_iterator end() const { return singly_ll_iterator(NULL); }

	singly_ll() = default; // 기본 생성자 
	//깊은 복사 - 복사 생성자
	singly_ll(const singly_ll& other) : head(NULL) {
		if (other.head) {
			head = new node{ 0,NULL };
			auto cur = head;
			auto it = other.begin();
			while (true) {
				cur->data = *it;

				auto tmp = it;
				++tmp;
				if (tmp == other.end())
					break;

				cur->next = new node{ 0, NULL };
				cur = cur->next;
				it = tmp;
			}
		}
	}
	//초기화 리스트 initializer_list이용 {}로 만드는 값들
	singly_ll(const std::initializer_list<int>& ilist) : head(NULL) {
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
			push_front(*it);
	}
};
int main()
{
	using std::cout;
	using std::endl;
	singly_ll sll = { 1,2,3 };
	sll.push_front(0);

	cout << "첫 번째 리스트: ";
	for (auto i : sll) {
		std::cout << i << " ";
	}
	cout << endl;

	auto sll2 = sll;
	sll2.push_front(-1);
	cout << "첫 번째 리스트를 복사한 후, 맨 앞에 -1을 추가: ";
	for (auto i : sll2) {
		cout << i << ' ';
	}
	cout << endl;
	cout << "깊은 복사 후 첫 번째 리스트: ";

	for (auto i : sll) {
		std::cout << i << " ";
	}
	cout << endl;
	return 0;
}
