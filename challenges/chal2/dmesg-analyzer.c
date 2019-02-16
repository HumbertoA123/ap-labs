#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#define REPORT_FILE "report.txt"

int fd;
FILE *fdO;
char c;
char* categories[256];

void analizeLog(char *logFile, char *report);
void categorizeLog(char log[], int counter);

struct Log
{
	char type[32];
	char log[256];
}log1;

struct Log logArray[2048];

int main(int argc, char **argv)
{

    if (argc < 2) 
    {
		printf("Usage:./dmesg-analizer.o logfile.txt\n");
		return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    close(fd);

    return 0;
}


void analizeLog(char *logFile, char *report)
{
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.

    fd = open(logFile, O_RDONLY);

    

	int counter = 0;
	while(read(fd, &c, 1) > 0)
	{
		char log[256];
		int i = 0;
		while(c != '\n')
		{
			char tmp = c;
			log[i] = tmp;
			i++;
			read(fd, &c, 1);
		}
		categorizeLog(log, counter);
		counter++;
		memset(log, 0, sizeof log);
	}


	int catCounter = 1;
	categories[0] = "General";
	for(int i = 0; strlen(logArray[i].type) > 0; i++)
	{
		int count = 0;
		for(int j = 0; strlen(logArray[j].type) > 0; j++)
		{
			if(strcmp(logArray[i].type, logArray[j].type) == 0)
			{
				count++;
			}
		}
		if(count > 1)
		{
			int flag = 0;
			for(int k = 0; categories[k] > 0; k++)
			{
				if(strcmp(logArray[i].type, categories[k]) == 0)
				{
					flag = 1;
				}
			}

			if(flag == 0)
			{
				categories[catCounter] = logArray[i].type;
				catCounter++;
			}
		}
		else
		{
			char * general = "General";
			for(int g = 0; g < strlen(general); g++)
			{
				logArray[i].type[g] = general[g];
			}
		}
	}

	fdO = fopen(report, "w");
	for(int l = 0; categories[l] > 0; l++)
	{
		fprintf(fdO, "%s:\n", categories[l]);
		for(int m = 0; strlen(logArray[m].type) > 0; m++)
		{
			if(strcmp(categories[l], logArray[m].type) == 0)
			{
				fprintf(fdO, "	%s\n", logArray[m].log);
			}
		}
	}

    printf("Report is generated at: [%s]\n", report);

    close(fd);
    fclose(fdO);
}


void categorizeLog(char log[], int counter)
{
	int iFlag = 0;
	int flag = 0;
	int flag2 = 0;
	char type[32];
	int j = 0;


	if(iFlag == 0)
	{
		for(int i = 0; i < strlen(log); i++)
		{
			logArray[counter].log[i] = log[i];
		}

		for(int i = 0; i < strlen(log); i++)
		{
			if(counter == 0)
			{
				logArray[counter].type[0] = 'G';
				logArray[counter].type[1] = 'e';
				logArray[counter].type[2] = 'n';
				logArray[counter].type[3] = 'e';
				logArray[counter].type[4] = 'r';
				logArray[counter].type[5] = 'a';
				logArray[counter].type[6] = 'l';
				//printf("HEEEEEEY");
			}
			if((log[i] == ' ' || log[i] == ':')&& flag == 1)
			{
				flag2 = 1;
			}

			else if(log[i] == ']' && flag == 0)
			{
				flag = 1;
				i++;
				while(log[i] == ' ')
				{
					i++;
				}
				i--;
			}

			else if(flag == 1 && flag2 == 0)
			{
				if(counter != 0)
				{
					logArray[counter].type[j] = log[i];
					j++;
				}
			}
		}
	}
	memset(type, 0, sizeof type);
}

























