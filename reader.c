#include "reader.h"
#include <stdlib.h>
#include "const.h"

void read(Queue* q) {
	char* str = calloc(BUFFER_SIZE, sizeof(char));
	while (fgets(str, BUFFER_SIZE, stdin)) {
		if (strchr(str, NULL) == NULL) {
			fprintf(stderr, "Input line length longer than buffer length\n");
			// Flush to end of line
			int endOfLineFound = 0;
			while (!endOfLineFound) {
				fgets(str, BUFFER_SIZE, stdin);
				if (strchr(str, NULL) != NULL) {
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
}
