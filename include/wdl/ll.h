#ifndef WDL_LL_H
#define WDL_LL_H

#include <stdbool.h>
#include <stddef.h>

struct wdl_ll {
	struct wdl_llnode* root;
};

struct wdl_llnode {
	char word[6];
	int prty;
	struct wdl_llnode* next;
};

void wdl_ll_init(struct wdl_ll* ll);

void wdl_ll_insert(struct wdl_ll* ll, char* word);

bool wdl_ll_check(struct wdl_ll* ll, char* word);

void wdl_ll_insert_p(struct wdl_ll* ll, char* word, int prty);

void wdl_ll_print(struct wdl_ll* ll);

size_t wdl_ll_len(struct wdl_ll* ll);

#endif
