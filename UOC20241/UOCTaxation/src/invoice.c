#include "tenant.h"
#include "invoice.h"
#include "date.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


// Initialize an invoice list
void invoiceList_init(tRentInvoiceData * list) {
    // PR2 Ex 1a
    assert(list != NULL);
    list -> first = NULL;
    list -> count = 0;
}

// Function to update or add a tenant's rent across their tenancy period
void invoiceList_update(tRentInvoiceData * list, tDate startMonthDate, tDate endMonthDate, char * cadastral_ref, float rent) {
    // PR2 Ex 1b
    tRentInvoiceMonthly * pNode;
    tRentInvoiceMonthly * last;

    assert(list != NULL);
    assert(cadastral_ref != NULL);

    startMonthDate.day = 1;
    endMonthDate.day = 1;

    // If the list is empty, just add a new element	
    if (list -> count == 0) {
        // Create the new element
        list -> first = (tRentInvoiceMonthly * ) malloc(sizeof(tRentInvoiceMonthly));
        assert(list -> first != NULL);

        list -> count = 1;
        // Initialize the new element
        monthlyInvoice_init(list -> first, startMonthDate);
        assert(list -> first -> next == NULL);
        pNode = list -> first -> next;
        date_addMonth( & startMonthDate, 1);
        // Update the rent
        monthlyInvoice_update(list -> first, cadastral_ref, rent);

    }

    //else {
    last = getLastRentInvoice(list);
    // Expandir la lista para cubrir el período de alquiler del inquilino
    if (date_cmp(list -> first -> month, startMonthDate) > 0) {
        // La fecha de inicio del inquilino es antes de la fecha más temprana en la lista
        tDate penultimateMonth = list -> first -> month;
        date_addMonth( & penultimateMonth, -1);
        invoiceList_expandLeft(list, startMonthDate, penultimateMonth, cadastral_ref, rent);
        // Set start position for update the first element
        pNode = list -> first;

    } 
    
    if (date_cmp(last -> month, endMonthDate) > 0) {
        // Date is in the range of dates we already have. We will start updating on provided date.
        pNode = invoiceList_find(list, startMonthDate);
        assert(pNode != NULL);
    } else {
        // La fecha de finalización del inquilino es después de la última fecha en la lista
        invoiceList_expandRight(list, startMonthDate, endMonthDate, cadastral_ref, rent);
        //last = getLastRentInvoice(list);
        //pNode = last;
        pNode = invoiceList_find(list, startMonthDate);
    }

    // Update all invoices from the pNode position to the end month date  
    while (pNode != NULL && date_cmp(pNode -> month, endMonthDate) <= 0) {
        monthlyInvoice_update(pNode, cadastral_ref, rent);
        pNode = pNode -> next;
    }

}

// Get the rent amount for a certain invoice and date
float getInvoiceMonthly(tRentInvoiceData * data, tDate date) {
    // PR2 Ex 1c
    assert(data != NULL);

    // Normalize the date by setting the day to 1
    date.day = 1;

    // Find the monthly invoice for the given date
    tRentInvoiceMonthly * monthlyInvoice = findMonthlyInvoiceByDate(data, date);
    if (monthlyInvoice == NULL) {
        // No invoices for this date
        return 0.0f;
    }

    // Sum up the rent amounts
    float totalRent = 0.0f;
    tRentInvoiceNode * currentInvoiceNode = monthlyInvoice -> first;
    while (currentInvoiceNode != NULL) {
        totalRent += currentInvoiceNode -> elem.rent;
        currentInvoiceNode = currentInvoiceNode -> next;
    }

    return totalRent;
}

// Release a list of invoices
void invoiceList_free(tRentInvoiceData * list) {
    // PR2 Ex 1d
    assert(list != NULL);
    tRentInvoiceMonthly * current = list -> first;
    while (current != NULL) {
        tRentInvoiceMonthly * next = current -> next;
        monthlyInvoice_free(current);
        free(current);
        current = next;
    }
    list -> first = NULL;
    list -> count = 0;
}


// Initialize an invoice element
void invoice_init(tRentInvoice * invoice, float rent,
    const char * cadastral_ref) {
    invoice -> rent = rent;
    strncpy(invoice -> cadastral_ref, cadastral_ref, MAX_CADASTRAL_REF);
    invoice -> cadastral_ref[MAX_CADASTRAL_REF] = '\0';
}

// Initialize an invoice node element
void invoiceNode_init(tRentInvoiceNode * node, float rent,
    const char * cadastral_ref) {
    assert(node != NULL);
    invoice_init( & node -> elem, rent, cadastral_ref);
    node -> next = NULL;
}

// Initialize a monthly invoice element
void monthlyInvoice_init(tRentInvoiceMonthly * invoice, tDate date) {
    assert(invoice != NULL);
    invoice -> month = date;
    invoice -> first = NULL;
    invoice -> count = 0;
    invoice -> next = NULL;
}

// Remove a monthly invoice element data
void monthlyInvoice_free(tRentInvoiceMonthly * invoice) {
    assert(invoice != NULL);
    tRentInvoiceNode * current = invoice -> first;
    while (current != NULL) {
        tRentInvoiceNode * next = current -> next;
        free(current);
        current = next;
    }
    invoice -> first = NULL;
    invoice -> count = 0;
}

// Function to find a monthly invoice by date
tRentInvoiceMonthly * findMonthlyInvoiceByDate(tRentInvoiceData * list, tDate date) {
    assert(list != NULL);

    tRentInvoiceMonthly * current = list -> first;
    while (current != NULL) {
        int cmpResult = date_cmp(current -> month, date);
        if (cmpResult == 0) {
            // Found the monthly invoice for the specified date
            return current;
        } else if (cmpResult > 0) {
            // Since the list is ordered chronologically, no need to continue
            break;
        }
        current = current -> next;
    }
    // Monthly invoice for the specified date not found
    return NULL;
}

// Function to find a monthly invoices by Cadastral reference, oldest invoice in the first position
tRentInvoiceData findMonthlyInvoiceByCadastralRef (tRentInvoiceData* list, char* cadastral_ref) {
    // PR3 Ex 1a
    tRentInvoiceData sortedList;
    
    invoiceList_init( &sortedList);
    sortedList.count = -1;

    return sortedList;
}

// Function to find a monthly invoices by Cadastral reference, oldest invoice in the last position
tRentInvoiceData findMonthlyInvoiceByCadastralRef_Reverse (tRentInvoiceData* list, char* cadastral_ref) {
    // PR3 Ex1b
    
    tRentInvoiceData sortedList;
    
    invoiceList_init( &sortedList);
    sortedList.count = -1;

    return sortedList;
}

// Sort the invoice list according to the total rent of the month, highest total rent in the first position
void sortMonthlyInvoicebyRent(tRentInvoiceData* list) {
    //PR3 1c
    
    list->count = -1;
}

// Sort the invoice list according to the date of the invoices, oldest invoice in the first position
void sortMonthlyInvoicebyDate(tRentInvoiceData* list) {
    //PR3 1d
    
    list->count = -1;
}

// Print on the screen the information of an invoice list
void printRentInvoiceData(tRentInvoiceData * list) {
    assert(list != NULL);
    tRentInvoiceMonthly * current = list -> first;
    while (current != NULL) {
        printf("Month: %d-%d\n", current -> month.year, current -> month.month);
        printRentInvoiceNode(current -> first);
        current = current -> next;
    }
}

// Print on the screen the information of a Node of a list of rent invoices
void printRentInvoiceNode(tRentInvoiceNode * node) {
    assert(node != NULL);
    while (node != NULL) {
        printf("Cadastral Ref: %s, Rent: %.2f\n", node -> elem.cadastral_ref, node -> elem.rent);
        node = node -> next;
    }
}

/////////////////////////////////////////
///// AUX Methods: Test PR2		   //////
/////////////////////////////////////////

// Function to verify invoices within a monthly invoice node
bool verifyMonthlyInvoices(tRentInvoiceMonthly * monthlyInvoice, ExpectedInvoices * expectedInvoices) {
    assert(monthlyInvoice != NULL);
    assert(expectedInvoices != NULL);

    // Verify the number of invoices
    if (monthlyInvoice -> count != expectedInvoices -> invoiceCount) {
        return false;
    }

    tRentInvoiceNode * currentInvoiceNode = monthlyInvoice -> first;
    int invoiceIndex = 0;

    while (currentInvoiceNode != NULL && invoiceIndex < expectedInvoices -> invoiceCount) {
        // Verify cadastral_ref and rent
        if (strcmp(currentInvoiceNode -> elem.cadastral_ref, expectedInvoices -> invoices[invoiceIndex].cadastral_ref) != 0 ||
            currentInvoiceNode -> elem.rent != expectedInvoices -> invoices[invoiceIndex].rent) {

            return false;
        }
        currentInvoiceNode = currentInvoiceNode -> next;
        invoiceIndex++;
    }

    // Check if there are extra invoices
    if (currentInvoiceNode != NULL || invoiceIndex != expectedInvoices -> invoiceCount) {
        return false;
    }

    // All invoices match
    return true;
}

int testVerifySpecificDate(tRentInvoiceData * invoiceList,
    const char * dateStr, ExpectedInvoices * expectedInvoices) {
    tDate dateToVerify;
    date_parse( & dateToVerify, dateStr);
    dateToVerify.day = 1;
    int passed = 0;
    tRentInvoiceMonthly * monthlyInvoice = findMonthlyInvoiceByDate(invoiceList, dateToVerify);

    if (monthlyInvoice == NULL) {

    }

    if (verifyMonthlyInvoices(monthlyInvoice, expectedInvoices)) {
        passed = 1;
    } else {

    }
    return passed;
}



/////////////////////////////////////////
///// AUX Methods: Top-down design //////
/////////////////////////////////////////

// Retrieves the last rent invoice from a linked list of rent invoices.
tRentInvoiceMonthly * getLastRentInvoice(tRentInvoiceData * list) {
    // Ensure the list pointer is not NULL and the list is not empty
    if (list == NULL || list -> count == 0) {
        return NULL; // The list is empty or NULL
    }

    // Initialize the current node to the first invoice
    tRentInvoiceMonthly * currentNode = list -> first;

    // Iterate through the list until the last invoice is reached
    while (currentNode -> next != NULL) {
        currentNode = currentNode -> next;
    }

    return currentNode; // Return the last invoice node
}

// Update the rent amount for a given invoice
void monthlyInvoice_update(tRentInvoiceMonthly * invoice, char * cadastral_ref, float rent) {
    tRentInvoiceNode * current = invoice -> first;
    tRentInvoiceNode * prev = NULL;

    // Search for the correct position to insert, maintaining order by cadastral_ref
    while (current != NULL && strcmp(current -> elem.cadastral_ref, cadastral_ref) < 0) {
        prev = current;
        current = current -> next;
    }

    if (current != NULL && strcmp(current -> elem.cadastral_ref, cadastral_ref) == 0) {
        // The invoice already exists, update the rent
        current -> elem.rent = rent;
    } else {
        // Create a new invoice node
        tRentInvoiceNode * newNode = (tRentInvoiceNode * ) malloc(sizeof(tRentInvoiceNode));
        assert(newNode != NULL);
        invoice_init( & newNode -> elem, rent, cadastral_ref);

        // Insert the new node into the list, maintaining order
        if (prev == NULL) {
            // Insert at the beginning
            newNode -> next = invoice -> first;
            invoice -> first = newNode;
        } else {
            // Insert between prev and current
            prev -> next = newNode;
            newNode -> next = current;
        }
        invoice -> count++;
    }
}

// Copy the contents from source to destination
void monthlyInvoice_copy(tRentInvoiceMonthly * src, tRentInvoiceMonthly * dst, char * cadastral_ref, float rent) {
    tRentInvoiceNode * pNode;

    // Ensure destination is initialized
    monthlyInvoice_init(dst, dst -> month);

    // Add vaccines from soruce to destination
    pNode = src -> first;
    while (pNode != NULL) {

        monthlyInvoice_update(dst, cadastral_ref, rent);
        pNode = pNode -> next;
    }

}

// Find the monthly invoice for a given date
tRentInvoiceMonthly * invoiceList_find(tRentInvoiceData * list, tDate date) {
    tRentInvoiceMonthly * pNode;
    tRentInvoiceMonthly * pDate;
    tRentInvoiceMonthly * last;
    assert(list != NULL);

    // Initialize the return pointer
    pDate = NULL;

    // Get the last monthly node in the list
    last = getLastRentInvoice(list);

    // Check if the list is not empty and the date is within the range of dates in the list
    if (list -> count > 0 && date_cmp(list -> first -> month, date) <= 0 && date_cmp(last -> month, date) >= 0) {
        pNode = list -> first;
        while (pNode != NULL && pDate == NULL) {
            if (date_cmp(pNode -> month, date) == 0) {
                // Point to the current node
                pDate = pNode;
            }
            pNode = pNode -> next;
        }
    }

    return pDate;
}

// Extend the invoice list to the left with the data of the first position
void invoiceList_expandLeft(tRentInvoiceData * list, tDate start_date, tDate end_date, char * cadastral_ref, float rent) {
    tDate currentMonth;
    tRentInvoiceMonthly * newMonthly;

    // Ensure the list is not empty
    assert(list -> first != NULL);

    currentMonth = end_date;

    // Iterate and add invoices until reaching the target date
    while (date_cmp(currentMonth, start_date) >= 0) {
        newMonthly = (tRentInvoiceMonthly * ) malloc(sizeof(tRentInvoiceMonthly));
        assert(newMonthly != NULL);

        // Initialize the new monthly invoice node
        monthlyInvoice_init(newMonthly, currentMonth);

        // Add the invoice for cadastral_ref and rent
        monthlyInvoice_update(newMonthly, cadastral_ref, rent);
        // Insert the new node at the beginning of the list
        newMonthly -> next = list -> first;
        list -> first = newMonthly;
        list -> count++;

        // Decrement the currentDate by one month
        date_addMonth( & currentMonth, -1);
    }
}

// Extend the list to the right os the start of contract
void invoiceList_expandRight(tRentInvoiceData * list, tDate start_date, tDate end_date, char * cadastral_ref, float rent) {
    tDate currentDate;
    tRentInvoiceMonthly * last = getLastRentInvoice(list);

    // Ensure the list is not empty
    assert(last != NULL);

    // Set currentDate to the month after the last invoice's date
    currentDate = last -> month;
    date_addMonth( & currentDate, 1);
    //currentDate = start_date;   

    // Iterate and add invoices until reaching the target date
    while (date_cmp(currentDate, end_date) <= 0) {
        // Allocate memory for a new monthly invoice
        last -> next = (tRentInvoiceMonthly * ) malloc(sizeof(tRentInvoiceMonthly));
        assert(last -> next != NULL);
        list -> count++;

        // Initialize the new invoice with the currentDate
        monthlyInvoice_init(last -> next, currentDate);

        // Copy the contents from the last invoice to the new invoice
        monthlyInvoice_copy(last, last -> next, cadastral_ref, rent);

        // Move to the newly added invoice
        last = last -> next;

        // Increment the currentDate by one month
        date_addMonth( & currentDate, 1);
    }
}

