#include <stdlib.h>
#include <semaphore.h>
#include "queue.h"

Queue *CreateStringQueue(int size) {
	Queue *newQueue = malloc(sizeof(Queue));

	// Queue structure
	newQueue->front_index = 0;
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

	int sem0_success = sem_init(newQueue->mutex, 0, 1);
	int sem1_success = sem_init(newQueue->full, 0, 0);
	int sem2_success = sem_init(newQueue->empty, 0, size);

	//TODO check system call return values

	return newQueue;
}

void EnqueueString(Queue *q, char *string) {
	sem_wait(q->empty);
	sem_wait(q->mutex);
	int index = q->count;
	q->strings[index] = string;
	q->count++;

	//TODO modify stats

	sem_post(q->mutex);
	sem_post(q->full);
}

char* DequeueString(Queue *q) {
	sem_wait(q->full);
	sem_wait(q->mutex);
	char* string = q->strings[q->front_index];
	q->count--;
	q->front_index++;

	//TODO modify stats

	sem_post(q->mutex);
	sem_post(q->empty);
	return string;
}

void PrintQueueStats(Queue *q) {

}
