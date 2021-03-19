#include <stdio.h>

static FILE *logfile;

void init_logfile();

void log_debug(const char *format, ...);