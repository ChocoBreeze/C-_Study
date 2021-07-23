#include<iostream>
#include<vector>
#include<algorithm>

#define DEBUG 1 // �� ���� ǥ��


//��ó���� ��� + ��ũ�� �Լ�(DEBUG�� 0�� �ƴ� ��쿡�� stderr ���)
#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;
// allSubsets�� 3D --> ���Ұ���, ���� ���ҿ����� ����, �ϳ��� ���;ȿ����� ���ҵ�.
void GetAllSubsets(vector<int> set, vector<int> subset, int index, vector<vector<vector<int>>>& allSubsets) {
	// ���� set�� ���� ������ ���
	if (index == set.size())
	{
		// �κ����� ũ�⸦ �ε����� ����Ͽ� �κ������� allSubsets�� �߰�
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	// ���Ҹ� �߰����� �ʰ� ��� ȣ��
	GetAllSubsets(set, subset, index + 1, allSubsets);

	// ���Ҹ� �κ����տ� �߰��� �� ��� ȣ��
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target) {
	// set = �Է� ����, target = �κ������� ��.
	vector<vector<vector<int>>> allSubsets(set.size() + 1); // �κ��������� ������ ���� ���� 0 ~ N�� -> N+1��

	GetAllSubsets(set, {}, 0, allSubsets);

	for (int size = 0; size <= set.size(); size++)
	{
		PRINT("�κ������� ���� ����: " << size << endl);

		for (auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}

			PRINT("} = " << sum << endl);

			if (sum == target)
				return true;
		}
	}
	return false;
}

int main()
{
	vector<int> set = { 13, 79, 45, 29 };
	int target = 1000;

	bool found = SubsetSum_BruteForce(set, target);

	if (found)
	{
		cout << "���� ���� " << target << "�� �κ������� �ֽ��ϴ�." << endl;
	}
	else
	{
		cout << "���� ���� " << target << "�� �κ������� �����ϴ�." << endl;
	}
}