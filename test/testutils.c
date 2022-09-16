#include <wdl/utils.h>

#include <wdl/dict.h>
#include <wdl/gen.h>

#include <assert.h>

#include <stdio.h>
#include <string.h>

int main() {
	char w1[6] = "tined";
	char w2[6] = "intel";
	char result[6];
//	struct wdl_dict d;
//	wdl_dict_load(&d, "words.txt");
//	wdl_gen_init(0);
//	wdl_gen(&d, w1);


	wdl_strcmp(w1, w2, result);

	printf("%s\n", result);

}
