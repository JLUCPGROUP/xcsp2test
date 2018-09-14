#include "commonline.h"

int main() {
	vector<string> files;
	auto path = R"(E:\Projects\benchmarks\)";
	getFoldersAll(path, files);
	for (auto f : files) {
		cout << f << endl;
	}
}