#ifndef QUEUE_H_   /* Include guard */
#define QUEUE_H_

#include <semaphore.h>

typedef struct {
	int size;
	int front_index;
	int end_index;
	int count;
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;
	char** strings;

	sem_t *mutex;
	sem_t *full;
	sem_t *empty;
	sem_t *count_mutex;
} Queue;

Queue *CreateStringQueue(int size);
void EnqueueString(Queue *q, char *string);
char* DequeueString(Queue *q);
void PrintQueueStats(Queue *q);

#endif // QUEUE_H_
