#include "munch2.h"
#include <ctype.h>
#include "queue.h"

void munch2(Queue* q, char* str) {
	char* ptr = str;
	while (*ptr != NULL) {
		if (*ptr.isLower()) {
			*ptr = toupper((unsigned char) *ptr);
		}
		ptr++;
	}
	EnqueueString(q, str);
}
