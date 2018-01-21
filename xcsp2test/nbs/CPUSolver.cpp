#include "CPUSolver.h"
using namespace std;

namespace cp {
void AssignedStack::initial(GModel* m) {
	//gm_ = m;
	max_size_ = m->vs.size();
	vals_.resize(m->vs.size());
	asnd_.resize(m->vs.size(), false);
};

void AssignedStack::push(BIntVal& v_a) {
	//const int pre = top_ - 1;
	////进入的是positive decision 当前栈顶是negative decision
	//if (pre >= 0 && (!vals_[pre].aop) && v_a.aop) {
	//	vals_[pre] = v_a;
	//	asnd_[v_a.v] = true;
	//}
	//else {
		vals_[top_] = v_a;
		asnd_[v_a.v] = v_a.aop ? true : false;
		++top_;
	//}
};

BIntVal AssignedStack::pop() {
	--top_;
	asnd_[vals_[top_].v] = false;
	return vals_[top_];
}

BIntVal AssignedStack::top() const { return vals_[top_]; };
int AssignedStack::size() const { return top_; }
int AssignedStack::capacity() const { return max_size_; }
bool AssignedStack::full() const { return top_ == max_size_; }
bool AssignedStack::empty() const { return top_ == 0; }
BIntVal AssignedStack::operator[](const int i) const { return vals_[i]; };
BIntVal AssignedStack::at(const int i) const { return vals_[i]; };
void AssignedStack::clear() { top_ = 0; };
bool AssignedStack::assiged(const int v) const { return asnd_[v]; };

ostream & operator<<(ostream & os, AssignedStack & I) {
	for (int i = 0; i < I.size(); ++i)
		os << I[i] << " ";
	return os;
}

ostream & operator<<(ostream & os, AssignedStack * I) {
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