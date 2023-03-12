#include "wdl/ll.h"

#include "wdl/utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

static struct wdl_llnode* create_node(char* word, int prty) {
	struct wdl_llnode* ptr = malloc(sizeof(struct wdl_llnode));
	strcpy(ptr->word, word);
	ptr->next = NULL;
	ptr->prty = prty;
	return ptr;
}

void wdl_ll_print(struct wdl_ll* ll) {
	struct wdl_llnode* cur = ll->root;
	while (cur) {
		printf("%s, %d\n", cur->word, cur->prty);
		cur = cur->next;
	}
}

void wdl_ll_init(struct wdl_ll* ll) {
	ll->root = NULL;
}

void wdl_ll_insert(struct wdl_ll* ll, char* word) {
	struct wdl_llnode* tmp = ll->root;
	ll->root = create_node(word, 0);
	ll->root->next = tmp;
}

bool wdl_ll_check(struct wdl_ll* ll, char* word) {
	struct wdl_llnode* tmp = ll->root;
	while (tmp) {
		if (wdl_streq(tmp->word, word)) {
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

void wdl_ll_insert_p(struct wdl_ll* ll, char* word, int prty) {
	struct wdl_llnode* cur = ll->root;
	if (cur == NULL) {
		ll->root = create_node(word, prty);
		return;
	}
	if (cur->prty < prty) {
		ll->root = create_node(word, prty);
		ll->root->next = cur;
		return;
	}
	while (cur->next != NULL && cur->next->prty > prty) {
		cur = cur->next;
	}
	struct wdl_llnode* tmp = cur->next;
	cur->next = create_node(word, prty);
	cur->next->next = tmp;
}

size_t wdl_ll_len(struct wdl_ll* ll) {
	size_t len = 0;
	struct wdl_llnode* cur = ll->root;
	while (cur) {
		len++;
		cur = cur->next;
	}
	return len;
}
