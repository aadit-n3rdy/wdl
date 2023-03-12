#include <wdl/dict.h>

#include <assert.h>

int main() {
	struct wdl_dict d;

	wdl_dict_load(&d, "words.txt");

	wdl_ll_print(&d.prty);

	return 0;
}
