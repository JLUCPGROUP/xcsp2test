/*
 * SAC1G.h
 *
 *  Created on: 2016年11月17日
 *      Author: leezear
 */
#pragma once
#include "GModel.h"
using namespace Gecode;

namespace cp{

class SAC1G {
public:
	GModel* model;
	SAC1G(GModel* model);
	bool enforce() const;
	virtual ~SAC1G();
};

} /* namespace cp */
