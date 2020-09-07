//
// Created by Cause_Hhc on 2020/9/2.
//

#ifndef MAZE_STM32_CUBEMX_CLION_QUEUE_H
#define MAZE_STM32_CUBEMX_CLION_QUEUE_H

typedef struct {
    char x;
    char y;
}type;
typedef struct Node{
    type data;
    struct Node *next;
} QNode;
typedef struct {
    QNode *front;
    QNode *rear;
}Queue;

Queue* initQueue();
void queue_offer(Queue *q, type data);
char isEmpty(Queue *q);
type queue_poll(Queue *q);

#endif //MAZE_STM32_CUBEMX_CLION_QUEUE_H
