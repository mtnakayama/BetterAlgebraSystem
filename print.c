/*
 * print.c
 *
 *  Created on: Sep 28, 2016
 *      Author: Matthew
 */

#include <stdio.h>
#include "error.h"
#include "number_representation.h"
#include "print.h"
#include "parser.h"




status_t printBuffer(uint8_t* pBuffer) {
#ifdef DEBUG
	//output to stdio.h
	while(*pBuffer != NULL_TOKEN) {
		if((*pBuffer & 0xB0) == 0x80) {
			//print simple rational number;
			uint8_t size = ((*pBuffer++ & 0x0F) + 1) * 2;

			int8_t exponent = *pBuffer++;

			uint8_t firstDigits = *pBuffer++;
			printf("%X.%X", firstDigits >> 4, (firstDigits & 0x0F));
			size--;

			do {
				uint8_t number = *pBuffer++;
				printf("%02X", number);
				size--;
			} while (size != 0);

			printf("*10^%d", exponent);
		} else if((*pBuffer & 0xE0) == 0x00){
			char operator;
			if(tokenToOperatorChar(*pBuffer++, &operator) != SUCCESS) return ERROR;
			putchar(operator);
		} else {
			return ERROR;
		}
		putchar(' ');
	}
	printf("\n");
#endif

	return SUCCESS;
}


