#include <wdl/gen.h>
#include <wdl/dict.h>
#include <wdl/guesser.h>
#include <wdl/utils.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv) {
	int test_count = 200;
	int total = 0;
	int total_correct = 0;
	if (argc > 1) {
		test_count = atoi(argv[1]);
	}
	printf("Testing %d times...\n", test_count);

	struct wdl_dict d;
	struct wdl_guesser g;
	wdl_gen_init(0);
	wdl_dict_load(&d, "words.txt");
	wdl_guesser_init(&g, &d);
	char word[6], guess[6], result[6] = "xxxxx";
	for (int i = 0; i < test_count; i++) {
		wdl_gen(&d, word);
		strcpy(result, "xxxxx");
		int attempts = 0;
		while (wdl_streq(result, "VVVVV") == false && attempts < 6) {
			wdl_guesser_guess(&g, guess);
			wdl_strcmp(word, guess, result);
			wdl_guesser_update(&g, guess, result);
			attempts++;
		}
		if (wdl_streq(result, "VVVVV")) {
			attempts--;
			total += attempts;
			total_correct++;
		} 
		wdl_guesser_reset(&g);
	}
	printf("Accuracy: %lf %%\n", (double)100.0 * (double)total_correct / (double)test_count);
	printf("Average attempts: %lf\n", (double)total / (double)total_correct);
}
