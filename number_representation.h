
#ifndef NUMBER_REPRESENTATIONS_H_
#define NUMBER_REPRESENTATIONS_H_

typedef uint8_t operator_token_t ;

#define NULL_TOKEN			0x00


/*
Format: 000x xPPP
P = precedence

*/
//These are defines instead of static const, so they can be used in switch-case statements
#define SPACE_TOKEN			0x01
#define PAREN_TOKEN			0x08
#define PAREN_CLOSE_TOKEN	0x10

#define POWER_TOKEN			0x01
#define XROOT_TOKEN			0x09
#define SQRT_TOKEN			0x11

#define MULTIPLY_TOKEN		0x02
#define DIVIDE_TOKEN		0x0A

#define ADD_TOKEN	 		0x03
#define SUBTRACT_TOKEN		0x0B
#define MOD_TOKEN			0x13

#define EQUAL_TOKEN			0x04
#define NOTEQ_TOKEN			0x0C
#define GT_TOKEN			0x14
#define LT_TOKEN			0x1C

//exceptions to the format:
// 0010 000x
#define GTEQ_TOKEN			0x20 //These have the same precedence as EQUAL!
#define LTEQ_TOKEN			0x21

#define IS_TOKEN			0x05
#define ISNOT_TOKEN			0x0D

#define IS_IN_TOKEN			0x06
#define NOT_IN_TOKEN		0x0E

//exceptions to the rules:
#define NOT_TOKEN			0x07
#define AND_TOKEN			0x0F //precedence == 8
#define OR_TOKEN			0x17 //precedence == 9

//SIMPLE RATIONAL
/*
 * Format: [0b1s00 zzzz] [EXPONENT] ([] [] [] [])
 *
 * zzzz = size; 2 * (0bzzzz + 1) bytes
 *
 *
 */

#endif /* NUMBER_REPRESENTATIONS_H_ */
