#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* fp;
	if ((fp = fopen("toto", "r")) == 0) {
		perror("Cannot open toto");
		return -1;
	}

	FILE* op;
	if ((op = fopen("titi", "w")) == 0) {
		perror("Cannot open titi");
		return -1;
	}



	char c;
	while ( (c = getc(fp)) != EOF)
		putc(c, op);

	fclose(fp);
	fclose(op);

	return 0;
}
