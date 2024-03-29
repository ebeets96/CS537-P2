#include <stdio.h>
#include <stdlib.h>
#include "writer.h"
#include "const.h"
#include "queue.h"

void writer (Queue* input) {
	char* string = DequeueString(input);
	while(string != NULL) {
		printf("%s", string);
		free(string);
		string = DequeueString(input);
	}
}
