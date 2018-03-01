#include <unordered_set>
#include "Timer.h"
#include "BacktrackingSearch.h"
namespace  cp {
int BacktrackingSearch::new_level() {
	++top_;
	for (auto v : vars)
		v->new_level(top_ - 1, top_);
	return top_;
}

int BacktrackingSearch::back_level() {
	--top_;
	//for (auto v : vars)
	//	v->back_to(top_ + 1, top_);
	return top_;
}

void BacktrackingSearch::copy_level(const int src, const int dest) {
	if (src == dest)
		return;
	for (auto v : vars)
		v->copy_level(src, dest);
}

vector<QVar*> BacktrackingSearch::get_neighbor(QVar* v) {
	unordered_set<QVar*> vs;
	for (auto c : subscription[v])
		for (auto x : c->scope)
			if (x != v)
				vs.insert(x);

	return vector<QVar*>(vs.begin(), vs.end());
}

BacktrackingSearch::BacktrackingSearch(HModel* h) :
	max_arity_(h->max_arity()),
	max_dom_size_(h->max_domain_size()),
	max_bitDom_size_(ceil(float(h->max_domain_size()) / BITSIZE)),
	num_vars_(h->vars.size()),
	num_tabs_(h->tabs.size()),
	top_(0),
	tmp_(h->vars.size() + 1) {

	vars.reserve(num_vars_);
	tabs.reserve(num_tabs_);
	nei_matrix.resize(num_vars_);

	for (auto hv : h->vars) {
		QVar *v = new QVar(hv);
		v->runtime(num_vars_);
		vars.push_back(v);
	}

	for (auto ht : h->tabs) {
		QTab *t = new QTab(ht, get_scope(ht));
		tabs.push_back(t);
	}

	for (auto t : tabs)
		for (auto v : t->scope)
			subscription[v].push_back(t);

	for (auto v : vars) {
		neighborhood[v] = get_neighbor(v);
		nei_matrix[v->id] = neighborhood[v];
	}

	con_stamp.resize(num_tabs_, 0);
	var_stamp.resize(num_tabs_, 0);
	con_weight.resize(num_tabs_, 0);
	q_.initial(num_vars_);
	tmp_tuple_.resize(max_arity_);
	Exclude(tmp_tuple_);

	I_.initial(h);
}

BacktrackingSearch::~BacktrackingSearch() {
	for (auto v : vars)
		delete v;
	for (auto t : tabs)
		delete t;
}

vector<QVar*> BacktrackingSearch::get_scope(HTab* t) {
	vector<QVar*> tt(t->scope.size());
	for (int i = 0; i < t->scope.size(); ++i)
		tt[i] = vars[t->scope[i]->id];
	return tt;
}
void BacktrackingSearch::insert(QVar* v) {
	q_.push(v);
	++time;
	var_stamp[v->id] = time;
}

SearchStatistics BacktrackingSearch::statistics() const {
	return ss_;
}

SearchStatistics BacktrackingSearch::solve(const Heuristic::Var varh, const Heuristic::Val valh, const int time_limits) {
	Timer t;
	vector<QVar*> x_evt;
	bool consistent_ = propagate(vars, 0).state;
	x_evt.clear();
	bool finished_ = false;
	if (!consistent_) {
		ss_.solve_time = t.elapsed();
		return ss_;
	}

	while (!finished_) {
		if (t.elapsed() > time_limits) {
			ss_.solve_time = t.elapsed();
			ss_.time_out = true;
			return ss_;
		}

		QVal v_a = select_QVal(varh, valh, top_);
		//cout << "=" << v_a << endl;
		top_ = new_level();
		I_.push(v_a);
		++ss_.num_positive;
		v_a.v->reduce_to(v_a.a, top_);
		x_evt.push_back(v_a.v);
		consistent_ = propagate(x_evt, top_).state;
		x_evt.clear();
		//I.update_model_assigned();
		if (consistent_&&I_.full()) {
			cout << I_ << endl;
			finished_ = true;
			//++sol_count_;
			//consistent_ = false;
		}

		while (!consistent_ && !I_.empty()) {
			v_a = I_.pop();
			//cout << "!" << v_a << endl;
			top_ = back_level();
			v_a.v->remove_value(v_a.a, top_);
			++ss_.num_negative;
			x_evt.push_back(v_a.v);
			consistent_ = v_a.v->size(top_) && propagate(x_evt, top_).state;
			x_evt.clear();
		}

		if (!consistent_)
			finished_ = true;
	}

	ss_.solve_time = t.elapsed();
	return ss_;
}

QVal BacktrackingSearch::select_QVal(const Heuristic::Var varh, const Heuristic::Val valh, const int p) {
	QVar* v = select_QVar(varh, p);
	const int a = select_value(v, valh, p);
	QVal val(v, a);
	return val;
}

QVar* BacktrackingSearch::select_QVar(const Heuristic::Var varh, const int p) {
	QVar* var = nullptr;
	double min_size = DBL_MAX;
	switch (varh) {
	case Heuristic::VRH_DOM_MIN: {
		for (auto v : vars)
			if (!I_.assigned(v))
				if (v->size(p) < min_size) {
					min_size = v->size(p);
					var = v;
				}
	} return var;
	case Heuristic::VRH_LEX:
		var = vars[I_.size() + 1];
		break;
	case Heuristic::VRH_VWDEG: break;
	case Heuristic::VRH_DOM_DEG_MIN: {
		for (auto v : vars)
			if (!I_.assigned(v)) {
				int dom_deg;
				if (neighborhood[v].size() == 0)
					dom_deg = -1;
				else
					dom_deg = v->size(p) / neighborhood[v].size();
				if (dom_deg < min_size) {
					min_size = dom_deg;
					var = v;
				}
			}
	}return var;
	case Heuristic::VRH_DOM_WDEG_MIN: {
		for (auto x : vars) {
			if (!I_.assigned(x)) {
				double x_w = 0.0;
				double x_dw = 0.0;

				for (auto c : subscription[x]) {
					int cnt = 0;
					for (auto y : c->scope)
						if (!I_.assigned(y))
							++cnt;
					if (cnt > 1)
						x_w += con_weight[c->id];
				}

				if (x->size(p) == 1 || x_w == 0)
					x_dw = -1;
				else
					x_dw = x->size(p) / x_w;

				if (x_dw < min_size) {
					min_size = x_dw;
					var = x;
				}
			}
		}
	} return var;
	default:
		var = nullptr;
		break;
	}
	return var;
}

int BacktrackingSearch::select_value(QVar* v, const Heuristic::Val valh, const int p) {
	int val = -1;
	switch (valh) {
	case Heuristic::VLH_MIN:
		val = v->head(p);
		break;
	case Heuristic::VLH_MIN_DOM: break;
	case Heuristic::VLH_MIN_INC: break;
	case Heuristic::VLH_MAX_INC: break;
	case Heuristic::VLH_VWDEG: val = -1; break;
	default:;
	}
	return val;
}


///////////////////////////////////////////////////////////////
MAC3::MAC3(HModel* h) :BacktrackingSearch(h) {}
PropagationState MAC3::propagate(vector<QVar*>& x_evt, const int level) {
	q_.clear();
	ps_.level = level;
	ps_.num_delete = 0;

	for (auto v : x_evt)
		insert(v);
	while (!q_.empty()) {
		QVar* x = q_.pop();
		//q_.pop_back();
		for (QTab* c : subscription[x]) {
			if (var_stamp[x->id] > con_stamp[c->id]) {
				for (auto y : c->scope) {
					if (!I_.assigned(y)) {
						bool aa = false;
						for (auto z : c->scope)
							if ((z != x) && var_stamp[z->id] > con_stamp[c->id])
								aa = true;

						if ((y != x) || aa)
							if (revise(c, y, level)) {
								if (y->faild(level)) {
									ps_.tab = c;
									ps_.var = y;
									++(con_weight[c->id]);
									ps_.state = false;
									return ps_;
								}
								insert(y);
							}
					}
				}
				++time;
				con_stamp[c->id] = time;
			}
		}
	}

	ps_.state = true;
	return ps_;
}
bool MAC3::revise(QTab* c, QVar* v, const int level) {
	const int num_elements = v->size(level);
	int a = v->head(level);

	while (a != Limits::INDEX_OVERFLOW) {
		if (!seek_support(c, v, a, level)) {
			v->remove_value(a, level);
			//cout << "(" << v->id << ", " << a << ")" << endl;
			++ps_.num_delete;
		}
		a = v->next(a, level);
	}

	return num_elements != v->size(level);
}

bool MAC3::seek_support(QTab* c, QVar* v, const int a, const int level) {
	c->get_first_valid_tuple(v, a, tmp_tuple_, level);
	while (Existed(tmp_tuple_)) {
		//cout << "tuple: " << tmp_tuple_[0] << "," << tmp_tuple_[1] << endl;
		if (c->sat(tmp_tuple_))
			return true;
		else
			c->get_next_valid_tuple(v, a, tmp_tuple_, level);
	}
	return false;
}

MAC3bit::MAC3bit(HModel* h) :BacktrackingSearch(h) {}
}

