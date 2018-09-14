#include "commonline.h"

int main() {
	vector<string> files;
	auto path = "E:\Projects\benchmarks";
	getFilesAll(path, files);
	for (auto f : files) {
		cout << f << endl;
	}
}