// 파일 시스템 자료 구조
// N-ary Tree
// 절대 경로 란 최상위 디렉토리가 반드시 포함 된 경로를 의미하며 
// 상대 경로 란 현재 디렉토리(비교 대상)를 기준으로 작성된 경로를 의미

// +알파 구현 해보기
// . = 현재 디렉토리(cwd), ..(상위 디렉터리 나타내기)
// Symbolic link지원, 파일/디렉터리 이름 지정시 '*' 문자 지원하는 기능


#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using std::string;
using std::vector;

struct n_ary_node {
	string name;
	bool is_dir;
	vector < n_ary_node*> children;
};

struct file_system {
	using node = n_ary_node;
	using node_ptr = node * ;

private:
	node_ptr root;
	node_ptr cwd; // 현재 디렉토리

public:
	file_system() {
		root = new node{ "/",true, {} }; // name, is_dir, vector
		cwd = root; // 초기 생성 -> root = 현재 디렉토리
	}

	node_ptr find(const string& path) {
		if (path[0] == '/') { //절대 경로
			return find_impl(root, path.substr(1));
		}
		else { // 상대 경로
			return find_impl(cwd, path);
		}
	}
private:
	node_ptr find_impl(node_ptr directory, const string& path) {
		if (path.empty())
			return directory;
		auto sep = path.find('/'); // 못 찾으면 npos 반환
		string current_path = sep == string::npos ? path : path.substr(0, sep);
		string rest_path = sep == string::npos ? "" : path.substr(sep + 1);
		auto found = std::find_if(directory->children.begin(), directory->children.end(),
			[&](const node_ptr child) {
			return child->name == current_path;
		});
		if (found != directory->children.end()) { // 찾아진 경우
			return find_impl(*found, rest_path);
		}
		return NULL;
	}

public:
	bool add(const std::string& path, bool is_dir) {
		if (path[0] == '/') { // 절대 경로
			return add_impl(root, path.substr(1), is_dir); // path.substr(1) : 1번 위치에서 끝까지 다 
		}
		else {
			return add_impl(cwd, path, is_dir);
		}
	}
private:
	bool add_impl(node_ptr directory, const string& path, bool is_dir) {
		if (not directory->is_dir) { // directory인지 확인
			std::cout << directory->name << "은(는) 파일입니다." << std::endl;
			return false;
		}

		auto sep = path.find('/');
		// string.find 에서 찾는 문자열이 없는 경우에 npos 반환
		if (sep == string::npos) { // path 에 '/'가 없는 경우 = 절대경로
			auto found = std::find_if(directory->children.begin(), directory->children.end(),
				[&](const node_ptr child) {
				return child->name == path;
			});
			if (found != directory->children.end()) { // 찾아진 경우
				std::cout << directory->name << "에 이미 " << path << " 이름의 파일/디렉토리가 있습니다." << std::endl;
				return false;
			}
			// 못 찾은 경우 추가
			directory->children.push_back(new node{ path, is_dir, {} });
			return true;
		}
		// path에 '/'가 있는 경우, 즉 디렉토리 이름을 포함하고 있는 경우
		std::string next_dir = path.substr(0, sep);
		auto found = std::find_if(directory->children.begin(), directory->children.end(),
			[&](const node_ptr child) {
			return child->name == next_dir && child->is_dir;
		});

		if (found != directory->children.end()) { // 해당하는 디렉토리를 찾은 경우
			return add_impl(*found, path.substr(sep + 1), is_dir);
		}

		//path 에 디렉토리 이름이 포함되어 있지만, 해당 디렉토리가 없는 경우.
		std::cout << directory->name << "에 " << next_dir << " 이름의 디렉토리가 없습니다. " << std::endl;
		return false;
	}

public:
	bool change_dir(const string& path) {
		auto found = find(path);
		if (!found && found->is_dir) {
			cwd = found;
			std::cout << "현재 디렉토리를 " << cwd->name << "로 이동합니다." << std::endl;
			return true;
		}
		std::cout << path << " 경로를 찾을 수 없습니다." << std::endl;
		return false;
	}

	void show_path(const string& path) {
		auto found = find(path);
		if (not found) {
			std::cout << path << " 경로가 존재하지 않습니다." << std::endl;
			return;
		}
		if (found->is_dir)
		{
			for (auto child : found->children)
			{
				std::cout << (child->is_dir ? "d " : "- ") << child->name << std::endl;
				// d: directory / -: file
			}
		}
		else
		{
			std::cout << "- " << found->name << std::endl;
		}
	}
};

int main()
{
	file_system fs;
	fs.add("usr", true);       // "/"에 usr 디렉토리 추가
	fs.add("etc", true);       // "/"에 etc 디렉토리 추가
	fs.add("var", true);       // "/"에 var 디렉토리 추가
	fs.add("tmp_file", false); // "/"에 tmp_file 파일 추가

	std::cout << "\"/\"의 파일/디렉토리 목록:" << std::endl;
	fs.show_path("/");        // "/"의 파일/디렉토리 목록 출력

	std::cout << std::endl;
	fs.change_dir("usr");
	fs.add("gilbut", true);
	fs.add("gilbut/Downloads", true);
	fs.add("gilbut/Downloads/newFile.cpp", false);

	std::cout << "현재 디렉토리에서 usr의 파일/디렉토리 목록: " << std::endl;
	fs.show_path("usr"); // usr 디렉토리에 파일이 없으므로 출력이 없습니다.
	std::cout << std::endl;

	std::cout << "\"/usr\"의 파일/디렉토리 목록:" << std::endl;
	fs.show_path("/usr"); //usr 디렉토리에 파일이 없으므로 출력이 없습니다.
	std::cout << std::endl;

	std::cout << "\"/usr/gilbut/Downloads\"의 파일/디렉토리 목록" << std::endl;
	fs.show_path("/usr/gilbut/Downloads");
	std::cout << std::endl;

	std::cout << "\"/gilbut/Downloads\"의 파일/디렉토리 목록" << std::endl;
	fs.show_path("/gilbut/Downloads");
	std::cout << std::endl;

	return 0;
}