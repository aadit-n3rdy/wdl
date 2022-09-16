#include "wdl/dict.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static unsigned int hash(char* word) {
	unsigned int result = 0;
	for (int i = 0; word[i] != '\0'; i++) {
		result += word[i] - 'a';
		result = (result << 7) + result;
	}
	return result % BUCKET_COUNT;
}

void wdl_dict_init(struct wdl_dict* d) {
	memset(d, 0, sizeof(struct wdl_dict));
}

void wdl_dict_insert(struct wdl_dict* d, char* word) {
	unsigned int h = hash(word);
	wdl_ll_insert(&d->bkts[h], word);
}

bool wdl_dict_check(struct wdl_dict* d, char* word) {
	unsigned int h = hash(word);
	return wdl_ll_check(&d->bkts[h], word);
}

static int calc_priority(char* word, int* freq) {
	int p = 0;
	unsigned int bitmap = 0;
	int diff;
	for (; *word != '\0'; word++) {
		diff = *word - 'a';
		if (((1<<diff) & bitmap) == 0) {
			bitmap = bitmap | (1<<diff);
			p += freq[diff];
		}
	}
	return p;
}

void wdl_dict_gen_prty(struct wdl_dict* d) {
	int freq[26] = {0};
	char *w;
	struct wdl_llnode* cur;
	for (int i = 0; i < BUCKET_COUNT; i++) {
		cur = d->bkts[i].root;
		while (cur) {
			w = cur->word;
			while (*w != '\0') {
				if (*w >= 'a' && *w <= 'z') {
					freq[*w - 'a']++;
				}
				w++;
			}
			cur = cur->next;
		}
	}
	for (int i = 0; i < BUCKET_COUNT; i++) {
		cur = d->bkts[i].root;
		while (cur != NULL) {
			w = cur->word;
			wdl_ll_insert_p(&d->prty, w, calc_priority(w, freq));
			cur = cur->next;
		}
	}
	d->word_count = wdl_ll_len(&d->prty);
}

void wdl_dict_load(struct wdl_dict* d, const char* fname) {
	FILE* fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("ERROR OPENING FILE\n");
	}
	char buf[5];
	wdl_dict_init(d);
	while (fscanf(fp, "%5s", buf) != EOF) {
		wdl_dict_insert(d, buf);
	}
	fclose(fp);
	wdl_dict_gen_prty(d);
}
