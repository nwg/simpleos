#include "video.h"
#include "syscall.h"
#include "process.h"
#include <string.h>
#include "asm.h"
#include <stdio.h>
#include <stdbool.h>

int atoi(const char *a);

int main(int argc, char **argv) {

	char blah[256];

	int color = atoi(argv[1]) << 8;
	int row = atoi(argv[2]);

	snprintf(blah, 256, "snprintf test: %s %d.", "something", 12345);
	print(row+5, 0, color, blah);

	sys_test();

	sys_add_pages(1);
	*(uint64_t*)USER_HEAP = 50;

	for (int i = 0; i < 80; i++) {

		if (i == 20 && row == 12) {
			print(row, i, color, "*");
			sys_exit();
		}

		print(row, i, color, "\07");
		usleep(100000);
	}

	while (true) {}
}

int atoi(const char *a) {
	int num = 0;
	int mult = 1;
	int len = strlen(a);

	for (int i = len - 1; i >= 0; i--) {
		char c = a[i];
		num += (c - '0') * mult;
		mult *= 10;
	}
	return num;
}
