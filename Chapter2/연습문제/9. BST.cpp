// Binary Search Tree(BST) 구현하기
#include<iostream>

using std::cout;
using std::endl;

struct node {
	int data;
	node* left;
	node* right;
};

struct bst {
	node* root = nullptr;

	// Find
	node* find(int value) { // insert 만들기 전에 find 먼저
		return find_impl(root, value);
	}
private:
	node * find_impl(node* current, int value) {
		if (!current) { // current == null 
			cout << endl;
			return NULL;
		}

		if (current->data == value) {
			cout << value << "을(를) 찾았습니다." << endl;
			return current;
		}

		if (value < current->data) { // value 값이 현재 노드 왼쪽에 있는 경우
			cout << current->data << "에서 왼쪽으로 이동: ";
			return find_impl(current->left, value);
		}

		// value 값이 현재 노드 오른쪽에 있는 경우
		cout << current->data << "에서 오른쪽으로 이동: ";
		return find_impl(current->right, value);
	}

	// Insert
public:
	void insert(int value) {
		if (!root)
			root = new node{ value, NULL,NULL };
		else
			insert_impl(root, value);
	}
private:
	void insert_impl(node* current, int value) {
		if (value < current->data) { // Left
			if (!current->left)
				current->left = new node{ value,NULL,NULL };
			else
				insert_impl(current->left, value);
		}
		else { //Right
			if (!current->right)
				current->right = new node{ value,NULL,NULL };
			else
				insert_impl(current->right, value);
		}
	}

	// Inorder
public:
	void inorder() {
		inorder_impl(root);
	}
private:
	void inorder_impl(node* start) { // Left -> 현재 -> Right
		if (!start)
			return;
		inorder_impl(start->left);
		cout << start->data << " ";
		inorder_impl(start->right);
	}

	//Delete
public:
	node* successor(node* start) { // delete에서 successor node 찾기
		auto current = start->right;
		while (current && current->left)
			current = current->left;
		return current;
	}

	void deleteValue(int value) { //delete시 부모 노드의 자식 노드 조정
		root = delete_impl(root, value);
	}
private:
	node * delete_impl(node* start, int value) {
		if (!start)
			return NULL;

		if (value < start->data) // 이동하는 과정
			start->left = delete_impl(start->left, value);
		else if (value > start->data) // 이동하는 과정
			start->right = delete_impl(start->right, value);
		else { // 원하는 value 찾음
			if (!start->left) {// 자식 노드가 전혀 없거나 왼쪽 자식 노드만 없는 경우
				auto tmp = start->right;
				delete start;
				return tmp;
			}
			if (!start->left) {// 오른쪽 자식 노드만 없는 경우
				auto tmp = start->left;
				delete start;
				return tmp;
			}

			// 자식 노드 둘 다 있는 경우 --> successor 찾아서 data 바꿔줌
			auto succNode = successor(start);
			start->data = succNode->data;

			// 오른쪽 서브 트리에서 후속(successor)을 찾아 삭제
			start->right = delete_impl(start->right, succNode->data);
		}

		return start;
	}
};

int main() {
	bst tree;
	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);

	cout << "중위 순회: ";
	tree.inorder(); // BST의 모든 원소를 오름차순으로 출력합니다.
	cout << std::endl;

	tree.deleteValue(12);
	cout << "12를 삭제한 후 중위 순회: ";
	tree.inorder(); // BST의 모든 원소를 오름차순으로 출력합니다.
	cout << endl;

	if (tree.find(12))
		cout << "원소 12는 트리에 있습니다." << endl;
	else
		cout << "원소 12는 트리에 없습니다." << endl;
}