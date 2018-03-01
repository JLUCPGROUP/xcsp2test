#pragma once
#include "QModel.h"
namespace cp {
class BacktrackingSearch {
public:
	BacktrackingSearch(HModel *h);
	~BacktrackingSearch();
	inline int new_level();
	inline int back_level();
	inline void copy_level(const int src, const int dest);
	//void clear_level(const int p);
	void insert(QVar* v);
	SearchStatistics statistics() const;
	virtual PropagationState propagate(vector<QVar*>& x_evt, const int level) = 0;

	virtual SearchStatistics solve(const Heuristic::Var varh, const Heuristic::Val valh, const int time_limit);
	QVal select_QVal(const Heuristic::Var varh, const Heuristic::Val valh, const int level);
	QVar* select_QVar(const Heuristic::Var varh, const int level);
	int select_value(QVar* v, const Heuristic::Val valh, const int level);
	vector<QVar*> vars;
	vector<QTab*> tabs;
	vector<u64> con_stamp;
	vector<u64> var_stamp;
	vector<double> con_weight;
	u64 time = 0;
	unordered_map<QVar*, vector<QTab*>> subscription;
	unordered_map<QVar*, vector<QVar* >> neighborhood;
	vector<vector<QVar*>> nei_matrix;
protected:
	vector<int> tmp_tuple_;
	vars_cir_que q_;
	vector<QVar*> get_scope(HTab* t);
	vector<QVar*> get_neighbor(QVar* v);
	const int max_arity_;
	const int max_dom_size_;
	const int max_bitDom_size_;
	const int num_vars_;
	const int num_tabs_;
	PropagationState ps_;
	SearchStatistics ss_;
	assignments_stack I_;
	int top_ = 0;
	int tmp_;
};

class MAC3 :public BacktrackingSearch {
public:
	MAC3(HModel *h);
	~MAC3(){};
	PropagationState propagate(vector<QVar*>& x_evt, const int level) override;
	bool revise(QTab* c, QVar* v, const int level);
	bool seek_support(QTab* c, QVar* v, int a, const int level);
};

class MAC3bit :public BacktrackingSearch {
public:
	MAC3bit(HModel *h);
	~MAC3bit() {};
	PropagationState propagate(vector<QVar*>& x_evt, const int level) override;
	bool revise(QTab* c, QVar* v, const int level);
	bool seek_support(QTab* c, QVar* v, int a, const int level);
protected:
	
};
}
