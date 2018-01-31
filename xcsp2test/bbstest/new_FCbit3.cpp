////#pragma once
////#include <gecode/search.hh>
////#include <string>
//////#include "BuildGModel.h"
////#include "CPUSolver.h"
////#include <windows.h>
////#include <io.h>  
////#include "XBuilder.h"
////#include <fstream>
////using namespace cp;
////using namespace Gecode;
////using namespace std;
////
////#define LOGFILE
////const string XPath = "BMPath.xml";
////const int64_t TimeLimit = 1800000;
////const string X_PATH = "E:\\Projects\\benchmarks\\";
////const string bmp_ext = ".xml";
////void getFilesAll(string path, vector<string>& files);
////void getScheme(char ** argv, SearchScheme& ss);
////
////
////int main(const int argc, char ** argv) {
////
////	if (argc <= 3) {
////		std::cout << "no argument" << endl;
////		return 0;
////	}
////	vector<string> files;
////	getFilesAll(X_PATH + argv[1], files);
////	vector<u64> SAC_times;
////	vector<u64> build_times;
////	vector<u64> search_times;
////	vector<u64> nodes;
////
////
////	SearchScheme ss;
////	getScheme(argv, ss);
////#ifdef LOGFILE
////	ofstream lofi;
////	const string bm_res = X_PATH + "res\\fcbit3" + argv[1] + "-" + ss.ds_str + "-" + ss.vrh_str + ".txt";
////	lofi.open(bm_res, ios::out | ios::app);
////	cout << bm_res << endl;
////	if (!lofi.is_open())
////		return 0;
////#endif
////
////	for (const auto f : files) {
////		cout << f << endl;
////		XBuilder builder(f, XRT_BM);
////		HModel* hm = new HModel();
////		builder.GenerateHModel(hm);
////		Network *n = new Network(hm);
////
////		SAC1 sac(n, AC_3bit);
////		Timer t;
////		const auto result = sac.enforce(n->vars, 0);
////		const int64_t sac_time = t.elapsed();
////		SAC_times.push_back(sac_time);
////
////		if (result) {
////			const SearchStatistics statistics = StartSearch(n, hm, ss.ds, ss.vrh, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
////
////			//const SearchStatistics statistics = StartSearch(hm, ss.ds, ss.vrh, Heuristic::VLH_MIN, TimeLimit, true, sac_time);
////			build_times.push_back(statistics.build_time);
////			search_times.push_back(statistics.solve_time);
////			nodes.push_back(statistics.nodes);
////		}
////		else {
////			build_times.push_back(0);
////			search_times.push_back(0);
////			nodes.push_back(0);
////		}
////		delete n;
////		delete hm;
////	}
////	vector<uint64_t> total_time(files.size(), 0);
////	vector<uint64_t> pre_time(files.size(), 0);
////	cout << "---------------SAC_times---------------" << endl;
////	for (size_t i = 0; i < files.size(); i++) {
////		cout << SAC_times[i] << endl;
////		total_time[i] += SAC_times[i];
////		pre_time[i] += SAC_times[i];
////	}
////	cout << "---------------build_times---------------" << endl;
////	for (size_t i = 0; i < files.size(); i++) {
////		cout << build_times[i] << endl;
////		total_time[i] += build_times[i];
////		pre_time[i] += build_times[i];
////	}
////	cout << "---------------search_times---------------" << endl;
////	for (size_t i = 0; i < files.size(); i++) {
////		cout << search_times[i] << endl;
////		total_time[i] += search_times[i];
////	}
////	cout << "---------------nodes---------------" << endl;
////	for (u64 i : nodes) {
////		cout << i << endl;
////	}
////#ifdef LOGFILE
////	lofi << "----------------" << argv[1] << "--------------------" << endl;
////	lofi << ss.ds_str << " " << ss.vrh_str << endl;
////	//lofi << "---------------SAC_times---------------" << endl;
////	for (size_t i = 0; i < files.size(); i++) {
////		lofi << SAC_times[i] << endl;
////	}
////	//lofi << "---------------build_times---------------" << endl;
////	for (size_t i = 0; i < files.size(); i++) {
////		lofi << build_times[i] << endl;
////	}
////
////	//lofi << "---------------search_times---------------" << endl;
////	for (size_t i = 0; i < files.size(); i++) {
////		lofi << search_times[i] << endl;
////	}
////	lofi << "---------------nodes---------------" << endl;
////	for (u64 i : nodes)
////		lofi << i << endl;
////	lofi << "---------------summary---------------" << endl;
////	lofi << "file :" << argv[1] << " branch = " << ss.ds_str << " heu = " << ss.vrh_str << endl;
////	const double avg_totoal = accumulate(total_time.begin(), total_time.end(), 0.000000) / total_time.size() / 1000;
////	const double avg_search = accumulate(search_times.begin(), search_times.end(), 0.000000) / search_times.size() / 1000;
////	lofi << "avg time = " << avg_totoal << "(" << avg_search << ")" << endl;
////	lofi << "avg node = " << accumulate(nodes.begin(), nodes.end(), 0.000000) / total_time.size() / 1000000 << "M." << endl;
////	lofi << "time out = " << count_if(total_time.begin(), total_time.end(), [](int x) {return x > TimeLimit - 100; }) << endl;
////	lofi << "---------------end---------------" << endl;
////	lofi.close();
////#endif
////	return 0;
////}
////
////
////void getFilesAll(const string path, vector<string>& files) {
////	//文件句柄 
////	intptr_t  h_file = 0;
////	//文件信息 
////	struct _finddata_t fileinfo;
////	string p;
////	if ((h_file = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
////		do {
////			if ((fileinfo.attrib & _A_SUBDIR)) {
////				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
////					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
////					getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
////				}
////			}
////			else {
////				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
////			}
////		} while (_findnext(h_file, &fileinfo) == 0);
////		_findclose(h_file);
////	}
////}
////
////
////void getScheme(char ** argv, SearchScheme& ss) {
////	ss.ds_str = argv[2];
////	ss.vrh_str = argv[3];
////	//ss.vlh_str = argv[4];
////
////	if (ss.ds_str == "2") {
////		ss.ds = Heuristic::DS_BI;
////	}
////	else if (ss.ds_str == "n") {
////		ss.ds = Heuristic::DS_NB;
////	}
////
////	if (ss.vrh_str == "d") {
////		ss.vrh = Heuristic::VRH_DOM_MIN;
////	}
////	else if (ss.vrh_str == "dg") {
////		ss.vrh = Heuristic::VRH_DOM_DEG_MIN;
////	}
////	else if(ss.vrh_str == "wd") {
////		ss.vrh = Heuristic::VRH_DOM_WDEG_MIN;
////	}
////}
//
//
//#pragma once
//#include <gecode/search.hh>
//#include <string>
////#include "BuildGModel.h"
//#include "CPUSolver.h"
//#include <windows.h>
//#include <io.h>  
//#include "XBuilder.h"
//#include <fstream>
//using namespace cp;
//using namespace std;
//
//#define LOGFILE
//const string XPath = "BMPath.xml";
//const int64_t TimeLimit = 1800000;
//const string X_PATH = "E:\\Projects\\benchmarks\\";
//const string bmp_ext = ".xml";
//void getFilesAll(string path, vector<string>& files);
//bool getScheme(char ** argv, SearchScheme& ss);
//
//
//int main(const int argc, char ** argv) {
//
//	if (argc <= 3) {
//		std::cout << "no argument" << endl;
//		return 0;
//	}
//	vector<string> files;
//	getFilesAll(X_PATH + argv[1], files);
//	vector<u64> SAC_times;
//	vector<u64> build_times;
//	vector<u64> search_times;
//	vector<u64> nodes;
//	double all_nodes = 0;
//	double all_search_time = 0;
//	double all_time = 0;
//
//	SearchScheme ss;
//	const bool no_error = getScheme(argv, ss);
//	if (!no_error) {
//		cout << "error" << endl;
//		return 0;
//	}
//
//#ifdef LOGFILE
//	ofstream lofi;
//	const string bm_res = X_PATH + "res\\fcbit3\\" + argv[1] + "-" + ss.ds_str + "-" + ss.vrh_str + ".txt";
//	lofi.open(bm_res, ios::out | ios::app);
//	cout << bm_res << endl;
//	vector<int> solution;
//	if (!lofi.is_open())
//		return 0;
//#endif
//
//	for (const auto f : files) {
//		cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		Network *n = new Network(hm);
//
//		SAC1 sac(n, AC_3bit);
//		Timer t;
//		const auto result = sac.enforce(n->vars, 0);
//		const int64_t sac_time = t.elapsed();
//		SAC_times.push_back(sac_time);
//		SearchStatistics statistics;
//		if (result) {
//			statistics = StartSearch(n, hm, ss.ds, ss.vrh, Heuristic::VLH_MIN, TimeLimit, false, solution, sac_time);
//
//			//const SearchStatistics statistics = StartSearch(hm, ss.ds, ss.vrh, Heuristic::VLH_MIN, TimeLimit, true, sac_time);
//			build_times.push_back(statistics.build_time);
//			search_times.push_back(statistics.solve_time);
//			nodes.push_back(statistics.nodes);
//		}
//		else {
//			build_times.push_back(0);
//			search_times.push_back(0);
//			nodes.push_back(0);
//		}
//		delete n;
//		delete hm;
//
//#ifdef LOGFILE
//		lofi << f << endl;
//		if (statistics.pass) {
//			lofi << "pass!!!!!!!" << endl;
//		}
//		else {
//			lofi << "**************error***************" << endl;
//		}
//
//		for (auto i : solution) {
//			lofi << i << " ";
//		}
//		lofi << endl;
//#endif
//	}
//	vector<uint64_t> total_time(files.size(), 0);
//	cout << "---------------SAC_times---------------" << endl;
//	for (size_t i = 0; i < files.size(); i++) {
//		cout << SAC_times[i] << endl;
//		total_time[i] += SAC_times[i];
//		all_time += SAC_times[i];
//	}
//	cout << "---------------build_times---------------" << endl;
//	for (size_t i = 0; i < files.size(); i++) {
//		cout << build_times[i] << endl;
//		total_time[i] += build_times[i];
//		all_time += build_times[i];
//	}
//	cout << "---------------search_times---------------" << endl;
//	for (size_t i = 0; i < files.size(); i++) {
//		cout << search_times[i] << endl;
//		total_time[i] += search_times[i];
//		all_time += search_times[i];
//		all_search_time += search_times[i];
//	}
//	cout << "---------------nodes---------------" << endl;
//	for (u64 i : nodes) {
//		cout << i << endl;
//		all_nodes += i;
//	}
//#ifdef LOGFILE
//	lofi << "----------------" << argv[1] << "--------------------" << endl;
//	lofi << ss.ds_str << " " << ss.vrh_str << endl;
//	lofi << "---------------SAC_times---------------" << endl;
//	for (size_t i = 0; i < files.size(); i++) {
//		lofi << SAC_times[i] << endl;
//	}
//	lofi << "---------------build_times---------------" << endl;
//	for (size_t i = 0; i < files.size(); i++) {
//		lofi << build_times[i] << endl;
//	}
//	lofi << "---------------search_times---------------" << endl;
//	for (size_t i = 0; i < files.size(); i++) {
//		lofi << search_times[i] << endl;
//	}
//	lofi << "---------------nodes---------------" << endl;
//	for (u64 i : nodes)
//		lofi << i << endl;
//	lofi << "---------------summary---------------" << endl;
//	lofi << "file :" << argv[1] << " branch = " << ss.ds_str << " heu = " << ss.vrh_str << endl;
//	lofi << "avg time = " << all_time / files.size() << "(" << all_search_time / files.size() << ") |" << all_time / files.size() / 1000 << "(" << all_search_time / files.size() / 1000 << ")" << endl;
//	lofi << "avg node = " << all_nodes / files.size() << "|" << all_nodes / files.size() / 1000000 << "M." << endl;
//	lofi << "time out = " << count_if(total_time.begin(), total_time.end(), [](int x) {return x > TimeLimit - 1; }) << endl;
//	lofi << "---------------end---------------" << endl;
//	lofi.close();
//#endif
//	return 0;
//}
//
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
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
//					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
//					getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
//				}
//			}
//			else {
//				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//			}
//		} while (_findnext(h_file, &fileinfo) == 0);
//		_findclose(h_file);
//	}
//}
//
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