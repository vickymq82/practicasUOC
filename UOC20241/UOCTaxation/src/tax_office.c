#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "tax_office.h"
// Initialize a tax office
void taxOffice_init(tTaxOffice * office,  const char * office_code) {
	// Ex PR3 2a
    assert(office != NULL);

    // Copy the office_code
    strcpy(office -> office_code, office_code);
    // Initialize the rent invoices
    invoiceList_init( &(office -> rentInvoices));

}

// Release a tax office's data
void taxOffice_free(tTaxOffice * office) {
	// Ex PR3 2b
   
    // Release rent invoices data
    invoiceList_free( &(office -> rentInvoices));
	office->office_code[0] = '\0';

}

// Initialize a list of tax offices
void taxOfficeList_init(tTaxOfficeList * list) {
	// Ex PR3 2c
    assert(list != NULL);

    list -> count = 0;
    list -> first = NULL;
}

// Check if an office code is valid
bool check_office_code(const char * office_code) {
	// Ex PR2 2d

    int length = 0;
    int i;

    // Ensure that office_code is not NULL
    assert(office_code != NULL);

    // Get the total length of the code
    length = strlen(office_code);

    // Verify that the length is 6 or 7
    if (length != 6 && length != 7) {
        return false;
    }

    // Determine the number of province characters
    int province_length = (length == 7) ? 2 : 1;

    // Verify that the first 'province_length' characters are uppercase letters
    for (i = 0; i < province_length; i++) {
        if (!isalpha(office_code[i]) || !isupper(office_code[i])) {
            return false;
        }
    }

    // Verify that the next 5 characters are digits
    for (i = province_length; i < province_length + 5; i++) {
        if (!isdigit(office_code[i])) {
            return false;
        }
    }

    return true;
}

// Insert a new tax office
void taxOfficeList_insert(tTaxOfficeList * list,  const char * office_code) {
	// Ex PR3 2e
    tTaxOfficeNode * pNode;
    tTaxOfficeNode * pAux;

    assert(list != NULL);

    // Check office code
    if (!check_office_code(office_code)) {
        // Do not add the office because parameters are wrong
        return;
    }

    if (taxOfficeList_find(list, office_code) == NULL) {
        // Check if insertion point is the first position
        if (list -> first == NULL || strcmp(list -> first -> elem.office_code, office_code) > 0) {
            // Insert as initial position
            pAux = list -> first;
            list -> first = (tTaxOfficeNode * ) malloc(sizeof(tTaxOfficeNode));
            assert(list -> first != NULL);
            list -> first -> next = pAux;
            taxOffice_init( & (list -> first -> elem), office_code);
        } else {
            // Search insertion point
            pAux = list -> first;
            pNode = pAux -> next;
            while (pNode != NULL && strcmp(pNode -> elem.office_code, office_code) > 0) {
                pAux = pNode;
                pNode = pNode -> next;
            }
            pAux -> next = (tTaxOfficeNode * ) malloc(sizeof(tTaxOfficeNode));
            assert(pAux -> next != NULL);
            pAux -> next -> next = pNode;
            taxOffice_init( & (pAux -> next -> elem), office_code);
        }
        // Increase the number of elements
        list -> count++;
    }
}

// Find a tax office
tTaxOffice * taxOfficeList_find(tTaxOfficeList * list,  const char * office_code) {
	// Ex PR3 2f
    tTaxOfficeNode * pNode;
    tTaxOffice * pOffice;

    assert(list != NULL);

    // Search office with provided office_code
    pNode = list -> first;
    pOffice = NULL;
    while (pNode != NULL && pOffice == NULL) {
        if (strcmp(office_code, pNode -> elem.office_code) == 0) {
            pOffice = & (pNode -> elem);
        }
        pNode = pNode -> next;
    }

    return pOffice;
}

// Release a list of tax offices
void taxOfficeList_free(tTaxOfficeList * list) {
	// Ex PR3 2g
    tTaxOfficeNode * pNode;
    tTaxOfficeNode * pAux;

    assert(list != NULL);

    // Remove all elements in the list
    pNode = list -> first;
    while (pNode != NULL) {
        taxOffice_free( & (pNode -> elem));
        pAux = pNode;
        pNode = pNode -> next;
        free(pAux);
    }

    list -> count = 0;
    list -> first = NULL;
}





