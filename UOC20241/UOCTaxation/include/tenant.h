#ifndef __TENANT_H__
#define __TENANT_H__

#include "date.h"
#include "csv.h"

#define MAX_PERSON_ID 9
#define MAX_CADASTRAL_REF 7
#define MAX_POSTAL_CODE 8

#define NUM_FIELDS_TENANT 8

typedef struct _tTenant {
    tDate start_date;
    tDate end_date;
    char tenant_id[MAX_PERSON_ID + 1];
    char *name;
    float rent;
    int age;
	char postal_code [MAX_POSTAL_CODE + 1];;
    char cadastral_ref[MAX_CADASTRAL_REF + 1];
} tTenant;

typedef struct _tTenantData {
    tTenant *elems;
    int count;
} tTenantData;

// Initialize a tenant
void tenant_init(tTenant *tenant);

void tenant_initialize(tTenant *tenant, const char* start_date, const char * end_date, const char *tenant_id, 
                      const char *name, float rent, int age, const char *cadastral_ref, const char *postal_code );

// Copy a tenant
void tenant_cpy(tTenant *dst, tTenant src);

// Parse input from CSVEntry
void tenant_parse(tTenant* data, tCSVEntry entry);

// Release a tenant
void tenant_free(tTenant *tenant);

// Initialize the tenants data
void tenantData_init(tTenantData *data);

// Return the number of tenants
int tenantData_len(tTenantData tenants);

// Add a tenant to the data
void tenantData_add(tTenantData *data, tTenant tenant);

// Find a tenant into the data
int tenantData_find(tTenantData data, const char* tenant_id);

// Find the latest tenant of a property 
int findLatestTenant(tTenantData *data, char* cadastral_ref);

// Find the first tenant of a property 
int findFirstTenant(tTenantData *data, char* cadastral_ref);

// Sorts the tenants according to the Id using Bubble sorting, first elment witht he lowest tenant_id
void sortTenantsById_Bubble(tTenantData *data);

// Release the tenants data
void tenantData_free(tTenantData *data);

#endif
