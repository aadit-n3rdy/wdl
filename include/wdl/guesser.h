#ifndef WDL_GUESSER_H
#define WDL_GUESSER_H

#include "wdl/dict.h"

struct wdl_guesser {
	char known[6];
	unsigned int elim_o[5];
	unsigned int elim;
	char wordmap[26]; //no. of occurence of each letter
	unsigned int maxcap; //nth bit is 1 if nth letter has been xd
	struct wdl_dict *d;
	struct wdl_llnode *cur;
};

void wdl_guesser_init(struct wdl_guesser* g, struct wdl_dict* d);

void wdl_guesser_reset(struct wdl_guesser* g);

void wdl_guesser_guess(struct wdl_guesser* g, char* guess);

void wdl_guesser_update(struct wdl_guesser* g, char* guess, char* result);

#endif
