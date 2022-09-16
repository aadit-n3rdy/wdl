#include "wdl/utils.h"

#include <stdbool.h>
#include <string.h>

bool wdl_streq(char* s1, char* s2) {
	while (*s1 != '\0' && *s2 != '\0') {
		if (*s1 != *s2) {
			return false;
		}
		s1++;
		s2++;
	}
	return (*s1 || *s2) ? false : true;
}

void wdl_strcmp(char* w, char* guess, char* result) {
	int i = 0;
	int j = 0;
	char word[6];
	strcpy(word, w);
	strcpy(result, "xxxxx");
	for (i = 0; i < 5; i++) {
		if (guess[i] == word[i]) {
			result[i] = WDL_GREEN;
			word[i] = 'A';
		}
	}
	bool found = false;
	for (i = 0; i < 5; i++) {
		if (word[i] == 'A') {
			continue;
		}
		found = false;
		for (j = 0; j < 5; j++) {
			if (guess[i] == word[j]) {
				result[i] = WDL_YELLOW;
				word[j] = 'X';
				found = true;
				break;
			}
		}
		if (found != true) {
			if (word[i] != 'A') {
				result[i] = WDL_RED;
			}
		}
	}
}
