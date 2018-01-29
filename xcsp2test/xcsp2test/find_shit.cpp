//#pragma once
//#include <sstream>
//#include <string>
//#include "Timer.h"
//#include <string>
//#include <windows.h>
//#include <io.h>  
//#include <string>
//#include <iostream>
//#include "XModel.h"
//#include "XBuilder.h"
//#include "../CCSolver/Network.h"
//#include "../CCSolver/Solver.h"
//using namespace cp;
//using namespace std;
//
//typedef unsigned long long u64;
//
//const string XPath = "BMPath.xml";
//const int64_t TimeLimit = 1800000;
//const string bmp_root = "E:\\Projects\\benchmarks\\";
//const string bmp_ext = ".xml";
//void getFilesAll(string path, vector<string>& files);
//
//
//int main(const int argc, char ** argv) {
//
//	if (argc <= 1) {
//		cout << "no argument" << endl;
//		return 0;
//	}
//
//	vector<string> files;
//	getFilesAll(bmp_root + argv[1], files);
//	vector<string> shit_files;
//
//	for (const auto f : files) {
//		//cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		if (hm->have_same_scope()) {
//			shit_files.push_back(f);
//		}
//		delete hm;
//	}
//
//	cout << "----------------summary----------------" << endl;
//	cout << "test files: " << files.size() << ", have {" << shit_files.size() << "} shit files! Here are: " << endl;
//	for (const auto f : shit_files) {
//		cout << f << endl;
//	}
//
//	return 0;
//}
//
//void getFilesAll(const string path, vector<string>& files) {
//	//文件句柄 
//	intptr_t  h_file = 0;
//	//文件信息 
//	struct _finddata_t fileinfo;
//	string p;
//	if ((h_file = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
//		do {
//			if ((fileinfo.attrib & _A_SUBDIR)) {
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//					getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
//			}
//			else
//				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//		} while (_findnext(h_file, &fileinfo) == 0);
//		_findclose(h_file);
//	}
//}
