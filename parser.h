
#ifndef PARSER_H_
#define PARSER_H_

#include "error.h"
status_t parseText(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack);
status_t tokenToOperatorChar(operator_token_t token, char *pChar);
#endif /* PARSER_H_ */
