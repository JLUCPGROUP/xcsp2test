//#pragma once
//#include <gecode/search.hh>
//#include <string>
//#include "BuildGModel.h"
//#include "SAC1o.h"
//#include "CPUSolver.h"
//#include <windows.h>
//#include <io.h>  
//#include "XBuilder.h"
//#include "commonline.h"
//#include <fstream>
//using namespace cp;
//using namespace Gecode;
//using namespace std;
//
//#define LOGFILE
//const string XPath = "BMPath.xml";
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
//	const string bm_res = bmp_root + "res2\\mac3bit\\" + ss.vrh_str + "\\" + argv[1] + "-" + std::to_string(tt) + ".csv";
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
//		GModel* gm = new GModel();
//		BuildGModel(hm, gm);
//		SAC1G sac1(gm);
//		Timer t;
//		const bool result = sac1.enforce();
//		const int64_t sac_time = t.elapsed();
//		SAC_times.push_back(sac_time);
//		if (result) {
//			//sat sac
//			const SearchStatistics statistics = StartSearch(gm, hm, Heuristic::DS_BI, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
//			//const SearchStatistics statistics = StartSearch(hm, Heuristic::DS_NB, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN, TimeLimit, true, sac_time);
//			//const SearchStatistics statistics = StartSearch(gm, Heuristic::DS_BI, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
//			build_times.push_back(statistics.build_time);
//			search_times.push_back(statistics.solve_time);
//			nodes.push_back(statistics.nodes);
//		}
//		else {
//			build_times.push_back(0);
//			search_times.push_back(0);
//			nodes.push_back(0);
//		}
//		delete gm;
//		delete hm;
//	}
//
//	return 0;
//}