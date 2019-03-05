#include <stdio.h>
#include <time.h>


const char* TAG_INFO = "INFO";
const char* TAG_WARNING = "WARNING";
const char* TAG_ERROR = "ERROR";
const char* TAG_PANIC = "PANIC";


int infof(const char* tag, const char* message)
{
	printf("\033[1;32m");
	printf(" [%s]: %s\n", tag, message);
	printf("\033[0m");

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
