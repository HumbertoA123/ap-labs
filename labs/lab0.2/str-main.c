//str-main

#include <stdio.h>


int str_len(char*);
char* stradd(char*, char*);
int strfind(char*, char*);

int main(int argc, char **argv) {

	int size, isString;

	if(argc != 4) {
		printf("Invalid number of arguments.\n");
		return -1;
	}

	size = str_len(argv[1]);
	stradd(argv[1], argv[2]);
	isString = strfind(argv[1], argv[3]);

	printf("Initial Lenght:		%i\n", size);
	printf("New String:		%s\n", argv[1]);

	if(isString) {
		printf("Substring was found:	Yes\n");
	}
	else {
		printf("Substring was found:	No\n");
	}

	return 0;
}