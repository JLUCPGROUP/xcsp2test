//#include <string>
//#include <iostream>
//#include "XModel.h"
//#include "XBuilder.h"
//#include "../CCSolver/Network.h"
//#include "../CCSolver/Solver.h"
//using namespace std;
//using namespace cp;
//const string X_PATH = "BMPath.xml";
//
//const int TimeLimit = 1800000000000;
//int main() {
//	XBuilder builder(X_PATH, XRT_BM_PATH);
//	HModel* hm = new HModel();
//	builder.GenerateHModel(hm);
//	Network* n = new Network(hm);
//	//AC3bit ac_(n);
//	//ac_.enforce(n->vars, 0);
//	//n->vars[0]->ReduceTo(0, 0);
//	//n->vars[0]->assign(true, 0);
//	//vector<IntVar*> vs;
//	//vs.push_back(n->vars[0]);
//	//ac_.enforce(vs, 0);
//	////hm->show();
//	//n->show(0);
//	////MAC mac(n, AC_3, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//	//MAC mac(n, CA_LMRPC_BIT, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN);
//	//MAC mac(n, AC_3bit, Heuristic::VRH_DOM_WDEG_MIN, Heuristic::VLH_MIN);
//	//MAC mac(n, CA_LMRPC_BIT, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//	//MAC mac(n, AC_3bit, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//	MAC mac(n, CA_RPC3, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//	const SearchStatistics statistics = mac.enforce(TimeLimit);
//	cout << "is solution = " << mac.solution_check() << endl;
//	cout << "time = " << statistics.solve_time << endl;
//	cout << "positive = " << statistics.num_positive << endl;
//	cout << "negative = " << statistics.num_negative << endl;
//
//	//n->show(0);
//	//lMaxRPC ac(n);
//	//ac.enforce(n->vars, 0);
//	//n->show(0);
//
//	//n->show(0);
//	////SAC1 sac(n, AC_3bit);
//	//SAC3 sac(n, AC_3bit, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//	//sac.enforce(n->vars, 0);
//	//cout << sac.del() << endl;
//	//n->show(0);
//	delete hm;
//	delete n;
//	return 0;
//}
//
