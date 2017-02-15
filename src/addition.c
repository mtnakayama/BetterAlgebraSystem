/*
 * addition.c
 *
 *  Created on: Sep 30, 2016
 *      Author: Matthew
 */

#include "addition.h"

status_t addition(uint8_t* operand0, uint8_t* operand1, uint8_t** refScratchMemory) {
	uint8_t operand0_length = sizeofSimpleRational(*operand0);
	int8_t operand0_exponent = *(operand0 + 1);
	int8_t operand0_lowExponent = operand0_exponent - (operand0_length * 2);

	uint8_t operand1_length = sizeofSimpleRational(*operand1);
	int8_t operand1_exponent = *(operand1 + 1);
	int8_t operand1_lowExponent = operand1_exponent - (operand1_length * 2);


	int8_t lowestExponent = operand0_lowExponent < operand1_lowExponent ?
			operand0_lowExponent : operand1_lowExponent;
	int8_t highestExponent = operand0_exponent > operand1_exponent ?
			operand0_exponent : operand1_exponent;

	uint8_t newNumberSize = (highestExponent - lowestExponent + 2) / 2;
	//uint8_t scratchSize = newNumberSize + 2;

	*(*refScratchMemory)++ = 0x80 + newNumberSize;



	return SUCCESS;
}

uint8_t addBCDByte(uint8_t a, uint8_t b, uint8_t* carry) {
	uint16_t result = (a & 0x0F) + (b & 0x0F);
	if(result > 0x09) {
		result += 0x06;
	}
	result += (a & 0xF0) + (b & 0xF0);
	if(result > 0x99) {
		result += 0x60;
	}
	if(result >= 0x100) {
		*carry = 1;
	} else {
		*carry = 0;
	}
	return result & 0xFF;
}

uint8_t subtractADCByte(uint8_t a, uint8_t b, uint8_t* carry) {
	uint16_t result = (a & 0x0F) - (b & 0x0F);
	if(result > 0x09) {
		result += 0x06;
	}
	result += (a & 0xF0) + (b & 0xF0);
	if(result > 0x99) {
		result += 0x60;
	}
	if(result >= 0x100) {
		*carry = 1;
	} else {
		*carry = 0;
	}
	return result & 0xFF;
}
