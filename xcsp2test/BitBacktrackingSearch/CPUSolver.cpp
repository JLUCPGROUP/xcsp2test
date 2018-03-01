#include "CPUSolver.h"
using namespace std;

namespace cp {
void BAssignedStack::initial(GModel* m) {
	max_size_ = m->vs.size();
	vals_.reserve(m->vs.size());
	asnd_.resize(m->vs.size(), false);
};

void BAssignedStack::initial(HModel* m) {
	max_size_ = m->vars.size();
	vals_.reserve(m->vars.size());
	asnd_.resize(m->vars.size(), false);
};

void BAssignedStack::initial(Network* m) {
	max_size_ = m->vars.size();
	vals_.reserve(m->vars.size());
	asnd_.resize(m->vars.size(), false);
};

void BAssignedStack::push(BIntVal& v_a) {
	//const int pre = top_ - 1;
	////进入的是positive decision 当前栈顶是negative decision
	//if (pre >= 0 && (!vals_[pre].aop) && v_a.aop) {
	//	vals_[pre] = v_a;
	//	asnd_[v_a.v] = true;
	//}
	//else {
	//vals_[top_] = v_a;
	vals_.push_back(v_a);
	asnd_[v_a.v] = v_a.aop;
	//}
};

BIntVal BAssignedStack::pop() {
	auto val = vals_.back();
	vals_.pop_back();
	asnd_[val.v] = false;
	return val;
}

BIntVal BAssignedStack::top() const { return vals_[vals_.size()]; };
int BAssignedStack::size() const { return vals_.size(); }
int BAssignedStack::capacity() const { return max_size_; }
bool BAssignedStack::full() const { return vals_.size() == max_size_; }
bool BAssignedStack::empty() const { return  vals_.empty(); }
BIntVal BAssignedStack::operator[](const int i) const { return vals_[i]; };
BIntVal BAssignedStack::at(const int i) const { return vals_[i]; }

vector<int> BAssignedStack::solution() {
	if (size() == 0) {
		return vector<int>();
	}
	vector<int> sol(size());
	sol.reserve(max_size_);
	for (int i = 0; i < size(); ++i) {
		sol[vals_[i].v] = vals_[i].a;
	}
	return sol;
};
void BAssignedStack::clear() { vals_.clear(); asnd_.assign(asnd_.size(), false); };
bool BAssignedStack::assiged(const int v) const { return asnd_[v]; };

ostream & operator<<(ostream & os, BAssignedStack & I) {
	for (int i = 0; i < I.size(); ++i)
		os << I[i] << " ";
	return os;
}

ostream & operator<<(ostream & os, BAssignedStack * I) {
	for (int i = 0; i < I->size(); ++i)
		os << I->at(i) << " ";
	return os;
}
//////////////////////////////////////////////////////////////////////////
const BIntVal & BIntVal::operator=(const BIntVal & rhs) {
	v = rhs.v;
	a = rhs.a;
	aop = rhs.aop;
	return *this;
}

void BIntVal::flip() {
	aop = !aop;
}

BIntVal BIntVal::next() const {
	return BIntVal(v, a + 1, true);
}

bool BIntVal::operator==(const BIntVal & rhs) {
	return (this == &rhs) || (v == rhs.v && a == rhs.a && aop == rhs.aop);
}

bool BIntVal::operator!=(const BIntVal & rhs) {
	return !((this == &rhs) || (v == rhs.v && a == rhs.a && aop == rhs.aop));
}

ostream & operator<<(ostream & os, BIntVal & v_val) {
	const string s = (v_val.aop) ? " = " : " != ";
	os << "(" << v_val.v << s << v_val.a << ")";
	return os;
}
}