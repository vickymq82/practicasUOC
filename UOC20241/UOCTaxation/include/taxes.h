#ifndef __TAXES_H__
#define __TAXES_H__

#include <stdbool.h>

// Node of the tax queue
typedef struct _tTaxNode {
    float taxAmount;
    int month; // Month (1-12)
    struct _tTaxNode *next;
} tTaxNode;

// Queue of taxes assigned to a landlord
typedef struct _tTaxQueue {
    tTaxNode *front;
    tTaxNode *rear;
    int count;
} tTaxQueue;

// Initialize the tax queue
void taxQueue_init(tTaxQueue *queue);

// Check if the tax queue is empty
bool taxQueue_isEmpty(tTaxQueue queue);

// Return the number of elements in the tax queue
int taxQueue_len(tTaxQueue queue);

// Enqueue a tax into the queue
void taxQueue_enqueue(tTaxQueue *queue, float taxAmount, int month);

// Dequeue a tax from the queue
void taxQueue_dequeue(tTaxQueue *queue);

// Free the memory of the tax queue
void taxQueue_free(tTaxQueue *queue);

// Get a string representation of the tax queue
void taxQueue_toString(tTaxQueue queue, char *buffer, int bufferSize);

#endif // __TAXES_H__
