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
}

ConsistencyState lMaxRPC::enforce(vector<IntVar*>& x_evt, const int level) {
	//level_ = level;
	//q_var_.clear();
	//for (auto i : x_evt) {
	//	for (auto a : i->values()) {
	//		if (i->have(a, level_)) {
	//			for (auto j : m_->neighborhood[i]) {
	//				if (have_no_PC_support(i, a, j)) {
	//					i->RemoveValue(a, level_);
	//					if (!i->faild(level_)) {
	//						q_var_.push(i);
	//					}
	//					else {
	//						cs.state = false;
	//						return cs;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//while (!q_var_.empty()) {
	//	auto j = q_var_.pop();
	//	for (auto i : m_->neighborhood[j]) {
	//		for (auto a : i->values()) {
	//			if (i->have(a, level_)) {
	//				if (have_no_PC_support(i, a, j)) {
	//					i->RemoveValue(a, level_);
	//					if (!i->faild(level_)) {
	//						q_var_.push(i);
	//					}
	//					else {
	//						cs.state = false;
	//						return cs;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//cs.state = true;
	//return cs;	

	level_ = level;
	q_var_.clear();
	for (auto i : x_evt) {
		for (auto a : i->values()) {
			if (i->have(a, level_)) {
				for (auto j : m_->nei_[i->id()]) {
					if (have_no_PC_support(i, a, j)) {
						i->RemoveValue(a, level_);
						if (!i->faild(level_)) {
							q_var_.push(i);
						}
						else {
							cs.state = false;
							return cs;
						}
					}
				}
			}
		}
	}

	while (!q_var_.empty()) {
		const auto j = q_var_.pop();
		for (auto i : m_->nei_[j->id()]) {
			for (auto a : i->values()) {
				if (i->have(a, level_)) {
					if (have_no_PC_support(i, a, j)) {
						i->RemoveValue(a, level_);
						if (!i->faild(level_)) {
							q_var_.push(i);
						}
						else {
							cs.state = false;
							return cs;
						}
					}
				}
			}
		}
	}

	cs.state = true;
	return cs;
}

bool lMaxRPC::have_no_PC_support(IntVar* i, const int a, IntVar* j) {
	const int v = j->head(level_);
	const auto c = nei_[i->id()][j->id()];
	const int idx = m_->GetIntConValIndex(c->id(), i->id(), a);

	for (int b = v; b != Limits::INDEX_OVERFLOW; j->next_value(b, level_)) {
		int PCWitness = true;
		auto b_idx = GetBitIdx(b);
		if (bitSup_[idx][get<0>(b_idx)].test(get<1>(b_idx))) {
			for (auto k : m_->vars) {
				if (nei_[k->id()][i->id()] != nullptr&&nei_[k->id()][j->id()] != nullptr) {
					if (!have_PC_wit(i, a, j, b, k)) {
						PCWitness = false;
						break;
					}
				}
			}
			if (PCWitness != false) {
				return false;
			}
		}
	}

	return true;
}

bool lMaxRPC::have_PC_wit(IntVar* i, const int a, IntVar* j, const int b, IntVar* k) {
	const auto c_ik = nei_[i->id()][k->id()];
	const auto c_jk = nei_[j->id()][k->id()];
	const int idx0 = m_->GetIntConValIndex(c_ik->id(), i->id(), a);
	const int idx1 = m_->GetIntConValIndex(c_jk->id(), j->id(), b);
	for (int c = 0; c < k->bitDom(level_).size(); ++c)
		if ((bitSup_[idx0][c] & bitSup_[idx1][c] & k->bitDom(level_)[c]).any())
			return  true;
	return false;
}

//bool lMaxRPC::is_neibor(IntVar* x, IntVar* y) {
//	auto a = GetBitIdx(x->id());
//	return neibor_[y][get<0>(a)].test(get<1>(a));
//}
}
