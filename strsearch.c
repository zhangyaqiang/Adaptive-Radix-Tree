#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include <time.h>
#include "trie.h"

int main(int argc, char *argv[]) {
	clock_t begin = clock();

	art_tree t;
	int res = art_tree_init(&t);
	if (res != 0) {
		printf("initial error!\n");
	}

	int len;
	char buf[512];
	FILE *pool = fopen(argv[1], "r");
	FILE *check = fopen(argv[2], "r");
	FILE *result = fopen(argv[3], "wb");

	uintptr_t line = 1;
	while (fgets(buf, sizeof(buf), pool)) {
		len = strlen(buf) - 1;
		art_insert(&t, (unsigned char*)buf, len, (void*)line);
	}

	char buf1[512];
	line = 0;
	while (fgets(buf1, sizeof(buf1), check)) {
		len = strlen(buf1);
		if (buf1[len - 2] == '\r')
			buf1[len - 2] = '\0';
		else
			buf1[len - 1] = '\0';

		if (NULL != art_search(&t, (unsigned char*)buf1, strlen(buf1))) {
			fputs("yes\n", result);
			line++;
		}
		else {
			fputs("no\n", result);
		}
	}

	res = art_tree_destroy(&t);
	if (res != 0) {
		printf("destory error\n");
	}
	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time);
	printf("%d\n", line);
	return 0;
}