#include <stdio.h>
#include <unistd.h>

#define MAX 512

int power(int x, int n) {
	return (n<=0) ? 1 : x * power(x,n-1);
}

int is_num(char c) {
	return (c >= '0' && c <= '7');
}

int main(int argc, char* argv[]) {
	char buf[MAX];
	char out[MAX];
	unsigned char c;
	int res;
	char tmp[4];

	int size = read(0, buf, MAX);

	int index = 0;
	int i;
	for (i = 0; index < size; ++i, ++index) {
		c = buf[i]; // cache
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			out[i] = buf[index];

		// special char
		if (c == '\\') {
			++index;
			switch (buf[index]) {
			case 'n':
				out[i] = '\n';
				break;
			case 'r':
				out[i] = '\r';
				break;
			case 't':
				out[i] = '\t';
				break;
			case 'b':
				out[i] = '\b';
				break;
			case '\\':
				out[i] = '\\';
				break;
			case '\'':
				out[i] = '\'';
				break;
			case '\"':
				out[i] = '\"';
				break;
			default: // octal
				//extract up to 3 numbers
				res = 0;
				for (int j = 0; j < 3 && is_num(buf[index]); ++j, ++index) {
					res += buf[index] * power(10, j);
				}
				snprintf(tmp, 4, "\\%d", res);
				snprintf(&(out[i]), 1, tmp);
			}
		}
	}

	for(int j = 0; j < i; ++j)
		putc(out[j], stdout);
	
	return 0;
}
