#include <wdl/ll.h>

#include <assert.h>
#include <stdio.h>

#include <stdlib.h>

#define _TEST

int main() {
	struct wdl_ll ll;
	wdl_ll_init(&ll);
	wdl_ll_insert(&ll, "hello");
	printf("Inserted hello\n");
	wdl_ll_insert(&ll, "world");
	printf("Inserted world\n");
	wdl_ll_print(&ll);
	assert(wdl_ll_check(&ll, "hello"));
	assert(!wdl_ll_check(&ll, "rando"));

	printf("\n");
	struct wdl_ll pll;
	wdl_ll_init(&pll);
	wdl_ll_insert_p(&pll, "hello", 10);
	wdl_ll_insert_p(&pll, "world", 5);
	wdl_ll_insert_p(&pll, "rando", 7);
	wdl_ll_print(&pll);
	printf("All tests passed\n");
	return 0;
}
