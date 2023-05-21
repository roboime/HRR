/*
 * Encoder.hpp
 *
 *  Created on: May 21, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_ENCODER_HPP_
#define SRC_COMPONENTS_ENCODER_HPP_

#include "main.h"

class Encoder {
public:
	Encoder();
	virtual ~Encoder();
	uint32_t getPosition();
};

#endif /* SRC_COMPONENTS_ENCODER_HPP_ */
