/*
 * GModel.h
 *
 *  Created on: 2017年9月27日
 *      Author: leezear
 */

#pragma once
#include <iostream>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>
#include "HModel.h"

namespace cp {

using namespace Gecode;
using namespace std;
class GModel: public Space {
public:
	IntVarArray vs;
	int mds;
	vector<vector<vector<int>>> neighborhoods;
	GModel();
	GModel(bool share, GModel& s);
	Space* copy(bool share) override;
	void print(void) const;
	virtual ~GModel();
};

} /* namespace cp */

