#include "prodcomm.h"
#include "reader.h"
#include "queue.h"
#include <pthread.h>

struct twoArgs {
	Queue* arg1;
	Queue* arg2;
}

void* readerFunc(void* arg) {
	read(*arg);
}

void* munch1Func(void* args) {
	munch1(args->arg1, args->arg2);
}

void* munch2Func(void* args) {
	munch2(args->arg1, args->arg2);
}

void* writerFunc(void* arg) {
	write(*arg);
}

int main(int argc, char** argv) {
	Queue* q1 = malloc(sizeof(Queue));
	if (q1 == NULL) {
		// Did not work
	}
	
	Queue* q2 = malloc(sizeof(Queue));
	if (q2 == NULL) {
		// Did not work
	}
	
	Queue* q3 = malloc(sizeof(Queue));
	if (q3 == NULL) {
		// Did not work
	}

	pthread_t reader, munch1, munch2, writer;

	if (pthread_create(&reader, NULL, &readerFunc, q1) != 0) {
		// Did not work
	}

	struct twoArgs munch1Args;
	munch1Args.arg1 = q1;
	munch1Args.arg2 = q2;

	if (pthread_create(&munch1, NULL, &munch1Func, &munch1Args) != 0) {
	       // Did not work
	}

	struct twoArgs munch2Args;
	munch2Args.arg1 = q2;
	munch@args.arg2 = q3;

	if (pthread_create(&munch2, NULL, &munch2Func, &munch2Args) != 0) {
		// Did not work
	}	

	if (pthread_create(&writer, NULL, &writerFunc, q3) != 0) {
		// Did not work
	}

	if (pthread_join(reader) != 0) {
		// Did not work
	}
	if (pthread_join(munch1) != 0) {
		// Did not work
	}
	if (pthread_join(munch2) != 0) {
		// Did not work
	}
	if (pthread_join(writer) != 0) {
		// Did not work
	}

	free(q1);
	free(q2);
	free(q3);
}
