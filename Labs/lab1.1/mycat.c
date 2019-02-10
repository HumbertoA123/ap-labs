#include <stdio.h>

FILE *file;
int c;

int main(int argc, char **argv)
{
	file = fopen(argv[1], "r");

	if(file)
	{
		while((c = getc(file)) != EOF)
		{
			printf("%c", c);
		}
	}

	printf("\n");
	fclose(file);

	return 0;
}