#include <stdio.h>
#include <stdlib.h>

#include <wdl/dict.h>
#include <wdl/utils.h>
#include <wdl/gen.h>

#include <stdbool.h>

int main() {
	struct wdl_dict d;
	wdl_dict_load(&d, "words.txt");
	bool done = false;

	char word[6], guess[6], result[6];

	wdl_gen_init(0);
	wdl_gen(&d, word);

	int i = 0;

	while (done != true && i < 6) {
		printf("Enter guess no. %d\n", i+1);
		scanf("%s", guess);
		wdl_strcmp(word, guess, result);
		printf("RESULT: %s\n", result);
		if (wdl_streq(result, "VVVVV")) {
			done = true;
			printf("DONE!!!\n");
			printf("attempts: %d\n", i+1);
			exit(-1);
		}
		i++;
	}
	printf("%s\n", word);

	return 0;
}
