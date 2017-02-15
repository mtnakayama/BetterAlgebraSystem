#ifndef ECHO_H_
#define ECHO_H_

void echo(char* message);

#ifdef TEST
#define ECHO_STRING_LEN 255
extern char echoString[ECHO_STRING_LEN];
#endif

#endif /* ECHO_H_ */
