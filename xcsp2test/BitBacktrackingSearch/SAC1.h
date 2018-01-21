/*
 * SAC1.h
 *
 *  Created on: 2016年11月17日
 *      Author: leezear
 */
#pragma once
#include "GModel.h"
using namespace Gecode;

namespace cp{

class SAC1 {
public:
	GModel* model;
	SAC1(GModel* model);
	bool enforce() const;
	virtual ~SAC1();
};

} /* namespace cp */
