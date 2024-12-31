#ifndef __INVOICE_H__
#define __INVOICE_H__

#include "date.h"
#include "error.h"
#include <stdbool.h>
#include "tenant.h"


// Invoice structure holding information about rent and cadastral reference.
typedef struct _tRentInvoice {   
    float rent;
    char cadastral_ref[MAX_CADASTRAL_REF + 1];   
} tRentInvoice;

typedef struct _tRentInvoiceNode {    
    tRentInvoice elem;
    struct _tRentInvoiceNode* next;
} tRentInvoiceNode;

// Monthly Rent Invoice
typedef struct _tRentInvoiceMonthly {    
    tDate month;
    tRentInvoiceNode* first;
    int count;
    struct _tRentInvoiceMonthly* next;
} tRentInvoiceMonthly;

// Invoice rent data
typedef struct _tRentInvoiceData {        
    tRentInvoiceMonthly* first;
    int count;
} tRentInvoiceData;


// Initialize an invoice list
void invoiceList_init(tRentInvoiceData* list);

// Modify the rent of a certain invoice
void invoiceList_update(tRentInvoiceData* list, tDate startMonthDate, tDate endMonthDate, char * cadastral_ref, float rent);

// Get the rent amount for a certain invoice and date
float getInvoiceMonthly(tRentInvoiceData* data, tDate date);

// Release a list of invoices
void invoiceList_free(tRentInvoiceData * list);

// AUX METHODS

// Initialize an invoice element
void invoice_init(tRentInvoice* invoice, float rent, const char* cadastral_ref);

// Get the rent amount for a certain invoice and date
float invoiceList_getRentAmount(tRentInvoiceData* list, tDate date, tRentInvoice* invoice);

// Initialize an invoice node element
void invoiceNode_init(tRentInvoiceNode* node, float rent, const char* cadastral_ref);

// Initialize a monthly invoice element
void monthlyInvoice_init(tRentInvoiceMonthly* invoice, tDate date);

// Remove a monthly invoice element data
void monthlyInvoice_free(tRentInvoiceMonthly* invoice);

// Function to find a monthly invoice by date
tRentInvoiceMonthly* findMonthlyInvoiceByDate(tRentInvoiceData* list, tDate date) ;

// Function to find a monthly invoices by Cadastral reference, oldest invoice in the first position
tRentInvoiceData findMonthlyInvoiceByCadastralRef (tRentInvoiceData* list, char* cadastral_ref) ;

// Function to find a monthly invoices by Cadastral reference, oldest invoice in the last position
tRentInvoiceData findMonthlyInvoiceByCadastralRef_Reverse (tRentInvoiceData* list, char* cadastral_ref) ;

// Sort the invoice list according to the total rent of the month, highest total rent in the first position
void sortMonthlyInvoicebyRent(tRentInvoiceData* list);

// Sort the invoice list according to the date of the invoices, oldest invoice in the first position
void sortMonthlyInvoicebyDate(tRentInvoiceData* list);

// Print on the screen the information of an invoice list
void printRentInvoiceData(tRentInvoiceData* list);

// Print on the screen the information of a Node of a list of rent invoices
void printRentInvoiceNode(tRentInvoiceNode* node);

///// AUX Methods: Test PR2 //////

// Structure for testing to represent expected invoice data for a month
typedef struct {
    int invoiceCount;
    struct {
        char cadastral_ref[MAX_CADASTRAL_REF + 1];
        float rent;
    } invoices[30]; // Adjust size as needed
} ExpectedInvoices;

// Release a list of invoices
void invoiceList_free(tRentInvoiceData* list);

int testVerifySpecificDate(tRentInvoiceData* invoiceList, const char* dateStr, ExpectedInvoices* expectedInvoices);

///// AUX Methods: Top-down design //////

//Retrieves the last rent invoice from a linked list of rent invoices.
tRentInvoiceMonthly* getLastRentInvoice(tRentInvoiceData* list);

// Update the rent amount for a given invoice
void monthlyInvoice_update(tRentInvoiceMonthly* invoice, char* cadastral_ref, float rent);

// Copy the contents from source to destination
void monthlyInvoice_copy(tRentInvoiceMonthly* src, tRentInvoiceMonthly* dst, char * cadastral_ref, float rent);

// Find the monthly invoice for a given date
tRentInvoiceMonthly* invoiceList_find(tRentInvoiceData* list, tDate date);

// Extend the list adding empty month cells on left
void invoiceList_expandLeft(tRentInvoiceData* list, tDate start_date, tDate end_date, char * cadastral_ref, float rent);

// Extend the list to the right os the start of contract
void invoiceList_expandRight(tRentInvoiceData* list, tDate start_date, tDate end_date, char * cadastral_ref, float rent);

// Get the rent amount for a certain invoice and date
float invoiceList_getRent(tRentInvoiceData* list, char * cadastral_ref, tRentInvoice* invoice);


#endif 