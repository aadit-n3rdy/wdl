#ifndef WDL_GEN_H
#define WDL_GEN_H

#include "wdl/dict.h"

#include <stdlib.h>
#include <time.h>

void wdl_gen_init(unsigned int seed);

void wdl_gen(struct wdl_dict *d, char* w);


#endif
