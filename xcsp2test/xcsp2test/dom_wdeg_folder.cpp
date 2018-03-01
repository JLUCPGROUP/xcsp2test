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
//#include <io.h>  
//#include <fstream>
//using namespace cp;
//using namespace std;
//
//typedef unsigned long long u64;
//#define LOGFILE
//const string XPath = "BMPath.xml";
//const int64_t TimeLimit = 1800000;
//const string bmp_root = "E:\\Projects\\benchmarks\\";
//const string bmp_ext = ".xml";
//void getFilesAll(string path, vector<string>& files);
//bool getScheme(char ** argv, SearchScheme& ss);
//
//int main(const int argc, char ** argv) {
//
//	if (argc <= 2) {
//		cout << "no argument" << endl;
//		return 0;
//	}
//	SearchScheme ss;
//	const bool no_error = getScheme(argv, ss);
//	if (!no_error) {
//		cout << "error" << endl;
//		return 0;
//	}
//
//#ifdef LOGFILE
//	ofstream lofi;
//	const string bm_res = bmp_root + "res\\MAC\\" + argv[1] + "-" + ss.ds_str + "-" + ss.vrh_str + ".txt";
//	lofi.open(bm_res, ios::out | ios::app);
//	cout << bm_res << endl;
//	if (!lofi.is_open())
//		return 0;
//#endif
//
//	vector<string> files;
//	getFilesAll(bmp_root + argv[1], files);
//	vector<int64_t> positive;
//	vector<int64_t> negative;
//	vector<int64_t> solve_time;
//	positive.reserve(files.size());
//	negative.reserve(files.size());
//	solve_time.reserve(files.size());
//	double all_time = 0;
//	double all_nodes = 0;
//	for (const auto f : files) {
//		cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		Network* n = new Network(hm);
//		MAC mac(n, AC_3bit, ss.vrh, Heuristic::VLH_MIN);
//		const SearchStatistics statistics = mac.enforce(TimeLimit);
//		solve_time.push_back(statistics.solve_time);
//		positive.push_back(statistics.num_positive);
//		negative.push_back(statistics.num_negative);
//		vector<int> solution = mac.I.solution();
//		bool conflict = false;
//		if (!statistics.time_out)
//			conflict = hm->solution_check(solution).empty();
//
//		delete hm;
//		delete n;
//#ifdef LOGFILE
//		lofi << f << endl;
//		if (solution.empty() && !statistics.time_out) {
//			lofi << "so solution!!!!!!!" << endl;
//		}
//		else if (conflict) {
//			lofi << "**************error***************" << endl;
//		}
//		else if (statistics.time_out) {
//			lofi << "time out!!" << endl;
//		}
//
//		if (!solution.empty() && !statistics.time_out) {
//			for (size_t i = 0; i < solution.size(); i++) {
//				lofi << hm->vars[i]->anti_map[solution[i]] << " ";
//			}
//			lofi << endl;
//		}
//#endif
//	}
//
//	cout << "---------------time---------------" << endl;
//	for (auto i : solve_time) {
//		cout << i << endl;
//		all_time += i;
//	}
//	cout << "---------------positive---------------" << endl;
//	for (auto i : positive) {
//		cout << i << endl;
//		all_nodes += i;
//	}
//#ifdef LOGFILE
//	lofi << "----------------" << argv[1] << "--------------------" << endl;
//	lofi << ss.ds_str << " " << ss.vrh_str << endl;
//	lofi << "---------------time---------------" << endl;
//	for (auto i : solve_time) {
//		lofi << i << endl;
//
//	}
//	lofi << "---------------positive---------------" << endl;
//	for (auto i : positive) {
//		lofi << i << endl;
//	}
//	lofi << "---------------summary---------------" << endl;
//	lofi << "file :" << argv[1] << " branch = " << ss.ds_str << " heu = " << ss.vrh_str << endl;
//	lofi << "avg time = " << all_time / files.size() << " s |" << all_time / files.size() / 1000 << " ms." << endl;
//	lofi << "avg node = " << all_nodes / files.size() << "|" << all_nodes / files.size() / 1000000 << "M." << endl;
//	lofi << "time out = " << count_if(solve_time.begin(), solve_time.end(), [](int x) {return x > TimeLimit; }) << endl;
//	lofi << "---------------end---------------" << endl;
//	lofi.close();
//#endif
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
//
//bool getScheme(char ** argv, SearchScheme& ss) {
//	ss.ds_str = argv[2];
//	ss.vrh_str = argv[3];
//	//ss.vlh_str = argv[4];
//
//	if (ss.ds_str == "2") {
//		ss.ds = Heuristic::DS_BI;
//	}
//	else if (ss.ds_str == "n") {
//		ss.ds = Heuristic::DS_NB;
//	}
//	else {
//		return false;
//	}
//
//	if (ss.vrh_str == "d") {
//		ss.vrh = Heuristic::VRH_DOM_MIN;
//	}
//	else if (ss.vrh_str == "dg") {
//		ss.vrh = Heuristic::VRH_DOM_DEG_MIN;
//	}
//	else if (ss.vrh_str == "wd") {
//		ss.vrh = Heuristic::VRH_DOM_WDEG_MIN;
//	}
//	else {
//		return false;
//	}
//
//	return true;
//}