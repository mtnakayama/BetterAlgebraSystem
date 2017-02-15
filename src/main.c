#include <stdio.h>

#include "error.h"
#include "mem.h"
#include "number_representation.h"
#include "parser.h"
#include "print.h"


int main(){
    bool quit = false;
    printf("BetterAlgebraSystem\n");
    while(!quit){
        char pInputBuffer[INPUT_BUFFER_SIZE];
        uint8_t pTokenBuffer[INPUT_BUFFER_SIZE];
        uint8_t pOperatorStack[OPERATOR_STACK_SIZE];
        uint8_t* ppTokenStack[TOKEN_STACK_SIZE];
        uint8_t pScratchMemory[SCRATCH_MEMORY_SIZE];

        gets(pInputBuffer);
        switch(parseText(pInputBuffer, pTokenBuffer, pOperatorStack)) {
        case SUCCESS:
            if(printBuffer(pTokenBuffer) != SUCCESS) {
                printf("Printing Error!\n");
            }
            break;
        case QUIT:
            quit = true;
            break;
        default:
            printf("Parsing error!\n");
            break;
        }
        //puts(inputBuffer);
        fflush(stdout);
    }
    return 0;
}
