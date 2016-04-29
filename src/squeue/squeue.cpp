#include "squeue.h"
Queue *QCreate(void){
	Queue *Q = (Queue*)malloc(sizeof(Queue));
	Q->head = Q->tail = (QNode*)malloc(sizeof(QNode));
	Q->head->next = NULL;
	return Q;
}

State EnQueue(Queue *Q,QNodeType data){
	QNode *newnode = (QNode*)malloc(sizeof(QNode));
	newnode->data = data;
	newnode ->next = NULL;

	Q->tail->next = newnode;
	Q->tail = newnode;
	
	return 1;
}
bool QueueEmpty(Queue *Q){	
	return (Q->head == Q->tail)?1:0;
}
QNodeType DeQueue(Queue *Q){
	QNodeType e;
	QNode *p;
	if(Q->head == Q->tail){
		return NULL;
	}		
	else{
		p = Q->head->next;
		Q->head->next = p->next;
		e = p->data;
		if(Q->tail == p){
			Q->tail = Q->head;
		}
		free(p);
		return e;
	}
}
