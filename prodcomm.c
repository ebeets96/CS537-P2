#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"
#include "queue.h"
#include "const.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct twoArgs {
	Queue* arg1;
	Queue* arg2;
};

void* readFunc(void* arg) {
	read(arg);
	return NULL;
}

void* munch1Func(void* args) {
	struct twoArgs *arguments = (struct twoArgs *)args;
	munch1(arguments->arg1, arguments->arg2);
	return NULL;
}

void* munch2Func(void* args) {
	struct twoArgs *arguments = (struct twoArgs *)args;
	munch2(arguments->arg1, arguments->arg2);
	return NULL;
}

void* writerFunc(void* arg) {
	writer(arg);
	return NULL;
}

int main() {
	Queue* q1 = CreateStringQueue(QUEUE_SIZE);
	Queue* q2 = CreateStringQueue(QUEUE_SIZE);
	Queue* q3 = CreateStringQueue(QUEUE_SIZE);

	pthread_t reader, munch1, munch2, writer;

	if (pthread_create(&reader, NULL, &readFunc, q1) != 0) {
		// Did not work
	}
	struct twoArgs munch1Args;
	munch1Args.arg1 = q1;
	munch1Args.arg2 = q2;

	struct twoArgs munch2Args;
	munch2Args.arg1 = q2;
	munch2Args.arg2 = q3;

	if (pthread_create(&munch1, NULL, &munch1Func, &munch1Args) != 0 ||
		pthread_create(&munch2, NULL, &munch2Func, &munch2Args) != 0 ||
		pthread_create(&writer, NULL, &writerFunc, q3) != 0)
	{
		fprintf(stderr, "Could not create threads");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(reader, NULL) != 0 ||
		pthread_join(munch1, NULL) != 0 ||
		pthread_join(munch2, NULL) != 0 ||
		pthread_join(writer, NULL) != 0)
	{
		fprintf(stderr, "Could not join threads");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "---Queue 1 Stats---\n");
	PrintQueueStats(q1);

	fprintf(stderr, "---Queue 2 Stats---\n");
	PrintQueueStats(q2);

	fprintf(stderr, "---Queue 3 Stats---\n");
	PrintQueueStats(q3);

	free(q1);
	free(q2);
	free(q3);
}
