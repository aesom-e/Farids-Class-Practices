#ifndef ERROR_H
#define ERROR_H

#include <stdarg.h>

_Noreturn void __error(int lineNumber, const char* fileName, const char* format, ...);

#define error(___format, ...) __error(__LINE__, __FILE__, ___format, ##__VA_ARGS__)

#endif