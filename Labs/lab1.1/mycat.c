#include <stdio.h>
#include <stdlib.h>

FILE *file, *fileO;
int c;

int main(int argc, char **argv)
{

	file = fopen(argv[1], "r");

	if(file == NULL)
	{
		fprintf(stderr, "No such file\n");
      	exit(EXIT_FAILURE);
	}

	if (argc == 2)
	{
		while((c = getc(file)) != EOF)
		{
			printf("%c", c);
		}
		printf("\n");
	}

	if(argc == 3)
	{
		fileO = fopen(argv[2], "w");
		while((c = getc(file)) != EOF)
		{
			fprintf(fileO, "%c", c);
		}
		fclose(fileO);
	}

	fclose(file);
	return 0;
}