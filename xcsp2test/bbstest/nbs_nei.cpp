#pragma once
#include <sstream>
#include <string>
#include "BuildGModel.h"
#include "Timer.h"
#include "CPUSolver.h"
#include "XBuilder.h"
#include "GModel.h"
#include "SAC1.h"
using namespace cp;
using namespace std;
//#define LOGFILE

const int TimeLimit = 600000;
const string X_PATH = "BMPath.xml";

int main() {
	XBuilder builder(X_PATH, XRT_BM_PATH);
	HModel* hm = new HModel();
	builder.GenerateHModel(hm);

	GModel* gm = new GModel();
	BuildGModel(hm, gm);
	//hm->show();
	//delete hm;
	SAC1 sac1(gm);
	Timer t;
	const bool result = sac1.enforce();
	const int64_t sac_time = t.elapsed();


	cout << "------------------modeling------------------" << endl;
	//const SearchStatistics statistics = StartSearch(hm, Heuristic::DS_NB, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN, TimeLimit, true, 0);
	const SearchStatistics statistics = StartSearch(gm, hm, Heuristic::DS_NB, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN, TimeLimit, false, sac_time);
	//const SearchStatistics statistics = StartSearch(hm, Heuristic::VRH_DOM_DEG_MIN, Heuristic::VLH_MIN, TimeLimit, true, 0);
	//const SearchStatistics statistics = StartSearch(hm, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN, TimeLimit, true, 0);
	const string  slv_str = (statistics.num_sol > 0) ? "SAT!!" : "UNSAT";
	delete hm;
	delete gm;
	cout << "|| Build time = " << statistics.build_time << endl;
	cout << "------------------solving-------------------" << endl;
	cout << slv_str << "|| Solve time = " << statistics.solve_time << "|| nodes = " << statistics.nodes << endl;
	cout << "------------------sleeping------------------" << endl;

	return 0;
}

