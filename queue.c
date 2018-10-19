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

	if(newQueue->strings == NULL || newQueue->mutex == NULL ||
			newQueue->full == NULL || newQueue->empty == NULL)
	{
		fprintf(stderr, "Memory could not be allocated for the Queue.");
		exit(EXIT_FAILURE);
	}

	int sem0_success = sem_init(newQueue->mutex, 0, 1);
	int sem1_success = sem_init(newQueue->full, 0, 0);
	int sem2_success = sem_init(newQueue->empty, 0, size);

	//TODO check system call return values

	if(sem0_success == -1 || sem1_success == -1 || sem2_success == -1) {
		fprintf(stderr, "Semaphores could not be initialized.");
		exit(EXIT_FAILURE);
	}

	return newQueue;
}

void EnqueueString(Queue *q, char *string) {
	sem_wait(q->empty);
	int sem_error = (errno == EAGAIN);
	sem_wait(q->mutex);
	q->strings[q->end_index] = string;
	q->end_index = (q->end_index + 1) % q->size;
	q->count++;

	//TODO modify stats
	q->enqueueCount++;
	if (sem_error){
		q->enqueueBlockCount++;
	}

	sem_post(q->mutex);
	sem_post(q->full);
}

char* DequeueString(Queue *q) {
	sem_wait(q->full);
	int sem_error = (errno == EAGAIN);
	sem_wait(q->mutex);
	char* string = q->strings[q->front_index];
	q->count--;
	q->front_index = (q->front_index + 1) % q->size;

	//TODO modify stats
	q->dequeueCount++;
	if (sem_error){
		q->dequeueBlockCount++;
	}

	sem_post(q->mutex);
	sem_post(q->empty);
	return string;
}

void PrintQueueStats(Queue *q) {
	printf("Enqueue Count: %d\n", q->enqueueCount);
	printf("Dequeue Count: %d\n", q->dequeueCount);
	printf("Enqueue Block Count: %d\n", q->enqueueBlockCount);
	printf("Dequeue Block Count: %d\n", q->dequeueBlockCount);
}
