#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct queue {
    int front;
    int rear;
    void** buffer;
    int buffer_size;
    int size;
} queue;

void queue_init(queue* q,int size) {
    q->front = -1;
    q->rear = 0;
    q->buffer = malloc(sizeof(void*)*size);
    q->buffer_size = size;
    q->size = 0;
}
bool queue_enqueue(queue* q,void* val) {
    if(q->front == q->rear) // buffer full
	return false;
    if(q->front == -1) // first emplace
	q->front = 0;
    q->buffer[q->rear] = val;
    q->rear = (q->rear + 1) % q->buffer_size;
    q->size++;
    return true;
}
bool queue_dequeue(queue* q,void** val) {
    if(q->front == -1 && q->rear == 0) //empty queue
	return false;
    *val = q->buffer[q->front];
    q->front = (q->front + 1) % q->buffer_size;
    if(q->front == q->rear) {// buffer has emptied
	q->front = -1;
	q->rear = 0;
	q->size = 0;
	return true;
    }
    q->size--;
    return true;
}

int main() {
    queue q;
    queue_init(&q,5);
    queue_enqueue(&q,(void*)1);
    queue_enqueue(&q,(void*)2);
    queue_enqueue(&q,(void*)3);
    queue_enqueue(&q,(void*)4);
    queue_enqueue(&q,(void*)5);
    
    bool ret = queue_enqueue(&q,(void*)1);
    printf("ret = %d\n",ret);
    printf("queue size = %d\n",q.size);
    
    void* val;
    ret = queue_dequeue(&q,&val);
    queue_enqueue(&q,(void*)6);

    printf("ret = %d, queue_size = %d, val = %d\n",ret,q.size,(int)val);
    printf("front = %d\n",q.front);
    while(q.size != 0) {
	queue_dequeue(&q,&val);
	printf("%d\n",(int)val);
    }

}
