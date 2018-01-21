#include <string>
#include <iostream>
#include "XModel.h"
#include "XBuilder.h"
#include "../Solver/Network.h"
#include "../Solver/Solver.h"
using namespace std;
using namespace cp;
const string X_PATH = "BMPath.xml";

const int TimeLimit = 1800000000000;
int main() {
	XBuilder builder(X_PATH, XRT_BM_PATH);
	HModel* hm = new HModel();
	builder.GenerateHModel(hm);
	Network* n = new Network(hm);
	//hm->show();
	//AC3 ac_(n);
	//ac_.enforce(n->vars, 0);
	MAC mac(n, AC_3bit, DOM);
	const SearchStatistics statistics = mac.enforce(TimeLimit);
	cout << "time = " << statistics.solve_time << endl;
	cout << "positive = " << statistics.num_positive << endl;
	cout << "negative = " << statistics.num_negative << endl;
	delete hm;
	delete n;
	return 0;
}

