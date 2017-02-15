/*
 * calculate.c
 *
 *  Created on: Sep 30, 2016
 *      Author: Matthew
 */

#include <stdio.h>

#include "addition.h"

#include "number_representation.h"
#include "error.h"
#include "calculate.h"

status_t calculateNumbers(uint8_t* pTokenBuffer, uint8_t* pOutputBuffer, uint8_t** ppTokenStack, uint8_t* pScratchMemory) {
	uint8_t** ppTokenStackStart = ppTokenStack;
	ppTokenStack--;

	while(*pTokenBuffer != NULL_TOKEN){
		if(isSimpleRational(*pTokenBuffer)) {
			uint8_t size = sizeofSimpleRational(*pTokenBuffer);
			*++ppTokenStack = pTokenBuffer;
			pTokenBuffer += size;
		} else if (*pTokenBuffer == ADD_TOKEN) {
			uint8_t* operand1 = *ppTokenStack--;
			uint8_t* operand2 = *ppTokenStack--;
			addition(operand1, operand2, &pScratchMemory);
		} else {
#ifdef DEBUG
			printf("Unrecognized token detected during calculation.");
#endif
			return ERROR;
		}
	}

	return SUCCESS;
}


