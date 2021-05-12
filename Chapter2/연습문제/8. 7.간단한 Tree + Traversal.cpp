// ȸ�� ������ - Ʈ�� ���� + Traversal ����
#include<iostream>
#include<queue> // queue -> levelOrder�� �̿�
#include<string> // string

struct node { // binary tree ����
	std::string position;
	node* first;
	node* second;
};

struct org_tree {
	node* root; // ȸ�� CEO

	static org_tree create_org_structure(const std::string& pos) { // ���ο� Ʈ�� ����� ���� �Լ�
		org_tree tree;
		tree.root = new node{ pos,NULL,NULL };
		return tree;
	}

	static node* find(node* root, const std::string& value) { // Ư�� ��å �̸��� �ش��ϴ� ��� ã�� ��ȯ
		if (root == NULL)
			return NULL;

		if (root->position == value)
			return root;

		auto firstFound = org_tree::find(root->first, value); // ����

		if (firstFound != NULL)
			return firstFound;

		return org_tree::find(root->second, value); // ������
	}

	static void preOrder(node* start) { // Preorder Traversal
		if (!start)
			return;

		std::cout << start->position << ", ";
		preOrder(start->first);
		preOrder(start->second);
	}

	static void inOrder(node* start) { // Inorder Traversal
		if (!start)
			return;

		inOrder(start->first);
		std::cout << start->position << ", ";
		inOrder(start->second);
	}

	static void postOrder(node* start) { // Postorder Traversal
		if (!start)
			return;

		inOrder(start->first);
		inOrder(start->second);
		std::cout << start->position << ", ";
	}

	static void levelOrder(node* start) {
		if (!start)
			return;
		std::queue<node*> q; 
		q.push(start);
		// ���� Level node�� ���� ���� Level node �߰�
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++) {
				auto current = q.front();
				q.pop();

				std::cout << current->position << ", ";
				if (current->first)
					q.push(current->first);
				if (current->second)
					q.push(current->second);
			}
			std::cout << std::endl;
		}
	}

	bool addSubordinate(const std::string& manager, const std::string& subordinate) { 
		// ���� ����(new node) ���� -> ���� �� True ��ȯ
		auto managerNode = org_tree::find(root, manager);

		if (!managerNode) {
			std::cout << manager << "��(��) ã�� �� �����ϴ�." << std::endl;
			return false;
		}

		if (managerNode->first && managerNode->second) { // �Ѵ� ���� ���
			std::cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��� �� �����ϴ�." << std::endl;
			return false;
		}
		
		if (!managerNode->first) // ���� �߰�
			managerNode->first = new node{ subordinate, NULL,NULL };
		else //������ �߰�
			managerNode->second = new node{ subordinate, NULL,NULL };

		std::cout << manager << " �Ʒ��� " << subordinate << "��(��) �߰��߽��ϴ�. " << std::endl;

		return true;
	}

};

int main() {
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "�λ���");
	tree.addSubordinate("�λ���", "IT����");
	tree.addSubordinate("�λ���", "�����ú���");
	tree.addSubordinate("IT����", "��������");
	tree.addSubordinate("IT����", "�۰�������");
	tree.addSubordinate("�����ú���", "��������");
	tree.addSubordinate("�����ú���", "ȫ������");
	tree.addSubordinate("�λ���", "�繫����");
	org_tree::levelOrder(tree.root);
	return 0;
}

