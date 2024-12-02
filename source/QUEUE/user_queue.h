/*
 * Queue.h
 *
 *  Created on: Oct 28, 2024
 *      Author: thanhdatpham
 */

#ifndef USER_QUEUE_H_
#define USER_QUEUE_H_

#define RING_MAX_SIZE 4

typedef struct LineBuffer
{
	char str[100];
}Line;

typedef struct _RingbufferType
{
    Line buffer[RING_MAX_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} Ringbuffer;

void InitQueue(volatile Ringbuffer *rb);
//bool isFull(volatile Ringbuffer * rb);
//bool isEmpty(volatile Ringbuffer * rb);
void enQueue(volatile Ringbuffer * rb, Line data);
Line deQueue(volatile Ringbuffer * rb);
uint16_t queueSize(Ringbuffer *rb);

#endif /* USER_QUEUE_H_ */
