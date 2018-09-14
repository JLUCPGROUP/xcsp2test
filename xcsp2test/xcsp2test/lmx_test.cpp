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
//#include "commonline.h"
////#include <zmmintrin.h>
//using namespace cp;
//using namespace std;
//
//typedef unsigned long long u64;
//#define LOGFILE
//const string X_PATH = "BMPath.xml";
//const int64_t TimeLimit = 1800000;
//const string bmp_root = R"(E:\Projects\benchmarks\)";
//const string bmp_ext = ".xml";
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
//	auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//#ifdef LOGFILE
//	ofstream lofi;
//	const string bm_res = bmp_root + "res2\\lmx\\" + ss.vrh_str + "\\" + argv[1] + "-" + std::to_string(tt) + ".csv";
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
//	for (const auto f : files) {
//		cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		Network* n = new Network(hm);
//		MAC mac(n, CA_LMRPC_BIT, ss.vrh, Heuristic::VLH_MIN);
//		const SearchStatistics statistics = mac.enforce(TimeLimit);
//		//solve_time.push_back(statistics.solve_time);
//		//positive.push_back(statistics.num_positive);
//		//negative.push_back(statistics.num_negative);
//		const bool test = mac.solution_check();
//#ifdef LOGFILE
//		lofi << builder.file_name() << "," << statistics.solve_time << "," << statistics.num_positive << "," << test << "," << mac.sol_str << endl;
//#endif
//
//		ts += statistics.solve_time;
//		tn += statistics.num_positive;
//		if (statistics.solve_time > TimeLimit)
//			++to;
//
//		delete hm;
//		delete n;
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
//	return 0;
//}