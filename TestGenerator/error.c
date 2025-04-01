#include <stdio.h>
#include <stdlib.h>
#include "error.h"

_Noreturn void __error(int lineNumber, const char* fileName, const char* format, ...) {
    if(!format) exit(0);

    fprintf(stderr, "Error at %s:%d: ", fileName, lineNumber);
    va_list argv;
    va_start(argv, format);
    vfprintf(stderr, format, argv);
    va_end(argv);

    exit(1);
}