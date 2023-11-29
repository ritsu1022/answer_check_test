/*
 ============================================================================
 Name        : answer_check_test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define QSIZE 4

static const char qseeds[] = { 'R', 'G', 'B', 'Y', 'M', 'C' };
static const int num_of_colors = sizeof(qseeds)/sizeof(qseeds[0]);

bool chg_input_chars_is_no_dup(const char* buf) {
	size_t length = strlen(buf);

	int freq[num_of_colors];
	memset(freq, 0, sizeof(int) * num_of_colors);

	for (size_t i = 0; i < length; i++) {
		char* offset = memchr(qseeds, toupper(buf[i]), num_of_colors);
		if (offset != NULL) {
			int idx = offset - qseeds;
			freq[idx]++;
		}
	}

	bool ret = true;
	for (int i = 0; i < num_of_colors; i++) {
		if (freq[i] >= 2) {
			printf("同じ文字\"%c\"が%d回使われています\n", qseeds[i], freq[i]);
			ret = false;
		}
	}
	return ret;
}

bool chg_input_chars_is_valid(const char* buf) {
	size_t length = strlen(buf);

	char illegal_chars[QSIZE] = { '\0' };
	int j = 0;
	for (size_t i = 0; i < length; i++) {
		char ch = toupper(buf[i]);
		if (memchr(qseeds, ch, num_of_colors) == NULL) {
			if (memchr(illegal_chars, buf[i],QSIZE) == NULL) {
				illegal_chars[j++] = buf[i];
			}
		}
	}
	if (strlen(illegal_chars) > 0) {
		printf("使えない文字\"%s\"が含まれています。\n", illegal_chars);
		return false;
	}
	return true;
}

bool chg_input_length_is_valid(const char* buf) {
	size_t length = strlen(buf);

	if (length < QSIZE) {
		puts("入力が短すぎます");
		return false;
	}
	if (length > QSIZE) {
		puts("入力が長すぎます");
		return false;
	}
	return true;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char buf[10];
	char* cr;
	const int size = sizeof(buf);
	fgets(buf, size, stdin);
	cr = strchr(buf, '\n');
	if(cr != NULL) {
		*cr = '\0';
	}
	puts(buf);
	if(chg_input_length_is_valid(buf)
		&& chg_input_chars_is_valid(buf)
		&& chg_input_chars_is_no_dup(buf)) {
		puts("入力は妥当です");
	} else {
		puts("入力に不正があります");
	}
	return EXIT_SUCCESS;
}
