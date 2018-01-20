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

const u64 MASK1_64[64] = {
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

const u64 MASK0_64[64] = {
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
typedef vector<bitset<BITSIZE>> bitSetVector;

class IntVar {
public:
	IntVar(XVar* v, const int vs_size);
	~IntVar() {};
	void RemoveValue(const int a, const int p = 0);
	void ReduceTo(const int a, const int p = 0);
	void AddValue(const int a, const int  p = 0);
	void RestoreUpTo(const int p);
	int value(const int idx) const { return vals_[idx]; }
	int size(const int p) const;
	int capacity() const { return init_size_; }
	bool assigned(const int p) const { return assigned_[p]; }
	void assign(const bool a, const int p) { assigned_[p] = a; }
	int next(const int a, const int p) const;
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
	void GetDelete(const int src, const int dest, bitSetVector& del_vals);
	int NewLevel();
protected:
	int id_;
	int uid;
	string name_ = "";
	int init_size_;
	int curr_size_;
	int value_ = -1;
	u64 stamp_ = 0;
	//bool assigned_ = false;
	vector<bool> assigned_;
	int last_limit_;
	int num_bit_;
	int top_ = 0;
	int level = -1;
	vector<int> vals_;
	unordered_map<int, int> val_map;
	vector<int> anti_map;
	vector<bitSetVector> bit_doms_;
	bitSetVector bit_tmp_;
	vector<int> level_;
	static int get_value(const int i, const int j);
	vector<u64> tmp_;
};

}
