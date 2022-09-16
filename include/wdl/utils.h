#ifndef WDL_UTILS_H
#define WDL_UTILS_H

#include <stdbool.h>

#define WDL_GREEN 'V'
#define WDL_YELLOW 'O'
#define WDL_RED 'x'

bool wdl_streq(char* s1, char* s2);

void wdl_strcmp(char* word, char* guess, char* result);

#endif
