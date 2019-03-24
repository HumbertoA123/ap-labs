#include <stdio.h>
#include <string.h>

const char* base64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char encodedMsg[1024];
char binaryMsg[1024];
char decodedMsg[1024];

int base64encode(char* str);
char bytesB6ToChar(char* str);
int base64decode(char* str);


char bytesB6ToChar(char* str)
{
	int bitsMax = 32;
	int charValue = 0;
	for(int i = 0; i < strlen(str); i++)
	{
		char tmp = str[i];
		char one = '1';
		if(tmp == one)
		{
			charValue += bitsMax;
		}
		bitsMax /= 2;
	}
	return base64chars[charValue];
}


int base64encode(char* str)
{
	int c = 0;
	char* bits;
	int counter = 3;

	//Start base 64 encoding.
	memset(encodedMsg, 0, sizeof encodedMsg);
	memset(binaryMsg, 0, sizeof binaryMsg);
	//Start alphanumeric to bits conversion.
	for(int i = 0; i < strlen(str); i++)
	{
		int bitsMax = 128;

		if(counter == 0)
		{
			counter = 3;
		}

		c = str[i];
		while(bitsMax > 0)
		{
			if((c / bitsMax) >= 1)
			{
				strcat(binaryMsg, "1");
				c = c - bitsMax;
			}
			else
			{
				strcat(binaryMsg, "0");
			}
			bitsMax = bitsMax / 2;
		}
		counter--;
	}

	if(counter == 1)
	{
		strcat(binaryMsg, "q");
	}
	else if(counter  == 2)
	{
		strcat(binaryMsg, "q");
	}
	//End alphanumeric to bits conversion.

	//Start bytes base 6 to alphanumeric conversion.
	char byteB6[6] = "";
	counter = 0;
	int tcounter = 0;
	for(int i = 0; i < strlen(binaryMsg); i++)
	{
		char letter = binaryMsg[i];
		char q = 'q';
		if(letter == q)
		{
			break;
		}
		char tmp = binaryMsg[i];
		byteB6[counter] = tmp;
		counter++;
		if(counter == 6)
		{
			encodedMsg[tcounter] = bytesB6ToChar(byteB6);;
			tcounter++;
			counter = 0;
		}
	}
	//End bytes base 6 to alphanumeric conversion.
	//End base 64 encoding.

	return 0;
}


int base64decode(char* str)
{

	//Start base 64 decoding.
	memset(encodedMsg, 0, sizeof decodedMsg);
	memset(binaryMsg, 0, sizeof binaryMsg);

	printf("%s\n", str);

	for(int i = 0; i < strlen(str); i++)
	{
		for(int k = 0;  base64chars[k] == str[i]; k++)
		{
			printf("%d", k);
		}
	}

	return 0;
}




FILE *fd, *fdOut;

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Invalid number of arguments.\n");
		return -1;
	}

	int c;
	char line[256];
	int linePos = 0;

	if(strcmp(argv[1], "--encode") == 0){

		fd = fopen(argv[2], "r+");
		fdOut = fopen("encoded.txt", "w");

		if(fd)
		{
			while((c = getc(fd)) != EOF)
			{
				if(c == '\n')
				{
					base64encode(line);
					char* encodedLine = encodedMsg;
					fprintf(fdOut, "%s\n", encodedLine);
					memset(line, 0, sizeof line);
					linePos = 0;
				}
				else
				{
					line[linePos] = c;
					linePos++;
				}
			}
		}
		
	}
	else if(strcmp(argv[1], "--decode") == 0)
	{
		fd = fopen(argv[2], "r+");
		fdOut = fopen("decoded.txt", "w");

		if(fd)
		{
			while((c = getc(fd)) != EOF)
			{
				if(c == '\n')
				{
					base64decode(line);
					char* encodedLine = encodedMsg;
					fprintf(fdOut, "%s\n", encodedLine);
					memset(line, 0, sizeof line);
					linePos = 0;
				}
				else
				{
					line[linePos] = c;
					linePos++;
				}
			}
		}
	}
	else
	{
		printf("Invalid flag.\n");
	}
	
	return 0;
}



































