// Binary Search Tree(BST) �����ϱ�
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
	node* find(int value) { // insert ����� ���� find ����
		return find_impl(root, value);
	}
private:
	node * find_impl(node* current, int value) {
		if (!current) { // current == null 
			cout << endl;
			return NULL;
		}

		if (current->data == value) {
			cout << value << "��(��) ã�ҽ��ϴ�." << endl;
			return current;
		}

		if (value < current->data) { // value ���� ���� ��� ���ʿ� �ִ� ���
			cout << current->data << "���� �������� �̵�: ";
			return find_impl(current->left, value);
		}

		// value ���� ���� ��� �����ʿ� �ִ� ���
		cout << current->data << "���� ���������� �̵�: ";
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
	void inorder_impl(node* start) { // Left -> ���� -> Right
		if (!start)
			return;
		inorder_impl(start->left);
		cout << start->data << " ";
		inorder_impl(start->right);
	}

	//Delete
public:
	node* successor(node* start) { // delete���� successor node ã��
		auto current = start->right;
		while (current && current->left)
			current = current->left;
		return current;
	}

	void deleteValue(int value) { //delete�� �θ� ����� �ڽ� ��� ����
		root = delete_impl(root, value);
	}
private:
	node * delete_impl(node* start, int value) {
		if (!start)
			return NULL;

		if (value < start->data) // �̵��ϴ� ����
			start->left = delete_impl(start->left, value);
		else if (value > start->data) // �̵��ϴ� ����
			start->right = delete_impl(start->right, value);
		else { // ���ϴ� value ã��
			if (!start->left) {// �ڽ� ��尡 ���� ���ų� ���� �ڽ� ��常 ���� ���
				auto tmp = start->right;
				delete start;
				return tmp;
			}
			if (!start->left) {// ������ �ڽ� ��常 ���� ���
				auto tmp = start->left;
				delete start;
				return tmp;
			}

			// �ڽ� ��� �� �� �ִ� ��� --> successor ã�Ƽ� data �ٲ���
			auto succNode = successor(start);
			start->data = succNode->data;

			// ������ ���� Ʈ������ �ļ�(successor)�� ã�� ����
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

	cout << "���� ��ȸ: ";
	tree.inorder(); // BST�� ��� ���Ҹ� ������������ ����մϴ�.
	cout << std::endl;

	tree.deleteValue(12);
	cout << "12�� ������ �� ���� ��ȸ: ";
	tree.inorder(); // BST�� ��� ���Ҹ� ������������ ����մϴ�.
	cout << endl;

	if (tree.find(12))
		cout << "���� 12�� Ʈ���� �ֽ��ϴ�." << endl;
	else
		cout << "���� 12�� Ʈ���� �����ϴ�." << endl;
}