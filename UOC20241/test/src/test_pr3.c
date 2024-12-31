#include "test_pr3.h"
#include "api.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "taxes.h"


// Run all tests for PR3
bool run_pr3(tTestSuite * test_suite,

    const char * input) {
    bool ok = true;
    tTestSection * section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");

    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);

    ok = run_pr3_ex1(section, input);
    ok = run_pr3_ex2(section, input) && ok;
    ok = run_pr3_ex3(section, input) && ok;
    ok = run_pr3_ex4(section, input) && ok;

    return ok;
}

// Run all tests for Exercice 1 of PR3
bool run_pr3_ex1(tTestSection * test_section,
    const char * input) {

    tRentInvoiceData emptyList, invoiceList, sortedInvoiceList;
    tTenant tenant1, tenant2, tenant3, tenant4, tenant5;
    tRentInvoiceMonthly *auxRentInvoice, *firstRentInvoice;
    int i;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    // Initialize tenants
    tenant_init(&tenant1);
    tenant_init(&tenant2);
    tenant_init(&tenant3);
    tenant_init(&tenant4);
    tenant_init(&tenant5);
    tenant_initialize(&tenant1,"01/09/2022","31/08/2023","T001","John Doe",1000.0f,30,"ZYX1234","LE24001");
    tenant_initialize(&tenant2,"01/01/2023","31/12/2023","12345678A","Jason Garcia",1400.0f,36,"GHI1234","LE24001");
    tenant_initialize(&tenant3,"01/01/2022","31/12/2022","12345678A","Ana Fernandez",800.0f,41,"ABC1234","BA08001");
    tenant_initialize(&tenant4,"01/09/2022","31/07/2023","87654321Z","Maria Jackson",1300.0f,50,"JKL0123","BA08005");
    tenant_initialize(&tenant5,"01/03/2022","29/02/2048","31415926P","Peter Thomson",3141.0f,31,"JKL0124","BA08005");

    // Initialize the data 
    invoiceList_init(&emptyList);  
    invoiceList_init(&invoiceList);
    
    invoiceList_update( &invoiceList, tenant1.start_date, tenant1.end_date, tenant1.cadastral_ref, tenant1.rent);
    invoiceList_update( &invoiceList, tenant2.start_date, tenant2.end_date, tenant2.cadastral_ref, tenant2.rent);
    invoiceList_update( &invoiceList, tenant3.start_date, tenant3.end_date, tenant3.cadastral_ref, tenant3.rent);
    invoiceList_update( &invoiceList, tenant4.start_date, tenant4.end_date, tenant4.cadastral_ref, tenant4.rent);
    invoiceList_update( &invoiceList, tenant5.start_date, tenant5.end_date, tenant5.cadastral_ref, tenant5.rent);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX1_1", "Find Invoice by CadastralRef [Empty List]");
    
    sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&emptyList, tenant1.cadastral_ref);
    
    if (sortedInvoiceList.count != 0 || sortedInvoiceList.first != NULL) {
            failed = true;
            fail_all = true; 
    } 
    invoiceList_free( &sortedInvoiceList);
    end_test(test_section, "PR3_EX1_1", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 2  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_2", "Find Invoice by CadastralRef [AAA1111]");
    if (!fail_all) {
        failed = false;
        char aux_cadastral_ref[] = "AAA1111";
        sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&invoiceList, aux_cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 0 || sortedInvoiceList.first != NULL) {
                failed = true;
                fail_all = true; 
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_2", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 3  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_3", "Find Invoice by CadastralRef [ZYX1234]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&invoiceList, tenant1.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 12 || date_cmp(sortedInvoiceList.first->month, tenant1.start_date) != 0) {
            failed = true;
        } else if (auxRentInvoice->month.month != tenant1.end_date.month || auxRentInvoice->month.year != tenant1.end_date.year || auxRentInvoice->month.day != 1) {
            failed = true;
        }   else if (sortedInvoiceList.first->first->elem.rent != tenant1.rent || auxRentInvoice->first->elem.rent != tenant1.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 4  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_4", "Find Invoice by CadastralRef [GHI1234]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&invoiceList, tenant2.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 12 || date_cmp(sortedInvoiceList.first->month, tenant2.start_date) != 0) {
            failed = true;
        } else if (auxRentInvoice->month.month != tenant2.end_date.month || auxRentInvoice->month.year != tenant2.end_date.year || auxRentInvoice->month.day != 1) {
            failed = true;
        }  else if (sortedInvoiceList.first->first->elem.rent != tenant2.rent || auxRentInvoice->first->elem.rent != tenant2.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_4", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 5  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_5", "Find Invoice by CadastralRef [ABC1234]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&invoiceList, tenant3.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 12 || date_cmp(sortedInvoiceList.first->month, tenant3.start_date ) != 0) {
            failed = true;
        } else if (auxRentInvoice->month.month != tenant3.end_date.month || auxRentInvoice->month.year != tenant3.end_date.year || auxRentInvoice->month.day != 1) {
            failed = true;
        }  else if (sortedInvoiceList.first->first->elem.rent != tenant3.rent || auxRentInvoice->first->elem.rent != tenant3.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_5", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 6  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_6", "Find Invoice by CadastralRef [JKL0123]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&invoiceList, tenant4.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 11 || date_cmp(sortedInvoiceList.first->month, tenant4.start_date) != 0) {
            failed = true;
        } else if (auxRentInvoice->month.month != tenant4.end_date.month || auxRentInvoice->month.year != tenant4.end_date.year || auxRentInvoice->month.day != 1) {
            failed = true;
        }  else if (sortedInvoiceList.first->first->elem.rent != tenant4.rent || auxRentInvoice->first->elem.rent != tenant4.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_6", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 7  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_7", "Find Invoice by CadastralRef [JKL0124]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef(&invoiceList, tenant5.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 312 || date_cmp(sortedInvoiceList.first->month, tenant5.start_date) != 0) {
            failed = true;
        } else if (auxRentInvoice->month.month != tenant5.end_date.month || auxRentInvoice->month.year != tenant5.end_date.year || auxRentInvoice->month.day != 1) {
            failed = true;
        } else if (sortedInvoiceList.first->first->elem.rent != tenant5.rent || auxRentInvoice->first->elem.rent != tenant5.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_7", !failed);
    
    
        start_test(test_section, "PR3_EX1_8", "Find Invoice by CadastralRef Reverse [Empty List]");
    if (!fail_all) {
        failed = false;
        
        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&emptyList, tenant1.cadastral_ref);
        
        if (sortedInvoiceList.count != 0 || sortedInvoiceList.first != NULL) {
                failed = true;
                fail_all = true; 
        }
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_8", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 9  //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_9", "Find Invoice by CadastralRef [AAA1111]");
    if (!fail_all) {
        failed = false;

        char aux_cadastral_ref[] = "AAA1111";
        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&invoiceList, aux_cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 0 || sortedInvoiceList.first != NULL) {
                failed = true;
                fail_all = true; 
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_9", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 10 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_10", "Find Invoice by CadastralRef [ZYX1234]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&invoiceList, tenant1.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 12 || (sortedInvoiceList.first->month.month != tenant1.end_date.month || sortedInvoiceList.first->month.year != tenant1.end_date.year || sortedInvoiceList.first->month.day != 1)) {
            failed = true;
        } else if (date_cmp(auxRentInvoice->month, tenant1.start_date) != 0) {
            failed = true;
        }   else if (sortedInvoiceList.first->first->elem.rent != tenant1.rent || auxRentInvoice->first->elem.rent != tenant1.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_10", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 11 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_11", "Find Invoice by CadastralRef [GHI1234]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&invoiceList, tenant2.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 12 || (sortedInvoiceList.first->month.month != tenant2.end_date.month || sortedInvoiceList.first->month.year != tenant2.end_date.year || sortedInvoiceList.first->month.day != 1)) {
            failed = true;
        } else if (date_cmp(auxRentInvoice->month, tenant2.start_date) != 0) {
            failed = true;
        }   else if (sortedInvoiceList.first->first->elem.rent != tenant2.rent || auxRentInvoice->first->elem.rent != tenant2.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_11", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 12 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_12", "Find Invoice by CadastralRef [ABC1234]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&invoiceList, tenant3.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 12 || (sortedInvoiceList.first->month.month != tenant3.end_date.month || sortedInvoiceList.first->month.year != tenant3.end_date.year || sortedInvoiceList.first->month.day != 1)) {
            failed = true;
        } else if (date_cmp(auxRentInvoice->month, tenant3.start_date) != 0) {
            failed = true;
        }   else if (sortedInvoiceList.first->first->elem.rent != tenant3.rent || auxRentInvoice->first->elem.rent != tenant3.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_12", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 13 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_13", "Find Invoice by CadastralRef [JKL0123]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&invoiceList, tenant4.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 11 || (sortedInvoiceList.first->month.month != tenant4.end_date.month || sortedInvoiceList.first->month.year != tenant4.end_date.year || sortedInvoiceList.first->month.day != 1)) {
            failed = true;
        } else if (date_cmp(auxRentInvoice->month, tenant4.start_date) != 0) {
            failed = true;
        }   else if (sortedInvoiceList.first->first->elem.rent != tenant4.rent || auxRentInvoice->first->elem.rent != tenant4.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_13", !failed);
    
    
    /////////////////////////////
    /////  PR3 EX1 TEST 14 //////
    /////////////////////////////
    
    start_test(test_section, "PR3_EX1_14", "Find Invoice by CadastralRef [JKL0124]");
    if (!fail_all) {
        failed = false;

        sortedInvoiceList = findMonthlyInvoiceByCadastralRef_Reverse(&invoiceList, tenant5.cadastral_ref);
        auxRentInvoice = getLastRentInvoice(&sortedInvoiceList);
        
        if (sortedInvoiceList.count != 312 || (sortedInvoiceList.first->month.month != tenant5.end_date.month || sortedInvoiceList.first->month.year != tenant5.end_date.year || sortedInvoiceList.first->month.day != 1)) {
            failed = true;
        } else if (date_cmp(auxRentInvoice->month, tenant5.start_date) != 0) {
            failed = true;
        }   else if (sortedInvoiceList.first->first->elem.rent != tenant5.rent || auxRentInvoice->first->elem.rent != tenant5.rent ) {
            failed = true;
        }
        
        invoiceList_free( &sortedInvoiceList);
    }
    end_test(test_section, "PR3_EX1_14", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 15 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX1_15", "Sort Monthly Invoice [Empty List]");
    fail_all = false;
    sortMonthlyInvoicebyRent(&emptyList);
    
    if (emptyList.count != 0 || emptyList.first != NULL) {
            failed = true;
            fail_all = true; 
    }
    invoiceList_free(&emptyList);
    invoiceList_init(&emptyList);  

    end_test(test_section, "PR3_EX1_15", !failed);
    
    /////////////////////////////
    /////  PR3 EX1 TEST 16 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX1_16", "Sort Monthly Invoice by Rent");
    
    if(!fail_all) {
        firstRentInvoice = invoiceList.first;
        sortMonthlyInvoicebyRent(&invoiceList);
        auxRentInvoice = invoiceList.first;
        
        if (invoiceList.count != 314) {
                failed = true;
        } else {
            for(i=1; i<8;i++) {
                
                if (auxRentInvoice->month.year != 2023 || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                    failed = true;
                    break;
                }
                auxRentInvoice = auxRentInvoice->next;
            }
            
            if(!failed) {
                for(i=9; i<13;i++) {
                    if (auxRentInvoice->month.year != 2022 || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                        failed = true;
                        break;
                    }
                    auxRentInvoice = auxRentInvoice->next;
                }      
            }
            
            if(!failed) {
                for(i=8; i<13;i++) {
                    if (auxRentInvoice->month.year != 2023 || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                        failed = true;
                        break;
                    }
                    auxRentInvoice = auxRentInvoice->next;
                }      
            }
            if(!failed) {
                for(i=3; i<9;i++) {
                    if (auxRentInvoice->month.year != 2022 || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                        failed = true;
                        break;
                    }
                    auxRentInvoice = auxRentInvoice->next;
                }      
            }
            if(!failed) {
                for(int year = 2024; year < 2048; year++){
                    for(i=1; i<13;i++) {
                        if (auxRentInvoice->month.year != year || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                            failed = true;
                            break;
                        }
                        auxRentInvoice = auxRentInvoice->next;
                    }
                }      
            }
            if(!failed) {
                for(i=1; i<3;i++) {
                    if (auxRentInvoice->month.year != 2048 || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                        failed = true;
                        break;
                    }
                    auxRentInvoice = auxRentInvoice->next;
                }      
            }
            
            if(!failed) {
                for(i=1; i<3;i++) {
                    if (auxRentInvoice->month.year != 2022 || auxRentInvoice->month.month != i || auxRentInvoice->month.day != 1) {
                        failed = true;
                        break;
                    }
                    auxRentInvoice = auxRentInvoice->next;
                }
                if(auxRentInvoice != NULL) {
                    failed =true;
                }     
            }
        }
        
        fail_all = failed;
    }

    end_test(test_section, "PR3_EX1_16", !failed);

    /////////////////////////////
    /////  PR3 EX1 TEST 17 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX1_17", "Sort Monthly Invoice by Date");
    
    if(!fail_all) {
        failed = false;
        sortMonthlyInvoicebyDate(&invoiceList);
        auxRentInvoice = invoiceList.first;
        if (invoiceList.count != 314) {
            failed = true;
        } else if (firstRentInvoice != auxRentInvoice) {
            failed = true;
        } else if (strcmp(auxRentInvoice->first->elem.cadastral_ref, tenant3.cadastral_ref) != 0 || auxRentInvoice->first->elem.rent != tenant3.rent){
            failed = true;
        } else {
            i=1;
            while(auxRentInvoice->next != NULL) {
                if(date_cmp(auxRentInvoice->next->month,auxRentInvoice->month)<=0){
                    failed = true;
                    break;
                }
                auxRentInvoice = auxRentInvoice->next;
                i++;
            }
            if (i != 314) {
                failed = true;
            } else if (strcmp(auxRentInvoice->first->elem.cadastral_ref, tenant5.cadastral_ref) != 0 || auxRentInvoice->first->elem.rent != tenant5.rent) {
                failed = true;
            }
        }
    }
    
    end_test(test_section, "PR3_EX1_17", !failed);
    
    passed = passed && !fail_all && !failed;

    
    tenant_free(&tenant1);
    tenant_free(&tenant2);
    tenant_free(&tenant3);
    tenant_free(&tenant4);
    tenant_free(&tenant5);
    invoiceList_free( &emptyList);
    invoiceList_free( &invoiceList);
    invoiceList_free( &sortedInvoiceList);
    return passed;
}

// Run all tests for Exercice 2 of PR3
bool run_pr3_ex2(tTestSection * test_section, const char * input) {
    
    bool passed = true;
    bool failed = false;
    bool fail_all = false;    
    
    tLandlords emptyList, landlordsList, sortedList;
    tAddress* pAddress;
    tLandlord lanlord1, lanlord2;
    tProperty property1,property2,property3,property4,property5,property6,property7,property8,property9,property10;
    tProperties *auxProperties;
    tCSVEntry entryLanlord1,entryLanlord2,entryProperty1,entryProperty2,entryProperty3,entryProperty4,entryProperty5,entryProperty6,entryProperty7,entryProperty8,entryProperty9,entryProperty10;
    int i,j;
    
    landlords_init(&emptyList);
    landlords_init(&landlordsList);
    landlords_init(&sortedList);
    
    landlord_init(&lanlord1);
    landlord_init(&lanlord2);
    csv_initEntry(&entryLanlord1);
    csv_initEntry(&entryLanlord2);
    csv_parseEntry(&entryLanlord1, "James Meiji;11111111A;100", "LANLORD");
    csv_parseEntry(&entryLanlord2, "Don Trump;12345678Z;9999", "LANLORD");
    landlord_parse(&lanlord1, entryLanlord1);
    landlord_parse(&lanlord2, entryLanlord2);
    landlords_add(&landlordsList, lanlord1);
    landlords_add(&landlordsList, lanlord2);
    
    csv_initEntry(&entryProperty1);
    csv_initEntry(&entryProperty2);
    csv_initEntry(&entryProperty3);
    csv_initEntry(&entryProperty4);
    csv_initEntry(&entryProperty5);
    csv_initEntry(&entryProperty6);
    csv_initEntry(&entryProperty7);
    csv_initEntry(&entryProperty8);
    csv_initEntry(&entryProperty9);
    csv_initEntry(&entryProperty10);
    csv_parseEntry(&entryProperty1, "ABC1234;Big Street;1;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty2, "VQA9179;Main Street;900;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty3, "PQC6533;Oak Road;150;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty4, "ZMB8252;Lake Avenue;199;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty5, "VKF6225;Big Street;434;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty6, "EPY1713;Main Street;175;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty7, "WJY6414;Oak Road;907;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty8, "SSD9729;Lake Avenue;388;11111111A", "PROPERTY");
    csv_parseEntry(&entryProperty9, "KWV1417;Main Street;21;12345678Z", "PROPERTY");
    csv_parseEntry(&entryProperty10, "FTZ9173;Main Street;204;12345678Z", "PROPERTY");
    property_parse(&property1, entryProperty1);
    property_parse(&property2, entryProperty2);
    property_parse(&property3, entryProperty3);
    property_parse(&property4, entryProperty4);
    property_parse(&property5, entryProperty5);
    property_parse(&property6, entryProperty6);
    property_parse(&property7, entryProperty7);
    property_parse(&property8, entryProperty8);
    property_parse(&property9, entryProperty9);
    property_parse(&property10, entryProperty10);
    landlord_add_property(&landlordsList, property1);
    landlord_add_property(&landlordsList, property2);
    landlord_add_property(&landlordsList, property3);
    landlord_add_property(&landlordsList, property4);
    landlord_add_property(&landlordsList, property5);
    landlord_add_property(&landlordsList, property6);
    landlord_add_property(&landlordsList, property7);
    landlord_add_property(&landlordsList, property8);
    landlord_add_property(&landlordsList, property9);
    landlord_add_property(&landlordsList, property10);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_1", "Find Address by CadastralRef [Empty list]");
    
    pAddress = findAddressByCadastralRef(&emptyList, property1.cadastral_ref);
    
    if (pAddress != NULL) {
        failed = true;
        fail_all = true; 
        passed = false;
    } 
    
    end_test(test_section, "PR3_EX2_1", !failed);

    /////////////////////////////
    /////  PR3 EX2 TEST 2  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_2", "Find Address by CadastralRef [00000000A]");
    if (!fail_all) {
        pAddress = findAddressByCadastralRef(&landlordsList, "00000000A");
        
        if (pAddress != NULL) {
            failed = true;
            fail_all = true;
            passed = false;
        } 
        
    }
    end_test(test_section, "PR3_EX2_2", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 3  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_3", "Find Address by CadastralRef [ABC1234]");
    if (!fail_all) {
        pAddress = findAddressByCadastralRef(&landlordsList, property1.cadastral_ref);
        if (pAddress == NULL) {
            failed = true;
            fail_all = true;
            passed = false;
        } else if (strcmp(pAddress->street,property1.address.street)!=0 || pAddress->number !=property1.address.number) {
            failed = true;
            fail_all = true;
            passed = false;
        } 
        
    }
    end_test(test_section, "PR3_EX2_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 4  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_4", "Find Address by CadastralRef [VKF6225]");
    if (!fail_all) {
        pAddress = findAddressByCadastralRef(&landlordsList, property5.cadastral_ref);
        
        if (pAddress == NULL) {
            failed = true;
            fail_all = true;
            passed = false;
        } else if (strcmp(pAddress->street,property5.address.street)!=0 || pAddress->number !=property5.address.number) {
            failed = true;
            fail_all = true;
            passed = false;
        } 
        
    }
    end_test(test_section, "PR3_EX2_4", !failed);

    /////////////////////////////
    /////  PR3 EX2 TEST 5  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_5", "Find Address by CadastralRef [FTZ9173]");
    if (!fail_all) {
        pAddress = findAddressByCadastralRef(&landlordsList, property10.cadastral_ref);
        
        if (pAddress == NULL) {
            failed = true;
            fail_all = true;
            passed = false;
        } else if (strcmp(pAddress->street,property10.address.street)!=0 || pAddress->number !=property10.address.number) {
            failed = true;
            fail_all = true;
            passed = false;
        } 
        
    }
    end_test(test_section, "PR3_EX2_5", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 6  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_6", "Sort Propierties QickSort ");
    if (!fail_all) {
        failed = false;
        sortPropertiesByCadastralRef_QuickSort(&landlordsList.elems[0].properties);
        if(landlordsList.elems[0].properties.count != 8) {
            failed = true;
            fail_all = true;
        } else {
            auxProperties = &landlordsList.elems[0].properties;
            i = 0;
            while (i<auxProperties->count -1 && !failed) {
                if (strcmp(auxProperties->elems[i].cadastral_ref,auxProperties->elems[i+1].cadastral_ref)>0) {
                    failed = true;
                    fail_all = true;
                    passed = false;
                }
                i++;
            }
        }
        
    }
    end_test(test_section, "PR3_EX2_6", !failed);
    
    /////////////////////////////
    /////  PR3 EX2 TEST 7  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX2_7", "Sort Landlords QickSort");
    if (!fail_all) {
        failed = false;
        
        landlords_free(&landlordsList);
        landlords_init(&landlordsList);
        landlords_add(&landlordsList, lanlord1);
        landlords_add(&landlordsList, lanlord2);
        landlord_add_property(&landlordsList, property1);
        landlord_add_property(&landlordsList, property2);
        landlord_add_property(&landlordsList, property3);
        landlord_add_property(&landlordsList, property4);
        landlord_add_property(&landlordsList, property5);
        landlord_add_property(&landlordsList, property6);
        landlord_add_property(&landlordsList, property7);
        landlord_add_property(&landlordsList, property8);
        landlord_add_property(&landlordsList, property9);
        landlord_add_property(&landlordsList, property10);

        sortLandlordsByName_QuickSort(&landlordsList);
        
        i=0;
        while(i<landlordsList.count -1 && !failed) {
            
            if (strcmp(landlordsList.elems[i].name,landlordsList.elems[i+1].name)>0) {
                failed = true;
                fail_all = true;
                passed = false;
            } else {
                auxProperties = &landlordsList.elems[i].properties;
                j=0;
                while (j<auxProperties->count -1 && !failed) {
                    if (strcmp(auxProperties->elems[j].cadastral_ref,auxProperties->elems[j+1].cadastral_ref)>0) {
                        failed = true;
                        fail_all = true;
                        passed = false;
                    }
                j++;
                }
            }
            i++;
        }
        
        
        
    }
    end_test(test_section, "PR3_EX2_7", !failed);
    
    
        
    passed = passed && !fail_all && !failed;
    
    csv_freeEntry(&entryLanlord1);
    csv_freeEntry(&entryLanlord2);
    csv_freeEntry(&entryProperty1);
    csv_freeEntry(&entryProperty2);
    csv_freeEntry(&entryProperty3);
    csv_freeEntry(&entryProperty4);
    csv_freeEntry(&entryProperty5);
    csv_freeEntry(&entryProperty6);
    csv_freeEntry(&entryProperty7);
    csv_freeEntry(&entryProperty8);
    csv_freeEntry(&entryProperty9);
    csv_freeEntry(&entryProperty10);
    landlord_free(&lanlord1);
    landlord_free(&lanlord2);
    landlords_free(&emptyList);
    landlords_free(&landlordsList);
    landlords_free(&sortedList);    
    return passed;
}

// Run all tests for Exercice 3 of PR3
bool run_pr3_ex3(tTestSection * test_section,
    const char * input) {

    tTenant tenant1, tenant2, tenant3, tenant4, tenant5, tenant6, tenant7, tenant8, tenant9, tenant10;
    tTenantData emptyList, tenantList;
    int i;

    bool passed = true;
    bool failed = false;
    bool fail_all = false;

    // Initialize tenants
    tenant_init(&tenant1);
    tenant_init(&tenant2);
    tenant_init(&tenant3);
    tenant_init(&tenant4);
    tenant_init(&tenant5);
    tenant_init(&tenant6);
    tenant_init(&tenant7);
    tenant_init(&tenant8);
    tenant_init(&tenant9);
    tenant_init(&tenant10);
    tenant_initialize(&tenant1,"01/09/2022","31/08/2023","T001","John Doe",1000.0f,30,"ZYX1234","LE24001");
    tenant_initialize(&tenant2,"01/01/2023","31/12/2023","12345678A","Jason Garcia",1400.0f,36,"GHI1234","LE24001");
    tenant_initialize(&tenant3,"01/01/2022","31/12/2022","12345679B","Ana Fernandez",800.0f,41,"ABC1234","BA08001");
    tenant_initialize(&tenant4,"01/09/2022","31/07/2023","87654321Z","Maria Jackson",1300.0f,50,"JKL0123","BA08005");
    tenant_initialize(&tenant5,"01/03/2022","29/02/2048","31415926P","Peter Thomson",3141.0f,31,"JKL0124","BA08005");
    tenant_initialize(&tenant6,"01/02/2024","31/03/2024","22244678A","Smith Potter",400.0f,70,"GHI1234","LE24001");
    tenant_initialize(&tenant7,"01/01/2024","31/01/2024","88899978T","Niels Geuder",1000.0f,36,"GHI1234","LE24001");
    tenant_initialize(&tenant8,"01/09/2021","31/07/2021","3334321Z","Helena Jackson",300.0f,50,"JKL0123","BA08005");
    tenant_initialize(&tenant9,"01/08/2023","31/12/2023","4444321Z","Iker Garcia",10000.0f,50,"JKL0123","BA08005");
    tenant_initialize(&tenant10,"01/09/2020","31/08/2022","T002","Mary Doe",2000.0f,30,"ZYX1234","LE24001");
    
    tenantData_init(&emptyList);
    tenantData_init(&tenantList);
    tenantData_add(&tenantList,tenant1);
    tenantData_add(&tenantList,tenant2);
    tenantData_add(&tenantList,tenant3);
    tenantData_add(&tenantList,tenant4);
    tenantData_add(&tenantList,tenant5);
    tenantData_add(&tenantList,tenant6);
    tenantData_add(&tenantList,tenant7);
    tenantData_add(&tenantList,tenant8);
    tenantData_add(&tenantList,tenant9);
    tenantData_add(&tenantList,tenant10);

    
    /////////////////////////////
    /////  PR3 EX3 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_1", "Find Latest Tenant [Empty list]");
    
    i = findLatestTenant(&emptyList,tenant1.cadastral_ref);
    if (i != -1) {
            failed = true;
            fail_all = true; 
    }
    
    end_test(test_section, "PR3_EX3_1", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 2  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_2", "Find Latest Tenant [ZYX1234]");
    
    if(!fail_all) {
        failed = false;
        i = findLatestTenant(&tenantList,tenant1.cadastral_ref);
        if (i != 0) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_2", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 3  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_3", "Find Latest Tenant [GHI1234]");
    
    if(!fail_all) {
        failed = false;
        i = findLatestTenant(&tenantList,tenant2.cadastral_ref);
        if (i != 5) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 4  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_4", "Find Latest Tenant [ABC1234]");
    
    if(!fail_all) {
        failed = false;
        i = findLatestTenant(&tenantList,tenant3.cadastral_ref);
        if (i != 2) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_4", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 5  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_5", "Find Latest Tenant [JKL0123]");
    
    if(!fail_all) {
        failed = false;
        i = findLatestTenant(&tenantList,tenant4.cadastral_ref);
        if (i != 8) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_5", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 6  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_6", "Find Latest Tenant [JKL0124]");
    
    if(!fail_all) {
        failed = false;
        i = findLatestTenant(&tenantList,tenant5.cadastral_ref);
        if (i != 4) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_6", !failed);

    /////////////////////////////
    /////  PR3 EX3 TEST 7  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_7", "Find Latest Tenant [ZZZ1111]");
    
    if(!fail_all) {
        failed = false;
        i = findLatestTenant(&tenantList,"ZZZ1111");
        if (i != -1) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_7", !failed);

    /////////////////////////////
    /////  PR3 EX3 TEST 8  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_8", "Find First Tenant [Empty list]");
    failed = false;
    
    i = findFirstTenant(&emptyList,tenant1.cadastral_ref);
    if (i != -1) {
            failed = true;
            fail_all = true; 
    }
    
    end_test(test_section, "PR3_EX3_8", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 9  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_9", "Find First Tenant [ZYX1234]");
    
    if(!fail_all) {
        failed = false;
        i = findFirstTenant(&tenantList,tenant1.cadastral_ref);
        if (i != 9) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_9", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 10 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_10", "Find First Tenant [GHI1234]");
    
    if(!fail_all) {
        failed = false;
        i = findFirstTenant(&tenantList,tenant2.cadastral_ref);
        if (i != 1) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_10", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 11  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_11", "Find First Tenant [ABC1234]");
    
    if(!fail_all) {
        failed = false;
        i = findFirstTenant(&tenantList,tenant3.cadastral_ref);
        if (i != 2) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_11", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 12 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_12", "Find First Tenant [JKL0123]");
    
    if(!fail_all) {
        failed = false;
        i = findFirstTenant(&tenantList,tenant4.cadastral_ref);
        if (i != 7) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_12", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 13  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_13", "Find First Tenant [JKL0124]");
    
    if(!fail_all) {
        failed = false;
        i = findFirstTenant(&tenantList,tenant5.cadastral_ref);
        if (i != 4) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_13", !failed);

    /////////////////////////////
    /////  PR3 EX3 TEST 14 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_14", "Find First Tenant [ZZZ1111]");
    
    if(!fail_all) {
        failed = false;
        i = findFirstTenant(&tenantList,"ZZZ1111");
        if (i != -1) {
            failed = true; 
        }
    } 
    
    end_test(test_section, "PR3_EX3_14", !failed);
    
    
    /////////////////////////////
    /////  PR3 EX3 TEST 15 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_15", "Sort Tenants [Empty List]");
    
    failed = false;
    sortTenantsById_Bubble(&emptyList);
    if (emptyList.count != 0) {
        failed = true;
        fail_all = true;
    }
    
    end_test(test_section, "PR3_EX3_15", !failed);
    
    /////////////////////////////
    /////  PR3 EX3 TEST 16 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX3_16", "Sort Tenants");
    
    if(!fail_all) {
        failed = false;
        sortTenantsById_Bubble(&tenantList);
        if (tenantList.count != 10) {
            failed = true;
        } else if(strcmp(tenantList.elems[0].tenant_id,tenant2.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[1].tenant_id,tenant3.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[2].tenant_id,tenant6.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[3].tenant_id,tenant5.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[4].tenant_id,tenant8.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[5].tenant_id,tenant9.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[6].tenant_id,tenant4.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[7].tenant_id,tenant7.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[8].tenant_id,tenant1.tenant_id)!=0) {
            failed = true;
        } else if(strcmp(tenantList.elems[9].tenant_id,tenant10.tenant_id)!=0) {
            failed = true;
        }
    } 
    
    end_test(test_section, "PR3_EX3_16", !failed);
 
    passed = passed && !fail_all && !failed;

    
    tenant_free(&tenant1);
    tenant_free(&tenant2);
    tenant_free(&tenant3);
    tenant_free(&tenant4);
    tenant_free(&tenant5);
    tenant_free(&tenant6);
    tenant_free(&tenant7);
    tenant_free(&tenant8);
    tenant_free(&tenant9);
    tenant_free(&tenant10);
    tenantData_free(&emptyList);
    tenantData_free(&tenantList);
    return passed;
}

// Run all tests for Exercice 4 of PR3
bool run_pr3_ex4(tTestSection * test_section,
    const char * input) {
    
    tApiData data,emptyData;
    tApiError error;
    tCSVData report;
    tCSVEntry CSVEntry;
    tTaxOfficeNode *taxOfficeNode;
    tRentInvoiceMonthly *RentInvoiceMonthly;
    int i, year, month;
    char bufferStr[2048];

    bool passed = true;
    bool failed = false;
    bool fail_all = false;
    
    error = api_initData( &emptyData);
    error = api_initData( &data);
    error = api_loadData( &data, input, true);



    
    /////////////////////////////
    /////  PR3 EX4 TEST 1  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_1", "Get Monthly Invoices [Empty list]");
    
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef(emptyData,"ZYX1234",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=0) {
            failed = true;
            fail_all = true; 
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_1", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 2  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_2", "Get Monthly Invoices  [ZYX1234]");
    
    failed = false;
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef(data,"ZYX1234",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=36) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 1+(8+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2020+(8+i)/12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2023 && csv_getAsReal(report.entries[i], 3) != 1000.0) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2021 && csv_getAsReal(report.entries[i], 3) != 2000.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"ZYX1234")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_2", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 3  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_3", "Get Monthly Invoices  [GHI1234]");
    
    failed = false;
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef(data,"GHI1234",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=15) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 1+i%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2023+i/12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2023 && csv_getAsReal(report.entries[i], 3) != 1400.0) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2024 && csv_getAsInteger(report.entries[i], 1) == 1 && csv_getAsReal(report.entries[i], 3) != 1000.0) {
                failed = true;
            }  else if(csv_getAsInteger(report.entries[i], 2) == 2024 && csv_getAsInteger(report.entries[i], 1) != 1 && csv_getAsReal(report.entries[i], 3) != 400.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"GHI1234")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }

    csv_free(&report);
    end_test(test_section, "PR3_EX4_3", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 4  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_4", "Get Monthly Invoices  [SSD9729]");
    
    failed = false;
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef(data,"SSD9729",&report);
    
    if (error != E_SUCCESS) {
            failed = true; 
    }
    else if (report.count !=19) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 1+(3+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2022+(3+i)/12) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 100.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"SSD9729")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_4", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 5  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_5", "Get Monthly Invoices  [JKL0124]");
    
    failed = false;
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef(data,"JKL0124",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=312) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 1+(2+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2022+(2+i)/12) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 3141.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"JKL0124")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_5", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 6  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_6", "Get Monthly Invoices  [FTZ9174]");
    
    failed = false;
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef(data,"FTZ9174",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=30) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 1+(4+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2021+(4+i)/12) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 10.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"FTZ9174")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_6", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 7  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_7", "Get Monthly Invoices Reverse [Empty list]");
    
    failed = false;
    error = api_getMonthlyInvoiceByCadastralRef_Reverse(emptyData,"ZYX1234",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=0) {
            failed = true;
            fail_all = true; 
    }
    csv_free(&report);   
    end_test(test_section, "PR3_EX4_7", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 8  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_8", "Get Monthly Invoices Reverse  [ZYX1234]");
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef_Reverse(data,"ZYX1234",&report);
    failed = false;
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=36) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 12-(4+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2023-(4+i)/12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2023 && csv_getAsReal(report.entries[i], 3) != 1000.0) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2021 && csv_getAsReal(report.entries[i], 3) != 2000.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"ZYX1234")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_8", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 9  //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_9", "Get Monthly Invoices Reverse  [GHI1234]");
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef_Reverse(data,"GHI1234",&report);
    
    failed = false;
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=15) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 12-(9+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2024-(9+i)/12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2023 && csv_getAsReal(report.entries[i], 3) != 1400.0) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2) == 2024 && csv_getAsInteger(report.entries[i], 1) == 1 && csv_getAsReal(report.entries[i], 3) != 1000.0) {
                failed = true;
            }  else if(csv_getAsInteger(report.entries[i], 2) == 2024 && csv_getAsInteger(report.entries[i], 1) != 1 && csv_getAsReal(report.entries[i], 3) != 400.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"GHI1234")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }

    csv_free(&report);
    end_test(test_section, "PR3_EX4_9", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 10 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_10", "Get Monthly Invoices Reverse  [SSD9729]");
    csv_init(&report);
    error = api_getMonthlyInvoiceByCadastralRef_Reverse(data,"SSD9729",&report);
    
    failed = false;
    if (error != E_SUCCESS) {
            failed = true; 
    }
    else if (report.count !=19) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 12-(2+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2023-(2+i)/12) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 100.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"SSD9729")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_10", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 11 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_11", "Get Monthly Invoices Reverse  [JKL0124]");
    csv_init(&report);
    failed = false;    
    error = api_getMonthlyInvoiceByCadastralRef_Reverse(data,"JKL0124",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=312) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 12-(10+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2048-(10+i)/12) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 3141.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"JKL0124")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_11", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 12 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_12", "Get Monthly Invoices Reverse  [FTZ9174]");
    csv_init(&report);
    failed = false;
    error = api_getMonthlyInvoiceByCadastralRef_Reverse(data,"FTZ9174",&report);
    
    if (error != E_SUCCESS) {
            failed = true;
    }
    else if (report.count !=30) {
            failed = true;
    }else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 12-(2+i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2023-(2+i)/12) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 10.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"FTZ9174")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_12", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 13 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_13", "Get Monthly Invoices Tax Office  [Empty data]");
    
    failed = false;
    error = api_getMonthlyInvoicebyRent(emptyData,"BA08001",&report);
    
    if (error != E_SUCCESS) {
        failed = true;
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_13", !failed);
    
   
    /////////////////////////////
    /////  PR3 EX4 TEST 14 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_14", "Get Monthly Invoices Tax Office  [Empty data]");
    csv_init(&report);
    failed = false;
    error = api_getMonthlyInvoicebyRent(emptyData,"BA08001",&report);
    
    if (error != E_SUCCESS) {
        failed = true;
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_14", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 15 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_15", "Get Monthly Invoices Tax Office  [BA08001]");
    csv_init(&report);
    failed = false;
    error = api_getMonthlyInvoicebyRent(data,"BA08001",&report);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (report.count != 12) {
        failed = true;
    } else{
        i = 0;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 1)!= 1+(i)%12) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 2)!= 2022) {
                failed = true;
            } else if(csv_getAsReal(report.entries[i], 3) != 800.0) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if (strcmp(bufferStr,"ABC1234")!=0) {
                    failed = true;
                }
            }
            i++;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_15", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 16 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_16", "Get Monthly Invoices Tax Office  [LE24003]");
    csv_init(&report);
    failed = false;
    error = api_getMonthlyInvoicebyRent(data,"LE24003",&report);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (report.count != 97) {
        failed = true;
    } else{
        i = 0;
        year = -1;
        month = -1;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if (year > csv_getAsInteger(report.entries[i], 2) && i <72) {
                failed = true;
                
            } else if ((year == csv_getAsInteger(report.entries[i], 2)) && month > csv_getAsInteger(report.entries[i], 1) && i<72) {
                failed = true;
            } else if (i == 72 && csv_getAsInteger(report.entries[i], 2) != 2022 && csv_getAsInteger(report.entries[i], 1) != 4) {
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if(strcmp(bufferStr,"FTZ9174") == 0 && csv_getAsReal(report.entries[i], 3) != 10.0){
                    failed = true;
                } else if(strcmp(bufferStr,"FTZ9173") == 0 && csv_getAsReal(report.entries[i], 3) != 50.0){
                    failed = true;
                } else if(strcmp(bufferStr,"KWV1417") == 0 && csv_getAsReal(report.entries[i], 3) != 20.0){
                    failed = true;
                } else if(strcmp(bufferStr,"SSD9729") == 0 && csv_getAsReal(report.entries[i], 3) != 100.0){
                    failed = true;
                }
            }
            year = csv_getAsInteger(report.entries[i], 2);
            month = csv_getAsInteger(report.entries[i], 1);
            i++;
        }
        
        taxOfficeNode= data.taxOffices.first->next;
        RentInvoiceMonthly=taxOfficeNode->elem.rentInvoices.first;
        while(RentInvoiceMonthly->next != NULL) {
            if(date_cmp(RentInvoiceMonthly->month,RentInvoiceMonthly->next->month)>0) {
                failed = true;
            }
            RentInvoiceMonthly = RentInvoiceMonthly->next;
        }
    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_16", !failed);
 
    /////////////////////////////
    /////  PR3 EX4 TEST 17 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_17", "Get Monthly Invoices Tax Office  [BA08001]");
    csv_init(&report);
    failed = false;
    error = api_getMonthlyInvoicebyRent(data,"BA08001",&report);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (report.count != 12) {
        failed = true;
    } else{
        i = 0;
        year = -1;
        month = -1;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if (csv_getAsInteger(report.entries[i], 2)!=2022) {
                failed = true;
            } else if (month > csv_getAsInteger(report.entries[i], 1) ) {
                failed = true;
            } if (csv_getAsReal(report.entries[i], 3) != 800.0){
                failed = true;
            } else {
                csv_getAsString(report.entries[i], 4, bufferStr, MAX_CADASTRAL_REF+1);
                if(strcmp(bufferStr,"ABC1234") != 0){
                    failed = true; 
                }
            }
            
            month = csv_getAsInteger(report.entries[i], 1);
            i++;
        }
        
        taxOfficeNode= data.taxOffices.first;
        RentInvoiceMonthly=taxOfficeNode->elem.rentInvoices.first;
        while(RentInvoiceMonthly->next != NULL) {
            if(date_cmp(RentInvoiceMonthly->month,RentInvoiceMonthly->next->month)>0) {
                failed = true;
            }
            RentInvoiceMonthly = RentInvoiceMonthly->next;
        }

    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_17", !failed); 

    /////////////////////////////
    /////  PR3 EX4 TEST 18 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_18", "Get Monthly Invoices Tax Office  [BA08005]");
    csv_init(&report);
    failed = false;
    error = api_getMonthlyInvoicebyRent(data,"BA08005",&report);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (report.count != 336) {
        failed = true;
    } else{
        i = 0;
        year = -1;
        month = -1;
        while(i<report.count && !failed) {
            //"INVOICE"
            if(strcmp(report.entries[i].type, "INVOICE")!=0 ||report.entries[i].numFields!=5) {
                failed = true;
            } else if(csv_getAsInteger(report.entries[i], 0)!=1) {
                failed = true;
            } else if (i<5 && (csv_getAsInteger(report.entries[i], 2)!=2021 || month > csv_getAsInteger(report.entries[i], 1) || csv_getAsReal(report.entries[i], 3) != 10000.0)) {
                failed = true;
            } else if (i>5 && i <13 && (csv_getAsInteger(report.entries[i], 2)!=2022)) {
                failed = true;
            }  else if (i>38 && i <334 && (csv_getAsReal(report.entries[i], 3)!=3141.0)) {
                failed = true;
            }
            
            month = csv_getAsInteger(report.entries[i], 1);
            i++;
        }
        
        taxOfficeNode= data.taxOffices.first;
        RentInvoiceMonthly=taxOfficeNode->elem.rentInvoices.first;
        while(RentInvoiceMonthly->next != NULL) {
            if(date_cmp(RentInvoiceMonthly->month,RentInvoiceMonthly->next->month)>0) {
                failed = true;
            }
            RentInvoiceMonthly = RentInvoiceMonthly->next;
        }

    }
    csv_free(&report);
    end_test(test_section, "PR3_EX4_18", !failed); 
    
    /////////////////////////////
    /////  PR3 EX4 TEST 19 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_19", "Get Address By Cadastral Reference  [Empty data]");

    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_getAddressByCadastralRef(emptyData,"ZYX1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (CSVEntry.numFields!=0) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_19", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 20 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_20", "Get Address By Cadastral Reference  [ZYX1234]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_getAddressByCadastralRef(data,"ZYX1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (CSVEntry.numFields!=2) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"ADDRESS")!=0) {
        failed = true;
    } else if (csv_getAsInteger(CSVEntry, 1)!=900) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, MAX_STREET);
        if(strcmp(bufferStr,"Main Street") != 0){
            failed = true; 
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_20", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 21 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_21", "Get Address By Cadastral Reference  [FTZ9173]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_getAddressByCadastralRef(data,"FTZ9173",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (CSVEntry.numFields!=2) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"ADDRESS")!=0) {
        failed = true;
    } else if (csv_getAsInteger(CSVEntry, 1)!=204) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, MAX_STREET);
        if(strcmp(bufferStr,"Main Street") != 0){
            failed = true; 
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_21", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 22 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_22", "Get Address By Cadastral Reference  [SSD9729]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_getAddressByCadastralRef(data,"SSD9729",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (CSVEntry.numFields!=2) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"ADDRESS")!=0) {
        failed = true;
    } else if (csv_getAsInteger(CSVEntry, 1)!=388) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, MAX_STREET);
        if(strcmp(bufferStr,"Lake Avenue") != 0){
            failed = true; 
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_22", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 23 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_23", "Sort Lanlords  [Empty data]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_sortLandlordsByName(&emptyData);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (emptyData.landlords.count != 0) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_23", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 24 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_24", "Sort Lanlords");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_sortLandlordsByName(&data);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (data.landlords.count != 3) {
        failed = true;
    } else if (data.landlords.elems[0].properties.count != 2) {
        failed = true;
    } else if (data.landlords.elems[1].properties.count != 8) {
        failed = true;
    } else if (data.landlords.elems[2].properties.count != 1) {
        failed = true;
    } else if (strcmp(data.landlords.elems[0].properties.elems[0].cadastral_ref,"FTZ9173") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[0].properties.elems[1].cadastral_ref,"KWV1417") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[0].cadastral_ref,"ABC1234") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[1].cadastral_ref,"EPY1713") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[2].cadastral_ref,"GHI1234") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[3].cadastral_ref,"JKL0123") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[4].cadastral_ref,"JKL0124") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[5].cadastral_ref,"SSD9729") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[6].cadastral_ref,"WJY6414") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[1].properties.elems[7].cadastral_ref,"ZYX1234") !=0) {
        failed = true;
    } else if (strcmp(data.landlords.elems[2].properties.elems[0].cadastral_ref,"FTZ9174") !=0) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_24", !failed);
    

    /////////////////////////////
    /////  PR3 EX4 TEST 25 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_25", "Find Last Tenant [Empty data]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findLatestTenant(emptyData,"ABC1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (CSVEntry.numFields != 0) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_25", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 26 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_26", "Find Last Tenant [ABC1234]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findLatestTenant(data,"ABC1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/01/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/12/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "12345679B") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Ana Fernandez") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 800.0 || csv_getAsInteger(CSVEntry, 5) !=41 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "ABC1234") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "BA08001") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_26", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 27 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_27", "Find Last Tenant [JKL0123]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findLatestTenant(data,"JKL0123",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/09/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/07/2023") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "87654321Z") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Maria Jackson") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 1300.0 || csv_getAsInteger(CSVEntry, 5) !=50 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "JKL0123") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "BA08005") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_27", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 28 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_28", "Find Last Tenant [FTZ9173]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findLatestTenant(data,"FTZ9173",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/05/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/10/2023") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "T008") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Duang Chen") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 50.0 || csv_getAsInteger(CSVEntry, 5) !=45 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "FTZ9173") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "LE24003") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_28", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 29 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_29", "Find First Tenant [Empty data]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(emptyData,"ABC1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (CSVEntry.numFields != 0) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_29", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 30 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_30", "Find First Tenant [ABC1234]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(data,"ABC1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/01/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/12/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "12345679B") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Ana Fernandez") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 800.0 || csv_getAsInteger(CSVEntry, 5) !=41 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "ABC1234") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "BA08001") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_30", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 31 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_31", "Find First Tenant [JKL0123]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(data,"JKL0123",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/08/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/12/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "4444321Z") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Iker Garcia") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 10000.0 || csv_getAsInteger(CSVEntry, 5) !=50 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "JKL0123") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "BA08005") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_31", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 32 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_32", "Find First Tenant [FTZ9173]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(data,"FTZ9173",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/05/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/10/2023") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "T008") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Duang Chen") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 50.0 || csv_getAsInteger(CSVEntry, 5) !=45 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "FTZ9173") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "LE24003") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_32", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 33 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_33", "Sort Tenants  [Empty data]");
    
    failed = false;
    error = api_sortTenantsById(&emptyData);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (emptyData.tenants.count != 0) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_33", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 34 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_34", "Sort Tenants ");
    
    failed = false;
    error = api_sortTenantsById(&data);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (data.tenants.count != 16) {
        failed = true;
    } else if (strcmp(data.tenants.elems[0].tenant_id,"12345678A")!=0 || strcmp(data.tenants.elems[0].name,"Jason Garcia")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[1].tenant_id,"12345679B")!=0 || strcmp(data.tenants.elems[1].name,"Ana Fernandez")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[2].tenant_id,"22244678A")!=0 || strcmp(data.tenants.elems[2].name,"Smith Potter")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[3].tenant_id,"31415926P")!=0 || strcmp(data.tenants.elems[3].name,"Peter Thomson")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[4].tenant_id,"3334321Z")!=0 || strcmp(data.tenants.elems[4].name,"Helena Jackson")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[5].tenant_id,"4444321Z")!=0 || strcmp(data.tenants.elems[5].name,"Iker Garcia")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[6].tenant_id,"87654321Z")!=0 || strcmp(data.tenants.elems[6].name,"Maria Jackson")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[7].tenant_id,"88899978T")!=0 || strcmp(data.tenants.elems[7].name,"Niels Geuder")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[8].tenant_id,"T001")!=0 || strcmp(data.tenants.elems[8].name,"John Doe")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[9].tenant_id,"T002")!=0 || strcmp(data.tenants.elems[9].name,"Mary Doe")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[10].tenant_id,"T003")!=0 || strcmp(data.tenants.elems[10].name,"Ling Dong")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[11].tenant_id,"T004")!=0 || strcmp(data.tenants.elems[11].name,"Xiao Ping")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[12].tenant_id,"T005")!=0 || strcmp(data.tenants.elems[12].name,"Mao Zhuang")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[13].tenant_id,"T006")!=0 || strcmp(data.tenants.elems[13].name,"Meili Wang")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[14].tenant_id,"T007")!=0 || strcmp(data.tenants.elems[14].name,"Huang Zhao")) {
        failed = true;
    } else if (strcmp(data.tenants.elems[15].tenant_id,"T008")!=0 || strcmp(data.tenants.elems[15].name,"Duang Chen")) {
        failed = true;
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_34", !failed);
    
        /////////////////////////////
    /////  PR3 EX4 TEST 35 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_35", "Find First Tenant - after sorting [ABC1234]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(data,"ABC1234",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/01/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/12/2022") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "12345679B") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Ana Fernandez") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 800.0 || csv_getAsInteger(CSVEntry, 5) !=41 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "ABC1234") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "BA08001") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_35", !failed);

    /////////////////////////////
    /////  PR3 EX4 TEST 36 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_36", "Find First Tenant - after sorting [JKL0123]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(data,"JKL0123",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/08/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/12/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "4444321Z") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Iker Garcia") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 10000.0 || csv_getAsInteger(CSVEntry, 5) !=50 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "JKL0123") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "BA08005") !=0) {
            failed = true;
        }
    }

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_36", !failed);
    
    /////////////////////////////
    /////  PR3 EX4 TEST 37 //////
    /////////////////////////////
    start_test(test_section, "PR3_EX4_37", "Find First Tenant - after sorting [FTZ9173]");
    
    failed = false;
    csv_initEntry(&CSVEntry);
    error = api_findFirstTenant(data,"FTZ9173",&CSVEntry);
    
    if (error != E_SUCCESS) {
        failed = true;
    } else if (strcmp(CSVEntry.type,"TENANT")!=0) {
        failed = true;
    } else if (CSVEntry.numFields != 8) {
        failed = true;
    } else {
        csv_getAsString(CSVEntry, 0, bufferStr, 11);
        if(strcmp(bufferStr, "01/05/2021") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 1, bufferStr, 12);
        if(strcmp(bufferStr, "31/10/2023") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 2, bufferStr, MAX_PERSON_ID+1);
        if(strcmp(bufferStr, "T008") !=0) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 3, bufferStr, MAX_NAME+1);
        if(strcmp(bufferStr, "Duang Chen") !=0) {
            failed = true;
        }
    
        if(csv_getAsReal(CSVEntry, 4) != 50.0 || csv_getAsInteger(CSVEntry, 5) !=45 ) {
            failed = true;
        }
        csv_getAsString(CSVEntry, 6, bufferStr, MAX_CADASTRAL_REF+1);
        if(strcmp(bufferStr, "FTZ9173") !=0) {
            failed = true;
        }
        
        csv_getAsString(CSVEntry, 7, bufferStr, MAX_POSTAL_CODE+1);
        if(strcmp(bufferStr, "LE24003") !=0) {
            failed = true;
        }
    }
    

    csv_freeEntry(&CSVEntry);
    end_test(test_section, "PR3_EX4_37", !failed);
    
    passed = passed && !fail_all && !failed;
    
    csv_freeEntry(&CSVEntry);
    csv_free(&report);
    api_freeData(&emptyData);
    api_freeData(&data);

    return passed;
}