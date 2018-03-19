/*
 * GModel.cpp
 *
 *  Created on: 2017年9月27日
 *      Author: leezear
 */

#include "GModel.h"

namespace cp {

	GModel::GModel() {
		// TODO Auto-generated constructor stub

	}

	GModel::GModel(GModel& s) :
		Space(s) {
		vs.update(*this, s.vs);
	}

	Space* GModel::copy() {
		return new GModel(*this);
	}

	void GModel::print(void) const {
		for (size_t i = 0; i < vs.size(); i++) {
			cout << "(" << i << " = " << vs[i] << ") ";
		}
		cout << endl;
	}

	GModel::~GModel() {
		// TODO Auto-generated destructor stub
	}

} /* namespace cp */
