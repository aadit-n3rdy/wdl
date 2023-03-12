#include <assert.h>

#include <wdl/gen.h>

#include <string.h>
#include <stdio.h>

int main() {
	char buf1[6], buf2[6];
	struct wdl_dict d;
	wdl_dict_load(&d, "words.txt");
	printf("Total words: %zu\n", d.word_count);
	wdl_gen_init(20);
	wdl_gen(&d, buf1);
	printf("%s\n", buf1);
	wdl_gen_init(20);
	wdl_gen(&d, buf2);
	printf("%s\n", buf2);
	assert(strcmp(buf1, buf2) == 0);
}
