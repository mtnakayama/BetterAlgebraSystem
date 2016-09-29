#include <stdio.h>
#include <stdbool.h>

#include "number_representation.h"
#include "error.h"
#include "parser.h"

//@TODO add bounds checking!
//LOCAL DEFINITIONS
typedef bool associativity_t;
static const bool ASSOCIATIVITY_LEFT = false;
static const bool ASSOCIATIVITY_RIGHT = true;
//END LOCAL DEFINITIONS

//LOCAL FUNCTIONS
status_t readNumber(char** character_ref, uint8_t** outputTokens_ref);
status_t readOperator(char** refCharacter, uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart);
status_t operatorAttributes(uint8_t token, uint8_t* precedence, bool* associativity);
status_t shuntingYard(uint8_t token, uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart);
status_t shuntingYardParen(uint8_t** refOutputTokens, uint8_t** refOperatorStack);
status_t shuntingYardCloseParen(uint8_t** refOutputTokens, uint8_t** refOperatorStack);
status_t dumpOperatorStack(uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart);
//END LOCAL FUNCTIONS

status_t parseText(char* pInputText, uint8_t* pOutputTokens, uint8_t* pOperatorStack) {
	uint8_t* pOperatorStackStart = pOperatorStack;
	pOperatorStack--; //when we push, we increment the pointer then write the byte
	for(char* pCharacter = pInputText; *pCharacter != '\0'; /*pCharacter++*/){
		if((*pCharacter >= '0' && *pCharacter <= '9') || (*pCharacter == '.')) {
			//numeral character
			//isNumber = true;
			if(readNumber(&pCharacter, &pOutputTokens) != SUCCESS) return ERROR;
		} else if(*pCharacter == '+') {
			if(readOperator(&pCharacter, &pOutputTokens, &pOperatorStack, pOperatorStackStart) != SUCCESS) return ERROR;
		} else if(*pCharacter == '(') {
			pCharacter++;
			if(shuntingYardParen(&pOutputTokens, &pOperatorStack) != SUCCESS) return ERROR;
		} else if(*pCharacter == ')') {
			pCharacter++;
			if(shuntingYardCloseParen(&pOutputTokens, &pOperatorStack) != SUCCESS) return ERROR;
#ifdef DEBUG
		} else if(*pCharacter == '\r') {//ignore carriage return
			pCharacter++;
			continue;
#endif
		} else {
			pCharacter++;
		}
		//putchar(*character);
	}

	if(dumpOperatorStack(&pOutputTokens, &pOperatorStack, pOperatorStackStart) != SUCCESS) return ERROR;

	*pOutputTokens = NULL_TOKEN;
	return SUCCESS;
}

#ifdef DEBUG
#define DEBUG_READ_NUMBER
//#define DEBUG_READ_NUMBER_DETAILS
#endif
status_t readNumber(char** refCharacter, uint8_t** refOutputTokens) {
#ifdef DEBUG
	printf("Reading Number: ");
#endif
	char* pCharacter = *refCharacter;
	char* pNumberStart;
	uint8_t* pOutputTokens = *refOutputTokens;
	bool encounteredDecimal = false;
	bool bLeadingZeroes = true;
	int8_t exponent = -1;
	uint8_t digitCount = 0;
	uint8_t trailingZeroes = 0;

	while(true) {
		if(*pCharacter >= '0' && *pCharacter <= '9') {
			if (*pCharacter == '0') {
				trailingZeroes++;
				if(bLeadingZeroes && encounteredDecimal) {
					exponent--;
				}
			} else {
				trailingZeroes = 0;
				if(bLeadingZeroes){
					pNumberStart = pCharacter;
					bLeadingZeroes = false;
				}
				if(!encounteredDecimal) {
					exponent++;
				}
			}
			if(!bLeadingZeroes) {
				digitCount++;
			}
		} else if(*pCharacter == '.') {
			if(!encounteredDecimal){
				encounteredDecimal = true;
			} else {
				//there cannot be multiple decimal points!
				return ERROR;
			}
		} else {
			//that's the end of the numbers.
			break;
		}
		pCharacter++;
	}

#ifdef DEBUG_READ_NUMBER
	for(char* ch = *refCharacter; ch < pCharacter; ch++){
		putchar(*ch);
	}
	printf("\n");
#endif

	if(digitCount == 0 && trailingZeroes) {
		//The number is 0.
		digitCount = 1;
		exponent = 0; // not sure if this actually matters.
		pNumberStart = (pCharacter - 1); //point pNumberStart to the last zero.
	} else {
		digitCount -= trailingZeroes;
	}

#ifdef DEBUG_READ_NUMBER_DETAILS
	printf("digitCount: %u\n", digitCount);
#endif

	uint8_t size = digitCount / 4;
	if(size > 15) {
		//@TODO implement larger numbers later
		return ERROR;
	};
	uint8_t padding = (uint8_t)(-digitCount) % 4;

#ifdef DEBUG_READ_NUMBER_DETAILS
	printf("padding: %u\n", padding);
#endif

	uint8_t flagByte = 0x80 + size;
	//@TODO add code for negative numbers
	*pOutputTokens++ = flagByte;

	*pOutputTokens++ = exponent;

	while(digitCount >= 2){
		if(*pNumberStart == '.') {
			pNumberStart++;
		}
		uint8_t digit = *pNumberStart++ << 4;
		if(*pNumberStart == '.') {
			pNumberStart++;
		}
		digit |= (*pNumberStart++ & 0x0F);
		*pOutputTokens++ = digit;

		digitCount -= 2;
	}
	if(digitCount /*== 1*/){
		//last digit should not be a decimal point.
		uint8_t digit = *pNumberStart++ << 4;
		*pOutputTokens++ = digit;
		padding--;
		//digitCount--;
	}
	if(padding /*== 2*/){
		*pOutputTokens++ = 0;
		//padding -= 2;
	}

#ifdef DEBUG_READ_NUMBER_DETAILS
	printf("Exponent: %d\nTrailing Zeroes: %u\n", exponent, trailingZeroes);
#endif

#ifdef DEBUG_READ_NUMBER
	printf("Hex: ");
	for(uint8_t* tok = *refOutputTokens; tok < pOutputTokens; tok++){
		printf("%02X ", (unsigned char)*tok);
	}
	printf("\n\n");
#endif

	*refCharacter = pCharacter;
	*refOutputTokens = pOutputTokens;
	return SUCCESS;
}

status_t operatorAttributes(operator_token_t token, uint8_t* pPrecedence, associativity_t* pAssociativity) {
	switch(token) {
	case PAREN_TOKEN:
		*pPrecedence = 0;
		*pAssociativity = ASSOCIATIVITY_LEFT;
		break;
	case PAREN_CLOSE_TOKEN:
		*pPrecedence = 0;
		*pAssociativity = ASSOCIATIVITY_LEFT;
		break;
	case POWER_TOKEN:
		*pPrecedence = 0;
		*pAssociativity = ASSOCIATIVITY_RIGHT;
		break;
	case ADD_TOKEN:
		*pPrecedence = 3;
		*pAssociativity = ASSOCIATIVITY_LEFT;
		break;
	case SUBTRACT_TOKEN:
		*pPrecedence = 3;
		*pAssociativity = ASSOCIATIVITY_LEFT;
		break;
	default:
#ifdef DEBUG
		printf("Unrecognized Operator: %02X\n", token);
#endif
		return ERROR;
	}
	return SUCCESS;
}
status_t operatorCharToToken(char operatorChar, operator_token_t* pToken){
	switch(operatorChar) {
	case '+':
		*pToken = ADD_TOKEN;
		break;
	case '-':
		*pToken = SUBTRACT_TOKEN;
		break;
	default:
#ifdef DEBUG
		printf("Unrecognized Operator: %c\n", operatorChar);
#endif
		return ERROR;
	}
	return SUCCESS;
}
status_t tokenToOperatorChar(operator_token_t token, char *pChar){
	switch(token){
	case ADD_TOKEN:
		*pChar = '+';
		break;
	case SUBTRACT_TOKEN:
		*pChar = '-';
		break;
	default:
#ifdef DEBUG
		printf("Unrecognized Token: %02X\n", token);
#endif
		return ERROR;
	}
	return SUCCESS;
}


#ifdef DEBUG
#define DEBUG_READ_OPERATOR
#endif
status_t readOperator(char** refCharacter, uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart) {
#ifdef DEBUG_READ_OPERATOR
	printf("Reading Operator: %c\n\n", **refCharacter);
#endif

	operator_token_t token;
	if(operatorCharToToken(*(*refCharacter)++, &token) != SUCCESS) return ERROR;

	if(shuntingYard(token, refOutputTokens, refOperatorStack, pOperatorStackStart) != SUCCESS) return ERROR; //

	return SUCCESS;
}

status_t shuntingYard(uint8_t token, uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart) {
	uint8_t precedence;
	associativity_t associativity;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	if(operatorAttributes(token, &precedence, &associativity) != SUCCESS) return ERROR; //
#pragma GCC diagnostic pop

	while(*refOperatorStack >= pOperatorStackStart) {
		operator_token_t stackOperator = **refOperatorStack;
		uint8_t stackOperatorPrecedence;
		associativity_t stackOperatorAssoc;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
		if(operatorAttributes(stackOperator, &stackOperatorPrecedence, &stackOperatorAssoc) != SUCCESS) return ERROR; //
#pragma GCC diagnostic pop

		if((associativity == ASSOCIATIVITY_LEFT && precedence <= stackOperatorPrecedence)
				|| (associativity == ASSOCIATIVITY_RIGHT && precedence < stackOperatorPrecedence)) {

			*(*refOutputTokens)++ = stackOperator;
			(*refOperatorStack)--;
		} else {
			break;
		}
	}
	*++(*refOperatorStack) = token;

	return SUCCESS;
}

status_t shuntingYardParen(uint8_t** refOutputTokens, uint8_t** refOperatorStack){
	return SUCCESS;
}

status_t shuntingYardCloseParen(uint8_t** refOutputTokens, uint8_t** refOperatorStack){
	return SUCCESS;
}

status_t dumpOperatorStack(uint8_t** refOutputTokens, uint8_t** refOperatorStack, uint8_t* pOperatorStackStart){
	while(*refOperatorStack >= pOperatorStackStart){
		*(*refOutputTokens)++ = *(*refOperatorStack)--;
	}
	return SUCCESS;
}
