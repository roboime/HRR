/*
 * L298N.hpp
 *
 *  Created on: May 21, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_L298N_HPP_
#define SRC_COMPONENTS_L298N_HPP_

#include "main.h"

class L298N {
public:
	L298N();
	virtual ~L298N();
	void setPower(float power);
};

#endif /* SRC_COMPONENTS_L298N_HPP_ */
