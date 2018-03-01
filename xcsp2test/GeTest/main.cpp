﻿#pragma once
#include <sstream>
#include <string>
#include "Timer.h"
#include "GModel.h"
#include "BuildGModel.h"
#include "SAC1.h"
#include "XBuilder.h"

using namespace cp;
using namespace std;
//#define LOGFILE

const int TimeLimit = 1800000;
const string X_PATH = "BMPath.xml";

int main() {
	XBuilder builder(X_PATH, XRT_BM_PATH);
	HModel* hm = new HModel();
	builder.GenerateHModel(hm);
	GModel* gm = new GModel();
	BuildGModel(hm, gm);
	//gm->status();

	//int s[2] = { 0, 0 };

	//for (auto v : gm->vs)
	//	s[0] += v.size();

	//gm->status();

	//for (auto v : gm->vs)
	//	s[1] += v.size();

	//cout << s[0] - s[1] << endl;

	Search::TimeStop ts(TimeLimit);
	Search::Options options;
	options.stop = &ts;
	//branch(*gm, gm->vs, INT_VAR_AFC_SIZE_MAX(), INT_VALUES_MIN());
	branch(*gm, gm->vs, INT_VAR_SIZE_MIN(), INT_VALUES_MIN());
	DFS<GModel> ee(gm, options);

	Timer t0;
	if (GModel* ss = ee.next()) {
		ss->print();
		//cout << "nodes = " << ee.statistics().node << endl;
		delete ss;
	}
	cout << t0.elapsed() << endl;
	cout << ee.statistics().node << endl;



	//GModel* dgm = static_cast<GModel*>(gm->clone());
	//Search::TimeStop ts(200000);
	//Search::Options options;
	//options.stop = &ts;
	//branch(*dgm, dgm->vs, INT_VAR_SIZE_MIN(), INT_VALUES_MIN());
	//DFS<GModel> ee(dgm, options);
	//delete dgm;

	//int find = -1;
	//Timer t0;
	//if (GModel* ss = ee.next()) {
	//	ss->print();
	//	find = 1;
	//	cout << "nodes = " << ee.statistics().node << endl;
	//	delete ss;
	//}
	//else
	//	find = 0;

	//const int64_t gecode_solve_time = t0.elapsed();
	//cout << "---------------gecode solving---------------" << endl;
	//cout << "Gecode solve time = " << gecode_solve_time << endl;

	//SAC1 sac1(gm);
	//Timer t;
	//const bool result = sac1.enforce();
	//const int64_t sac_time = t.elapsed();
	////gm->print();
	delete hm;
	delete gm;
	return 0;
}