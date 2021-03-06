#include <stdio.h>
#include "number_representation.h"
#include "print.h"
#include "parser.h"
#include "error.h"

#define INPUT_BUFFER_SIZE 1024
#define SCRATCH_MEMORY_SIZE 256
#define OPERATOR_STACK_SIZE 256
#define TOKEN_STACK_SIZE 256

int main(){
	printf("BetterAlgebraSystem\n");
	while(1){
		char pInputBuffer[INPUT_BUFFER_SIZE];
		uint8_t pTokenBuffer[INPUT_BUFFER_SIZE];
		uint8_t pOperatorStack[OPERATOR_STACK_SIZE];
		uint8_t* ppTokenStack[TOKEN_STACK_SIZE];
		uint8_t pScratchMemory[SCRATCH_MEMORY_SIZE];

		gets(pInputBuffer);
		if(parseText(pInputBuffer, pTokenBuffer, pOperatorStack) == SUCCESS){
			if(printBuffer(pTokenBuffer) != SUCCESS) {
				printf("Printing Error!\n");
			}
		} else {
			printf("Parsing error!\n");
		}
		//puts(inputBuffer);
		fflush(stdout);
	}
	return 0;
}
