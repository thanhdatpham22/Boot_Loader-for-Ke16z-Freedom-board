/*
 * Queue.c
 *
 *  Created on: Oct 28, 2024
 *      Author: thanhdatpham
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <user_queue.h>
#include "fsl_debug_console.h"

void InitQueue(volatile Ringbuffer *rb)
{
	rb->head = 0;
	rb->tail = 0;
	rb->count = 0;
}

static uint8_t Increase(uint16_t x)
{
	 return (x + 1) % RING_MAX_SIZE;
}

static bool isFull(volatile Ringbuffer * rb)
{
	return rb->count == RING_MAX_SIZE;
}

static bool isEmpty(volatile Ringbuffer * rb)
{
	return rb->count == 0;
}

void enQueue(volatile Ringbuffer *rb, Line data)
{
    if (!isFull(rb))
    {
        rb->buffer[rb->tail] = data;
        rb->tail = Increase(rb->tail);
        rb->count++;
    }
    else
    {
        PRINTF("Queue is full, cannot add data\n");
    }
}

Line deQueue(volatile Ringbuffer *rb)
{
    Line value = {0};
    if (!isEmpty(rb))
    {
        value = rb->buffer[rb->head];
        rb->head = Increase(rb->head);
        rb->count--;
    }
    else
    {
        PRINTF("Queue is empty, cannot dequeue\n");
    }
    return value;
}

void print_Queue(Ringbuffer *rb)
{
	if(isEmpty(rb))
	{
		PRINTF("Queue is Empty!");
		return;
	}
	PRINTF("Current Queue: ");
	uint16_t index = rb->head;
	while(index != rb->tail)
	{
		PRINTF("%d ",rb->buffer[index]);
		index = (index  + 1 ) % RING_MAX_SIZE;
	}
	PRINTF("\r\n");
}

uint16_t queueSize(Ringbuffer *rb)
{
	return rb->count;
}
