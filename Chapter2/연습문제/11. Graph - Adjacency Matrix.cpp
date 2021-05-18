// 그래프 - adjacency matrix
#include<iostream>
#include<vector>

enum class city : int {
	MOSCOW,
	LONDON,
	SEOUL,
	SEATTLE,
	DUBAI,
	SYDNEY
};

std::ostream& operator<<(std::ostream& os, const city c) {
	switch (c) {
	case city::LONDON:
		os << "런던";
		return os;
	case city::MOSCOW:
		os << "모스크바";
		return os;
	case city::SEOUL:
		os << "서울";
		return os;
	case city::SEATTLE:
		os << "시애틀";
		return os;
	case city::DUBAI:
		os << "두바이";
		return os;
	case city::SYDNEY:
		os << "시드니";
		return os;
	default:
		return os;
	}
}

struct graph { // 실제 데이터를 저장할 graph 구조체
	std::vector<std::vector<int>> data;

	graph(int n) {
		data.reserve(n); // 공간 예약 
		std::vector<int> row(n);
		std::fill(row.begin(), row.end(), -1); // 전부 다 -1로 채움

		for (int i = 0; i < n; i++) {
			data.push_back(row); // 2차원 배열 할당
		}
	}

	void addEdge(const city c1, const city c2, int dis) { // edge 추가
		std::cout << "에지 추가: " << c1 << "-" << c2 << "=" << dis << std::endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = dis;
		data[n2][n1] = dis;
	}
	//https://blockdmask.tistory.com/236 static_cast 참고
	void removeEdge(const city c1, const city c2) { // edge 제거
		std::cout << "에지 삭제: " << c1 << "-" << c2 << std::endl;

		auto n1 = static_cast<int>(c1);
		auto n2 = static_cast<int>(c2);
		data[n1][n2] = -1;
		data[n2][n1] = -1;
	}
};

int main() {
	graph g(6);
	g.addEdge(city::LONDON, city::MOSCOW, 2500);
	g.addEdge(city::LONDON, city::SEOUL, 9000);
	g.addEdge(city::LONDON, city::DUBAI, 5500);
	g.addEdge(city::SEOUL, city::MOSCOW, 6600);
	g.addEdge(city::SEOUL, city::SEATTLE, 8000);
	g.addEdge(city::SEOUL, city::DUBAI, 7000);
	g.addEdge(city::SEOUL, city::SYDNEY, 8000);
	g.addEdge(city::SEATTLE, city::MOSCOW, 8400);
	g.addEdge(city::SEATTLE, city::SYDNEY, 12000);
	g.addEdge(city::DUBAI, city::SYDNEY, 1200);

	g.addEdge(city::SEATTLE, city::LONDON, 8000);
	g.removeEdge(city::SEATTLE, city::LONDON);

	return 0;
}