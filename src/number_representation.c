#include <stdbool.h>
#include <stdint.h>

#include "number_representation.h"

inline bool isOperatorToken(uint8_t token) {
	return (((token & 0xE0) == 0x00) && (token != 0x00));
}

inline bool isSimpleRational(uint8_t token) {
	return ((token & 0xB0) == 0x80);
}

inline uint8_t sizeofSimpleRational(uint8_t token){
	// Total number of bytes
	return (token & 0x0F) * 2 + 4;
}
