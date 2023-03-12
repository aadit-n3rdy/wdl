#ifndef WDL_DICT_H
#define WDL_DICT_H

#include "ll.h"

#include <stdbool.h>

#define BUCKET_COUNT 128

struct wdl_dict {
	struct wdl_ll bkts[128];
	struct wdl_ll prty;
	size_t word_count;
};

void wdl_dict_init(struct wdl_dict* d);

void wdl_dict_insert(struct wdl_dict* d, char* word);

bool wdl_dict_check(struct wdl_dict* d, char* word);

void wdl_dict_gen_prty(struct wdl_dict* d);

void wdl_dict_load(struct wdl_dict* d, const char* fname);

#endif
