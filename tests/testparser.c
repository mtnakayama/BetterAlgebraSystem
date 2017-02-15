
#include <assert.h>
#include <string.h>

#include "error.h"
#include "echo.h"
#include "mem.h"
#include "parser.h"


void testReversePolishSwitch(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack);

void testParser() {
    assert(1);
    char pInputText[INPUT_BUFFER_SIZE];
    uint8_t pOutputTokens[INPUT_BUFFER_SIZE];
    uint8_t pOperatorStack[OPERATOR_STACK_SIZE];
    testReversePolishSwitch(pInputText, pOutputTokens, pOperatorStack);
}

void testReversePolishSwitch(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack) {
    assert(global_reversePolishNotation == false);
    assert(parseText("rpolish", pOutputTokens, pOperatorStack) == SUCCESS);
    assert(global_reversePolishNotation == true);
    assert(parseText("infix", pOutputTokens, pOperatorStack) == SUCCESS);
    assert(global_reversePolishNotation == false);
}
