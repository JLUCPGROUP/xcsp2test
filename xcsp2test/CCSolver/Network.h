﻿#pragma once
#include <climits>
#include <vector>
#include "XBuilder.h"
#include <bitset>

using namespace std;
namespace cp {

static bool Existed(vector<int>& tuple) {
	return tuple[0] != INT_MAX;
}

static void Exclude(vector<int>& tuple) {
	tuple[0] = INT_MAX;
}

const uint64_t MASK1_64[64] = {
	0x8000000000000000, 0x4000000000000000, 0x2000000000000000, 0x1000000000000000,
	0x0800000000000000, 0x0400000000000000, 0x0200000000000000, 0x0100000000000000,
	0x0080000000000000, 0x0040000000000000, 0x0020000000000000, 0x0010000000000000,
	0x0008000000000000, 0x0004000000000000, 0x0002000000000000, 0x0001000000000000,
	0x0000800000000000, 0x0000400000000000, 0x0000200000000000, 0x0000100000000000,
	0x0000080000000000, 0x0000040000000000, 0x0000020000000000, 0x0000010000000000,
	0x0000008000000000, 0x0000004000000000, 0x0000002000000000, 0x0000001000000000,
	0x0000000800000000, 0x0000000400000000, 0x0000000200000000, 0x0000000100000000,
	0x0000000080000000, 0x0000000040000000, 0x0000000020000000, 0x0000000010000000,
	0x0000000008000000, 0x0000000004000000, 0x0000000002000000, 0x0000000001000000,
	0x0000000000800000, 0x0000000000400000, 0x0000000000200000, 0x0000000000100000,
	0x0000000000080000, 0x0000000000040000, 0x0000000000020000, 0x0000000000010000,
	0x0000000000008000, 0x0000000000004000, 0x0000000000002000, 0x0000000000001000,
	0x0000000000000800, 0x0000000000000400, 0x0000000000000200, 0x0000000000000100,
	0x0000000000000080, 0x0000000000000040, 0x0000000000000020, 0x0000000000000010,
	0x0000000000000008, 0x0000000000000004, 0x0000000000000002, 0x0000000000000001,
};

const uint64_t MASK0_64[64] = {
	0x7FFFFFFFFFFFFFFF, 0xBFFFFFFFFFFFFFFF, 0xDFFFFFFFFFFFFFFF, 0xEFFFFFFFFFFFFFFF,
	0xF7FFFFFFFFFFFFFF, 0xFBFFFFFFFFFFFFFF, 0xFDFFFFFFFFFFFFFF, 0xFEFFFFFFFFFFFFFF,
	0xFF7FFFFFFFFFFFFF, 0xFFBFFFFFFFFFFFFF, 0xFFDFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF,
	0xFFF7FFFFFFFFFFFF, 0xFFFBFFFFFFFFFFFF, 0xFFFDFFFFFFFFFFFF, 0xFFFEFFFFFFFFFFFF,
	0xFFFF7FFFFFFFFFFF, 0xFFFFBFFFFFFFFFFF, 0xFFFFDFFFFFFFFFFF, 0xFFFFEFFFFFFFFFFF,
	0xFFFFF7FFFFFFFFFF, 0xFFFFFBFFFFFFFFFF, 0xFFFFFDFFFFFFFFFF, 0xFFFFFEFFFFFFFFFF,
	0xFFFFFF7FFFFFFFFF, 0xFFFFFFBFFFFFFFFF, 0xFFFFFFDFFFFFFFFF, 0xFFFFFFEFFFFFFFFF,
	0xFFFFFFF7FFFFFFFF, 0xFFFFFFFBFFFFFFFF, 0xFFFFFFFDFFFFFFFF, 0xFFFFFFFEFFFFFFFF,
	0xFFFFFFFF7FFFFFFF, 0xFFFFFFFFBFFFFFFF, 0xFFFFFFFFDFFFFFFF, 0xFFFFFFFFEFFFFFFF,
	0xFFFFFFFFF7FFFFFF, 0xFFFFFFFFFBFFFFFF, 0xFFFFFFFFFDFFFFFF, 0xFFFFFFFFFEFFFFFF,
	0xFFFFFFFFFF7FFFFF, 0xFFFFFFFFFFBFFFFF, 0xFFFFFFFFFFDFFFFF, 0xFFFFFFFFFFEFFFFF,
	0xFFFFFFFFFFF7FFFF, 0xFFFFFFFFFFFBFFFF, 0xFFFFFFFFFFFDFFFF, 0xFFFFFFFFFFFEFFFF,
	0xFFFFFFFFFFFF7FFF, 0xFFFFFFFFFFFFBFFF, 0xFFFFFFFFFFFFDFFF, 0xFFFFFFFFFFFFEFFF,
	0xFFFFFFFFFFFFF7FF, 0xFFFFFFFFFFFFFBFF, 0xFFFFFFFFFFFFFDFF, 0xFFFFFFFFFFFFFEFF,
	0xFFFFFFFFFFFFFF7F, 0xFFFFFFFFFFFFFFBF, 0xFFFFFFFFFFFFFFDF, 0xFFFFFFFFFFFFFFEF,
	0xFFFFFFFFFFFFFFF7, 0xFFFFFFFFFFFFFFFB, 0xFFFFFFFFFFFFFFFD, 0xFFFFFFFFFFFFFFFE,
};

namespace Limits {
/**
* \brief 取值范围
*/
const int MIN_INTVAR_ID = 0x7fff7000;
const int MAX_INTVAR_ID = INT_MAX - 1;
const int MAX_OPT = INT_MIN & 0xffff7000 - 1;
const int MIN_OPT = INT_MIN + 1;
const int UNSIGNED_VAL = INT_MIN & 0xffff7000;
const int MIN_VAL = UNSIGNED_VAL + 1;
const int MAX_VAL = MIN_INTVAR_ID - 1;
const int INDEX_OVERFLOW = -1;
const int PRESENT = -1;
const int ABSENT = 0;
}

const int BITSIZE = 64;

//class dynamic_bitset {
//public:
//	dynamic_bitset() {};
//	void resize(const int size, bool a = false);
//	auto& operator[](const int i);
//	bool any();
//	bool test(const int idx);
//	int count();
//	dynamic_bitset operator|(const dynamic_bitset &&lhs, const dynamic_bitset &&rhs);
//	dynamic_bitset& operator|=(const dynamic_bitset &t) const;
//protected:
//	tuple<int, int> get_index(const int i) const;
//	vector<bitset<BITSIZE>> data_;
//	int size_;
//	int limit_;
//};

inline static tuple<int, int> GetBitIdx(const int idx) {
	tuple<int, int> a;
	get<0>(a) = idx / BITSIZE;
	get<1>(a) = idx % BITSIZE;
	return a;
}
inline static int GetValue(const int i, const int j) {
	return  i*BITSIZE + j;
}
typedef vector<bitset<BITSIZE>> bitSetVector;

class IntVar {
public:
	IntVar(HVar* v, const int vs_size);
	//IntVar(const int id, vector<int>& v);
	~IntVar() {};
	void RemoveValue(const int a, const int p = 0);
	void ReduceTo(const int a, const int p = 0);
	void AddValue(const int a, const int  p = 0);
	//void RestoreUpTo(const int p);
	int value(const int idx) const { return vals_[idx]; }
	int size(const int p) const;
	int capacity() const { return init_size_; }
	bool assigned(const int p) const { return assigned_[p]; }
	void assign(const bool a, const int p) { assigned_[p] = a; }
	int next(const int a, const int p) const;
	void next_value(int& a, const int p);
	int prev(const int a, const int p) const;
	bool have(const int a, const int p) const;
	int head(const int p) const;
	int tail(const int p) const;
	bool faild(const int p) const { return size(p) == 0; };
	int stamp() const { return stamp_; }
	void stamp(const int s) { stamp_ = s; }
	bitSetVector& bitDom(const int p) { return bit_doms_[p]; }
	int id() const { return id_; }
	void show(const int p);
	inline tuple<int, int> get_bit_index(const int idx) const;
	vector<int>& values() { return vals_; }
	int GetDelete(const int src, const int dest, bitSetVector& del_vals);
	void BackTo(const int dest);
	void ClearLevel(const int p);
	int new_level(int src);
	void copy(const int src, const int dest);
protected:
	int id_;
	int init_size_;
	int value_ = -1;
	uint64_t stamp_ = 0;
	vector<bool> assigned_;
	int limit_;
	int num_bit_;
	vector<int> vals_;
	int top_;
	//unordered_map<int, int> val_map;
	//vector<int> anti_map;
	vector<bitSetVector> bit_doms_;
	bitSetVector bit_tmp_;
	static inline int get_value(const int i, const int j);
	//vector<uint64_t> tmp_;
};

class IntVal {
public:
	//int v;
	IntVal() : v_(nullptr), a_(-2) {};
	IntVal(IntVar* v, const int a, const bool aop = true) :v_(v), a_(a), aop_(aop) {};

	const IntVal& operator=(const IntVal& rhs);
	IntVar* v() const { return v_; }
	void v(IntVar* v) { v_ = v; }
	void a(const int a) { a_ = a; }
	int vid() const { return v_->id(); }
	int a() const { return a_; }
	bool op() const { return aop_; }
	void flip();
	IntVal next(const int p) const;
	bool operator==(const IntVal& rhs);
	bool operator!=(const IntVal& rhs);
	//bool operator<(const IntVar &v);
	friend std::ostream& operator<< (std::ostream &os, IntVal &v_val);
	tuple<int, int> get_bit_index() const;
	~IntVal() {};
protected:
	IntVar* v_;
	int a_;
	bool aop_ = true;
};

static const IntVal Nil_Val(nullptr, -1);

class Tabular {
public:
	Tabular(HTab* t, const vector<IntVar*> scp);
	//Tabular(const int id, const std::vector<IntVar *>& scope, vector<vector<int>>& ts, const int len);
	bool sat(vector<int> &t) const;
	~Tabular() {}
	void GetFirstValidTuple(IntVal& v_a, vector<int>& t, const int p);
	void GetNextValidTuple(IntVal& v_a, vector<int>& t, const int p);
	int index(IntVar* v) const;
	bool IsValidTuple(vector<int>& t, const int p);
	int id() const { return id_; }
	void stamp(const int s) { stamp_ = s; }
	int stamp() const { return stamp_; }
	size_t arity;
	vector<IntVar *>scope;
	const vector<vector<int>>& tuples() const { return tuples_; }
	float weight;
private:
	int id_;
	vector<vector<int>>& tuples_;
	uint64_t stamp_ = 0;
};

class arc {
public:
	arc() {}
	arc(Tabular* c, IntVar* v) :c_(c), v_(v) {}
	virtual ~arc() {}

	Tabular* c() const { return c_; }
	void c(Tabular* val) { c_ = val; }

	int c_id() const { return c_->id(); }
	int v_id() const { return v_->id(); }

	const arc& operator=(arc& rhs) {
		c_ = rhs.c_;
		v_ = rhs.v_;

		return *this;
	}

	friend std::ostream& operator<< (std::ostream &os, arc &c_x) {
		os << "(" << c_x.c_->id() << ", " << c_x.v_->id() << ")";
		return os;
	}

	IntVar* v() const { return v_; }
	void v(IntVar* val) { v_ = val; }
private:
	Tabular* c_;
	IntVar* v_;
};


class IntConVal {
public:
	IntConVal() {}
	IntConVal(Tabular* c, IntVar *v, const  int a) : c_(c), v_(v), a_(a) {}
	IntConVal(Tabular* c, IntVal& va) :c_(c), v_(va.v()), a_(va.a()) {}
	IntConVal(arc& rc, const int a) :c_(rc.c()), v_(rc.v()), a_(a) {}

	virtual ~IntConVal() {}

	Tabular* c() const { return c_; }
	void c(Tabular* c) { c_ = c; }


	IntVar* v() const { return v_; }
	void v(IntVar* val) { v_ = val; }

	int a() const { return a_; }
	void a(const int val) { a_ = val; }

	arc get_arc() const { return arc(c_, v_); }
	IntVal get_v_value() const { return IntVal(v_, a_); }

	int get_var_index()const { return c_->index(v_); }

	const IntConVal& operator=(const IntConVal& rhs);

	int GetVarIndex() const { return c_->index(v_); };

	friend std::ostream& operator<< (std::ostream &os, IntConVal &c_val) {
		os << "(" << c_val.c_->id() << ", " << c_val.v_->id() << ", " << c_val.a_ << ")";
		return os;
	}

private:
	Tabular* c_;
	IntVar* v_;
	int a_;
};

class Network {
public:
	vector<IntVar*> vars;
	vector<Tabular*> tabs;
	unordered_map<IntVar*, vector<Tabular*>> subscription;
	unordered_map<IntVar*, vector<IntVar* >> neighborhood;
	vector<vector<IntVar*>> nei_;
	//unordered_map<IntVar*, vector<IntVar*>> neighborhood;
	Network(HModel* h);
	static void GetFirstValidTuple(IntConVal & c_val, vector<int>& t, const int p);
	static void GetNextValidTuple(IntConVal & c_val, vector<int>& t, const int p);

	//  由于所有变量的域长度不一定相同 所以这里的c-value值不一定真实存在
	int GetIntConValIndex(IntConVal & c_val) const;
	int GetIntConValIndex(const int c_id, const int v_id, const int a);
	IntConVal GetIntConVal(int index);
	int top() const { return top_; }
	int tmp() const { return tmp_; }
	//void RestoreUpto(const int level);
	int NewLevel(const int src);
	void BackTo(const int dest);
	void CopyLevel(const int src, const int dest);
	void ClearLevel(const int p);
	//int NewTmpLevel();
	int max_arity() const { return max_arity_; }
	int max_domain_size() const { return max_dom_size_; }
	int max_bitDom_size() const { return max_bitDom_size_; }
	vector<IntVar*> get_neighbor(IntVar* v);
	void show(const int p);
	~Network();
private:
	vector<IntVar*> get_scope(HTab* t);
	void get_scope(HTab* t, vector<IntVar*> scp);
	HModel *hm_;
	const int max_arity_;
	const int max_dom_size_;
	const int max_bitDom_size_;
	const int num_vars_;
	const int num_tabs_;
	int top_ = 0;
	int tmp_ = 0;
};

}
