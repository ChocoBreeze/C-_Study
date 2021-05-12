// 회사 조직도 - 트리 구현
#include<iostream>
#include<queue> // queue
#include<string> // string

struct node { // binary tree 구현
	std::string position;
	node* first;
	node* second;
};

struct org_tree {
	node* root; // 회사 CEO

	static org_tree create_org_structure(const std::string& pos) { // 새로운 트리 만드는 정적 함수
		org_tree tree;
		tree.root = new node{ pos,NULL,NULL };
		return tree;
	}

	static node* find(node* root, const std::string& value) { // 특정 직책 이름에 해당하는 노드 찾아 반환
		if (root == NULL)
			return NULL;

		if (root->position == value)
			return root;

		auto firstFound = org_tree::find(root->first, value); // 왼쪽

		if (firstFound != NULL)
			return firstFound;

		return org_tree::find(root->second, value); // 오른쪽
	}

	bool addSubordinate(const std::string& manager, const std::string& subordinate) { 
		// 부하 직원(new node) 삽입 -> 성공 시 True 반환
		auto managerNode = org_tree::find(root, manager);

		if (!managerNode) {
			std::cout << manager << "을(를) 찾을 수 없습니다." << std::endl;
			return false;
		}

		if (managerNode->first && managerNode->second) { // 둘다 꽉찬 경우
			std::cout << manager << " 아래에 " << subordinate << "을(를) 추가할 수 없습니다." << std::endl;
			return false;
		}
		
		if (!managerNode->first) // 왼쪽 추가
			managerNode->first = new node{ subordinate, NULL,NULL };
		else //오른쪽 추가
			managerNode->second = new node{ subordinate, NULL,NULL };

		std::cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다. " << std::endl;

		return true;
	}
};

int main() {
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "부사장");
	tree.addSubordinate("부사장", "IT부장");
	tree.addSubordinate("부사장", "마케팅부장");
	tree.addSubordinate("IT부장", "보안팀장");
	tree.addSubordinate("IT부장", "앱개발팀장");
	tree.addSubordinate("마케팅부장", "물류팀장");
	tree.addSubordinate("마케팅부장", "홍보팀장");
	tree.addSubordinate("부사장", "재무부장");

	return 0;
}

