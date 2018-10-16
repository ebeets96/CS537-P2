#include "reader.h"
#include <stdlib.h>

void read(Queue* q) {
	char* str = calloc(100, sizeof(char));
	while (fgets(str, 100, stdin)) {
		if (strchr(str, NULL) == NULL) {
			fprintf(stderr, "Input line length longer than buffer length\n");
			// Flush to end of line
			int endOfLineFound = 0;
			while (!endOfLineFound) {
				fgets(str, 100, stdin);
				if (strchr(str, NULL) != NULL) {
					endOfLineFound = 1;
				}
			}
		}
		else {
			EnqueueString(q, str);
			str = calloc(100, sizeof(char));
		}
	}
	free(str);
}
