#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <stdarg.h>


const char* TAG_INFO = "INFO";
const char* TAG_WARNING = "WARNING";
const char* TAG_ERROR = "ERROR";
const char* TAG_PANIC = "PANIC";

int loggerMode = 0;

int initLogger(char* logType)
{
	if(strcmp("stdout", logType))
	{
		loggerMode = 0;
	}
	else if(strcmp("syslog", logType))
	{
		loggerMode = 1;
	}
	else
	{
		printf("Invalid input\n");
		return -1;
	}
	return 0;
}


int infof(const char* tag, const char* message)
{
	if(loggerMode == 0)
	{
		printf("\033[1;32m");
		printf(" [%s]: %s\n", tag, message);
		printf("\033[0m");
	}
	else
	{
		syslog(LOG_USER | LOG_EMERG, "[INFO]: " + message, message);
		printf("%d", loggerMode);
	}

	return 0;
}


int warnf(const char* tag, const char* message)
{
	printf("\033[1;33m");
	printf(" [%s]: %s\n", tag, message);
	printf("\033[0m");

	return 1;
}


int errorf(const char* tag, const char* message)
{
	printf("\033[1;31m");
	printf(" [%s]: %s\n", tag, message);
	printf("\033[0m");

	return -1;
}


int panicf(const char* tag, const char* message)
{
	printf("\033[1;35m");
	printf(" [%s]: %s\n", tag, message);
	printf("\033[0m");

	return -2;
}

/*
int main()
{
	infof(TAG_INFO, "Hello Again");
	warnf(TAG_WARNING, "Hello Again");
	errorf(TAG_ERROR, "Hello Again");
	panicf(TAG_PANIC, "Hello Again");

	return 0;
}
*/