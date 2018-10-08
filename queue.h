struct Queue;

Queue *CreateStringQueue(int size);
void EnqueueString(Queue *q, char *string);
char* DequeueString(Queue *q);
void PrintQueueStats(Queue *q);
