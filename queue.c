#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include "queue.h"

Queue *CreateStringQueue(int size) {
	Queue *newQueue = malloc(sizeof(Queue));

	// Queue structure
	newQueue->size = size;
	newQueue->front_index = 0;
	newQueue->end_index = 0;
	newQueue->count = 0;

	// Stats
	newQueue->enqueueCount = 0;
	newQueue->dequeueCount = 0;
	newQueue->enqueueBlockCount = 0;
	newQueue->dequeueBlockCount = 0;
	newQueue->strings = malloc(size * sizeof(char*));

	// Semaphores
	newQueue->mutex = malloc(sizeof(sem_t));
	newQueue->full = malloc(sizeof(sem_t));
	newQueue->empty = malloc(sizeof(sem_t));
	newQueue->count_mutex = malloc(sizeof(sem_t));

	if(newQueue->strings == NULL || newQueue->mutex == NULL ||
			newQueue->full == NULL || newQueue->empty == NULL || newQueue->count_mutex == NULL)
	{
		fprintf(stderr, "Memory could not be allocated for the Queue.");
		exit(EXIT_FAILURE);
	}

	int sem0_success = sem_init(newQueue->mutex, 0, 1);
	int sem1_success = sem_init(newQueue->full, 0, 0);
	int sem2_success = sem_init(newQueue->empty, 0, size);
	int sem3_success = sem_init(newQueue->count_mutex, 0, 1);

	//TODO check system call return values

	if(sem0_success == -1 || sem1_success == -1 || sem2_success == -1 || sem3_success == -1) {
		fprintf(stderr, "Semaphores could not be initialized.");
		exit(EXIT_FAILURE);
	}

	return newQueue;
}

void EnqueueString(Queue *q, char *string) {
	//Critical section for approximating number of semaphore blocks
	sem_wait(q->count_mutex);
	q->enqueueBlockCount += (q->count == q->size); //Adds one if they are equal and zero if space is available
	sem_post(q->count_mutex);

	//Wait until queue has an available space
	sem_wait(q->empty);
	sem_wait(q->mutex);
	q->strings[q->end_index] = string;
	q->end_index = (q->end_index + 1) % q->size;
	q->count++;

	//TODO modify stats
	if(string != NULL) {
		q->enqueueCount++;
	}

	sem_post(q->mutex);
	sem_post(q->full);
}

char* DequeueString(Queue *q) {
	//Critical section for approximating number of semaphore blocks
	sem_wait(q->count_mutex);
	q->dequeueBlockCount += (q->count == 0); //Adds one if they are equal and zero if space is available
	sem_post(q->count_mutex);

	//Wait until queue has a string in the queue
	sem_wait(q->full);
	sem_wait(q->mutex);
	char* string = q->strings[q->front_index];
	q->count--;
	q->front_index = (q->front_index + 1) % q->size;

	//TODO modify stats
	if(string != NULL) {
		q->dequeueCount++;
	}

	sem_post(q->mutex);
	sem_post(q->empty);
	return string;
}

void PrintQueueStats(Queue *q) {
	fprintf(stderr,"Enqueue Count: %d\n", q->enqueueCount);
	fprintf(stderr,"Dequeue Count: %d\n", q->dequeueCount);
	fprintf(stderr,"Enqueue Block Count: %d\n", q->enqueueBlockCount);
	fprintf(stderr,"Dequeue Block Count: %d\n", q->dequeueBlockCount);
}
