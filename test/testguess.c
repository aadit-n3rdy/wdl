#include <stdio.h>

#include <wdl/guesser.h>
#include <wdl/dict.h>
#include <wdl/utils.h>
#include <wdl/gen.h>

#include <stdbool.h>

int main() {
	struct wdl_dict d;
	wdl_dict_load(&d, "words.txt");
	struct wdl_guesser g;
	wdl_guesser_init(&g, &d);
	bool done = false;

	char word[6], guess[6], result[6];

	wdl_gen_init(0);
	wdl_gen(&d, word);


	FILE* log = fopen("guesses.txt", "w+");

	printf("Word is %s\n", word);

	fprintf(log, "Word is %s\n\n", word);

	int i = 0;

	while (done != true && i < 10) {
		wdl_guesser_guess(&g, guess);
		printf("Guessed %s\n", guess);
		fprintf(log, "Guess: %s\n", guess);
		wdl_strcmp(word, guess, result);
		printf("Result: %s\n", result);
		if (wdl_streq(result, "VVVVV")) {
			done = true;
			printf("DONE!!!!!!\n");
			printf("Attempts: %d\n", i+1);
			fprintf(log, "\nDone in attempts: %d\n", i+1);
			fclose(log);
			exit(-1);
			break;
		}
		wdl_guesser_update(&g, guess, result);
		i++;
	}
	if (done == false) {
		printf("FAILED!!!!!\n");
	}
	fclose(log);
}
