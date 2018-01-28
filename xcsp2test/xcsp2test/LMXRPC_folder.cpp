﻿//#pragma once
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
//	vector<int64_t> positive;
//	vector<int64_t> negative;
//	vector<int64_t> solve_time;
//	positive.reserve(files.size());
//	negative.reserve(files.size());
//	solve_time.reserve(files.size());
//
//	for (const auto f : files) {
//		cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		Network* n = new Network(hm);
//
//		MAC mac(n, CA_LMRPC_BIT, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN);
//		const SearchStatistics statistics = mac.enforce(TimeLimit);
//		solve_time.push_back(statistics.solve_time);
//		positive.push_back(statistics.num_positive);
//		negative.push_back(statistics.num_negative);
//
//		delete hm;
//		delete n;
//	}
//
//	cout << "---------------time---------------" << endl;
//	for (auto i : solve_time)
//		cout << i << endl;
//	cout << "---------------positive---------------" << endl;
//	for (auto i : positive)
//		cout << i << endl;
//	cout << "---------------negative---------------" << endl;
//	for (auto i : negative)
//		cout << i << endl;
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