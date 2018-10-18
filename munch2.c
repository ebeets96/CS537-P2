#include "munch2.h"
#include <ctype.h>
#include "queue.h"

void munch2(Queue* input, Queue* output) {
	char* string = DequeueString(input);
	char* curr = string;
	while (string != NULL) {
		while (*curr != NULL) {
			if (*curr.isLower()) {
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
