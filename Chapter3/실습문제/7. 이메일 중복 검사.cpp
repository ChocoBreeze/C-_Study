// �̸��� �ּ� �ߺ� �˻� -- bloom filter �̿�

#include<iostream>
#include<string>
#include<vector>

#include<openssl/md5.h> // ��ġ �ʿ�

class BloomFilter {
	int nHashes;
	std::vector<bool> bits;

	static constexpr int hashSize = 128 / 8;

	unsigned char hashValue[hashSize];

public:
	BloomFilter(int size, int hashes) : bits(size), nHashes(hashes) {
		if (nHashes > hashSize) {
			throw("�ؽ� �Լ� ������ �ʹ� �����ϴ�.");
		}

		if (size > 255) {
			throw("��� ���� ũ�Ⱑ 255���� Ŭ �� �����ϴ�.");
		}
	}
	void hash(const std::string& key) {
		MD5(reinterpret_cast<const unsigned char*>(key.data()), key.length(), hashValue);
	}

	void add(const std::string& key) {
		hash(key);
		for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++) {
			bits[*it%bits.size()] = true;
		}

		std::cout << "�ҷ� ���Ϳ� �߰�: " << key << std::endl;
	}
	bool mayContain(const std::string& key) {
		hash(key);
		for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++) {
			if (!bits[*it% bits.size()]) {
				std::cout << key << " : ����� �� �ִ� �̸����Դϴ�." << std::endl;
				return false;
			}
		}

		std::cout << key << ": �̹� ��� ���Դϴ�." << std::endl;
		return true;
	}
};

int main() {
	BloomFilter bloom(128, 5);

	bloom.add("abc@gilbut.com");
	bloom.add("xyz@gilbut.com");

	bloom.mayContain("abc");
	bloom.mayContain("xyz@gilbut.com");
	bloom.mayContain("xyz");

	bloom.add("abcd@gilbut.com");
	bloom.add("ab@gilbut.com");

	bloom.mayContain("abcd");
	bloom.mayContain("ab@gilbut.com");
	return 0;
}