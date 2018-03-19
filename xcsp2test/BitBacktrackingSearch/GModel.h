/*
 * GModel.h
 *
 *  Created on: 2017年9月27日
 *      Author: leezear
 */

#pragma once
#include <iostream>
 //#include <int.hh>
 //#include <minimodel.hh>
 //#include <search.hh>
#include "HModel.h"
//#include <gecode/kernel/core.hpp>
#include <gecode/int.hh>
namespace cp {

	using namespace Gecode;
	using namespace std;
	class GModel : public Space {
	public:
		IntVarArray vs;
		int mds;
		vector<vector<vector<int>>> neighborhoods;
		GModel();
		GModel(GModel& s);
		Space* copy();
		void print(void) const;
		virtual ~GModel();
	};

} /* namespace cp */

