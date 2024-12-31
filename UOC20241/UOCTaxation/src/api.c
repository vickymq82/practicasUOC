#include <stdio.h>
#include <assert.h>
#include "csv.h"
#include "api.h"

#include <string.h>


#define FILE_READ_BUFFER_SIZE 2048

// Get the API version information
const char* api_version() {
    return "UOC PP 20241";
}

// Load data from a CSV file. If reset is true, remove previous data
tApiError api_loadData(tApiData* data, const char* filename, bool reset) {
    tApiError error;
    FILE *fin;    
    char buffer[FILE_READ_BUFFER_SIZE];
    tCSVEntry entry;
    
    // Check input data
    assert( data != NULL );
    assert(filename != NULL);
    
    // Reset current data    
    if (reset) {
        // Remove previous information
        error = api_freeData(data);
        if (error != E_SUCCESS) {
            return error;
        }
        
        // Initialize the data
        error = api_initData(data);
        if (error != E_SUCCESS) {
            return error;
        }
    }

    // Open the input file
    fin = fopen(filename, "r");
    if (fin == NULL) {
        return E_FILE_NOT_FOUND;
    }
    
    // Read file line by line
    while (fgets(buffer, FILE_READ_BUFFER_SIZE, fin)) {
        // Remove new line character     
        buffer[strcspn(buffer, "\n\r")] = '\0';
        
        csv_initEntry(&entry);
        csv_parseEntry(&entry, buffer, NULL);
        // Add this new entry to the api Data
        error = api_addDataEntry(data, entry);
        if (error != E_SUCCESS) {
            return error;
        }
        csv_freeEntry(&entry);

    }
    
    fclose(fin);
    
    return E_SUCCESS;
}

// Initialize the data structure
tApiError api_initData(tApiData* data) {            
    //////////////////////////////////
    // Ex PR1 2b
    /////////////////////////////////
    // Check input data structure
    assert(data != NULL);
    
    // Initialize data structures
    tenantData_init(&(data->tenants));
    landlords_init(&(data->landlords));
    rentalIncomes_init(&(data->rentalIncomes));
	
	//////////////////////////////////
    // Ex PR2 3b
    /////////////////////////////////
	taxOfficeList_init(&(data->taxOffices));
    /////////////////////////////////
    

    
    return E_SUCCESS;
    
    /////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a tenant into the data if it does not exist
tApiError api_addTenant(tApiData* data, tCSVEntry entry) {
    //////////////////////////////////
    // Ex PR1 2c
    /////////////////////////////////
    tTenant tenant;
	
	//////////////////////////////////
    // Ex PR2 3c
    ///////////////////////////////// 
	tTaxOffice * pTaxOffice;
    /////////////////////////////////

    
    // Check input data structure
    assert(data != NULL);
    
    // Check the entry type
    if (strcmp(csv_getType(&entry), "TENANT") != 0) {
        return E_INVALID_ENTRY_TYPE;
    }
    
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_TENANT) {
        return E_INVALID_ENTRY_FORMAT;
    }
    
    // Parse a tenant
    tenant_parse(&tenant, entry);
    
    // Check if the tenant already exists
    if (tenantData_find(data->tenants, tenant.tenant_id) >= 0) {
        // Release the allocated memory
        tenant_free(&tenant);
        
        return E_TENANT_DUPLICATED;
    }
    
    // Add the tenant into the data
    tenantData_add(&(data->tenants), tenant);
	
	//////////////////////////////////
    // Ex PR2 3c
    /////////////////////////////////
	
    pTaxOffice = taxOfficeList_find(&(data->taxOffices), tenant.postal_code);
    if (pTaxOffice == NULL) {
		taxOfficeList_insert(&data->taxOffices,tenant.postal_code);     
       
        pTaxOffice = taxOfficeList_find(&(data->taxOffices), tenant.postal_code);
    }
	invoiceList_update(&pTaxOffice->rentInvoices, tenant.start_date, tenant.end_date, tenant.cadastral_ref, tenant.rent);		

    /////////////////////////////////

    
    // Release the allocated memory
    tenant_free(&tenant);
    
    return E_SUCCESS;
    /////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a landlord if it does not exist
tApiError api_addLandlord(tApiData* data, tCSVEntry entry) {
    //////////////////////////////////
    // Ex PR1 2d
    /////////////////////////////////
    tLandlord landlord;
    
    // Check input data structure
    assert(data != NULL);
    
    // Check the entry type
    if (strcmp(csv_getType(&entry), "LANDLORD") != 0) {
        return E_INVALID_ENTRY_TYPE;
    }
    
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_LANDLORD) {
        return E_INVALID_ENTRY_FORMAT;
    }
    
    // Initialize the landlord
    landlord_init(&landlord);
    
    // Parse the landlord
    landlord_parse(&landlord, entry);
    
    // Check if the landlord already exists
    if (landlords_find(data->landlords, landlord.id) >= 0) {
        // Release the memory
        landlord_free(&landlord);
        
        return E_LANDLORD_DUPLICATED;
    }
    
    // Insert the landlord
    landlords_add(&(data->landlords), landlord);
    
    // Release the memory
    landlord_free(&landlord);
    
    return E_SUCCESS;
    /////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a property into the properties of an specific landlord
tApiError api_addProperty(tApiData* data, tCSVEntry entry) {
    //////////////////////////////////
    // Ex PR1 2e
    /////////////////////////////////
    tProperty property;
    
    // Check input data structure
    assert(data != NULL);
    
    // Check the entry type
    if (strcmp(csv_getType(&entry), "PROPERTY") != 0) {
        return E_INVALID_ENTRY_TYPE;
    }
    
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_PROPERTY) {
        return E_INVALID_ENTRY_FORMAT;
    }
    
    // Parse the property
    property_parse(&property, entry);
    
    // Check if the landlord exist
    if (landlords_find(data->landlords, property.landlord_id) < 0) {
        return E_LANDLORD_NOT_FOUND;
    }
    
    // Check if the property already exists
    if (landlords_find_by_cadastral_ref(data->landlords, property.cadastral_ref) >= 0) {
        return E_PROPERTY_DUPLICATED;
    }
    
    // Add the property to the landlord
    landlord_add_property(&(data->landlords), property);
    
    // No release data because it does not use allocated memory
    
    return E_SUCCESS;
    /////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Add a rental income into a list if the landlord already exists
tApiError api_addRentalIncome(tApiData* data, tCSVEntry entry) {
    //////////////////////////////////
    // Ex PR1 2f
    /////////////////////////////////
    char document[MAX_PERSON_ID + 1];
    int idx;
    tRentalIncome rentalIncome;
    
    // Check input data structure
    assert(data != NULL);
    
    // Check the entry type
    if (strcmp(csv_getType(&entry), "RENTAL_INCOME") != 0) {
        return E_INVALID_ENTRY_TYPE;
    }
    
    // Check the number of fields
    if(csv_numFields(entry) != NUM_FIELDS_RENTAL_INCOME) {
        return E_INVALID_ENTRY_FORMAT;
    }
    
    // Get the document id
    csv_getAsString(entry, 2, document, MAX_PERSON_ID + 1);
    
    // Check if the landlord exist
    idx = landlords_find(data->landlords, document);
    if (idx < 0) {
        return E_LANDLORD_NOT_FOUND;
    }
    
    // Parse the information of the rental income
    rentalIncome_parse(&rentalIncome, entry);
    
    // Point the landlord of the rental income to the landlord of the vector
    rentalIncome.landlord = &(data->landlords.elems[idx]);
    
    // Insert the rental income into the list
    rentalIncomes_add(&(data->rentalIncomes), rentalIncome);
    
    // No release data because it does not use allocated memory
    
    return E_SUCCESS;
    /////////////////////////////////
    // return E_NOT_IMPLEMENTED;
}

// Find a rental income by year and landlord document id
tRentalIncome* rentalIncomes_find(tRentalIncomeList list, int year, const char* document_id) {
    //////////////////////////////////
    // Ex PR1 2g
    /////////////////////////////////
    tRentalIncomeListNode *pNode = NULL;
    tRentalIncome *rentalIncome = NULL;
    
    // Check input data (Pre-conditions)
    assert(document_id != NULL);
    
    rentalIncome = NULL;
    pNode = list.first;
    
    while (pNode != NULL && rentalIncome == NULL) {
        if (pNode->elem.year == year && strcmp(pNode->elem.landlord->id, document_id) == 0) {
            rentalIncome = &(pNode->elem);
        }
        
        pNode = pNode->next;
    }
    
    return rentalIncome;
    /////////////////////////////////
    // return NULL;
}

// Get the number of tenants registered on the application
int api_tenantCount(tApiData data) {
    //////////////////////////////////
    // Ex PR1 2h
    /////////////////////////////////
    return tenantData_len(data.tenants);
    /////////////////////////////////
    //return -1;
}


// Get the number of landlords registered on the application
int api_landlordsCount(tApiData data) {
    //////////////////////////////////
    // Ex PR1 2h
    /////////////////////////////////
    return landlords_len(data.landlords);    
    /////////////////////////////////
    //return -1;
}

// Get the number of properties in all landlords registered on the application
int api_propertiesCount(tApiData data) {
    //////////////////////////////////
    // Ex PR1 2h
    /////////////////////////////////
	return landlords_propertiesCount(data.landlords);    
    /////////////////////////////////
    //return -1;
}

// Get the number of rental incomes registered
int api_rentalIncomesCount(tApiData data) {
    //////////////////////////////////
    // Ex PR1 2h
    /////////////////////////////////
	return rentalIncomes_len(data.rentalIncomes);    
    /////////////////////////////////
    //return -1;
}

// Get the number of health centers registered on the application
int api_taxOfficeCount(tApiData data) {
    //////////////////////////////////
    // Ex PR2 3e
    
    return data.taxOffices.count;
    
    /////////////////////////////////
    // return -1;
}


// Free all used memory
tApiError api_freeData(tApiData* data) {
    //////////////////////////////////
    // Ex PR1 2i
    /////////////////////////////////
    tenantData_free(&(data->tenants));
    landlords_free(&(data->landlords));
    rentalIncomes_free(&(data->rentalIncomes));  
    //////////////////////////////////
    // Ex PR2 3d
    /////////////////////////////////  
    taxOfficeList_free(&(data->taxOffices)); 
	/////////////////////////////////
    return E_SUCCESS;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}


// Add a new entry
tApiError api_addDataEntry(tApiData* data, tCSVEntry entry) { 
    //////////////////////////////////
    // Ex PR1 2j
    /////////////////////////////////
    assert(data != NULL);

    if (strcmp(csv_getType(&entry), "TENANT") == 0) {
        // Add a tenant
        return api_addTenant(data, entry);
	} else if (strcmp(csv_getType(&entry), "LANDLORD") == 0) {
        // Add winegrower
        return api_addLandlord(data, entry);   
    } else if (strcmp(csv_getType(&entry), "PROPERTY") == 0) {
        // Add a property
        return api_addProperty(data, entry);
	} else if (strcmp(csv_getType(&entry), "RENTAL_INCOME") == 0) {
        // Add vineyard plot
        return api_addRentalIncome(data, entry);           
    } else {
        return E_INVALID_ENTRY_TYPE;
    }
    return E_SUCCESS;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Get landlord data
tApiError api_getLandlord(tApiData data, const char *id, tCSVEntry *entry) {
    //////////////////////////////////
    // Ex PR1 3a
    /////////////////////////////////
    char buffer[2048];
    
    tLandlord* landlord = NULL;
    int idx;
        
    assert(id != NULL);
    assert(entry != NULL);
    
    // Search the landlord
    idx = landlords_find(data.landlords, id);
	
	if (idx < 0) {
		return E_LANDLORD_NOT_FOUND;
	}
	
    landlord = &(data.landlords.elems[idx]);
    
    // Print data in the buffer
    sprintf(buffer, "%s;%s;%.1f", landlord->name, landlord->id, landlord->tax);
    // Initialize the output structure
    csv_initEntry(entry);
    csv_parseEntry(entry, buffer, "LANDLORD");
    
    return E_SUCCESS;
    
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED; 
}

// Get the rental income by year of a landlord
tApiError api_getRentalIncome(tApiData data, int year, const char* id, tCSVEntry *entry) {
    //////////////////////////////////
    // Ex PR1 3b
    /////////////////////////////////
    char buffer[2048];    
	tRentalIncome *rentalIncome= NULL; 

    assert(id != NULL);
    assert(entry != NULL);
    
    rentalIncome = rentalIncomes_find(data.rentalIncomes, year, id);
        
    if (rentalIncome == NULL) {
        return E_RENTAL_INCOME_NOT_FOUND;
    }

    // Print data in the buffer
    sprintf(buffer, "%d;%.1f;%s", 
        rentalIncome->year,
        rentalIncome->totalIncome,
        rentalIncome->landlord->id
    );
    // Initialize the output structure
    csv_initEntry(entry);
    csv_parseEntry(entry, buffer, "RENTAL_INCOME");
    
    return E_SUCCESS;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED; 
}

// Get registered properties
tApiError api_getProperties(tApiData data, tCSVData *properties) {
    //////////////////////////////////
    // Ex PR1 3c
    /////////////////////////////////
    char buffer[2048];
    tProperty *property;
    
    csv_init(properties);
    
    for (int i = 0; i < data.landlords.count; i++) {
        for (int j = 0; j < data.landlords.elems[i].properties.count; j++) {
            property = &(data.landlords.elems[i].properties.elems[j]);
            sprintf(buffer, "%s;%s;%d;%s", 
                property->cadastral_ref,
                property->address.street,
                property->address.number,
                property->landlord_id
            );
            
            csv_addStrEntry(properties, buffer, "PROPERTY");
        }
    }
    
    return E_SUCCESS;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}

// Get monthly invoices by cadastral reference, oldest invoice in first position
tApiError api_getMonthlyInvoiceByCadastralRef(tApiData data, char* cadastral_ref ,tCSVData *invoices) {
    // PR3 4a
    
    return E_NOT_IMPLEMENTED;     
}

// Get monthly invoices by cadastral reference, oldest invoice in first position
tApiError api_getMonthlyInvoiceByCadastralRef_Reverse(tApiData data, char* cadastral_ref ,tCSVData *invoices) {
    
    return E_NOT_IMPLEMENTED;  
}

// Get monthly invoices of a Tax office, month sorted according to total rent, month with the highest total rent first
tApiError api_getMonthlyInvoicebyRent(tApiData data, char* office_code, tCSVData *invoices) {
    // PR3 4c
    
    
    return E_NOT_IMPLEMENTED; 
}

// Get the address of a cadastral reference
tApiError api_getAddressByCadastralRef (tApiData data, char* cadastral_ref, tCSVEntry *address) {
    // PR3 4d
    
    return E_NOT_IMPLEMENTED; 
}

// Sort list of landlorda by Name and properties by cadastral reference, from low to high
tApiError api_sortLandlordsByName(tApiData *data) {
    // PR3 4e
    
    return E_NOT_IMPLEMENTED;
}

// Find the latest tenant of a property 
tApiError api_findLatestTenant(tApiData data, char* cadastral_ref, tCSVEntry *tenant ) {
    // PR3 4f
    
    return E_NOT_IMPLEMENTED;
}

// Find the first tenant of a property 
tApiError api_findFirstTenant(tApiData data, char* cadastral_ref, tCSVEntry *tenant) {
    // PR3 4g
    
    
    return E_NOT_IMPLEMENTED;
}

// Sort list of tenants by id
tApiError api_sortTenantsById(tApiData *data) {
    // PR3 4h
    
    
    return E_NOT_IMPLEMENTED;
}


// Get registered rental incomes
tApiError api_getRentalIncomes(tApiData data, tCSVData *rentalIncomes) {
    //////////////////////////////////
    // Ex PR1 3d
    /////////////////////////////////
    char buffer[2048];
    tRentalIncomeListNode *pNode = NULL;
    
    csv_init(rentalIncomes);
        
    pNode = data.rentalIncomes.first;
    while(pNode != NULL) {
        sprintf(buffer, "%d;%.2f;%s", 
            pNode->elem.year,
            pNode->elem.totalIncome,
            pNode->elem.landlord->id
        );

        csv_addStrEntry(rentalIncomes, buffer, "RENTAL_INCOME");
        pNode = pNode->next;
    }    
    
    return E_SUCCESS;
    /////////////////////////////////
    //return E_NOT_IMPLEMENTED;
}
