#include<iostream>
#include<vector>
#include<array>
#include<sstream> // to_string
#include<algorithm> // ?
#include<random> // default_random_engine
#include<chrono> // time
#include<string> // 추가

struct card {
	int number;

	enum suit {
		HEART,
		SPADE,
		CLUB,
		DIAMOND
	}suit;

	std::string to_string() const {
		std::ostringstream os;
		
		if (number > 0 && number <= 10)
			os << number;
		else {
			switch (number) {
			case 1:
				os << "Ace";
				break;
			case 11:
				os << "Jack";
				break;
			case 12:
				os << "Queen";
				break;
			case 13:
				os << "King";
				break;
			default:
				return "Invalid Card";
			}
		}

		os << "of";
		switch(suit) {
		case HEART:
			os << "hearts";
			break;
		case SPADE:
			os << "spades";
			break;
		case CLUB:
			os << "clubs";
			break;
		case DIAMOND:
			os << "diamondss";
			break;
		}
		return os.str();
	}
};

struct game {
	std::array<card, 52> deck;
	std::vector<card> p1, p2, p3, p4;

	void buildDeck() {
		for (int i = 0; i < 13; i++) {
			deck[i] = card{ i + 1,card::HEART };
			deck[i + 13] = card{ i + 1,card::SPADE };
			deck[i + 26] = card{ i + 1,card::CLUB };
			deck[i + 39] = card{ i + 1,card::DIAMOND };
		}
	}

	void dealCards() {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
		//기존 C에서는 srand와 rand이용
		//C++에서는 seed + std::default_random_engine
		// https://goguri.tistory.com/1399 참고
		p1 = { deck.begin(),deck.begin() + 13 };
		p2 = { deck.begin() + 13,deck.begin() + 26 };
		p3 = { deck.begin() + 26,deck.begin() + 39 };
		p4 = { deck.begin() + 39,deck.end() };
	}

	bool compareAndRemove(std::vector<card>& p1, std::vector<card>&p2) {
		if (p1.back().number == p2.back().number) {
			p1.pop_back();
			p2.pop_back();
			return true;
		}
		return false;
	}

	void playOneRound() {
		if (compareAndRemove(p1, p2)) {
			compareAndRemove(p3, p4);
			return;
		}
		else if (compareAndRemove(p1, p3)) {
			compareAndRemove(p2, p4);
			return;
		}
		else if (compareAndRemove(p1, p4)) {
			compareAndRemove(p2, p3);
			return;
		}
		else if (compareAndRemove(p2, p3)) {
			return;
		}
		else if (compareAndRemove(p2, p4)) {
			return;
		}
		else if (compareAndRemove(p3, p4)) {
			return;
		}

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(p1.begin(), p1.end(), std::default_random_engine(seed));
		std::shuffle(p2.begin(), p2.end(), std::default_random_engine(seed));
		std::shuffle(p3.begin(), p3.end(), std::default_random_engine(seed));
		std::shuffle(p4.begin(), p4.end(), std::default_random_engine(seed));
	}

	bool isGameComplete() const {
		return p1.empty() || p2.empty() || p3.empty() || p4.empty();
	}

	void playGame() {
		int count=0;
		while (not isGameComplete()) { // ? 이것도 되는지 몰랐다..
			std::cout << count << "번째 턴 수행 중" << std::endl; //추가
			playOneRound();
			// 5줄 추가
			std::cout << "p1의 카드 수 : " << p1.size() << std::endl;
			std::cout << "p2의 카드 수 : " << p2.size() << std::endl;
			std::cout << "p3의 카드 수 : " << p3.size() << std::endl;
			std::cout << "p4의 카드 수 : " << p4.size() << std::endl << std::endl;
			count++;
		}
	}

	int getWinner() const {
		if (p1.empty()) return 1;
		if (p2.empty()) return 2;
		if (p3.empty()) return 3;
		if (p4.empty()) return 4;
	}
};

int main() {
	game newGame;
	newGame.buildDeck();
	newGame.dealCards();
	newGame.playGame();
	auto winner = newGame.getWinner();
	std::cout << winner << "번 플레이어가 이겼습니다!" << std::endl;
	return 0;
}
