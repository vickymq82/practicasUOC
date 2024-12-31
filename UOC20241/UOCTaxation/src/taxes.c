#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taxes.h"

// Initialize the tax queue
void taxQueue_init(tTaxQueue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
}

// Check if the tax queue is empty
bool taxQueue_isEmpty(tTaxQueue queue) {
    return queue.count == 0;
}

// Return the number of elements in the tax queue
int taxQueue_len(tTaxQueue queue) {
    return queue.count;
}

// Enqueue a tax into the queue
void taxQueue_enqueue(tTaxQueue *queue, float taxAmount, int month) {
    tTaxNode *newNode = (tTaxNode *)malloc(sizeof(tTaxNode));
    if (newNode == NULL) {
        printf("Error allocating memory for a new tax node.\n");
        exit(1);
    }
    newNode->taxAmount = taxAmount;
    newNode->month = month;
    newNode->next = NULL;
    if (taxQueue_isEmpty(*queue)) {
        queue->front = newNode;
    } else {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
    queue->count++;
}

// Dequeue a tax from the queue
void taxQueue_dequeue(tTaxQueue *queue) {
    if (taxQueue_isEmpty(*queue)) {
        printf("The tax queue is empty.\n");
        return;
    }
    tTaxNode *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->count--;
}

// Free the memory of the tax queue
void taxQueue_free(tTaxQueue *queue) {
    while (!taxQueue_isEmpty(*queue)) {
        taxQueue_dequeue(queue);
    }
}

// Get a string representation of the tax queue
void taxQueue_toString(tTaxQueue queue, char *buffer, int bufferSize) {
    tTaxNode *current = queue.front;
    char temp[256];
    buffer[0] = '\0';
    while (current != NULL) {
        snprintf(temp, sizeof(temp), "Month: %d, Tax: %.2f\n", current->month, current->taxAmount);
        strncat(buffer, temp, bufferSize - strlen(buffer) - 1);
        current = current->next;
    }
}
