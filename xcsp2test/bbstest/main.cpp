//#pragma once
//#include <gecode/search.hh>
//#include <gecode/driver.hh>
//#include <sstream>
//#include <fstream>
//#include <string>
//#include "BuildGModel.h"
//#include "Timer.h"
//#include "SAC1o.h"
//#include "CPUSolver.h"
//#include "XBuilder.h"
//#include "GModel.h"
//#include "../CCSolver/Network.h"
//using namespace cp;
//using namespace Gecode;
//using namespace std;
////#define LOGFILE
//
//const int TimeLimit = 100000;
//const string X_PATH = "BMPath.xml";
//
//int main() {
//	XBuilder builder(X_PATH, XRT_BM_PATH);
//	HModel* hm = new HModel();
//	builder.GenerateHModel(hm);
//	//GModel* gm = new GModel();
//	//BuildGModel(hm, gm);
//	Network *n = new Network(hm);
//	//GModel* dgm = static_cast<GModel*>(gm->clone());
//	//Search::TimeStop ts(2000);
//	//Search::Options options;
//	//options.stop = &ts;
//	//branch(*dgm, dgm->vs, INT_VAR_SIZE_MIN(), INT_VALUES_MIN());
//	//DFS<GModel> ee(dgm, options);
//	//delete dgm;
//	//int find = -1;
//	//Timer t0;
//	//if (GModel* ss = ee.next()) {
//	//	ss->print();
//	//	find = 1;
//	//	cout << "nodes = " << ee.statistics().node << endl;
//	//	delete ss;
//	//}
//	//else 
//	//	find = 0;
//	//const int64_t gecode_solve_time = t0.elapsed();
//	//cout << "---------------gecode solving---------------" << endl;
//	//cout << "Gecode solve time = " << gecode_solve_time << endl;
//
//
//	//SAC1G sac1(gm);
//	//Timer t;
//	//const bool result = sac1.enforce();
//	//const int64_t sac_time = t.elapsed();
//
//	//Timer t;
//	//const SpaceStatus ss = gm->status();
//	//const bool result = (ss != SS_FAILED);
//	//const int64_t sac_time = t.elapsed();
//	//SAC3 sac(n, AC_3bit, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//	SAC1 sac(n, AC_3bit);
//	Timer t0;
//	auto result = sac.enforce(n->vars, 0);
//	auto sac_time = t0.elapsed();
//	Timer t1;
//	if (!result) {
//		cout << "UNSAC || SAC time = " << sac_time << endl;
//		cout << "--------------------end---------------------" << endl;
//		delete hm;
//		return 0;
//	}
//
//	cout << "------------------modeling------------------" << endl;
//	//const SearchStatistics statistics = StartSearch(gm, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
//	const SearchStatistics statistics = StartSearch(n, hm, Heuristic::DS_BI, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
//	//const SearchStatistics statistics = StartSearch(gm, Heuristic::VRH_DOM_DEG_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
//	//const SearchStatistics statistics = StartSearch(gm, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
//	const string  slv_str = (statistics.num_sol > 0) ? "SAT!!" : "UNSAT";
//	delete hm;
//	//delete gm;
//	cout << "SAC time = " << sac_time << "|| Build time = " << statistics.build_time << endl;
//	cout << "------------------solving-------------------" << endl;
//	cout << slv_str << "|| Solve time = " << statistics.solve_time << "|| nodes = " << statistics.nodes << endl;
//	cout << "------------------sleeping------------------" << endl;
//
//	return 0;
//}
//
