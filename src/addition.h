/*
 * addition.h
 *
 *  Created on: Sep 30, 2016
 *      Author: Matthew
 */

#ifndef ADDITION_H_
#define ADDITION_H_

#include <stdint.h>
#include "error.h"

status_t addition(uint8_t* operand0, uint8_t* operand1, uint8_t** refScratchMemory);

#endif /* ADDITION_H_ */
