const char* TAG_INFO = "INFO";
const char* TAG_WARNING = "WARNING";
const char* TAG_ERROR = "ERROR";
const char* TAG_PANIC = "PANIC";

int initLogger(char* logType);
int infof(const char* tag, const char* message);
int warnf(const char* tag, const char* message);
int errorf(const char* tag, const char* message);
int panicf(const char* tag, const char* message);