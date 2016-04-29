#ifndef SQUEUE_H
#define SQUEUE_H
#include <stdio.h>
#include <stdlib.h>

#define QNodeType int
#define State int

typedef struct QNode
{
	QNodeType data;
	QNode *next;
}QNode;
typedef struct Queue
{
	QNode *head;
	QNode *tail;
}Queue;

Queue *QCreate(void);
State EnQueue(Queue *Q,QNodeType data);
QNodeType DeQueue(Queue *Q);
bool QueueEmpty(Queue *Q);

#endif
