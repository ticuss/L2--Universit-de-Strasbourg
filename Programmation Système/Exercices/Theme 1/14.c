#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 9

unsigned int lire_16(void) {
	char buf[MAX_SIZE];
	char c;
	unsigned int tmp;
	unsigned int ret = 0;

	if (fgets(buf, MAX_SIZE, stdin) == 0) {
		perror("Unable to read.");
		return 0;
	}

	int len = strlen(buf);
	for(int i = 0; i < len; ++i) { // start at the end
		c = buf[i];
		if (c >= '0' && c <= '9') {
			tmp = c - '0';
		} else if (c >= 'A' && c <= 'F') {
			tmp = c - 'A' + 10;
		} else if (c >= 'a' && c <= 'f') {
			tmp = c - 'a' + 10;
		} else if (c == '\n') {
			break;
		} else {
			fwrite("Error : not a hexadecimal string", 1, 33, stderr);
			exit(-1);
		}

		ret += (tmp << ((len-i-2)* 4));
	}
	return ret;
}

int main() {
	unsigned t = lire_16();
	printf("=> %d\n", t);
	return 0;
}

