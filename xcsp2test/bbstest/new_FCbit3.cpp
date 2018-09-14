//#pragma once
//#include <gecode/search.hh>
//#include <string>
////#include "BuildGModel.h"
//#include "CPUSolver.h"
//#include <windows.h>
//#include <io.h>  
//#include "XBuilder.h"
//#include <fstream>
//#include "commonline.h"
//using namespace cp;
//using namespace std;
//
//#define LOGFILE
//const string XPath = "BMPath.xml";
//const int64_t TimeLimit = 1800000;
//const string bmp_root = "E:\\Projects\\benchmarks\\";
//const string bmp_ext = ".xml";
//
//
//int main(const int argc, char ** argv) {
//
//	if (argc <= 3) {
//		std::cout << "no argument" << endl;
//		return 0;
//	}
//	SearchScheme ss;
//	const bool no_error = getScheme(argv, ss);
//	if (!no_error) {
//		cout << "error" << endl;
//		return 0;
//	}
//	vector<string> files;
//	//getFilesAll(bmp_root + argv[1], files);
//	const auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//#ifdef LOGFILE
//	ofstream lofi;
//	const string bm_res = bmp_root + "res2\\efc\\" + ss.vrh_str + "\\" + argv[1] + "-" + std::to_string(tt) + ".csv";
//	lofi.open(bm_res, ios::out | ios::trunc);
//	cout << bm_res << endl;
//	if (!lofi.is_open())
//		return 0;
//	lofi << "files" << "," << "cpu" << "," << "#nodes" << "," << "test" << "," << "solution" << endl;
//#endif
//	getFilesAll(bmp_root + argv[1], files);
//
//	double ts = 0;
//	double tn = 0;
//	u64 to = 0;
//
//	for (const auto f : files) {
//		cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		Network *n = new Network(hm);
//
//		//SAC1 sac(n, AC_3bit);
//		//Timer t;
//		//const auto result = sac.one_pass(n->vars, 0);
//		//const int64_t sac_time = t.elapsed();
//		vector<int> solution;
//		//if (result) {
//		const SearchStatistics statistics = StartSearch(n, hm, ss.ds, ss.vrh, Heuristic::VLH_MIN, TimeLimit, false, solution, 0);
//		stringstream strs;
//		for (int a : solution) {
//			strs << a << " ";
//		}
//		string sol_str = strs.str();
//		sol_str.pop_back();
//		//const SearchStatistics statistics = StartSearch(hm, ss.ds, ss.vrh, Heuristic::VLH_MIN, TimeLimit, true, sac_time);
//		//build_times.push_back(statistics.build_time);
//		//search_times.push_back(statistics.solve_time);
//		//nodes.push_back(statistics.nodes);
//	//}
//	//else {
//	//	build_times.push_back(0);
//	//	search_times.push_back(0);
//	//	nodes.push_back(0);
//
//	//}
//#ifdef LOGFILE
//		lofi << builder.file_name() << "," << statistics.total_time << "," << statistics.nodes << "," << statistics.pass << "," << "" << endl;
//#endif
//		ts += statistics.total_time;
//		tn += statistics.nodes;
//		if (statistics.total_time > TimeLimit)
//			++to;
//
//		delete n;
//		delete hm;
//	}
//
//	const double avg_ts = ts / files.size() / 1000;
//	const double avg_tn = tn / files.size() / 1000000;
//#ifdef LOGFILE
//	lofi << avg_ts << endl;
//	lofi << avg_tn << "M" << endl;
//	lofi << to << endl;
//	lofi.close();
//#endif
//
//	return 0;
//}