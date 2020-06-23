#include <stdio.h>
#include <unistd.h>

#define MAX 512

int main(int argc, char* argv[]) {
	char buf[MAX];
	char out[MAX * 2];
	unsigned char c;

	int size = read(0, buf, MAX);

	int index = 0;
	for (int i = 0; i < size; ++i, index+=2) {
		c = buf[i]; // cache
		switch (c) {
		case '\n':
			out[index] = '\\';
			out[index+1] = 'n';
			break;
		case '\t':
			out[index] = '\\';
			out[index+1] = 't';
			break;
		case '\r':
			out[index] = '\\';
			out[index+1] = 'r';
			break;
		case '\b':
			out[index] = '\\';
			out[index+1] = 'b';
			break;
		case '\\':
			out[index] = '\\';
			out[index+1] = '\\';
			break;
		case '\'':
			out[index] = '\\';
			out[index+1] = '\'';
			break;
		case '\"':
			out[index] = '\\';
			out[index+1] = '\"';
			break;
		default:
			if (c >= 32 && c <= 126) { // std 
				out[index] = c;
			}
			else if (c <= 31 || c > 127) { // octal
				index += snprintf(out+index, 5, "\\0%o", (unsigned) c);
			}
			--index;
		}
	}

	printf("%s\n", out);



	return 0;
}
