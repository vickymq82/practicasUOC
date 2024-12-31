#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tenant.h"

// Initialize a tenant
void tenant_init(tTenant *tenant) {
    // Check input data (Pre-conditions)
    assert(tenant != NULL);
    
    tenant->start_date.day = -1;
    tenant->start_date.month = -1;
    tenant->start_date.year = -1;
    
    tenant->end_date.day = -1;
    tenant->end_date.month = -1;
    tenant->end_date.year = -1;
    
    tenant->name = NULL;
    tenant->rent = -1.0;
    tenant->age = - 1;
}

// Initialize a tenant with values
void tenant_initialize(tTenant *tenant, const char* start_date, const char * end_date, const char *tenant_id, 
                      const char *name, float rent, int age, const char *cadastral_ref, const char *postal_code
                      ) {
						  
    // Assign start and end dates
	date_parse( &tenant->start_date, start_date);
	date_parse( &tenant->end_date, end_date);
    
    
    // Copy tenant_id to structure
	
    strcpy(tenant->tenant_id, tenant_id);

    // Allocate memory and copy name
    tenant->name = malloc(strlen(name) + 1);
    if (tenant->name != NULL) {
        strcpy(tenant->name, name);
    }
    
    // Assign other fields
    tenant->rent = rent;
    tenant->age = age;
    
    // Copy postal_code and cadastral_ref
    strcpy(tenant->postal_code, postal_code);
    strcpy(tenant->cadastral_ref, cadastral_ref);
}

// Copy a tenant
void tenant_cpy(tTenant *dst, tTenant src) {
    // Check input data (Pre-conditions)
    assert(dst != NULL);
    
    // Remove old data 
    tenant_free(dst);
    
    // Copy the start date
    date_cpy(&(dst->start_date), src.start_date);
    
    // Copy the end date
    date_cpy(&(dst->end_date), src.end_date);
    
    // Copy the tenant id
    strcpy(dst->tenant_id, src.tenant_id);
    
    // Copy the name
    if (dst->name == NULL) {
        dst->name = (char*) malloc((strlen(src.name) + 1) * sizeof(char));
    }
    assert(dst->name != NULL);
    strcpy(dst->name, src.name);
    
    // Copy the rent
    dst->rent = src.rent;
    
    // Copy the age
    dst->age = src.age;
    
    // Copy the cadastral_ref
    strcpy(dst->cadastral_ref, src.cadastral_ref);
	
	// Copy the postal_code
    strcpy(dst->postal_code, src.postal_code);
}

// Parse input from CSVEntry
void tenant_parse(tTenant* data, tCSVEntry entry) {
    char start_date[11];
    char end_date[11];
    
    // Check input data (Pre-conditions)
    assert(data != NULL);    
    assert(csv_numFields(entry) == NUM_FIELDS_TENANT);
    
    // Initialize the tentant
    tenant_init(data);
    
    // Get the date and time
    csv_getAsString(entry, 0, start_date, 11);    
    date_parse(&(data->start_date), start_date);

    csv_getAsString(entry, 1, end_date, 11);    
    date_parse(&(data->end_date), end_date);
    
    // Assign the tenant ID
    csv_getAsString(entry, 2, data->tenant_id, MAX_PERSON_ID + 1);

    // Assign the tenant name
    data->name = (char*) malloc((strlen(entry.fields[3]) + 1) * sizeof(char));
    assert(data->name != NULL);
    memset(data->name, 0, (strlen(entry.fields[3]) + 1) * sizeof(char));
    csv_getAsString(entry, 3, data->name, strlen(entry.fields[3]) + 1);	
	
    data->rent = csv_getAsInteger(entry, 4);
    data->age = csv_getAsInteger(entry, 5);
    csv_getAsString(entry, 6, data->cadastral_ref, MAX_CADASTRAL_REF + 1);
	// Assign the tenant postal_code
	csv_getAsString(entry, 7, data->postal_code, MAX_POSTAL_CODE + 1);
    
}

// Release a tenant
void tenant_free(tTenant *tenant) {
    // Check input data (Pre-conditions)
    assert(tenant != NULL);
    
    // Release the name
    if (tenant->name != NULL) {
        free(tenant->name);
    }
    tenant->name = NULL;
	
	
}

// Initialize the tenants data
void tenantData_init(tTenantData *data) {
    // Check input data (Pre-conditions)
    assert(data != NULL);
    
    data->elems = NULL;
    data->count = 0;
}

// Return the number of tenants
int tenantData_len(tTenantData tenants) {
    return tenants.count;
}

// Add a tenant to the data
void tenantData_add(tTenantData *data, tTenant tenant) {
    // Check input data (Pre-conditions)
    assert(data != NULL);
    
    // If tenant does not exist, add it
    if (tenantData_find(*(data), tenant.tenant_id) < 0) {
        // Allocate memory for new element
        if (data->count == 0) {
            // Request new memory space
            data->elems = (tTenant*) malloc(sizeof(tTenant));
        } else {
            // Modify currently allocated memory
            data->elems = (tTenant*) realloc(data->elems, sizeof(tTenant) * (data->count + 1));
        }
        
        assert(data->elems != NULL);
    
        // Initialize the new element
        tenant_init(&(data->elems[data->count]));
        
        // Copy the element to the position
        tenant_cpy(&(data->elems[data->count]), tenant);
        
        // Increase the number of elements
        data->count++;
    }
}

// Return the position of the tenant if it exists, otherwise, it returns -1
int tenantData_find(tTenantData data, const char* tenant_id) {
    int i;
    
    // Check input data (Pre-conditions)
    assert(tenant_id != NULL);
    
    for (i = 0; i < data.count; i++) {
        if (strcmp(data.elems[i].tenant_id, tenant_id) == 0) {
            return i;
        }
    }
    
    return -1;
}

// Find the latest tenant of a property 
int findLatestTenant(tTenantData *data, char* cadastral_ref) {
    // PR3 3a

    return -10;
}

// Find the first tenant of a property 
int findFirstTenant(tTenantData *data, char* cadastral_ref){
    // PR3 3b
    
    return -10;
}

// Sorts the tenants according to the Id using Bubble sorting, first elment witht he lowest tenant_id
void sortTenantsById_Bubble(tTenantData *data){
    //PR3 3c
    data->count = -1;
}


// Release the tenants data
void tenantData_free(tTenantData *data) {
    // Check input data (Pre-conditions)
    assert(data != NULL);
    
    // Release memory
    if (data->elems != NULL) {
        for(int i = 0 ; i < data->count ; i++) {
        tenant_free(&(data->elems[i]));
        }  
        free(data->elems);
    }
    
    // Initialize the structure again
    tenantData_init(data);
}
