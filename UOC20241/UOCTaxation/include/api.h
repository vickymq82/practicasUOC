#ifndef __UOCTAXATION_API__H
#define __UOCTAXATION_API__H
#include <stdbool.h>
#include "error.h"
#include "csv.h"

#include "tenant.h"
#include "landlord.h"
#include "rental_incomes.h"
#include "invoice.h"
#include "tax_office.h"

// Type that stores all the application data
typedef struct _ApiData {
    ////////////////////////////////
    // Ex PR1 2a
    ////////////////////////////////
    // Tenants
    tTenantData tenants;	
	// Landlords
    tLandlords landlords;
    // Landlords rental income
    tRentalIncomeList rentalIncomes;
	 ////////////////////////////////
    // Ex PR2 3b
    tTaxOfficeList taxOffices;
    ////////////////////////////////   

	
    ////////////////////////////////
} tApiData;

// Get the API version information
const char* api_version();

// Load data from a CSV file. If reset is true, remove previous data
tApiError api_loadData(tApiData* data, const char* filename, bool reset);

// Initialize the data structure
tApiError api_initData(tApiData* data);

// Add a tenant into the data if it does not exist
tApiError api_addTenant(tApiData* data, tCSVEntry entry);

// Add a landlord if it does not exist
tApiError api_addLandlord(tApiData* data, tCSVEntry entry);

// Add a property into the properties of an specific landlord
tApiError api_addProperty(tApiData* data, tCSVEntry entry);

// Add a rental income into a list if the landlord already exists
tApiError api_addRentalIncome(tApiData* data, tCSVEntry entry);

// Find a rental income by year and landlord document id
tRentalIncome* rentalIncomes_find(tRentalIncomeList list, int year, const char* document_id);

// Get the number of tenants registered on the application
int api_tenantCount(tApiData data);

// Get the number of landlords registered on the application
int api_landlordsCount(tApiData data);

// Get the number of properties in all landlords registered on the application
int api_propertiesCount(tApiData data);

// Get the number of rental incomes registered
int api_rentalIncomesCount(tApiData data);

// Get the number of health centers registered on the application
int api_taxOfficeCount(tApiData data);

// Free all used memory
tApiError api_freeData(tApiData* data);

// Add a new entry
tApiError api_addDataEntry(tApiData* data, tCSVEntry entry);

// Get landlord data
tApiError api_getLandlord(tApiData data, const char *id, tCSVEntry *entry);

// Get the rental income by year of a landlord
tApiError api_getRentalIncome(tApiData data, int year, const char* id, tCSVEntry *entry);

// Get registered properties
tApiError api_getProperties(tApiData data, tCSVData *properties);

// Get monthly invoices by cadastral reference, oldest invoice in first position
tApiError api_getMonthlyInvoiceByCadastralRef(tApiData data, char* cadastral_ref ,tCSVData *invoices);

// Get monthly invoices by cadastral reference, oldest invoice in last position
tApiError api_getMonthlyInvoiceByCadastralRef_Reverse(tApiData data, char* cadastral_ref ,tCSVData *invoices);

// Get monthly invoices of a Tax office, month sorted according to total rent, month with the highest total rent first
tApiError api_getMonthlyInvoicebyRent(tApiData data, char* office_code, tCSVData *invoices);

// Get the address of a cadastral reference
tApiError api_getAddressByCadastralRef (tApiData data, char* cadastral_ref, tCSVEntry *address);

// Sort list of landlords by Name and properties by cadastral reference, from low to high
tApiError api_sortLandlordsByName(tApiData *data);

// Find the latest tenant of a property 
tApiError api_findLatestTenant(tApiData data, char* cadastral_ref, tCSVEntry *tenant);

// Find the first tenant of a property 
tApiError api_findFirstTenant(tApiData data, char* cadastral_ref, tCSVEntry *tenant);

// Sort list of tenants by id
tApiError api_sortTenantsById(tApiData *data);

// Get registered rental incomes
tApiError api_getRentalIncomes(tApiData data, tCSVData *rentalIncomes);


#endif // __UOCTAXATION_API__H