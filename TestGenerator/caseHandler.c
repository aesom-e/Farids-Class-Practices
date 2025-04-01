#include <stdio.h>
#include "constants.h"
#include "error.h"
#include "caseHandler.h"

int caseHandler_GetNextCase(char* programNumber) {
    int numbers[3];
    if(sscanf(programNumber, "%d-%d-%d", &(numbers[0]), &(numbers[1]), &(numbers[2])) != 3)
        error("Invalid program number: %s\n", programNumber);
    
    // Get the name of the directory
    char dirName[MAX_PROGRAM_PATH_SIZE];
    snprintf(dirName, MAX_PROGRAM_PATH_SIZE, "C:/PyCharm/CompSci11/Classroom/Practices-E-Sadler_REAL/Practices-E-Sadler/tests/%02d-%02d-%02d/",
                     numbers[0], numbers[1], numbers[2]);
    
    // Find what the first unwritten test number is
    int number = 1;
    char testName[MAX_PROGRAM_PATH_SIZE+10];
    while(1) {
        snprintf(testName, MAX_PROGRAM_PATH_SIZE+10, "%s1-%02d.in", dirName, number);
        FILE* file = fopen(testName, "r");
        if(!file) continue;
        fclose(file);
        break;
    }

    return number;
}