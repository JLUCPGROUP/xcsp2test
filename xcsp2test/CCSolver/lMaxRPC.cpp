#include "Solver.h"

using namespace std;
namespace cp {
using namespace std;

lMaxRPC::lMaxRPC(Network * m) :AC3bit(m) {
	//初始化队列
	q_var_.initial(m_->vars.size());
	//初始化约束查找矩阵
	nei_.resize(m_->vars.size(), vector<Tabular*>(m_->vars.size(), nullptr));
	for (auto c : m_->tabs) {
		nei_[c->scope[0]->id()][c->scope[1]->id()] = c;
		nei_[c->scope[1]->id()][c->scope[0]->id()] = c;
	}

	pc_nei_.resize(m_->vars.size(), vector<vector<IntVar*>>(m_->vars.size()));
	set<IntVar*> vars_map;
	vector<bool> vars_in(m_->vars.size(), false);
	for (auto x : m_->vars) {
		for (auto y : m_->vars) {
			for (auto z : m_->vars) {
				if (nei_[x->id()][z->id()] != nullptr&&nei_[y->id()][z->id()]) {
					if (!vars_in[z->id()]) {
						vars_in[z->id()] = true;
						pc_nei_[x->id()][y->id()].push_back(z);
					}
				}
			}
			vars_in.assign(vars_in.size(), false);
		}
	}

	last_pc.resize(m_->tabs.size()*m_->max_domain_size()*m_->max_arity(), Limits::INDEX_OVERFLOW);
	last_ac.resize(m_->tabs.size()*m_->max_domain_size()*m_->max_arity(), Limits::INDEX_OVERFLOW);
}

ConsistencyState lMaxRPC::enforce(vector<IntVar*>& x_evt, const int level) {
	level_ = level;
	q_var_.clear();
	for (auto i : x_evt) {
		for (int a = i->head(level_); a != Limits::INDEX_OVERFLOW; i->next_value(a, level_)) {
			for (auto j : m_->nei_[i->id()]) {
				if (have_no_PC_support(i, a, j)) {
					i->RemoveValue(a, level_);
					if (!i->faild(level_)) {
						q_var_.push(i);
					}
					else {
						++nei_[i->id()][j->id()]->weight;
						cs.state = false;
						return cs;
					}
				}
			}
		}
	}

	while (!q_var_.empty()) {
		const auto j = q_var_.pop();
		for (auto i : m_->nei_[j->id()]) {
			for (int a = i->head(level_); a != Limits::INDEX_OVERFLOW; i->next_value(a, level_)) {
				const auto c = nei_[i->id()][j->id()];
				const auto idx = m_->GetIntConValIndex(c->id(), i->id(), a);
				if (j->have(last_pc[idx], level_) && have_no_PC_support(i, a, j)) {
					i->RemoveValue(a, level_);
					if (!i->faild(level_)) {
						q_var_.push(i);
					}
					else {
						++c->weight;
						cs.state = false;
						return cs;
					}
				}
			}
		}
	}

	cs.state = true;
	return cs;
}

bool lMaxRPC::have_no_PC_support(IntVar* i, const int a, IntVar* j) {
	const auto c = nei_[i->id()][j->id()];
	const auto idx1 = m_->GetIntConValIndex(c->id(), i->id(), a);

	for (int b = j->head(level_); b != Limits::INDEX_OVERFLOW; j->next_value(b, level_)) {
		int PCWitness = true;
		auto b_idx = GetBitIdx(b);
		if (bitSup_[idx1][get<0>(b_idx)].test(get<1>(b_idx))) {
			for (auto k : pc_nei_[i->id()][j->id()]) {
				if (!have_PC_wit(i, a, j, b, k)) {
					PCWitness = false;
					break;
				}
			}
			if (PCWitness != false) {
				const auto idx2 = m_->GetIntConValIndex(c->id(), j->id(), b);
				last_pc[idx1] = b;
				last_pc[idx2] = a;
				last_ac[idx1] = b / BITSIZE;
				return false;
			}
		}
	}

	return true;
}

bool lMaxRPC::have_PC_wit(IntVar* i, const int a, IntVar* j, const int b, IntVar* k) {
	const auto c_ik = nei_[i->id()][k->id()];
	const auto c_jk = nei_[j->id()][k->id()];
	const auto cva_ikia = m_->GetIntConValIndex(c_ik->id(), i->id(), a);
	const auto cva_jkjb = m_->GetIntConValIndex(c_jk->id(), j->id(), b);
	//const auto cva_ikia = m_->GetIntConValIndex(c_ik->id(), i->id(), a);
	if (last_ac[cva_ikia] != Limits::INDEX_OVERFLOW) {
		const auto d = last_ac[cva_ikia];
		if ((bitSup_[cva_ikia][d] &
			bitSup_[cva_jkjb][d] &
			k->bitDom(level_)[d]).any()) {
			return true;
		}
		//const auto d = last_ac[cva_ikia];
		//const auto idx = GetBitIdx(d);
		//if (bitSup_[cva_ikia][get<0>(idx)].test(get<1>(idx))&
		//	bitSup_[cva_jkjb][get<0>(idx)].test(get<1>(idx))&
		//	k->bitDom(level_)[get<0>(idx)].test(get<1>(idx))) {
		//	return true;
		//}
	}

	if (last_ac[cva_jkjb] != Limits::INDEX_OVERFLOW) {
		const auto d = last_ac[cva_jkjb];
		if ((bitSup_[cva_ikia][d] &
			bitSup_[cva_jkjb][d] &
			k->bitDom(level_)[d]).any()) {
			return true;
		}
		//const auto idx = GetBitIdx(d);
		//if (bitSup_[cva_ikia][get<0>(idx)].test(get<1>(idx))&
		//	bitSup_[cva_jkjb][get<0>(idx)].test(get<1>(idx))&
		//	k->bitDom(level_)[get<0>(idx)].test(get<1>(idx))) {
		//	return true;
		//}
	}

	//const auto c_ik = nei_[i->id()][k->id()];
	//const auto c_jk = nei_[j->id()][k->id()];
	//const int cva_ikia = m_->GetIntConValIndex(c_ik->id(), i->id(), a);
	//const int cva_ikia = m_->GetIntConValIndex(c_jk->id(), j->id(), b);
	for (int c = 0; c < bitSup_[cva_ikia].size(); ++c)
		if ((bitSup_[cva_ikia][c] & bitSup_[cva_jkjb][c] & k->bitDom(level_)[c]).any()) {
			last_ac[cva_ikia] = c;
			last_ac[cva_jkjb] = c;
			return  true;
		}
	return false;
}

//bool lMaxRPC::is_neibor(IntVar* x, IntVar* y) {
//	auto a = GetBitIdx(x->id());
//	return neibor_[y][get<0>(a)].test(get<1>(a));
//}
}
