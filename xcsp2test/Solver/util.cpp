#include "util.h"
namespace cp {
//void dynamic_bitset::resize(const int size, const bool a) :
//	size_(size) {
//	const int s = ceil(float(size) / BITSIZE);
//	limit_ = s / BITSIZE;
//	if (a) {
//		data_.resize(s, ULLONG_MAX);
//		if (BITSIZE - limit_)
//			data_.back() <<= BITSIZE - limit_;
//	}
//	else
//		data_.resize(s, 0);
//}
//
//auto& dynamic_bitset::operator[](const int i) {
//	const auto index = get_index(i);
//	return data_[get<0>(index)][get<1>(index)];
//}
//
//bool dynamic_bitset::any() {
//	for (auto& a : data_)
//		if (a.any())
//			return true;
//	return false;
//}
//
//bool dynamic_bitset::test(const int idx) {
//	auto a = get_index(idx);
//	return data_[get<0>(a)][get<1>(a)];
//}
//
//int dynamic_bitset::count() {
//	int cnt = 0;
//	for (auto a : data_)
//		cnt += a.count();
//	return cnt;
//}
//
//dynamic_bitset dynamic_bitset::operator|(const dynamic_bitset && lhs, const dynamic_bitset && rhs) {
//	data_
//}
//
////dynamic_bitset dynamic_bitset::operator|(const dynamic_bitset & t) const {
////	return dynamic_bitset();
////}
//
//dynamic_bitset& dynamic_bitset::operator|=(const dynamic_bitset& t) const {}
//
//tuple<int, int> dynamic_bitset::get_index(const int i) const {
//	tuple<int, int> a;
//	get<0>(a) = i / BITSIZE;
//	get<1>(a) = i % BITSIZE;
//	return a;
//}


IntVar::IntVar(XVar* v, const int vs_size) :id_(v->id),init_size_() {
	int j = 0;
	const int size = max_val - min_val + 1;
	vals.resize(size);
	anti_map.resize(size);
	for (int i = min_val; i <= max_val; ++i) {
		val_map[i] = j;
		vals[j] = j;
		anti_map[j] = i;
		++j;
	}
}
}
