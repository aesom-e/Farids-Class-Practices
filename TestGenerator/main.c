#include <stdio.h>
#include <stdlib.h>
#include "programHandler.h"
#include "caseHandler.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: %s <Program Number>\n", argv[0]);
        return 1;
    }

    // Run the program and get the input/output
    char* name = programHandler_GetProgramName(argv[1]);
    char** programIO = programHandler_RunPythonProgram(name);
    free(name);

    // Get the next test number
    int nextTestNumber = caseHandler_GetNextCase(argv[1]);
    printf("Next test number: %d\n", nextTestNumber);

    free(programIO[0]);
    free(programIO[1]);
    free(programIO);
}