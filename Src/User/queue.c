//
// Created by Cause_Hhc on 2020/9/2.
//

#include "queue.h"
#include <stdlib.h>

Queue* initQueue(){
  Queue *q = (Queue *)malloc(sizeof(Queue));
  if(!q)  return NULL;
  q->front = NULL;
  q->rear = NULL;
  return q;
}

void queue_offer(Queue *q, type data){
  QNode *node = (QNode *)malloc(sizeof(QNode));
  if(!node) return;
  node->data = data;
  node->next = NULL;
  if(!q->front) q->front = node;
  if(!q->rear)  q->rear = node;
  else{
    q->rear->next = node;
    q->rear = node;
  }
}

char isEmpty(Queue *q){
  return (q->front==NULL);
}

type queue_poll(Queue *q){
  if(isEmpty(q))  while(1);
  QNode *temp = q->front;
  type data;
  if(q->front == q->rear){
    q->front = NULL;
    q->rear = NULL;
  }else{
    q->front = q->front->next;
  }
  data = temp->data;
  free(temp);
  return data;
}

