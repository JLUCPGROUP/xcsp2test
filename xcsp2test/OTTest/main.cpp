#pragma once
#include <string>
#include <iostream>
#include "ortools/base/join.h"
#include "ortools/constraint_solver/constraint_solveri.h"
#include "ortools/base/logging.h"
#include "ortools/util/tuple_set.h"
#include <windows.h>
#include <io.h> 
#include "XBuilder.h"
using namespace cp;
using namespace std;
using namespace operations_research;


const int64 time_limit = 1800000;
const string XPath = "BMPath.xml";
const string bmp_root = "E:\\Projects\\benchmarks\\";
const string bmp_ext = ".xml";
void getFilesAll(string path, vector<string>& files);

namespace {
class DegreeDecisionBuilder : public DecisionBuilder {
public:
	DegreeDecisionBuilder(const int size, const vector<IntVar*>& vars, const vector<int>& deg) :
		size_(size), vars_(vars), deg(deg) {
		CHECK_EQ(vars_.size(), size_);
	}
	~DegreeDecisionBuilder() {}
	vector<int> deg;
	// Select a variable with the smallest domain starting from the center
	IntVar* SelectVar(Solver* const s) const {
		IntVar* selected_var = nullptr;
		int64 id = -1;
		double min_domain_size = DBL_MAX;
		for (int64 i = 0; i < size_; ++i) {
			if (deg[i] == 0)
				return selected_var;

			IntVar* const var = vars_[i];
			//cout << i << " " << var->Size() << " " << deg[i] << endl;
			const double dom_deg = var->Size() / deg[i];
			if (!var->Bound() && dom_deg < min_domain_size) {
				selected_var = var;
				id = i;
				min_domain_size = dom_deg;
			}
		}

		if (id == -1) {
			return nullptr;
		}
		else {
			return selected_var;
		}
	}

	//  For a given variable, take the row with the least compatible columns, starting from the center
	int64 SelectValue(const IntVar* const v) const {
		CHECK_GE(v->Size(), 2);

		int64 max_incompatible_columns = -1;
		int64 selected_value = -1;

		const int64 vmin = v->Min();
		const int64 vmax = v->Max();
		const int64 v_middle = (vmin + vmax) / 2;

		for (int64 i = vmin; i <= vmax; i++) {
			if (v->Contains(i)) {
				selected_value = i;
			}
		}

		CHECK_NE(selected_value, -1);

		return selected_value;
	}

	Decision* Next(Solver* const s) override {
		IntVar* const var = SelectVar(s);
		if (nullptr != var) {
			const int64 value = SelectValue(var);
			return s->MakeAssignVariableValue(var, value);
		}

		return nullptr;
	}

private:
	const int size_;
	const vector<IntVar*> vars_;

}; //  class DegreeDecisionBuilder
}  // namespace

DecisionBuilder* MakeNQueensDecisionBuilder(Solver* const s, const int size, const vector<IntVar*>& vars, vector<int>& deg) {
	return s->RevAlloc(new DegreeDecisionBuilder(size, vars, deg));
}

class MySearchMonitor : public SearchMonitor {
public:
	explicit MySearchMonitor(Solver* s)
		: SearchMonitor(s) {}

	void ApplyDecision(Decision * const d) override {
		++p_;
	}

	void RefuteDecision(Decision* const d) override {
		++n_;
	}
	int64 positives() const {
		return p_;
	}
	int64 negatives()const {
		return n_;
	}
private:

	int64 n_ = 0;
	int64 p_ = 0;
};

int main(const int argc, char ** argv) {
	XBuilder builder(XPath, XRT_BM_PATH);
	HModel* hm = new HModel();
	builder.GenerateHModel(hm);

	Solver s("CPSimple");
	vector<IntVar*> vars(hm->vars.size());
	vector<int> deg(vars.size());

	for (auto v : hm->vars) {
		vars[v->id] = s.MakeIntVar(v->vals, v->name);
		deg[v->id] = hm->subscriptions[v].size();
	}

	for (auto t : hm->tabs) {
		vector<IntVar*> vs;
		for (auto v : t->scope)
			vs.push_back(vars[v->id]);
		IntTupleSet ts(t->scope.size());
		ts.InsertAll(t->tuples);
		s.AddConstraint(s.MakeAllowedAssignments(vs, ts));
		ts.Clear();
	}

	//DecisionBuilder* db = MakeNQueensDecisionBuilder(&s, vars.size(), vars, deg);
	DecisionBuilder* const db = s.MakePhase(vars, Solver::CHOOSE_MIN_SIZE, Solver::ASSIGN_MIN_VALUE);
	SearchLimit* limit = s.MakeTimeLimit(time_limit);
	MySearchMonitor * const sm = new MySearchMonitor(&s);
	s.NewSearch(db, limit, sm);
	s.NextSolution();
	if (s.NextSolution()) {
		for (auto v : vars)
			cout << v->index() << " = " << v->Value() << " ";
		cout << endl;
		cout << "solve time = " << s.wall_time() << " || #nodes = " << sm->positives() << " || #brs = " << s.branches() << endl;
	}
	else {
		const auto time = s.wall_time();
		if (time > s.GetTime(limit))
			cout << "time out!!" << endl;
		cout << "no solution! || time =  " << s.wall_time() << " || #nodes = " << sm->positives() << " || #brs = " << s.branches() << endl;
	}

	s.EndSearch();

	delete sm;
	delete hm;

	return 0;
};