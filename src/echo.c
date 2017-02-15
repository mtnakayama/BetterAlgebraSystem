
#include <stdio.h>
#include <string.h>

#include "echo.h"

#ifdef TEST
char echoString[ECHO_STRING_LEN];
#endif

void echo(char* message) {
#ifdef TEST
    strncpy(echoString, message, ECHO_STRING_LEN);
    printf("echo: %s\n", message);
#else
    puts(message);
#endif
}
