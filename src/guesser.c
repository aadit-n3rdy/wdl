#include "wdl/guesser.h"

#include "wdl/dict.h"
#include "wdl/ll.h"
#include "wdl/utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static inline bool is_valid(char c) {
	return (c >= 'a' && c <= 'z');
}

static inline int char_index(char c) {
	return (is_valid(c)) ? c-'a' : -1;
}

void wdl_guesser_init(struct wdl_guesser* g, struct wdl_dict* d) {
	memset(g, 0, sizeof(struct wdl_guesser));
	memset(g->known, '?', sizeof(g->known)-1);
	g->d = d;
	g->cur = d->prty.root;
}

void wdl_guesser_reset(struct wdl_guesser* g) {
	wdl_guesser_init(g, g->d);
}

static void calc_wm(char* w, char* wm) {
	memset(wm, 0, 26);
	for (int i = 0; i < 5; i++) {
		if (is_valid(w[i])) {
			wm[char_index(w[i])]++;
		}
	}
}

void wdl_guesser_guess(struct wdl_guesser* g, char* guess) {
	bool done = false;
	int i = 0;
	char cur_wm[26] = {0};
	while (g->cur) {
		done = true;
		for (i = 0; i < 5; i++) {
			if (is_valid(g->known[i]) && g->known[i] != g->cur->word[i]) {
				done = false;
				goto next;
			}
		}
		calc_wm(g->cur->word, cur_wm);
		for (i = 0; i < 26; i++) {
			if (g->maxcap & (1<<(i))) {
				if (g->wordmap[i] != cur_wm[i]) {
					done = false;
					goto next;
				}
			} else {
				if (g->wordmap[i] > cur_wm[i]) {
					done = false;
					goto next;
				}
			}
		}
next:
		if (done) {
			break;
		} else {
			g->cur = g->cur->next;
		}
	}
	if (g->cur == NULL) {
		exit(-1);
	}
	strcpy(guess, g->cur->word);
	g->cur = g->cur->next;
}

void wdl_guesser_update(struct wdl_guesser* g, char* guess, char* result) {
	memset(g->wordmap, 0, sizeof(g->wordmap));
	for (int i = 0; i < 5; i++) {
		if (result[i] == WDL_GREEN) {
			g->known[i] = guess[i];
			g->wordmap[char_index(guess[i])]++;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (result[i] == WDL_YELLOW) {
			g->wordmap[char_index(guess[i])]++;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (result[i] == WDL_RED) {
			g->maxcap = g->maxcap | (1<<(char_index(guess[i])));
		}
	}

}
