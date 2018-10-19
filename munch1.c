#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "munch1.h"
#include "queue.h"

void munch1(Queue* input, Queue* output) {
	char* string = DequeueString(input);
	while(string != NULL) {
		char* nextOccurence = index(string, ' ');
		while(nextOccurence != NULL) {
			*nextOccurence = '*';
			nextOccurence = index(string, ' ');
		}
		EnqueueString(output, string);
		string = DequeueString(input);
	}
	EnqueueString(output, NULL);
}
