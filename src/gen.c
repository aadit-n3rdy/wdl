#include "wdl/gen.h"

#include <stdlib.h>
#include <string.h>

void wdl_gen(struct wdl_dict *d, char* w) {
	size_t i = (size_t)random() % d->word_count;
	struct wdl_llnode* cur = d->prty.root;
	for(size_t j = 0; j < i; j++) {
		cur = cur->next;
	}
	strcpy(w, cur->word);
}

void wdl_gen_init(unsigned int seed) {
	if (seed == 0) {
		seed = time(NULL);
	}
	srandom(seed);
}
