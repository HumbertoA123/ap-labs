
#include "logger.h"

int main()
{
	initLogger("stdout");
	infof("Info", "This is an info log.");
	warnf("Warning", "This is a warning log.");
	errorf("Error", "This is an error log.");
	panicf("Panic", "This is a panic log.");


	initLogger("syslog");
	infof("Info", "THIS IS AN INFO LOG.");
	warnf("Warning", "This is a warning log.");
	errorf("Error", "This is an error log.");
	panicf("Panic", "This is a panic log.");

	return 0;
}