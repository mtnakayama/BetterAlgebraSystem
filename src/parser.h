
#ifndef PARSER_H_
#define PARSER_H_

#include <stdbool.h>

#include "error.h"
#include "number_representation.h"

status_t parseText(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack);
status_t parseInfixText(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack);
status_t parseReversePolishText(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack);

status_t tokenToOperatorChar(operator_token_t token, char *pChar);

status_t readNumber(char** character_ref, uint8_t** outputTokens_ref);
status_t readOperator(char** refCharacter, uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart);
status_t operatorAttributes(uint8_t token, uint8_t* precedence, bool* associativity);
status_t shuntingYard(uint8_t token, uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart);
status_t shuntingYardParen(uint8_t** refOutputTokens, uint8_t** refOperatorStack);
status_t shuntingYardCloseParen(uint8_t** refOutputTokens, uint8_t** refOperatorStack);
status_t dumpOperatorStack(uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart);

extern bool global_reversePolishNotation;

#endif /* PARSER_H_ */
