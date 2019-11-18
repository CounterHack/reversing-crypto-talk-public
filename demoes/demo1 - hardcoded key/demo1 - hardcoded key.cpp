#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is BAD! */
#define KEY "\xf0\xa9\xaa\xf1\x2a\xdc\x69\xc6\x50\x9e\x9a\xbe\xf2\x76\x8c\xde"

void do_aes(char *key, char *data) {
	// TODO (if this was real)
}

void do_encrypt(char *text) {
	do_aes(KEY, text);
}

int main(int argc, char *argv[]) {
	do_encrypt("This is a data string");
	return 0;
}