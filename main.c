#include <stdio.h>
#include "number_representation.h"
#include "parser.h"
#include "error.h"

#define INPUT_BUFFER_SIZE 256
#define OPERATOR_STACK_SIZE 256

int main(){
	while(1){
		char pInputBuffer[INPUT_BUFFER_SIZE];
		uint8_t pTokenBuffer[INPUT_BUFFER_SIZE];
		uint8_t pOperatorStack[OPERATOR_STACK_SIZE];

		/*
		char* buf = inputBuffer;
		*buf++ = 'a';
		*buf = 'b';
		buf++;
		*buf = '\0';
		puts(inputBuffer);
		*/

		gets(pInputBuffer);
		if(parseText(pInputBuffer, pTokenBuffer, pOperatorStack) != SUCCESS){
			printf("Parsing error!\n");
		}
		//puts(inputBuffer);
		fflush(stdout);
	}
	return 0;
}
