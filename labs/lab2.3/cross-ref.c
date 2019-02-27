
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

FILE *file;
int c;
int size, lines;
int z = 0;

struct pair
{
	char* value;
	int key;
	int linesOccurrence[350];
	int tableCounter;
}q;

struct pair pairArray[10000];

void display(struct pair table[], int size)
{
	printf("Value\tKey\n");

	for(int m = 0; m < size; m++)
	{
		printf("%s\t%d\n", pairArray[m].value, pairArray[m].key);
	}
}

//unsigned long
unsigned long hash(char *s)
{
    int k;
    size_t h = 0;

    for(k = 1; *s; s++ )
    {
    	h = (h * 10) + *s++ - '0';
    }
    return(h % 131);
}

int toLowercase(int letter)
{
	letter = letter + 32;
	return letter;
}

bool isUpperCase(int letter)
{
	if(letter >= 64 & letter <= 90)
	{
		return true;
	}
	return false;
	
}

void manageLine(char* line, struct pair table[], int l)
{
	char word[32];
	int i = 0;
	int j = 0;
	
	while(line[i] == ' ')
	{
		i++;
	}
	
	
	for(i = i; i < strlen(line); i++)
	{
		if(line[1] == '\0')
		{
			return;
		}

		if(isalpha(line[i]) != 0)
		{
			if(isUpperCase(line[i]))
			{
				line[i] = toLowercase(line[i]);
			}
			word[j] = line[i];
			j++;
		}

		else if(strlen(word) > 0)
		{
			word[j] = '\0';

			int val = hash(word);

			while(table[val].value != NULL && strcmp(table[val].value, word) != 0)
			{
				val++;
			}
	
			pairArray[z].value = word;
			pairArray[z].key = val;
			pairArray[z].linesOccurrence[pairArray[z].tableCounter] = l;
			pairArray[z].tableCounter++;
			z++;

			//pairArray[z] = table;
			//printf("%s : %d\n", table[val].value, table[val].tableCounter);

			//printf("%s\n", table[val].value);

			

			memset(word, 0, sizeof word);
			j = 0;
		}
	}
}


int getSize(FILE *fp)
{
	int i, counter = 0;
	int flag = 0;
	char word[32];
	while((c = getc(fp)) != EOF)
	{
		if(isalpha(c) != 0)
		{
			flag = 1;
		}

		if(c == ' ')
		{
			flag = 0;
			i = 0;
			counter++;
			memset(word, 0, sizeof word);
		}

		if(flag == 1)
		{
			word[i] = c;
		}
	}
	return counter;
}


int main(int argc, char **argv)
{
	file = fopen(argv[1], "r+");
	if(file)
	{
		int size = getSize(file);
		struct pair hashTable[size];

		fseek(file, 0, SEEK_SET );
		char log[256];
		int i = 0;
		int l = 1;
		int flag = 1;

		while((c = getc(file)) != EOF)
		{
			if(flag == 1)
			{
				//printf("%d:	", l);
				flag = 0;
				//l++;
			}

			char tmp = c;
			log[i] = tmp;
			i++;

			if(c == '\n')
			{
				flag = 1;
				i = 0;
				l++;
				manageLine(log, hashTable, l);
				memset(log, 0, sizeof log);
			}
		}
		display(hashTable, 5000);
	}

	fclose(file);
	
	return 0;
}