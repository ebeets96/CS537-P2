#include "reader.h"
#include <stdlib.h>
#include "const.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>

void read(Queue* q) {
	char* str = calloc(BUFFER_SIZE, sizeof(char));
	while (fgets(str, BUFFER_SIZE, stdin)) {
		int next_char = fgetc(stdin);
		ungetc(next_char, stdin);
		if (strchr(str, '\n') == NULL && next_char != EOF) {
			fprintf(stderr, "Input line length longer than buffer length\n");
			// Flush to end of line
			int endOfLineFound = 0;
			while (!endOfLineFound) {
				fgets(str, BUFFER_SIZE, stdin);

				//If string contains null terminator, then the \n is found
				if (strchr(str, '\n') == NULL) {
					endOfLineFound = 1;
				}
			}
		}
		else {
			EnqueueString(q, str);
			str = calloc(BUFFER_SIZE, sizeof(char));
		}
	}
	free(str);
	EnqueueString(q, NULL);
}
