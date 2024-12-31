#include "test_pr2.h"
#include "api.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "taxes.h"


// Run all tests for PR2
bool run_pr2(tTestSuite * test_suite,
    const char * input) {
    bool ok = true;
    tTestSection * section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section, input);
    ok = run_pr2_ex2(section, input) && ok;
    ok = run_pr2_ex3(section, input) && ok;

    return ok;
}

// Run all tests for Exercice 1 of PR1
bool run_pr2_ex1(tTestSection * test_section,
    const char * input) {

    ExpectedInvoices expectedInvoices;
    tRentInvoiceData invoiceList;
    tTenant tenant, tenant2, tenant3, tenant4;
    float totalRent = 0.0f;
    tDate date;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    tenant_init(&tenant);
    tenant_init(&tenant2);
    tenant_init(&tenant3);
    tenant_init(&tenant4);
    
    /////////////////////////////
    /////  PR2 EX1 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR2_EX1_1", "Initialize invoices data structure");

    // set with wrong values to test the Initialization
    invoiceList.count = -34;

    // Initialize the data    
    invoiceList_init(&invoiceList);
    invoiceList_init(&invoiceList);

    if (invoiceList.count != 0 || invoiceList.first != NULL) {
        failed = true;
        passed = false;
        fail_all = true;
    }

    end_test(test_section, "PR2_EX1_1", !failed);

    /////////////////////////////
    /////  PR2 EX1 TEST 2  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX1_2", "Add a contract to an empty invoice list");

    if (!fail_all) {

        // Initialize an empty rent invoice list
        invoiceList.first = NULL;
        invoiceList.count = 0;

		// Ensure all fields are initialized		
		tenant_initialize(&tenant,"01/09/2022","31/08/2023","T001","John Doe",1000.0f,30,"ZYX1234","LE24001");				

        // Update the invoice list with the tenant
        if (!failed) {
            invoiceList_update( &invoiceList, tenant.start_date, tenant.end_date, tenant.cadastral_ref, tenant.rent);
        }

        // Check the results
        if (!failed) {
            // Verify that the invoice list has exactly one monthly invoice
            if (invoiceList.count != 12) {
                failed = true;
            } else if (invoiceList.first == NULL) {
                failed = true;
            } else {
                // Verify date 01/09/2022
                expectedInvoices.invoiceCount = 1;
                strcpy(expectedInvoices.invoices[0].cadastral_ref, "ZYX1234");
                expectedInvoices.invoices[0].rent = 1000.00f;

                if (!testVerifySpecificDate( &invoiceList, "01/09/2022", & expectedInvoices)) {
                    failed = true;
                }

                // Verify date 01/08/2022
                expectedInvoices.invoiceCount = 1;
                strcpy(expectedInvoices.invoices[0].cadastral_ref, "ZYX1234");
                expectedInvoices.invoices[0].rent = 1000.00f;
                if (!testVerifySpecificDate( & invoiceList, "01/08/2023", & expectedInvoices)) {
                    failed = true;
                }
            } //
        }
        

        // If any check failed, mark the entire test as failed
        if (failed) {
            fail_all = true;
            passed = false;
        }
    }

    // End the test and report the result
    end_test(test_section, "PR2_EX1_2", !failed);

    /////////////////////////////
    /////  PR2 EX1 TEST 3  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX1_3", "Add new contract in order");

    if (!fail_all) {
		// Ensure all fields are initialized
		
		tenant_initialize(&tenant2,"01/01/2023","31/12/2023","12345678A","Jason Garcia",1400.0f,36,"GHI1234","LE24001");		
   
        if (!failed) {
            invoiceList_update( &invoiceList, tenant2.start_date, tenant2.end_date, tenant2.cadastral_ref, tenant2.rent);

        }

        // Verify that the invoice list has exactly one monthly invoice
        if (invoiceList.count != 16) {
            failed = true;
        } else {
            // Verify date 01/09/2022
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[0].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/09/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/01/2023
            expectedInvoices.invoiceCount = 2;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[1].rent = 1000.00f;

            if (!testVerifySpecificDate( &invoiceList, "01/01/2023", & expectedInvoices)) {
                failed = true;
            }

            // Verify date 01/09/2023
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            if (!testVerifySpecificDate( &invoiceList, "01/09/2023", & expectedInvoices)) {
                failed = true;
            }

            // Verify date 01/12/2023
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            if (!testVerifySpecificDate( &invoiceList, "01/12/2023", & expectedInvoices)) {
                failed = true;
            }
        } //

        if (failed) {
            fail_all = true;
            passed = false;
        }
    }

    end_test(test_section, "PR2_EX1_3", !failed);

    /////////////////////////////
    /////  PR2 EX1 TEST 4  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX1_4", "Add contract before existing invoices");

    if (!fail_all) {
		tenant_initialize(&tenant3,"01/01/2022","31/12/2022","12345678A","Ana Fernandez",800.0f,41,"ABC1234","BA08001");		
    
        if (!failed) {
            invoiceList_update( & invoiceList, tenant3.start_date, tenant3.end_date, tenant3.cadastral_ref, tenant3.rent);

        }

        // Verify that the invoice list has exactly one monthly invoice
        if (invoiceList.count != 24) {
            failed = true;
        } else {
            // Verify date 01/01/2022
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/01/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/08/2022
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/08/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/09/2022
            expectedInvoices.invoiceCount = 2;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[1].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/09/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 31/12/2022
            expectedInvoices.invoiceCount = 2;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[1].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "31/12/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/01/2023
            expectedInvoices.invoiceCount = 2;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[1].rent = 1000.00f;
            if (!testVerifySpecificDate( & invoiceList, "01/01/2023", & expectedInvoices)) {
                failed = true;
            }
        } //

        if (failed) {
            fail_all = true;
            passed = false;
        }
    }

    end_test(test_section, "PR2_EX1_4", !failed);

    /////////////////////////////
    /////  PR2 EX1 TEST 5  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX1_5", "Add another contract");

    if (!fail_all) {
		tenant_initialize(&tenant4,"01/09/2022","31/07/2023","87654321Z","Maria Jackson",1300.0f,50,"JKL0123","BA08005");		
    
        if (!failed) {
            invoiceList_update( & invoiceList, tenant4.start_date, tenant4.end_date, tenant4.cadastral_ref, tenant4.rent);

        }

        // Verify that the invoice list has exactly one monthly invoice
        if (invoiceList.count != 24) {
            failed = true;
        } else {
            // Verify date 01/01/2022
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/01/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/08/2022
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/08/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/09/2022
            expectedInvoices.invoiceCount = 3;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "JKL0123");
            expectedInvoices.invoices[1].rent = 1300.00f;
            strcpy(expectedInvoices.invoices[2].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[2].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/09/2022", & expectedInvoices)) {
                failed = true;
            }

            // Verify date 01/01/2023
            expectedInvoices.invoiceCount = 3;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "JKL0123");
            expectedInvoices.invoices[1].rent = 1300.00f;
            strcpy(expectedInvoices.invoices[2].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[2].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/01/2023", & expectedInvoices)) {
                failed = true;
            }

            // Verify date 01/08/2023
            expectedInvoices.invoiceCount = 2;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[1].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/08/2023", & expectedInvoices)) {
                failed = true;
            }

            // Verify date 01/12/2023
            expectedInvoices.invoiceCount = 1;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/12/2023", & expectedInvoices)) {
                failed = true;
            }

        } //

    }
    end_test(test_section, "PR2_EX1_5", !failed);

    /////////////////////////////
    /////  PR2 EX1 TEST 6  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX1_6", "Update contract rent");

    if (!fail_all) {
        // Actualizar el contrato reciente (tenant4) para revertir el último test

        date_parse( & tenant4.start_date, "01/10/2022");
        tenant4.rent += 400.0f; // Increase rent

        if (!failed) {
            invoiceList_update( & invoiceList, tenant4.start_date, tenant4.end_date, tenant4.cadastral_ref, tenant4.rent);

        }

        // Verify that the invoice list has exactly one monthly invoice
        if (invoiceList.count != 24) {
            failed = true;
        } else {

            // Verify date 01/09/2022
            expectedInvoices.invoiceCount = 3;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "JKL0123");
            expectedInvoices.invoices[1].rent = 1300.00f;
            strcpy(expectedInvoices.invoices[2].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[2].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/09/2022", & expectedInvoices)) {
                failed = true;
            }

            // Verify date 01/10/2022
            expectedInvoices.invoiceCount = 3;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "ABC1234");
            expectedInvoices.invoices[0].rent = 800.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "JKL0123");
            expectedInvoices.invoices[1].rent = 1700.00f;
            strcpy(expectedInvoices.invoices[2].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[2].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/10/2022", & expectedInvoices)) {
                failed = true;
            }
            // Verify date 01/07/2023
            expectedInvoices.invoiceCount = 3;
            strcpy(expectedInvoices.invoices[0].cadastral_ref, "GHI1234");
            expectedInvoices.invoices[0].rent = 1400.00f;
            strcpy(expectedInvoices.invoices[1].cadastral_ref, "JKL0123");
            expectedInvoices.invoices[1].rent = 1700.00f;
            strcpy(expectedInvoices.invoices[2].cadastral_ref, "ZYX1234");
            expectedInvoices.invoices[2].rent = 1000.00f;

            if (!testVerifySpecificDate( & invoiceList, "01/07/2023", & expectedInvoices)) {
                failed = true;
            }

        } //

        if (failed) {
            fail_all = true;
            passed = false;
        }
    }

    end_test(test_section, "PR2_EX1_6", !failed);

    /////////////////////////////
    /////  PR2 EX1 TEST 8  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX1_8", "Request the total rent for a specific date");

    if (!fail_all) {
        // Calculate  the total rent of 2022-9       
        date_parse( & date, "01/09/2022");

        // total rent expected 800 + 1300 + 1000 = 3100
        totalRent = getInvoiceMonthly( & invoiceList, date);
        if (totalRent != 3100.0f) {
            failed = true;
        }

        // Calculate for a date without invoices
        date_parse( & date, "01/12/2021");
        totalRent = getInvoiceMonthly( & invoiceList, date);
        if (totalRent != 0.0f) {
            failed = true;
        }

        // Calculate  the total rent of 2023-7	      

        date_parse( & date, "01/07/2023");

        // total rent expected 1400 + 1700 + 1000 = 4100
        totalRent = getInvoiceMonthly( & invoiceList, date);
        if (totalRent != 4100.0f) {
            failed = true;
        }

        // Calculate for a date without invoices
        date_parse( & date, "01/01/2024");
        totalRent = getInvoiceMonthly( & invoiceList, date);
        if (totalRent != 0.0f) {
            failed = true;
        }

        if (failed) {
            fail_all = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX1_8", !failed);

    // free memory   
    tenant_free(&tenant);
    tenant_free(&tenant2);
    tenant_free(&tenant3);
    tenant_free(&tenant4);
    invoiceList_free( & invoiceList);
    return passed;
}

// Run all tests for Exercice 2 of PR2
bool run_pr2_ex2(tTestSection * test_section,
    const char * input) {

    bool passed = true;
    bool failed;
    bool fail_all = false;
    //tRentInvoiceData invoiceList;
    tTenant tenant;
    //tDate dateWithInvoices;
    tTaxOffice taxOffice;
    tTaxOffice * pTaxOffice;
    tTaxOfficeList taxOfficeList;

    /////////////////////////////
    /////  PR2 EX2 TEST 1  //////
    /////////////////////////////

    failed = fail_all;
    start_test(test_section, "PR2_EX2_1", "Initialize a tax office");

    if (!fail_all) {

        // Set incorrect value
        taxOffice.rentInvoices.count = -34;

        // Initialize a tax office list
        taxOffice_init( & taxOffice, "B08016");

        if (taxOffice.rentInvoices.count != 0 || strcmp(taxOffice.office_code, "B08016") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

    }
    end_test(test_section, "PR2_EX2_1", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 2  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_2", "Remove tax office data");

    if (!fail_all) {

        // Define tenant details  
        memset( & tenant, 0, sizeof(tTenant)); // Ensure all fields are initialized
        tenant_init(&tenant);
		tenant_initialize(&tenant,"01/09/2022","31/08/2023","01234567Y","John Doe",1300.0f,30,"ZYX1234","BA08005");		
           
        invoiceList_update( & taxOffice.rentInvoices, tenant.start_date, tenant.end_date, tenant.cadastral_ref, tenant.rent);

        // Clean center data
        taxOffice_free( & taxOffice);
        if (taxOffice.rentInvoices.count != 0) {
            failed = true;
        } else if (taxOffice.rentInvoices.first != NULL) {
            failed = true;
        }

        if (failed) {
            fail_all = true;
            passed = false;
        }
    }
    end_test(test_section, "PR2_EX2_2", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 3  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_3", "Initialize list of tax office");

    if (!fail_all) {
        // Set incorrect value
        taxOfficeList.count = -34;

        // Initialize the data    
        taxOfficeList_init( & taxOfficeList);
        if (taxOfficeList.count != 0 || taxOfficeList.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR2_EX2_3", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 4  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_4", "Check if the office code is correct");

    if (!fail_all) {
        // Define invalid office codes
        const char * invalid_codes[] = {
            "Ca12345", // Lowercase letter in province
            "CA12A45", // Non-numeric character
            "CA1234", // Incorrect length (6 instead of 7)
            "C1234A", // Last character non-numeric
            "TX123456", // Incorrect length (8 characters)
            "T1234", // Incorrect length (5 characters)
            "1234567", // Does not start with letters
            "A1B2345" // Mix of letters and numbers in incorrect positions
        };
        // Define valid office codes
        const char * valid_codes[] = {
            "C12345", // 1 uppercase letter province code, followed by 5 digits
            "CA12345", // 2 uppercase letters province code, followed by 5 digits
            "N54321", // 1 uppercase letter province code, followed by 5 digits
            "NY54321", // 2 uppercase letters province code, followed by 5 digits
            "A00001", // 1 uppercase letter province code with leading zeros
            "AB99999", // 2 uppercase letters province code with maximum digits
            "Z12345", // 1 uppercase letter province code, followed by 5 digits
            "ZX67890", // 2 uppercase letters province code, followed by 5 digits
            "B54321", // 1 uppercase letter province code, followed by 5 digits
            "BT12345", // 2 uppercase letters province code, followed by 5 digits
            "M98765", // 1 uppercase letter province code, followed by 5 digits
            "ML12345" // 2 uppercase letters province code, followed by 5 digits
        };

        int num_invalid = sizeof(invalid_codes) / sizeof(invalid_codes[0]);

        for (int i = 0; i < num_invalid; i++) {
            bool isValid = check_office_code(invalid_codes[i]);
            if (isValid) {
                failed = true;
                passed = false;
                fail_all = true;
                break;
            }
        }

        int num_valid = sizeof(valid_codes) / sizeof(valid_codes[0]);

        for (int i = 0; i < num_valid; i++) {
            bool isValid = check_office_code(valid_codes[i]);
            if (!isValid) {
                failed = true;
                passed = false;
                fail_all = true;
                break;
            }
        }

    }
    
    end_test(test_section, "PR2_EX2_4", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 5  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_5", "Insert a tax office to an empty list");

    if (!fail_all) {

        // Initialize the data    
        taxOfficeList_init( & taxOfficeList);

        // Insert a tax office
        taxOfficeList_insert( & taxOfficeList, "B08001");

        if (taxOfficeList.count != 1 || taxOfficeList.first == NULL || strcmp(taxOfficeList.first -> elem.office_code, "B08001") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR2_EX2_5", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 6  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_6", "Test office code is sorting");

    if (!fail_all) {
        // Initialize the tax office list    
        tTaxOfficeList list;
        taxOfficeList_init( & list);

        // Insert a new office
        taxOfficeList_insert( & list, "C12345");

        // After first insertion, count should be 1 and first element should be "C12345"
        if (list.count != 1 || list.first == NULL || strcmp(list.first -> elem.office_code, "C12345") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        // Insert a second office
        taxOfficeList_insert( & list, "B08001");

        // Expected order: "B8001", "C12345"
        if (list.count != 2 || list.first == NULL || strcmp(list.first -> elem.office_code, "B08001") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        } else if (list.first -> next == NULL || strcmp(list.first -> next -> elem.office_code, "C12345") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

        if (!fail_all) {
            // Insert a third office
            taxOfficeList_insert( & list, "A08000");

            // Expected order: "A08000", "B8001", "C12345"
            if (list.count != 3 || list.first == NULL || strcmp(list.first -> elem.office_code, "A08000") != 0) {
                failed = true;
                passed = false;
                fail_all = true;
            } else if (list.first -> next == NULL || strcmp(list.first -> next -> elem.office_code, "B08001") != 0) {
                failed = true;
                passed = false;
                fail_all = true;
            } else if (list.first -> next -> next == NULL || strcmp(list.first -> next -> next -> elem.office_code, "C12345") != 0) {
                failed = true;
                passed = false;
                fail_all = true;
            }
        }
        taxOfficeList_free( &list);
    }
    end_test(test_section, "PR2_EX2_6", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 7  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_7", "Find an existing office by code");

    if (!fail_all) {

        // Initialize the data   
        pTaxOffice = taxOfficeList_find( & taxOfficeList, "B08001");
        if (pTaxOffice == NULL || strcmp(pTaxOffice -> office_code, "B08001") != 0) {
            failed = true;
            passed = false;
            fail_all = true;
        }

    }
    end_test(test_section, "PR2_EX2_7", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 8  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_8", "Find a non existing office by code");

    if (!fail_all) {

        // Initialize the data    
        pTaxOffice = taxOfficeList_find( & taxOfficeList, "LE24001");
        if (pTaxOffice != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR2_EX2_8", !failed);

    /////////////////////////////
    /////  PR2 EX2 TEST 9  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX2_9", "Release a list of list office");

    if (!fail_all) {

        // Initialize the data    
        taxOfficeList_free( & taxOfficeList);
		tenant_free(&tenant);
        if (taxOfficeList.count != 0 || taxOfficeList.first != NULL) {
            failed = true;
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR2_EX2_9", !failed);  

    return passed;
}

// Run all tests for Exercice 3 of PR2
bool run_pr2_ex3(tTestSection * test_section,
    const char * input) {
    tApiData data;
    tApiError error;
    int nTenants;
    int nTaxOffices;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    /////////////////////////////
    /////  PR2 EX3 TEST 1  //////
    /////////////////////////////
    failed = false;
    start_test(test_section, "PR2_EX3_1", "Initialize the API data");
    // Initialize the data    
    error = api_initData( & data);
    if (error != E_SUCCESS) {
        passed = false;
        failed = true;
        fail_all = true;
    } else if (api_taxOfficeCount(data) != 0) {
        passed = false;
        failed = true;
        fail_all = true;
    }

    end_test(test_section, "PR2_EX3_1", !failed);

    /////////////////////////////
    /////  PR2 EX3 TEST 2  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX3_2", "Load API data");

    if (!fail_all) {
        error = api_loadData( & data, input, true);

        nTenants = api_tenantCount(data);

        if (error != E_SUCCESS || nTenants != 3) {
            passed = false;
            fail_all = true;
        }
    }
    end_test(test_section, "PR2_EX3_2", !failed);

    /////////////////////////////
    /////  PR2 EX3 TEST 3  //////
    /////////////////////////////
    failed = fail_all;
    start_test(test_section, "PR2_EX3_3", "Obtain number of centers in the API");
    if (!fail_all) {
        nTaxOffices = api_taxOfficeCount(data);
        if (nTaxOffices != 3) {
            passed = false;
            failed = true;
            fail_all = true;
        }
    }

    end_test(test_section, "PR2_EX3_3", !failed);

    // Release all data
    api_freeData( & data);

    return passed;
}

