
#include "logger.h"

int main()
{
	infof(TAG_INFO, "This is an info log.");
	warnf(TAG_WARNING, "This is a warning log.");
	errorf(TAG_ERROR, "This is an error log.");
	panicf(TAG_PANIC, "This is a panic log.");

	return 0;
}