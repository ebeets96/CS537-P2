#include "munch2.h"
#include <ctype.h>
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void munch2(Queue* input, Queue* output) {
	char* string = DequeueString(input);

	char* curr = string;
	while (string != NULL) {
		while (*curr != '\0') {
			if (islower(*curr)) {
				*curr = toupper((unsigned char) *curr);
			}
			curr++;
		}
		EnqueueString(output, string);
		string = DequeueString(input);
		curr = string;
	}
	EnqueueString(output, string);
}
