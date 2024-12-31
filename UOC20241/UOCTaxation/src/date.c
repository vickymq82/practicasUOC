#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "date.h"

// Parse a tDate from string information
void date_parse(tDate* date, const char* text)
{
    // Check output data
    assert(date != NULL);
    
    // Check input date
    assert(text != NULL);
    assert(strlen(text) == DATE_LENGTH);
 
    // Parse the input date
    sscanf(text, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Copy a date from src to dst
void date_cpy(tDate *dst, tDate src) {
    // Check output data
    assert(dst != NULL);
    
    dst->day = src.day;
    dst->month = src.month;
    dst->year = src.year;
}

// Compare two dates
int date_cmp(tDate date1, tDate date2) {
    // Checkl year
    if (date1.year < date2.year) {
        return -1;
    }
    if (date1.year > date2.year) {
        return 1;
    }
    // Check month
    if (date1.month < date2.month) {
        return -1;
    }
    if (date1.month > date2.month) {
        return 1;
    }  
    // Check day
    if (date1.day < date2.day) {
        return -1;
    }
    if (date1.day > date2.day) {
        return 1;
    }
    
    return 0;
}

// Parse a tDateTime from string information
void dateTime_parse(tDateTime* dateTime, const char* date, const char* time) {
    // Check output data
    assert(dateTime != NULL);
    
    // Check input date
    assert(date != NULL);
    assert(strlen(date) == 10);
    
    // Check input time
    assert(time != NULL);
    assert(strlen(time) == 5);
    
    // Parse the input date
    sscanf(date, "%d/%d/%d", &(dateTime->date.day), &(dateTime->date.month), &(dateTime->date.year));
    
    // Parse the input time
    sscanf(time, "%d:%d", &(dateTime->time.hour), &(dateTime->time.minutes));
}

// Compare two tDateTime structures and return -1 if dateTime1<dateTime2, 0 if equals and 1 if dateTime1>dateTime2.
int dateTime_cmp(tDateTime dateTime1, tDateTime dateTime2) {    
    // Checkl year
    if (dateTime1.date.year < dateTime2.date.year) {
        return -1;
    }
    if (dateTime1.date.year > dateTime2.date.year) {
        return 1;
    }
    // Check month
    if (dateTime1.date.month < dateTime2.date.month) {
        return -1;
    }
    if (dateTime1.date.month > dateTime2.date.month) {
        return 1;
    }  
    // Check day
    if (dateTime1.date.day < dateTime2.date.day) {
        return -1;
    }
    if (dateTime1.date.day > dateTime2.date.day) {
        return 1;
    }
    // Check hour
    if (dateTime1.time.hour < dateTime2.time.hour) {
        return -1;
    }
    if (dateTime1.time.hour > dateTime2.time.hour) {
        return 1;
    }
    // Check minutes
    if (dateTime1.time.minutes < dateTime2.time.minutes) {
        return -1;
    }
    if (dateTime1.time.minutes > dateTime2.time.minutes) {
        return 1;
    }
    
    return 0;
}

// Compare two tDateTime structures and return true if they contain the same value or false otherwise.
bool dateTime_equals(tDateTime dateTime1, tDateTime dateTime2) {
    return dateTime_cmp(dateTime1, dateTime2) == 0;
}

// Initialize a time structure
void dateTime_initTime(struct tm *std_time, tDateTime timestamp) {
    std_time->tm_sec = 0;
    std_time->tm_min = timestamp.time.minutes;
    std_time->tm_hour = timestamp.time.hour;
    std_time->tm_mday = timestamp.date.day;
    std_time->tm_mon = timestamp.date.month - 1;
    std_time->tm_year = timestamp.date.year - 1900;    
    
    // Upate the date
    mktime(std_time);
}

// Initialize a time structure
void dateTime_fromTime(tDateTime *timestamp, struct tm std_time) {
    
    assert (timestamp != NULL);

    timestamp->time.minutes = std_time.tm_min;
    timestamp->time.hour = std_time.tm_hour;
    timestamp->date.day = std_time.tm_mday;
    timestamp->date.month = std_time.tm_mon + 1;
    timestamp->date.year = std_time.tm_year + 1900;    
}


// Add a months to a given date
void dateTime_addMonth(tDateTime* dateTime, int months) {
    struct tm initTimestamp = { 0 };   
    assert(dateTime != NULL);
    
    // Get standard time representation
    dateTime_initTime(&initTimestamp, *dateTime);
    
    // Add the number of months    
    initTimestamp.tm_mon += months;
    
    // Upate the date
    (void)mktime(&initTimestamp);
    
    // Update output structure
    dateTime_fromTime(dateTime, initTimestamp);
}



// Add months to a given date
void date_addMonth(tDate* date, int months) {
    tDateTime timestamp;
    
    assert(date != NULL);

    timestamp.date = *date;
    timestamp.time.hour = 0;
    timestamp.time.minutes = 0;
    
    dateTime_addMonth(&timestamp, months);
    
    *date = timestamp.date;
}
