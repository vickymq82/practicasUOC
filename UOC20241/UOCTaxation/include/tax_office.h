#ifndef __TAX_OFFICE_H__
#define __TAX_OFFICE_H__

#include "invoice.h"
#define MAX_OFFICE_CODE 8

// Tax Inspection Office
typedef struct _tTaxOffice {    
    char office_code[MAX_OFFICE_CODE + 1];  // Unique identifier for the tax office
    tRentInvoiceData rentInvoices;  // Data structure managing all rent invoices   
   
} tTaxOffice;

// Tax Inspection Office list node
typedef struct _tTaxOfficeNode {    
    tTaxOffice elem;
    struct _tTaxOfficeNode *next;
} tTaxOfficeNode;

// Tax Inspection Office list
typedef struct _tTaxOfficeList {    
    tTaxOfficeNode* first;  // Pointer to the first tax office in the list
    int count;               // Number of tax offices in the list
} tTaxOfficeList;

// Initialize a tax office
void taxOffice_init(tTaxOffice* office, const char* office_code);

// Release a tax office's data
void taxOffice_free(tTaxOffice* office);

// Initialize a list of tax offices
void taxOfficeList_init(tTaxOfficeList* list);

// Release a list of tax offices
void taxOfficeList_free(tTaxOfficeList* list);

// Insert a new tax office
void taxOfficeList_insert(tTaxOfficeList* list, const char* office_code);

// Find a tax office
tTaxOffice* taxOfficeList_find(tTaxOfficeList* list, const char* office_code);

// Check if an office code is valid
bool check_office_code(const char* office_code);


#endif // __TAX_OFFICE_H__
